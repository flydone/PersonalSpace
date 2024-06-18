/*************************************************************************
 * Copyright (C) 2021 GWM Automotive Inc.
 *
 * The copyright notice above does not evidence any actual
 * or intended publication of such source code.
 * The code contains GWM Confidential Proprietary Information.
 *************************************************************************/

/*
 * TBoxV2X.cpp
 *
 *  Created on: Jun 5, 2021
 *      Author: zhangxin
 */

#include "public_util.h"
#include "TBoxV2X.h"

#include <v1/GREATWALL/TBOX/TBoxV2XSystemFunctionsSomeIPProxy.hpp>

TBoxV2XSystemFunctionsListener *gTBoxV2XSystemFunctionsListener = NULL;

Subscription mSubscriptionV2XFunction;
bool isV2XFunctionSubSet = false;

void TBoxV2XComInit(char *appName, char *configFile) {
    if (configFile) {
        setenv("VSOMEIP_CONFIGURATION", configFile, 1);
    }
    // setenv("VSOMEIP_APPLICATION_NAME", appName, 1);
    if (gRuntime == NULL) {
        gRuntime = CommonAPI::Runtime::get();
    }
    gTBoxV2XSystemFunctionsProxy =
        gRuntime->buildProxy<TBoxV2XSystemFunctionsProxy>("local", "TBoxV2XSystemFunctions01", appName);
}

bool TBoxV2XComIsReady() { return gTBoxV2XSystemFunctionsProxy->isAvailable(); }

CallStatus_DT getV2XFunctionStatus(V2XStatus_out& outV2XStatus) {
    CommonAPI::CallStatus callStatus;
    TBoxV2XSystemFunctions::V2XStatus v2XStatus;
    LOGD("getV2XFunctionStatus start");
    gTBoxV2XSystemFunctionsProxy->getV2XFunctionStatusAttribute().getValue(callStatus, v2XStatus);
    outV2XStatus.value = static_cast<V2XStatus_DT>(v2XStatus.value_);
    LOGD("getV2XFunctionStatus end:[%d]",v2XStatus.value_);
    return static_cast<CallStatus_DT>(callStatus);
}

CallStatus_DT V2XLockSwitch(V2XLOCKRequest_DT inRequest, V2XLOCKRespone_out& outResponse) {
    CommonAPI::CallStatus callStatus;
    TBoxV2XSystemFunctions::V2XLOCKRespone respone;
    TBoxV2XSystemFunctions::V2XLOCKRequest request;
    request.value_ = inRequest;
    LOGD("V2XLockSwitch start:[%d]",request.value_);
    gTBoxV2XSystemFunctionsProxy->V2XLockSwitch(request, callStatus, respone);
    outResponse.value = static_cast<V2XLOCKRespone_DT>(respone.value_);
    LOGD("V2XLockSwitch end:[%d]",respone.value_);
    return static_cast<CallStatus_DT>(callStatus);
}

Subscription TBoxV2XFunctionListenerRegister(TBoxV2XSystemFunctionsListener* listener) {
    gTBoxV2XSystemFunctionsListener = listener;
    mSubscriptionV2XFunction = gTBoxV2XSystemFunctionsProxy->getV2XFunctionStatusAttribute()
        .getChangedEvent()
        .subscribe([&](const v1::GREATWALL::TBOX::TBoxV2XSystemFunctions::V2XStatus& v2xStatus) {
            LOGD("TBoxV2XFunctionListenerRegister start, isV2XFunctionSubSet[%d]", isV2XFunctionSubSet);
            if (gTBoxV2XSystemFunctionsListener) {
                LOGD("TBoxV2XFunctionListenerRegister: listener->V2XFunctionStatusListener");
                gTBoxV2XSystemFunctionsListener->V2XFunctionStatusListener(static_cast<V2XStatus_DT>(v2xStatus.value_));
            }
        });
    isV2XFunctionSubSet = true;
    LOGD("TBoxV2XFunctionListenerRegister end, isV2XFunctionSubSet[%d]", isV2XFunctionSubSet);
    return mSubscriptionV2XFunction;
}

void TBoxV2XFunctionListenerUnRegister() {
    LOGD("TBoxV2XFunctionListenerUnRegister start, isV2XFunctionSubSet[%d]", isV2XFunctionSubSet);
    if(isV2XFunctionSubSet){
        isV2XFunctionSubSet = false;
        gTBoxV2XSystemFunctionsProxy->getV2XFunctionStatusAttribute()
            .getChangedEvent()
            .unsubscribe(mSubscriptionV2XFunction);
    }
}

