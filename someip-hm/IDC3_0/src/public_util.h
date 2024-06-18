/*************************************************************************
 * Copyright (C) 2022 GWM Automotive Inc.
 *
 * The copyright notice above does not evidence any actual
 * or intended publication of such source code.
 * The code contains GWM Confidential Proprietary Information.
 *************************************************************************/
//
// Created by Zengweifeng on 2022/2/14.
//

#ifndef HAVPANDAVP_FUNCTIONS_SOMEIPTEST_PUBLIC_UTIL_H
#define HAVPANDAVP_FUNCTIONS_SOMEIPTEST_PUBLIC_UTIL_H

#include <CommonAPI/CommonAPI.hpp>
#include <android/log.h>
#include <sys/system_properties.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <v1/GREATWALL/IDC3_0/HAVPandAVPFunctionsProxy.hpp>
#include "public_def.h"

#define LOG_TAG "HAVPandAVPFunctions_SOMEIP_TAG"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

using namespace v1::GREATWALL::IDC3_0;
extern std::shared_ptr<CommonAPI::Runtime> gRuntime;
extern std::shared_ptr<v1::GREATWALL::IDC3_0::HAVPandAVPFunctionsProxy<>> gHAVPandAVPFunctionsProxy;

#define DLL_PUBLIC __attribute__((visibility("default")))

#endif // HAVPANDAVP_FUNCTIONS_SOMEIPTEST_PUBLIC_UTIL_H
