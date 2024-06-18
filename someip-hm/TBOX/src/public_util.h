/*************************************************************************
 * Copyright (C) 2020 GWM Automotive Inc.
 *
 * The copyright notice above does not evidence any actual
 * or intended publication of such source code.
 * The code contains GWM Confidential Proprietary Information.
 *************************************************************************/
//
// Created by yuzhengyang on 2020/8/6.
//

#ifndef SOMEIPTEST_PUBLIC_UTIL_H
#define SOMEIPTEST_PUBLIC_UTIL_H

#include <CommonAPI/CommonAPI.hpp>
#include <android/log.h>
#include <sys/system_properties.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <v1/GREATWALL/TBOX/TBoxSystemFunctionsProxy.hpp>
#include <v1/GREATWALL/TBOX/TBoxTSPComProxy.hpp>
#include <v1/GREATWALL/TBOX/TBoxTelephonyProxy.hpp>
#include <v1/GREATWALL/TBOX/TBoxReservationFunctionsProxy.hpp>
#include <v1/GREATWALL/TBOX/TBoxV2XSystemFunctionsProxy.hpp>


#include "public_def.h"

#define LOG_TAG "SOMEIP_TAG"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

using namespace v1::GREATWALL::TBOX;

extern std::shared_ptr<CommonAPI::Runtime> gRuntime;
extern std::shared_ptr<TBoxTSPComProxy<>> gTboxTSPComProxy;
extern std::shared_ptr<TBoxTelephonyProxy<>> gTboxTelephonyProxy;
extern std::shared_ptr<TBoxSystemFunctionsProxy<>> gTBoxSystemFunctionsProxy;
extern std::shared_ptr<TBoxReservationFunctionsProxy<>> gTBoxReservationFunctionsProxy;
extern std::shared_ptr<TBoxV2XSystemFunctionsProxy<>> gTBoxV2XSystemFunctionsProxy;

#define DLL_PUBLIC __attribute__((visibility("default")))

#endif // SOMEIPTEST_PUBLIC_UTIL_H
