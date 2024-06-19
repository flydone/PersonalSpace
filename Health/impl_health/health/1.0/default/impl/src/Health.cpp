/*************************************************************************
* Copyright (C) 2020-2021 GWM Automotive Inc.
*
* The copyright notice above does not evidence any actual
* or intended publication of such source code.
* The code contains GWM Confidential Proprietary Information.
*************************************************************************/

/**************************************************************************
 * @file Health.cpp
 * Health Main
 *
 * @project     v3.5
 * @subsystem
 * @version     0.1
 * @author
 * @date        2020-8-21

 Module-History:
 Date(dd.mm.year)| Author            | Reason
 The latest entry at the head of the history list.
 21/8/2020         Hong Jiu Jin          Init version

***************************************************************************/
#include "Health.h"

#include <FdbusClientBase.h>
#include <HealthFdbusClient.h>
#include <SOCThermalFdbClient.h>
#include <VIPThermalFdbClient.h>
#include "CPUMonitor.h"
#include "MemoryMonitor.h"
#include "DiskMonitor.h"
#include "IptableMonitor.h"
#include "EthconfigMonitor.h"
#include <android-base/file.h>
#include <android-base/logging.h>
#include <android-base/properties.h>
#include <android-base/stringprintf.h>
#include <android-base/strings.h>
#include <common_base/fdbus.h>
#include <cutils/properties.h>
#include <log/log.h>
#include <vendor/gwm/hardware/logmaster/1.0/ILog.h>
#include <vendor/gwm/hardware/logmaster/1.0/types.h>

#include "HealthThreadWorker.h"

#undef LOG_TAG
#define LOG_TAG "HealthMain"

namespace vendor {
namespace gwm {
namespace hardware {
namespace health {
namespace V1_0 {
namespace implementation {

using ::android::hardware::Return;
using namespace android::base;
static CBaseWorker main_worker;
using namespace vendor::gwm::hardware::logmaster::V1_0;
namespace NOBOLOG = vendor::gwm::hardware::logmaster::V1_0;

static uint32_t pidInterval = 3U;//restart for PID change interval*NUMBER_OF_PID_CHANGE
static uint32_t lifeSign_interval = 3U;//Send heartbeat interval time

static void fdbus_init_func(Health* this_) {
  ALOGD("%s start to init fdbus clients...", __func__);
  this_->fdbus_init();
}

Health::Health() {
  proc_tbl_init();
  std::thread fdbus_init_thread(fdbus_init_func, this);
  fdbus_init_thread.detach();
  monitor_init();
  mHealthThreadWorker = new HealthThreadWorker(this);
  assert(mHealthThreadWorker != nullptr);
  mHealthThreadWorker->initReportInterval(lifeSign_interval, pidInterval);
  mHealthThreadWorker->start_LifeSignThread();
  mHealthThreadWorker->start_ResMonitorThread();
  mHealthDeathListener = new HealthDeathListener(this);
}

Health::~Health() {
  // Methods from ::android::hidl::base::V1_0::IBase follow.
  if (mHealthThreadWorker != nullptr) {
    mHealthThreadWorker->stop_LifeSignThread();
    mHealthThreadWorker->stop_ResMonitorThread();
  }

  if (mHealthDeathListener != nullptr) {
    if (mCallback != nullptr) {
      mCallback->unlinkToDeath(mHealthDeathListener);
    }
    mHealthDeathListener = nullptr;
  }
}

/* Initializing the proc name for determining whether the pid changing */
void Health::proc_tbl_init() {
  proc_stat vehicle_proc;
  proc_stat audiocontrol_proc;
  proc_stat carlauncher_proc;
  proc_stat nameserver_proc;
  proc_stat beanserver_proc;

  vehicle_proc.proc_name =
      "vendor.gwm.hardware.automotive.vehicle@1.0-service";
  vehicle_proc.proc_pid = "";
  vehicle_proc.nr_pid_chgs = 0;
  proc_tbl.push_back(vehicle_proc);

  audiocontrol_proc.proc_name =
      "vendor.gwm.hardware.automotive.audiocontrol@1.0-service";
  audiocontrol_proc.proc_pid = "";
  audiocontrol_proc.nr_pid_chgs = 0;
  proc_tbl.push_back(audiocontrol_proc);

  carlauncher_proc.proc_name = "com.gwm.app.gwmscenelauncher";
  carlauncher_proc.proc_pid = "";
  carlauncher_proc.nr_pid_chgs = 0;
  proc_tbl.push_back(carlauncher_proc);

  nameserver_proc.proc_name = "name-server";
  nameserver_proc.proc_pid = "";
  nameserver_proc.nr_pid_chgs = 0;
  proc_tbl.push_back(nameserver_proc);

#if 0
  beanserver_proc.proc_name = "com.beantechs.adapterservice.server.adapter";
  beanserver_proc.proc_pid = "";
  beanserver_proc.nr_pid_chgs = 0;
  proc_tbl.push_back(beanserver_proc);
#endif
}

/* Initializing fdbus for connecting */
void Health::fdbus_init() {
  /* start fdbus context thread */
  FDB_CONTEXT->start();

  /* start worker thread */
  CBaseWorker* worker_ptr = &main_worker;
  worker_ptr->start();

  /* create client to connect lifecycle server */
  std::string lifecycle_ipc_srv_name = "fdbus_lifecycle_qnx";
  std::string lifecyclesrv_url(FDB_URL_SVC);
  lifecyclesrv_url += lifecycle_ipc_srv_name;

  mHealthFdbusClient = new HealthFdbusClient(
      lifecyclesrv_url, lifecycle_ipc_srv_name, worker_ptr, this);
  assert(mHealthFdbusClient != nullptr);

  mHealthFdbusClient->enableReconnect(true);
  mHealthFdbusClient->connect(lifecyclesrv_url.c_str());
#if 0
  /* create client to connect backlight server
   * qnx integrate soc thermal proto into backlight
   *
   * Unused features
   */
  std::string socthermal_ipc_srv_name = "fdbus_info";
  std::string socthermal_ipc_srv_url(FDB_URL_SVC);
  socthermal_ipc_srv_url += socthermal_ipc_srv_name;

  mSOCThermalFdbClient = new SOCThermalFdbClient(
      socthermal_ipc_srv_url, socthermal_ipc_srv_name, worker_ptr, this);
  assert(mSOCThermalFdbClient != nullptr);

  mSOCThermalFdbClient->enableReconnect(true);
  mSOCThermalFdbClient->connect(socthermal_ipc_srv_url.c_str());

  /* create client to connect mcu ipc fdbus server */
  /* Unused features */
  std::string vipthermal_ipc_srv_name = "fdbus_mcu_ipc";
  std::string vipthermal_ipc_srv_url(FDB_URL_SVC);
  vipthermal_ipc_srv_url += vipthermal_ipc_srv_name;

  mVIPThermalFdbClient = new VIPThermalFdbClient(
      vipthermal_ipc_srv_url, vipthermal_ipc_srv_name, worker_ptr, this);
  assert(mVIPThermalFdbClient != nullptr);

  mVIPThermalFdbClient->enableReconnect(true);
  mVIPThermalFdbClient->connect(vipthermal_ipc_srv_url.c_str());
#endif
}

/* Initializing monitor for getting cpu,memory,disk,eth info */
void Health::monitor_init() {
  mCPUMonitor = new CPUMonitor();
  assert(mCPUMonitor != nullptr);
  mMemoryMonitor = new MemoryMonitor();
  assert(mMemoryMonitor != nullptr);
  mDiskMonitor = new DiskMonitor();
  assert(mDiskMonitor != nullptr);
  mIptableMonitor = new IptableMonitor();
  assert(mIptableMonitor != nullptr);
  mEthconfigMonitor = new EthconfigMonitor();
  assert(mEthconfigMonitor != nullptr);
}

void Health::ResMonitor() {
  if (mCPUMonitor != nullptr) {
    mCPUMonitor->dumpResource();
  }
  if (mMemoryMonitor != nullptr) {
    mMemoryMonitor->dumpResource();
  }
  if (mDiskMonitor != nullptr) {
    mDiskMonitor->dumpResource();
  }
  if (mIptableMonitor != nullptr) {
    mIptableMonitor->dumpResource();
  }
  if (mEthconfigMonitor != nullptr) {
    mEthconfigMonitor->dumpResource();
  }
}

std::string Health::readPid(const std::string& proc_name) {
  static const string pidof_cmd = string("/system/bin/pidof");
  std::string content = readCommand({pidof_cmd, proc_name});
  return content;
}

/* Utility functions */
std::string Health::readCommand(const std::vector<std::string>& commands) {
  std::string cmds_str = android::base::Join(commands, ' ');
  /* ALOGD("%s: cmds_str: %s", __func__, cmds_str.c_str());*/
  FILE* fp = popen(cmds_str.c_str(), "r");
  std::string content;
  ReadFdToString(fileno(fp), &content);
  pclose(fp);
  return content;
}

/* check pid changing function for Restart */
void Health::checkSystemStatus(int32_t interval) {
  std::string curr_pid;
  for (vector<proc_stat>::iterator ite = proc_tbl.begin();
       ite != proc_tbl.end(); ++ite) {
    proc_stat element = *ite;
    curr_pid = readPid(element.proc_name.c_str());
    if (!curr_pid.empty()) {
      if ((*ite).proc_pid.empty()) {
        (*ite).proc_pid = curr_pid;
      } else if (curr_pid != (*ite).proc_pid) {
        (*ite).nr_pid_chgs++;
        (*ite).proc_pid = curr_pid;
#if 0
        ALOGI("proc_name = %s, proc_pid = %s, nr_pid_chgs = %d, curr_pid = %s",
              element.proc_name.c_str(), element.proc_pid.c_str(),
              element.nr_pid_chgs, curr_pid.c_str());
#endif
      }
    }

    if (((*ite).nr_pid_chgs) == (NUMBER_OF_PID_CHANGE * interval)) {
      setSystemStatus(GWM_HealthSystemStatus::DEALIVE);
      ALOGI("proc_name = %s, nr_pid_chgs = %d, curr_pid = %s",
            element.proc_name.c_str(), element.nr_pid_chgs, curr_pid.c_str());
      ALOGI("notify DEALIVE event to QNX Lifecycle");
    }
  }
}

void Health::setSystemStatus(GWM_HealthSystemStatus status) {
  mSysStatus = status;
}

GWM_HealthSystemStatus Health::getSystemStatus() { return mSysStatus; }

/* Restart function for HealthFdbus */
GWM_StatusCode Health::sendRestartReq(GWM_HealthSystemStatus status) {
  // TODO implement
  /* ALOGI("%s enter interface", __func__); */
  GWM_StatusCode sc = GWM_StatusCode::ERROR;
  if (mHealthFdbusClient != nullptr) {
    sc = mHealthFdbusClient->sendRestartReq((int32_t)status);
  }
  return sc;
}

/* sendHeartBeat function for HealthFdbus */
GWM_StatusCode Health::sendHeartBeat() {
  // TODO implement
  /* ALOGI("%s enter interface", __func__); */
  GWM_StatusCode sc = GWM_StatusCode::ERROR;
  GWM_HealthSystemStatus status = getSystemStatus();
  if (mHealthFdbusClient != nullptr) {
    sc = mHealthFdbusClient->sendHeartBeat((int32_t)status);
  }
  return sc;
}

#ifdef GWM_V4_DV
static bool isSendSystemReady = false;
bool Health::getSendSystemReady() {
    return isSendSystemReady;
}

bool Health::isBootComplete() {
    bool ret = false;
    char val[PROPERTY_VALUE_MAX] = {};

    property_get("sys.boot_completed", val, "0");

    if(std::string(val) == "1"){
        ALOGD("isBootComplete true");
        ret = true;
    }else{
        ALOGD("isBootComplete false");
    }
    return ret;
}

void Health::sendSystemReady() {
    ALOGD("%s v4_dv platform, Health send SystemReady by self", __func__);
    GWM_StatusCode sc = GWM_StatusCode::ERROR;
    if(!getSendSystemReady()) {
        if(isBootComplete()) {
            sc = gwm_systemReady();
            if (sc == GWM_StatusCode::OK) {
                isSendSystemReady = true;
                ALOGI("send systemReady OK.");
            } else if (sc == GWM_StatusCode::ERROR) {
                ALOGE("send systemReady FAIL.");
            }
        }
    }
}
#endif

// Methods from ::vendor::gwm::hardware::health::V1_0::IHealth follow.
Return<GWM_StatusCode> Health::gwm_systemReady() {
  // TODO implement
  ALOGI("%s enter interface", __func__);
  lifecycle::IviReadyNotify msg;
  lifecycle::IviReadyStatus new_status;
  new_status = lifecycle::IviReadyStatus::IVI_READY;
  msg.set_ivi_ready_status(new_status);
  CFdbProtoMsgBuilder builder(msg);
  if (mHealthFdbusClient == nullptr) {
    ALOGE("%s client create fdbus fail", __func__);
    return GWM_StatusCode::ERROR;
  }
  if (mHealthFdbusClient->getConnectStatus() == false) {
    ALOGE("%s connect to fdbus fail", __func__);
    return GWM_StatusCode::ERROR;
  }

  GWM_StatusCode sc = mHealthFdbusClient->sendMessage(
      lifecycle::EventMsgId::IVI_READY_NOTIFY, builder);

  sp<ILog> logMasterClient;
  logMasterClient = ILog::getService();
  if (logMasterClient != nullptr) {
      auto ret = logMasterClient->gwm_notifyEvent(NOBOLOG::GWM_Event::BOOT_COMPLETED);
      if (!ret.isOk()) {
          ALOGE("%s gwm_notifyEvent failed", __func__);
      }
  } else {
      ALOGE("%s getService logMaster error", __func__);
  }

  return sc;
}

Return<::vendor::gwm::hardware::health::V1_0::GWM_StatusCode>
Health::gwm_registerCallback(const sp<
    ::vendor::gwm::hardware::health::V1_0::IHealthCallBack>& callback) {
  GWM_StatusCode status = GWM_StatusCode::ERROR;
  // TODO implement
  if (callback != nullptr) {
    mCallback = callback;
    status = GWM_StatusCode::OK;
    mCallback->linkToDeath(mHealthDeathListener, 10 /*cookies*/);
  }

  return status;
}

void Health::onServiceDied() {
  ALOGD("%s", __func__);
  if (mCallback != nullptr) {
    mCallback = nullptr;
  }
}

/* Unused features */
// Methods from ::vendor::gwm::hardware::health::V1_0::IHealth follow.
Return<GWM_StatusCode> Health::gwm_systemShutdowm() {
  return GWM_StatusCode::ERROR;
#if 0
  // TODO implement
  ALOGI("%s enter gwm_systemShutdowm", __func__);
  lifecycle::IviShutdownNotify msg;
  lifecycle::IviShutdownReason new_status;
  new_status = lifecycle::IviShutdownReason::POWER_OFF;
  msg.set_reason(new_status);
  CFdbProtoMsgBuilder builder(msg);
  if (mHealthFdbusClient == nullptr) {
    ALOGE("%s client create fdbus fail", __func__);
    return GWM_StatusCode::ERROR;
  }
  if (mHealthFdbusClient->getConnectStatus() == false) {
    ALOGE("%s connect to fdbus fail", __func__);
    return GWM_StatusCode::ERROR;
  }
  ALOGI("%s enter sendMessage", __func__);
  GWM_StatusCode sc = mHealthFdbusClient->sendMessage(
      lifecycle::EventMsgId::IVI_SHUTDOWN_NOTIFY, builder);
  return sc;
#endif
}

/* Unused features */
Return<GWM_StatusCode> Health::gwm_systemVcfgUpdate() {
  return GWM_StatusCode::ERROR;
#if 0
  // TODO implement
  ALOGI("%s enter gwm_systemVcfgUpdate", __func__);
  lifecycle::IviShutdownNotify msg;
  lifecycle::IviShutdownReason new_status;
  new_status = lifecycle::IviShutdownReason::VCFG_UPDATE;
  msg.set_reason(new_status);
  CFdbProtoMsgBuilder builder(msg);
  if (mHealthFdbusClient == nullptr) {
    ALOGE("%s client create fdbus fail", __func__);
    return GWM_StatusCode::ERROR;
  }
  if (mHealthFdbusClient->getConnectStatus() == false) {
    ALOGE("%s connect to fdbus fail", __func__);
    return GWM_StatusCode::ERROR;
  }
  ALOGI("%s enter sendMessage", __func__);
  GWM_StatusCode sc = mHealthFdbusClient->sendMessage(
      lifecycle::EventMsgId::IVI_SHUTDOWN_NOTIFY, builder);
  return sc;
#endif
}

#if 0
/* Unused features */
void Health::onSOCChipTemperature(uint8_t socTemp) {
  if (mCallback != nullptr) {
    auto ret = mCallback->gwm_onReportSOCChipTemp(socTemp);
    if (!ret.isOk()) {
      ALOGI("%s  has error", __func__);
    }
  }
}

/* Unused features */
void Health::onVIPBoardTemperature(float32_t temperature, uint8_t tempState) {
  if (mCallback != nullptr) {
    GWM_HealthTemperaState state = GWM_HealthTemperaState::NORMAL;
    bool invalidState = false;
    switch (tempState) {
      case 0x00U:
        state = GWM_HealthTemperaState::LOW_SLEEP;
        break;
      case 0x01U:
        state = GWM_HealthTemperaState::NORMAL;
        break;
      case 0x02u:
        state = GWM_HealthTemperaState::HIGH_PROTECT;
        break;
      case 0x03U:
        state = GWM_HealthTemperaState::HIGH_SLEEP;
        break;
      default:
        ALOGD("%s: VIP Report unexpected tempstate", __func__);
        invalidState = true;
        break;
    }

    /* Temperature(254.0) indicate hardware exception, temperature exceed */

    if (!invalidState && mCallback != nullptr) {
      /* ALOGD("%s: VIP Board temperature:%f, temperature state:%x", __func__,
            temperature, tempState); */
      auto ret = mCallback->gwm_onReportVIPBoardTemp(temperature, state);
      if (!ret.isOk()) {
        ALOGI("%s  has error", __func__);
      }
    }
  }
}

/* Unused features */
void Health::onSOCPowerOff(GWM_HealthPowerOffReq req) {
  if (mCallback != nullptr) {
    auto ret = mCallback->gwm_onReqPowerOff(req);
    if (!ret.isOk()) {
      ALOGI("%s  has error", __func__);
    }
  }
}
#endif

// Methods from ::android::hidl::base::V1_0::IBase follow.

// IHealth* HIDL_FETCH_IHealth(const char* name) {
// return new Health();
//}
//
}  // namespace implementation
}  // namespace V1_0
}  // namespace health
}  // namespace hardware
}  // namespace gwm
}  // namespace vendor
