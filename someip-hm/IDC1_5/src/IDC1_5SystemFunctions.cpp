/*************************************************************************
 * Copyright (C) 2020 GWM Automotive Inc.
 *
 * The copyright notice above does not evidence any actual
 * or intended publication of such source code.
 * The code contains GWM Confidential Proprietary Information.
 *************************************************************************/
//
// Created by Song Yajing on 2021/11/24.
//

#include "public_util.h"
#include "IDC1_5SystemFunctions.h"

IDC1_5SystemFunctionsListener *gIDC1_5SystemFunctionsListener = NULL;

void IDC1_5SystemFunctionsInit(char *appName, char *configFile) {
    LOGD("IDC1_5SystemFunctionsInit: enter");
    if (configFile) {
        setenv("VSOMEIP_CONFIGURATION", configFile, 1);
    }
    if (gRuntime == NULL) {
        gRuntime = CommonAPI::Runtime::get();
    }
    gIDC1_5SystemFunctionsProxy = gRuntime->buildProxy<IDC1_5SystemFunctionsProxy>(
        "local", "IDC1_5SystemFunctions01", appName);
    std::string versionInfo = gRuntime->get_version();
    std::string version = versionInfo.substr(versionInfo.rfind(" ") + 1);

    LOGD("IDC1_5SystemFunctionsInit: appName = %s version = %s", appName, version.c_str());
    __system_property_set("vendor.gwm.someip.version", version.c_str());
}

bool IDC1_5SystemFunctionsIsReady() {
    bool ret = gIDC1_5SystemFunctionsProxy->isAvailable();
    LOGD("IDC1_5SystemFunctionsIsReady: %d",ret);
    return ret;
}

void IDC1_5SystemFunctionsListenerRegister(IDC1_5SystemFunctionsListener *listener) {
    LOGD("IDC1_5SystemFunctionsListenerRegister: enter");
    gIDC1_5SystemFunctionsListener = listener;

    gIDC1_5SystemFunctionsProxy->getVideoUploadEvent().subscribe([&](const IDC1_5SystemFunctions::DataCollectTriggerStruct &val) {
        if (gIDC1_5SystemFunctionsListener == NULL) {
            LOGE("IDC1_5SystemFunctionsListenerRegister: gIDC1_5SystemFunctionsListener is null.");
            return;
        }

            

        if (!val.getTrigger_type().validate() || !val.getTrigger_subtype().validate()) {
            LOGE("getVideoUploadEvent Trigger_type=%d or Trigger_subtype=%d invalid!\n",
                   val.getTrigger_type().value_, val.getTrigger_subtype().value_);
            return;
        }

        DataCollectTriggerStruct_DT dataCollectTriggerStructDt;

        dataCollectTriggerStructDt.sysTimeUsDt = val.getSys_time_us();
        dataCollectTriggerStructDt.collectBeforeTimeDt = val.getCollect_before_time();
        dataCollectTriggerStructDt.collectAfterTimeDt = val.getCollect_after_time();

        dataCollectTriggerStructDt.triggerTypeDt =
            static_cast<TriggerType_DT>(val.getTrigger_type().value_);
        dataCollectTriggerStructDt.trigger_subtypeDt =
            static_cast<TriggerType_DT>(val.getTrigger_subtype().value_);

        LOGD("DataCollectTriggerStruct: Sys_time_us [%d],CollectBeforeTimeDt [%d],CollectAfterTimeDt [%d],TriggerTypeDt [%d],TriggerTypeDt [%d]",
            dataCollectTriggerStructDt.sysTimeUsDt, dataCollectTriggerStructDt.collectBeforeTimeDt, dataCollectTriggerStructDt.collectAfterTimeDt,
            dataCollectTriggerStructDt.triggerTypeDt, dataCollectTriggerStructDt.trigger_subtypeDt);

        gIDC1_5SystemFunctionsListener->VideoUploadEventListener(dataCollectTriggerStructDt);
        LOGD("IDC1_5SystemFunctionsListenerRegister: end");
    });
}
