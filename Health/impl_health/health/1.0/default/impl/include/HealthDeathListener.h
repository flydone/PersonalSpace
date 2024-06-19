/*************************************************************************
* Copyright (C) 2020-2021 GWM Automotive Inc.
*
* The copyright notice above does not evidence any actual
* or intended publication of such source code.
* The code contains GWM Confidential Proprietary Information.
*************************************************************************/

#ifndef VENDOR_NOCH_HARDWARE_HEALTH_V1_0_HEALTH_DEATH_H
#define VENDOR_NOCH_HARDWARE_HEALTH_V1_0_HEALTH_DEATH_H

#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>
#include <android-base/file.h>
#include <android-base/logging.h>
#include <android-base/properties.h>
#include <android-base/stringprintf.h>
#include <android-base/strings.h>
#include "Health.h"

namespace vendor {
namespace gwm {
namespace hardware {
namespace health {
namespace V1_0 {
namespace implementation {

class Health;

class HealthDeathListener : public android::hardware::hidl_death_recipient {
 public:
  explicit HealthDeathListener(Health *health);
  virtual ~HealthDeathListener();
  virtual void serviceDied(uint64_t cookie, const ::android::wp<::android::hidl::base::V1_0::IBase> &who) override;

 private:
  Health *mHealth;
};

}  // namespace implementation
}  // namespace V1_0
}  // namespace health
}  // namespace hardware
}  // namespace gwm
}  // namespace vendor
#endif  // VENDOR_NOCH_HARDWARE_HEALTH_V1_0_HEALTH_DEATH_H
