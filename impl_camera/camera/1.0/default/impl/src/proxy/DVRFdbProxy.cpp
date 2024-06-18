/*************************************************************************
 * Copyright (C) 2023 GWM Automotive Inc.
 *
 * The copyright notice above does not evidence any actual
 * or intended publication of such source code.
 * The code contains GWM Confidential Proprietary Information.
 *************************************************************************/
/**************************************************************************
 * @file DVRFdbProxy.h
 * DVRFdbProxy
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
#include <android/log.h>
#include <log/log.h>
#include <impl/src/proto/common.base.CameraIviQnx.pb.h>
#include "DVRFdbProxy.h"

#undef LOG_TAG
#define LOG_TAG "CameraHAL_DVRFdbProxy"

namespace vendor {
namespace gwm {
namespace hardware {
namespace camera {
namespace V1_0 {
namespace implementation {

using namespace CameraFdb;
using namespace DVRFdb;
using namespace vendor::gwm::hardware::camera::V1_0;

using ::android::sp;

DVRFdbProxy::DVRFdbProxy(sp<CameraFdbClient> fdbClient, sp<CameraFdbServer> fdbServer)
    : mCameraFdbClient(fdbClient), mCameraFdbServer(fdbServer)
{
    ALOGI("%s:  DVRFdbProxy build.", __FUNCTION__);
}

DVRFdbProxy::~DVRFdbProxy()
{
}

GWM_Status DVRFdbProxy::startPreview(GWM_DVRCameraId cameraId)
{
    if(mCameraFdbClient == nullptr)
    {
        ALOGE("%s:  mCameraFdbClient == nullptr!", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    CameraFdb::DVRFdbDvrAndroidOperatePreview previewCmd;
    previewCmd.set_operation_type(
        CameraFdb::DVRPreviewOperateType::DVR_PREVIEW_OPERATE_START);
    previewCmd.set_drv_id(static_cast<CameraFdb::DVRCameraID>(cameraId));
    // build dvr message
    CFdbProtoMsgBuilder builder(previewCmd);
    return mCameraFdbClient->sendMessage(
        CameraFdb::FdbCameraManagerMsgId::DVR_FDB_ANDROID_OPERATE_PREVIEW,
        builder, true);
}

GWM_Status DVRFdbProxy::stopPreview(GWM_DVRCameraId cameraId)
{
    if(mCameraFdbClient == nullptr)
    {
        ALOGE("%s:  mCameraFdbClient == nullptr!", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    CameraFdb::DVRFdbDvrAndroidOperatePreview previewCmd;
    previewCmd.set_operation_type(
        CameraFdb::DVRPreviewOperateType::DVR_PREVIEW_OPERATE_STOP);
    previewCmd.set_drv_id(static_cast<CameraFdb::DVRCameraID>(cameraId));
    // build drv message
    CFdbProtoMsgBuilder builder(previewCmd);
    return mCameraFdbClient->sendMessage(
        CameraFdb::FdbCameraManagerMsgId::DVR_FDB_ANDROID_OPERATE_PREVIEW,
        builder, true);
}

GWM_Status DVRFdbProxy::startRecord(GWM_DVRCameraId cameraId, GWM_DVR_VIDEO_TYPE type)
{
    if(mCameraFdbClient == nullptr)
    {
        ALOGE("%s:  mCameraFdbClient == nullptr!", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    CameraFdb::DVRFdbDvrAndroidOperateRecord videoCmd;
    videoCmd.set_operation_type(
        CameraFdb::DVRRecordOperateType::DVR_RECORD_OPERATE_START);
    videoCmd.set_drv_id(static_cast<CameraFdb::DVRCameraID>(cameraId));
    if (cameraId == GWM_DVRCameraId::GWM_DVR_CAMERA_ID_FRONT)
    {
        videoCmd.set_sdcard_id(CameraFdb::DVRSDCardID::DVR_SDCARD_ID_FRONT);
    }
    else if (cameraId == GWM_DVRCameraId::GWM_DVR_CAMERA_ID_INCAR)
    {
        videoCmd.set_sdcard_id(CameraFdb::DVRSDCardID::DVR_SDCARD_ID_INCAR);
    }
    else if (cameraId == GWM_DVRCameraId::GWM_DVR_CAMERA_ID_AVM)
    {
        /* AVM use incar sdcard to record in QNX */
        videoCmd.set_sdcard_id(CameraFdb::DVRSDCardID::DVR_SDCARD_ID_INCAR);
    }
    else if (cameraId == GWM_DVRCameraId::GWM_DVR_CAMERA_ID_FRONT_AND_AVM)
    {
        videoCmd.set_sdcard_id(CameraFdb::DVRSDCardID::DVR_SDCARD_ID_ALL);
    }
    videoCmd.set_video_type(static_cast<CameraFdb::DVRVideoType>(type));
    // build drv message
    CFdbProtoMsgBuilder builder(videoCmd);
    return mCameraFdbClient->sendMessage(
        CameraFdb::FdbCameraManagerMsgId::DVR_FDB_ANDROID_OPERATE_RECORD,
        builder, true);
}

GWM_Status DVRFdbProxy::stopRecord(GWM_DVRCameraId cameraId, GWM_DVR_VIDEO_TYPE type)
{
    if(mCameraFdbClient == nullptr)
    {
        ALOGE("%s:  mCameraFdbClient == nullptr!", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    CameraFdb::DVRFdbDvrAndroidOperateRecord videoCmd;
    videoCmd.set_operation_type(
        CameraFdb::DVRRecordOperateType::DVR_RECORD_OPERATE_STOP);
    videoCmd.set_drv_id(static_cast<CameraFdb::DVRCameraID>(cameraId));
    if (cameraId == GWM_DVRCameraId::GWM_DVR_CAMERA_ID_FRONT)
    {
        videoCmd.set_sdcard_id(CameraFdb::DVRSDCardID::DVR_SDCARD_ID_FRONT);
    }
    else if (cameraId == GWM_DVRCameraId::GWM_DVR_CAMERA_ID_INCAR)
    {
        videoCmd.set_sdcard_id(CameraFdb::DVRSDCardID::DVR_SDCARD_ID_INCAR);
    }
    else if (cameraId == GWM_DVRCameraId::GWM_DVR_CAMERA_ID_AVM)
    {
        videoCmd.set_sdcard_id(CameraFdb::DVRSDCardID::DVR_SDCARD_ID_INCAR);
    }
    else if (cameraId == GWM_DVRCameraId::GWM_DVR_CAMERA_ID_FRONT_AND_AVM)
    {
        videoCmd.set_sdcard_id(CameraFdb::DVRSDCardID::DVR_SDCARD_ID_ALL);
    }
    videoCmd.set_video_type(static_cast<CameraFdb::DVRVideoType>(type));
    // build drv message
    CFdbProtoMsgBuilder builder(videoCmd);
    return mCameraFdbClient->sendMessage(
        CameraFdb::FdbCameraManagerMsgId::DVR_FDB_ANDROID_OPERATE_RECORD,
        builder, true);
}

GWM_Status DVRFdbProxy::startCapture(GWM_DVRCameraId cameraId, GWM_DVR_VIDEO_TYPE type)
{
    if(mCameraFdbClient == nullptr)
    {
        ALOGE("%s:  mCameraFdbClient == nullptr!", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    CameraFdb::DVRFdbDvrAndroidOperateRecord captureCmd;
    captureCmd.set_operation_type(
        CameraFdb::DVRRecordOperateType::DVR_RECORD_OPERATE_START);
    captureCmd.set_drv_id(static_cast<CameraFdb::DVRCameraID>(cameraId));
    if (cameraId == GWM_DVRCameraId::GWM_DVR_CAMERA_ID_FRONT)
    {
        captureCmd.set_sdcard_id(CameraFdb::DVRSDCardID::DVR_SDCARD_ID_FRONT);
    }
    else if (cameraId == GWM_DVRCameraId::GWM_DVR_CAMERA_ID_INCAR)
    {
        captureCmd.set_sdcard_id(CameraFdb::DVRSDCardID::DVR_SDCARD_ID_INCAR);
    }
    else if (cameraId == GWM_DVRCameraId::GWM_DVR_CAMERA_ID_AVM)
    {
        captureCmd.set_sdcard_id(CameraFdb::DVRSDCardID::DVR_SDCARD_ID_INCAR);
    }
    else if (cameraId == GWM_DVRCameraId::GWM_DVR_CAMERA_ID_FRONT_AND_AVM)
    {
        captureCmd.set_sdcard_id(CameraFdb::DVRSDCardID::DVR_SDCARD_ID_ALL);
    }
    captureCmd.set_video_type(static_cast<CameraFdb::DVRVideoType>(type));
    // build drv message
    CFdbProtoMsgBuilder builder(captureCmd);
    return mCameraFdbClient->sendMessage(
        CameraFdb::FdbCameraManagerMsgId::DVR_FDB_ANDROID_OPERATE_RECORD,
        builder, true);
}

GWM_Status DVRFdbProxy::startLapseVideo(GWM_DVRCameraId cameraId,
                            int64_t timeLapseVideoInteval,
                            int16_t totalFrameNumber,
                            int16_t playFrameNumber)
{
    if(mCameraFdbClient == nullptr)
    {
        ALOGE("%s:  mCameraFdbClient == nullptr!", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    CameraFdb::DVRFdbDvrAndroidOperateRecord videoLapseCmd;
    videoLapseCmd.set_operation_type(
        CameraFdb::DVRRecordOperateType::DVR_RECORD_OPERATE_START);
    videoLapseCmd.set_drv_id(static_cast<CameraFdb::DVRCameraID>(cameraId));
    if (cameraId == GWM_DVRCameraId::GWM_DVR_CAMERA_ID_FRONT)
    {
        videoLapseCmd.set_sdcard_id(CameraFdb::DVRSDCardID::DVR_SDCARD_ID_FRONT);
    }
    else if (cameraId == GWM_DVRCameraId::GWM_DVR_CAMERA_ID_INCAR)
    {
        videoLapseCmd.set_sdcard_id(CameraFdb::DVRSDCardID::DVR_SDCARD_ID_INCAR);
    }
    else if (cameraId == GWM_DVRCameraId::GWM_DVR_CAMERA_ID_AVM)
    {
        videoLapseCmd.set_sdcard_id(CameraFdb::DVRSDCardID::DVR_SDCARD_ID_INCAR);
    }
    videoLapseCmd.set_video_type(
        CameraFdb::DVRVideoType::DVR_VIDEO_TYPE_TIME_LAPSE);
    // build drv message
    CFdbProtoMsgBuilder builder(videoLapseCmd);
    return mCameraFdbClient->sendMessage(
        CameraFdb::FdbCameraManagerMsgId::DVR_FDB_ANDROID_OPERATE_RECORD,
        builder, true);
}

GWM_Status DVRFdbProxy::stopLapseVideo(GWM_DVRCameraId cameraId)
{
    if(mCameraFdbClient == nullptr)
    {
        ALOGE("%s:  mCameraFdbClient == nullptr!", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    CameraFdb::DVRFdbDvrAndroidOperateRecord videoLapseCmd;
    videoLapseCmd.set_operation_type(
        CameraFdb::DVRRecordOperateType::DVR_RECORD_OPERATE_STOP);
    videoLapseCmd.set_drv_id(static_cast<CameraFdb::DVRCameraID>(cameraId));
    if (cameraId == GWM_DVRCameraId::GWM_DVR_CAMERA_ID_FRONT)
    {
        videoLapseCmd.set_sdcard_id(CameraFdb::DVRSDCardID::DVR_SDCARD_ID_FRONT);
    }
    else if (cameraId == GWM_DVRCameraId::GWM_DVR_CAMERA_ID_INCAR)
    {
        videoLapseCmd.set_sdcard_id(CameraFdb::DVRSDCardID::DVR_SDCARD_ID_INCAR);
    }
    else if (cameraId == GWM_DVRCameraId::GWM_DVR_CAMERA_ID_AVM)
    {
        videoLapseCmd.set_sdcard_id(CameraFdb::DVRSDCardID::DVR_SDCARD_ID_INCAR);
    }
    videoLapseCmd.set_video_type(
        CameraFdb::DVRVideoType::DVR_VIDEO_TYPE_TIME_LAPSE);
    // build drv message
    CFdbProtoMsgBuilder builder(videoLapseCmd);
    return mCameraFdbClient->sendMessage(
        CameraFdb::FdbCameraManagerMsgId::DVR_FDB_ANDROID_OPERATE_RECORD,
        builder, true);
}

GWM_Status DVRFdbProxy::formatTFCard(GWM_DVR_TFCardId tfcard_id)
{
    if(mCameraFdbClient == nullptr)
    {
        ALOGE("%s:  mCameraFdbClient == nullptr!", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    CameraFdb::DVRFdbAndroidOperateSD operationTFcmd;
    operationTFcmd.set_operation_type(
        CameraFdb::DVRSDCardOperateType::DVR_SDCARD_OPERATE_FORMATE);
    operationTFcmd.set_sdcard_id(
        static_cast<CameraFdb::DVRSDCardID>(tfcard_id));
    // build drv message
    CFdbProtoMsgBuilder builder(operationTFcmd);
    return mCameraFdbClient->sendMessage(
        CameraFdb::FdbCameraManagerMsgId::DVR_FDB_ANDROID_OPERATE_SDCARD,
        builder, true);
}

GWM_Status DVRFdbProxy::resetFactory()
{
    if(mCameraFdbClient == nullptr)
    {
        ALOGE("%s:  mCameraFdbClient == nullptr!", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    /* build empty protobuf builder, dont deserialize in QNX */
    CameraFdb::DVRFdbDvrAndroidSetupSet setParamCmd;
    CFdbProtoMsgBuilder builder(setParamCmd);
    return mCameraFdbClient->sendMessage(
        CameraFdb::FdbCameraManagerMsgId::DVR_FDB_ANDROID_RESTORE_FACTORY_SETUP,
        builder, true);
}

GWM_Status DVRFdbProxy::querySystemInfoFromQNX()
{
    if(mCameraFdbClient == nullptr)
    {
        ALOGE("%s:  mCameraFdbClient == nullptr!", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    // build drv message
    CameraFdb::DVRFdbQnxSystemInfro systemInfo;
    CFdbProtoMsgBuilder builder(systemInfo);
    return mCameraFdbClient->sendMessage(
        CameraFdb::FdbCameraManagerMsgId::DVR_FDB_ANDROID_GET_SYSTEM_INFRO,
        builder, true);
}

GWM_Status DVRFdbProxy::operateFile(const GWM_DVR_FileOperateAction &operation)
{
    if(mCameraFdbClient == nullptr)
    {
        ALOGE("%s:  mCameraFdbClient == nullptr!", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    // build dvr message
    CameraFdb::DVRFdbAndroidOperateFile fileOperation;
    fileOperation.set_operation_type(
        static_cast<CameraFdb::DVRFileOperateType>(operation.operation_type));
    fileOperation.set_drv_id(static_cast<CameraFdb::DVRCameraID>(operation.camera_id));
    fileOperation.set_sdcard_id(static_cast<CameraFdb::DVRSDCardID>(operation.tfcard_id));
    fileOperation.set_src_file_name(operation.src_file_name);
    fileOperation.set_dst_file_name(operation.dst_file_name);

    CFdbProtoMsgBuilder builder(fileOperation);
    return mCameraFdbClient->sendMessage(
        CameraFdb::FdbCameraManagerMsgId::DVR_FDB_ANDROID_OPERATE_FILE, builder,
        true);
}

GWM_Status DVRFdbProxy::setParam(const GWM_DVRSetParam &params)
{
    if(mCameraFdbClient == nullptr)
    {
        ALOGE("%s:  mCameraFdbClient == nullptr!", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    CameraFdb::DVRFdbDvrAndroidSetupSet setParamCmd;
    setParamCmd.set_setup_bit_flag(params.setup_bit_flag);
    setParamCmd.set_sounds_enable_status(
        static_cast<CameraFdb::DVRENABLEStatus>(params.sounds_enable_req));
    setParamCmd.set_wide_dynamic_enable_status(
        static_cast<CameraFdb::DVRENABLEStatus>(
            params.wide_dynamic_enable_req));
    setParamCmd.set_automatical_overwrite__enable_status(
        static_cast<CameraFdb::DVRENABLEStatus>(
            params.automatical_overwrite__enable_req));
    setParamCmd.set_dvr_enable_status(
        static_cast<CameraFdb::DVRENABLEStatus>(params.dvr_enable_req));
    setParamCmd.set_paking_monitoring_enable_status(
        static_cast<CameraFdb::DVRENABLEStatus>(
            params.paking_monitoring_enable_req));
    setParamCmd.set_avm_enable_status(
        static_cast<CameraFdb::DVRENABLEStatus>(params.avm_enable_req));
    setParamCmd.set_delay_shutdown(params.delay_shutdown_req);
    setParamCmd.set_record_time(params.record_time_req);
    setParamCmd.set_incar_camera_enable_status(
        static_cast<CameraFdb::DVRENABLEStatus>(
            params.incar_camera_enable_req));
    CFdbProtoMsgBuilder builder(setParamCmd);
    return mCameraFdbClient->sendMessage(
        CameraFdb::FdbCameraManagerMsgId::DVR_FDB_ANDROID_SETUP_SET, builder,
        true);
}

GWM_Status DVRFdbProxy::getParam()
{
    if(mCameraFdbClient == nullptr)
    {
        ALOGE("%s:  mCameraFdbClient == nullptr!", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    /* build empty protobuf builder, dont deserialize in QNX */
    CameraFdb::DVRFdbDvrAndroidSetupSet setParamCmd;
    CFdbProtoMsgBuilder builder(setParamCmd);
    return mCameraFdbClient->sendMessage(
        CameraFdb::FdbCameraManagerMsgId::DVR_FDB_ANDROID_SETUP_GET, builder, true);
}

GWM_Status DVRFdbProxy::uploadRequset()
{
    if(mCameraFdbClient == nullptr)
    {
        ALOGE("%s:  mCameraFdbClient == nullptr!", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    CameraFdb::DVRFdbReplay upload_reply;
    upload_reply.set_reply_status(DVR_REPLY_STATUS_OK);
    CFdbProtoMsgBuilder builder(upload_reply);
    return mCameraFdbClient->sendMessage(
        CameraFdb::FdbCameraManagerMsgId::DVR_FDB_ANDROID_UPLOAD_REQUEST, builder,
        true);
}

GWM_Status DVRFdbProxy::uploadResult(const GWM_DVRUploadFileResult &uploadResult)
{
    if(mCameraFdbClient == nullptr)
    {
        ALOGE("%s:  mCameraFdbClient == nullptr!", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    CameraFdb::DVRFdbQNXBroadcastUploadResult upload_Result;
    upload_Result.set_file_path(uploadResult.file_path);
    upload_Result.set_sequence(uploadResult.sequence);
    upload_Result.set_result(static_cast<CameraFdb::DVRUPLOADStatus>(uploadResult.uploadstatus));

    CFdbProtoMsgBuilder builder(upload_Result);
    return mCameraFdbClient->sendMessage(
        CameraFdb::FdbCameraManagerMsgId::DVR_FDB_ANDROID_UPLOAD_RESEULT, builder,
        true);
}

GWM_Status DVRFdbProxy::sendActCommd(const GWM_DVRBroadcastActCommand &boardcastActions)
{
    if (mCameraFdbServer == nullptr)
    {
        ALOGE("%s:  mCameraFdbServer == nullptr!", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    DVRFdb::DVRFdbBroadcastOperationAction act_cmd;
    act_cmd.set_operation_type((DVROperationType)boardcastActions.act_module);
    act_cmd.set_action_type((DVRActionType)boardcastActions.act_cmd);
    act_cmd.set_sequence(boardcastActions.sequence);
    CFdbProtoMsgBuilder builder(act_cmd);
    return mCameraFdbServer->sendMessage(
        DVRFdb::FdbCameraServerMsgId::DVR_Android_Send_Operation_Action, builder);
}

GWM_Status DVRFdbProxy::sendModuleEvent(const GWM_DVRSendModuleEvent &moduleEvent)
{
    if (mCameraFdbServer == nullptr)
    {
        ALOGE("%s:  mCameraFdbServer == nullptr!", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    DVRFdb::DVRFdbBroadcastModuleEventAction event_status;
    event_status.set_operation_type((DVROperationType)(uint32_t)moduleEvent.act_module);
    event_status.set_act_event((DVRModuleEvent)(uint32_t)moduleEvent.event);
    event_status.set_sequence((uint64_t)moduleEvent.sequence);
    ALOGD("%s:  send %d %d %lu",
        __FUNCTION__,
        (uint32_t)event_status.operation_type(),
        (uint32_t)event_status.act_event(),
        (uint64_t)event_status.sequence());
    CFdbProtoMsgBuilder builder(event_status);
    return mCameraFdbServer->sendMessage(
         DVRFdb::FdbCameraServerMsgId::DVR_Android_Send_Modules_Event, builder);
}

}
}
}
}
}
}