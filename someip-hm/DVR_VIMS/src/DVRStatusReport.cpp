/*************************************************************************
 * Copyright (C) 2022 GWM Automotive Inc.
 *
 * The copyright notice above does not evidence any actual
 * or intended publication of such source code.
 * The code contains GWM Confidential Proprietary Information.
 *************************************************************************/
//
// Created by LZX on 2022/4/5.
//

#include "public_util.h"
#include "DVRStatusReport.h"

DVRStatusReportListener *gDVRStatusReportListener = NULL;

Subscription mSubscriptionDVRSystemStatus;
Subscription mSubscriptionOMCStatus;
Subscription mSubscriptionDVRSensorStatus;

bool isDVRSystemStatusSubSet = false;
bool isOMCStatusSubSet = false;
bool isDVRSensorStatusSubSet = false;

void DVRStatusReportInit(char *appName, char *configFile) {
    LOGI("DVRStatusReportInit, appName[%s], configFile[%s]", appName, configFile);
    if (configFile) {
        setenv("VSOMEIP_CONFIGURATION", configFile, 1);
    }
    if (gRuntime == NULL) {
        gRuntime = CommonAPI::Runtime::get();
    }
    gDVRStatusReportProxy = gRuntime->buildProxy<DVRStatusReportProxy>(
            "local", "DVRStatusReport01", appName);
    std::string versionInfo = gRuntime->get_version();
    std::string version = versionInfo.substr(versionInfo.rfind(" ") + 1);

    LOGI("DVRStatusReportInit: appName = %s version = %s", appName, version.c_str());
    __system_property_set("vendor.gwm.someip.version", version.c_str());
}

bool DVRStatusReportIsReady() {
    bool ret = gDVRStatusReportProxy->isAvailable();
    LOGD("DVRStatusReportIsReady: %d",ret);
    return ret;
}

//CallStatus_DT OMCSystemStatusReportFunc(OMCSystemStatus_DT omcSystemStatusDt){
//    CommonAPI::CallStatus callStatus;
//
//    DVRStatusReport::OMCSystemStatus status;
//    status.value_ = omcSystemStatusDt;
//
//    gDVRStatusReportProxy->OMCSystemStatusReport(status ,callStatus);
//    LOGD("OMCSystemStatusReportFunc: callStatus = %d", static_cast<CallStatus_DT>(callStatus));
//    return static_cast<CallStatus_DT>(callStatus);
//}

CallStatus_DT DVRSystemStatusReportFunc(DVRSystemStatusOut &out){
    CommonAPI::CallStatus callStatus;

    DVRStatusReport::DVRSystemStatus dvrSystemStatus;

    gDVRStatusReportProxy->getDVRSystemStatusReportAttribute().getValue(callStatus, dvrSystemStatus);

    out.dvrSystemStatusDt = static_cast<DVRSystemStatus_DT>(dvrSystemStatus.value_);

    LOGD("DVRSystemStatusReportFunc: callStatus = %d , dvrSystemStatusDt = %d", static_cast<CallStatus_DT>(callStatus) , out.dvrSystemStatusDt);
    return static_cast<CallStatus_DT>(callStatus);
}

CallStatus_DT DVRSensorStatusReportFunc(DVRSensorStatusStruct_DT &out){
    CommonAPI::CallStatus callStatus;

    DVRStatusReport::DVRSensorStatusStruct dvrSensorStatusStruct;

    gDVRStatusReportProxy->getDVRSensorStatusReportAttribute().getValue(callStatus, dvrSensorStatusStruct);

    out.accessTypeDt = static_cast<AccessType_DT>(dvrSensorStatusStruct.getAccessType().value_);
    out.dvrSensorStatusDt = static_cast<DVRSensorStatus_DT>(dvrSensorStatusStruct.getDVRSensorStatus().value_);

    LOGD("DVRSensorStatusReportFunc: callStatus = %d , accessTypeDt= %d , dvrSensorStatusDt = %d", static_cast<CallStatus_DT>(callStatus) , out.accessTypeDt, out.dvrSensorStatusDt);
    return static_cast<CallStatus_DT>(callStatus);
}

CallStatus_DT DVRStatusReportACKFunc(SetResult_DT statusReportACKDt){
    CommonAPI::CallStatus callStatus;

    DVRStatusReport::SetResult result;
    result.value_ = statusReportACKDt;

    gDVRStatusReportProxy->DVRStatusReportACK(result ,callStatus);
    LOGD("DVRStatusReportACKFunc: result = %d , callStatus = %d", statusReportACKDt , static_cast<CallStatus_DT>(callStatus));
    return static_cast<CallStatus_DT>(callStatus);
}

CallStatus_DT DVRContinuousCaptureFunc(AccessType_DT accessTypeDt,CaptureNumber captureNumber,CaptureInterval captureInterval,SetResultContinuousCaptureACKOut &out){
    CommonAPI::CallStatus callStatus;

    DVRStatusReport::AccessType accessType;
    accessType.value_ = accessTypeDt;

    DVRStatusReport::SetResult result;

    gDVRStatusReportProxy->DVRContinuousCapture(accessType ,captureNumber ,captureInterval ,callStatus ,result);

    out.continuousCaptureACK = static_cast<SetResult_DT>(result.value_);

    LOGD("DVRContinuousCaptureFunc: callStatus = %d , accessType = %d , captureNumber = %d , captureInterval = %d ,result = %d", static_cast<CallStatus_DT>(callStatus) , accessTypeDt , captureNumber , captureInterval , out.continuousCaptureACK);
    return static_cast<CallStatus_DT>(callStatus);
}

//CallStatus_DT OMCContinuousCaptureFunc(AccessType_DT accessTypeDt,CaptureNumber captureNumber,CaptureInterval captureInterval,SetResultContinuousCaptureACKOut &out){
//    CommonAPI::CallStatus callStatus;
//
//    DVRStatusReport::AccessType accessType;
//    accessType.value_ = accessTypeDt;
//
//    DVRStatusReport::SetResult result;
//
//    gDVRStatusReportProxy->OMCContinuousCapture(accessType ,captureNumber ,captureInterval ,callStatus ,result);
//
//    out.continuousCaptureACK = static_cast<SetResult_DT>(result.value_);
//
//    LOGD("OMCContinuousCaptureFunc: callStatus = %d", static_cast<CallStatus_DT>(callStatus));
//    return static_cast<CallStatus_DT>(callStatus);
//}

CallStatus_DT DVRManualOperationFunc(ManualOperation_DT manualOperationDt,AccessType_DT accessTypeDt,SetResultManualOperationACKOut &out){
    CommonAPI::CallStatus callStatus;

    DVRStatusReport::ManualOperation manualOperation_dvrstatus;
    manualOperation_dvrstatus.value_ = manualOperationDt;

    DVRStatusReport::AccessType accessType_dvrstatus;
    accessType_dvrstatus.value_ = accessTypeDt;

    DVRStatusReport::SetResult result;

    gDVRStatusReportProxy->DVRManualOperation(manualOperation_dvrstatus ,accessType_dvrstatus ,callStatus ,result);

    out.manualOperationACK = static_cast<SetResult_DT>(result.value_);

    LOGD("DVRManualOperationFunc: manualOperation = %d , accessType = %d , result = %d , callStatus = %d", manualOperationDt , accessTypeDt , out.manualOperationACK , static_cast<CallStatus_DT>(callStatus));
    return static_cast<CallStatus_DT>(callStatus);
}

CallStatus_DT StartShortVideoRecordingFunc(AccessType_DT videoRecordingChannel,PreRecordingTime preRecordingTime,TotalRecordingTime totalRecordingTime,SetResultVideoRecordingACKOut &out){
    CommonAPI::CallStatus callStatus;

    DVRStatusReport::AccessType accessType;
    accessType.value_ = videoRecordingChannel;

    DVRStatusReport::SetResult result;

    gDVRStatusReportProxy->StartShortVideoRecording(accessType ,preRecordingTime ,totalRecordingTime ,callStatus ,result);

    out.videoRecordingACK = static_cast<SetResult_DT>(result.value_);

    LOGD("StartShortVideoRecordingFunc: accessType = %d , preRecordingTime = %d , totalRecordingTime = %d , result = %d , callStatus = %d", videoRecordingChannel , preRecordingTime , totalRecordingTime , out.videoRecordingACK , static_cast<CallStatus_DT>(callStatus));
    return static_cast<CallStatus_DT>(callStatus);
}

CallStatus_DT StopShortVideoRecordingFunc(AccessType_DT videoRecordingChannel,SetResultVideoRecordingACKOut &out){
    CommonAPI::CallStatus callStatus;

    DVRStatusReport::AccessType accessType;
    accessType.value_ = videoRecordingChannel;

    DVRStatusReport::SetResult result;

    gDVRStatusReportProxy->StopShortVideoRecording(accessType ,callStatus ,result);

    out.videoRecordingACK = static_cast<SetResult_DT>(result.value_);

    LOGD("StopShortVideoRecordingFunc: accessType = %d , callStatus = %d", videoRecordingChannel , static_cast<CallStatus_DT>(callStatus));
    return static_cast<CallStatus_DT>(callStatus);
}

CallStatus_DT DVRTimelapseVideoTapeFunc(TimelapseVideoInterval timelapseVideoInterval,TimelapseVideoTotalFrameNumber timelapseVideoTotalFrameNumber,DVRTimelapseVideoPlayFrameNumber dvrTimelapseVideoPlayFrameNumber,AccessType_DT accessTypeDt,SetResultTimelapseVideoTapeACKOut &out){
    CommonAPI::CallStatus callStatus;

    DVRStatusReport::AccessType accessType;
    accessType.value_ = accessTypeDt;

    DVRStatusReport::SetResult result;

    gDVRStatusReportProxy->DVRTimelapseVideoTape(timelapseVideoInterval ,timelapseVideoTotalFrameNumber ,dvrTimelapseVideoPlayFrameNumber ,accessType ,callStatus ,result);

    out.timelapseVideoTapeACK = static_cast<SetResult_DT>(result.value_);

    LOGD("DVRTimelapseVideoTapeFunc: timelapseVideoInterval = %d , timelapseVideoTotalFrameNumber = %d , dvrTimelapseVideoPlayFrameNumber = %d , accessType = %d , result = %d , callStatus = %d",
         timelapseVideoInterval ,
         timelapseVideoTotalFrameNumber ,
         dvrTimelapseVideoPlayFrameNumber ,
         accessTypeDt , out.timelapseVideoTapeACK ,
         static_cast<CallStatus_DT>(callStatus));

    return static_cast<CallStatus_DT>(callStatus);
}

CallStatus_DT CaringModeFunc(AccessType_DT accessTypeDt,TotalCareTime totalCareTime,SetResultCaringModeACKOut &out){
    CommonAPI::CallStatus callStatus;

    DVRStatusReport::AccessType accessType;
    accessType.value_ = accessTypeDt;

    DVRStatusReport::SetResult result;

    gDVRStatusReportProxy->CaringMode(accessType ,totalCareTime ,callStatus ,result);

    out.caringModeACK = static_cast<SetResult_DT>(result.value_);

    LOGD("CaringModeFunc: accessType = %d , totalCareTime = %d , result = %d , callStatus = %d", accessTypeDt , totalCareTime , out.caringModeACK , static_cast<CallStatus_DT>(callStatus));
    return static_cast<CallStatus_DT>(callStatus);
}

CallStatus_DT TFCardExportCapacityQueryFuc(TFCardOption_DT tFCardOptionDt , TotalExportCapacity &totalExportCapacity , FreeExportCapacity &freeExportCapacity){
    CommonAPI::CallStatus callStatus;

    CommonAPI::CallInfo callInfo;
    callInfo.timeout_ = 10*1000;

    DVRStatusReport::TFCardOption tfCardOption;
    tfCardOption.value_ = tFCardOptionDt;

    DVRStatusReport::TotalExportCapacity totalExport;

    DVRStatusReport::FreeExportCapacity freeExport;

    gDVRStatusReportProxy->TFCardExportCapacityQuery(tfCardOption , callStatus , totalExport , freeExport ,&callInfo);

    totalExportCapacity = totalExport;

    freeExportCapacity = freeExport;

    LOGD("TFCardExportCapacityQueryFuc: callStatus = %d , tFCardOptionDt = %d , totalExportCapacity = %d , freeExportCapacity = %d", static_cast<CallStatus_DT>(callStatus) ,tFCardOptionDt ,totalExportCapacity ,freeExportCapacity);
    return static_cast<CallStatus_DT>(callStatus);
}

CallStatus_DT OMCCaptureRequestFuc(const char *eventTime , EventType_DT eventTypeDt , AccessType_DT accessTypeDt , FileID fileId , FileSize fileSize , OMCCaptureFaileCodeOut &out){
    CommonAPI::CallStatus callStatus;

    std::string eventTimeIn(eventTime);
    DVRStatusReport::EventType eventType;
    eventType.value_ = eventTypeDt;

    DVRStatusReport::AccessType accessType;
    accessType.value_ = accessTypeDt;

    DVRStatusReport::FileID id;
    id = fileId;

    DVRStatusReport::FileSize size;
    size = fileSize;

    DVRStatusReport::OMCCaptureFaileCode oMCCaptureFaileCode;

    gDVRStatusReportProxy->OMCCaptureRequest(eventTimeIn , eventType , accessType , id , size , callStatus , oMCCaptureFaileCode);

    out.omcCaptureFaileCode = static_cast<OMCCaptureFaileCode_DT>(oMCCaptureFaileCode.value_);

    LOGD("OMCCaptureRequestFuc: callStatus = %d , eventTimeIn = %s , eventType = %d , accessType = %d , fileId = %d , fileSize = %d , FaileCode = %d" , static_cast<CallStatus_DT>(callStatus) ,eventTimeIn.c_str() ,eventTypeDt ,accessTypeDt ,fileId ,fileSize ,out.omcCaptureFaileCode);

    return static_cast<CallStatus_DT>(callStatus);
}

CallStatus_DT PictureTransferRequestFuc(const char *eventTime , EventType_DT eventTypeDt , AccessType_DT accessTypeDt , FileID fileId , FileSize fileSize , FileContentArray_DT &fileContentArray , OMCCaptureFaileCodeOut &out){
    CommonAPI::CallStatus callStatus;

    std::string eventTimeIn(eventTime);
    DVRStatusReport::EventType eventType;
    eventType.value_ = eventTypeDt;

    DVRStatusReport::AccessType accessType;
    accessType.value_ = accessTypeDt;

    DVRStatusReport::FileID id;
    id = fileId;

    DVRStatusReport::FileSize size;
    size = fileSize;

    DVRStatusReport::FileContentArray contentArray;
    for (int i = 0; i < fileContentArray.dynamicBYTE.size(); ++i) {
        contentArray.push_back(fileContentArray.dynamicBYTE[i]);
    }

    DVRStatusReport::OMCCaptureFaileCode oMCCaptureFaileCode;

    gDVRStatusReportProxy->PictureTransferRequest(eventTimeIn , eventType , accessType , id , size , contentArray , callStatus , oMCCaptureFaileCode);

    out.omcCaptureFaileCode = static_cast<OMCCaptureFaileCode_DT>(oMCCaptureFaileCode.value_);

    LOGD("PictureTransferRequestFuc: callStatus = %d , eventTimeIn = %s , eventType = %d , accessType = %d , fileId = %d , fileSize = %d , FaileCode = %d" , static_cast<CallStatus_DT>(callStatus) ,eventTimeIn.c_str() ,eventTypeDt ,accessTypeDt ,fileId ,fileSize ,out.omcCaptureFaileCode);

    return static_cast<CallStatus_DT>(callStatus);
}

CallStatus_DT OMCThemePictureResultFuc(AccessType_DT accessTypeDt , ThemePictureID themePictureId , FileSize fileSize , FileContentArray_DT &fileContentArray , OMCCaptureFaileCodeOut &out){
    CommonAPI::CallStatus callStatus;

    DVRStatusReport::AccessType accessType;
    accessType.value_ = accessTypeDt;

    DVRStatusReport::ThemePictureID id;
    id = themePictureId;

    DVRStatusReport::FileSize size;
    size = fileSize;

    DVRStatusReport::FileContentArray contentArray;
    for (int i = 0; i < fileContentArray.dynamicBYTE.size(); ++i) {
        contentArray.push_back(fileContentArray.dynamicBYTE[i]);
    }

    DVRStatusReport::OMCCaptureFaileCode oMCCaptureFaileCode;

    gDVRStatusReportProxy->OMCThemePictureResult(accessType , id , size , contentArray , callStatus , oMCCaptureFaileCode);

    out.omcCaptureFaileCode = static_cast<OMCCaptureFaileCode_DT>(oMCCaptureFaileCode.value_);

    LOGD("OMCThemePictureResultFuc: callStatus = %d , accessType = %d , themePictureId = %d , fileSize = %d , FaileCode = %d" , static_cast<CallStatus_DT>(callStatus) ,accessTypeDt ,themePictureId ,fileSize ,out.omcCaptureFaileCode);

    return static_cast<CallStatus_DT>(callStatus);
}

void DVRStatusReportListenerRegister(DVRStatusReportListener *listener) {
    LOGD("DVRStatusReportListenerRegister: enter [%p]", listener);
    gDVRStatusReportListener = listener;
    if (gDVRStatusReportListener == NULL) {
        LOGE("DVRStatusReportListenerRegister, gDVRStatusReportListener is invalid");
        return;
    }

    isDVRSystemStatusSubSet = true;
    mSubscriptionDVRSystemStatus = gDVRStatusReportProxy->getDVRSystemStatusReportAttribute().
        getChangedEvent().
        subscribe([&](const DVRStatusReport::DVRSystemStatus &val) {
            if (!val.validate()) {
                LOGE("DVRStatusReportListenerRegister, getDVRSystemStatusReport DVRSystemStatus=%d invalid!\n", val.value_);
                return;
            }
            DVRSystemStatus_DT dvrSystemStatusDt = static_cast<DVRSystemStatus_DT>(val.value_);
            gDVRStatusReportListener->DVRSystemStatusReportListener(dvrSystemStatusDt);
            LOGD("DVRStatusReportListenerRegister, dvrSystemStatusDt = %d",dvrSystemStatusDt);
         });

//    isOMCStatusSubSet = true;
//    mSubscriptionOMCStatus = gDVRStatusReportProxy->getOMCStatusReportACKAttribute()
//            .getChangedEvent()
//            .subscribe([&](const DVRStatusReport::SetResult &val) {
//                LOGD("+++++++++++  OMCStatusReport CallBack +++++++++++");
//                if (gDVRStatusReportListener == NULL)
//                    return;
//                if (!val.validate()) {
//                    LOGE("getOMCStatusReportACK OMCStatusReportACK=%d invalid!\n", val.value_);
//                    return;
//                }
//                SetResult_DT statusReportACKDt =
//                        static_cast<SetResult_DT>(val.value_);
//                gDVRStatusReportListener->OMCStatusReportACKListener(
//                        statusReportACKDt);
//
//                LOGD("OMCStatusReport >>>>>>>>>>> statusReportACKDt = %d",statusReportACKDt);
//            });

    isDVRSensorStatusSubSet = true;
    mSubscriptionDVRSensorStatus = gDVRStatusReportProxy->getDVRSensorStatusReportAttribute()
        .getChangedEvent()
        .subscribe([&](const DVRStatusReport::DVRSensorStatusStruct &val) {
            DVRSensorStatusStruct_DT dvrSensorStatusStructDt;
            dvrSensorStatusStructDt.accessTypeDt = static_cast<AccessType_DT>(val.getAccessType().value_);
            dvrSensorStatusStructDt.dvrSensorStatusDt = static_cast<DVRSensorStatus_DT>(val.getDVRSensorStatus().value_);

            gDVRStatusReportListener->DVRSensorStatusReportListener(dvrSensorStatusStructDt);

            LOGD("DVRStatusReportListenerRegister, accessTypeDt = %d, dvrSensorStatusDt = %d",dvrSensorStatusStructDt.accessTypeDt ,dvrSensorStatusStructDt.dvrSensorStatusDt);
        });

    gDVRStatusReportProxy->getEventOperationReportEvent().subscribe(
        [&](DVRStatusReport::EventOperationType eventOperationType, DVRStatusReport::EventType eventType,
        DVRStatusReport::AccessType accessType) {
            EventOperationType_DT eventOperationTypeDt = static_cast<EventOperationType_DT>(eventOperationType.value_);
            EventType_DT eventTypeDt = static_cast<EventType_DT>(eventType.value_);
            AccessType_DT accessTypeDt = static_cast<AccessType_DT>(accessType.value_);

            gDVRStatusReportListener->EventOperationReportEventListener(eventOperationTypeDt, eventTypeDt, accessTypeDt);

            LOGD("DVRStatusReportListenerRegister, eventOperationTypeDt = %d , eventTypeDt = %d , accessTypeDt = %d ", eventOperationTypeDt,
                 eventTypeDt, accessTypeDt);
        });

    gDVRStatusReportProxy->getDVREventReportEvent().subscribe(
        [&](std::string eventTime, DVRStatusReport::EventType eventType,
        DVRStatusReport::AccessType accessType ,std::string filePath ,std::string thumbnailPath) {
            EventType_DT eventTypeDt = static_cast<EventType_DT>(eventType.value_);
            AccessType_DT accessTypeDt = static_cast<AccessType_DT>(accessType.value_);

            gDVRStatusReportListener->DVREventReportEventListener(const_cast<char *>(eventTime.c_str()), eventTypeDt, accessTypeDt ,const_cast<char *>(filePath.c_str()) ,const_cast<char *>(thumbnailPath.c_str()));
            LOGD("DVRStatusReportListenerRegister, eventTime = %s , eventTypeDt = %d , accessTypeDt = %d , filePath = %s , thumbnailPath = %s", eventTime.c_str(), eventTypeDt,accessTypeDt , filePath.c_str() , thumbnailPath.c_str());
        });

    gDVRStatusReportProxy->getDVRTFStatusReportEvent().subscribe(
        [&](DVRStatusReport::TFCardOption tfCardOption, DVRStatusReport::TFCardStatus tfCardStatus,
        DVRStatusReport::TFCardCapacity tfCardCapacity) {
            TFCardOption_DT tFCardOptionDt = static_cast<TFCardOption_DT>(tfCardOption.value_);
            TFCardStatus_DT tFCardStatusDt = static_cast<TFCardStatus_DT>(tfCardStatus.value_);

            TFCardCapacity_DT tfCardCapacityDt;
            tfCardCapacityDt.totalCapacity = tfCardCapacity.getTotalCapacity();
            tfCardCapacityDt.remainingCapacity = tfCardCapacity.getRemainingCapacity();

            gDVRStatusReportListener->DVRTFStatusReportEventListener(tFCardOptionDt, tFCardStatusDt, tfCardCapacityDt);
            LOGD("DVRStatusReportListenerRegister, tFCardOptionDt = %d , tFCardStatusDt = %d , totalCapacity = %d , remainingCapacity = %d", tFCardOptionDt, tFCardStatusDt, tfCardCapacityDt.totalCapacity, tfCardCapacityDt.remainingCapacity);

        });

    gDVRStatusReportProxy->getDVREMMCStatusReportEvent().subscribe(
        [&](DVRStatusReport::EMMCStatus emmcStatus, DVRStatusReport::EMMCCapacityStruct emmcCapacityStruct) {
            EMMCStatus_DT emmcStatusDt = static_cast<EMMCStatus_DT>(emmcStatus.value_);

            EMMCCapacityStruct_DT emmcCapacityStructDt;
            emmcCapacityStructDt.totalCapacity = emmcCapacityStruct.getTotalCapacity();
            emmcCapacityStructDt.remainingCapacity = emmcCapacityStruct.getRemainingCapacity();

            gDVRStatusReportListener->DVREMMCStatusReportEventListener(emmcStatusDt, emmcCapacityStructDt);
            LOGD("DVRStatusReportListenerRegister emmcStatusDt = %d , totalCapacity = %d , remainingCapacity = %d ", emmcStatusDt, emmcCapacityStructDt.totalCapacity ,emmcCapacityStructDt.remainingCapacity);
        });

    gDVRStatusReportProxy->getExportOperationProgressReportEvent().subscribe(
        [&](DVRStatusReport::ExportFileInfoStruct exportFileInfoStruct, uint8_t progress) {
            ExportFileInfoStruct_DT exportFileInfoStructDt;
            exportFileInfoStructDt.currentTransProgress = exportFileInfoStruct.getCurrentTransProgress();

            memset(exportFileInfoStructDt.filePath, 0x00, PATH_LEN);
            memcpy(exportFileInfoStructDt.filePath, exportFileInfoStruct.getFilePath().c_str(), exportFileInfoStruct.getFilePath().size());

            TotalTransProgress totalTransProgress = progress;
            gDVRStatusReportListener->ExportOperationProgressReportEventListener(exportFileInfoStructDt, totalTransProgress);
            LOGD("DVRStatusReportListenerRegister currentTransProgress = %d , filePath = %s , totalTransProgress = %d ", exportFileInfoStructDt.currentTransProgress , exportFileInfoStructDt.filePath , totalTransProgress);

        });

    gDVRStatusReportProxy->getAsyncDeleteOperationProgressEvent().subscribe(
        [&](uint8_t progress) {
            DeleteProgress deleteProgress = progress;
            gDVRStatusReportListener->AsyncDeleteOperationProgressEventListener(deleteProgress);
            LOGD("DVRStatusReportListenerRegister AsyncDeleteOperationProgress = %d ", deleteProgress);

        });

//    OMCThemePictureReport Cancel ---- HAIKANG Not Support
//    gDVRStatusReportProxy->getOMCThemePictureReportEvent().subscribe(
//            [&](DVRStatusReport::AccessType accessType, uint32_t pictureId) {
//                LOGD("+++++++++++  OMCThemePictureReport CallBack +++++++++++");
//                if (gDVRStatusReportListener) {
//
//                    AccessType_DT accessTypeDt = static_cast<AccessType_DT>(accessType.value_);
//                    ThemePictureID themePictureId = pictureId;
//                    LOGD("OMCThemePictureReport >>>>>>>>>>> accessTypeDt = %d , themePictureId = %d ", accessTypeDt , themePictureId);
//                    gDVRStatusReportListener->OMCThemePictureReportEventListener(accessTypeDt,themePictureId);
//        }
//    });
}

void DVRStatusReportListenerUnRegister() {
    LOGD("DVRStatusReportListenerUnRegister start, isDVRSensorStatusSubSet[%d], isDVRSystemStatusSubSet[%d], isOMCStatusSubSet[%d] ",
         isDVRSensorStatusSubSet,isDVRSystemStatusSubSet, isOMCStatusSubSet);

    if(isDVRSensorStatusSubSet){
        isDVRSensorStatusSubSet = false;
        gDVRStatusReportProxy->getDVRSensorStatusReportAttribute()
                .getChangedEvent()
                .unsubscribe(mSubscriptionDVRSensorStatus);
    }

     if(isDVRSystemStatusSubSet){
         isDVRSystemStatusSubSet = false;
         gDVRStatusReportProxy->getDVRSystemStatusReportAttribute()
                 .getChangedEvent()
                 .unsubscribe(mSubscriptionDVRSystemStatus);
     }

//    if(isOMCStatusSubSet){
//        isOMCStatusSubSet = false;
//        gDVRStatusReportProxy->getOMCStatusReportACKAttribute()
//                .getChangedEvent()
//                .unsubscribe(mSubscriptionOMCStatus);
//    }
}