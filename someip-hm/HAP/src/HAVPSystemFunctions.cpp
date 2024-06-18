/*************************************************************************
 * Copyright (C) 2020 GWM Automotive Inc.
 *
 * The copyright notice above does not evidence any actual
 * or intended publication of such source code.
 * The code contains GWM Confidential Proprietary Information.
 *************************************************************************/
//
// Created by liangyu on 2023/8/20.
//
#include "public_util.h"
#include "HAVPSystemFunctions.h"


std::shared_ptr<HAVPandAVPFunctionsProxy<>> gHAVPandAVPFunctionsProxy = NULL;

HAVPSystemFunctionsListener *gHAVPSystemFunctionsListener =NULL;
// Subscription mSubscriptionLnWorld;
// Subscription mSubscriptionVehData;
// Subscription mSubscriptionMapFile;

bool isLnWorldSubSet=false;
bool isVehDataSubSet=false;
bool isMapFileSubSet=false;

void HAVPSystemFunctionInit(char *appName, char *configFile){
    if(configFile){
        setenv("VSOMEIP_CONFIGURATION", configFile, 1);
    }
    if (gRuntime == NULL) {
        gRuntime = CommonAPI::Runtime::get();
    }
    gHAVPandAVPFunctionsProxy = gRuntime->buildProxy<HAVPandAVPFunctionsProxy>(
        "local","HAPSystemFunctions01",appName);
    std::string versionInfo = gRuntime->get_version();
    std::string version = versionInfo.substr(versionInfo.rfind(" ")+1);
    
    LOGD("appName = %s version = %s", appName, version.c_str());
    __system_property_set("vendor.gwm.someip.version", version.c_str());
}

bool HAVPSystemFunctionsIsReady(){
    bool ret = gHAVPandAVPFunctionsProxy->isAvailable();
    LOGD("HAVPandAVPFunctionsIsReady: %d",ret);
    return ret;
}

void HAVPSystemFunctionsListenerRegister(HAVPSystemFunctionsListener *listener){
//    HAVPSystemFunctionsListenerLnWorld (listener);
//    HAVPSystemFunctionsListenerVehData (listener);
//    HAVPSystemFunctionsListenerMapfile (listener);
    LOGD("HAVPandAVPFunctionsListenerRegister: enter");
    gHAVPSystemFunctionsListener = listener;
    
        gHAVPandAVPFunctionsProxy->getHAVPPathMapEvent().subscribe([&](HAVPandAVPFunctions::HAVPMapFileArray array) {
        if (gHAVPSystemFunctionsListener == NULL) {
            LOGE("HAVPandAVPFunctionsListenerRegister: gHAVPSystemFunctionsListener is null.");
            return;
        }
        MapFileArray out;
        for (int i = 0; i < array.size(); i++) {
            out.dynamicBYTE.push_back(array[i]);
            LOGD("HAVPPathMapEvent: out i： %d ,dynamicBYTE： %d", i, out.dynamicBYTE[i]);
        }

        gHAVPSystemFunctionsListener->PathMapEventListener(out);
        isLnWorldSubSet=true;
        LOGD("HAVPPathMapEvent: out.len = %lu", out.dynamicBYTE.size());
    });

    gHAVPandAVPFunctionsProxy->getHAVPRendergInfoEvent().subscribe([&](HAVPandAVPFunctions::HAVPVehDataArray array) {
        if (gHAVPSystemFunctionsListener == NULL) {
            LOGE("HAVPandAVPFunctionsListenerRegister: gHAVPSystemFunctionsListener is null.");
            return;
        }
        VehDataArray out;
        for (int i = 0; i < array.size(); i++) {
            out.dynamicBYTE.push_back(array[i]);
            LOGD("HAVPRendergInfoEvent: out i： %d ,dynamicBYTE： %d", i, out.dynamicBYTE[i]);
        }

        gHAVPSystemFunctionsListener->RendergInfoEventListener(out);
        isVehDataSubSet=true;
        LOGD("HAVPRendergInfoEvent: out.len = %lu", out.dynamicBYTE.size());
    });

    gHAVPandAVPFunctionsProxy->getHAVPPathInfoEvent().subscribe([&](HAVPandAVPFunctions::HAVPLearningWorldArray array) {
        if (gHAVPSystemFunctionsListener == NULL) {
            LOGE("HAVPandAVPFunctionsListenerRegister: gHAVPSystemFunctionsListener is null.");
            return;
        }
        LearningWorldArray out;
        for (int i = 0; i < array.size(); i++) {
            out.dynamicBYTE.push_back(array[i]);
            LOGD("HAVPPathInfoEvent: out i： %d ,dynamicBYTE： %d", i, out.dynamicBYTE[i]);
        }

        gHAVPSystemFunctionsListener->PathInfoEventListener(out);
        isMapFileSubSet=true;
        LOGD("HAVPPathInfoEvent: out.len = %lu", out.dynamicBYTE.size());
    });
}
//AVPhal is not using this interface.  Reserved as a backup
// void HAVPSystemFunctionsListenerUnRegister() {
//     LOGD("TBoxSystemFuntionsListenerUnRegister start, isLnWorldSubSet[%d], isVehDataSubSet[%d], isMapFileSubSet[%d],
//     isLnWorldSubSet, isVehDataSubSet, isMapFileSubSet);
//     if(isLnWorldSubSet){
//         isLnWorldSubSet = false;
//         gHAVPSystemFunctionsListener->getGPSDataAttribute().getChangedEvent().unsubscribe(mSubscriptionGPSData);
//     }
    
//     if(isVehDataSubSet){
        
//     }
    
//     if(isMapFileSubSet){
        
//     }
    
// }