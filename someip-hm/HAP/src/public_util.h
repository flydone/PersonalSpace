/*************************************************************************
 * Copyright (C) 2023 GWM Automotive Inc.
 *
 * The copyright notice above does not evidence any actual
 * or intended publication of such source code.
 * The code contains GWM Confidential Proprietary Information.
 *************************************************************************/
//
// Created by liangyu on 2023/8/20.
//

#ifndef HVP_SOMEIPTEST_PUBLIC_UTIL_H
#define HVP_SOMEIPTEST_PUBLIC_UTIL_H

#include <CommonAPI/CommonAPI.hpp>
#include <android/log.h>
#include <sys/system_properties.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <v1/GREATWALL_MDC_A_IDC1_5_IDC3_0_HAP/HAVPandAVPFunctionsProxy.hpp>

#include "public_def.h"

#define LOG_TAG "HVP_SOMEIP_TAG"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

using namespace v1::GREATWALL_MDC_A_IDC1_5_IDC3_0_HAP;

extern std::shared_ptr<CommonAPI::Runtime> gRuntime;
extern std::shared_ptr<HAVPandAVPFunctionsProxy<>> gHAVPandAVPFunctionsProxy;

#define DLL_PUBLIC __attribute__((visibility("default")))

#endif // HVP_SOMEIPTEST_PUBLIC_UTIL_H
