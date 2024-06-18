/*************************************************************************
 * Copyright (C) 2020-2022 GWM Automotive Inc.
 *
 * The copyright notice above does not evidence any actual
 * or intended publication of such source code.
 * The code contains GWM Confidential Proprietary Information.
 *************************************************************************/
/**************************************************************************
 * @file CameraClient
 *
 *
 * @project     v3.5
 * @subsystem
 * @version     0.1
 * @author
 * @date        2020-12-2

 Module-History:
 Date(dd.mm.year)| Author            | Reason
 The latest entry at the head of the history list.
 2/12/2020         Hong Jiu Jin   Init version

***************************************************************************/
#include <sys/time.h>
#include <log/log.h>
#include <android/log.h>
#include <vendor/gwm/hardware/camera/1.0/ICamera.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

#undef LOG_TAG
#define LOG_TAG "CameraClient"

using namespace vendor::gwm::hardware::camera::V1_0;

using ::android::sp;
using ::android::hardware::hidl_array;
using ::android::hardware::hidl_memory;
using ::android::hardware::hidl_string;
using ::android::hardware::hidl_vec;
using ::android::hardware::Return;
using ::android::hardware::Void;

using namespace std;
using vendor::gwm::hardware::camera::V1_0::ICamera;
// using vendor::gwm::hardware::camera::V1_0::implementation::DVRCallback;

void usage()
{

    cout << "**************************************************************************************************" << endl;
    cout << "*   If you want to exit, please input: q or Q                                                    *" << endl;
    cout << "*   gwm_registerDVRCallback---Please input: registerDVRCallback                                  *" << endl;
    cout << "*   gwm_startPreview---Please input: startPreview                                                *" << endl;
    cout << "*   gwm_stopPreview---Please input: stopPreview                                                  *" << endl;
    cout << "*   gwm_userStartRecord---Please input: userStartRecord  params(cameraId, videoType)             *" << endl;
    cout << "*   gwm_userStopRecord---Please input: userStopRecord  params(cameraId, videoType)               *" << endl;
    cout << "*   gwm_startLapseVideo---Please input: startLapseVideo                                          *" << endl;
    cout << "*   gwm_stopLapseVideo---Please input: stopLapseVideo                                            *" << endl;
    cout << "*   gwm_formatTFCard---Please input: formatTFCard                                                *" << endl;
    cout << "*   gwm_querySystemStatus---Please input: querySystemStatus                                      *" << endl;
    cout << "*   gwm_setParam---Please input: setParam  params(params)                                        *" << endl;
    cout << "*   gwm_getParam---Please input: getParam                                                        *" << endl;
    cout << "*   gwm_resetFactory---Please input: resetFactory                                                *" << endl;
    cout << "*   gwm_operateFile---Please input: operateFile  params(operation)                               *" << endl;
    cout << "*   gwm_uploadRequset---Please input: uploadRequset                                              *" << endl;
    cout << "*   gwm_uploadResult---Please input: uploadResult                                                *" << endl;
    cout << "*   gwm_sendActCommd---Please input: sendActCommd  params(actCommand)                            *" << endl;
    cout << "*   gwm_sendModuleEvent---Please input: sendModuleEvent  params(moduleEvent)                     *" << endl;
    cout << "*   gwm_FileListRequest---Please input: fileListRequest  params(fileListREQ)                     *" << endl;
    cout << "*   gwm_deleteFileList---Please input: deleteFileList  params(filePath)                          *" << endl;
    cout << "*   gwm_AllFiledelete---Please input: allFiledelete  params(cameraId,fileType)                   *" << endl;
    cout << "*   gwm_AsyncAllFiledelete---Please input: asyncAllFiledelete                                    *" << endl;
    cout << "*   gwm_StopAsyncAllFiledelete---Please input: stopAsyncAllFiledelete                            *" << endl;
    cout << "*   gwm_ExportFileList---Please input: exportFileList  params(exportType,filePath)               *" << endl;
    cout << "*   gwm_AllFileExport---Please input: allFileExport  params(exportType,cameraId,fileType)        *" << endl;
    cout << "*   gwm_CancelFilesExport--Please input: cancelFilesExport  params(cameraId)                     *" << endl;
    cout << "*   gwm_SelectAllFileCapacity--Please input: selectAllFileCapacity  params(cameraId,fileType)    *" << endl;
    cout << "*   gwm_ExportFileCapacity--Please input: exportFileCapacity  params(filePath)                   *" << endl;
    cout << "*   gwm_EMMCStatusRequest--Please input: eMMCStatusRequest                                       *" << endl;
    cout << "*   gwm_TFCardStatusRequest--Please input: tFCardStatusRequest  params(tfcardId)                 *" << endl;
    cout << "*   gwm_TFCardCapacityRequest--Please input: tFCardCapacityRequest  params(tfcardId)             *" << endl;
    cout << "*   gwm_RecordStateRequest--Please input: recordStateRequest  params(tfcardId)                   *" << endl;
    cout << "*   gwm_OMCCaptureRequest--Please input: oMCCaptureRequest  params(tfcardId)                     *" << endl;
    cout << "*   gwm_OMCCaptureTransferRequest--Please input: oMCCaptureTransferRequest  params(tfcardId)     *" << endl;
    cout << "*   gwm_AsyncAllFiledelete--Please input: AsyncAllFiledelete                                     *" << endl;
    cout << "*   gwm_DVRFileCapacityInfoReq--Please input: DVRFileCapacityInfoReq                             *" << endl;
    cout << "*   gwm_FileListIncludeDateReq--Please input: FileListIncludeDateReq                             *" << endl;
    cout << "*   help---Please input: help                                                                    *" << endl;
    cout << "**************************************************************************************************" << endl;
}

struct DVRCameraCallback : public IDVRCallback
{
    Return<void> gwm_onDVRFileOperateNotify(
        const ::vendor::gwm::hardware::camera::V1_0::GWM_FileOperateEvent &
            event)
    {
        ALOGD("%s, operation_type = %hhu", __func__, event.operation_type);
        ALOGD("%s, cameraId = %hu", __func__, event.camera_id);
        ALOGD("%s, tfcard_id = %hhu", __func__, event.tfcard_id);
        ALOGD("%s, src_file_name = %s", __func__, event.src_file_name.c_str());
        ALOGD("%s, dst_file_name = %s", __func__, event.dst_file_name.c_str());
        return Void();
    }

    Return<void> gwm_onVideoOperateEventNotify(
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVRVideoOperateEvent &
            event)
    {
        ALOGD("%s, cmd_action = %hhu", __func__, event.cmd_action);
        ALOGD("%s, operation_type = %hhu", __func__, event.operation_type);
        ALOGD("%s, camera_id = %hu", __func__, event.camera_id);
        ALOGD("%s, tfcard_id = %hhu", __func__, event.tfcard_id);
        ALOGD("%s, video_type = %hhu", __func__, event.video_type);
        ALOGD("%s, reply_result = %hhu", __func__, event.reply_result);
        return Void();
    }

    Return<void> gwm_onDVRSystemStatusNotify(
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVR_SystemStatus &
            status)
    {
        ALOGD("%s", __func__);
        ALOGD("device_status = %hhu", status.device_status);
        ALOGD("front_sdcard_status = %hhu", status.front_sdcard_status);
        ALOGD("front_camera_status = %hhu", status.front_camera_status);
        ALOGD("avm_camera_status = %hhu", status.avm_camera_status);
        ALOGD("incar_sdcard_status = %hhu", status.incar_sdcard_status);
        ALOGD("incar_camera_status = %hhu", status.incar_camera_status);

        ALOGD("front tfcard_total_capacity = %f",
              status.front_infor.tfcard_total_capacity);
        ALOGD("front tfcard_loop_capacity = %f",
              status.front_infor.tfcard_loop_capacity);
        ALOGD("front tfcard_emergency_capacity = %f",
              status.front_infor.tfcard_emergency_capacity);
        ALOGD("front tfcard_normal_capacity = %f",
              status.front_infor.tfcard_normal_capacity);
        ALOGD("front tfcard_format_type = %hhu",
              status.front_infor.tfcard_format_type);
        ALOGD("front tfcard_loop_capacity_status = %hhu",
              status.front_infor.tfcard_loop_capacity_status);
        ALOGD("front tfcard_emergency_capacity_status= %hhu",
              status.front_infor.tfcard_emergency_capacity_status);
        ALOGD("front tfcard_normal_capacity_status= %hhu",
              status.front_infor.tfcard_normal_capacity_status);

        ALOGD("inner tfcard_total_capacity = %f",
              status.inner_infor.tfcard_total_capacity);
        ALOGD("inner tfcard_loop_capacity = %f",
              status.inner_infor.tfcard_loop_capacity);
        ALOGD("inner tfcard_emergency_capacity = %f",
              status.inner_infor.tfcard_emergency_capacity);
        ALOGD("inner tfcard_normal_capacity = %f",
              status.inner_infor.tfcard_normal_capacity);
        ALOGD("inner tfcard_format_type = %hhu",
              status.inner_infor.tfcard_format_type);
        ALOGD("inner tfcard_loop_capacity_status = %hhu",
              status.inner_infor.tfcard_loop_capacity_status);
        ALOGD("inner tfcard_emergency_capacity_status= %hhu",
              status.inner_infor.tfcard_emergency_capacity_status);
        ALOGD("inner tfcard_normal_capacity_status= %hhu",
              status.inner_infor.tfcard_normal_capacity_status);
        return Void();
    }

    Return<void> gwm_onDVRTFCardOperateNotify(
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVRTFCardOperateEvent &
            event)
    {
        ALOGD("%s", __func__);
        return Void();
    }

    Return<void> gwm_onGetParameterNotify(
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVRGetParam &params)
    {
        ALOGD("%s, sounds_enable_status = %hhu", __func__,
              params.sounds_enable_status);
        ALOGD("%s, wide_dynamic_enable_status = %hhu", __func__,
              params.wide_dynamic_enable_status);
        ALOGD("%s, automatical_overwrite__enable_status = %hhu", __func__,
              params.automatical_overwrite__enable_status);
        ALOGD("%s, dvr_enable_status = %hhu", __func__, params.dvr_enable_status);
        ALOGD("%s, paking_monitoring_enable_status = %hhu", __func__,
              params.paking_monitoring_enable_status);
        ALOGD("%s, avm_enable_status = %hhu", __func__, params.avm_enable_status);
        ALOGD("%s, delay_shutdown = %u", __func__, params.delay_shutdown);
        ALOGD("%s, record_time = %u", __func__, params.record_time);
        return Void();
    }

    Return<void> gwm_onSetParameterNotify(
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVRSetParamReply &
            set_params_reply)
    {
        ALOGD("%s", __func__);
        return Void();
    }

    Return<void> gwm_onDVRPreviewNotify(
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVRPreviewReply &
            preview_reply)
    {
        ALOGD("%s", __func__);
        return Void();
    }

    Return<void> gwm_onDVRRecordTimeNotify(
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVRRecordTimeInfo &
            time_info)
    {
        // TODO implement
        ALOGD("%s, report_bit_flag = %lu", __func__, time_info.report_bit_flag);
        ALOGD("%s, front_long_recorded_time = %lu", __func__,
              time_info.front_long_recorded_time);
        ALOGD("%s, front_short_recorded_time = %lu", __func__,
              time_info.front_short_recorded_time);
        ALOGD("%s, front_time_lapse_recorded_time = %lu", __func__,
              time_info.front_time_lapse_recorded_time);
        return Void();
    }

    Return<void> gwm_onDVRResetFactoryNotify(
        ::vendor::gwm::hardware::camera::V1_0::GWM_DVRReply reply_result)
    {
        // TODO implement
        ALOGD("%s", __func__);
        return Void();
    }

    Return<void> gwm_onDVRRecordStatusNotify(uint64_t record_status)
    {
        // TODO implement
        ALOGD("%s, record_status = %lu", __func__, record_status);
        return Void();
    }

    Return<void> gwm_onDVRCameraStatusNotify(
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVRCameraStatus &
            camera_status)
    {
        // TODO implement
        ALOGD("%s", __func__);
        return Void();
    }

    Return<void> gwm_onDVRTFCardStatusNotify(
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVRTFCardStatus &
            tfcard_status)
    {
        // TODO implement
        ALOGD("%s", __func__);
        return Void();
    }

    Return<void> gwm_onDVRTFCardCapacityNotify(
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVRTFCardCapacityStatus &
            capacity_status)
    {
        // TODO implement
        ALOGD("%s", __func__);
        return Void();
    }

    Return<void> gwm_onDVRTFCardCapacityCostNotify(
        const ::vendor::gwm::hardware::camera::V1_0::
            GWM_DVRTFCardCapacityCostStatus &capacity_cost_status)
    {
        // TODO implement
        ALOGD("%s", __func__);
        return Void();
    }
    Return<void> gwm_onDVRUploadFileStatusNotify(
        const ::vendor::gwm::hardware::camera::V1_0::
            GWM_DVRUploadFileStatus &file_status)
    {
        // TODO implement
        ALOGD("%s", __func__);
        return Void();
    }
    Return<void> gwm_onDVRIPCStatusNotify(
        ::vendor::gwm::hardware::camera::V1_0::GWM_DVRIPCStatus ipc_status)
    {
        // TODO implement
        ALOGD("%s ipc_status value = %hhu", __func__, ipc_status);
        return Void();
    }
    Return<void> gwm_onDVRDeviceStatusNotify(
        ::vendor::gwm::hardware::camera::V1_0::GWM_DVRDeviceStatus device_status)
    {
        // TODO implement
        ALOGD("%s device_status value = %hhu", __func__, device_status);
        return Void();
    }
    Return<void> gwm_onDVRReqUploadStatusNotify(
        ::vendor::gwm::hardware::camera::V1_0::GWM_DVRReply req_status)
    {
        // TODO implement
        ALOGD("%s  value = %d", __func__, (int)req_status);
        return Void();
    }
    Return<void> gwm_onDVRBroadcastActionsStatusNotify(
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVRBroadcastActionsResult &act_status)
    {
        // TODO implement
        ALOGD("%s  value ", __func__);
        return Void();
    }
    Return<void> gwm_onDVRBroadcastEventsNotify(
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVRModulesEventResult &act_status)
    {
        // TODO implement
        ALOGD("%s  value", __func__);
        return Void();
    }
    // add for outside DVR
    Return<void> gwm_onDVRStatusNotify(
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVRDeviceStatus dvr_status)
    {
        // TODO implement
        ALOGD("%s  value = %hhu", __func__, dvr_status);
        return Void();
    }

    Return<void> gwm_onDVREventReportNotify(
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVREventReport &dvr_event_status)
    {
        // TODO implement
        ALOGD("%s", __func__);
        return Void();
    }
    Return<void> gwm_onDVREventOperationNotify(
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVROperationReport &dvr_operation_status)
    {
        // TODO implement
        ALOGD("%s", __func__);
        return Void();
    }
    Return<void> gwm_onDVRQueryFileListNotify(
        const ::android::hardware::hidl_vec<GWM_DVRFileListResult> &quest_result)
    {
        // TODO implement
        ALOGD("%s", __func__);
        return Void();
    }
    Return<void> gwm_onDVRFileStatusNotify(
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVRFileOperateResult event_result)
    {
        // TODO implement
        ALOGD("%s  value = %hhu", __func__, event_result);
        return Void();
    }
    Return<void> gwm_onDVRFileExportProcessNotify(uint32_t export_status)
    {
        // TODO implement
        ALOGD("%s  value = %d", __func__, (int)export_status);
        return Void();
    }
    Return<void> gwm_onDVRFileExportStatusNotify(
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVRFileExportStatus export_status)
    {
        // TODO implement
        ALOGD("%s  value = %hhu", __func__, export_status);
        return Void();
    }
    Return<void> gwm_onDVRCancelFileExportStatusNotify(
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVRFileOperateResult export_status)
    {
        // TODO implement
        ALOGD("%s  value = %hhu", __func__, export_status);
        return Void();
    }
    Return<void> gwm_onDVREMMCStatusNotify(
        const ::vendor::gwm::hardware::camera::V1_0::GWM_DVREMMCReport &emmc_status)
    {
        // TODO implement
        ALOGD("%s", __func__);
        return Void();
    }

    Return<void> gwm_onDVRRecordStateNotify(const ::vendor::gwm::hardware::camera::V1_0::GWM_DVRCameraId camera_id,
                                            const ::vendor::gwm::hardware::camera::V1_0::GWM_DVRRecordStatus status,
                                            const ::vendor::gwm::hardware::camera::V1_0::GWM_DVREventType type)
    {
        ALOGD("%s", __func__);
        return Void();
    }

    Return<void> gwm_onExportFileCapacityNotify(int32_t capacity, const hidl_vec<hidl_string>& file_path_url)
    {
        ALOGD("%s", __func__);
        return Void();
    }

    Return<void> gwm_onAllFileCapacityNotify(int32_t capacity,
                                            const ::vendor::gwm::hardware::camera::V1_0::GWM_DVRCameraId camera_id,
                                            const ::vendor::gwm::hardware::camera::V1_0::GWM_DVRFileType file_type)
    {
        ALOGD("%s", __func__);
        return Void();
    }

    Return<void> gwm_onOMCCaptureStatusNotify(const ::vendor::gwm::hardware::camera::V1_0::GWM_DVROMCCaptureStatus status,
                                            const hidl_string& eventTime,
                                            const ::vendor::gwm::hardware::camera::V1_0::GWM_DVREventType eventType,
                                            uint32_t fileId, uint32_t fileSize)
    {
        ALOGD("%s", __func__);
        return Void();
    }

    Return<void> gwm_onOMCCaptureTransferStatusNotify(const ::vendor::gwm::hardware::camera::V1_0::GWM_DVROMCCaptureStatus status,
                                                    const hidl_string& eventTime,
                                                    const ::vendor::gwm::hardware::camera::V1_0::GWM_DVREventType eventType,
                                                    uint32_t fileId, uint32_t fileSize, const hidl_string& filePath)
    {
        ALOGD("%s", __func__);
        return Void();
    }


    Return<void> gwm_onAsyncDeleteOperationProgressNotify(uint32_t delete_progress)
    {
        ALOGD("%s", __func__);
        return Void();
    }

    Return<void> gwm_onDVRStopAsyncAllFileDeleteStatusNotify(const ::vendor::gwm::hardware::camera::V1_0::GWM_DVRFileOperateResult export_status)
    {
        ALOGD("%s", __func__);
        return Void();
    }

    /**
     * File capacity info reporting interface
     */
    Return<void> gwm_onDVRFileCapacityInfoNotify(const ::android::hardware::hidl_vec<::vendor::gwm::hardware::camera::V1_0::GWM_DVRFileCapacity> &capacity_list)
    {
        ALOGD("%s: size:%lu", __func__, capacity_list.size());
        return Void();
    }

    /**
     * File list include date reporting interface
     */
    Return<void> gwm_onFileListIncludeDateNotify(const ::android::hardware::hidl_vec<::vendor::gwm::hardware::camera::V1_0::GWM_FileListIncludeDate> &file_list)
    {
        ALOGD("%s: size:%lu", __func__, file_list.size());
        return Void();
    }
};

int main(int /*argc*/, char * /*argv*/[])
{
    GWM_Status status = GWM_Status::GWM_ERROR;
    sp<DVRCameraCallback> mDVRCallback;

    sp<ICamera> CameraClient = ICamera::getService();

    sp<::vendor::gwm::hardware::camera::V1_0::IDVR> mDVRInterface =
        CameraClient->gwm_getDVRInterface();
    if (nullptr == CameraClient.get())
    {
        cout << "getService return NULL " << endl;
        return -1;
    }

    usage();

    std::string s = "";
    cout<<" >";
    std::cin >> s;
    while (s.compare("q") != 0)
    {
        if (s.compare("help") == 0)
        {
            usage();
        }
        else if (s.compare("resetFactory") == 0)
        {
            status = mDVRInterface->gwm_resetFactory();

            std::cout << "gwm_resetFactory status: " << static_cast<int>(status) << endl;
        }
        else if (s.compare("startPreview") == 0)
        {

            cout << "gwm_startPreview enter" << endl;
            GWM_DVRCameraId camera_id = GWM_DVRCameraId::GWM_DVR_CAMERA_ID_FRONT;
            status = mDVRInterface->gwm_startPreview(camera_id);
            std::cout << "gwm_startPreview status: " << static_cast<int>(status) << endl;
        }
        else if (s.compare("stopPreview") == 0)
        {

            GWM_DVRCameraId camera_id = GWM_DVRCameraId::GWM_DVR_CAMERA_ID_FRONT;
            status = mDVRInterface->gwm_stopPreview(camera_id);
            std::cout << "gwm_stopPreview status: " << static_cast<int>(status) << endl;
        }
        else if (s.compare("formatTFCard") == 0)
        {

            GWM_DVR_TFCardId tfCardId = GWM_DVR_TFCardId::GWM_DVR_TFCARD_FRONT;
            status = mDVRInterface->gwm_formatTFCard(tfCardId);
            std::cout << "gwm_formatTFCard status: " << static_cast<int>(status) << endl;
        }
        else if (s.compare("userStartRecord") == 0)
        {
            cout << "  Please input operation:(2:longVideo, 3:shortVideo, 5:capture)" << endl;
            cout << "  > ";
            cin >> s;
            uint8_t opt = stoi(s);
            cout << "select num: " << static_cast<int>(opt) << endl;
            GWM_DVRCameraId camera_id = GWM_DVRCameraId::GWM_DVR_CAMERA_ID_FRONT;
            GWM_DVR_VIDEO_TYPE loop_video_type = GWM_DVR_VIDEO_TYPE(opt);
            status = mDVRInterface->gwm_userStartRecord(camera_id, loop_video_type);
            std::cout << "gwm_userStartRecord status: " << static_cast<int>(status) << endl;
        }
        else if (s.compare("userStopRecord") == 0)
        {
            cout << "  Please input operation:(2:longVideo, 3:shortVideo, 5:capture)" << endl;
            cout << "  > ";
            cin >> s;
            uint8_t opt = stoi(s);
            cout << "select num: " << static_cast<int>(opt) << endl;
            GWM_DVRCameraId camera_id = GWM_DVRCameraId::GWM_DVR_CAMERA_ID_FRONT;
            GWM_DVR_VIDEO_TYPE loop_video_type = GWM_DVR_VIDEO_TYPE(opt);
            status = mDVRInterface->gwm_userStopRecord(camera_id, loop_video_type);
            std::cout << "gwm_userStopRecord status: " << static_cast<int>(status) << endl;
        }
        else if (s.compare("startLapseVideo") == 0)
        {

            GWM_DVRCameraId camera_id = GWM_DVRCameraId::GWM_DVR_CAMERA_ID_FRONT;
            int64_t timeLapseVideoInteval = 0;
            int16_t totalFrameNumber = 0;
            int16_t playFrameNumber = 0;
            status = mDVRInterface->gwm_startLapseVideo(camera_id, timeLapseVideoInteval, totalFrameNumber, playFrameNumber);
            std::cout << "startLapseVideo status: " << static_cast<int>(status) << endl;
        }
        else if (s.compare("stopLapseVideo") == 0)
        {

            GWM_DVRCameraId camera_id = GWM_DVRCameraId::GWM_DVR_CAMERA_ID_FRONT;
            status = mDVRInterface->gwm_stopLapseVideo(camera_id);
            std::cout << "startLapseVideo status: " << static_cast<int>(status) << endl;
        }
        else if (s.compare("setParam") == 0)
        {

            cout << "  Please input operation:(1:wind_dynamic, 2:delay_shutdown, 3:parking monitoring)" << endl;
            cout << "  > ";
            cin >> s;
            uint8_t opt = stoi(s);
            cout << "select num: " << static_cast<int>(opt) << endl;
            if (opt == 1)
            {
                GWM_DVRSetParam params;
                memset(&params, 0, sizeof(params));
                params.setup_bit_flag = 2;
                params.wide_dynamic_enable_req = GWM_DVRRequest::GWM_DVR_ENABLE_REQUEST;
                params.camera_id = GWM_DVRCameraId::GWM_DVR_CAMERA_ID_FRONT;
                status = mDVRInterface->gwm_setParam(params);
                std::cout << "wind_dynamic status: " << static_cast<int>(status) << endl;
            }
            else if (opt == 2)
            {

                GWM_DVRSetParam params;
                memset(&params, 0, sizeof(params));
                params.setup_bit_flag = 8;
                params.delay_shutdown_req = 60;
                params.camera_id = GWM_DVRCameraId::GWM_DVR_CAMERA_ID_FRONT;
                status = mDVRInterface->gwm_setParam(params);
                std::cout << "gwm_setParam delayed shutdown status: " << static_cast<int>(status) << endl;
            }
            else if (opt == 3)
            {

                GWM_DVRSetParam params;
                memset(&params, 0, sizeof(params));
                params.setup_bit_flag = 64;
                params.paking_monitoring_enable_req = GWM_DVRRequest::GWM_DVR_ENABLE_REQUEST;
                params.camera_id = GWM_DVRCameraId::GWM_DVR_CAMERA_ID_FRONT;
                status = mDVRInterface->gwm_setParam(params);
                std::cout << "gwm_setParam parking_monitoring status: " << static_cast<int>(status) << endl;
            }
        }
        else if (s.compare("fileListRequest") == 0)
        {

            GWM_DVRFileListREQ list;
            list.operation_type = GWM_DVRFileType::GWM_DVRFileNormalVideo;
            list.camera_id = GWM_DVRCameraId::GWM_DVR_CAMERA_ID_FRONT;
            list.file_sum = 30;
            list.last_file_name = "0";
            status = mDVRInterface->gwm_FileListRequest(list);
        }
        else if (s.compare("deleteFileList") == 0)
        {

            // hidl_vec<hidl_string> data(4);
            // data[0] = "http://172.16.12.91/file/medium?filepath=/tmp/mmc11/DCIM/ch1_20220711_124341_0569_0_00.mp4";
            // data[1] = "http://172.16.12.91/file/medium?filepath=/tmp/mmc11/DCIM/ch1_20220711_124041_0568_0_00.mp4";
            // data[2] = "http://172.16.12.91/file/medium?filepath=/tmp/mmc11/DCIM/ch1_20220711_123742_0567_0_00.mp4";
            // data[3] = "http://172.16.12.91/file/medium?filepath=/tmp/mmc11/DCIM/ch1_20220711_123442_0566_0_00.mp4";

            // status = mDVRInterface->gwm_deleteFileList(data);
            // std::cout << "deleteFileList status: " << static_cast<int>(status) << endl;
            cout<<"code has //"<<endl;
        }
        else if (s.compare("tFCardStatusRequest") == 0)
        {
            GWM_DVR_TFCardId tfcardId = GWM_DVR_TFCardId::GWM_DVR_TFCARD_FRONT;
            status = mDVRInterface->gwm_TFCardStatusRequest(tfcardId);
            cout << "tFCardStatusRequest status: " << static_cast<int>(status) << endl;
        }
        else if (s.compare("tFCardCapacityRequest") == 0)
        {
            GWM_DVR_TFCardId tfcardId = GWM_DVR_TFCardId::GWM_DVR_TFCARD_FRONT;
            status = mDVRInterface->gwm_TFCardCapacityRequest(tfcardId);
            cout << "tFCardCapacityRequest status: " << static_cast<int>(status) << endl;
        }
        else if (s.compare("recordStateRequest") == 0)
        {
            GWM_DVRCameraId camera_id = GWM_DVRCameraId::GWM_DVR_CAMERA_ID_FRONT;
            status = mDVRInterface->gwm_RecordStateRequest(camera_id);
            cout << "recordStateRequest status: " << static_cast<int>(status) << endl;
        }
        else if (s.compare("oMCCaptureRequest") == 0)
        {
            const hidl_string &eventTime = "2022-07-13 17:58:00";
            GWM_DVREventType type = GWM_DVREventType::GWM_ManualCapture_ByButton;
            uint32_t fileId = 0;
            uint32_t fileSize = 5;
            status = mDVRInterface->gwm_OMCCaptureRequest(eventTime, type, fileId, fileSize);
            cout << "oMCCaptureRequest status: " << static_cast<int>(status) << endl;
        }
        else if (s.compare("oMCCaptureTransferRequest") == 0)
        {
            const hidl_string &eventTime = "2022-07-13 17:58:00";
            GWM_DVREventType type = GWM_DVREventType::GWM_ManualCapture_ByButton;
            uint32_t fileId = 0;
            uint32_t fileSize = 5;
            status = mDVRInterface->gwm_OMCCaptureTransferRequest(
                eventTime, type, fileId, fileSize,
                "http://172.16.12.91/file/medium?filepath=/tmp/mmc11/DCIM/ch1_20220630_191712_0488_0_00.mp4");
            cout << "gwm_OMCCaptureTransferRequest status: " << static_cast<int>(status) << endl;

        }
        else if (s.compare("exportFileCapacity") == 0)
        {
            cout << "code has //" << endl;
            // hidl_vec<hidl_string> data(4);
            // data[0] = "http://172.16.12.91/file/medium?filepath=/tmp/mmc11/DCIM/ch1_20220630_193813_0498_0_00.mp4";
            // data[1] = "http://172.16.12.91/file/medium?filepath=/tmp/mmc11/DCIM/ch1_20220630_193602_0497_0_00.mp4";
            // data[2] = "http://172.16.12.91/file/medium?filepath=/tmp/mmc11/DCIM/ch1_20220630_193302_0496_0_00.mp4";
            // data[3] = "http://172.16.12.91/file/medium?filepath=/tmp/mmc11/DCIM/ch1_20220630_191712_0488_0_00.mp4";
            // std::cout << "DVR Init success " << endl;
            // int32_t result = mDVRInterface->gwm_ExportFileCapacity(data);
            // ALOGI("gwm_ExportFileCapacity:  %d", result);
            // std::cout << "gwm_ExportFileCapacity: " << result << endl;
        }
        else if (s.compare("asyncAllFiledelete") == 0)
        {
            status = mDVRInterface->gwm_AsyncAllFiledelete(
                GWM_DVRCameraId::GWM_DVR_CAMERA_ID_FRONT,GWM_DVRFileType::GWM_DVRFileUserData);
            mDVRInterface->gwm_StopAsyncAllFiledelete(GWM_DVRCameraId::GWM_DVR_CAMERA_ID_FRONT);
            cout << "gwm_AsyncAllFiledelete status: " << static_cast<int>(status) << endl;
        }
        else if (s.compare("DVRFileCapacityInfoReq") == 0)
        {
            hidl_vec<GWM_ParamFileType> data(1);
            data[0] = GWM_ParamFileType::GWM_CustomData;
            status = mDVRInterface->gwm_DVRFileCapacityInfoReq(GWM_TFAllFileCapacity::GWM_Get_Array_Capacity, data);
            cout << "gwm_DVRFileCapacityInfoReq status: " << static_cast<int>(status) << endl;
        }
        else if (s.compare("FileListIncludeDateReq") == 0)
        {
            GWM_DVRFileIncludeDateREQ fileReq;
            memset(&fileReq, 0, sizeof(fileReq));
            // status = mDVRInterface->gwm_FileListIncludeDateReq(fileReq);
            cout << "gwm_FileListIncludeDateReq status: " << static_cast<int>(status) << endl;
        }
        else if (s.compare("DVR") == 0)
        {

            // GWM_DVRCameraId camera_id = GWM_DVRCameraId::GWM_DVR_CAMERA_ID_FRONT;

            // mDVRCallback = new DVRCameraCallback();
            // status = mDVRInterface->gwm_registerDVRCallback(mDVRCallback);
            // ALOGD("%s register dvrcallback status = %d", __FUNCTION__,
            //       (int8_t)status);

            // status = GWM_Status::GWM_ERROR;
            // status = mDVRInterface->gwm_querySystemStatus();
            // ALOGD("%s send gwm_querySystemStatus request, request status = %d",
            //       __FUNCTION__, status);

            // status = mDVRInterface->gwm_startPreview(camera_id);
            // ALOGD("%s preview status = %d", __FUNCTION__, (int8_t)status);
            // status = mDVRInterface->gwm_stopPreview(camera_id);
            // ALOGD("%s stop preview status = %d", __FUNCTION__, (int8_t)status);

            // status = mDVRInterface->gwm_startCapture(
            //     camera_id, GWM_DVR_VIDEO_TYPE::GWM_DVR_CAPTURE);
            // ALOGD("%s start capture status = %d", __FUNCTION__, (int8_t)status);
            // sleep(1);
            // status = mDVRInterface->gwm_userStartRecord(
            //     camera_id, GWM_DVR_VIDEO_TYPE::GWM_DVR_VIDEO_TYPE_LONG);
            // ALOGD("%s gwm_userStartRecord status = %d", __FUNCTION__, (int8_t)status);
            // sleep(5);
            // status = mDVRInterface->gwm_userStopRecord(
            //     camera_id, GWM_DVR_VIDEO_TYPE::GWM_DVR_VIDEO_TYPE_LONG);
            // ALOGD("%s gmw_userStartRecord status = %d", __FUNCTION__, (int8_t)status);

            // status = mDVRInterface->gwm_startLapseVideo(camera_id, 0, 0, 0);
            // ALOGD("%s gwm_startLapseVideo status = %d", __FUNCTION__, (int8_t)status);
            // status = mDVRInterface->gwm_stopLapseVideo(camera_id);
            // ALOGD("%s gwm_stopLapseVideo status = %d", __FUNCTION__, (int8_t)status);

            // status = mDVRInterface->gwm_getParam();
            // ALOGD("%s get param status = %d", __FUNCTION__, (int8_t)status);
            // sleep(1);
            // GWM_DVRSetParam params;
            // memset(&params, 0, sizeof(params));
            // params.setup_bit_flag = 1;
            // params.sounds_enable_req = GWM_DVRRequest::GWM_DVR_ENABLE_REQUEST;
            // params.camera_id = GWM_DVRCameraId::GWM_DVR_CAMERA_ID_FRONT;

            // status = mDVRInterface->gwm_setParam(params);
            // ALOGD("%s set param status = %d", __FUNCTION__, (int8_t)status);
            // sleep(1);

            // status = mDVRInterface->gwm_resetFactory();
            // ALOGD("%s first gwm_resetFactory status = %d", __FUNCTION__,
            //       (int8_t)status);
            // sleep(1);

            // status = mDVRInterface->gwm_formatTFCard(
            //     GWM_DVR_TFCardId::GWM_DVR_TFCARD_FRONT);
            // ALOGD("%s gwm_formatTFCard status = %d", __FUNCTION__, (int8_t)status);
            // sleep(1);

            // GWM_DVR_FileOperateAction operation;
            // operation.operation_type = GWM_DVR_FileOperateType::GWM_DVR_FILE_DELETE;
            // operation.camera_id = GWM_DVRCameraId::GWM_DVR_CAMERA_ID_FRONT;
            // operation.tfcard_id = GWM_DVR_TFCardId::GWM_DVR_TFCARD_FRONT;
            // operation.src_file_name = "/src/";
            // operation.dst_file_name = "/dst/";

            // status = mDVRInterface->gwm_operateFile(operation);
            // ALOGD("%s gwm_operateFile status = %d", __FUNCTION__, (int8_t)status);

            // status = mDVRInterface->gwm_uploadRequset();
            // ALOGD("%s gwm_uploadRequset status = %d", __FUNCTION__, (int8_t)status);

            // status = mDVRInterface->gwm_uploadResult();
            // ALOGD("%s gwm_uploadRequset status = %d", __FUNCTION__, (int8_t)status);

            GWM_DVR_TFCardId tfcardId = GWM_DVR_TFCardId::GWM_DVR_TFCARD_FRONT;
            status = mDVRInterface->gwm_TFCardStatusRequest(tfcardId);
            ALOGD("%s gwm_TFCardStatusRequest status = %d", __FUNCTION__, (int8_t)status);

            sleep(1);
        }
        std::cin >> s;
    }
    return 0;
}
