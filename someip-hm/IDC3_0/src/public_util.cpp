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
#include "public_util.h"

std::shared_ptr<CommonAPI::Runtime> gRuntime = NULL;
std::shared_ptr<v1::GREATWALL::IDC3_0::HAVPandAVPFunctionsProxy<>> gHAVPandAVPFunctionsProxy = NULL;
