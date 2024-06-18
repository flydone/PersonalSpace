/*************************************************************************
 * Copyright (C) 2022 GWM Automotive Inc.
 *
 * The copyright notice above does not evidence any actual
 * or intended publication of such source code.
 * The code contains GWM Confidential Proprietary Information.
 *************************************************************************/
//
// Created by LZX on 2022/4/3.
//

#include "public_util.h"
#include "DVRSystemConfig.h"

void DVRSystemConfigInit(char *appName, char *configFile) {
    LOGI("DVRSystemConfigInit, appName[%s], configFile[%s]", appName, configFile);
    if (configFile) {
        setenv("VSOMEIP_CONFIGURATION", configFile, 1);
    }
    if (gRuntime == NULL) {
        gRuntime = CommonAPI::Runtime::get();
    }
    gDVRSystemConfigProxy = gRuntime->buildProxy<DVRSystemConfigProxy>(
            "local", "DVRSystemConfig01", appName);
    std::string versionInfo = gRuntime->get_version();
    std::string version = versionInfo.substr(versionInfo.rfind(" ") + 1);

    LOGI("DVRSystemConfigInit: appName = %s version = %s", appName, version.c_str());
    __system_property_set("vendor.gwm.someip.version", version.c_str());
}

bool DVRSystemConfigIsReady() {
    bool ret = gDVRSystemConfigProxy->isAvailable();
    LOGD("DVRSystemConfigIsReady: %d",ret);
    return ret;
}

void fillPathInfoStruct(DVRSystemConfig::ConfigListArray &array,ConfigListArrayOut &out) {
    int len = array.size();
    LOGD("fillPathInfoStruct: enter, len:%d", len);

    for (int i=0;i<len;i++) {
        ParamCofigStruct_DT configItem;
        configItem.configParamValueTypeDt = static_cast<ConfigParamValueType_DT>(array[i].getConfigParamValueType().value_);
        configItem.paramConfigTypeDt = static_cast<ParamConfigType_DT>(array[i].getParamConfigType().value_);
        configItem.paramConfigOperationDt = static_cast<ParamConfigOperation_DT>(array[i].getParamConfigOperation().value_);
        out.dynamicArray.push_back(std::move(configItem));
        LOGD("fillPathInfoStruct: ConfigParamValueType = %d, ParamConfigType = %d, ParamConfigOperation = %d, len = %d",
             out.dynamicArray[i].configParamValueTypeDt ,out.dynamicArray[i].paramConfigTypeDt ,out.dynamicArray[i].paramConfigOperationDt ,len);
    }
}

CallStatus_DT DVRGetConfigFunc(GetAllConfig_DT GetAllConfig,ConfigTypeList &list,ConfigListArrayOut &out){
    CommonAPI::CallStatus callStatus;

    DVRSystemConfig::GetAllConfig config;
    config.value_ = GetAllConfig;
    
    DVRSystemConfig::ConfigTypeList configTypeList;
    for (int i = 0; i < list.dynamicList.size(); ++i) {
        configTypeList[i].value_ = static_cast<ParamConfigType_DT>(list.dynamicList[i].ParamConfigType);
    }

    DVRSystemConfig::ConfigListArray array;
    gDVRSystemConfigProxy->DVRGetConfig(config, configTypeList, callStatus, array);

    int len = array.size();
    if(len == 0){
        LOGI("DVRGetConfigFunc: out.len == 0 callStatus = %d",static_cast<CallStatus_DT>(callStatus));
        return static_cast<CallStatus_DT>(callStatus);
    }
    fillPathInfoStruct(array,out);
    LOGD("DVRGetConfigFunc: callStatus = %d, out.len = %lu",static_cast<CallStatus_DT>(callStatus), out.dynamicArray.size());
    return static_cast<CallStatus_DT>(callStatus);
}

CallStatus_DT DVRSetConfig(ConfigListArrayInput &array,SetResultOut &out){
    LOGD("DVRSetConfig, len:%lu", array.dynamicArray.size());
    CommonAPI::CallStatus callStatus;

    DVRSystemConfig::ConfigListArray configListArray;

    DVRSystemConfig::ConfigParamValueType configParamValueType;
    DVRSystemConfig::ParamConfigType paramConfigType;
    DVRSystemConfig::ParamConfigOperation paramConfigOperation;

    for (int i = 0; i < array.dynamicArray.size(); ++i) {
        configParamValueType.value_ = array.dynamicArray[i].configParamValueTypeDt;
        paramConfigType.value_ = array.dynamicArray[i].paramConfigTypeDt;
        paramConfigOperation.value_ = array.dynamicArray[i].paramConfigOperationDt;

        DVRSystemConfig::ParamCofigStruct config;
        config.setConfigParamValueType(static_cast<DVRSystemConfig::ConfigParamValueType>(configParamValueType));
        config.setParamConfigType(static_cast<DVRSystemConfig::ParamConfigType>(paramConfigType));
        config.setParamConfigOperation(static_cast<DVRSystemConfig::ParamConfigOperation>(paramConfigOperation));

        configListArray.push_back(config);
    }

    DVRSystemConfig::SetResult result;
    gDVRSystemConfigProxy->DVRSetConfig(configListArray, callStatus, result);
    out.ParamConfigResult = static_cast<SetResult_DT>(result.value_);
    LOGD("DVRSetConfig: out = %d, callStatus = %d",out.ParamConfigResult, static_cast<CallStatus_DT>(callStatus));
    return static_cast<CallStatus_DT>(callStatus);
}

CallStatus_DT ResetDefaultConfigFunc(ResetConfigType_DT ResetConfigType,SetResultResetConfigOut &out){
    CommonAPI::CallStatus callStatus;

    DVRSystemConfig::ResetConfigType type;
    type.value_ = ResetConfigType;

    DVRSystemConfig::SetResult result;

    gDVRSystemConfigProxy->ResetDefaultConfig(type ,callStatus ,result);

    out.ResetConfigACK = static_cast<SetResult_DT>(result.value_);

    LOGD("ResetDefaultConfigFunc: out = %d, callStatus = %d",out.ResetConfigACK, static_cast<CallStatus_DT>(callStatus));
    return static_cast<CallStatus_DT>(callStatus);
}