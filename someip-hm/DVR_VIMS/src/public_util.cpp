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
#include "public_util.h"

std::shared_ptr<CommonAPI::Runtime> gRuntime = NULL;
std::shared_ptr<DVRStatusReportProxy<>> gDVRStatusReportProxy = NULL;
std::shared_ptr<DVRFileOperationProxy<>> gDVRFileOperationProxy = NULL;
std::shared_ptr<DVRSystemConfigProxy<>> gDVRSystemConfigProxy = NULL;

