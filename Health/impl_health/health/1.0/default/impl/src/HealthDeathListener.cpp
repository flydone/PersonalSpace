/*************************************************************************
* Copyright (C) 2020-2021 GWM Automotive Inc.
*
* The copyright notice above does not evidence any actual
* or intended publication of such source code.
* The code contains GWM Confidential Proprietary Information.
*************************************************************************/

/**************************************************************************
 * @file HealthDeathListener.cpp
 * HealthDeathListener
 *
 * @project     v3.5
 * @subsystem
 * @version     0.1
 * @author
 * @date        2021-6-15

 Module-History:
 Date(dd.mm.year)| Author            | Reason
 The latest entry at the head of the history list.
 15/6/2021       Hong Jiu Jin         Init version

***************************************************************************/

#include "HealthDeathListener.h"
#include <log/log.h>

#undef LOG_TAG
#define LOG_TAG "HealthMain_DeathListener"

namespace vendor {
namespace gwm {
namespace hardware {
namespace health {
namespace V1_0 {
namespace implementation {

using ::android::wp;
using ::android::hidl::base::V1_0::IBase;
using namespace android::base;
using namespace std;

HealthDeathListener::HealthDeathListener(Health* health) {
  if (health != nullptr) {
    mHealth = health;
  }
}

HealthDeathListener::~HealthDeathListener() {}
void HealthDeathListener::serviceDied(uint64_t cookie, const wp<IBase>& who) {
  if (mHealth != nullptr) {
    mHealth->onServiceDied();
  }
}

}  // namespace implementation
}  // namespace V1_0
}  // namespace health
}  // namespace hardware
}  // namespace gwm
}  // namespace vendor
