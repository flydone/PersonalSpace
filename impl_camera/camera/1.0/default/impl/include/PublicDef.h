 /*************************************************************************
 * Copyright (C) 2023 GWM Automotive Inc.
 *
 * The copyright notice above does not evidence any actual
 * or intended publication of such source code.
 * The code contains GWM Confidential Proprietary Information.
 *************************************************************************/
 /**************************************************************************
 * @file PublicDef.h
 * Define commonly used definitions.
 *
 * @project     v3.5
 * @subsystem
 * @version     0.1
 * @author
 * @date        2023-9-8

 Module-History:
 Date(dd.mm.year)| Author            | Reason
 The latest entry at the head of the history list.
 8/9/2023         Zhao Ying         Init version

***************************************************************************/
#ifndef VENDOR_GWM_HARDWARE_CAMERA_V1_0_PUBLICDEF_H
#define VENDOR_GWM_HARDWARE_CAMERA_V1_0_PUBLICDEF_H

#define FDBUS_TIMEOUT   3000
#define RETRY_COUNT     20
#define INTERVAL_TIME   500 //ms
#define INVALID_VALUE   -1

#define STATUS_REPORT_INTERNAL 1000
#define STATUS_REPORT_LMT      5

namespace vendor {
namespace gwm {
namespace hardware {
namespace camera {
namespace V1_0 {
namespace implementation {

    // enum DVR function action
    enum DVR_FUNCTION_ACRION : uint8_t
    {
        DVR_UNKOWN = 0,
        DVR_VIDEO_START = 1U,
        DVR_VIDEO_STOP = 2U,
        DVR_VIDEO_PAUSE = 3U,
        DVR_TFCARD_FORMAT = 4U,
        DVR_TFCARD_QUERY = 5U,
    };

    enum InterfaceType : uint8_t
    {
        FILE_OPERATION = 0,  // FileOperation
        STATUS_REPORT = 1U,  // StatusReport
        SYSTEM_CONFIG = 2U,  // SystemConfig
    };

    enum DVRMessageId : int32_t
    {
        START_PREVIEW = 1,
        STOP_PREVIEW,
        START_RECORD,
        STOP_RECORD,
        START_CAPTURE,
        START_LAPSEVIDEO,
        STOP_LAPSEVIDEO,
        FORMAT_TFCARD,
        QUERY_SYSTEMSTATUS,
        SET_PARAM,
        GET_PARAM,
        RESET_FACTORY,
        FILELIST_REQUEST,
        DELETE_FILELIST,
        ALLFILE_DELETE,
        ASYNC_ALLFILE_DELETE,
        STOP_ASYNC_ALLFILE_DELETE,
        EXPORT_FILELIST,
        ALLFILE_EXPORT,
        CANCEL_FILESEXPORT,
        EXPORT_FILECAPACITY,
        SELECT_ALLFILECAPACITY,
        EMMCSTATUS_REQUEST,
        TFCARDSTATUS_REQUEST,
        TFCARDCAPACITY_REQUEST,
        RECORDSTATE_REQUEST,
        OMCCAPTURE_REQUEST,
        OMCCAPTURETRANSFER_REQUEST,
        DVRCAPTURE_REQUEST,
        DVRCAPTURETRANSFER_REQUEST,
        DVRFILECAPACITYINFO_REQUEST,
        FILELISTINCLUDEDATE_REQUEST,
    };

    struct DVRSystemStatusCache
    {
        bool needNotify = false;
        DVRSystemStatus_DT dVRSystemStatus;
    };

    struct OMCStatusCache
    {
        bool needNotify = false;
        SetResult_DT statusReportACK;
    };

    struct DVRSensorStatusCache
    {
        bool needNotify = false;
        std::vector<DVRSensorStatusStruct_DT> dVRSensorStatusStruct;
    };

    struct EventOperationReportCache
    {
        bool needNotify = false;
        EventOperationType_DT eventOperationType;
        EventType_DT eventType;
        AccessType_DT accessType;
    };

    struct DVRTFStatusCache
    {
        bool needNotify = false;
        TFCardOption_DT tFCardOption;
        TFCardStatus_DT tFCardStatus;
        TFCardCapacity_DT tFCardCapacity;
    };

    struct DVREMMCStatusCache
    {
        bool needNotify = false;
        EMMCStatus_DT eMMCStatus;
        EMMCCapacityStruct_DT eMMCCapacityStruct;
    };

    typedef struct DVRMessage
    {
        DVRMessageId id;
        GWM_DVRCameraId cameraId;
        GWM_DVR_VIDEO_TYPE videoType;
        int64_t timeLapseVideoInteval;
        int16_t totalFrameNumber;
        int16_t playFrameNumber;
        GWM_DVR_TFCardId tfCardId;
        GWM_DVRSetParam param;
        GWM_DVR_FileOperateAction fileOperateAction;
        GWM_DVRFileListREQ fileListREQ;
        std::vector<std::string> file_path_url;
        GWM_DVRFileType fileType;
        GWM_DVRExportType exportType;
        std::string eventTime;
        GWM_DVREventType eventType;
        uint32_t fileId;
        uint32_t fileSize;
        std::string filePath;
        GWM_TFAllFileCapacity fileCapacityType;
        std::vector<GWM_ParamFileType> fileTypeList;
        uint8_t fileNumber;
        std::string fileName;
    } DVRMessage_t;
}
}
}
}
}
}

#endif // VENDOR_GWM_HARDWARE_CAMERA_V1_0_PUBLICDEF_H