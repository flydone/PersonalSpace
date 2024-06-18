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
#include "TBoxSystemFunctions.h"

TBoxSystemFuntionsListener *gTBoxSystemFuntionsListener = NULL;
Subscription mSubscriptionGPSData;
Subscription mSubscriptionDoubleGPSData;
Subscription mSubscriptionGPSInfoData;
Subscription mSubscriptionHeartbeat;
Subscription mSubscriptionUpgradeProcess;
Subscription mSubscriptionUpgradeResult;
Subscription mSubscriptionTboxUpgrade;

bool isGPSDataSubSet = false;
bool isDoubleGPSDataSubSet = false;
bool isGPSInfoDataSubset = false;
bool isHeartbeatSubSet = false;
bool isUpgradeProcessSubSet = false;
bool isUpgradeResultSubSet = false;
bool isTboxUpgradeSubSet = false;

void TBoxSystemFuctionsInit(char *appName, char *configFile) {
    if (configFile) {
        setenv("VSOMEIP_CONFIGURATION", configFile, 1);
    }
    if (gRuntime == NULL) {
        gRuntime = CommonAPI::Runtime::get();
    }
    gTBoxSystemFunctionsProxy = gRuntime->buildProxy<TBoxSystemFunctionsProxy>(
        "local", "TBoxSystemFunctions01", appName);
    std::string versionInfo = gRuntime->get_version();
    std::string version = versionInfo.substr(versionInfo.rfind(" ") + 1);

    LOGD("appName = %s version = %s", appName, version.c_str());
    __system_property_set("vendor.gwm.someip.version", version.c_str());
}

bool TBoxSystemFuctionsIsReady() {
    return gTBoxSystemFunctionsProxy->isAvailable();
}

CallStatus_DT
TBoxLoggingDownloadFunc(LogDownloadCommand_DT logDownloadCommandDt,
                        ConnectionInfo_DT &out) {
    CommonAPI::CallStatus callStatus;
    TBoxSystemFunctions::LogDownloadCommand logDownloadCommand(
        static_cast<TBoxSystemFunctions::LogDownloadCommand::Literal>(
            logDownloadCommandDt));
    TBoxSystemFunctions::ConnectionInfo connectionInfo;
    gTBoxSystemFunctionsProxy->TBoxLoggingDownload(logDownloadCommand,
                                                   callStatus, connectionInfo);
    for (uint32_t i = 0; i < connectionInfo.size(); i++) {
        out.dynamicBYTE.push_back(connectionInfo[i]);
    }
    return static_cast<CallStatus_DT>(callStatus);
}

CallStatus_DT TBoxInfrastructureDataFunc(TBoxInfrastructureDataOut &out) {
    CommonAPI::CallStatus callStatus;
    std::string strSN;
    std::string strFW0;
    std::string strSW0;
    std::string strFW1;
    std::string strSW1;
    std::string strCOMP1;
    std::string strCOMP2;
    gTBoxSystemFunctionsProxy->TBoxInfrastructureData(
        callStatus, strSN, strFW0, strSW0, strFW1, strSW1, strCOMP1, strCOMP2);
    memset(&out, 0x00, sizeof(TBoxInfrastructureDataOut));
    memcpy(out.SN, strSN.c_str(), strSN.length());
    memcpy(out.FW0, strFW0.c_str(), strFW0.length());
    memcpy(out.FW1, strFW1.c_str(), strFW1.length());
    memcpy(out.SW0, strSW0.c_str(), strSW0.length());
    memcpy(out.SW1, strSW1.c_str(), strSW1.length());
    memcpy(out.COMP1, strCOMP1.c_str(), strCOMP1.length());
    memcpy(out.COMP2, strCOMP2.c_str(), strCOMP2.length());
    return static_cast<CallStatus_DT>(callStatus);
}

CallStatus_DT TBoxDTCFunc(TBoxDTCOut &out) {
    CommonAPI::CallStatus callStatus;
    TBoxSystemFunctions::TBoxDTCCode tBoxDtcCode;
    gTBoxSystemFunctionsProxy->TBoxDTC(callStatus, tBoxDtcCode);
    for (uint32_t i = 0; i < tBoxDtcCode.size(); i++) {
        out.dynamicIntArray.push_back(tBoxDtcCode[i]);
    }
    return static_cast<CallStatus_DT>(callStatus);
}

CallStatus_DT TBoxAPN2Status(TBoxAPN2StatusOut &tBoxApn2StatusOut) {
    CommonAPI::CallStatus callStatus;
    TBoxSystemFunctions::TBoxAPN2Status tBoxApn2Status;
    gTBoxSystemFunctionsProxy->TBoxAPN2Status(callStatus, tBoxApn2Status);
    tBoxApn2StatusOut.tBoxApn2StatusDt =
        static_cast<TBoxAPN2Status_DT>(tBoxApn2Status.value_);
    return static_cast<CallStatus_DT>(callStatus);
}

CallStatus_DT TBoxAPN2Operation(TBoxAPN2Operation_DT tBoxApn2OperationDt,
                                TBoxAPN2OperationOut &out) {
    CommonAPI::CallStatus callStatus;
    TBoxSystemFunctions::TBoxAPN2Operation tBoxApn2Operation;
    tBoxApn2Operation.value_ = tBoxApn2OperationDt;
    TBoxSystemFunctions::TBoxResponse tBoxResponse;
    TBoxSystemFunctions::TBoxAPN2Status tBoxApn2Status;
    gTBoxSystemFunctionsProxy->TBoxAPN2Operation(tBoxApn2Operation, callStatus,
                                                 tBoxResponse, tBoxApn2Status);
    out.tBoxResponseDt = static_cast<TBoxResponse_DT>(tBoxResponse.value_);
    out.tBoxApn2StatusDt =
        static_cast<TBoxAPN2Status_DT>(tBoxApn2Status.value_);
    return static_cast<CallStatus_DT>(callStatus);
}

CallStatus_DT GetGPSDataFunc(GPSData_DT &out) {
    CommonAPI::CallStatus callStatus;
    TBoxSystemFunctions::GPSRawData gpsRawData;
    gTBoxSystemFunctionsProxy->getGPSDataAttribute().getValue(callStatus,
                                                              gpsRawData);
    out.gpsData = gpsRawData;
    return static_cast<CallStatus_DT>(callStatus);
}

CallStatus_DT GetDoubleGPSDataFunc(DoubleGPSData_DT &out) {
    CommonAPI::CallStatus callStatus;
    TBoxSystemFunctions::DoubleGPSRawData doubleGpsRawData;
    gTBoxSystemFunctionsProxy->getGPSDataAttribute().getValue(callStatus,
                                                              doubleGpsRawData);
    out.doubleGpsData = doubleGpsRawData;

    return static_cast<CallStatus_DT>(callStatus);
}

CallStatus_DT GetGPSInfoDataFunc(GPSInfoData_DT &out){
    CommonAPI::CallStatus callStatus;
    TBoxSystemFunctions::GPSInfo gpsInfoRawData;
    gTBoxSystemFunctionsProxy->getGPSDataAttribute().getValue(callStatus,
                                                              gpsInfoRawData);
    out.gpsInfoData = gpsInfoRawData;
    return static_cast<CallStatus_DT>(callStatus);
}

void TBoxSystemFuntionsListenerRegister(TBoxSystemFuntionsListener *listener) {
    TBoxSystemFuntionsListenerRegisterGPS(listener);
    TBoxSystemFuntionsListenerRegisterHeartbeat(listener);
    TBoxSystemFuntionsListenerRegisterUpgradeProcess(listener);
    TBoxSystemFuntionsListenerRegisterUpgradeResult(listener);
    TBoxSystemFuntionsListenerRegisterTboxUpgrade(listener);
}

void TBoxSystemFuntionsListenerRegisterGPS(TBoxSystemFuntionsListener *listener) {
    gTBoxSystemFuntionsListener = listener;
    mSubscriptionGPSData = gTBoxSystemFunctionsProxy->getGPSDataAttribute()
        .getChangedEvent()
        .subscribe([&](std::string gpsData) {
            if (gTBoxSystemFuntionsListener) {
                gTBoxSystemFuntionsListener->GPSDataChangedListener(
                    const_cast<char *>(gpsData.c_str()));
            }
        });
    isGPSDataSubSet = true;

    LOGD("TBoxSystemFuntionsListenerRegisterGPS end, isGPSDataSubSet[%d]", isGPSDataSubSet);
}

void TBoxSystemFuntionsListenerRegisterDoubleGPS(TBoxSystemFuntionsListener *listener) {
    gTBoxSystemFuntionsListener = listener;
    mSubscriptionDoubleGPSData = gTBoxSystemFunctionsProxy->getDoubleGPSDataAttribute()
        .getChangedEvent()
        .subscribe([&](std::string doubleGpsData) {
            if (gTBoxSystemFuntionsListener) {
                gTBoxSystemFuntionsListener->DoubleGPSDataChangedListener(
                    const_cast<char *>(doubleGpsData.c_str()));
            }
        });
    isDoubleGPSDataSubSet = true;

    LOGD("TBoxSystemFuntionsListenerRegisterDoubleGPS end, isDoubleGPSDataSubSet[%d]", isDoubleGPSDataSubSet);
}

void TBoxSystemFuntionsListenerRegisterGPSInfoBD(TBoxSystemFuntionsListener *listener) {
    gTBoxSystemFuntionsListener = listener;
    mSubscriptionGPSInfoData = gTBoxSystemFunctionsProxy->getGPSFunctionAttribute()
        .getChangedEvent()
        .subscribe([&](std::string gpsInfoData){
            if (gTBoxSystemFuntionsListener){
                gTBoxSystemFuntionsListener->GPSInfoDataChangedListener(
                    const_cast<char *>(gpsInfoData.c_str()));
            }
        });
        isGPSDataSubSet = true;
    LOGD("TBoxSystemFuntionsListenerRegisterGPSInfoBD end, isGPSDataSubSet[%d]", isGPSDataSubSet);
}

void TBoxSystemFuntionsListenerRegisterHeartbeat(TBoxSystemFuntionsListener *listener) {
    gTBoxSystemFuntionsListener = listener;
    mSubscriptionHeartbeat = gTBoxSystemFunctionsProxy->getHeartbeatCheckEvent().subscribe([&]() {
        if (gTBoxSystemFuntionsListener) {
            gTBoxSystemFuntionsListener->HeartbeatCheckEventListener();
        }
    });
    isHeartbeatSubSet = true;

    LOGD("TBoxSystemFuntionsListenerRegisterHeartbeat end, isHeartbeatSubSet[%d]", isHeartbeatSubSet);
}

void TBoxSystemFuntionsListenerRegisterUpgradeProcess(TBoxSystemFuntionsListener *listener) {
    gTBoxSystemFuntionsListener = listener;
    mSubscriptionUpgradeProcess = gTBoxSystemFunctionsProxy->getUpgradeProcessEvent().subscribe(
            [&](TBoxSystemFunctions::UpgradeProcess upgradeProcess) {
            if (gTBoxSystemFuntionsListener) {
            gTBoxSystemFuntionsListener->UpgradeProcessEventListener(
                    upgradeProcess);
            }
    });
    isUpgradeProcessSubSet = true;

    LOGD("TBoxSystemFuntionsListenerRegisterUpgradeProcess end, isUpgradeProcessSubSet[%d]", isUpgradeProcessSubSet);
}

void TBoxSystemFuntionsListenerRegisterUpgradeResult(TBoxSystemFuntionsListener *listener) {
    gTBoxSystemFuntionsListener = listener;
    mSubscriptionUpgradeResult = gTBoxSystemFunctionsProxy->getUpgradeResultEvent().subscribe(
            [&](TBoxSystemFunctions::UpgradeResult upgradeResult) {
            if (gTBoxSystemFuntionsListener) {
            UpgradeResult_DT upgradeResultDt;
            upgradeResultDt =
            static_cast<UpgradeResult_DT>(upgradeResult.value_);
            gTBoxSystemFuntionsListener->UpgradeResultEventListener(
                    upgradeResultDt);
            }
    });
    isUpgradeResultSubSet = true;

    LOGD("TBoxSystemFuntionsListenerRegisterUpgradeProcess end, isUpgradeResultSubSet[%d]", isUpgradeResultSubSet);
}

void TBoxSystemFuntionsListenerRegisterTboxUpgrade(TBoxSystemFuntionsListener *listener) {
    gTBoxSystemFuntionsListener = listener;
    mSubscriptionTboxUpgrade = gTBoxSystemFunctionsProxy->getTboxUpgradeEvent().subscribe(
                [&](TBoxSystemFunctions::UpgradeResponse upgradeResponse) {
                if (gTBoxSystemFuntionsListener) {
                UpgradeResponse_DT upgradeResponseDt;
                upgradeResponseDt =
                static_cast<UpgradeResponse_DT>(upgradeResponse.value_);
                gTBoxSystemFuntionsListener->TboxUpgradeEventListener(
                        upgradeResponseDt);
                }
        });
        isTboxUpgradeSubSet = true;

        LOGD("TBoxSystemFuntionsListenerRegisterTboxUpgrade end, isTboxUpgradeSubSet[%d]", isTboxUpgradeSubSet);
}

void TBoxSystemFuntionsListenerUnRegister() {
    LOGD("TBoxSystemFuntionsListenerUnRegister start, isGPSDataSubSet[%d], isDoubleGPSDataSubSet[%d], isHeartbeatSubSet[%d], isUpgradeProcessSubSet[%d], isUpgradeResultSubSet[%d], isTboxUpgradeSubSet[%d]",
    isGPSDataSubSet, isDoubleGPSDataSubSet, isHeartbeatSubSet, isUpgradeProcessSubSet, isUpgradeResultSubSet, isTboxUpgradeSubSet);
    if(isGPSDataSubSet){
        isGPSDataSubSet = false;
        gTBoxSystemFunctionsProxy->getGPSDataAttribute()
            .getChangedEvent()
            .unsubscribe(mSubscriptionGPSData);
    }

    if(isDoubleGPSDataSubSet){
        isDoubleGPSDataSubSet = false;
        gTBoxSystemFunctionsProxy->getDoubleGPSDataAttribute()
            .getChangedEvent()
            .unsubscribe(mSubscriptionDoubleGPSData);
    }

    if(isHeartbeatSubSet){
        isHeartbeatSubSet = false;
        gTBoxSystemFunctionsProxy->getHeartbeatCheckEvent().unsubscribe(mSubscriptionHeartbeat);
    }
    if(isUpgradeProcessSubSet){
        isUpgradeProcessSubSet = false;
        gTBoxSystemFunctionsProxy->getUpgradeProcessEvent().unsubscribe(mSubscriptionUpgradeProcess);
    }

    if(isUpgradeResultSubSet){
        isUpgradeResultSubSet = false;
        gTBoxSystemFunctionsProxy->getUpgradeResultEvent().unsubscribe(mSubscriptionUpgradeResult);
    }

    if(isTboxUpgradeSubSet){
        isTboxUpgradeSubSet = false;
        gTBoxSystemFunctionsProxy->getTboxUpgradeEvent().unsubscribe(mSubscriptionTboxUpgrade);
    }
}

void TBoxSystemFuntionsListenerUnRegisterGPS() {
    if(isGPSDataSubSet){
        isGPSDataSubSet = false;
        gTBoxSystemFunctionsProxy->getGPSDataAttribute()
            .getChangedEvent()
            .unsubscribe(mSubscriptionGPSData);
        LOGD("TBoxSystemFuntionsListenerUnRegister: Unregister GPSDataSubSet");
    } else {
        LOGD("TBoxSystemFuntionsListenerUnRegister: GPSDataSubSet is not registered");
    }
}

void TBoxSystemFuntionsListenerUnRegisterDoubleGPS() {
    if(isDoubleGPSDataSubSet){
        isDoubleGPSDataSubSet = false;
        gTBoxSystemFunctionsProxy->getDoubleGPSDataAttribute()
            .getChangedEvent()
            .unsubscribe(mSubscriptionDoubleGPSData);
        LOGD("TBoxSystemFuntionsListenerUnRegister: Unregister DoubleGPSDataSubSet");
    } else {
        LOGD("TBoxSystemFuntionsListenerUnRegister: DoubleGPSDataSubSet is not registered");
    }
}

void TBoxSystemFuntionsListenerUnRegisterGPSInfoBD() {
    if(isGPSDataSubSet){
        isGPSDataSubSet = false;
        gTBoxSystemFunctionsProxy->getGPSFunctionAttribute()
            .getChangedEvent()
            .unsubscribe(mSubscriptionGPSInfoData);
        LOGD("TBoxSystemFuntionsListenerUnRegister: Unregister GPSInfoDataSubSet");
    }else{
        LOGD("TBoxSystemFuntionsListenerUnRegister: GPSInfoDataSubSet is not registered");
    }
}

void TBoxSystemFuntionsListenerUnRegisterHeartbeat() {
    if(isHeartbeatSubSet){
        isHeartbeatSubSet = false;
        gTBoxSystemFunctionsProxy->getHeartbeatCheckEvent().unsubscribe(mSubscriptionHeartbeat);
        LOGD("TBoxSystemFuntionsListenerUnRegister: Unregister HeartbeatSubSet");
    } else {
        LOGD("TBoxSystemFuntionsListenerUnRegister: HeartbeatSubSet is not registered");
    }
}

void TBoxSystemFuntionsListenerUnRegisterUpgradeProcess() {
    if(isUpgradeProcessSubSet){
        isUpgradeProcessSubSet = false;
        gTBoxSystemFunctionsProxy->getUpgradeProcessEvent().unsubscribe(mSubscriptionUpgradeProcess);
        LOGD("TBoxSystemFuntionsListenerUnRegister: Unregister UpgradeProcess");
    }else {
        LOGD("TBoxSystemFunionsListenerUnRegister: UpgradeProcess is not registered");
    }
}

void TBoxSystemFuntionsListenerUnRegisterUpgradeResult() {
    if(isUpgradeResultSubSet){
        isUpgradeResultSubSet = false;
        gTBoxSystemFunctionsProxy->getUpgradeResultEvent().unsubscribe(mSubscriptionUpgradeResult);
        LOGD("TBoxSystemFuntionsListenerUnRegister: Unregister UpgradeResult");
    }else {
        LOGD("TBoxSystemFunionsListenerUnRegister: UpgradeResult is not registered");
    }

}

void TBoxSystemFuntionsListenerUnRegisterTboxUpgrade() {
    if(isTboxUpgradeSubSet){
        isTboxUpgradeSubSet = false;
        gTBoxSystemFunctionsProxy->getTboxUpgradeEvent().unsubscribe(mSubscriptionTboxUpgrade);
        LOGD("TBoxSystemFuntionsListenerUnRegister: Unregister TboxUpgrade");
    }else {
        LOGD("TBoxSystemFunionsListenerUnRegister: TboxUpgrade is not registered");
    }
}

CallStatus_DT TBoxResetFunc(TBoxResetOption_DT tBoxResetOptionDt,
                            TBoxResetOut &out) {
    CommonAPI::CallStatus callStatus;
    TBoxSystemFunctions::TBoxResponse tBoxResponse;
    TBoxSystemFunctions::TBoxResetOption tBoxResetOption;
    tBoxResetOption.value_ = tBoxResetOptionDt;
    gTBoxSystemFunctionsProxy->TBoxReset(tBoxResetOption, callStatus,
                                         tBoxResponse);
    out.tBoxResponseDt = static_cast<TBoxResponse_DT>(tBoxResponse.value_);
    return static_cast<CallStatus_DT>(callStatus);
}

CallStatus_DT TboxUpgradeFunc(UpgradeRequst_DT upgradeRequstDt) {
    CommonAPI::CallStatus callStatus;
    TBoxSystemFunctions::UpgradeRequst upgradeRequst;
    upgradeRequst.value_ = upgradeRequst;
    gTBoxSystemFunctionsProxy->TboxUpgrade(upgradeRequst, callStatus);
    return static_cast<CallStatus_DT>(callStatus);
}

CallStatus_DT UpdateFileTransmitFunc(UpgradeComplete_DT upgradeCompleteDt) {
    CommonAPI::CallStatus callStatus;
    TBoxSystemFunctions::UpgradeComplete upgradeComplete;
    upgradeComplete.value_ = upgradeComplete;
    gTBoxSystemFunctionsProxy->UpdateFileTransmit(upgradeComplete, callStatus);
    return static_cast<CallStatus_DT>(callStatus);
}

