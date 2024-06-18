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
#include "TBoxTSPCom.h"
#include <stdlib.h>

TBoxTSPComListener *gTBoxTspComListener = NULL;
Subscription mSubscriptionTBoxTSPLogin;

bool isTSPLoginSubSet = false;

void TBoxTSPComInit(char *appName, char *configFile) {
    if (configFile) {
        setenv("VSOMEIP_CONFIGURATION", configFile, 1);
    }
    // setenv("VSOMEIP_APPLICATION_NAME", appName, 1);
    if (gRuntime == NULL) {
        gRuntime = CommonAPI::Runtime::get();
    }
    gTboxTSPComProxy =
        gRuntime->buildProxy<TBoxTSPComProxy>("local", "TBoxTSPCom01", appName);
}

bool TBoxTSPComIsReady() { return gTboxTSPComProxy->isAvailable(); }

TBoxTSPLoginState_DT GetTBoxTSPLoginState() {
    CommonAPI::CallStatus callStatus;
    TBoxTSPCom::TBoxTSPLoginState tBoxTspLoginState;
    gTboxTSPComProxy->getTBoxTSPLoginStateAttribute().getValue(
        callStatus, tBoxTspLoginState);
    if (callStatus == CommonAPI::CallStatus::SUCCESS)
        return static_cast<TBoxTSPLoginState_DT>(tBoxTspLoginState.value_);
    else
        return TBoxTSPLoginState_DT::E_UNKNOW_STATE;
}

void TBoxTSPComListenerRegister(TBoxTSPComListener *listener) {
    gTBoxTspComListener = listener;
    isTSPLoginSubSet = true;
    mSubscriptionTBoxTSPLogin = gTboxTSPComProxy->getTBoxTSPLoginStateAttribute()
        .getChangedEvent()
        .subscribe([&](const TBoxTSPCom::TBoxTSPLoginState &val) {
            if (gTBoxTspComListener == NULL)
                return;
            if (!val.validate()) {
                LOGE("TBoxTSPLoginStateChanged TBoxTSPLoginState=%d invalid!\n", val.value_);
                return;
            }
            TBoxTSPLoginState_DT tBoxTspLoginStateDt =
                static_cast<TBoxTSPLoginState_DT>(val.value_);
            gTBoxTspComListener->TBoxTSPLoginStateChangedListener(
                tBoxTspLoginStateDt);
        });
    LOGD("TBoxTSPComListenerRegister end, isTSPLoginSubSet[%d]",isTSPLoginSubSet);
}

void TBoxTSPComListenerUnRegister() {
    LOGD("TBoxTSPComListenerUnRegister start, isTSPLoginSubSet[%d]",isTSPLoginSubSet);
    if(isTSPLoginSubSet){
        isTSPLoginSubSet = false;
        gTboxTSPComProxy->getTBoxTSPLoginStateAttribute()
        .getChangedEvent()
        .unsubscribe(mSubscriptionTBoxTSPLogin);
    }
}
