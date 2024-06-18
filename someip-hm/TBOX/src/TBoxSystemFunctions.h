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

#ifndef SOMEIPTEST_TBOXSYSTEMFUNCTIONS_H
#define SOMEIPTEST_TBOXSYSTEMFUNCTIONS_H

#include "public_def.h"
#include <string>
#include <vector>

typedef enum {
    E_DISABLE_LOG_DWN = 0,
    E_ENABLE_LOG_DWN = 1
} LogDownloadCommand_DT;

struct TBoxInfrastructureDataOut {
    char SN[32];
    char FW0[32];
    char SW0[32];
    char FW1[32];
    char SW1[32];
    char COMP1[32];
    char COMP2[32];
};

struct ConnectionInfo_DT {
  public:
    ConnectionInfo_DT() {};
    ~ConnectionInfo_DT() {
    }

  public:
    std::vector<__uint8_t> dynamicBYTE;
};

typedef enum { E_DISCONNECTED_ = 0, E_CONNECTED_ = 1 } TBoxAPN2Status_DT;

typedef enum { E_CLOSE = 0, E_OPEN = 1 } TBoxAPN2Operation_DT;

typedef enum { E_MANUALRESET = 0, E_RESERVED = 1 } TBoxResetOption_DT;

typedef enum { E_REQUEST = 0, E_RESERVED_REQ = 1 } UpgradeRequst_DT;

typedef enum { E_NOTIFY = 0, E_RESERVED_COM = 1 } UpgradeComplete_DT;

typedef enum {
    E_ALLOW = 0,
    E_SOC_LOW_ = 1,
    E_NOTPGEAR_ = 2,
    E_NOTSPEED_ = 3,
    E_CALLING_ = 4,
    E_RESERVED1_RESP = 5,
    E_RESERVED2_RESP = 6
} UpgradeResponse_DT;

typedef enum {
    E_SUCCESS = 0,
    E_ERRORNAME_ = 1,
    E_SAFETYFAILED_ = 2,
    E_CARABNORMAL_ = 3,
    E_MCUABNORMAL_ = 4,
    E_SOCMCUABNORMAL_ = 5,
    E_FWABNORMAL_ = 6,
    E_RESERVED_ = 7
} UpgradeResult_DT;

struct TBoxDTCOut {
    TBoxDTCOut() {};
    ~TBoxDTCOut() {
    }

  public:
    std::vector<__uint32_t> dynamicIntArray;
};

struct TBoxAPN2StatusOut {
    TBoxAPN2Status_DT tBoxApn2StatusDt;
};

struct TBoxAPN2OperationOut {
    TBoxResponse_DT tBoxResponseDt;
    TBoxAPN2Status_DT tBoxApn2StatusDt;
};

struct GPSData_DT {
  public:
    GPSData_DT() {}

    ~GPSData_DT() {
    }
    std::string gpsData = "";
};

struct DoubleGPSData_DT {
  public:
    DoubleGPSData_DT() {}

    ~DoubleGPSData_DT() {
    }
    std::string doubleGpsData = "";
};

struct GPSInfoData_DT {
  public:
    GPSInfoData_DT() {}

    ~GPSInfoData_DT() {
    }
    std::string gpsInfoData = "";
};

struct TBoxResetOut {
    TBoxResponse_DT tBoxResponseDt;
};

struct TboxUpgradeOut {
    UpgradeResponse_DT upgradeResponseDt;
};

void TBoxSystemFuctionsInit(char *appName, char *configFile);
bool TBoxSystemFuctionsIsReady();

class TBoxSystemFuntionsListener {
  public:
    virtual ~TBoxSystemFuntionsListener(){};
    virtual void GPSDataChangedListener(char *gpsData){};
    virtual void DoubleGPSDataChangedListener(char *doubleGpsData){};
    virtual void GPSInfoDataChangedListener(char *gpsInfoData){};
    virtual void HeartbeatCheckEventListener(){};
    virtual void UpgradeProcessEventListener(__uint8_t processValue){};
    virtual void UpgradeResultEventListener(UpgradeResult_DT upgradeResultDt){};
    virtual void TboxUpgradeEventListener(UpgradeResponse_DT upgradeResponseDt){};
};

CallStatus_DT
TBoxLoggingDownloadFunc(LogDownloadCommand_DT logDownloadCommandDt,
                        ConnectionInfo_DT &out);
CallStatus_DT TBoxInfrastructureDataFunc(TBoxInfrastructureDataOut &out);
CallStatus_DT TBoxDTCFunc(TBoxDTCOut &out);
CallStatus_DT TBoxAPN2Status(TBoxAPN2StatusOut &tBoxApn2StatusOut);
CallStatus_DT TBoxAPN2Operation(TBoxAPN2Operation_DT tBoxApn2OperationDt,
                                TBoxAPN2OperationOut &out);
CallStatus_DT GetGPSDataFunc(GPSData_DT &out);
CallStatus_DT GetDoubleGPSDataFunc(DoubleGPSData_DT &out);
CallStatus_DT GetGPSInfoDataFunc(GPSInfoData_DT &out);
CallStatus_DT TBoxResetFunc(TBoxResetOption_DT tBoxResetOptionDt,
                            TBoxResetOut &out);
void TBoxSystemFuntionsListenerRegister(TBoxSystemFuntionsListener *listener); // Register GPS and Heartbeat as default
void TBoxSystemFuntionsListenerRegisterGPS(TBoxSystemFuntionsListener *listener);
void TBoxSystemFuntionsListenerRegisterDoubleGPS(TBoxSystemFuntionsListener *listener);
void TBoxSystemFuntionsListenerRegisterGPSInfoBD(TBoxSystemFuntionsListener *listener);
void TBoxSystemFuntionsListenerRegisterHeartbeat(TBoxSystemFuntionsListener *listener);
void TBoxSystemFuntionsListenerRegisterUpgradeProcess(TBoxSystemFuntionsListener *listener);
void TBoxSystemFuntionsListenerRegisterUpgradeResult(TBoxSystemFuntionsListener *listener);
void TBoxSystemFuntionsListenerRegisterTboxUpgrade(TBoxSystemFuntionsListener *listener);

CallStatus_DT TboxUpgradeFunc(UpgradeRequst_DT upgradeRequstDt);
CallStatus_DT UpdateFileTransmitFunc(UpgradeComplete_DT upgradeCompleteDt);

void TBoxSystemFuntionsListenerUnRegister(); // Unregister All as default
void TBoxSystemFuntionsListenerUnRegisterGPS();
void TBoxSystemFuntionsListenerUnRegisterDoubleGPS();
void TBoxSystemFuntionsListenerUnRegisterGPSInfoBD();
void TBoxSystemFuntionsListenerUnRegisterHeartbeat();
void TBoxSystemFuntionsListenerUnRegisterUpgradeProcess();
void TBoxSystemFuntionsListenerUnRegisterUpgradeResult();
void TBoxSystemFuntionsListenerUnRegisterTboxUpgrade();
#endif // SOMEIPTEST_TBOXSYSTEMFUNCTIONS_H
