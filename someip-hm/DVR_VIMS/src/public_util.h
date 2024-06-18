/*************************************************************************
 * Copyright (C) 2022 GWM Automotive Inc.
 *
 * The copyright notice above does not evidence any actual
 * or intended publication of such source code.
 * The code contains GWM Confidential Proprietary Information.
 *************************************************************************/
//
// Created by zhaoying on 2021/5/10.
//

#ifndef DVR_VIMS_SOMEIPTEST_PUBLIC_UTIL_H
#define DVR_VIMS_SOMEIPTEST_PUBLIC_UTIL_H

#include <CommonAPI/CommonAPI.hpp>
#include <android/log.h>
#include <sys/system_properties.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <v1/GREATWALL/DVR_VIMS/DVRStatusReportProxy.hpp>
#include <v1/GREATWALL/DVR_VIMS/DVRFileOperationProxy.hpp>
#include <v1/GREATWALL/DVR_VIMS/DVRSystemConfigProxy.hpp>

#include "public_def.h"

#define LOG_TAG "DVR_VIMS_SOMEIP_TAG"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

using namespace v1::GREATWALL::DVR_VIMS;

extern std::shared_ptr<CommonAPI::Runtime> gRuntime;
extern std::shared_ptr<DVRStatusReportProxy<>> gDVRStatusReportProxy;
extern std::shared_ptr<DVRFileOperationProxy<>> gDVRFileOperationProxy;
extern std::shared_ptr<DVRSystemConfigProxy<>> gDVRSystemConfigProxy;

#define DLL_PUBLIC __attribute__((visibility("default")))

#endif // AVP_SOMEIPTEST_PUBLIC_UTIL_H
