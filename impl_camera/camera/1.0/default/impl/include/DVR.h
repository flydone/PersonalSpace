/*************************************************************************
* Copyright (C) 2020-2023 GWM Automotive Inc.
*
* The copyright notice above does not evidence any actual
* or intended publication of such source code.
* The code contains GWM Confidential Proprietary Information.
*************************************************************************/
/**************************************************************************
 * @file DVR.h
 * camera DVR function  implimentation
 *
 * @project     v3.5
 * @subsystem
 * @version     0.1
 * @author      XiuFang Liu
 * @date        2020-10-13

 Module-History:
 Date(dd.mm.year)| Author            | Reason
 The latest entry at the head of the history list.
 13/10/2020         XiuFang Liu          Init version
 ***************************************************************************/
#ifndef VENDOR_GWM_HARDWARE_CAMERA_V1_0_DVR_H
#define VENDOR_GWM_HARDWARE_CAMERA_V1_0_DVR_H

#include <vendor/gwm/hardware/camera/1.0/IDVR.h>
#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>
#include <impl/src/proto/common.base.CameraIviQnx.pb.h>
#include <utils/RefBase.h>
#include <common_base/fdbus.h>
#include <mutex>
#include <semaphore.h>
#include <signal.h>
#include <stdint.h>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <iostream>
#include <vendor/gwm/common/hardware/psservice/hidl/1.0/IPSSHidlInterface.h>
#include "IDC1_5SystemFunctions.h"
#include "DVRStatusReport.h"
#include "DVRFileOperation.h"
#include "DVRSystemConfig.h"
#include "public_def.h"
#include "PublicDef.h"

namespace vendor {
namespace gwm {
namespace hardware {
namespace camera {
namespace V1_0 {
namespace implementation {

class CameraFdbClient;
class CameraFdbServer;
class DVRConnectionTimer;
class DVRMessageHandler;
class DVRFdbProxy;
class DVR : public IDVR, public android::hardware::hidl_death_recipient {
public:
    DVR(const android::sp<CameraFdbClient> client, const android::sp<CameraFdbServer> server);
    ~DVR();
    virtual void serviceDied(uint64_t cookie, const android::wp<IBase> &who) override;

    /* Methods from ::vendor::gwm::hardware::camera::V1_0::IDVR follow. */
    android::hardware::Return<::vendor::gwm::hardware::camera::V1_0::GWM_Status> gwm_registerDVRCallback(
        const android::sp<::vendor::gwm::hardware::camera::V1_0::IDVRCallback> &callback)
        override;
    android::hardware::Return<::vendor::gwm::hardware::camera::V1_0::GWM_Status> gwm_startPreview(
        ::vendor::gwm::hardware::camera::V1_0::GWM_DVRCameraId cameraId)
        override;
    android::hardware::Return<::vendor::gwm::hardware::camera::V1_0::GWM_Status> gwm_stopPreview(
        ::vendor::gwm::hardware::camera::V1_0::GWM_DVRCameraId cameraId)
        override;
    android::hardware::Return<::vendor::gwm::hardware::camera::V1_0::GWM_Status> gwm_userStartRecord(
        ::vendor::gwm::hardware::camera::V1_0::GWM_DVRCameraId cameraId,
        ::vendor::gwm::hardware::camera::V1_0::GWM_DVR_VIDEO_TYPE type)
        override;
    android::hardware::Return<::vendor::gwm::hardware::camera::V1_0::GWM_Status> gwm_userStopRecord(
        ::vendor::gwm::hardware::camera::V1_0::GWM_DVRCameraId cameraId,
        ::vendor::gwm::hardware::camera::V1_0::GWM_DVR_VIDEO_TYPE type)
        override;
    android::hardware::Return<::vendor::gwm::hardware::camera::V1_0::GWM_Status> gwm_startCapture(
        ::vendor::gwm::hardware::camera::V1_0::GWM_DVRCameraId cameraId,
        ::vendor::gwm::hardware::camera::V1_0::GWM_DVR_VIDEO_TYPE type)
        override;
    android::hardware::Return<::vendor::gwm::hardware::camera::V1_0::GWM_Status> gwm_startLapseVideo(
        ::vendor::gwm::hardware::camera::V1_0::GWM_DVRCameraId cameraId,
        int64_t timeLapseVideoInteval, int16_t totalFrameNumber,
        int16_t playFrameNumber)
        override;
    android::hardware::Return<::vendor::gwm::hardware::camera::V1_0::GWM_Status> gwm_stopLapseVideo(
        ::vendor::gwm::hardware::camera::V1_0::GWM_DVRCameraId cameraId)
        override;
    android::hardware::Return<::vendor::gwm::hardware::camera::V1_0::GWM_Status> gwm_formatTFCard(
        ::vendor::gwm::hardware::camera::V1_0::GWM_DVR_TFCardId tfcard_id)
        override;
    android::hardware::Return<::vendor::gwm::hardware::camera::V1_0::GWM_Status> gwm_querySystemStatus() override;
    android::hardware::Return<::vendor::gwm::hardware::camera::V1_0::GWM_Status> gwm_setParam(
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVRSetParam &params)
        override;
    android::hardware::Return<::vendor::gwm::hardware::camera::V1_0::GWM_Status> gwm_getParam() override;
    android::hardware::Return<::vendor::gwm::hardware::camera::V1_0::GWM_Status> gwm_resetFactory()
        override;
    android::hardware::Return<::vendor::gwm::hardware::camera::V1_0::GWM_Status> gwm_operateFile(
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVR_FileOperateAction &operation)
        override;
    android::hardware::Return<::vendor::gwm::hardware::camera::V1_0::GWM_Status> gwm_uploadRequset()
        override;
    android::hardware::Return<::vendor::gwm::hardware::camera::V1_0::GWM_Status> gwm_uploadResult(
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVRUploadFileResult &uploadResult)
        override;
    android::hardware::Return<::vendor::gwm::hardware::camera::V1_0::GWM_Status> gwm_sendActCommd(
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVRBroadcastActCommand &boardcastActions)
        override;
    android::hardware::Return<::vendor::gwm::hardware::camera::V1_0::GWM_Status> gwm_sendModuleEvent(
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVRSendModuleEvent &moduleEvent)
        override;
    android::hardware::Return<::vendor::gwm::hardware::camera::V1_0::GWM_Status> gwm_userStartRecord_sync(
        ::vendor::gwm::hardware::camera::V1_0::GWM_DVRCameraId cameraId,
        ::vendor::gwm::hardware::camera::V1_0::GWM_DVR_VIDEO_TYPE type)
        override;
    android::hardware::Return<::vendor::gwm::hardware::camera::V1_0::GWM_Status> gwm_userStopRecord_sync(
        ::vendor::gwm::hardware::camera::V1_0::GWM_DVRCameraId cameraId,
        ::vendor::gwm::hardware::camera::V1_0::GWM_DVR_VIDEO_TYPE type)
        override;
    android::hardware::Return<::vendor::gwm::hardware::camera::V1_0::GWM_Status> gwm_startCapture_sync(
        ::vendor::gwm::hardware::camera::V1_0::GWM_DVRCameraId cameraId,
        ::vendor::gwm::hardware::camera::V1_0::GWM_DVR_VIDEO_TYPE type)
        override;
    android::hardware::Return<::vendor::gwm::hardware::camera::V1_0::GWM_Status> gwm_startLapseVideo_sync(
        ::vendor::gwm::hardware::camera::V1_0::GWM_DVRCameraId cameraId,
        int64_t timeLapseVideoInteval, int16_t totalFrameNumber,
        int16_t playFrameNumber)
        override;
    android::hardware::Return<::vendor::gwm::hardware::camera::V1_0::GWM_Status> gwm_stopLapseVideo_sync(
        ::vendor::gwm::hardware::camera::V1_0::GWM_DVRCameraId cameraId)
        override;

    // add for outside DVR
    //Add file request interface: file type, cameraid, tfid, number of files, last file name
    android::hardware::Return<::vendor::gwm::hardware::camera::V1_0::GWM_Status> gwm_FileListRequest(
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVRFileListREQ &query_file_list)
        override;
    //Add file delete list interface: File URL list
    android::hardware::Return<::vendor::gwm::hardware::camera::V1_0::GWM_Status> gwm_deleteFileList(
        const ::android::hardware::hidl_vec<android::hardware::hidl_string> &file_path_url)
        override;
    //Add file export interface export mode, file URL list
    android::hardware::Return<::vendor::gwm::hardware::camera::V1_0::GWM_Status> gwm_ExportFileList(
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVRExportType export_type,
        const ::android::hardware::hidl_vec<android::hardware::hidl_string> &file_path_url)
        override;
    //Add and cancel export interface
    android::hardware::Return<::vendor::gwm::hardware::camera::V1_0::GWM_Status> gwm_CancelFilesExport(
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVRCameraId camera_id)
        override;
    //Add the capacity acquisition interface for obtaining the list of files to be exported
    android::hardware::Return<::vendor::gwm::hardware::camera::V1_0::GWM_Status> gwm_ExportFileCapacity(
        const ::android::hardware::hidl_vec<android::hardware::hidl_string> &file_path_url)
        override;
    //Add get get EMMC status information: file list
    //1. The status information of EMMC returned in the response command: refer to [EMMC status report] for the value
    //2. Return the capacity information of EMMC in the response command, including total capacity, remaining capacity, unit: MB.
    android::hardware::Return<::vendor::gwm::hardware::camera::V1_0::GWM_Status> gwm_EMMCStatusRequest() override;
    //Get tfcard status information: ID
    android::hardware::Return<::vendor::gwm::hardware::camera::V1_0::GWM_Status> gwm_TFCardStatusRequest(
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVR_TFCardId tfcard_id)
        override;
    //Add all file export interfaces
    android::hardware::Return<::vendor::gwm::hardware::camera::V1_0::GWM_Status> gwm_AllFileExport(
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVRExportType export_type,
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVRCameraId cameraId,
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVRFileType file_type)
        override;
    //Add file delete list interface: File URL list
    android::hardware::Return<::vendor::gwm::hardware::camera::V1_0::GWM_Status> gwm_AllFiledelete(
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVRCameraId cameraId,
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVRFileType file_type)
        override;
    android::hardware::Return<::vendor::gwm::hardware::camera::V1_0::GWM_Status> gwm_AsyncAllFiledelete(
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVRCameraId cameraId,
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVRFileType file_type)
        override;
    android::hardware::Return<::vendor::gwm::hardware::camera::V1_0::GWM_Status> gwm_StopAsyncAllFiledelete(
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVRCameraId cameraId)
        override;
    //Add an interface to obtain the file capacity information of all selected files
    android::hardware::Return<::vendor::gwm::hardware::camera::V1_0::GWM_Status> gwm_SelectAllFileCapacity(
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVRCameraId camera_id,
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVRFileType file_type)
        override;
    android::hardware::Return<::vendor::gwm::hardware::camera::V1_0::GWM_Status> gwm_TFCardCapacityRequest(
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVR_TFCardId tfcard_id)
        override;
    android::hardware::Return<::vendor::gwm::hardware::camera::V1_0::GWM_Status> gwm_RecordStateRequest(
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVRCameraId camera_id)
        override;
    android::hardware::Return<::vendor::gwm::hardware::camera::V1_0::GWM_Status> gwm_OMCCaptureRequest(
        const android::hardware::hidl_string &eventTime,
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVREventType eventType,
        uint32_t fileId,
        uint32_t fileSize)
        override;
    android::hardware::Return<::vendor::gwm::hardware::camera::V1_0::GWM_Status> gwm_OMCCaptureTransferRequest(
        const android::hardware::hidl_string &eventTime,
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVREventType eventType,
        uint32_t fileId,
        uint32_t fileSize,
        const android::hardware::hidl_string &filePath)
        override;
    android::hardware::Return<::vendor::gwm::hardware::camera::V1_0::GWM_Status> gwm_DVRCaptureRequest(
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVRCameraId camera_id,
        const android::hardware::hidl_string &eventTime,
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVREventType eventType,
        uint32_t fileId,
        uint32_t fileSize)
        override;
    android::hardware::Return<::vendor::gwm::hardware::camera::V1_0::GWM_Status> gwm_DVRCaptureTransferRequest(
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVRCameraId camera_id,
        const android::hardware::hidl_string &eventTime,
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVREventType eventType,
        uint32_t fileId,
        uint32_t fileSize,
        const android::hardware::hidl_string &filePath)
        override;
    android::hardware::Return<::vendor::gwm::hardware::camera::V1_0::GWM_Status> gwm_DVRFileCapacityInfoReq(
        const ::vendor::gwm::hardware::camera::V1_0::GWM_TFAllFileCapacity file_capacity_type,
        const ::android::hardware::hidl_vec<::vendor::gwm::hardware::camera::V1_0::GWM_ParamFileType> &file_type_list)
        override;
    android::hardware::Return<::vendor::gwm::hardware::camera::V1_0::GWM_Status> gwm_FileListIncludeDateReq(
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVRFileIncludeDateREQ &file_req)
        override;
    android::hardware::Return<int32_t> gwm_ExportFileCapacity_sync(
        const ::android::hardware::hidl_vec<android::hardware::hidl_string> &file_path_url)
        override;
    android::hardware::Return<int32_t> gwm_SelectAllFileCapacity_sync(
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVRCameraId camera_id,
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVRFileType file_type)
        override;
    android::hardware::Return<::vendor::gwm::hardware::camera::V1_0::GWM_DVROMCCaptureStatus> gwm_OMCCaptureRequest_sync(
        const android::hardware::hidl_string &eventTime,
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVREventType eventType,
        uint32_t fileId,
        uint32_t fileSize)
        override;
    android::hardware::Return<::vendor::gwm::hardware::camera::V1_0::GWM_DVROMCCaptureStatus> gwm_OMCCaptureTransferRequest_sync(
        const android::hardware::hidl_string &eventTime,
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVREventType eventType,
        uint32_t fileId,
        uint32_t fileSize,
        const android::hardware::hidl_string &filePath)
        override;
    android::hardware::Return<::vendor::gwm::hardware::camera::V1_0::GWM_DVROMCCaptureStatus> gwm_DVRCaptureRequest_sync(
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVRCameraId camera_id,
        const android::hardware::hidl_string &eventTime,
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVREventType eventType,
        uint32_t fileId,
        uint32_t fileSize)
        override;
    android::hardware::Return<::vendor::gwm::hardware::camera::V1_0::GWM_DVROMCCaptureStatus> gwm_DVRCaptureTransferRequest_sync(
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVRCameraId camera_id,
        const android::hardware::hidl_string &eventTime,
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVREventType eventType,
        uint32_t fileId,
        uint32_t fileSize,
        const android::hardware::hidl_string &filePath)
        override;
    /* Methods from ::vendor::gwm::hardware::camera::V1_0::IDVR follow. */

    bool checkIsReady(const InterfaceType type, string method_name);
    AccessType_DT switch_cameraid(const ::vendor::gwm::hardware::camera::V1_0::GWM_DVRCameraId cameraId);
    GWM_DVRCameraId accessTypeToCameraId(AccessType_DT accesType);
    void sendActCommdAck(GWM_DVRBroadcastActionsResult act_result);
    void sendModuleEventAck(GWM_DVRModulesEventResult event_result);
    // DVR abnormal status notify status.
    void notifyDVRConnectStatus(bool status);

    /* Only for internal communication with someip. */
    GWM_Status startRecord(GWM_DVRCameraId cameraId, GWM_DVR_VIDEO_TYPE type);
    GWM_Status stopRecord(GWM_DVRCameraId cameraId, GWM_DVR_VIDEO_TYPE type);
    GWM_Status startCapture(GWM_DVRCameraId cameraId, GWM_DVR_VIDEO_TYPE type);
    GWM_Status startLapseVideo(GWM_DVRCameraId cameraId,
                            int64_t timeLapseVideoInteval,
                            int16_t totalFrameNumber,
                            int16_t playFrameNumber);
    GWM_Status stopLapseVideo(GWM_DVRCameraId cameraId);
    GWM_Status querySystemStatus();
    int32_t exportFileCapacity(const std::vector<std::string>& file_path_url, bool isSync);
    int32_t selectAllFileCapacity(GWM_DVRCameraId camera_id, GWM_DVRFileType file_type, bool isSync);
    GWM_DVROMCCaptureStatus dvrCaptureRequest(const AccessType_DT access_type,
        const std::string& eventTime,
        GWM_DVREventType eventType,
        uint32_t fileId,
        uint32_t fileSize,
        bool isOmc,
        bool isSync);
    GWM_DVROMCCaptureStatus dvrCaptureTransferRequest(const AccessType_DT access_type,
        const std::string& eventTime,
        GWM_DVREventType eventType,
        uint32_t fileId,
        uint32_t fileSize,
        const std::string& filePath,
        bool isOmc,
        bool isSync);
    /* Only for internal communication with someip. */

    /* Only for send callback to FWK. */
    void onQNXReplyData(GWM_Status status, FdbMsgCode_t code);
    void onQNXBoardcastData(FdbMsgCode_t code);
    void onReportIPCStatus(GWM_DVRIPCStatus status);
    // add callback for out side DVR
    void onVideoUploadEventListener(DataCollectTriggerStruct_DT dataCollectTriggerStructDt);
    void onDVRSystemStatusReportListener(DVRSystemStatus_DT dVRSystemStatusDt);
    void onOMCStatusReportACKListener(SetResult_DT statusReportACKDt);
    void onDVRSensorStatusReportListener(DVRSensorStatusStruct_DT dVRSensorStatusStructDt);
    void onEventOperationReportEventListener(EventOperationType_DT eventOperationTypeDt, EventType_DT eventTypeDt, AccessType_DT accessTypeDt);
    void onDVREventReportEventListener(std::string eventTime, EventType_DT eventTypeDt, AccessType_DT accessTypeDt, std::string filePath, std::string thumbnailPath);
    void onDVRTFStatusReportEventListener(TFCardOption_DT tFCardOptionDt, TFCardStatus_DT tFCardStatusDt, TFCardCapacity_DT tFCardCapacityDt);
    void onDVREMMCStatusReportEventListener(EMMCStatus_DT eMMCStatusDt, EMMCCapacityStruct_DT eMMCCapacityStructDt);
    void onExportOperationProgressReportEventListener(ExportFileInfoStruct_DT exportFileInfoStructDt, TotalTransProgress totalTransProgress);
    void onAsyncDeleteOperationProgressEventListener(DeleteProgress deleteProgress);
    /* Only for send callback to FWK. */

    GWM_DVR_SystemStatus mSystemStatusInfo;
    DVRSystemStatusCache mDVRSystemStatus;
    OMCStatusCache mOMCStatus;
    DVRSensorStatusCache mDVRSensorStatus;
    EventOperationReportCache mEventOperationReport;
    DVRTFStatusCache mDVRTFStatus;
    DVREMMCStatusCache mDVREMMCStatus;
    CameraFdb::DVRFdbDvrAndroidSetupSetQnxBroadcastResult mSetupParamResult;
    CameraFdb::DVRFdbDvrAndroidSetupGetReply mSetupGetResult;
    CameraFdb::DVRFdbQnxSystemInfro mDVRSystemInfo;
    GWM_DVRGetParam mGetParam;
    GWM_DVRSetParamReply mSetParamReply;
    GWM_DVRPreviewReply mPreviewReply;
    GWM_DVRVideoOperateEvent mVideoOperateEvent;
    GWM_FileOperateEvent mFileOperateEvent;
    GWM_DVRTFCardOperateEvent mTfCardOperateEvent;
    GWM_DVRReply mfactoryreset_result = GWM_DVRReply::GWM_DVR_REPLY_NULL;
    GWM_DVRRecordTimeInfo mRecordTimeInfo;
    GWM_DVRTFCardStatus mTfcardStatus;
    GWM_DVRCameraStatus mCameraStatus;
    GWM_DVRTFCardCapacityStatus mCapacityStatus;
    GWM_DVRTFCardCapacityCostStatus mCapacityCostStatus;
    GWM_DVRIPCStatus mIPCStatus = GWM_DVRIPCStatus::GWM_DVR_IPC_OFFLINE;
    GWM_DVRDeviceStatus mDeviceStatus;
    // add by dingyu
    GWM_DVRReply mUploadStatus = GWM_DVRReply::GWM_DVR_REPLY_NULL;
    GWM_DVRUploadFileStatus mFileStatus;
    GWM_DVRBroadcastActionsResult mActResult;
    GWM_DVRModulesEventResult mEventResult;
    mutable std::mutex mMutex;
    uint64_t mRecordStatus;

private:
    std::vector<android::sp<IDVRCallback>> mDVRCallbackList;
    std::vector<android::sp<IDVRCallback>>::iterator it;
    android::sp<CameraFdbClient> mCameraFdbClient;
    android::sp<CameraFdbServer> mCameraFdbServer;
    android::sp<DVRConnectionTimer> mConnTimer;
    android::sp<DVRMessageHandler> mMessageHandler;
    android::sp<DVRFdbProxy> mDVRFdbProxy;

    static void getDVRPssCFG();
    void sendMsgToQnxForOMSStream(GWM_DVRCameraId cameraId, GWM_DVRVideoOperateType operateType, GWM_DVR_VIDEO_TYPE videoType);
    bool replyDVRStatusReportACKFunc(SetResult_DT statusReportACKDt);
    GWM_Status queryTFCardInfo(TFCardStatus_DT &tfCardStatusOut, TFCardCapacity_DT &tfCardCapacityOut);
    GWM_Status queryTFCardExportCapacity(TotalExportCapacity &totalExportCapacity, FreeExportCapacity &freeExportCapacity, CallStatus_DT &callStatus);
    GWM_Status queryDVRSystemStatus(DVRSystemStatusOut &systemStatusOut, CallStatus_DT &dvrSystemcallStatus);
    GWM_Status queryDVRSensorStatus(DVRSensorStatusStruct_DT &sensorStatusOut, CallStatus_DT &dvrSensorcallStatus);
    bool checkCallbackIsNull(android::sp<IDVRCallback> callback);
};

// FIXME: most likely delete, this is only for passthrough implementations
// extern "C" IDVR* HIDL_FETCH_IDVR(const char* name);

}  // namespace implementation
}  // namespace V1_0
}  // namespace camera
}  // namespace hardware
}  // namespace gwm
}  // namespace vendor

#endif  // VENDOR_GWM_HARDWARE_CAMERA_V1_0_DVR_H
