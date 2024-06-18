/*************************************************************************
 * Copyright (C) 2020 GWM Automotive Inc.
 *
 * The copyright notice above does not evidence any actual
 * or intended publication of such source code.
 * The code contains GWM Confidential Proprietary Information.
 *************************************************************************/
//
// Created by yuzhengyang on 2020/8/5.
//

#include "public_util.h"
#include "TBoxTelephony.h"

TBoxTelephonyListener *g_tboxTelephonyListener = NULL;
Subscription mSubscriptionSimStatus;
Subscription mSubscriptionNetwork;
Subscription mSubscriptionCallState;
Subscription mSubscriptionSignal;

bool isSimStatusSubSet = false;
bool isNetworkSubSet = false;
bool isCallStateSubSet = false;
bool isSignalSubSet = false;

void TboxTelephonyInit(char *appName, char *configFile) {
    if (configFile) {
        setenv("VSOMEIP_CONFIGURATION", configFile, 1);
    }
    LOGD("appName = %s  config = %s", appName, configFile);
    if (gRuntime == NULL) {
        gRuntime = CommonAPI::Runtime::get();
    }
    gTboxTelephonyProxy = gRuntime->buildProxy<TBoxTelephonyProxy>(
        "local", "TBoxTelephony01", appName);
}

bool TboxTelephonyIsReady() { return gTboxTelephonyProxy->isAvailable(); }

CallStatus_DT TBoxStartCallFunc(TBoxTelephoneNumber_DT number,
                                TBoxCallType_DT callTypeDt, CallId callId,
                                TBoxCallOperationOut &out) {
    CommonAPI::CallStatus callStatus;
    std::vector<uint8_t> vectorNumber(&number.dynamicBYTE[0],
                                      &number.dynamicBYTE[number.len]);
    TBoxTelephony::TBoxTelephoneNumber phone_number(vectorNumber);
    TBoxTelephony::TBoxCallType call_type(
        static_cast<TBoxTelephony::TBoxCallType::Literal>(callTypeDt));

    TBoxTelephony::TBoxResponse call_response;
    gTboxTelephonyProxy->TBoxStartCall(phone_number, call_type, callId,
                                       callStatus, call_response, out.callId);
    out.tBoxResponseDt = static_cast<TBoxResponse_DT>(call_response.value_);
    return static_cast<CallStatus_DT>(callStatus);
}

CallStatus_DT TBoxCallOperationFunc(TBoxTelephoneNumber_DT number,
                                    TBoxCallType_DT callTypeDt,
                                    TBoxCallOperation_DT tBoxCallOperationDt,
                                    CallId callId, TBoxCallOperationOut &out) {
    CommonAPI::CallStatus callStatus;
    std::vector<uint8_t> vectorNumber(&number.dynamicBYTE[0],
                                      &number.dynamicBYTE[number.len]);
    TBoxTelephony::TBoxTelephoneNumber phone_number(vectorNumber);
    TBoxTelephony::TBoxCallType call_type(
        static_cast<TBoxTelephony::TBoxCallType::Literal>(callTypeDt));
    TBoxTelephony::TBoxCallOperation call_op(
        static_cast<TBoxTelephony::TBoxCallOperation::Literal>(
            tBoxCallOperationDt));
    TBoxTelephony::TBoxResponse call_response;
    gTboxTelephonyProxy->TBoxCallOperation(phone_number, call_type, call_op,
                                           callId, callStatus, call_response,
                                           out.callId);
    out.tBoxResponseDt = static_cast<TBoxResponse_DT>(call_response.value_);
    return static_cast<CallStatus_DT>(callStatus);
}

CallStatus_DT TBoxSIMInforFunc(TBoxSIMInforOut &out) {
    CommonAPI::CallStatus callStatus;
    TBoxTelephony::ICCID valICCID;
    TBoxTelephony::IMEI valIMEI;
    TBoxTelephony::IMSI valIMSI;
    gTboxTelephonyProxy->TBoxSIMInfor(callStatus, valICCID, valIMEI, valIMSI);
    memset(&out, 0x00, sizeof(TBoxSIMInforOut));
    memcpy(out.IMSI, valIMSI.c_str(), valIMSI.length());
    memcpy(out.IMEI, valIMEI.c_str(), valIMEI.length());
    memcpy(out.ICCID, valICCID.c_str(), valICCID.length());

    return static_cast<CallStatus_DT>(callStatus);
}

CallStatus_DT
GetTBoxSimStatusStruct(TBoxSimStatusStruct_DT &tBoxSimStatusStructDt) {
    CommonAPI::CallStatus callStatus;
    TBoxTelephony::TBoxSimStatusStruct simstatus;
    gTboxTelephonyProxy->getTBoxSimStatusAttribute().getValue(callStatus,
                                                              simstatus);
    tBoxSimStatusStructDt.tBoxSimState =
        static_cast<TBoxSimState_DT>(simstatus.getTBoxSimState().value_);
    tBoxSimStatusStructDt.tBoxSimMode =
        static_cast<TBoxSimMode_DT>(simstatus.getTBoxSimMode().value_);
    return static_cast<CallStatus_DT>(callStatus);
}

CallStatus_DT GetTBoxNetworkProviderStruct(
    TBoxNetworkProviderStruct_DT &tBoxNetworkProviderStructDt) {
    CommonAPI::CallStatus callStatus;
    TBoxTelephony::TBoxNetworkProviderStruct tBoxNetworkProviderStruct;
    gTboxTelephonyProxy->getTBoxNetworkProviderAttribute().getValue(
        callStatus, tBoxNetworkProviderStruct);
    tBoxNetworkProviderStructDt.mncDt = tBoxNetworkProviderStruct.getMNC();
    tBoxNetworkProviderStructDt.mccDt = tBoxNetworkProviderStruct.getMCC();
    TBoxTelephony::NetworkProvider networkProvider = tBoxNetworkProviderStruct.getNetworkProvider();
    if (tBoxNetworkProviderStructDt.networkProvider != NULL) {
        memset(tBoxNetworkProviderStructDt.networkProvider, 0x00, PATH_LEN);
        memcpy(tBoxNetworkProviderStructDt.networkProvider, networkProvider.c_str(),
                   networkProvider.length());
    }
    return static_cast<CallStatus_DT>(callStatus);
}

CallStatus_DT GetTBoxSignalStrengthStruct(
    TBoxSignalStrengthStruct_DT &tBoxSignalStrengthStructDt) {
    CommonAPI::CallStatus callStatus;
    TBoxTelephony::TBoxSignalStrengthStruct tBoxSignalStrengthStruct;
    gTboxTelephonyProxy->getTBoxSignalStrengthAttribute().getValue(
        callStatus, tBoxSignalStrengthStruct);
    tBoxSignalStrengthStructDt.signalStrenghRawData =
        tBoxSignalStrengthStruct.getSignalStrengthRawData();
    tBoxSignalStrengthStructDt.tBoxNetTypeDt = static_cast<TBoxNetType_DT>(
        tBoxSignalStrengthStruct.getTBoxNetType().value_);
    return static_cast<CallStatus_DT>(callStatus);
}

void TBoxTelephonyListenerRegister(TBoxTelephonyListener *listener) {
    g_tboxTelephonyListener = listener;
    isSimStatusSubSet = true;
    mSubscriptionSimStatus = gTboxTelephonyProxy->getTBoxSimStatusAttribute()
        .getChangedEvent()
        .subscribe([&](const TBoxTelephony::TBoxSimStatusStruct &val) {
            if (g_tboxTelephonyListener == NULL)
                return;
            if (!val.getTBoxSimState().validate() || !val.getTBoxSimMode().validate()) {
                LOGE("TBoxSimStatusChanged TBoxSimState=%d or TBoxSimMode=%d invalid!\n",
                       val.getTBoxSimState().value_, val.getTBoxSimMode().value_);
                return;
            }
            TBoxSimStatusStruct_DT tBoxSimStatusStructDt;
            tBoxSimStatusStructDt.tBoxSimState =
                static_cast<TBoxSimState_DT>(val.getTBoxSimState().value_);
            tBoxSimStatusStructDt.tBoxSimMode =
                static_cast<TBoxSimMode_DT>(val.getTBoxSimMode().value_);
            g_tboxTelephonyListener->TBoxSimStatusChangedListener(
                tBoxSimStatusStructDt);
        });

    isNetworkSubSet = true;
    mSubscriptionNetwork = gTboxTelephonyProxy->getTBoxNetworkProviderAttribute()
        .getChangedEvent()
        .subscribe([&](const TBoxTelephony::TBoxNetworkProviderStruct &val) {
            if (g_tboxTelephonyListener == NULL)
                return;
            TBoxNetworkProviderStruct_DT tBoxNetworkProviderStructDt;
            TBoxTelephony::NetworkProvider networkProvider = val.getNetworkProvider();
            if (tBoxNetworkProviderStructDt.networkProvider != NULL) {
                memset(tBoxNetworkProviderStructDt.networkProvider, 0x00, PATH_LEN);
                memcpy(tBoxNetworkProviderStructDt.networkProvider, networkProvider.c_str(),
                        networkProvider.length());
            }
            tBoxNetworkProviderStructDt.mccDt = val.getMCC();
            tBoxNetworkProviderStructDt.mncDt = val.getMNC();
            g_tboxTelephonyListener->TBoxNetworkProviderChangedListener(
                tBoxNetworkProviderStructDt);
        });

    isCallStateSubSet = true;
    mSubscriptionCallState = gTboxTelephonyProxy->getTBoxCallStateEvent().subscribe(
        [&](const TBoxTelephony::TBoxTelephoneNumber &telephoneNumber,
            const TBoxTelephony::TBoxCallType &tBoxCallType,
            const TBoxTelephony::TBoxCallState &tBoxCallState,
            const long &callid) {
            if (g_tboxTelephonyListener == NULL)
                return;
            if (!tBoxCallState.validate() || !tBoxCallType.validate()) {
                LOGE("TBoxCallStateEvent TBoxCallState=%d or TBoxCallType=%d invalid!\n",
                        tBoxCallState.value_, tBoxCallType.value_);
                return;
            }
            TBoxCallStateEvent_DT tBoxCallStateEventDt;
            tBoxCallStateEventDt.tBoxTelephoneNumber.len =
                telephoneNumber.size();
            tBoxCallStateEventDt.tBoxTelephoneNumber.setTelephoneNumber(
                (char *)&telephoneNumber[0], telephoneNumber.size());
            tBoxCallStateEventDt.tBoxCallStateDt =
                static_cast<TBoxCallState_DT>(tBoxCallState.value_);
            tBoxCallStateEventDt.tBoxCallTypeDt =
                static_cast<TBoxCallType_DT>(tBoxCallType.value_);
            tBoxCallStateEventDt.callId = callid;
            g_tboxTelephonyListener->TBoxCallStateEventListener(
                tBoxCallStateEventDt);
        });

    isSignalSubSet = true;
    mSubscriptionSignal = gTboxTelephonyProxy->getTBoxSignalStrengthAttribute()
        .getChangedEvent()
        .subscribe([&](const TBoxTelephony::TBoxSignalStrengthStruct &val) {
            if (g_tboxTelephonyListener == NULL)
                return;
            if (!val.getTBoxNetType().validate()) {
                LOGE("TBoxSignalStrengthChanged TBoxNetType=%d invalid!\n", val.getTBoxNetType().value_);
                return;
            }
            TBoxSignalStrengthStruct_DT tBoxSignalStrengthStructDt;
            tBoxSignalStrengthStructDt.tBoxNetTypeDt =
                static_cast<TBoxNetType_DT>(val.getTBoxNetType().value_);
            tBoxSignalStrengthStructDt.signalStrenghRawData =
                val.getSignalStrengthRawData();
            g_tboxTelephonyListener->TBoxSignalStrengthChangedListener(
                tBoxSignalStrengthStructDt);
        });
    LOGD("TBoxTelephonyListenerRegister end, isSimStatusSubSet[%d], isNetworkSubSet[%d], isCallStateSubSet[%d], isSignalSubSet[%d]" ,
        isSimStatusSubSet,isNetworkSubSet, isCallStateSubSet, isSignalSubSet);
}

void TBoxTelephonyListenerUnRegister() {
    LOGD("TBoxTelephonyListenerUnRegister start, isSimStatusSubSet[%d], isNetworkSubSet[%d], isCallStateSubSet[%d], isSignalSubSet[%d] ",
        isSimStatusSubSet,isNetworkSubSet, isCallStateSubSet, isSignalSubSet);
    if(isSimStatusSubSet){
        isSimStatusSubSet = false;
        gTboxTelephonyProxy->getTBoxSimStatusAttribute()
            .getChangedEvent()
            .unsubscribe(mSubscriptionSimStatus);
    }

    if(isNetworkSubSet){
        isNetworkSubSet = false;
        gTboxTelephonyProxy->getTBoxNetworkProviderAttribute()
            .getChangedEvent()
            .unsubscribe(mSubscriptionNetwork);
    }

    if(isCallStateSubSet){
        isCallStateSubSet = false;
        gTboxTelephonyProxy->getTBoxCallStateEvent()
            .unsubscribe(mSubscriptionCallState);
    }

    if(isSignalSubSet){
        isSignalSubSet = false;
        gTboxTelephonyProxy->getTBoxSignalStrengthAttribute()
            .getChangedEvent()
            .unsubscribe(mSubscriptionSignal);
    }

}
