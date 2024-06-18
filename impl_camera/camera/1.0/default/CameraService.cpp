 /*************************************************************************
 * Copyright (C) 2020-2021 GWM Automotive Inc.
 *
 * The copyright notice above does not evidence any actual
 * or intended publication of such source code.
 * The code contains GWM Confidential Proprietary Information.
 *************************************************************************/
/**************************************************************************
 * @file CameraService.cpp
 * vendor camera hal implimentation
 *
 * @project     v3.5
 * @subsystem
 * @version     0.1
 * @author      XiuFang Liu
 * @date        2020-7-17

 Module-History:
 Date(dd.mm.year)| Author            | Reason
 The latest entry at the head of the history list.
 17/7/2020         XiuFang Liu         Init version
 ***************************************************************************/
#include <stdio.h>
#include <android/log.h>
#include <utils/SystemClock.h>
#include <hidl/HidlTransportSupport.h>
#include "Camera.h"

#undef LOG_TAG
#define LOG_TAG "CameraHALService"

using namespace android;
using namespace android::hardware;
using namespace vendor::gwm::hardware::camera::V1_0::implementation;
using namespace std::placeholders;
using std::make_unique;

int main(int /* argc */, char* /* argv */ []) {
    auto service = make_unique<Camera>();
    configureRpcThreadpool(4, true);

    ALOGD("Camera HAL service starting");
    status_t status = service->registerAsService();
    if (status != OK) {
        ALOGE("Unable to register Camera HAL service (%d)", status);
        return 1;
    }
    ALOGI("Register Camera HAL Service successfully");
    joinRpcThreadpool();
    return 0;
}

