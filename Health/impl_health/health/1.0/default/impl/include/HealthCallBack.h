/*************************************************************************
* Copyright (C) 2020-2021 GWM Automotive Inc.
*
* The copyright notice above does not evidence any actual
* or intended publication of such source code.
* The code contains GWM Confidential Proprietary Information.
*************************************************************************/

#ifndef VENDOR_GWM_HARDWARE_HEALTH_V1_0_HEALTHCALLBACK_H
#define VENDOR_GWM_HARDWARE_HEALTH_V1_0_HEALTHCALLBACK_H

#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>
#include <vendor/gwm/hardware/health/1.0/IHealthCallBack.h>

typedef float float32_t;

namespace vendor {
namespace gwm {
namespace hardware {
namespace health {
namespace V1_0 {
namespace implementation {


struct HealthCallBack : public IHealthCallBack {
  // Methods from ::vendor::gwm::hardware::health::V1_0::IHealthCallBack
  // follow.
  ::android::hardware::Return<void> gwm_onReportSystemStatus(
      ::vendor::gwm::hardware::health::V1_0::GWM_HealthSystemStatus status)
      override;
  ::android::hardware::Return<void> gwm_onReportSOCBoardTemp(int32_t temp) override;
  ::android::hardware::Return<void> gwm_onReportSOCChipTemp(int32_t temp) override;
  ::android::hardware::Return<void> gwm_onReportVIPBoardTemp(
      float32_t temp,
      ::vendor::gwm::hardware::health::V1_0::GWM_HealthTemperaState tempState)
      override;
  ::android::hardware::Return<void> gwm_onReportVIPChipTemp(float32_t temp) override;
  ::android::hardware::Return<void> gwm_onReportDisPanelTemp(
      ::vendor::gwm::hardware::health::V1_0::GWM_HealthDispIndex dispanel_id,
      int32_t temp) override;
  ::android::hardware::Return<void> gwm_onReportDiskStatus(
      ::vendor::gwm::hardware::health::V1_0::GWM_HealthDiskIndex diskpart_id,
      ::vendor::gwm::hardware::health::V1_0::GWM_HealthDiskStatus status)
      override;
  ::android::hardware::Return<void> gwm_onReqPowerOff(::vendor::gwm::hardware::health::V1_0::GWM_HealthPowerOffReq req) override;

  // Methods from ::android::hidl::base::V1_0::IBase follow.
};

// FIXME: most likely delete, this is only for passthrough implementations
// extern "C" IHealthCallBack* HIDL_FETCH_IHealthCallBack(const char* name);

}  // namespace implementation
}  // namespace V1_0
}  // namespace health
}  // namespace hardware
}  // namespace gwm
}  // namespace vendor
#endif  // VENDOR_GWM_HARDWARE_HEALTH_V1_0_HEALTHCALLBACK_H
