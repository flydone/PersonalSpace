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

#ifndef SOMEIPTEST_TBOXTSPCOM_H
#define SOMEIPTEST_TBOXTSPCOM_H

#include "public_def.h"

typedef enum {
    E_CONNECTING = 0,
    E_CONNECTED = 1,
    E_DISCONNECTED = 2,
    E_NETWORK_UNREACHABLE = 3,
    E_LOGGINGFAIL = 4,
    E_UNKNOW_STATE = 99
} TBoxTSPLoginState_DT;

class TBoxTSPComListener {
  public:
    virtual ~TBoxTSPComListener(){};
    void TBoxTSPLoginStateChangedListener(
        TBoxTSPLoginState_DT tBoxTspLoginStateDt){};
};

TBoxTSPLoginState_DT GetTBoxTSPLoginState();
void TBoxTSPComInit(char *appName, char *configFile);
bool TBoxTSPComIsReady();
void TBoxTSPComListenerRegister(TBoxTSPComListener *listener);
void TBoxTSPComListenerUnRegister();
#endif // SOMEIPTEST_TBOXTSPCOM_H
