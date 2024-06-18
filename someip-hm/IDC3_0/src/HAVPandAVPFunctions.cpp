/*************************************************************************
 * Copyright (C) 2022 GWM Automotive Inc.
 *
 * The copyright notice above does not evidence any actual
 * or intended publication of such source code.
 * The code contains GWM Confidential Proprietary Information.
 *************************************************************************/
//
// Created by Zeng weifeng on 2023/2/14.
//

#include "public_util.h"
#include "HAVPandAVPFunctions.h"

HAVPandAVPFunctionsListener *gHAVPandAVPFunctionsListener = NULL;

Subscription mSubHAPFuncHAVPPathMap;
Subscription mSubHAPFuncHAVPRendergInfo;
Subscription mSubHAPFuncHAVPPathInfo;

Subscription mSubHAVPandAVPFuncHAVPSVPScrnDispInfo;
Subscription mSubHAVPandAVPFuncAVMDispReq;
Subscription mSubHAVPandAVPFuncHAVPPathMap;
Subscription mSubHAVPandAVPFuncHAVPRendergInfo;
Subscription mSubHAVPandAVPFuncHAVPPathInfo;

Subscription mSubSideBsdDispStsInfo;

void HAVPandAVPFunctionsInit(char *appName, char *configFile) {
    LOGD("HAVPandAVPFunctionsInit: enter");
    if (configFile) {
        setenv("VSOMEIP_CONFIGURATION", configFile, 1);
    }
    if (gRuntime == NULL) {
        gRuntime = CommonAPI::Runtime::get();
    }
    gHAVPandAVPFunctionsProxy = gRuntime->buildProxy<HAVPandAVPFunctionsProxy>(
        "local", "HAVPandAVPFunctions01", appName);
    std::string versionInfo = gRuntime->get_version();
    std::string version = versionInfo.substr(versionInfo.rfind(" ") + 1);

    LOGD("HAVPandAVPFunctionsInit: appName = %s version = %s", appName, version.c_str());
    __system_property_set("vendor.gwm.someip.version", version.c_str());
}

bool HAVPandAVPFunctionsIsReady() {
    if(gHAVPandAVPFunctionsProxy == NULL){
        LOGE("HAVPandAVPFunctionsIsReady:HAVPandAVP proxy was built incorrectly");
        return false;
    }
    bool ret = gHAVPandAVPFunctionsProxy->isAvailable();
    LOGD("HAVPandAVPFunctionsIsReady: %d",ret);
    return ret;
}

void HAPFunctionsListenerRegister(HAVPandAVPFunctionsListener *listener){
    LOGD("HAPFunctionsListenerRegister: enter");
    gHAVPandAVPFunctionsListener = listener;
    if(gHAVPandAVPFunctionsProxy == NULL){
        LOGE("HAP proxy was built incorrectly .");
        return ;
    }
    mSubHAPFuncHAVPPathMap = gHAVPandAVPFunctionsProxy->getHAVPPathMapEvent().subscribe([&](HAVPandAVPFunctions::HAVPMapFileArray array) {
        if (gHAVPandAVPFunctionsListener == NULL) {
            LOGE("HAVPandAVPFunctionsListenerRegister: gHAVPandAVPFunctionsListener is null.");
            return;
        }
        HAVPMapFileArray out;
        std::swap(array , out.dynamicBYTE);

        gHAVPandAVPFunctionsListener->HAVPPathMapEventListener(out);
        LOGD("HAVPPathMapEvent: out.len = %lu", out.dynamicBYTE.size());
    });

    mSubHAPFuncHAVPRendergInfo = gHAVPandAVPFunctionsProxy->getHAVPRendergInfoEvent().subscribe([&](HAVPandAVPFunctions::HAVPVehDataArray array) {
        if (gHAVPandAVPFunctionsListener == NULL) {
            LOGE("HAVPandAVPFunctionsListenerRegister: gHAVPandAVPFunctionsListener is null.");
            return;
        }
        HAVPVehDataArray out;
        std::swap(array , out.dynamicBYTE);

        gHAVPandAVPFunctionsListener->HAVPRendergInfoEventListener(out);
        LOGD("HAVPRendergInfoEvent: out.len = %lu", out.dynamicBYTE.size());
    });

    mSubHAPFuncHAVPPathInfo = gHAVPandAVPFunctionsProxy->getHAVPPathInfoEvent().subscribe([&](HAVPandAVPFunctions::HAVPLearningWorldArray array) {
        if (gHAVPandAVPFunctionsListener == NULL) {
            LOGE("HAVPandAVPFunctionsListenerRegister: gHAVPandAVPFunctionsListener is null.");
            return;
        }
        HAVPLearningWorldArray out;
        std::swap(array , out.dynamicBYTE);

        gHAVPandAVPFunctionsListener->HAVPPathInfoEventListener(out);
        LOGD("HAVPPathInfoEvent: out.len = %lu", out.dynamicBYTE.size());
    });
}

void HAVPandAVPFunctionsListenerRegister(HAVPandAVPFunctionsListener *listener) {
    LOGD("HAVPandAVPFunctionsListenerRegister: enter");
    gHAVPandAVPFunctionsListener = listener;
    if(gHAVPandAVPFunctionsProxy == NULL){
        LOGE("HAVPandAVP proxy was built incorrectly.");
        return ;
    }
    mSubHAVPandAVPFuncHAVPSVPScrnDispInfo = gHAVPandAVPFunctionsProxy->getHAVP_SVPScrnDispInfoEvent().subscribe([&](HAVPandAVPFunctions::HAVP_SVPScrnInfoStruct val) {
        if (gHAVPandAVPFunctionsListener == NULL) {
            LOGE("HAVPandAVPFunctionsListenerRegister: gHAVPandAVPFunctionsListener is null.");
            return;
        }
        HAVP_SVPScrnInfoStruct havp_SVPScrnInfoStruct;
        havp_SVPScrnInfoStruct.MapUpdateReq = static_cast<MapUpdateReq>(val.getMapUpdateReq().value_);
        havp_SVPScrnInfoStruct.CurrMAPID = static_cast<CurrMAPID>(val.getCurrMAPID());
        havp_SVPScrnInfoStruct.FunctBtnDisp = static_cast<FunctBtnDisp>(val.getFunctBtnDisp().value_);
        havp_SVPScrnInfoStruct.FunctBtnSts = static_cast<FunctBtnSts>(val.getFunctBtnSts().value_);
        havp_SVPScrnInfoStruct.FunctWorkSts = static_cast<FunctWorkSts>(val.getFunctWorkSts().value_);
        havp_SVPScrnInfoStruct.Signal_Indnc = static_cast<Signal_Indnc>(val.getSignal_Indnc().value_);
        havp_SVPScrnInfoStruct.InterfaceDisTyp = static_cast<InterfaceDisTyp>(val.getInterfaceDisTyp().value_);
        havp_SVPScrnInfoStruct.PopupDisp = static_cast<PopupDisp>(val.getPopupDisp().value_);
        havp_SVPScrnInfoStruct.MapBuildProcBar = static_cast<MapBuildProcBar>(val.getMapBuildProcBar());
        havp_SVPScrnInfoStruct.StartPrkBtnDisp = static_cast<StartPrkBtnDisp>(val.getStartPrkBtnDisp().value_);
        havp_SVPScrnInfoStruct.UpdateRouteBtnDisp = static_cast<UpdateRouteBtnDisp>(val.getUpdateRouteBtnDisp().value_);
        havp_SVPScrnInfoStruct.GuidanceSts = static_cast<GuidanceSts>(val.getGuidanceSts().value_);
        havp_SVPScrnInfoStruct.ActualMapFlr = static_cast<ActualMapFlr>(val.getActualMapFlr());
        havp_SVPScrnInfoStruct.CurrLeavingPOI = static_cast<CurrLeavingPOI>(val.getCurrLeavingPOI());
        havp_SVPScrnInfoStruct.ActualPrkgSlotTyp = static_cast<ActualPrkgSlotTyp>(val.getActualPrkgSlotTyp().value_);
        havp_SVPScrnInfoStruct.ActualPrkgSlot = static_cast<ActualPrkgSlot>(val.getActualPrkgSlot());
        havp_SVPScrnInfoStruct.ActualPrkgArea = static_cast<ActualPrkgArea>(val.getActualPrkgArea());
        havp_SVPScrnInfoStruct.HAVPFunctTextDisp = static_cast<HAVPFunctTextDisp>(val.getHAVPFunctTextDisp().value_);
        havp_SVPScrnInfoStruct.SVPFunctTextDisp = static_cast<SVPFunctTextDisp>(val.getSVPFunctTextDisp().value_);
        havp_SVPScrnInfoStruct.BtnEnaAck = static_cast<BtnEnaAck>(val.getBtnEnaAck().value_);
        havp_SVPScrnInfoStruct.HAVPfunctionSts = static_cast<HAVPfunctionSts>(val.getHAVPfunctionSts().value_);
        havp_SVPScrnInfoStruct.AutoPushSts = static_cast<AutoPushSts>(val.getAutoPushSts().value_);
        havp_SVPScrnInfoStruct.SVPfunctionSts = static_cast<SVPfunctionSts>(val.getSVPfunctionSts().value_);

        gHAVPandAVPFunctionsListener->HAVP_SVPScrnDispInfoEventListener(havp_SVPScrnInfoStruct);
        LOGD("HAVP_SVPScrnDispInfo: HAVP_SVPScrnInfoStruct %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d",
                                    havp_SVPScrnInfoStruct.MapUpdateReq, havp_SVPScrnInfoStruct.CurrMAPID, havp_SVPScrnInfoStruct.FunctBtnDisp, havp_SVPScrnInfoStruct.FunctBtnSts,
                                    havp_SVPScrnInfoStruct.FunctWorkSts, havp_SVPScrnInfoStruct.Signal_Indnc, havp_SVPScrnInfoStruct.InterfaceDisTyp, havp_SVPScrnInfoStruct.PopupDisp,
                                    havp_SVPScrnInfoStruct.MapBuildProcBar, havp_SVPScrnInfoStruct.StartPrkBtnDisp, havp_SVPScrnInfoStruct.UpdateRouteBtnDisp, havp_SVPScrnInfoStruct.GuidanceSts,
                                    havp_SVPScrnInfoStruct.ActualMapFlr, havp_SVPScrnInfoStruct.CurrLeavingPOI, havp_SVPScrnInfoStruct.ActualPrkgSlotTyp, havp_SVPScrnInfoStruct.ActualPrkgSlot,
                                    havp_SVPScrnInfoStruct.ActualPrkgArea, havp_SVPScrnInfoStruct.HAVPFunctTextDisp, havp_SVPScrnInfoStruct.SVPFunctTextDisp, havp_SVPScrnInfoStruct.BtnEnaAck,
                                    havp_SVPScrnInfoStruct.HAVPfunctionSts, havp_SVPScrnInfoStruct.AutoPushSts, havp_SVPScrnInfoStruct.SVPfunctionSts);
    });

    mSubHAVPandAVPFuncAVMDispReq = gHAVPandAVPFunctionsProxy->getAVMDispReqEvent().subscribe([&](HAVPandAVPFunctions::AVMStsReq val) {
        if (gHAVPandAVPFunctionsListener == NULL) {
            LOGE("HAVPandAVPFunctionsListenerRegister: gHAVPandAVPFunctionsListener is null.");
            return;
        }
        AVMStsReq avmStsReq = static_cast<AVMStsReq>(val.value_);
        LOGD("AVMDispReqEvent: AVMStsReq %d", avmStsReq);
        gHAVPandAVPFunctionsListener->AVMDispReqEventListener(avmStsReq);

    });
    mSubHAVPandAVPFuncHAVPPathMap = gHAVPandAVPFunctionsProxy->getHAVPPathMapEvent().subscribe([&](HAVPandAVPFunctions::HAVPMapFileArray array) {
        if (gHAVPandAVPFunctionsListener == NULL) {
            LOGE("HAVPandAVPFunctionsListenerRegister: gHAVPandAVPFunctionsListener is null.");
            return;
        }
        HAVPMapFileArray out;
        std::swap(array , out.dynamicBYTE);

        gHAVPandAVPFunctionsListener->HAVPPathMapEventListener(out);
        LOGD("HAVPPathMapEvent: out.len = %lu", out.dynamicBYTE.size());
    });

    mSubHAVPandAVPFuncHAVPRendergInfo = gHAVPandAVPFunctionsProxy->getHAVPRendergInfoEvent().subscribe([&](HAVPandAVPFunctions::HAVPVehDataArray array) {
        if (gHAVPandAVPFunctionsListener == NULL) {
            LOGE("HAVPandAVPFunctionsListenerRegister: gHAVPandAVPFunctionsListener is null.");
            return;
        }
        HAVPVehDataArray out;
        std::swap(array , out.dynamicBYTE);

        gHAVPandAVPFunctionsListener->HAVPRendergInfoEventListener(out);
        LOGD("HAVPRendergInfoEvent: out.len = %lu", out.dynamicBYTE.size());
    });

    mSubHAVPandAVPFuncHAVPPathInfo = gHAVPandAVPFunctionsProxy->getHAVPPathInfoEvent().subscribe([&](HAVPandAVPFunctions::HAVPLearningWorldArray array) {
        if (gHAVPandAVPFunctionsListener == NULL) {
            LOGE("HAVPandAVPFunctionsListenerRegister: gHAVPandAVPFunctionsListener is null.");
            return;
        }
        HAVPLearningWorldArray out;
        std::swap(array , out.dynamicBYTE);

        gHAVPandAVPFunctionsListener->HAVPPathInfoEventListener(out);
        LOGD("HAVPPathInfoEvent: out.len = %lu", out.dynamicBYTE.size());
    });
}

void SideBsdDispStsInfoListenerRegister(HAVPandAVPFunctionsListener *listener) {
    LOGD("SideBsdDispStsInfoListenerRegister: enter");
    gHAVPandAVPFunctionsListener = listener;
    if(gHAVPandAVPFunctionsProxy == NULL){
        LOGE("HAVPandAVP proxy was built incorrectly.");
        return ;
    }

    mSubSideBsdDispStsInfo = gHAVPandAVPFunctionsProxy->getSideBsdDispStsInfoEvent().subscribe([&](HAVPandAVPFunctions::SideBsdDispStatus val) {
        if (gHAVPandAVPFunctionsListener == NULL) {
            LOGE("HAVPandAVPFunctionsListenerRegister: gHAVPandAVPFunctionsListener is null.");
            return;
        }
        SideBsdDispStatus sideBsdDispStatus = static_cast<SideBsdDispStatus>(val.value_);
        LOGD("SideBsdDispStsInfoEvent: SideBsdDispStatus %d", sideBsdDispStatus);
        gHAVPandAVPFunctionsListener->SideBsdDispStsInfoEventListener(sideBsdDispStatus);
    });
}

void HAPFunctionsListenerUnRegister() {
	LOGD("HAPFunctionsListenerUnRegister: enter");
    if(gHAVPandAVPFunctionsProxy == NULL){
        LOGE("HAVPandAVP proxy was built incorrectly.");
        return ;
    }
    gHAVPandAVPFunctionsProxy->getHAVPPathMapEvent().unsubscribe(mSubHAPFuncHAVPPathMap);
    gHAVPandAVPFunctionsProxy->getHAVPRendergInfoEvent().unsubscribe(mSubHAPFuncHAVPRendergInfo);
    gHAVPandAVPFunctionsProxy->getHAVPPathInfoEvent().unsubscribe(mSubHAPFuncHAVPPathInfo);
}

void HAVPandAVPFunctionsListenerUnRegister() {
	LOGD("HAVPandAVPFunctionsListenerUnRegister: enter");
    if(gHAVPandAVPFunctionsProxy == NULL){
        LOGE("HAVPandAVP proxy was built incorrectly.");
        return ;
    }
    gHAVPandAVPFunctionsProxy->getHAVP_SVPScrnDispInfoEvent().unsubscribe(mSubHAVPandAVPFuncHAVPSVPScrnDispInfo);
    gHAVPandAVPFunctionsProxy->getAVMDispReqEvent().unsubscribe(mSubHAVPandAVPFuncAVMDispReq);
    gHAVPandAVPFunctionsProxy->getHAVPPathMapEvent().unsubscribe(mSubHAVPandAVPFuncHAVPPathMap);
    gHAVPandAVPFunctionsProxy->getHAVPRendergInfoEvent().unsubscribe(mSubHAVPandAVPFuncHAVPRendergInfo);
    gHAVPandAVPFunctionsProxy->getHAVPPathInfoEvent().unsubscribe(mSubHAVPandAVPFuncHAVPPathInfo);
}

void SideBsdDispStsInfoListenerUnRegister() {
    LOGD("SideBsdDispStsInfoListenerUnRegister: enter");
    if(gHAVPandAVPFunctionsProxy == NULL){
        LOGE("HAVPandAVP proxy was built incorrectly.");
        return ;
    }
    gHAVPandAVPFunctionsProxy->getSideBsdDispStsInfoEvent().unsubscribe(mSubSideBsdDispStsInfo);
}

CallStatus AVMDispResp(AVMStsResp avmStsResp){
    CommonAPI::CallStatus callStatus;
    HAVPandAVPFunctions::AVMStsResp resp;
    resp.value_ = avmStsResp;

    gHAVPandAVPFunctionsProxy->AVMDispResp(resp,callStatus);
    LOGD("AVMDispResp: callStatus = %d, avmStsResp = %d ", static_cast<CallStatus>(callStatus), resp.value_);

    return static_cast<CallStatus>(callStatus);
}

CallStatus AutoReq(AutoPushReq autoPushReq){
    CommonAPI::CallStatus callStatus;
    HAVPandAVPFunctions::AutoPushReq req;
    req.value_ = autoPushReq;

    gHAVPandAVPFunctionsProxy->AutoReq(req,callStatus);
    LOGD("AutoReq: callStatus = %d, autoPushReq = %d ", static_cast<CallStatus>(callStatus), req.value_);

    return static_cast<CallStatus>(callStatus);
}

CallStatus HAVPReq(HAVPfunctionReq havpFunctionReq){
    CommonAPI::CallStatus callStatus;
    HAVPandAVPFunctions::HAVPfunctionReq req;
    req.value_ = havpFunctionReq;

    gHAVPandAVPFunctionsProxy->HAVPReq(req,callStatus);
    LOGD("HAVPReq: callStatus = %d, havpFunctionReq = %d ", static_cast<CallStatus>(callStatus), req.value_);

    return static_cast<CallStatus>(callStatus);
}

CallStatus NearSlotIDReq(SelNearSlotID selNearSlotID){
    CommonAPI::CallStatus callStatus;

    gHAVPandAVPFunctionsProxy->NearSlotIDReq(selNearSlotID,callStatus);
    LOGD("NearSlotIDReq: callStatus = %d, selNearSlotID = %d ", static_cast<CallStatus>(callStatus), selNearSlotID);

    return static_cast<CallStatus>(callStatus);
}

CallStatus PrkgFlrReq(SetMapFlr setMapFlr){
    CommonAPI::CallStatus callStatus;

    gHAVPandAVPFunctionsProxy->PrkgFlrReq(setMapFlr,callStatus);
    LOGD("PrkgFlrReq: callStatus = %d, setMapFlr = %d ", static_cast<CallStatus>(callStatus), setMapFlr);

    return static_cast<CallStatus>(callStatus);
}

CallStatus PrkgSlotReq(SetPrkgSlot setPrkgSlot){
    CommonAPI::CallStatus callStatus;

    gHAVPandAVPFunctionsProxy->PrkgSlotReq(setPrkgSlot,callStatus);
    LOGD("PrkgSlotReq: callStatus = %d, setPrkgSlot = %d ", static_cast<CallStatus>(callStatus), setPrkgSlot);

    return static_cast<CallStatus>(callStatus);
}

CallStatus HAVP_SVPSwtReq(BtnEnaReq btnEnaReq){
    CommonAPI::CallStatus callStatus;
    HAVPandAVPFunctions::BtnEnaReq req;
    req.value_ = btnEnaReq;

    gHAVPandAVPFunctionsProxy->HAVP_SVPSwtReq(req,callStatus);
    LOGD("HAVP_SVPSwtReq: callStatus = %d, btnEnaReq = %d ", static_cast<CallStatus>(callStatus), req.value_);

    return static_cast<CallStatus>(callStatus);
}

CallStatus TarPrkgIDReq(TarMapID tarMapID){
    CommonAPI::CallStatus callStatus;

    gHAVPandAVPFunctionsProxy->TarPrkgIDReq(tarMapID,callStatus);
    LOGD("TarPrkgIDReq: callStatus = %d, tarMapID = %d ", static_cast<CallStatus>(callStatus), tarMapID);

    return static_cast<CallStatus>(callStatus);
}

CallStatus PrkgAreaReq(SetPrkgArea setPrkgArea){
    CommonAPI::CallStatus callStatus;

    gHAVPandAVPFunctionsProxy->PrkgAreaReq(setPrkgArea,callStatus);
    LOGD("PrkgAreaReq: callStatus = %d, setPrkgArea = %d ", static_cast<CallStatus>(callStatus), setPrkgArea);

    return static_cast<CallStatus>(callStatus);
}

CallStatus PrkgTypReq(SetPrkgSlotTyp setPrkgSlotTyp){
    CommonAPI::CallStatus callStatus;
    HAVPandAVPFunctions::SetPrkgSlotTyp slotTyp;
    slotTyp.value_ = setPrkgSlotTyp;

    gHAVPandAVPFunctionsProxy->PrkgTypReq(slotTyp,callStatus);
    LOGD("PrkgTypReq: callStatus = %d, setPrkgSlotTyp = %d ", static_cast<CallStatus>(callStatus), slotTyp.value_);

    return static_cast<CallStatus>(callStatus);
}

CallStatus PrkgLotMapUpdSt(MapUpdSt mapUpdSt){
    CommonAPI::CallStatus callStatus;
    HAVPandAVPFunctions::MapUpdSt map;
    map.value_ = mapUpdSt;

    gHAVPandAVPFunctionsProxy->PrkgLotMapUpdSt(map,callStatus);
    LOGD("PrkgLotMapUpdSt: callStatus = %d, mapUpdSt = %d ", static_cast<CallStatus>(callStatus), map.value_);

    return static_cast<CallStatus>(callStatus);
}

CallStatus LvngPOIReq(SetLvngPOI setLvngPOI){
    CommonAPI::CallStatus callStatus;

    gHAVPandAVPFunctionsProxy->LvngPOIReq(setLvngPOI,callStatus);
    LOGD("LvngPOIReq: callStatus = %d, setLvngPOI = %d ", static_cast<CallStatus>(callStatus), setLvngPOI);

    return static_cast<CallStatus>(callStatus);
}

CallStatus SVPReq(SVPfunctionReq svpFunctionReq){
    CommonAPI::CallStatus callStatus;
    HAVPandAVPFunctions::SVPfunctionReq req;
    req.value_ = svpFunctionReq;

    gHAVPandAVPFunctionsProxy->SVPReq(req,callStatus);
    LOGD("SVPReq: callStatus = %d, svpFunctionReq = %d ", static_cast<CallStatus>(callStatus), req.value_);

    return static_cast<CallStatus>(callStatus);
}

CallStatus SideBsdDisp(SideBsdDispRequest sideBsdDispRequest,SideBsdDispStsOut &out){
    CommonAPI::CallStatus callStatus;
    HAVPandAVPFunctions::SideBsdDispRequest req;
    req.value_ = sideBsdDispRequest;
    HAVPandAVPFunctions::SideBsdDispSts sideBsdDispSts;

    gHAVPandAVPFunctionsProxy->SideBsdDisp(req,callStatus,sideBsdDispSts);
    out.sideBsdDispSts = static_cast<SideBsdDispSts>(sideBsdDispSts.value_);

    LOGD("SideBsdDisp: out = %d, callStatus = %d , sideBsdDispRequest = %d",out.sideBsdDispSts, static_cast<CallStatus>(callStatus),req.value_);
    return static_cast<CallStatus>(callStatus);
}


