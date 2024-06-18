/*************************************************************************
 * Copyright (C) 2024 GWM Automotive Inc.
 *
 * The copyright notice above does not evidence any actual
 * or intended publication of such source code.
 * The code contains GWM Confidential Proprietary Information.
 *************************************************************************/
/**************************************************************************
 * @file DVRSomeipProxy.h
 * DVRSomeipProxy
 *
 * @project     v3.5
 * @subsystem
 * @version     0.1
 * @author
 * @date        2023-9-8

 Module-History:
 Date(dd.mm.year)| Author            | Reason
 The latest entry at the head of the history list.
 8/9/2023         Zhao Ying           Init version
***************************************************************************/
#ifndef VENDOR_GWM_HARDWARE_DVR_V1_0_DVR_SOMEIP_PROXY_H
#define VENDOR_GWM_HARDWARE_DVR_V1_0_DVR_SOMEIP_PROXY_H

#include <utils/RefBase.h>
#include <vendor/gwm/hardware/camera/1.0/IDVR.h>
#include "DVR.h"

namespace vendor {
namespace gwm {
namespace hardware {
namespace camera {
namespace V1_0 {
namespace implementation {

class DVRMessageHandler;
class DVRSomeipProxy : public android::RefBase
{
public:
    DVRSomeipProxy(android::sp<DVR> dvr);

    ~DVRSomeipProxy();

    void setDVRCallback(const std::vector<android::sp<IDVRCallback>>& callbackList);

    GWM_Status startPreview(::vendor::gwm::hardware::camera::V1_0::GWM_DVRCameraId cameraId);
    GWM_Status stopPreview(::vendor::gwm::hardware::camera::V1_0::GWM_DVRCameraId cameraId);
    GWM_Status startRecord(::vendor::gwm::hardware::camera::V1_0::GWM_DVRCameraId cameraId,
        ::vendor::gwm::hardware::camera::V1_0::GWM_DVR_VIDEO_TYPE type);
    GWM_Status stopRecord(::vendor::gwm::hardware::camera::V1_0::GWM_DVRCameraId cameraId,
        ::vendor::gwm::hardware::camera::V1_0::GWM_DVR_VIDEO_TYPE type);
    GWM_Status startCapture(::vendor::gwm::hardware::camera::V1_0::GWM_DVRCameraId cameraId,
        ::vendor::gwm::hardware::camera::V1_0::GWM_DVR_VIDEO_TYPE type);
    GWM_Status startLapseVideo(::vendor::gwm::hardware::camera::V1_0::GWM_DVRCameraId cameraId,
                                int64_t timeLapseVideoInteval,
                                int16_t totalFrameNumber,
                                int16_t playFrameNumber);
    GWM_Status stopLapseVideo(::vendor::gwm::hardware::camera::V1_0::GWM_DVRCameraId cameraId);
    GWM_Status formatTFCard(::vendor::gwm::hardware::camera::V1_0::GWM_DVR_TFCardId tfcard_id);
    GWM_Status resetFactory();
    GWM_Status querySystemInfoFromExtDVR();
    GWM_Status setParam(const ::vendor::gwm::hardware::camera::V1_0::GWM_DVRSetParam &params);
    GWM_Status getParam();
    GWM_Status fileListRequest(const ::vendor::gwm::hardware::camera::V1_0::GWM_DVRFileListREQ &query_file_list);
    GWM_Status deleteFileList(const std::vector<std::string>& file_path_url);
    GWM_Status allFiledelete(::vendor::gwm::hardware::camera::V1_0::GWM_DVRCameraId cameraId,
        ::vendor::gwm::hardware::camera::V1_0::GWM_DVRFileType file_type);
    GWM_Status asyncAllFiledelete(::vendor::gwm::hardware::camera::V1_0::GWM_DVRCameraId cameraId,
        ::vendor::gwm::hardware::camera::V1_0::GWM_DVRFileType file_type);
    GWM_Status stopAsyncAllFiledelete(::vendor::gwm::hardware::camera::V1_0::GWM_DVRCameraId cameraId);
    GWM_Status exportFileList(::vendor::gwm::hardware::camera::V1_0::GWM_DVRExportType export_type,
        const std::vector<std::string>& file_path_url);
    GWM_Status allFileExport(::vendor::gwm::hardware::camera::V1_0::GWM_DVRExportType export_type,
        ::vendor::gwm::hardware::camera::V1_0::GWM_DVRCameraId cameraId,
        ::vendor::gwm::hardware::camera::V1_0::GWM_DVRFileType file_type);
    GWM_Status cancelFilesExport(::vendor::gwm::hardware::camera::V1_0::GWM_DVRCameraId camera_id);
    int32_t exportFileCapacity(const std::vector<std::string>& file_path_url);
    int32_t selectAllFileCapacity(::vendor::gwm::hardware::camera::V1_0::GWM_DVRCameraId camera_id,
        ::vendor::gwm::hardware::camera::V1_0::GWM_DVRFileType file_type);
    GWM_Status emmcStatusRequest();
    GWM_Status tfCardStatusRequest(::vendor::gwm::hardware::camera::V1_0::GWM_DVR_TFCardId tfcard_id);
    GWM_Status tfCardCapacityRequest(::vendor::gwm::hardware::camera::V1_0::GWM_DVR_TFCardId tfcard_id);
    GWM_Status recordStateRequest(::vendor::gwm::hardware::camera::V1_0::GWM_DVRCameraId camera_id);
    GWM_DVROMCCaptureStatus dvrCaptureRequest(::vendor::gwm::hardware::camera::V1_0::GWM_DVRCameraId cameraId,
        const std::string& eventTime,
        ::vendor::gwm::hardware::camera::V1_0::GWM_DVREventType eventType,
        uint32_t fileId,
        uint32_t fileSize,
        bool isOmc);
    GWM_DVROMCCaptureStatus dvrCaptureTransferRequest(::vendor::gwm::hardware::camera::V1_0::GWM_DVRCameraId cameraId,
        const std::string& eventTime,
        ::vendor::gwm::hardware::camera::V1_0::GWM_DVREventType eventType,
        uint32_t fileId,
        uint32_t fileSize,
        const std::string& filePath,
        bool isOmc);
    GWM_Status dvrFileCapacityInfoReq(const ::vendor::gwm::hardware::camera::V1_0::GWM_TFAllFileCapacity file_capacity_type,
        const std::vector<::vendor::gwm::hardware::camera::V1_0::GWM_ParamFileType> &file_type_list);
    GWM_Status fileListIncludeDateReq(const ::vendor::gwm::hardware::camera::V1_0::GWM_DVRFileType file_type,
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVRCameraId camera_id,
        uint8_t file_number,
        const std::string &file_name);

private:
    std::vector<android::sp<IDVRCallback>> mDVRCallbackList;
    std::vector<android::sp<IDVRCallback>>::iterator it;
    android::sp<DVR> mDVR;

    void setDVRTFCardStatus(TFCardStatus_DT dt_status, GWM_DVRTFCardStatus& dvr_tfcard_status);
    void setFileListResult(GWM_Status status, const GWM_DVRFileListREQ& query_file_list,
        const FileListStructArrayOut& out,
        std::vector<GWM_DVRFileListResult>& vec_quest_result);
    void setDVRGetParam(ParamCofigStruct_DT dt, GWM_DVRGetParam& params);
    void setParamCofigStructDT(int32_t i, const GWM_DVRSetParam& params, ParamCofigStruct_DT& dt);
    void setFileCapacityInfo(GWM_Status status, const FileCapacityListArrayOut &out,
        std::vector<GWM_DVRFileCapacity> &vec_file_capacity);
    void setFileListIncludeDate(GWM_Status status, const FileListIncludeDateArrayOut &out,
        std::vector<GWM_FileListIncludeDate> &vec_file_list);
};

}
}
}
}
}
}
#endif // VENDOR_GWM_HARDWARE_DVR_V1_0_DVR_SOMEIP_PROXY_H