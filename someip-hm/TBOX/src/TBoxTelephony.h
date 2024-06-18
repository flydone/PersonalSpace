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

#ifndef SOMEIPTEST_TBOXTELEPHONY_H
#define SOMEIPTEST_TBOXTELEPHONY_H

#include "public_def.h"
#define PATH_LEN 32

/*****************************************************************************
 * data define
 *****************************************************************************/

#define TEL_NUM_LEN 16

typedef __int64_t CallId;
typedef __uint16_t MCC_DT;
typedef __uint8_t MNC_DT;

typedef enum {
    E_NORMAL = 0,
    E_LOCKED = 1,
    E_NOT_EXISTS = 2,
    E_ERROR = 3
} TBoxSimState_DT;

typedef enum {
    E_OUT_OF_COVERAGE = 0,
    E_SEARCHING = 1,
    E_FLIGHT_MODE = 2,
    E_LIMITED_SERVICE = 3,
    E_FULL_SERVICE = 4
} TBoxSimMode_DT;

typedef enum {
    E_I_CALL = 0,
    E_B_CALL = 1,
    E_AUTO_E_CALL = 2,
    E_MANUAL_E_CALL = 3,
    E_VOICE_CALL = 4,
    E_VIDEO_CALL = 5,
    E_E_CALLBACK = 6,
    E_INCOMING_CALL = 7
} TBoxCallType_DT;

typedef enum {
    RESUME_OP = 0,
    PAUSE_OP = 1,
    ACCEPT_OP = 2,
    REJECT_OP = 3,
    HANGUP_OP = 4,
    NOT_AUTHORIZED_OP = 5
} TBoxCallOperation_DT;

typedef enum {
    E_IDLE = 0,
    E_DIALING = 1,
    E_CALLING = 2,
    E_REMOTE_CALLING = 3,
    E_ACCEPTED = 4,
    E_REMOTE_ACCEPTED = 5,
    E_ON_GOING = 6,
    E_ON_HOLD = 7,
    E_HANGUP = 8,
    E_REMOTE_HANGUP = 9,
    E_REJECTED = 10,
    E_REMOTE_REJECTED = 11,
    E_NO_ANSWER = 12,
    E_BUSY = 13,
    E_CONNECTION_ERROR = 14,
    E_ECALL_ACTIVATED = 15,
    E_TERMINATED = 16
} TBoxCallState_DT;

typedef enum {
    E_NONETWORKAVAILABLE = 0,
    E_GPRS = 1,
    E_EGPRS = 2,
    E_WCDMA = 3,
    E_HSDPA = 4,
    E_LTE = 5,
    E_5G = 6
} TBoxNetType_DT;

struct TBoxSimStatusStruct_DT {
    TBoxSimState_DT tBoxSimState;
    TBoxSimMode_DT tBoxSimMode;
};

struct TBoxCallOperationOut {
    CallId callId;
    TBoxResponse_DT tBoxResponseDt;
};

struct TBoxSIMInforOut {
    char ICCID[20];
    char IMEI[15];
    char IMSI[15];
};

struct TBoxTelephoneNumber_DT {
  public:
    TBoxTelephoneNumber_DT() {
        dynamicBYTE = realdata;
        memset(dynamicBYTE, 0x00, TEL_NUM_LEN);
        len = 0;
    };
    ~TBoxTelephoneNumber_DT() {
    }

  private:
    char realdata[TEL_NUM_LEN];

  public:
    void setTelephoneNumber(char *buf, size_t size) {
        if (size > TEL_NUM_LEN) {
            len = TEL_NUM_LEN;
        }
        else {
            len = size;
        }
        memcpy(dynamicBYTE, buf, len);
    }
    char * dynamicBYTE;
    int len;
};

struct TBoxCallStateEvent_DT {
    TBoxTelephoneNumber_DT tBoxTelephoneNumber;
    TBoxCallType_DT tBoxCallTypeDt;
    TBoxCallState_DT tBoxCallStateDt;
    CallId callId;
};

struct TBoxNetworkProviderStruct_DT {

    MCC_DT mccDt;
    MNC_DT mncDt;
    char networkProvider[PATH_LEN];
};

struct TBoxSignalStrengthStruct_DT {
    TBoxNetType_DT tBoxNetTypeDt;
    __int16_t signalStrenghRawData;
};

class TBoxTelephonyListener {
  public:
    virtual ~TBoxTelephonyListener(){};
    virtual void TBoxSimStatusChangedListener(
        TBoxSimStatusStruct_DT tBoxSimStatusStructDt){};
    virtual void TBoxNetworkProviderChangedListener(
        TBoxNetworkProviderStruct_DT tBoxNetworkProviderStructDt){};
    virtual void TBoxSignalStrengthChangedListener(
        TBoxSignalStrengthStruct_DT tBoxSignalStrengthStructDt){};
    virtual void TBoxCallStateEventListener(TBoxCallStateEvent_DT event){};
};

void TboxTelephonyInit(char *appName, char *configFile);
CallStatus_DT TBoxStartCallFunc(TBoxTelephoneNumber_DT number,
                                TBoxCallType_DT callTypeDt, CallId callId,
                                TBoxCallOperationOut &out);
CallStatus_DT TBoxCallOperationFunc(TBoxTelephoneNumber_DT number,
                                    TBoxCallType_DT callTypeDt,
                                    TBoxCallOperation_DT tBoxCallOperationDt,
                                    CallId callId, TBoxCallOperationOut &out);
CallStatus_DT TBoxSIMInforFunc(TBoxSIMInforOut &out);
bool TboxTelephonyIsReady();
CallStatus_DT GetTBoxSimStatusStruct(TBoxSimStatusStruct_DT &tBoxSimStatusStructDt);
CallStatus_DT GetTBoxNetworkProviderStruct(
    TBoxNetworkProviderStruct_DT &tBoxNetworkProviderStructDt);
CallStatus_DT GetTBoxSignalStrengthStruct(
    TBoxSignalStrengthStruct_DT &tBoxSignalStrengthStructDt);
void TBoxTelephonyListenerRegister(TBoxTelephonyListener *listener);
void TBoxTelephonyListenerUnRegister();
#endif // SOMEIPTEST_TBOXTELEPHONY_H
