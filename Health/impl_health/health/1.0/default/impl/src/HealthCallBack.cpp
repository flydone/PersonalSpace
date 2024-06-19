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
 * @date        2020-9-4

 Module-History:
 Date(dd.mm.year)| Author            | Reason
 The latest entry at the head of the history list.
 4/9/2020         Hong Jiu Jin          Init version

***************************************************************************/
#include "HealthCallBack.h"

namespace vendor {
namespace gwm {
namespace hardware {
namespace health {
namespace V1_0 {
namespace implementation {

using ::android::hardware::Return;
using ::android::hardware::Void;

// Methods from ::vendor::gwm::hardware::health::V1_0::IHealthCallBack follow.
Return<void> HealthCallBack::gwm_onReportSystemStatus(
    ::vendor::gwm::hardware::health::V1_0::GWM_HealthSystemStatus status) {
  // TODO implement
  return Void();
}

Return<void> HealthCallBack::gwm_onReportSOCBoardTemp(int32_t temp) {
  // TODO implement
  return Void();
}

Return<void> HealthCallBack::gwm_onReportSOCChipTemp(int32_t temp) {
  // TODO implement
  return Void();
}

Return<void> HealthCallBack::gwm_onReportVIPBoardTemp(
    float32_t temp,
    ::vendor::gwm::hardware::health::V1_0::GWM_HealthTemperaState tempState) {
  // TODO implement
  return Void();
}

Return<void> HealthCallBack::gwm_onReportVIPChipTemp(float32_t temp) {
  // TODO implement
  return Void();
}

Return<void> HealthCallBack::gwm_onReportDisPanelTemp(
    ::vendor::gwm::hardware::health::V1_0::GWM_HealthDispIndex dispanel_id,
    int32_t temp) {
  // TODO implement
  return Void();
}

Return<void> HealthCallBack::gwm_onReportDiskStatus(
    ::vendor::gwm::hardware::health::V1_0::GWM_HealthDiskIndex diskpart_id,
    ::vendor::gwm::hardware::health::V1_0::GWM_HealthDiskStatus status) {
  // TODO implement
  return Void();
}

// Methods from ::android::hidl::base::V1_0::IBase follow.

// IHealthCallBack* HIDL_FETCH_IHealthCallBack(const char* name) {
// return new HealthCallBack();
//}
//
}  // namespace implementation
}  // namespace V1_0
}  // namespace health
}  // namespace hardware
}  // namespace gwm
}  // namespace vendor
