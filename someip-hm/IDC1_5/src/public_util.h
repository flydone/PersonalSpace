/*************************************************************************
 * Copyright (C) 2020 GWM Automotive Inc.
 *
 * The copyright notice above does not evidence any actual
 * or intended publication of such source code.
 * The code contains GWM Confidential Proprietary Information.
 *************************************************************************/
//
// Created by Song Yajing on 2021/11/24.
//

#ifndef IDC1_5_SOMEIPTEST_PUBLIC_UTIL_H
#define IDC1_5_SOMEIPTEST_PUBLIC_UTIL_H

#include <CommonAPI/CommonAPI.hpp>
#include <android/log.h>
#include <sys/system_properties.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <v1/GREATWALL/IDC1_5/IDC1_5SystemFunctionsProxy.hpp>

#include "public_def.h"

#define LOG_TAG "IDC1_5_SOMEIP_TAG"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

using namespace v1::GREATWALL::IDC1_5;

extern std::shared_ptr<CommonAPI::Runtime> gRuntime;
extern std::shared_ptr<IDC1_5SystemFunctionsProxy<>> gIDC1_5SystemFunctionsProxy;

#define DLL_PUBLIC __attribute__((visibility("default")))

#endif // IDC1_5_SOMEIPTEST_PUBLIC_UTIL_H
