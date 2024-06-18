/*************************************************************************
* Copyright (C) 2020-2024 GWM Automotive Inc.
*
* The copyright notice above does not evidence any actual
* or intended publication of such source code.
* The code contains GWM Confidential Proprietary Information.
*************************************************************************/
/**************************************************************************
 * @file CameraFdbClient.cpp
 * Camera Fdbus Client class implementation
 *
 * @project     v3.5
 * @subsystem
 * @version     0.1
 * @author      XiuFang Liu
 * @date        2020-6-15

 Module-History:
 Date(dd.mm.year)| Author            | Reason
 The latest entry at the head of the history list.
 17/7/2020         XiuFang Liu         Init version
 ***************************************************************************/
#include <android/log.h>
#include <log/log.h>
#include "CameraFdbClient.h"
#include <DVR.h>

#undef LOG_TAG
#define LOG_TAG "CameraHAL_CameraFdbClient"

namespace vendor {
namespace gwm {
namespace hardware {
namespace camera {
namespace V1_0 {
namespace implementation {

using namespace vendor::gwm::hardware::camera::V1_0;
using namespace std;

using ::android::sp;
typedef std::vector<uint8_t> ByteBuffer;

CameraFdbClient::CameraFdbClient(const char *name, CBaseWorker *worker)
    : CBaseClient(name, worker), mDVR(nullptr) {}

CameraFdbClient::~CameraFdbClient() {}

void CameraFdbClient::onOnline(FdbSessionId_t sid, bool is_first) {
    ALOGI("%s:  client session online: %d, is_first: %d", __FUNCTION__, sid, is_first);

    isFdbOnline = GWM_DVRIPCStatus::GWM_DVR_IPC_ONLINE;
    if (mDVR != nullptr) {
        ALOGI("%s:  client ipc online notify", __FUNCTION__);
        mDVR->onReportIPCStatus(isFdbOnline);
    }

    if (is_first) {
        fdb_online = true;
        subscribeMsg();
    }
}

void CameraFdbClient::onOffline(FdbSessionId_t sid, bool is_last) {
    ALOGI("%s:  client session offline: %d, is_last: %d", __FUNCTION__, sid, is_last);
    isFdbOnline = GWM_DVRIPCStatus::GWM_DVR_IPC_OFFLINE;
    if (mDVR != nullptr) {
        ALOGI("%s:  client ipc offline notify", __FUNCTION__);
        mDVR->onReportIPCStatus(isFdbOnline);
    }

    fdb_online = false;
}

void CameraFdbClient::onBroadcast(CBaseJob::Ptr &msg_ref) {
    auto msg = castToMessage<CBaseMessage *>(msg_ref);
    ALOGD("%s:  Broadcast is received: %#X; filter: %s",
        __FUNCTION__,
        msg->code(),
        msg->getFilter());

    switch (msg->code()) {
        case CameraFdb::FdbCameraManagerMsgId::DVR_FDB_ANDROID_GET_SYSTEM_INFRO:
        case CameraFdb::FdbCameraManagerMsgId::DVR_FDB_QNX_BROADCAST_SYSTEM_INFRO: {
            notifyDVRSystemStatus(msg);
        }
        break;
        case CameraFdb::FdbCameraManagerMsgId::DVR_FDB_QNX_BROADCAST_SETUP_SET_RESULT: {
            notifySetParam(msg);
        }
        break;
        case CameraFdb::FdbCameraManagerMsgId::DVR_FDB_ANDROID_SETUP_GET_RESULT: {
            notifyGetParam(msg);
        }
        break;
        case CameraFdb::FdbCameraManagerMsgId::DVR_FDB_QNX_BROADCAST_OPERATE_FILE: {
            notifyFileOperate(msg);
        }
        break;
        case CameraFdb::FdbCameraManagerMsgId::DVR_FDB_QNX_BROADCAST_OPERATE_RECORD_RESULT: {
            notifyVideoOperate(msg);
        }
        break;
        case CameraFdb::FdbCameraManagerMsgId::DVR_FDB_QNX_BROADCAST_OPERATE_SDCARD_RESULT: {
            notifyTFCardOperate(msg);
        }
        break;
        case CameraFdb::FdbCameraManagerMsgId::DVR_FDB_QNX_BROADCAST_RESTORE_FACTORY_SETUP_RESULT: {
            notifyFactoryReset(msg);
        }
        break;
        case CameraFdb::FdbCameraManagerMsgId::DVR_FDB_ANDROID_OPERATE_PREVIEW_RESULT: {
            notifyPreviewReply(msg);
        }
        break;
        case CameraFdb::FdbCameraManagerMsgId::DVR_FDB_QNX_BROADCAST_RECORD_TIME: {
            notifyRecordTimeInfo(msg);
        }
        break;
        case CameraFdb::FdbCameraManagerMsgId::DVR_FDB_QNX_BROADCAST_RECORD_STATUS: {
            notifyRecordStatus(msg);
        }
        break;
        case CameraFdb::FdbCameraManagerMsgId::DVR_FDB_QNX_BROADCAST_TF_STATUS_CHANGED: {
            notifyTFStatus(msg);
        }
        break;
        case CameraFdb::FdbCameraManagerMsgId::DVR_FDB_QNX_BROADCAST_CAMERA_STATUS_CHANGED: {
            notifyCameraStatus(msg);
        }
        break;
        case CameraFdb::FdbCameraManagerMsgId::DVR_FDB_QNX_BROADCAST_TF_CAPACITY_STATUS_CHANGED: {
            notifyTFCapacityStatus(msg);
        }
        break;
        case CameraFdb::FdbCameraManagerMsgId::DVR_FDB_QNX_BROADCAST_TF_CAPACITY_COST_CHANGED: {
            notifyTFCapacityCostStatus(msg);
        }
        break;
        case CameraFdb::FdbCameraManagerMsgId::DVR_FDB_QNX_BROADCAST_DEVICE_STATUS_CHANGED: {
            notifyDeviceStatus(msg);
        }
        break;
        //add by dingyu for upload video file
        case CameraFdb::FdbCameraManagerMsgId::DVR_FDB_QNX_UPLOAD_REQUEST_ACK: {
            notifyUploadStatus(msg);
        }
        break;
        case CameraFdb::FdbCameraManagerMsgId::DVR_FDB_QNX_UPLOAD_ADD: {
            notifyUploadFileStatus(msg);
        }
        break;
        default:
        break;
    }
}

void CameraFdbClient::onReply(CBaseJob::Ptr &msg_ref) {
    auto msg = castToMessage<CBaseMessage *>(msg_ref);
    ALOGI("%s:  response is receieved. sn: %d code =%#X", __FUNCTION__, msg->sn(),
        msg->code());
    switch (msg->code()) {
        case CameraFdb::FdbCameraManagerMsgId::DVR_FDB_ANDROID_OPERATE_SDCARD:
        /*SDCard format*/
        case CameraFdb::FdbCameraManagerMsgId::DVR_FDB_ANDROID_RESTORE_FACTORY_SETUP:
        /*Factory reset setup*/
        case CameraFdb::FdbCameraManagerMsgId::DVR_FDB_ANDROID_OPERATE_RECORD: {
            /*Video operation*/
            CameraFdb::DVRFdbReplay drv_reply;
            CFdbProtoMsgParser parser(drv_reply);
            if (msg->deserialize(parser)) {
                mDVR->onQNXReplyData(static_cast<GWM_Status>(drv_reply.reply_status()),
                    msg->code());
            }
        }
        break;
        default:
        break;
    }
}

void CameraFdbClient::onStatus(CBaseJob::Ptr &msg_ref, int error_code,
    const char *description) {
    auto msg = castToMessage<CBaseMessage *>(msg_ref);

    if (msg->isSubscribe()) {
        if (msg->isError()) {
            ALOGW("%s:  subscribe is error !", __FUNCTION__);
        } else {
            ALOGI("%s:  subscribe is ok! sn: %d is received.", __FUNCTION__, msg->sn());
        }
    }
    ALOGI("%s:  Reason: %s", __FUNCTION__, description);
}

GWM_Status CameraFdbClient::sendMessage(FdbMsgCode_t code,
    CFdbProtoMsgBuilder builder,
    bool is_sync) {
    if (!fdb_online) {
        ALOGE("%s:  fdbus is not line.", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    // sync interface
    if (is_sync) {
        CBaseJob::Ptr msg_ref(new CBaseMessage(code));
        bool ret = false;
        ret = invoke(msg_ref, builder, FDBUS_TIMEOUT);
        if (ret) {
            ALOGI("%s:  msg:%#X has successfully sent to fdbus tx queue(sync).",
                __FUNCTION__,
                code);
        } else {
            ALOGE("%s:  msg:%#X has failed to send to fdbus queue(sync).",
                __FUNCTION__,
                code);
            return GWM_Status::GWM_ERROR;
        }

        auto msg = castToMessage<CBaseMessage *>(msg_ref);
        /* Check msg status*/
        if (msg->isStatus()) {
            /* Unable to get intended reply from server... Check what happen. */
            int32_t id;
            std::string reason;
            if (!msg->decodeStatus(id, reason)) {
                ALOGE("%s:  onReply: fail to decode status!\n", __FUNCTION__);
            }
            /* Check if something is wrong... */
            if (msg->isError()) {
                ALOGI("%s:  sync reply: status is received: msg code: %#X, id: %d, reason: %s",
                    __FUNCTION__, msg->code(), id, reason.c_str());
            }
            return GWM_Status::GWM_ERROR;
        }

        switch (code) {
            case CameraFdb::FdbCameraManagerMsgId::DVR_FDB_ANDROID_OPERATE_PREVIEW: {
                CameraFdb::DVRFdbReplay preview_reply;
                CFdbProtoMsgParser parser(preview_reply);
                if (msg->deserialize(parser)) {
                    std::lock_guard<std::mutex> lock(mMutex);
                    return static_cast<GWM_Status>(preview_reply.reply_status());
                }
            } break;
            default: {
                /*Parse data return*/
                CameraFdb::DVRFdbReplay drv_reply;
                CFdbProtoMsgParser parser(drv_reply);
                if (msg->deserialize(parser)) {
                    return static_cast<GWM_Status>(drv_reply.reply_status());
                }
            } break;
        }
    } else {
        bool ret = false;
        ret = invoke(code, builder);
        if (ret) {
            ALOGI("%s:  msg:%#X has successfully sent to fdbus tx queue(async).",
                __FUNCTION__,
                code);
            return GWM_Status::GWM_OK;
        } else {
            ALOGE("%s:  msg:%#X has failed to send to fdbus queue(async).",
                __FUNCTION__,
                code);
            return GWM_Status::GWM_ERROR;
        }
    }
    return GWM_Status::GWM_ERROR;
}

void CameraFdbClient::setDVRClient(sp<DVR> drv) { mDVR = drv; }

void CameraFdbClient::subscribeMsg()
{
    CFdbMsgSubscribeList subscribe_list;
    addNotifyItem(subscribe_list,
        CameraFdb::FdbCameraManagerMsgId::DVR_FDB_QNX_BROADCAST_OPERATE_FILE);
    addNotifyItem(subscribe_list,
        CameraFdb::FdbCameraManagerMsgId::DVR_FDB_QNX_BROADCAST_RESTORE_FACTORY_SETUP_RESULT);
    addNotifyItem(subscribe_list,
        CameraFdb::FdbCameraManagerMsgId::DVR_FDB_ANDROID_SETUP_GET_RESULT);
    addNotifyItem(subscribe_list,
        CameraFdb::FdbCameraManagerMsgId::DVR_FDB_QNX_BROADCAST_SETUP_SET_RESULT);
    addNotifyItem(subscribe_list,
        CameraFdb::FdbCameraManagerMsgId::DVR_FDB_QNX_BROADCAST_OPERATE_SDCARD_RESULT);
    addNotifyItem(subscribe_list,
        CameraFdb::FdbCameraManagerMsgId::DVR_FDB_QNX_BROADCAST_OPERATE_RECORD_RESULT);
    addNotifyItem(subscribe_list,
        CameraFdb::FdbCameraManagerMsgId::DVR_FDB_QNX_BROADCAST_SYSTEM_INFRO);
    addNotifyItem(subscribe_list,
        CameraFdb::FdbCameraManagerMsgId::DVR_FDB_ANDROID_OPERATE_PREVIEW_RESULT);
    addNotifyItem(subscribe_list,
        CameraFdb::FdbCameraManagerMsgId::DVR_FDB_QNX_BROADCAST_RECORD_TIME);
    addNotifyItem(subscribe_list,
        CameraFdb::FdbCameraManagerMsgId::DVR_FDB_QNX_BROADCAST_RECORD_STATUS);
    addNotifyItem(subscribe_list,
        CameraFdb::FdbCameraManagerMsgId::DVR_FDB_QNX_BROADCAST_TF_STATUS_CHANGED);
    addNotifyItem(subscribe_list,
        CameraFdb::FdbCameraManagerMsgId::DVR_FDB_QNX_BROADCAST_CAMERA_STATUS_CHANGED);
    addNotifyItem(subscribe_list,
        CameraFdb::FdbCameraManagerMsgId::DVR_FDB_QNX_BROADCAST_TF_CAPACITY_STATUS_CHANGED);
    addNotifyItem(subscribe_list,
        CameraFdb::FdbCameraManagerMsgId::DVR_FDB_QNX_BROADCAST_TF_CAPACITY_COST_CHANGED);
    addNotifyItem(subscribe_list,
        CameraFdb::FdbCameraManagerMsgId::DVR_FDB_QNX_BROADCAST_DEVICE_STATUS_CHANGED);
    addNotifyItem(subscribe_list,
        CameraFdb::FdbCameraManagerMsgId::DVR_FDB_QNX_UPLOAD_REQUEST_ACK);
    addNotifyItem(subscribe_list,
        CameraFdb::FdbCameraManagerMsgId::DVR_FDB_QNX_UPLOAD_ADD);
    bool ret = subscribe(subscribe_list);
    ALOGI("%s:  ret: %d", __FUNCTION__, ret);
}

void CameraFdbClient::notifyDVRSystemStatus(const CBaseMessage* msg)
{
    CameraFdb::DVRFdbQnxSystemInfro systemInfo;
    CFdbProtoMsgParser parser(systemInfo);
    if (msg->deserialize(parser)) {
        if (mDVR == nullptr)
        {
            ALOGE("%s:  mDVR == nullptr!", __FUNCTION__);
            return;
        }

        mDVR->mSystemStatusInfo.device_status =
            (GWM_DVRSystemStatus)systemInfo.device_status();
        mDVR->mSystemStatusInfo.front_sdcard_status =
            (GWM_DVR_TFCardStatus)systemInfo.front_sdcard_status();
        mDVR->mSystemStatusInfo.front_camera_status =
            (GWM_DVRSystemStatus)systemInfo.front_camera_status();
        mDVR->mSystemStatusInfo.avm_camera_status =
            (GWM_DVRSystemStatus)systemInfo.avm_camera_status();
        mDVR->mSystemStatusInfo.incar_sdcard_status =
            (GWM_DVR_TFCardStatus)systemInfo.incar_sdcard_status();
        mDVR->mSystemStatusInfo.incar_camera_status =
            (GWM_DVRSystemStatus)systemInfo.incar_camera_status();

        mDVR->mSystemStatusInfo.front_infor.tfcard_total_capacity =
            systemInfo.tfcard_front_total_capacity();
        mDVR->mSystemStatusInfo.front_infor.tfcard_loop_capacity =
            systemInfo.tfcard_front_loop_capacity();
        mDVR->mSystemStatusInfo.front_infor.tfcard_emergency_capacity =
            systemInfo.tfcard_front_emergency_capacity();
        mDVR->mSystemStatusInfo.front_infor.tfcard_normal_capacity =
            systemInfo.tfcard_front_normal_capacity();
        mDVR->mSystemStatusInfo.front_infor.tfcard_format_type =
            (GWM_DVR_TFType)systemInfo.tfcard_front_format_type();
        mDVR->mSystemStatusInfo.front_infor.tfcard_used_capacity =
            systemInfo.tfcard_front_used_capacity();
        mDVR->mSystemStatusInfo.front_infor.tfcard_loop_capacity_status =
            (GWM_DVRCapacityStatus)systemInfo.tfcard_front_loop_capacity_status();
        mDVR->mSystemStatusInfo.front_infor.tfcard_emergency_capacity_status =
            (GWM_DVRCapacityStatus)systemInfo.tfcard_front_emergency_capacity_status();
        mDVR->mSystemStatusInfo.front_infor.tfcard_normal_capacity_status =
            (GWM_DVRCapacityStatus)systemInfo.tfcard_front_normal_capacity_status();

        mDVR->mSystemStatusInfo.inner_infor.tfcard_total_capacity =
            systemInfo.tfcard_inner_total_capacity();
        mDVR->mSystemStatusInfo.inner_infor.tfcard_loop_capacity =
            systemInfo.tfcard_inner_loop_capacity();
        mDVR->mSystemStatusInfo.inner_infor.tfcard_emergency_capacity =
            systemInfo.tfcard_inner_emergency_capacity();
        mDVR->mSystemStatusInfo.inner_infor.tfcard_normal_capacity =
            systemInfo.tfcard_inner_normal_capacity();
        mDVR->mSystemStatusInfo.inner_infor.tfcard_format_type =
            (GWM_DVR_TFType)systemInfo.tfcard_inner_format_type();
        mDVR->mSystemStatusInfo.inner_infor.tfcard_used_capacity =
            systemInfo.tfcard_incar_used_capacity();
        mDVR->mSystemStatusInfo.inner_infor.tfcard_loop_capacity_status =
            (GWM_DVRCapacityStatus)systemInfo.tfcard_inner_loop_capacity_status();
        mDVR->mSystemStatusInfo.inner_infor.tfcard_emergency_capacity_status =
            (GWM_DVRCapacityStatus)systemInfo.tfcard_inner_emergency_capacity_status();
        mDVR->mSystemStatusInfo.inner_infor.tfcard_normal_capacity_status =
            (GWM_DVRCapacityStatus)systemInfo.tfcard_inner_normal_capacity_status();

        /* avm use inner sdcard total/used capacity and format type */
        mDVR->mSystemStatusInfo.avm_infor.tfcard_total_capacity =
            systemInfo.tfcard_inner_total_capacity();
        mDVR->mSystemStatusInfo.avm_infor.tfcard_loop_capacity =
            systemInfo.tfcard_avm_loop_capacity();
        mDVR->mSystemStatusInfo.avm_infor.tfcard_emergency_capacity =
            systemInfo.tfcard_avm_emergency_capacity();
        mDVR->mSystemStatusInfo.avm_infor.tfcard_normal_capacity =
            systemInfo.tfcard_avm_normal_capacity();
        mDVR->mSystemStatusInfo.avm_infor.tfcard_format_type =
            (GWM_DVR_TFType)systemInfo.tfcard_inner_format_type();
        mDVR->mSystemStatusInfo.avm_infor.tfcard_used_capacity =
            systemInfo.tfcard_incar_used_capacity();
        mDVR->mSystemStatusInfo.avm_infor.tfcard_loop_capacity_status =
            (GWM_DVRCapacityStatus)systemInfo.tfcard_avm_loop_capacity_status();
        mDVR->mSystemStatusInfo.avm_infor.tfcard_emergency_capacity_status =
            (GWM_DVRCapacityStatus)systemInfo.tfcard_avm_emergency_capacity_status();
        mDVR->mSystemStatusInfo.avm_infor.tfcard_normal_capacity_status =
            (GWM_DVRCapacityStatus)systemInfo.tfcard_avm_normal_capacity_status();

        mDVR->onQNXBoardcastData(msg->code());
    } else {
        ALOGE("%s:  Unable to decode DVR_FDB_ANDROID_GET_SYSTEM_INFRO!", __FUNCTION__);
    }
}

void CameraFdbClient::notifySetParam(const CBaseMessage* msg)
{
    CameraFdb::DVRFdbDvrAndroidSetupSetQnxBroadcastResult setupParam;
    CFdbProtoMsgParser parser(setupParam);
    if (msg->deserialize(parser)) {
        if (mDVR == nullptr)
        {
            ALOGE("%s:  mDVR == nullptr!", __FUNCTION__);
            return;
        }

        mDVR->mSetParamReply.set_bit_flag = setupParam.setup_bit_flag();
        mDVR->mSetParamReply.sounds_enable_reply =
            static_cast<GWM_DVRReply>(setupParam.sounds_enable_status());
        mDVR->mSetParamReply.wide_dynamic_enable_reply =
            static_cast<GWM_DVRReply>(setupParam.wide_dynamic_enable_status());
        mDVR->mSetParamReply.automatical_overwrite__enable_reply =
            static_cast<GWM_DVRReply>(setupParam.automatical_overwrite__enable_status());
        mDVR->mSetParamReply.dvr_enable_reply =
            static_cast<GWM_DVRReply>(setupParam.dvr_enable_status());
        mDVR->mSetParamReply.paking_monitoring_enable_reply =
            static_cast<GWM_DVRReply>(setupParam.paking_monitoring_enable_status());
        mDVR->mSetParamReply.avm_enable_reply =
            static_cast<GWM_DVRReply>(setupParam.avm_enable_status());
        mDVR->mSetParamReply.delay_shutdown_reply =
            static_cast<GWM_DVRReply>(setupParam.delay_shutdown());
        mDVR->mSetParamReply.record_time_reply =
            static_cast<GWM_DVRReply>(setupParam.record_time());
        mDVR->mSetParamReply.incar_camera_enable_reply =
            static_cast<GWM_DVRReply>(setupParam.incar_camera_enable_status());
        mDVR->onQNXBoardcastData(msg->code());
    } else {
        ALOGE("%s:  Unable to decode DVR_FDB_ANDROID_SETUP_SET!", __FUNCTION__);
    }
}

void CameraFdbClient::notifyGetParam(const CBaseMessage* msg)
{
    CameraFdb::DVRFdbDvrAndroidSetupGetReply getParam;
    CFdbProtoMsgParser parser(getParam);
    if (msg->deserialize(parser)) {
        if (mDVR == nullptr)
        {
            ALOGE("%s:  mDVR == nullptr!", __FUNCTION__);
            return;
        }
        mDVR->mGetParam.sounds_enable_status =
            static_cast<GWM_DVRStatus>(getParam.sounds_enable_status());
        mDVR->mGetParam.wide_dynamic_enable_status =
            static_cast<GWM_DVRStatus>(getParam.wide_dynamic_enable_status());
        mDVR->mGetParam.automatical_overwrite__enable_status =
            static_cast<GWM_DVRStatus>(getParam.automatical_overwrite__enable_status());
        mDVR->mGetParam.dvr_enable_status =
            static_cast<GWM_DVRStatus>(getParam.dvr_enable_status());
        mDVR->mGetParam.paking_monitoring_enable_status =
            static_cast<GWM_DVRStatus>(getParam.paking_monitoring_enable_status());
        mDVR->mGetParam.avm_enable_status =
            static_cast<GWM_DVRStatus>(getParam.avm_enable_status());
        mDVR->mGetParam.delay_shutdown = getParam.delay_shutdown();
        mDVR->mGetParam.record_time = getParam.record_time();
        mDVR->mGetParam.incar_camera_enable_status =
            static_cast<GWM_DVRStatus>(getParam.incar_camera_enable_status());
        mDVR->onQNXBoardcastData(msg->code());
    } else {
        ALOGE("%s:  Unable to decode DVR_FDB_ANDROID_SETUP_GET!", __FUNCTION__);
    }
}

void CameraFdbClient::notifyFileOperate(const CBaseMessage* msg)
{
    CameraFdb::DVRFdbQNXBroadcastOperateFile file_operate;
    CFdbProtoMsgParser parser(file_operate);
    if (msg->deserialize(parser)) {
        if (mDVR == nullptr)
        {
            ALOGE("%s:  mDVR == nullptr!", __FUNCTION__);
            return;
        }

        mDVR->mFileOperateEvent.operation_type =
            static_cast<GWM_DVR_FileOperateType>(file_operate.operation_type());
        mDVR->mFileOperateEvent.camera_id =
            static_cast<GWM_DVRCameraId>(file_operate.drv_id());
        mDVR->mFileOperateEvent.tfcard_id =
            static_cast<GWM_DVR_TFCardId>(file_operate.sdcard_id());
        mDVR->mFileOperateEvent.src_file_name = file_operate.src_file_name();
        mDVR->mFileOperateEvent.dst_file_name = file_operate.dst_file_name();
        mDVR->mFileOperateEvent.video_type =
            static_cast<GWM_DVR_VIDEO_TYPE>(file_operate.video_type());
        mDVR->onQNXBoardcastData(msg->code());
    } else {
        ALOGE("%s:  Unable to decode DVR_FDB_QNX_BROADCAST_OPERATE_FILE!", __FUNCTION__);
    }
}

void CameraFdbClient::notifyVideoOperate(const CBaseMessage* msg)
{
    CameraFdb::DVRFdbAndroidOperateRecordBroadcastResult record_capture_start_result;
    CFdbProtoMsgParser parser(record_capture_start_result);
    if (msg->deserialize(parser)) {
        if (mDVR == nullptr)
        {
            ALOGE("%s:  mDVR == nullptr!", __FUNCTION__);
            return;
        }

        mDVR->mVideoOperateEvent.cmd_action =
            static_cast<GWM_DVR_CMD_ACTION>(record_capture_start_result.operation_stage());
        mDVR->mVideoOperateEvent.operation_type =
            static_cast<GWM_DVRVideoOperateType>(record_capture_start_result.operation_type());
        mDVR->mVideoOperateEvent.camera_id =
            static_cast<GWM_DVRCameraId>(record_capture_start_result.drv_id());
        mDVR->mVideoOperateEvent.tfcard_id =
            static_cast<GWM_DVR_TFCardId>(record_capture_start_result.sdcard_id());
        mDVR->mVideoOperateEvent.video_type =
            static_cast<GWM_DVR_VIDEO_TYPE>(record_capture_start_result.video_type());
        mDVR->mVideoOperateEvent.reply_result =
            static_cast<GWM_DVRReply>(record_capture_start_result.result());
        mDVR->onQNXBoardcastData(msg->code());
    } else {
        ALOGE("%s:  Unable to decode DVR_FDB_QNX_BROADCAST_OPERATE_RECORD_CAPTURE_RESULT!", __FUNCTION__);
    }
}

void CameraFdbClient::notifyTFCardOperate(const CBaseMessage* msg)
{
    CameraFdb::DVRFdbAndroidOperateSDBroadcastResult tfcard_operate;
    CFdbProtoMsgParser parser(tfcard_operate);
    if (msg->deserialize(parser)) {
        if (mDVR == nullptr)
        {
            ALOGE("%s:  mDVR == nullptr!", __FUNCTION__);
            return;
        }

        mDVR->mTfCardOperateEvent.operation_type =
            static_cast<GWM_DVR_TFCardOperateType>(tfcard_operate.operation_type());
        mDVR->mTfCardOperateEvent.tfcard_id =
            static_cast<GWM_DVR_TFCardId>(tfcard_operate.sdcard_id());
        mDVR->mTfCardOperateEvent.reply_result =
            static_cast<GWM_DVRReply>(tfcard_operate.result());
        mDVR->onQNXBoardcastData(msg->code());
    } else {
        ALOGE("%s:  Unable to decode DVR_FDB_QNX_BROADCAST_OPERATE_SDCARD_RESULT!", __FUNCTION__);
    }
}

void CameraFdbClient::notifyFactoryReset(const CBaseMessage* msg)
{
    CameraFdb::DVRFdbAndroidRestoreFactorySetupBroadcastResult factory_reset;
    CFdbProtoMsgParser parser(factory_reset);
    if (msg->deserialize(parser)) {
        if (mDVR == nullptr)
        {
            ALOGE("%s:  mDVR == nullptr!", __FUNCTION__);
            return;
        }

        mDVR->mfactoryreset_result =
            static_cast<GWM_DVRReply>(factory_reset.result());
        mDVR->onQNXBoardcastData(msg->code());
    } else {
        ALOGE("%s:  Unable to decode DVR_FDB_QNX_BROADCAST_RESTORE_FACTORY_SETUP_RESULT!", __FUNCTION__);
    }
}

void CameraFdbClient::notifyPreviewReply(const CBaseMessage* msg)
{
    CameraFdb::DVRFdbDvrPreviewRtspInfo preview_reply;
    CFdbProtoMsgParser parser(preview_reply);
    if (msg->deserialize(parser)) {
        if (mDVR == nullptr)
        {
            ALOGE("%s:  mDVR == nullptr!", __FUNCTION__);
            return;
        }

        mDVR->mPreviewReply.rtsp_addr = preview_reply.addr();
        mDVR->mPreviewReply.cameraId =
            static_cast<GWM_DVRCameraId>(preview_reply.drv_id());
        mDVR->mPreviewReply.preview_result =
            static_cast<GWM_DVRReply>(preview_reply.result());
        mDVR->mPreviewReply.operation_type =
            static_cast<GWM_DVRVideoOperateType>(preview_reply.operation_type());
        mDVR->onQNXBoardcastData(msg->code());
    } else {
        ALOGE("%s:  Unable to decode DVR_FDB_ANDROID_OPERATE_PREVIEW_RESULT!", __FUNCTION__);
    }
}

void CameraFdbClient::notifyRecordTimeInfo(const CBaseMessage* msg)
{
    CameraFdb::DVRFdbAndroidRecordTime record_time_info;
    CFdbProtoMsgParser parser(record_time_info);
    if (msg->deserialize(parser)) {
        if (mDVR == nullptr)
        {
            ALOGE("%s:  mDVR == nullptr!", __FUNCTION__);
            return;
        }

        mDVR->mRecordTimeInfo.report_bit_flag =
            record_time_info.report_bit_flag();
        mDVR->mRecordTimeInfo.front_long_recorded_time =
            record_time_info.front_long_recorded_time();
        mDVR->mRecordTimeInfo.front_short_recorded_time =
            record_time_info.front_short_recorded_time();
        mDVR->mRecordTimeInfo.front_time_lapse_recorded_time =
            record_time_info.front_time_lapse_recorded_time();
        mDVR->mRecordTimeInfo.front_emergency_recorded_time =
            record_time_info.front_emergency_recorded_time();
        mDVR->mRecordTimeInfo.incar_long_recorded_time =
            record_time_info.incar_long_recorded_time();
        mDVR->mRecordTimeInfo.incar_short_recorded_time =
            record_time_info.incar_short_recorded_time();
        mDVR->mRecordTimeInfo.incar_time_lapse_recorded_time =
            record_time_info.incar_time_lapse_recorded_time();
        mDVR->mRecordTimeInfo.incar_emergency_recorded_time =
            record_time_info.incar_emergency_recorded_time();
        mDVR->mRecordTimeInfo.avm_long_recorded_time =
            record_time_info.avm_long_recorded_time();
        mDVR->mRecordTimeInfo.avm_short_recorded_time =
            record_time_info.avm_short_recorded_time();
        mDVR->mRecordTimeInfo.avm_emergency_recorded_time =
            record_time_info.avm_emergency_recorded_time();
        mDVR->onQNXBoardcastData(msg->code());
    } else {
        ALOGE("%s:  Unable to decode DVR_FDB_QNX_BROADCAST_RECORD_TIME!", __FUNCTION__);
    }
}

void CameraFdbClient::notifyRecordStatus(const CBaseMessage* msg)
{
    CameraFdb::DVRFdbAndroidRecordStatus recordstatus;
    CFdbProtoMsgParser parser(recordstatus);
    if (msg->deserialize(parser)) {
        if (mDVR == nullptr)
        {
            ALOGE("%s:  mDVR == nullptr!", __FUNCTION__);
            return;
        }
        mDVR->mRecordStatus = recordstatus.record_status();
        mDVR->onQNXBoardcastData(msg->code());
    } else {
        ALOGE("%s:  Unable to decode DVR_FDB_QNX_BROADCAST_RECORD_STATUS!", __FUNCTION__);
    }
}

void CameraFdbClient::notifyTFStatus(const CBaseMessage* msg)
{
    CameraFdb::DVRFdbAndroidTFStatus tfcard_status;
    CFdbProtoMsgParser parser(tfcard_status);
    if (msg->deserialize(parser)) {
        if (mDVR == nullptr)
        {
            ALOGE("%s:  mDVR == nullptr!", __FUNCTION__);
            return;
        }
        mDVR->mTfcardStatus.tfcard_id =
            static_cast<GWM_DVR_TFCardId>(tfcard_status.sdcard_id());
        mDVR->mTfcardStatus.tfcard_status =
            static_cast<GWM_DVR_TFCardStatus>(tfcard_status.sdcard_status());
        mDVR->onQNXBoardcastData(msg->code());
    } else {
        ALOGE("%s:  Unable to decode DVR_FDB_QNX_BROADCAST_TF_STATUS_CHANGED!", __FUNCTION__);
    }
}

void CameraFdbClient::notifyCameraStatus(const CBaseMessage* msg)
{
    CameraFdb::DVRFdbAndroidCameraStatus camera_status;
    CFdbProtoMsgParser parser(camera_status);
    if (msg->deserialize(parser)) {
        if (mDVR == nullptr)
        {
            ALOGE("%s:  mDVR == nullptr!", __FUNCTION__);
            return;
        }
        mDVR->mCameraStatus.camera_id =
            static_cast<GWM_DVRCameraId>(camera_status.camera_id());
        mDVR->mCameraStatus.camera_status =
            static_cast<GWM_DVRSystemStatus>(camera_status.camera_status());
        mDVR->onQNXBoardcastData(msg->code());
    } else {
        ALOGE("%s:  Unable to decode DVR_FDB_QNX_BROADCAST_CAMERA_STATUS_CHANGED!", __FUNCTION__);
    }
}

void CameraFdbClient::notifyTFCapacityStatus(const CBaseMessage* msg)
{
    CameraFdb::DVRFdbAndroidTFCapacityStatusChanged capacity_status;
    CFdbProtoMsgParser parser(capacity_status);
    if (msg->deserialize(parser)) {
        if (mDVR == nullptr)
        {
            ALOGE("%s:  mDVR == nullptr!", __FUNCTION__);
            return;
        }

        mDVR->mCapacityStatus.tfcard_id =
            static_cast<GWM_DVR_TFCardId>(capacity_status.sdcard_id());
        mDVR->mCapacityStatus.camera_id =
            static_cast<GWM_DVRCameraId>(capacity_status.camera_id());
        mDVR->mCapacityStatus.capacity_id =
            static_cast<GWM_DVRCapacityId>(capacity_status.capacity_id());
        mDVR->mCapacityStatus.capacity_status =
            static_cast<GWM_DVRCapacityStatus>(capacity_status.capacity_status());
        mDVR->onQNXBoardcastData(msg->code());
    } else {
        ALOGE("%s:  Unable to decode DVR_FDB_QNX_BROADCAST_TF_CAPACITY_STATUS_CHANGED!", __FUNCTION__);
    }
}

void CameraFdbClient::notifyTFCapacityCostStatus(const CBaseMessage* msg)
{
    CameraFdb::DVRFdbAndroidTFCapacityCostChanged capacity_cost_status;
    CFdbProtoMsgParser parser(capacity_cost_status);
    if (msg->deserialize(parser)) {
        if (mDVR == nullptr)
        {
            ALOGE("%s:  mDVR == nullptr!", __FUNCTION__);
            return;
        }

        mDVR->mCapacityCostStatus.camera_id =
            static_cast<GWM_DVRCameraId>(capacity_cost_status.camera_id());
        mDVR->mCapacityCostStatus.tfcard_id =
            static_cast<GWM_DVR_TFCardId>(capacity_cost_status.sdcard_id());
        mDVR->mCapacityCostStatus.loop_capacity =
            capacity_cost_status.loop_capacity();
        mDVR->mCapacityCostStatus.emergency_capacity =
            capacity_cost_status.emergency_capacity();
        mDVR->mCapacityCostStatus.user_capacity =
            capacity_cost_status.user_capacity();
        mDVR->mCapacityCostStatus.total_capacity =
            capacity_cost_status.total_capacity();
        mDVR->mCapacityCostStatus.used_capacity =
            capacity_cost_status.used_capacity();
        mDVR->mCapacityCostStatus.tfcard_type =
            static_cast<GWM_DVR_TFType>(capacity_cost_status.card_format_type());
        mDVR->onQNXBoardcastData(msg->code());
    } else {
        ALOGE("%s:  Unable to decode DVR_FDB_QNX_BROADCAST_TF_CAPACITY_COST_CHANGED!", __FUNCTION__);
    }
}

void CameraFdbClient::notifyDeviceStatus(const CBaseMessage* msg)
{
    CameraFdb::DVRFdbAndroidDeviceStatus device_status;
    CFdbProtoMsgParser parser(device_status);
    if (msg->deserialize(parser)) {
        if (mDVR == nullptr)
        {
            ALOGE("%s:  mDVR == nullptr!", __FUNCTION__);
            return;
        }
        mDVR->mDeviceStatus =
            static_cast<GWM_DVRDeviceStatus>(device_status.device_status());
        mDVR->onQNXBoardcastData(msg->code());
    } else {
        ALOGE("%s:  Unable to decode DVR_FDB_QNX_BROADCAST_DEVICE_STATUS_CHANGED!", __FUNCTION__);
    }
}

void CameraFdbClient::notifyUploadStatus(const CBaseMessage* msg)
{
    CameraFdb::DVRFdbReplay upload_status;
    CFdbProtoMsgParser parser(upload_status);
    if (msg->deserialize(parser)) {
        if (mDVR == nullptr)
        {
            ALOGE("%s:  mDVR == nullptr!", __FUNCTION__);
            return;
        }
        mDVR->mUploadStatus =
            static_cast<GWM_DVRReply>(upload_status.reply_status());
        mDVR->onQNXBoardcastData(msg->code());
    } else {
        ALOGE("%s:  Unable to decode DVR_FDB_QNX_UPLOAD_REQUEST_ACK!", __FUNCTION__);
    }
}

void CameraFdbClient::notifyUploadFileStatus(const CBaseMessage* msg)
{
    CameraFdb::DVRFdbQNXBroadcastUploadFile upload_file;
    CFdbProtoMsgParser parser(upload_file);
    if (msg->deserialize(parser)) {
        if (mDVR == nullptr)
        {
            ALOGE("%s:  mDVR == nullptr!", __FUNCTION__);
            return;
        }

        mDVR->mFileStatus.file_path = upload_file.file_path();
        mDVR->mFileStatus.file_size = upload_file.file_size();
        mDVR->mFileStatus.sequence = upload_file.sequence();
        mDVR->mFileStatus.tfcard_id = static_cast<GWM_DVR_TFCardId>(upload_file.sdcard_id());
        mDVR->mFileStatus.camera_id = static_cast<GWM_DVRCameraId>(upload_file.camera_id());
        mDVR->mFileStatus.upload_type = static_cast<GWM_DVRUploadType>(upload_file.upload_type());
        mDVR->onQNXBoardcastData(msg->code());
    } else {
        ALOGE("%s:  Unable to decode DVR_FDB_QNX_UPLOAD_ADD!", __FUNCTION__);
    }
}

}  // namespace implementation
}  // namespace V1_0
}  // namespace camera
}  // namespace hardware
}  // namespace gwm
}  // namespace vendor
