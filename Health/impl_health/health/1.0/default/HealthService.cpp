/*************************************************************************
* Copyright (C) 2020-2021 GWM Automotive Inc.
*
* The copyright notice above does not evidence any actual
* or intended publication of such source code.
* The code contains GWM Confidential Proprietary Information.
*************************************************************************/

/**
 * @file     HealthService.cpp
 * @brief    HealthService main file
 * @par      Project: V3.5
 * @par      SW Component: IVI Android Infrastructure
 * @par      SW Package: service
 * @author   Kun Li
 * */
/*===========================================================================
 *
 *              Modification    Tracking
 *              Author          Date       Description of Changes
 *              ------      ------------   -------------
 *              Kun Li       28/6/2020     Init version
 *              ===========================================================*/

#define LOG_TAG "HealthMain_Service"

#include <android/log.h>
#include <hidl/HidlTransportSupport.h>
#include <stdio.h>
#include <utils/SystemClock.h>

#include "Health.h"

using namespace android;
using namespace android::hardware;
using namespace vendor::gwm::hardware::health::V1_0::implementation;
using namespace std::placeholders;

int32_t main(int32_t /* argc */, char** /* argv */ ) {
  auto service = std::make_unique<Health>();
  configureRpcThreadpool(4, true /* callerWillJoin */);
  ALOGD("Health HAL service starting");
  status_t status = service->registerAsService();
  if (status != OK) {
    ALOGE("Unable to register Health HAL service (%d)", status);
    return 1;
  }
  ALOGI("Register HealthHAL Service successfully");
  joinRpcThreadpool();
  return 1;
}
