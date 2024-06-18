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

#ifndef SOMEIP_TBOXRESERVATION_H
#define SOMEIP_TBOXRESERVATION_H

#include "public_def.h"

#define TIME_LEN 6

typedef enum {
    E_CANCEL = 0,
    E_SET = 1,
    E_CHANGE = 2
} ReservationOperation_DT;

typedef enum {
    E_IMMEDIATELY = 0,
    E_RESERVATION = 1
} ChargMode_DT;

typedef enum {
    E_ONLYONCE = 0,
    E_EVERYDAY = 1
} Repeat_DT;

struct LocalFOTAResParStruct_DT {
    ReservationOperation_DT operation;
    char time[TIME_LEN];
};

struct LocalChargeResParStruct_DT {
    ChargMode_DT chargMode_DT;
    char start[TIME_LEN];
    Repeat_DT repeat_DT;
    char end[TIME_LEN];
};

class TBoxReservationFunctionsListener {
  public:
    virtual ~TBoxReservationFunctionsListener(){};
    virtual void FOTAReservationEventListener(ReservationOperation_DT operation,
            char time[TIME_LEN]){};
    virtual void RemoteChargeReservationEventListener(ChargMode_DT chargMode_DT, Repeat_DT repeat_DT,
            char start[TIME_LEN], char end[TIME_LEN]){};
};

class TBoxFOTAReservationFunctionsListener {
  public:
    virtual ~TBoxFOTAReservationFunctionsListener(){};
    virtual void FOTAReservationEventListener(ReservationOperation_DT operation,
            char time[TIME_LEN]){};
};

class TBoxChargeReservationFunctionsListener {
  public:
    virtual ~TBoxChargeReservationFunctionsListener(){};
    virtual void RemoteChargeReservationEventListener(ChargMode_DT chargMode_DT, Repeat_DT repeat_DT,
            char start[TIME_LEN], char end[TIME_LEN]){};
};
void TBoxReservationFunctionsInit(char *appName, char *configFile);
bool TBoxReservationFunctionsIsReady();
void TBoxReservationFunctionsListenerRegister(TBoxReservationFunctionsListener *listener);
void TBoxReservationFunctionsListenerUnRegister();
void TBoxFOTAReservationFunctionsListenerRegister(TBoxFOTAReservationFunctionsListener *listener);
void TBoxFOTAReservationFunctionsListenerUnRegister();
void TBoxChargeReservationFunctionsListenerRegister(TBoxChargeReservationFunctionsListener *listener);
void TBoxChargeReservationFunctionsListenerUnRegister();
CallStatus_DT LocalFOTAReservationFunc(ReservationOperation_DT reservationOption,
        char time[TIME_LEN], TBoxResponse_DT & response);
CallStatus_DT LocalFOTAReservationFunc(ReservationOperation_DT reservationOption,
        char time[TIME_LEN], TBoxResponse_DT & response, int32_t timeout);

CallStatus_DT FOTAReservationResponeFunc(TBoxResponse_DT respone);
CallStatus_DT GetLocalFOTAResPar(LocalFOTAResParStruct_DT &out);
CallStatus_DT GetLocalFOTAResPar(LocalFOTAResParStruct_DT &out, int32_t timeout);
CallStatus_DT LocalChargeReservationFunc(ChargMode_DT chargMode_DT, Repeat_DT repeat_DT,
        char start[TIME_LEN], char end[TIME_LEN], TBoxResponse_DT &out);
CallStatus_DT LocalChargeReservationFunc(ChargMode_DT chargMode_DT, Repeat_DT repeat_DT,
        char start[TIME_LEN], char end[TIME_LEN], TBoxResponse_DT &out, int32_t timeout);
CallStatus_DT RemoteChargeReservationFunc(TBoxResponse_DT respone);
CallStatus_DT GetLocalChargeResPar(LocalChargeResParStruct_DT &out);
CallStatus_DT GetLocalChargeResPar(LocalChargeResParStruct_DT &out, int32_t timeout);
#endif
