/*************************************************************************
 * Copyright (C) 2020 GWM Automotive Inc.
 *
 * The copyright notice above does not evidence any actual
 * or intended publication of such source code.
 * The code contains GWM Confidential Proprietary Information.
 *************************************************************************/
//
// Created by yuzhengyang on 2020/12/10.
//

#include "public_util.h"
#include "TBoxReservationFunctions.h"

TBoxReservationFunctionsListener* gTBoxReservationFunctionsListener = NULL;
TBoxFOTAReservationFunctionsListener* gTBoxFOTAReservationFunctionsListener = NULL;
TBoxChargeReservationFunctionsListener* gTBoxChargeReservationFunctionsListener = NULL;
Subscription mSubscriptionFOTAReservation;
Subscription mSubscriptionChargeReservation;

bool isFOTAReservationSubSet = false;
bool isChargeReservationSubSet = false;

void TBoxReservationFunctionsInit(char *appName, char *configFile) {
    if (configFile) {
        setenv("VSOMEIP_CONFIGURATION", configFile, 1);
    }
    if (gRuntime == NULL) {
        gRuntime = CommonAPI::Runtime::get();
    }
    gTBoxReservationFunctionsProxy = gRuntime->buildProxy<TBoxReservationFunctionsProxy>(
        "local", "TBoxReservationFunctions01", appName);
}

bool TBoxReservationFunctionsIsReady() {
    return gTBoxReservationFunctionsProxy->isAvailable();
}

CallStatus_DT LocalFOTAReservationFunc(ReservationOperation_DT reservationOption,
        char time[TIME_LEN], TBoxResponse_DT & response)
{
    CommonAPI::CallStatus callStatus;
    TBoxReservationFunctions::ReservationOperation reservationOp(
            static_cast<TBoxReservationFunctions::ReservationOperation::Literal>(reservationOption));
    TBoxReservationFunctions::TimeArray timeArray(&time[0],
                                      &time[TIME_LEN]);
    TBoxReservationFunctions::ReservationACK resp;
    gTBoxReservationFunctionsProxy->LocalFOTAReservation(reservationOp, timeArray, callStatus, resp);
    response = static_cast<TBoxResponse_DT>(resp.value_);

    return static_cast<CallStatus_DT>(callStatus);
}

CallStatus_DT LocalFOTAReservationFunc(ReservationOperation_DT reservationOption,
        char time[TIME_LEN], TBoxResponse_DT & response, int32_t timeout)
{
    CommonAPI::CallStatus callStatus;
    CommonAPI::CallInfo callInfo;
    callInfo.timeout_ = timeout;
    TBoxReservationFunctions::ReservationOperation reservationOp(
            static_cast<TBoxReservationFunctions::ReservationOperation::Literal>(reservationOption));
    TBoxReservationFunctions::TimeArray timeArray(&time[0],
                                      &time[TIME_LEN]);
    TBoxReservationFunctions::ReservationACK resp;
    gTBoxReservationFunctionsProxy->LocalFOTAReservation(reservationOp, timeArray, callStatus, resp, &callInfo);
    response = static_cast<TBoxResponse_DT>(resp.value_);

    return static_cast<CallStatus_DT>(callStatus);
}

void TBoxReservationFunctionsListenerRegister(TBoxReservationFunctionsListener *listener)
{
    gTBoxReservationFunctionsListener = listener;
    isFOTAReservationSubSet = true;
    mSubscriptionFOTAReservation = gTBoxReservationFunctionsProxy->getRemoteFOTAReservationEvent().subscribe(
            [&](TBoxReservationFunctions::ReservationOperation  opration,
                TBoxReservationFunctions::TimeArray time){
                if (gTBoxReservationFunctionsListener) {
                    char timeChr[TIME_LEN];
                    memset(timeChr, 0x00, TIME_LEN);
                    memcpy(timeChr, &time[0], time.size());
                    gTBoxReservationFunctionsListener->FOTAReservationEventListener(
                            static_cast<ReservationOperation_DT>(opration.value_), timeChr);
                }
            });

    isChargeReservationSubSet = true;
    mSubscriptionChargeReservation = gTBoxReservationFunctionsProxy->getRemoteChargeReservationEvent().subscribe(
            [&](TBoxReservationFunctions::ChargMode charMode,
                TBoxReservationFunctions::TimeArray timeStart,
                TBoxReservationFunctions::Repeat repeat,
                TBoxReservationFunctions::TimeArray timeEnd){
                if (gTBoxReservationFunctionsListener) {
                    ChargMode_DT chargMode_DT = static_cast<ChargMode_DT>(charMode.value_);
                    Repeat_DT repeat_DT = static_cast<Repeat_DT>(repeat.value_);
                    char start[TIME_LEN];
                    memset(start, 0x00, TIME_LEN);
                    memcpy(start, &timeStart[0], timeStart.size());
                    char end[TIME_LEN];
                    memset(end, 0x00, TIME_LEN);
                    memcpy(end, &timeEnd[0], timeEnd.size());
                    gTBoxReservationFunctionsListener->RemoteChargeReservationEventListener(
                            chargMode_DT, repeat_DT, start, end);
                }
            });
    LOGD("TBoxReservationFunctionsListenerRegister end, isFOTAReservationSubSet[%d], isChargeReservationSubSet[%d]",
        isFOTAReservationSubSet, isChargeReservationSubSet);
}

void TBoxReservationFunctionsListenerUnRegister()
{
    LOGD("TBoxReservationFunctionsListenerUnRegister start, isFOTAReservationSubSet[%d], isChargeReservationSubSet[%d]",
        isFOTAReservationSubSet, isChargeReservationSubSet);
    if(isFOTAReservationSubSet){
        isFOTAReservationSubSet = false;
        gTBoxReservationFunctionsProxy->getRemoteFOTAReservationEvent().unsubscribe(mSubscriptionFOTAReservation);
    }

    if(isChargeReservationSubSet){
        isChargeReservationSubSet = false;
        gTBoxReservationFunctionsProxy->getRemoteChargeReservationEvent().unsubscribe(mSubscriptionChargeReservation);
    }

}

void TBoxFOTAReservationFunctionsListenerRegister(TBoxFOTAReservationFunctionsListener *listener)
{
    gTBoxFOTAReservationFunctionsListener = listener;
    isFOTAReservationSubSet = true;
    mSubscriptionFOTAReservation = gTBoxReservationFunctionsProxy->getRemoteFOTAReservationEvent().subscribe(
            [&](TBoxReservationFunctions::ReservationOperation  opration,
                TBoxReservationFunctions::TimeArray time){
                if (gTBoxFOTAReservationFunctionsListener) {
                    char timeChr[TIME_LEN];
                    memset(timeChr, 0x00, TIME_LEN);
                    memcpy(timeChr, &time[0], time.size());
                    gTBoxFOTAReservationFunctionsListener->FOTAReservationEventListener(
                            static_cast<ReservationOperation_DT>(opration.value_), timeChr);
                }
            });
    LOGD("TBoxFOTAReservationFunctionsListenerRegister end, isFOTAReservationSubSet[%d]", isFOTAReservationSubSet);
}
void TBoxChargeReservationFunctionsListenerRegister(TBoxChargeReservationFunctionsListener *listener)
{
    gTBoxChargeReservationFunctionsListener = listener;
    isChargeReservationSubSet = true;
    mSubscriptionChargeReservation = gTBoxReservationFunctionsProxy->getRemoteChargeReservationEvent().subscribe(
            [&](TBoxReservationFunctions::ChargMode charMode,
                TBoxReservationFunctions::TimeArray timeStart,
                TBoxReservationFunctions::Repeat repeat,
                TBoxReservationFunctions::TimeArray timeEnd){
                if (gTBoxChargeReservationFunctionsListener) {
                    ChargMode_DT chargMode_DT = static_cast<ChargMode_DT>(charMode.value_);
                    Repeat_DT repeat_DT = static_cast<Repeat_DT>(repeat.value_);
                    char start[TIME_LEN];
                    memset(start, 0x00, TIME_LEN);
                    memcpy(start, &timeStart[0], timeStart.size());
                    char end[TIME_LEN];
                    memset(end, 0x00, TIME_LEN);
                    memcpy(end, &timeEnd[0], timeEnd.size());
                    gTBoxChargeReservationFunctionsListener->RemoteChargeReservationEventListener(
                            chargMode_DT, repeat_DT, start, end);
                }
            });
    LOGD("TBoxChargeReservationFunctionsListenerRegister end, isChargeReservationSubSet[%d]", isChargeReservationSubSet);
}

void TBoxFOTAReservationFunctionsListenerUnRegister()
{
    LOGD("TBoxFOTAReservationFunctionsListenerUnRegister start, isFOTAReservationSubSet[%d]", isFOTAReservationSubSet);
    if(isFOTAReservationSubSet){
        isFOTAReservationSubSet = false;
        gTBoxReservationFunctionsProxy->getRemoteFOTAReservationEvent().unsubscribe(mSubscriptionFOTAReservation);
    }
}

void TBoxChargeReservationFunctionsListenerUnRegister()
{
    LOGD("TBoxChargeReservationFunctionsListenerUnRegister start, isChargeReservationSubSet[%d]", isChargeReservationSubSet);
    if(isChargeReservationSubSet){
        isChargeReservationSubSet = false;
        gTBoxReservationFunctionsProxy->getRemoteChargeReservationEvent().unsubscribe(mSubscriptionChargeReservation);
    }
}

CallStatus_DT FOTAReservationResponeFunc(TBoxResponse_DT respone)
{
    CommonAPI::CallStatus callStatus;
    TBoxReservationFunctions::ReservationACK resp;
    resp.value_ = respone;
    gTBoxReservationFunctionsProxy->RemoteFOTAReservation(resp, callStatus);

    return static_cast<CallStatus_DT>(callStatus);
}

CallStatus_DT RemoteChargeReservationFunc(TBoxResponse_DT respone)
{
    CommonAPI::CallStatus callStatus;
    TBoxReservationFunctions::ReservationACK resp;
    resp.value_ = respone;
    gTBoxReservationFunctionsProxy->RemoteChargeReservation(resp, callStatus);

    return static_cast<CallStatus_DT>(callStatus);
}

CallStatus_DT GetLocalFOTAResPar(LocalFOTAResParStruct_DT &out)
{
    CommonAPI::CallStatus callStatus;
    TBoxReservationFunctions::LocalFOTAResParStruct resParStruct;
    gTBoxReservationFunctionsProxy->getLocalFOTAResParAttribute().getValue(callStatus, resParStruct);
    out.operation = static_cast<ReservationOperation_DT>(resParStruct.getReservationOperation().value_);
    memset(out.time, 0x00, TIME_LEN);
    memcpy(out.time, &(resParStruct.getUpdateTime()[0]), resParStruct.getUpdateTime().size());

    return static_cast<CallStatus_DT>(callStatus);
}

CallStatus_DT GetLocalFOTAResPar(LocalFOTAResParStruct_DT &out, int32_t timeout)
{
    CommonAPI::CallStatus callStatus;
    CommonAPI::CallInfo callInfo;
    callInfo.timeout_ = timeout;
    TBoxReservationFunctions::LocalFOTAResParStruct resParStruct;
    gTBoxReservationFunctionsProxy->getLocalFOTAResParAttribute().getValue(callStatus, resParStruct, &callInfo);
    out.operation = static_cast<ReservationOperation_DT>(resParStruct.getReservationOperation().value_);
    memset(out.time, 0x00, TIME_LEN);
    memcpy(out.time, &(resParStruct.getUpdateTime()[0]), resParStruct.getUpdateTime().size());

    return static_cast<CallStatus_DT>(callStatus);
}

CallStatus_DT LocalChargeReservationFunc(ChargMode_DT chargMode_DT, Repeat_DT repeat_DT,
        char start[TIME_LEN], char end[TIME_LEN], TBoxResponse_DT &out)
{
    CommonAPI::CallStatus callStatus;
    TBoxReservationFunctions::ChargMode charMode;
    TBoxReservationFunctions::TimeArray timeStart(&start[0], &start[TIME_LEN]);
    TBoxReservationFunctions::Repeat repeat;
    TBoxReservationFunctions::TimeArray timeEnd(&end[0], &end[TIME_LEN]);
    TBoxReservationFunctions::ReservationACK reservationACK;
    charMode.value_ = chargMode_DT;
    repeat.value_ = repeat_DT;
    gTBoxReservationFunctionsProxy->LocalChargeReservation(charMode, timeStart, repeat, timeEnd,
            callStatus, reservationACK);
    out = static_cast<TBoxResponse_DT>(reservationACK.value_);
    return static_cast<CallStatus_DT>(callStatus);
}

CallStatus_DT LocalChargeReservationFunc(ChargMode_DT chargMode_DT, Repeat_DT repeat_DT,
        char start[TIME_LEN], char end[TIME_LEN], TBoxResponse_DT &out, int32_t timeout)
{
    CommonAPI::CallStatus callStatus;
    CommonAPI::CallInfo callInfo;
    callInfo.timeout_ = timeout;
    TBoxReservationFunctions::ChargMode charMode;
    TBoxReservationFunctions::TimeArray timeStart(&start[0], &start[TIME_LEN]);
    TBoxReservationFunctions::Repeat repeat;
    TBoxReservationFunctions::TimeArray timeEnd(&end[0], &end[TIME_LEN]);
    TBoxReservationFunctions::ReservationACK reservationACK;
    charMode.value_ = chargMode_DT;
    repeat.value_ = repeat_DT;
    gTBoxReservationFunctionsProxy->LocalChargeReservation(charMode, timeStart, repeat, timeEnd,
            callStatus, reservationACK, &callInfo);
    out = static_cast<TBoxResponse_DT>(reservationACK.value_);
    return static_cast<CallStatus_DT>(callStatus);
}

CallStatus_DT GetLocalChargeResPar(LocalChargeResParStruct_DT &out)
{
    CommonAPI::CallStatus callStatus;
    TBoxReservationFunctions::LocalChargeResParStruct resParStruct;
    gTBoxReservationFunctionsProxy->getLocalChargeResParAttribute().getValue(callStatus, resParStruct);
    memset(&out, 0x00, sizeof(LocalChargeResParStruct_DT));
    out.chargMode_DT = static_cast<ChargMode_DT>(resParStruct.getChargMode().value_);
    out.repeat_DT = static_cast<Repeat_DT>(resParStruct.getRepeat().value_);
    memcpy(out.start, &(resParStruct.getStartTime()[0]), resParStruct.getStartTime().size());
    memcpy(out.end, &(resParStruct.getEndTime()[0]), resParStruct.getEndTime().size());
    return static_cast<CallStatus_DT>(callStatus);
}

CallStatus_DT GetLocalChargeResPar(LocalChargeResParStruct_DT &out, int32_t timeout)
{
    CommonAPI::CallStatus callStatus;
    CommonAPI::CallInfo callInfo;
    callInfo.timeout_ = timeout;
    TBoxReservationFunctions::LocalChargeResParStruct resParStruct;
    gTBoxReservationFunctionsProxy->getLocalChargeResParAttribute().getValue(callStatus, resParStruct, &callInfo);
    memset(&out, 0x00, sizeof(LocalChargeResParStruct_DT));
    out.chargMode_DT = static_cast<ChargMode_DT>(resParStruct.getChargMode().value_);
    out.repeat_DT = static_cast<Repeat_DT>(resParStruct.getRepeat().value_);
    memcpy(out.start, &(resParStruct.getStartTime()[0]), resParStruct.getStartTime().size());
    memcpy(out.end, &(resParStruct.getEndTime()[0]), resParStruct.getEndTime().size());
    return static_cast<CallStatus_DT>(callStatus);
}
