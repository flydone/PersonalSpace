/*************************************************************************
 * Copyright (C) 2021 GWM Automotive Inc.
 *
 * The copyright notice above does not evidence any actual
 * or intended publication of such source code.
 * The code contains GWM Confidential Proprietary Information.
 *************************************************************************/

/*
 * TBoxV2X.h
 *
 *  Created on: Jun 5, 2021
 *      Author: zhangxin
 */

#ifndef SOMEIP_HM_TBOX_SRC_TBOXV2X_H_
#define SOMEIP_HM_TBOX_SRC_TBOXV2X_H_

#include "public_def.h"

typedef enum : uint8_t{
    E_DISABLE_V2XStatus = 0,
    E_OFF_V2XStatus = 1,
    E_ON_V2XStatus = 2
} V2XStatus_DT;

typedef enum : uint8_t{
    E_OFF_V2xLOCKREPONSE = 0,
    E_ON_V2xLOCKREPONSE = 1
} V2XLOCKRequest_DT;

typedef enum : uint8_t{
    E_FAIL_V2XLOCK = 0,
    E_SUCCESS_V2XLOCK = 1
} V2XLOCKRespone_DT;

typedef struct {
    V2XStatus_DT value;
} V2XStatus_out;

typedef struct {
    V2XLOCKRespone_DT value;
} V2XLOCKRespone_out;

/*
typedef TBoxV2XSystemFunctions::V2XStatus V2XStatus_DT;
typedef TBoxV2XSystemFunctions::V2XLOCKRequest V2XLOCKRequest_DT;
typedef TBoxV2XSystemFunctions::V2XLOCKRespone V2XLOCKRespone_DT;
*/

class TBoxV2XSystemFunctionsListener {
public:
    virtual ~TBoxV2XSystemFunctionsListener(){};
    virtual void V2XFunctionStatusListener(V2XStatus_DT status);
};

void TBoxV2XComInit(char *appName, char *configFile);
bool TBoxV2XComIsReady();
CallStatus_DT getV2XFunctionStatus(V2XStatus_out& outV2XStatus);
CallStatus_DT V2XLockSwitch(V2XLOCKRequest_DT inRequest, V2XLOCKRespone_out& outResponse);
Subscription TBoxV2XFunctionListenerRegister(TBoxV2XSystemFunctionsListener* listener);
void TBoxV2XFunctionListenerUnRegister();

#endif /* SOMEIP_HM_TBOX_SRC_TBOXV2X_H_ */
