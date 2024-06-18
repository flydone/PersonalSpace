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

#ifndef DVR_VIMS_DVRSTATUSREPORT_H
#define DVR_VIMS_DVRSTATUSREPORT_H


#include "public_def.h"
#include <vector>
#include <stdint.h>

#define PATH_LEN 128

typedef __uint8_t CurrentTransProgress;
typedef __uint8_t TimelapseVideoInterval;
typedef __uint8_t TotalRecordingTime;
typedef __uint8_t CaptureNumber;
typedef __uint8_t TotalCareTime;
typedef __uint16_t TimelapseVideoTotalFrameNumber;
typedef __uint8_t CaptureInterval;
typedef __uint8_t PreRecordingTime;
typedef __uint8_t DVRTimelapseVideoPlayFrameNumber;
typedef __uint8_t TotalTransProgress;
typedef __uint8_t DeleteProgress;
typedef __uint32_t FileID;
typedef __uint32_t FileSize;
typedef __uint32_t ThemePictureID;

typedef enum {
    E_OMC_OK = 0,
    E_OMC_FAULT = 1
}OMCSystemStatus_DT;

typedef enum {
    E_SENSOR_OK = 0,
    E_SENSOR_FAULT = 1,
    E_SENSOR_INIT = 2
}DVRSensorStatus_DT;

typedef enum {
    E_DVR_STATUS_OK = 0,
    E_DVR_STATUS_FAULT = 1
}DVRSystemStatus_DT;

typedef enum {
    E_MANUALCAPTURE = 0,
    E_MANUALRECORDING = 1,
    E_STOPTIMELAPSEVIDEOTAPE = 2,
    E_STOPCARINGMODE = 3,
    E_STOPEXPORTFILE = 4,
    E_OMCMANUALCAPTURE = 5,
    E_STOPASYNCDELETEFILE = 6,
    E_FINDCARCAPTURE = 7
}ManualOperation_DT;

typedef enum {
    E_EVENTSTART = 0,
    E_EVENTSTOP = 1,
    E_EVENTFAILED = 2
}EventOperationType_DT;

typedef enum {
    E_SUCCESS = 0,
    E_UNKNOW = 1,
    E_EVENTTYPEERROR = 2,
    E_ACCESSTYPEERROR = 3,
    E_BUSY = 4,
    E_CAPACITYNOTENOUGH = 5
}OMCCaptureFaileCode_DT;

struct DVRSystemStatusOut{
    DVRSystemStatus_DT dvrSystemStatusDt;
};

struct SetResultContinuousCaptureACKOut{
    SetResult_DT continuousCaptureACK;
};

struct SetResultManualOperationACKOut{
    SetResult_DT manualOperationACK;
};

struct SetResultVideoRecordingACKOut{
    SetResult_DT videoRecordingACK;
};

struct SetResultTimelapseVideoTapeACKOut{
    SetResult_DT timelapseVideoTapeACK;
};

struct SetResultCaringModeACKOut{
    SetResult_DT caringModeACK;
};

struct DVRSensorStatusStruct_DT{
    AccessType_DT accessTypeDt;
    DVRSensorStatus_DT dvrSensorStatusDt;
};

struct OMCCaptureFaileCodeOut{
    OMCCaptureFaileCode_DT omcCaptureFaileCode;
};

struct ExportFileInfoStruct_DT{
        CurrentTransProgress currentTransProgress;
        char filePath[PATH_LEN];
};

struct FileContentArray_DT {
    public:
        FileContentArray_DT() {
        };
        ~FileContentArray_DT() {
        }

    public:
        std::vector<uint8_t> dynamicBYTE;
};

class DVRStatusReportListener {
public:
    virtual ~DVRStatusReportListener(){};
    virtual void DVRSystemStatusReportListener(DVRSystemStatus_DT dVRSystemStatusDt){};
    virtual void DVRSensorStatusReportListener(DVRSensorStatusStruct_DT dVRSensorStatusStructDt){};

    virtual void EventOperationReportEventListener(EventOperationType_DT eventOperationTypeDt, EventType_DT eventTypeDt, AccessType_DT accessTypeDt){};
    virtual void DVREventReportEventListener(char *eventTime ,EventType_DT eventTypeDt ,AccessType_DT accessTypeDt ,char *filePath ,char *thumbnailPath){};
    virtual void DVRTFStatusReportEventListener(TFCardOption_DT tFCardOptionDt ,TFCardStatus_DT tFCardStatusDt ,TFCardCapacity_DT tFCardCapacityDt){};
    virtual void DVREMMCStatusReportEventListener(EMMCStatus_DT eMMCStatusDt ,EMMCCapacityStruct_DT eMMCCapacityStructDt){};
    virtual void ExportOperationProgressReportEventListener(ExportFileInfoStruct_DT exportFileInfoStructDt ,TotalTransProgress totalTransProgress){};
    virtual void AsyncDeleteOperationProgressEventListener(DeleteProgress deleteProgress){};

    virtual void OMCThemePictureReportEventListener(AccessType_DT accessTypeDt , ThemePictureID themePictureId){};

};

void DVRStatusReportInit(char *appName, char *configFile);
bool DVRStatusReportIsReady();
CallStatus_DT DVRSystemStatusReportFunc(DVRSystemStatusOut &out);
CallStatus_DT DVRSensorStatusReportFunc(DVRSensorStatusStruct_DT &out);
CallStatus_DT DVRStatusReportACKFunc(SetResult_DT statusReportACKDt);
CallStatus_DT DVRContinuousCaptureFunc(AccessType_DT accessTypeDt,CaptureNumber captureNumber,CaptureInterval captureInterval,SetResultContinuousCaptureACKOut &out);
CallStatus_DT DVRManualOperationFunc(ManualOperation_DT manualOperationDt,AccessType_DT accessTypeDt,SetResultManualOperationACKOut &out);
CallStatus_DT StartShortVideoRecordingFunc(AccessType_DT videoRecordingChannel,PreRecordingTime preRecordingTime,TotalRecordingTime totalRecordingTime,SetResultVideoRecordingACKOut &out);
CallStatus_DT StopShortVideoRecordingFunc(AccessType_DT videoRecordingChannel,SetResultVideoRecordingACKOut &out);
CallStatus_DT DVRTimelapseVideoTapeFunc(TimelapseVideoInterval timelapseVideoInterval,TimelapseVideoTotalFrameNumber timelapseVideoTotalFrameNumber,DVRTimelapseVideoPlayFrameNumber dvrTimelapseVideoPlayFrameNumber,AccessType_DT accessTypeDt,SetResultTimelapseVideoTapeACKOut &out);
CallStatus_DT CaringModeFunc(AccessType_DT accessTypeDt,TotalCareTime totalCareTime,SetResultCaringModeACKOut &out);

CallStatus_DT TFCardExportCapacityQueryFuc(TFCardOption_DT tFCardOptionDt , TotalExportCapacity &totalExportCapacity , FreeExportCapacity &freeExportCapacity);
CallStatus_DT OMCCaptureRequestFuc(const char *eventTime , EventType_DT eventTypeDt , AccessType_DT accessTypeDt , FileID fileId , FileSize fileSize , OMCCaptureFaileCodeOut &out);
CallStatus_DT PictureTransferRequestFuc(const char *eventTime , EventType_DT eventTypeDt , AccessType_DT accessTypeDt , FileID fileId , FileSize fileSize , FileContentArray_DT &fileContentArray , OMCCaptureFaileCodeOut &out);
CallStatus_DT OMCThemePictureResultFuc(AccessType_DT accessTypeDt , ThemePictureID themePictureId , FileSize fileSize , FileContentArray_DT &fileContentArray , OMCCaptureFaileCodeOut &out);

void DVRStatusReportListenerRegister(DVRStatusReportListener *listener);
void DVRStatusReportListenerUnRegister();

//V2.2 Interface Abandoned
//virtual void OMCStatusReportACKListener(SetResult_DT statusReportACKDt){};
//CallStatus_DT OMCSystemStatusReportFunc(OMCSystemStatus_DT omcSystemStatusDt);
//CallStatus_DT OMCContinuousCaptureFunc(AccessType_DT accessTypeDt,CaptureNumber captureNumber,CaptureInterval captureInterval,SetResultContinuousCaptureACKOut &out);

#endif //DVR_VIMS_DVRSTATUSREPORT_H
