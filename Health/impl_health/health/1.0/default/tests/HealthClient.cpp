/*************************************************************************
* Copyright (C) 2020-2021 GWM Automotive Inc.
*
* The copyright notice above does not evidence any actual
* or intended publication of such source code.
* The code contains GWM Confidential Proprietary Information.
*************************************************************************/

#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <log/log.h>
#include <android/log.h>
#include <vendor/gwm/hardware/health/1.0/IHealth.h>

#undef LOG_TAG
#define LOG_TAG "HealthMain_HealthClient"

using namespace std;
using namespace android;
using namespace android::hardware;
using namespace vendor::gwm::hardware::health::V1_0;

sp<IHealth> mHealthClient;

struct HealthCallback : public IHealthCallBack {
  Return<void> gwm_onReportVIPBoardTemp(float temp,
                                        GWM_HealthTemperaState tempState) {
    ALOGD("%s, temp = %f, tempState = %d", __func__, temp, tempState);
    return Void();
  }

  Return<void> gwm_onReportVIPChipTemp(float temp) {
    ALOGD("%s, temp = %f", __func__, temp);
    return Void();
  }

  Return<void> gwm_onReportSOCChipTemp(int32_t temp) {
    ALOGD("%s, temp = %d", __func__, temp);
    return Void();
  }

  Return<void> gwm_onReportSOCBoardTemp(int32_t temp) {
    ALOGD("%s, temp = %d", __func__, temp);
    return Void();
  }

  Return<void> gwm_onReportDisPanelTemp(GWM_HealthDispIndex panel_id,
                                        int32_t temp) {
    ALOGD("%s, temp = %d", __func__, temp);
    return Void();
  }

  Return<void> gwm_onReportDiskStatus(GWM_HealthDiskIndex diskpart_idx,
                                      GWM_HealthDiskStatus status) {
    ALOGD("%s, disk_idx = %d, status = %d", __func__, diskpart_idx, status);
    return Void();
  }

  Return<void> gwm_onReportSystemStatus(GWM_HealthSystemStatus status) {
    ALOGD("%s, System status = %d", __func__, status);
    return Void();
  }

  Return<void> gwm_onReqPowerOff(GWM_HealthPowerOffReq req) {
    ALOGD("%s, PowerOff req = %d", __func__, req);
    return Void();
  }
};

int main(int /* argc */, char* /* argv */ []) {
  ALOGI("HealthClient started");
  GWM_StatusCode sc = GWM_StatusCode::ERROR;
  sp<HealthCallback> mHealthCallback;
#if 0
  GWM_HealthSystemStatus status = GWM_HealthSystemStatus::ALIVE;
#endif

  mHealthClient = IHealth::getService();
  if (mHealthClient == nullptr) {
    ALOGE("get Vendor Health service failed!");
    return -1;
  }

  mHealthCallback = new HealthCallback();

  sc = mHealthClient->gwm_registerCallback(mHealthCallback);
  if (sc == GWM_StatusCode::OK) {
    ALOGD("registerCallback OK.");
  } else if (sc == GWM_StatusCode::ERROR) {
    ALOGE("registerCallback fail.");
    return -1;
  }

#if 0
  status = GWM_HealthSystemStatus::ALIVE;
  sc = mHealthClient->sendHeartBeat(status);
  if (sc == GWM_StatusCode::OK) {
    ALOGD("sendHeartBeat OK.");
  } else if (sc == GWM_StatusCode::ERROR) {
    ALOGE("sendHeartBeat fail.");
    return -1;
  }

  GWM_HealthSystemStatus status = GWM_HealthSystemStatus::DEALIVE;
  sc = mHealthClient->sendRestartReq(status);
  if (sc == GWM_StatusCode::OK) {
    ALOGD("sendRestartReq OK.");
  } else if (sc == GWM_StatusCode::ERROR) {
    ALOGE("sendRestartReq fail.");
    return -1;
  }
#endif

  sc = mHealthClient->gwm_systemReady();
  if (sc == GWM_StatusCode::OK) {
    ALOGD("send systemReady OK.");
  } else if (sc == GWM_StatusCode::ERROR) {
    ALOGE("send systemReady FAIL.");
    return -1;
  }

#if 0
  sc = mHealthClient->gwm_systemShutdowm();
  if (sc == GWM_StatusCode::OK) {
    ALOGD("send systemShutdown OK.");
  } else if (sc == GWM_StatusCode::ERROR) {
    ALOGE("send systemShutdown FAIL.");
    return -1;
  }
#endif

  while (1) {
    /* TBD */
  }

  return 0;
}
