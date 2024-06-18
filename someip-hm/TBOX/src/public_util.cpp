/*************************************************************************
 * Copyright (C) 2020 GWM Automotive Inc.
 *
 * The copyright notice above does not evidence any actual
 * or intended publication of such source code.
 * The code contains GWM Confidential Proprietary Information.
 *************************************************************************/
//
// Created by yuzhengyang on 2020/8/7.
//
#include "public_util.h"

std::shared_ptr<CommonAPI::Runtime> gRuntime = NULL;
std::shared_ptr<TBoxTelephonyProxy<>> gTboxTelephonyProxy = NULL;
std::shared_ptr<TBoxTSPComProxy<>> gTboxTSPComProxy = NULL;
std::shared_ptr<TBoxSystemFunctionsProxy<>> gTBoxSystemFunctionsProxy = NULL;
std::shared_ptr<TBoxReservationFunctionsProxy<>> gTBoxReservationFunctionsProxy = NULL;
std::shared_ptr<TBoxV2XSystemFunctionsProxy<>> gTBoxV2XSystemFunctionsProxy = NULL;
