/*************************************************************************
* Copyright (C) 2020-2021 GWM Automotive Inc.
*
* The copyright notice above does not evidence any actual
* or intended publication of such source code.
* The code contains GWM Confidential Proprietary Information.
*************************************************************************/

#ifndef VENDOR_GWM_HARDWARE_HEALTH_V1_0_HEALTH_H
#define VENDOR_GWM_HARDWARE_HEALTH_V1_0_HEALTH_H

#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>
#include <string.h>
#include <vendor/gwm/hardware/health/1.0/IHealth.h>
#include <vendor/gwm/hardware/health/1.0/types.h>
#include "HealthDeathListener.h"

#define NUMBER_OF_PID_CHANGE 90

typedef float float32_t;

namespace vendor {
namespace gwm {
namespace hardware {
namespace health {
namespace V1_0 {
namespace implementation {


class HealthFdbusClient;
class HealthDeathListener;
#if 0
class SOCThermalFdbClient;
class VIPThermalFdbClient;
#endif
class FdbusClientBase;
class CPUMonitor;
class MemoryMonitor;
class DiskMonitor;
class IptableMonitor;
class EthconfigMonitor;
class HealthThreadWorker;

struct proc_stat {
  std::string proc_name;    /* process name */
  std::string proc_pid;     /* process pid*/
  int32_t nr_pid_chgs; /* number of proc pid chang */
};

class Health : public IHealth {
 public:
  Health();
  virtual ~Health();
  // Methods from ::vendor::gwm::hardware::health::V1_0::IHealth follow.
  ::android::hardware::Return<::vendor::gwm::hardware::health::V1_0::GWM_StatusCode>
  gwm_systemReady() override;

  ::android::hardware::Return<::vendor::gwm::hardware::health::V1_0::GWM_StatusCode>
  gwm_registerCallback(const ::android::sp<IHealthCallBack>& callback) override;

  /* Unused features */
  ::android::hardware::Return<::vendor::gwm::hardware::health::V1_0::GWM_StatusCode>
  gwm_systemShutdowm() override;
  /* Unused features */
  ::android::hardware::Return<::vendor::gwm::hardware::health::V1_0::GWM_StatusCode>
  gwm_systemVcfgUpdate() override;
#if 0
  /* Unused features */
  void onSOCChipTemperature(uint8_t socTemp);
  void onVIPBoardTemperature(float32_t temperature, uint8_t tempstate);
  void onSOCPowerOff(GWM_HealthPowerOffReq req);
#endif
  void checkSystemStatus(int32_t interval);
  GWM_HealthSystemStatus getSystemStatus();
  GWM_StatusCode sendRestartReq(GWM_HealthSystemStatus status);
  GWM_StatusCode sendHeartBeat();
  void onServiceDied();
  void fdbus_init();
  void ResMonitor();
#ifdef GWM_V4_DV
  bool isBootComplete();
  bool getSendSystemReady();
  void sendSystemReady();
#endif

 private:
  std::vector<proc_stat> proc_tbl;
  ::android::sp<HealthThreadWorker> mHealthThreadWorker;
  ::android::sp<HealthFdbusClient> mHealthFdbusClient;
#if 0
  ::android::sp<SOCThermalFdbClient> mSOCThermalFdbClient;
  ::android::sp<VIPThermalFdbClient> mVIPThermalFdbClient;
#endif
  ::android::sp<HealthDeathListener> mHealthDeathListener;
  ::android::sp<CPUMonitor> mCPUMonitor;
  ::android::sp<MemoryMonitor> mMemoryMonitor;
  ::android::sp<DiskMonitor> mDiskMonitor;
  ::android::sp<IptableMonitor> mIptableMonitor;
  ::android::sp<EthconfigMonitor> mEthconfigMonitor;
  ::android::sp<IHealthCallBack> mCallback;

  void monitor_init();
  void proc_tbl_init();
  void setSystemStatus(GWM_HealthSystemStatus status);

  std::string readPid(const std::string& proc_name);
  std::string readCommand(const std::vector<std::string>& commands);

  GWM_HealthSystemStatus mSysStatus = GWM_HealthSystemStatus::ALIVE;
};

// FIXME: most likely delete, this is only for passthrough impls
// extern "C" IHealth* HIDL_FETCH_IHealth(const char* name);

}  // namespace implementation
}  // namespace V1_0
}  // namespace health
}  // namespace hardware
}  // namespace gwm
}  // namespace vendor
#endif  // VENDOR_GWM_HARDWARE_HEALTH_V1_0_HEALTH_H
