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
#include <android/log.h>
#include <log/log.h>
#include "DVRSomeipProxy.h"

#undef LOG_TAG
#define LOG_TAG "CameraHAL_DVRSomeipProxy"

namespace vendor {
namespace gwm {
namespace hardware {
namespace camera {
namespace V1_0 {
namespace implementation {

using namespace vendor::gwm::hardware::camera::V1_0;

using ::android::sp;
using ::std::string;

DVRSomeipProxy::DVRSomeipProxy(android::sp<DVR> dvr)
    : mDVR(dvr)
{
    ALOGI("%s:  DVRSomeipProxy build.", __FUNCTION__);
}

DVRSomeipProxy::~DVRSomeipProxy()
{
}

void DVRSomeipProxy::setDVRCallback(const std::vector<android::sp<IDVRCallback>>& callbackList)
{
    mDVRCallbackList.assign(callbackList.begin(), callbackList.end());
}

GWM_Status DVRSomeipProxy::startPreview(GWM_DVRCameraId cameraId)
{
    if (mDVR == nullptr)
    {
        ALOGE("%s:  mDVR == nullptr !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    GWM_Status status = GWM_Status::GWM_ERROR;
    if (mDVR->checkIsReady(InterfaceType::FILE_OPERATION, __FUNCTION__))
    {
        SetResultVideoBrowseOut out;
        memset(&out, 0, sizeof(out));
        /**
         * @brief StartVideoBrowse comes from DVRFileOperation service of someip.
         * serviceid:0x0402
         * methodid: 0x0001
         */
        CallStatus_DT callStatus = StartVideoBrowseFunc(mDVR->switch_cameraid(cameraId), out);
        ALOGI("%s:  StartVideoBrowseFunc callStatus:%d, SetResultVideoBrowseOut:%d",
            __FUNCTION__,
            callStatus,
            out.videoBrowseACKDt);
        if (callStatus == CallStatus_DT::SUCCESS
            && out.videoBrowseACKDt == SetResult_DT::E_SUCCESSFUL)
        {
            status = GWM_Status::GWM_OK;
        }
    }

    if (mDVRCallbackList.size() == 0)
    {
        ALOGE("%s:  mDVRCallbackList is null !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    GWM_DVRPreviewReply mPreviewReply;
    memset(&mPreviewReply, 0, sizeof(mPreviewReply));
    mPreviewReply.rtsp_addr = "rtsp://193.18.1.200:50006/front";
    mPreviewReply.cameraId = cameraId;
    mPreviewReply.operation_type = GWM_DVRVideoOperateType::GWM_DVR_VIDEO_OPERATE_START;
    mPreviewReply.preview_result = (GWM_DVRReply)status;
    for(it = mDVRCallbackList.begin(); it != mDVRCallbackList.end(); ++it)
    {
        ALOGI("%s:  gwm_onDVRPreviewNotify, GWM_DVRPreviewReply[addr:%s, cameraId:%hu, preview_result:%hhu, operation_type:%hhu]",
            __FUNCTION__,
            mPreviewReply.rtsp_addr.c_str(),
            mPreviewReply.cameraId,
            mPreviewReply.preview_result,
            mPreviewReply.operation_type);
        auto ret = it->get()->gwm_onDVRPreviewNotify(mPreviewReply);
        if (!ret.isOk())
        {
            ALOGW("%s:  has error", __FUNCTION__);
        }
    }
    return status;
}

GWM_Status DVRSomeipProxy::stopPreview(GWM_DVRCameraId cameraId)
{
    if (mDVR == nullptr)
    {
        ALOGE("%s:  mDVR == nullptr !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    GWM_Status status = GWM_Status::GWM_ERROR;
    if (mDVR->checkIsReady(InterfaceType::FILE_OPERATION, __FUNCTION__))
    {
        SetResultVideoBrowseOut out;
        memset(&out, 0, sizeof(out));
        /**
         * @brief StopVideoBrowse comes from DVRFileOperation service of someip.
         * serviceid:0x0402
         * methodid: 0x0002
         */
        CallStatus_DT callStatus = StopVideoBrowseFunc(mDVR->switch_cameraid(cameraId), out);
        ALOGI("%s:  StopVideoBrowseFunc callStatus:%d, SetResultVideoBrowseOut:%d",
            __FUNCTION__,
            callStatus,
            out.videoBrowseACKDt);
        if (callStatus == CallStatus_DT::SUCCESS
            && out.videoBrowseACKDt == SetResult_DT::E_SUCCESSFUL)
        {
            status = GWM_Status::GWM_OK;
        }
    }

    if (mDVRCallbackList.size() == 0)
    {
        ALOGE("%s:  mDVRCallbackList is null !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    GWM_DVRPreviewReply mPreviewReply;
    memset(&mPreviewReply, 0, sizeof(mPreviewReply));
    mPreviewReply.rtsp_addr = "rtsp://193.18.1.200:50006/front";
    mPreviewReply.cameraId = cameraId;
    mPreviewReply.operation_type = GWM_DVRVideoOperateType::GWM_DVR_VIDEO_OPERATE_STOP;
    mPreviewReply.preview_result = (GWM_DVRReply)status;
    for(it = mDVRCallbackList.begin(); it != mDVRCallbackList.end(); ++it)
    {
        ALOGI("%s:  gwm_onDVRPreviewNotify, GWM_DVRPreviewReply[addr:%s, cameraId:%hu, preview_result:%hhu, operation_type:%hhu]",
            __FUNCTION__,
            mPreviewReply.rtsp_addr.c_str(),
            mPreviewReply.cameraId,
            mPreviewReply.preview_result,
            mPreviewReply.operation_type);
        auto ret = it->get()->gwm_onDVRPreviewNotify(mPreviewReply);
        if (!ret.isOk())
        {
            ALOGW("%s:  has error", __FUNCTION__);
        }
    }
    return status;
}

// invoke startRecord() in DVR.cpp
GWM_Status DVRSomeipProxy::startRecord(GWM_DVRCameraId cameraId, GWM_DVR_VIDEO_TYPE type)
{
    if (mDVR == nullptr)
    {
        ALOGE("%s:  mDVR == nullptr !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }
    return mDVR->startRecord(cameraId, type);
}

// invoke stopRecord() in DVR.cpp
GWM_Status DVRSomeipProxy::stopRecord(GWM_DVRCameraId cameraId, GWM_DVR_VIDEO_TYPE type)
{
    if (mDVR == nullptr)
    {
        ALOGE("%s:  mDVR == nullptr !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }
    return mDVR->stopRecord(cameraId, type);
}

// invoke startCapture() in DVR.cpp
GWM_Status DVRSomeipProxy::startCapture(GWM_DVRCameraId cameraId, GWM_DVR_VIDEO_TYPE type)
{
    if (mDVR == nullptr)
    {
        ALOGE("%s:  mDVR == nullptr !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }
    return mDVR->startCapture(cameraId, type);
}

// invoke startLapseVideo() in DVR.cpp
GWM_Status DVRSomeipProxy::startLapseVideo(GWM_DVRCameraId cameraId,
                            int64_t timeLapseVideoInteval,
                            int16_t totalFrameNumber,
                            int16_t playFrameNumber)
{
    if (mDVR == nullptr)
    {
        ALOGE("%s:  mDVR == nullptr !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }
    return mDVR->startLapseVideo(cameraId, timeLapseVideoInteval, totalFrameNumber, playFrameNumber);
}

// invoke stopLapseVideo() in DVR.cpp
GWM_Status DVRSomeipProxy::stopLapseVideo(GWM_DVRCameraId cameraId)
{
    if (mDVR == nullptr)
    {
        ALOGE("%s:  mDVR == nullptr !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }
    return mDVR->stopLapseVideo(cameraId);
}

GWM_Status DVRSomeipProxy::formatTFCard(GWM_DVR_TFCardId tfcard_id)
{
    if (mDVR == nullptr)
    {
        ALOGE("%s:  mDVR == nullptr !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    GWM_Status status = GWM_Status::GWM_ERROR;
    GWM_DVRReply reply = GWM_DVRReply::GWM_DVR_REPLY_ERROR;
    if (mDVR->checkIsReady(InterfaceType::FILE_OPERATION, __FUNCTION__))
    {
        SetResultTFCardFormatACKOut tfcard_out;
        memset(&tfcard_out, 0, sizeof(tfcard_out));
        /**
         * @brief SDCardFormat comes from DVRFileOperation service of someip.
         * serviceid:0x0402
         * methodid: 0x0004
         */
        CallStatus_DT callStatus = SDCardFormatFunc(E_SDCARD1, tfcard_out); // 默认走E_SDCARD1
        ALOGI("%s:  SDCardFormatFunc callStatus:%d, SetResultTFCardFormatACKOut:%d",
            __FUNCTION__,
            callStatus,
            tfcard_out.tFCardFormatACKDt);
        if (callStatus == CallStatus_DT::SUCCESS
            && tfcard_out.tFCardFormatACKDt == SetResult_DT::E_SUCCESSFUL)
        {
            status = GWM_Status::GWM_OK;
            reply = GWM_DVRReply::GWM_DVR_REPLY_OK;
        }
    }

    if (mDVRCallbackList.size() == 0)
    {
        ALOGE("%s:  mDVRCallbackList is null !", __FUNCTION__);
        return status;
    }

    GWM_DVRTFCardOperateEvent event;
    memset(&event, 0, sizeof(event));
    event.operation_type = GWM_DVR_TFCardOperateType::GWM_DVR_TFCARD_OPERATE_FORMAT;
    event.tfcard_id = tfcard_id;
    event.reply_result = reply;
    for(it = mDVRCallbackList.begin(); it != mDVRCallbackList.end(); ++it)
    {
        ALOGI("%s:  gwm_onDVRTFCardOperateNotify, GWM_DVRTFCardOperateEvent[operation_type:%hhu, tfcard_id:%hhu, reply_result:%hhu]",
            __FUNCTION__,
            event.operation_type,
            event.tfcard_id,
            event.reply_result);
        auto ret = it->get()->gwm_onDVRTFCardOperateNotify(event);
        if (!ret.isOk())
        {
            ALOGW("%s:  has error", __FUNCTION__);
        }
    }
    return status;
}

GWM_Status DVRSomeipProxy::resetFactory()
{
    if (mDVR == nullptr)
    {
        ALOGE("%s:  mDVR == nullptr !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    GWM_Status status = GWM_Status::GWM_ERROR;
    GWM_DVRReply reply = GWM_DVRReply::GWM_DVR_REPLY_ERROR;
    if (mDVR->checkIsReady(InterfaceType::SYSTEM_CONFIG, __FUNCTION__))
    {
        SetResultResetConfigOut reset_out;
        memset(&reset_out, 0, sizeof(reset_out));
        /**
         * @brief ResetDefaultConfig comes from DVRSystemConfig service of someip.
         * serviceid:0x0403
         * methodid: 0x0003
         */
        CallStatus_DT callStatus = ResetDefaultConfigFunc(E_RESUMEFACTORY, reset_out);
        ALOGI("%s:  ResetDefaultConfigFunc callStatus:%d, SetResultResetConfigOut:%d",
            __FUNCTION__,
            callStatus,
            reset_out.ResetConfigACK);
        if (callStatus == CallStatus_DT::SUCCESS
            && reset_out.ResetConfigACK == SetResult_DT::E_SUCCESSFUL)
        {
            status = GWM_Status::GWM_OK;
            reply = GWM_DVRReply::GWM_DVR_REPLY_OK;
        }
    }

    if (mDVRCallbackList.size() == 0)
    {
        ALOGE("%s:  mDVRCallbackList is null !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    for(it = mDVRCallbackList.begin(); it != mDVRCallbackList.end(); ++it)
    {
        ALOGI("%s:  gwm_onDVRResetFactoryNotify, reply:%hhu", __FUNCTION__, reply);
        auto ret = it->get()->gwm_onDVRResetFactoryNotify(reply);
        if (!ret.isOk())
        {
            ALOGW("%s:  has error", __FUNCTION__);
        }
    }
    return status;
}

// invoke querySystemStatus() in DVR.cpp
GWM_Status DVRSomeipProxy::querySystemInfoFromExtDVR()
{
    if (mDVR == nullptr)
    {
        ALOGE("%s:  mDVR == nullptr !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }
    return mDVR->querySystemStatus();
}

GWM_Status DVRSomeipProxy::setParam(const GWM_DVRSetParam &params)
{
    /*
     * setup_bit_flag :
     *  GWM_DVR_SETUP_TEYPE_NULL                = 0,
     *  GWM_DVR_RECORD_OUTSIDE_SOUNDS           = 1,
     *  GWM_DVR_TURN_ON_WIDE_DYNAMIC            = 2,
     *  GWM_DVR_RECORD_TIME                     = 4,
     *  GWM_DVR_DELAY_SHUTDOW                   = 8,
     *  GWM_DVR_RECORD_AUTOMATICAL_OVERWRITE    = 16,
     *  GWM_DVR_RECORD_SWITCH                   = 32,
     *  GWM_DVR_PARKING_MONITORING              = 64,
     *  GWM_DVR_QUERY_TFCARD1_INFOR             = 128,
     *  GWM_DVR_QUERY_TFCARD2_INFOR             = 256,
     *  GWM_DVR_360_VIDEO_SWITCH                = 512,
     *  GWM_DVR_INCAR_VIDEO_SWITCH              = 1024,
     *  GWM_DVR_SET_OSD_INFO_SWITCH             = 2048
     */
    uint64_t bit = params.setup_bit_flag;
    uint32_t states[11];
    uint32_t num = 0;
    for (uint32_t i = 0; i < 12; i++)
    {
        if (bit & (1U << i))
        {
            states[i] = 1U;
        }
        else
        {
            states[i] = 0;
        }
        num += states[i];
        ALOGD("%s:  states %d:%d ", __FUNCTION__, i, states[i]);
    }
    ALOGI("%s:  setup_bit_flag:%lu, num:%d", __FUNCTION__, bit, num);

    GWM_Status status = GWM_Status::GWM_ERROR;
    if (num != 0)
    {
        ConfigListArrayInput input_bean;
        memset(&input_bean, 0, sizeof(input_bean));
        uint32_t count = 0;
        for (int32_t i = 0; i < 12; i++)
        {
            if (states[i])
            {
                ParamCofigStruct_DT dt;
                memset(&dt, 0, sizeof(dt));
                dt.configParamValueTypeDt = E_ENUM;
                setParamCofigStructDT(i, params, dt);
                ALOGD("%s:  states input[i:%d, value:%d]", __FUNCTION__, i, dt.paramConfigOperationDt);
                input_bean.dynamicArray.push_back(dt);
                count++;
            }
        }

        if (mDVR == nullptr)
        {
            ALOGE("%s:  mDVR == nullptr !", __FUNCTION__);
            return GWM_Status::GWM_ERROR;
        }
        SetResultOut out;
        memset(&out, 0, sizeof(out));
        if (mDVR->checkIsReady(InterfaceType::SYSTEM_CONFIG, __FUNCTION__))
        {
            /**
             * @brief DVRSetConfig comes from DVRSystemConfig service of someip.
             * serviceid:0x0403
             * methodid: 0x0001
             */
            CallStatus_DT callStatus = DVRSetConfig(input_bean, out);
            ALOGI("%s:  DVRSetConfig callStatus:%d, SetResultOut:%d",
                __FUNCTION__,
                callStatus,
                out.ParamConfigResult);
            if (callStatus == CallStatus_DT::SUCCESS
                && out.ParamConfigResult == E_SUCCESSFUL)
            {
                status = GWM_Status::GWM_OK;
            }
        }

        GWM_DVRSetParamReply reply;
        memset(&reply, 0, sizeof(reply));
        reply.set_bit_flag = bit;
        if (status == GWM_Status::GWM_OK)
        {
            reply.sounds_enable_reply = GWM_DVRReply::GWM_DVR_REPLY_OK;
            reply.wide_dynamic_enable_reply = GWM_DVRReply::GWM_DVR_REPLY_OK;
            reply.automatical_overwrite__enable_reply = GWM_DVRReply::GWM_DVR_REPLY_OK;
            reply.dvr_enable_reply = GWM_DVRReply::GWM_DVR_REPLY_OK;
            reply.paking_monitoring_enable_reply = GWM_DVRReply::GWM_DVR_REPLY_OK;
            reply.avm_enable_reply = GWM_DVRReply::GWM_DVR_REPLY_OK;
            reply.delay_shutdown_reply = GWM_DVRReply::GWM_DVR_REPLY_OK;
            reply.record_time_reply = GWM_DVRReply::GWM_DVR_REPLY_OK;
            reply.incar_camera_enable_reply = GWM_DVRReply::GWM_DVR_REPLY_OK;
            reply.set_osd_info_reply = GWM_DVRReply::GWM_DVR_REPLY_OK;
        }
        else
        {
            reply.sounds_enable_reply = GWM_DVRReply::GWM_DVR_REPLY_ERROR;
            reply.wide_dynamic_enable_reply = GWM_DVRReply::GWM_DVR_REPLY_ERROR;
            reply.automatical_overwrite__enable_reply = GWM_DVRReply::GWM_DVR_REPLY_ERROR;
            reply.dvr_enable_reply = GWM_DVRReply::GWM_DVR_REPLY_ERROR;
            reply.paking_monitoring_enable_reply = GWM_DVRReply::GWM_DVR_REPLY_ERROR;
            reply.avm_enable_reply = GWM_DVRReply::GWM_DVR_REPLY_ERROR;
            reply.delay_shutdown_reply = GWM_DVRReply::GWM_DVR_REPLY_ERROR;
            reply.record_time_reply = GWM_DVRReply::GWM_DVR_REPLY_ERROR;
            reply.incar_camera_enable_reply = GWM_DVRReply::GWM_DVR_REPLY_ERROR;
            reply.set_osd_info_reply = GWM_DVRReply::GWM_DVR_REPLY_ERROR;
        }

        if (mDVRCallbackList.size() == 0)
        {
            ALOGE("%s:  mDVRCallbackList is null !", __FUNCTION__);
            return GWM_Status::GWM_ERROR;
        }

        for(it = mDVRCallbackList.begin(); it != mDVRCallbackList.end(); ++it)
        {
            ALOGI("%s:  gwm_onSetParameterNotify, SetResultOut:%d, status:%d", __FUNCTION__, out.ParamConfigResult, status);
            auto ret = it->get()->gwm_onSetParameterNotify(reply);
            if (!ret.isOk())
            {
                ALOGW("%s:  has error", __FUNCTION__);
            }
        }
    }
    return status;
}

GWM_Status DVRSomeipProxy::getParam()
{
    if (mDVR == nullptr)
    {
        ALOGE("%s:  mDVR == nullptr !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    GWM_Status status = GWM_Status::GWM_ERROR;
    ConfigListArrayOut out;
    memset(&out, 0, sizeof(out));
    if (mDVR->checkIsReady(InterfaceType::SYSTEM_CONFIG, __FUNCTION__))
    {
        ConfigTypeList config_bean;
        memset(&config_bean, 0, sizeof(config_bean));
        /**
         * @brief DVRGetConfig comes from DVRSystemConfig service of someip.
         * serviceid:0x0403
         * methodid: 0x0002
         */
        CallStatus_DT callStatus = DVRGetConfigFunc(E_GET_ALL_CONFIG, config_bean, out);
        ALOGI("%s:  DVRGetConfigFunc callStatus:%d, ConfigListArrayOut:%lu",
            __FUNCTION__,
            callStatus,
            out.dynamicArray.size());
        if (callStatus == CallStatus_DT::SUCCESS
            && out.dynamicArray.size() != 0)
        {
            status = GWM_Status::GWM_OK;
        }
    }

    GWM_DVRGetParam params;
    memset(&params, 0, sizeof(params));
    if (status == GWM_Status::GWM_OK)
    {
        for (uint32_t i = 0; i < out.dynamicArray.size(); i++)
        {
            ParamCofigStruct_DT dt = out.dynamicArray[i];
            ALOGD("%s:  params[i:%d, type:%d, value:%d]",
                __FUNCTION__,
                i,
                dt.paramConfigTypeDt,
                dt.paramConfigOperationDt);
            setDVRGetParam(dt, params);
        }
    }
    else
    {
        params.wide_dynamic_enable_status = GWM_DVRStatus::GWM_DVR_STATUS_NULL;
        params.record_time = (uint32_t)60;
        params.delay_shutdown = (uint32_t)0;
        params.automatical_overwrite__enable_status = GWM_DVRStatus::GWM_DVR_STATUS_NULL;
        params.sounds_enable_status = GWM_DVRStatus::GWM_DVR_STATUS_NULL;
        params.dvr_enable_status = GWM_DVRStatus::GWM_DVR_STATUS_NULL;
        params.incar_camera_enable_status = GWM_DVRStatus::GWM_DVR_STATUS_NULL;
        params.avm_enable_status = GWM_DVRStatus::GWM_DVR_STATUS_NULL;
        params.paking_monitoring_enable_status = GWM_DVRStatus::GWM_DVR_STATUS_NULL;
        params.set_osd_info_status = GWM_DVRStatus::GWM_DVR_STATUS_NULL;
    }

    if (mDVRCallbackList.size() == 0)
    {
        ALOGE("%s:  mDVRCallbackList is null !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    for(it = mDVRCallbackList.begin(); it != mDVRCallbackList.end(); ++it)
    {
        ALOGI("%s:  gwm_onGetParameterNotify params[wideDynamicStatus:%hhu, recordTime:%d, delayShutdown:%d, automaticalOverwriteStatus:%hhu, soundsStatus:%hhu, dvrStatus:%hhu, incarCameraStatus:%hhu, avmStatus:%hhu, pakingMonitoringStatus:%hhu, setOsdInfoStatus:%hhu]",
            __FUNCTION__,
            params.wide_dynamic_enable_status,
            params.record_time,
            params.delay_shutdown,
            params.automatical_overwrite__enable_status,
            params.sounds_enable_status,
            params.dvr_enable_status,
            params.incar_camera_enable_status,
            params.avm_enable_status,
            params.paking_monitoring_enable_status,
            params.set_osd_info_status);
        auto ret = it->get()->gwm_onGetParameterNotify(params);
        if (!ret.isOk())
        {
            ALOGW("%s:  has error", __FUNCTION__);
        }
    }
    return status;
}

GWM_Status DVRSomeipProxy::fileListRequest(const GWM_DVRFileListREQ &query_file_list)
{
    if (mDVR == nullptr)
    {
        ALOGE("%s:  mDVR == nullptr !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    GWM_Status status = GWM_Status::GWM_ERROR;
    FileListStructArrayOut out;
    memset(&out, 0, sizeof(out));
    if (mDVR->checkIsReady(InterfaceType::FILE_OPERATION, __FUNCTION__))
    {
        FileType_DT fileType = (FileType_DT)query_file_list.operation_type;
        AccessType_DT accessType = mDVR->switch_cameraid(query_file_list.camera_id);
        FileNumber fileNumber = query_file_list.file_sum;
        /**
         * @brief FileListRequest comes from DVRFileOperation service of someip.
         * serviceid:0x0402
         * methodid: 0x0003
         */
        CallStatus_DT callStatus = FileListRequestFunc(fileType, accessType, fileNumber, query_file_list.last_file_name.c_str(), out);
        ALOGI("%s:  FileListRequestFunc callStatus:%d, fileListSize:%lu",
            __FUNCTION__,
            callStatus,
            out.dynamicArray.size());
        if (callStatus == CallStatus_DT::SUCCESS
            && out.dynamicArray.size() != 0)
        {
            status = GWM_Status::GWM_OK;
        }
    }

    std::vector<GWM_DVRFileListResult> vec_quest_result;
    memset(&vec_quest_result, 0, sizeof(vec_quest_result));
    setFileListResult(status, query_file_list, out, vec_quest_result);

    if (mDVRCallbackList.size() == 0)
    {
        ALOGE("%s:  mDVRCallbackList is null !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    for(it = mDVRCallbackList.begin(); it != mDVRCallbackList.end(); ++it)
    {
        ALOGI("%s:  gwm_onDVRQueryFileListNotify, filenumber:%d, filename:%s",
            __FUNCTION__,
            query_file_list.file_sum,
            query_file_list.last_file_name.c_str());
        auto ret = it->get()->gwm_onDVRQueryFileListNotify(vec_quest_result);
        if (!ret.isOk())
        {
            ALOGW("%s:  has error", __FUNCTION__);
        }
    }
    return status;
}

GWM_Status DVRSomeipProxy::deleteFileList(const std::vector<std::string>& file_path_url)
{
    if (mDVR == nullptr)
    {
        ALOGE("%s:  mDVR == nullptr !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    FileListPath_DT dt;
    memset(&dt, 0, sizeof(dt));
    for (uint32_t i = 0; i < file_path_url.size(); i++)
    {
        ALOGD("%s:  path:%s", __FUNCTION__, file_path_url[i].c_str());
        dt.filePath.push_back(file_path_url[i]);
    }

    GWM_Status status = GWM_Status::GWM_ERROR;
    GWM_DVRFileOperateResult result = GWM_DVRFileOperateResult::GWM_Fail;
    if (mDVR->checkIsReady(InterfaceType::FILE_OPERATION, __FUNCTION__))
    {
        SetResultFileDeleteACKOut out;
        memset(&out, 0, sizeof(out));
        /**
         * @brief FileDeleteRequest comes from DVRFileOperation service of someip.
         * serviceid:0x0402
         * methodid: 0x0005
         */
        CallStatus_DT callStatus = FileDeleteRequestFunc(dt, out);
        ALOGI("%s:  FileDeleteRequestFunc callStatus:%d, SetResultFileDeleteACKOut:%d",
            __FUNCTION__,
            callStatus,
            out.fileDeleteACKDt);
        if (callStatus == CallStatus_DT::SUCCESS)
        {
            status = GWM_Status::GWM_OK;
            result = (GWM_DVRFileOperateResult)out.fileDeleteACKDt;
        }
    }

    if (mDVRCallbackList.size() == 0)
    {
        ALOGE("%s:  mDVRCallbackList is null !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    for(it = mDVRCallbackList.begin(); it != mDVRCallbackList.end(); ++it)
    {
        ALOGI("%s:  gwm_onDVRFileStatusNotify, result:%hhu",
            __FUNCTION__,
            result);
        auto ret = it->get()->gwm_onDVRFileStatusNotify(result);
        if (!ret.isOk())
        {
            ALOGW("%s:  has error", __FUNCTION__);
        }
    }
    return status;
}

GWM_Status DVRSomeipProxy::allFiledelete(GWM_DVRCameraId cameraId, GWM_DVRFileType file_type)
{
    if (mDVR == nullptr)
    {
        ALOGE("%s:  mDVR == nullptr !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    GWM_Status status = GWM_Status::GWM_ERROR;
    GWM_DVRFileOperateResult result = GWM_DVRFileOperateResult::GWM_Fail;
    if (mDVR->checkIsReady(InterfaceType::FILE_OPERATION, __FUNCTION__))
    {
        SetResultFileDeleteACKOut out;
        memset(&out, 0, sizeof(out));
        /**
         * @brief AllFileDeleteRequest comes from DVRFileOperation service of someip.
         * serviceid:0x0402
         * methodid: 0x000B
         */
        CallStatus_DT callStatus = AllFileDeleteRequestFunc(mDVR->switch_cameraid(cameraId), (FileType_DT)file_type, out);
        ALOGI("%s:  AllFileDeleteRequestFunc cameraId:%hu, file_type:%hhu, callStatus:%d, SetResultFileDeleteACKOut:%d",
            __FUNCTION__,
            cameraId,
            file_type,
            callStatus,
            out.fileDeleteACKDt);
        if (callStatus == CallStatus_DT::SUCCESS)
        {
            status = GWM_Status::GWM_OK;
            result = (GWM_DVRFileOperateResult)out.fileDeleteACKDt;
        }
    }

    if (mDVRCallbackList.size() == 0)
    {
        ALOGE("%s:  mDVRCallbackList is null !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    for(it = mDVRCallbackList.begin(); it != mDVRCallbackList.end(); ++it)
    {
        ALOGI("%s:  gwm_onDVRFileStatusNotify, result:%hhu",
            __FUNCTION__,
            result);
        auto ret = it->get()->gwm_onDVRFileStatusNotify(result);
        if (!ret.isOk())
        {
            ALOGW("%s:  has error", __FUNCTION__);
        }
    }
    return status;
}

GWM_Status DVRSomeipProxy::asyncAllFiledelete(GWM_DVRCameraId cameraId, GWM_DVRFileType file_type)
{
    if (mDVR == nullptr)
    {
        ALOGE("%s:  mDVR == nullptr !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    GWM_Status status = GWM_Status::GWM_ERROR;
    if (mDVR->checkIsReady(InterfaceType::FILE_OPERATION, __FUNCTION__))
    {
        SetResultFileDeleteACKOut out;
        memset(&out, 0, sizeof(out));
        /**
         * @brief AsyncAllFileDeleteRequest comes from DVRFileOperation service of someip.
         * serviceid:0x0402
         * methodid: 0x0010
         */
        CallStatus_DT callStatus = AsyncAllFileDeleteRequestFuc(mDVR->switch_cameraid(cameraId), (FileType_DT)file_type, out);
        ALOGI("%s:  AsyncAllFileDeleteRequestFuc cameraId:%hu, file_type:%hhu, callStatus:%d, SetResultFileDeleteACKOut:%d",
            __FUNCTION__,
            cameraId,
            file_type,
            callStatus,
            out.fileDeleteACKDt);
        if (callStatus == CallStatus_DT::SUCCESS)
        {
            status = GWM_Status::GWM_OK;
        }
    }

    return status;
}

GWM_Status DVRSomeipProxy::stopAsyncAllFiledelete(GWM_DVRCameraId cameraId)
{
    if (mDVR == nullptr)
    {
        ALOGE("%s:  mDVR == nullptr !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    GWM_Status status = GWM_Status::GWM_ERROR;
    GWM_DVRFileOperateResult result = GWM_DVRFileOperateResult::GWM_Fail;
    if (mDVR->checkIsReady(InterfaceType::FILE_OPERATION, __FUNCTION__))
    {
        SetResultManualOperationACKOut out;
        memset(&out, 0, sizeof(out));
        /**
         * @brief DVRManualOperation comes from DVRStatusReport service of someip.
         * serviceid:0x0401
         * methodid: 0x0002
         */
        CallStatus_DT callStatus = DVRManualOperationFunc(ManualOperation_DT::E_STOPASYNCDELETEFILE, mDVR->switch_cameraid(cameraId), out);
        ALOGI("%s:  DVRManualOperationFunc cameraId:%hu, callStatus:%d, SetResultManualOperationACKOut:%d",
            __FUNCTION__,
            cameraId,
            callStatus,
            out.manualOperationACK);
        if (callStatus == CallStatus_DT::SUCCESS)
        {
            status = GWM_Status::GWM_OK;
            result = (GWM_DVRFileOperateResult)out.manualOperationACK;
        }
    }

    if (mDVRCallbackList.size() == 0)
    {
        ALOGE("%s:  mDVRCallbackList is null !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    for(it = mDVRCallbackList.begin(); it != mDVRCallbackList.end(); ++it)
    {
        ALOGI("%s:  gwm_onDVRStopAsyncAllFileDeleteStatusNotify, result:%hhu",
            __FUNCTION__,
            result);
        auto ret = it->get()->gwm_onDVRStopAsyncAllFileDeleteStatusNotify(result);
        if (!ret.isOk())
        {
            ALOGW("%s:  has error", __FUNCTION__);
        }
    }

    return status;
}

GWM_Status DVRSomeipProxy::exportFileList(GWM_DVRExportType export_type, const std::vector<std::string>& file_path_url)
{
    if (mDVR == nullptr)
    {
        ALOGE("%s:  mDVR == nullptr !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    FileListPath_DT dt;
    memset(&dt, 0, sizeof(dt));
    for (uint32_t i = 0; i < file_path_url.size(); i++)
    {
        ALOGD("%s:  export_type:%hhu, path:%s",
              __FUNCTION__,
              export_type,
              file_path_url[i].c_str());
        dt.filePath.push_back(file_path_url[i]);
    }

    for (auto path : dt.filePath)
    {
        ALOGD("%s:  FileExportRequestFunc, size:%lu, path:%s", __FUNCTION__, dt.filePath.size(), path.c_str());
    }

    GWM_Status status = GWM_Status::GWM_ERROR;
    GWM_DVRFileExportStatus exportStatus = GWM_DVRFileExportStatus::GWM_File_Missing;
    ExportFileACKOut out;
    memset(&out, 0, sizeof(out));
    if (mDVR->checkIsReady(InterfaceType::FILE_OPERATION, __FUNCTION__))
    {
        /**
         * @brief FileExportRequest comes from DVRFileOperation service of someip.
         * serviceid:0x0402
         * methodid: 0x0007
         */
        CallStatus_DT callStatus = FileExportRequestFunc((ExportMode_DT)export_type, dt, out);
        ALOGI("%s:  FileExportRequestFunc callStatus:%d, ExportFileACKOut:%d",
            __FUNCTION__,
            callStatus,
            out.exportFileACKDt);
        if (callStatus == CallStatus_DT::SUCCESS)
        {
            status = GWM_Status::GWM_OK;
            exportStatus = (GWM_DVRFileExportStatus)out.exportFileACKDt;
        }
    }

    if (mDVRCallbackList.size() == 0)
    {
        ALOGE("%s:  mDVRCallbackList is null !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    for(it = mDVRCallbackList.begin(); it != mDVRCallbackList.end(); ++it)
    {
        ALOGI("%s:  gwm_onDVRFileExportStatusNotify, export_type:%hhu, exportStatus:%hhu",
            __FUNCTION__,
            export_type,
            exportStatus);
        auto ret = it->get()->gwm_onDVRFileExportStatusNotify(exportStatus);
        if (!ret.isOk())
        {
            ALOGW("%s:  has error", __FUNCTION__);
        }
    }
    return status;
}

GWM_Status DVRSomeipProxy::allFileExport(GWM_DVRExportType export_type, GWM_DVRCameraId cameraId, GWM_DVRFileType file_type)
{
    if (mDVR == nullptr)
    {
        ALOGE("%s:  mDVR == nullptr !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    GWM_Status status = GWM_Status::GWM_ERROR;
    GWM_DVRFileExportStatus exportStatus = GWM_DVRFileExportStatus::GWM_File_Missing;
    ExportFileACKOut out;
    memset(&out, 0, sizeof(out));
    if (mDVR->checkIsReady(InterfaceType::FILE_OPERATION, __FUNCTION__))
    {
        /**
         * @brief AllFileExportRequest comes from DVRFileOperation service of someip.
         * serviceid:0x0402
         * methodid: 0x000D
         */
        CallStatus_DT callStatus = AllFileExportRequestFunc((ExportMode_DT)export_type, mDVR->switch_cameraid(cameraId), (FileType_DT)file_type, out);
        ALOGI("%s:  AllFileExportRequestFunc callStatus:%d, ExportFileACKOut:%d",
            __FUNCTION__,
            callStatus,
            out.exportFileACKDt);
        if (callStatus == CallStatus_DT::SUCCESS)
        {
            status = GWM_Status::GWM_OK;
            exportStatus = (GWM_DVRFileExportStatus)out.exportFileACKDt;
        }
    }

    if (mDVRCallbackList.size() == 0)
    {
        ALOGE("%s:  mDVRCallbackList is null !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    for(it = mDVRCallbackList.begin(); it != mDVRCallbackList.end(); ++it)
    {
        ALOGI("%s:  gwm_onDVRFileExportStatusNotify, export_type:%hhu, cameraId:%hu, file_type:%hhu, exportStatus:%hhu",
            __FUNCTION__,
            export_type,
            cameraId,
            file_type,
            exportStatus);
        auto ret = it->get()->gwm_onDVRFileExportStatusNotify(exportStatus);
        if (!ret.isOk())
        {
            ALOGW("%s:  has error", __FUNCTION__);
        }
    }
    return status;
}

GWM_Status DVRSomeipProxy::cancelFilesExport(GWM_DVRCameraId camera_id)
{
    if (mDVR == nullptr)
    {
        ALOGE("%s:  mDVR == nullptr !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    GWM_Status status = GWM_Status::GWM_ERROR;
    GWM_DVRFileOperateResult result = GWM_DVRFileOperateResult::GWM_Fail;
    SetResultManualOperationACKOut out;
    memset(&out, 0, sizeof(out));
    if (mDVR->checkIsReady(InterfaceType::STATUS_REPORT, __FUNCTION__))
    {
        /**
         * @brief DVRManualOperation comes from DVRStatusReport service of someip.
         * serviceid:0x0401
         * methodid: 0x0002
         */
        CallStatus_DT callStatus = DVRManualOperationFunc(ManualOperation_DT::E_STOPEXPORTFILE, mDVR->switch_cameraid(camera_id), out);
        ALOGI("%s:  DVRManualOperationFunc callStatus:%d, SetResultManualOperationACKOut:%d",
            __FUNCTION__,
            callStatus,
            out.manualOperationACK);
        if (callStatus == CallStatus_DT::SUCCESS)
        {
            status = GWM_Status::GWM_OK;
            result = (GWM_DVRFileOperateResult)out.manualOperationACK;
        }
    }

    if (mDVRCallbackList.size() == 0)
    {
        ALOGE("%s:  mDVRCallbackList is null !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    for(it = mDVRCallbackList.begin(); it != mDVRCallbackList.end(); ++it)
    {
        ALOGI("%s:  gwm_onDVRCancelFileExportStatusNotify, result:%hhu",
            __FUNCTION__,
            result);
        auto ret = it->get()->gwm_onDVRCancelFileExportStatusNotify(result);
        if (!ret.isOk())
        {
            ALOGW("%s:  has error", __FUNCTION__);
        }
    }
    return status;
}

// invoke exportFileCapacity() in DVR.cpp
int32_t DVRSomeipProxy::exportFileCapacity(const std::vector<std::string>& file_path_url)
{
    if (mDVR == nullptr)
    {
        ALOGE("%s:  mDVR == nullptr !", __FUNCTION__);
        return -1;
    }
    return mDVR->exportFileCapacity(file_path_url, false);
}

// invoke selectAllFileCapacity() in DVR.cpp
int32_t DVRSomeipProxy::selectAllFileCapacity(GWM_DVRCameraId camera_id,
    GWM_DVRFileType file_type)
{
    if (mDVR == nullptr)
    {
        ALOGE("%s:  mDVR == nullptr !", __FUNCTION__);
        return -1;
    }
    return mDVR->selectAllFileCapacity(camera_id, file_type, false);
}

GWM_Status DVRSomeipProxy::emmcStatusRequest()
{
    if (mDVR == nullptr)
    {
        ALOGE("%s:  mDVR == nullptr !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    GWM_Status status = GWM_Status::GWM_ERROR;
    EMMCStatus_DT EMMCStatus = EMMCStatus_DT::E_EMMCNORMAL;
    EMMCCapacityStructOut out;
    memset(&out, 0, sizeof(out));
    if (mDVR->checkIsReady(InterfaceType::FILE_OPERATION, __FUNCTION__))
    {
        /**
         * @brief EMMCInfoQuery comes from DVRFileOperation service of someip.
         * serviceid:0x0402
         * methodid: 0x0008
         */
        CallStatus_DT callStatus = EMMCInfoQueryFunc(E_GET_ALL_INFO, EMMCStatus, out);
        ALOGI("%s:  EMMCInfoQueryFunc callStatus:%d, EMMCCapacityStructOut-Size:%lu",
            __FUNCTION__,
            callStatus,
            out.dynamicList.size());
        if (callStatus == CallStatus_DT::SUCCESS
            && out.dynamicList.size() != 0)
        {
            status = GWM_Status::GWM_OK;
        }
    }

    GWM_DVREMMCReport emmc_report;
    memset(&emmc_report, 0, sizeof(emmc_report));
    emmc_report.emmc_status = (GWM_DVREMMCStatus)EMMCStatus;
    if (status == GWM_Status::GWM_OK)
    {
        emmc_report.TotalCapacity = out.dynamicList[0].totalCapacity;
        emmc_report.RemainingCapacity = out.dynamicList[0].remainingCapacity;
    }
    else
    {
        emmc_report.TotalCapacity = 0;
        emmc_report.RemainingCapacity = 0;
    }

    if (mDVRCallbackList.size() == 0)
    {
        ALOGE("%s:  mDVRCallbackList is null !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    for(it = mDVRCallbackList.begin(); it != mDVRCallbackList.end(); ++it)
    {
        ALOGI("%s:  gwm_onDVREMMCStatusNotify, total:%d, remaining:%d",
            __FUNCTION__,
            emmc_report.TotalCapacity,
            emmc_report.RemainingCapacity);
        auto ret = it->get()->gwm_onDVREMMCStatusNotify(emmc_report);
        if (!ret.isOk())
        {
            ALOGW("%s:  has error", __FUNCTION__);
        }
    }
    return status;
}

GWM_Status DVRSomeipProxy::tfCardStatusRequest(GWM_DVR_TFCardId tfcard_id)
{
    if (mDVR == nullptr)
    {
        ALOGE("%s:  mDVR == nullptr !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    GWM_Status status = GWM_Status::GWM_ERROR;
    TFCardInfoListOut out;
    memset(&out, 0, sizeof(out));
    if (mDVR->checkIsReady(InterfaceType::FILE_OPERATION, __FUNCTION__))
    {
        TFCardOptionList list;
        memset(&list, 0, sizeof(list));
        TFCardOptionList_DT dt_list;
        memset(&dt_list, 0, sizeof(dt_list));
        TFCardOption_DT dt = TFCardOption_DT::E_TFCARD1;
        if (tfcard_id == GWM_DVR_TFCardId::GWM_DVR_TFCARD_INCAR)
        {
            dt = TFCardOption_DT::E_TFCARD2;
        }
        dt_list.tfCardOptionDt = dt;
        list.dynamicList.push_back(dt_list);
        /**
         * @brief TFCardInfoQuery comes from DVRFileOperation service of someip.
         * serviceid:0x0402
         * methodid: 0x0006
         */
        CallStatus_DT callStatus = TFCardInfoQueryFunc(E_GET_ARRAY_INFO, list, out);
        ALOGI("%s:  TFCardInfoQueryFunc callStatus:%d, TFCardInfoListOut-Size:%lu",
            __FUNCTION__,
            callStatus,
            out.dynamicList.size());
        if (callStatus == CallStatus_DT::SUCCESS
            && out.dynamicList.size() != 0)
        {
            status = GWM_Status::GWM_OK;
        }
    }

    TFCardOption_DT dt_opt = TFCardOption_DT::E_TFCARD1;
    TFCardStatus_DT dt_status = TFCardStatus_DT::E_DVR_NOT_FOUND;
    if (status == GWM_Status::GWM_OK)
    {
        dt_opt = out.dynamicList[0].tfCardOptionDt;
        dt_status = out.dynamicList[0].tfCardStatusDt;
    }
    GWM_DVRTFCardStatus dvr_tfcard_status;
    memset(&dvr_tfcard_status, 0, sizeof(dvr_tfcard_status));
    dvr_tfcard_status.tfcard_id = (GWM_DVR_TFCardId)dt_opt;
    setDVRTFCardStatus(dt_status, dvr_tfcard_status);

    if (mDVRCallbackList.size() == 0)
    {
        ALOGE("%s:  mDVRCallbackList is null !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    for(it = mDVRCallbackList.begin(); it != mDVRCallbackList.end(); ++it)
    {
        ALOGI("%s:  gwm_onDVRTFCardStatusNotify, tfcard_id:%hhu, tfCardOptionDt:%d, tfCardStatusDt:%d, tfcard_status:%hhu",
            __FUNCTION__,
            tfcard_id,
            dt_opt,
            dt_status,
            dvr_tfcard_status.tfcard_status);
        auto ret = it->get()->gwm_onDVRTFCardStatusNotify(dvr_tfcard_status);
        if (!ret.isOk())
        {
            ALOGW("%s:  has error", __FUNCTION__);
        }
    }
    return status;
}

GWM_Status DVRSomeipProxy::tfCardCapacityRequest(GWM_DVR_TFCardId tfcard_id)
{
    if (mDVR == nullptr)
    {
        ALOGE("%s:  mDVR == nullptr !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    CallStatus_DT callStatus = CallStatus_DT::UNKNOWN;
    TFCardInfoListOut out;
    memset(&out, 0, sizeof(out));
    TFCardCapacity_DT dt_capa;
    memset(&dt_capa, 0, sizeof(dt_capa));
    bool isTFCardInfoQuerySuccess = false;
    if (mDVR->checkIsReady(InterfaceType::FILE_OPERATION, __FUNCTION__))
    {
        TFCardOptionList list;
        memset(&list, 0, sizeof(list));
        TFCardOptionList_DT dt_list;
        memset(&dt_list, 0, sizeof(dt_list));
        TFCardOption_DT dt = TFCardOption_DT::E_TFCARD1;
        if (tfcard_id == GWM_DVR_TFCardId::GWM_DVR_TFCARD_INCAR)
        {
            dt = TFCardOption_DT::E_TFCARD2;
        }
        dt_list.tfCardOptionDt = dt;
        list.dynamicList.push_back(dt_list);
        /**
         * @brief TFCardInfoQuery comes from DVRFileOperation service of someip.
         * serviceid:0x0402
         * methodid: 0x0006
         */
        callStatus = TFCardInfoQueryFunc(E_GET_ARRAY_INFO, list, out);
        ALOGI("%s:  TFCardInfoQueryFunc callStatus:%d, TFCardInfoListOut-Size:%lu",
            __FUNCTION__,
            callStatus,
            out.dynamicList.size());
        if (callStatus == CallStatus_DT::SUCCESS
            && out.dynamicList.size() != 0)
        {
            isTFCardInfoQuerySuccess = true;
            dt_capa = out.dynamicList[0].tfCardCapacityDt;
        }
    }

    bool isTFCardExportCapacityQuerySuccess = false;
    TotalExportCapacity totalExportCapacity = 0;
    FreeExportCapacity freeExportCapacity = 0;
    if (mDVR->checkIsReady(InterfaceType::STATUS_REPORT, __FUNCTION__))
    {
        /**
         * @brief TFCardExportCapacityQuery comes from DVRStatusReport service of someip.
         * serviceid:0x0401
         * methodid: 0x0008
         */
        callStatus = TFCardExportCapacityQueryFuc(E_TFCARD1, totalExportCapacity, freeExportCapacity);
        ALOGI("%s:  TFCardExportCapacityQueryFuc callStatus:%d, totalExportCapacity:%u, freeExportCapacity:%u !",
            __FUNCTION__,
            callStatus,
            totalExportCapacity,
            freeExportCapacity);
        if (callStatus == CallStatus_DT::SUCCESS)
        {
            isTFCardExportCapacityQuerySuccess = true;
        }
    }

    GWM_Status status = GWM_Status::GWM_ERROR;
    GWM_DVRTFCardCapacityCostStatus capacity_status;
    memset(&capacity_status, 0, sizeof(capacity_status));
    capacity_status.tfcard_id = tfcard_id;
    capacity_status.loop_capacity = 0;
    capacity_status.emergency_capacity = 0;
    capacity_status.user_capacity = 0;
    if (isTFCardInfoQuerySuccess && isTFCardExportCapacityQuerySuccess)
    {
        status = GWM_Status::GWM_OK;
        capacity_status.total_capacity = (float)dt_capa.totalCapacity;
        capacity_status.used_capacity = (float)(dt_capa.totalCapacity - dt_capa.remainingCapacity);
        capacity_status.total_export_capacity = (float)totalExportCapacity;
        capacity_status.free_export_capacity = (float)freeExportCapacity;
    }
    else
    {
        ALOGW("%s:  capacity_status is error !", __FUNCTION__);
        capacity_status.total_capacity = 0;
        capacity_status.used_capacity = 0;
        capacity_status.total_export_capacity = 0;
        capacity_status.free_export_capacity = 0;
    }

    if (mDVRCallbackList.size() == 0)
    {
        ALOGE("%s:  mDVRCallbackList is null !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    for(it = mDVRCallbackList.begin(); it != mDVRCallbackList.end(); ++it)
    {
        ALOGI("%s:  gwm_onDVRTFCardCapacityCostNotify, total_capacity:%f, used_capacity:%f, totalExportCapacity:%f, freeExportCapacity:%f",
            __FUNCTION__,
            capacity_status.total_capacity,
            capacity_status.used_capacity,
            capacity_status.total_export_capacity,
            capacity_status.free_export_capacity);
        auto ret = it->get()->gwm_onDVRTFCardCapacityCostNotify(capacity_status);
        if (!ret.isOk())
        {
            ALOGW("%s:  has error", __FUNCTION__);
        }
    }
    return status;
}

GWM_Status DVRSomeipProxy::recordStateRequest(GWM_DVRCameraId camera_id)
{
    if (mDVR == nullptr)
    {
        ALOGE("%s:  mDVR == nullptr !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    GWM_Status status = GWM_Status::GWM_ERROR;
    RecordStatus_DT recordStatus = RecordStatus_DT::E_INACTIVE;
    EventType_DT eventType = EventType_DT::E_MANUALCAPTURE_BYBUTTON;
    if (mDVR->checkIsReady(InterfaceType::FILE_OPERATION, __FUNCTION__))
    {
        /**
         * @brief RecordEventStatusRequest comes from DVRFileOperation service of someip.
         * serviceid:0x0402
         * methodid: 0x000F
         */
        CallStatus_DT callStatus = RecordEventStatusRequestFuc(mDVR->switch_cameraid(camera_id), recordStatus, eventType);
        ALOGI("%s:  RecordEventStatusRequestFuc callStatus:%d, recordStatus:%d, eventType:%d",
            __FUNCTION__,
            callStatus,
            recordStatus,
            eventType);
        if (callStatus == CallStatus_DT::SUCCESS)
        {
            status = GWM_Status::GWM_OK;
        }
    }

    if (mDVRCallbackList.size() == 0)
    {
        ALOGE("%s:  mDVRCallbackList is null !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    for(it = mDVRCallbackList.begin(); it != mDVRCallbackList.end(); ++it)
    {
        ALOGI("%s:  gwm_onDVRRecordStateNotify, camera_id:%hu, recordStatus:%d, type:%d",
            __FUNCTION__,
            camera_id,
            recordStatus,
            eventType);
        auto ret = it->get()->gwm_onDVRRecordStateNotify((GWM_DVRCameraId)camera_id,
            (GWM_DVRRecordStatus)recordStatus,
            (GWM_DVREventType)eventType);
        if (!ret.isOk())
        {
            ALOGW("%s:  has error", __FUNCTION__);
        }
    }
    return status;
}

// invoke omcCaptureRequest() in DVR.cpp
GWM_DVROMCCaptureStatus DVRSomeipProxy::dvrCaptureRequest(GWM_DVRCameraId cameraId,
    const std::string& eventTime,
    GWM_DVREventType eventType,
    uint32_t fileId,
    uint32_t fileSize,
    bool isOmc)
{
    if (mDVR == nullptr)
    {
        ALOGE("%s:  mDVR == nullptr !", __FUNCTION__);
        return GWM_DVROMCCaptureStatus::GWM_OMCCapture_Unknow;
    }
    return mDVR->dvrCaptureRequest(mDVR->switch_cameraid(cameraId), eventTime, eventType, fileId, fileSize, isOmc, false);
}

// invoke omcCaptureTransferRequest() in DVR.cpp
GWM_DVROMCCaptureStatus DVRSomeipProxy::dvrCaptureTransferRequest(GWM_DVRCameraId cameraId,
    const std::string& eventTime,
    GWM_DVREventType eventType,
    uint32_t fileId,
    uint32_t fileSize,
    const std::string& filePath,
    bool isOmc)
{
    if (mDVR == nullptr)
    {
        ALOGE("%s:  mDVR == nullptr !", __FUNCTION__);
        return GWM_DVROMCCaptureStatus::GWM_OMCCapture_Unknow;
    }
    return mDVR->dvrCaptureTransferRequest(mDVR->switch_cameraid(cameraId), eventTime, eventType, fileId, fileSize, filePath, isOmc, false);
}

GWM_Status DVRSomeipProxy::dvrFileCapacityInfoReq(const GWM_TFAllFileCapacity file_capacity_type,
    const vector<GWM_ParamFileType> &file_type_list)
{
    if (mDVR == nullptr)
    {
        ALOGE("%s:  mDVR == nullptr !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    GWM_Status status = GWM_Status::GWM_ERROR;
    FileCapacityListArrayOut  out;
    memset(&out, 0, sizeof(out));
    if (mDVR->checkIsReady(InterfaceType::FILE_OPERATION, __FUNCTION__))
    {
        TFCardFileTypeListArrayInput list;
        memset(&list, 0, sizeof(list));
        ParamFileTypeEnum_DT dt;
        memset(&dt, 0, sizeof(dt));
        for (uint32_t i = 0; i < file_type_list.size(); i++)
        {
            ALOGD("%s:  file_type_list-size:%lu, file_type:%hhu",
                __FUNCTION__,
                file_type_list.size(),
                file_type_list[i]);
            dt = static_cast<ParamFileTypeEnum_DT>(file_type_list[i]);
            list.dynamicInArray.push_back(dt);
        }

        /**
         * @brief DVRFileCapacityInfoReq comes from DVRFileOperation service of someip.
         * serviceid:0x0402
         * methodid: 0x0011
         */
        CallStatus_DT callStatus = DVRFileCapacityInfoReqFunc(static_cast<TFAllFileCapacityEnum_DT>(file_capacity_type), list, out);
        ALOGI("%s:  DVRFileCapacityInfoReqFunc callStatus:%d, FileCapacityListArrayOut-Size:%lu",
            __FUNCTION__,
            callStatus,
            out.dynamicOutArray.size());
        if (callStatus == CallStatus_DT::SUCCESS && out.dynamicOutArray.size() != 0)
        {
            status = GWM_Status::GWM_OK;
        }
    }

    std::vector<GWM_DVRFileCapacity> vec_file_capacity;
    memset(&vec_file_capacity, 0, sizeof(vec_file_capacity));
    setFileCapacityInfo(status, out, vec_file_capacity);

    if (mDVRCallbackList.size() == 0)
    {
        ALOGE("%s:  mDVRCallbackList is null !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    for(it = mDVRCallbackList.begin(); it != mDVRCallbackList.end(); ++it)
    {
        ALOGI("%s:  gwm_onDVRFileCapacityInfoNotify, vec_file_capacity.size:%zu",
            __FUNCTION__,
            vec_file_capacity.size());
        auto ret = it->get()->gwm_onDVRFileCapacityInfoNotify(vec_file_capacity);
        if (!ret.isOk())
        {
            ALOGW("%s:  has error", __FUNCTION__);
        }
    }
    return status;
}

GWM_Status DVRSomeipProxy::fileListIncludeDateReq(const GWM_DVRFileType file_type,
    const GWM_DVRCameraId camera_id,
    uint8_t file_number,
    const string &file_name)
{
    if (mDVR == nullptr)
    {
        ALOGE("%s:  mDVR == nullptr !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    GWM_Status status = GWM_Status::GWM_ERROR;
    FileListIncludeDateArrayOut out;
    memset(&out, 0, sizeof(out));
    if (mDVR->checkIsReady(InterfaceType::FILE_OPERATION, __FUNCTION__))
    {
        FileType_DT fileType = (FileType_DT)file_type;
        AccessType_DT accessType = mDVR->switch_cameraid(camera_id);
        FileNumber fileNumber = file_number;

        /**
         * @brief FileListIncludeDateReq comes from DVRFileOperation service of someip.
         * serviceid:0x0402
         * methodid: 0x0012
         */
        CallStatus_DT callStatus = FileListIncludeDateReqFunc(fileType, accessType, fileNumber, file_name.c_str(), out);
        ALOGI("%s:  FileListIncludeDateReqFunc callStatus:%d, FileCapacityListArrayOut-Size:%lu",
            __FUNCTION__,
            callStatus,
            out.dynamicOutArray.size());
        if (callStatus == CallStatus_DT::SUCCESS && out.dynamicOutArray.size() != 0)
        {
            status = GWM_Status::GWM_OK;
        }
    }

    std::vector<GWM_FileListIncludeDate> vec_file_list;
    memset(&vec_file_list, 0, sizeof(vec_file_list));
    setFileListIncludeDate(status, out, vec_file_list);

    if (mDVRCallbackList.size() == 0)
    {
        ALOGE("%s:  mDVRCallbackList is null !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    for(it = mDVRCallbackList.begin(); it != mDVRCallbackList.end(); ++it)
    {
        ALOGI("%s:  gwm_onFileListIncludeDateNotify, vec_file_list.size:%zu",
            __FUNCTION__,
            vec_file_list.size());
        auto ret = it->get()->gwm_onFileListIncludeDateNotify(vec_file_list);
        if (!ret.isOk())
        {
            ALOGW("%s:  has error", __FUNCTION__);
        }
    }
    return status;
}

void DVRSomeipProxy::setDVRTFCardStatus(TFCardStatus_DT dt_status, GWM_DVRTFCardStatus& dvr_tfcard_status)
{
    switch (dt_status)
    {
        case E_DVR_NOT_FOUND:
            dvr_tfcard_status.tfcard_status = GWM_DVR_TFCardStatus::GWM_DVR_TFCARD_NOT_EXIST;
            break;
        case E_DVR_FAULT:
            dvr_tfcard_status.tfcard_status = GWM_DVR_TFCardStatus::GWM_DVR_TFCARD_EXCEPTION;
            break;
        case E_DVR_MEMEORY_FULL:
            dvr_tfcard_status.tfcard_status = GWM_DVR_TFCardStatus::GWM_DVR_TFCARD_FULL;
            break;
        case E_DVR_OK:
            dvr_tfcard_status.tfcard_status = GWM_DVR_TFCardStatus::GWM_DVR_TFCARD_PLUGIN;
            break;
        case E_WRITESLOWLY:
            dvr_tfcard_status.tfcard_status = GWM_DVR_TFCardStatus::GWM_DVR_TFCARD_WRITE_SLOW;
            break;
        case E_DVR_EMERGENCY_SPACE_FULL:
            dvr_tfcard_status.tfcard_status = GWM_DVR_TFCardStatus::GWM_DVR_TFCARD_Emergency_Space_Full;
            break;
        case E_DVR_CAPACITY_NOT_SUPPORTED:
            dvr_tfcard_status.tfcard_status = GWM_DVR_TFCardStatus::GWM_DVR_TFCARD_Capacity_Not_Supported;
            break;
        default:
            dvr_tfcard_status.tfcard_status = GWM_DVR_TFCardStatus::GWM_DVR_TFCARD_NULL;
            break;
    }
}

void DVRSomeipProxy::setFileListResult(GWM_Status status, const GWM_DVRFileListREQ& query_file_list,
    const FileListStructArrayOut& out,
    std::vector<GWM_DVRFileListResult>& vec_quest_result)
{
    if (status == GWM_Status::GWM_OK)
    {
        for (uint32_t i = 0; i < out.dynamicArray.size(); i++)
        {
            GWM_DVRFileListResult quest_result;
            memset(&quest_result, 0, sizeof(quest_result));
            quest_result.camera_id = query_file_list.camera_id;
            quest_result.file_path_url = out.dynamicArray[i].filePath;
            quest_result.thumb_path_url = out.dynamicArray[i].thumbnailPath;
            quest_result.operation_type = (GWM_DVRFileType)out.dynamicArray[i].fileTypeDt;
            vec_quest_result.push_back(quest_result);
        }
    }
    else
    {
        GWM_DVRFileListResult quest_result;
        memset(&quest_result, 0, sizeof(quest_result));
        quest_result.camera_id = query_file_list.camera_id;
        quest_result.file_path_url = "";
        quest_result.thumb_path_url = "";
        quest_result.operation_type = query_file_list.operation_type;
        vec_quest_result.push_back(quest_result);
    }
}

void DVRSomeipProxy::setDVRGetParam(ParamCofigStruct_DT dt, GWM_DVRGetParam& params)
{
    switch (dt.paramConfigTypeDt)
    {
        case E_SETWIDEDYNAMICMODE:
            if (dt.paramConfigOperationDt == E_ON)
            {
                params.wide_dynamic_enable_status = GWM_DVRStatus::GWM_DVR_STATUS_ENABLE;
            }
            else if (dt.paramConfigOperationDt == E_OFF)
            {
                params.wide_dynamic_enable_status = GWM_DVRStatus::GWM_DVR_STATUS_DISABLE;
            }
            else
            {
                params.wide_dynamic_enable_status = GWM_DVRStatus::GWM_DVR_STATUS_NULL;
            }
            break;
        case E_SETSEGMENTRECORDINGTIME:
            if (dt.paramConfigOperationDt == E_60SOR1MINUTE)
            {
                params.record_time = (uint32_t)60;
            }
            else if (dt.paramConfigOperationDt == E_3MINUTE)
            {
                params.record_time = (uint32_t)180;
            }
            else if (dt.paramConfigOperationDt == E_5MINUTE)
            {
                params.record_time = (uint32_t)300;
            }
            else
            {
                params.record_time = (uint32_t)180;
            }
            ALOGD("%s:  record timing:%d->%d", __FUNCTION__, dt.paramConfigOperationDt, params.record_time);
            break;
        case E_SETPOWEROFFDELAY:
            if (dt.paramConfigOperationDt == E_60SOR1MINUTE)
            {
                params.delay_shutdown = (uint32_t)60;
            }
            else if (dt.paramConfigOperationDt == E_0S)
            {
                params.delay_shutdown = (uint32_t)0;
            }
            else if (dt.paramConfigOperationDt == E_10S)
            {
                params.delay_shutdown = (uint32_t)10;
            }
            else
            {
                params.delay_shutdown = (uint32_t)0;
            }
            ALOGD("%s:  power delay:%d->%d", __FUNCTION__, dt.paramConfigOperationDt, params.delay_shutdown);
            break;
        case E_SETEVENTVIDEOCYCLECOVERAGE:
            if (dt.paramConfigOperationDt == E_ON)
            {
                params.automatical_overwrite__enable_status = GWM_DVRStatus::GWM_DVR_STATUS_ENABLE;
            }
            else if (dt.paramConfigOperationDt == E_OFF)
            {
                params.automatical_overwrite__enable_status = GWM_DVRStatus::GWM_DVR_STATUS_DISABLE;
            }
            else
            {
                params.automatical_overwrite__enable_status = GWM_DVRStatus::GWM_DVR_STATUS_NULL;
            }
            break;
        case E_SETTAPERECORDING:
            if (dt.paramConfigOperationDt == E_ON)
            {
                params.sounds_enable_status = GWM_DVRStatus::GWM_DVR_STATUS_ENABLE;
            }
            else if (dt.paramConfigOperationDt == E_OFF)
            {
                params.sounds_enable_status = GWM_DVRStatus::GWM_DVR_STATUS_DISABLE;
            }
            else
            {
                params.sounds_enable_status = GWM_DVRStatus::GWM_DVR_STATUS_NULL;
            }
            break;
        case E_SETCYCLEVIDEOTAPEMODE:
            if (dt.paramConfigOperationDt == E_ON)
            {
                params.dvr_enable_status = GWM_DVRStatus::GWM_DVR_STATUS_ENABLE;
            }
            else if (dt.paramConfigOperationDt == E_OFF)
            {
                params.dvr_enable_status = GWM_DVRStatus::GWM_DVR_STATUS_DISABLE;
            }
            else
            {
                params.dvr_enable_status = GWM_DVRStatus::GWM_DVR_STATUS_NULL;
            }
            break;
        case E_SETINTERIORCAMERA:
            if (dt.paramConfigOperationDt == E_ON)
            {
                params.incar_camera_enable_status = GWM_DVRStatus::GWM_DVR_STATUS_ENABLE;
            }
            else if (dt.paramConfigOperationDt == E_OFF)
            {
                params.incar_camera_enable_status = GWM_DVRStatus::GWM_DVR_STATUS_DISABLE;
            }
            else
            {
                params.incar_camera_enable_status = GWM_DVRStatus::GWM_DVR_STATUS_NULL;
            }
            break;
        case E_SET360SURROUNDVIEW:
            if (dt.paramConfigOperationDt == E_ON)
            {
                params.avm_enable_status = GWM_DVRStatus::GWM_DVR_STATUS_ENABLE;
            }
            else if (dt.paramConfigOperationDt == E_OFF)
            {
                params.avm_enable_status = GWM_DVRStatus::GWM_DVR_STATUS_DISABLE;
            }
            else
            {
                params.avm_enable_status = GWM_DVRStatus::GWM_DVR_STATUS_NULL;
            }
            break;
        case E_SETPARKMONITOR:
            if (dt.paramConfigOperationDt == E_ON)
            {
                params.paking_monitoring_enable_status = GWM_DVRStatus::GWM_DVR_STATUS_ENABLE;
            }
            else if (dt.paramConfigOperationDt == E_OFF)
            {
                params.paking_monitoring_enable_status = GWM_DVRStatus::GWM_DVR_STATUS_DISABLE;
            }
            else
            {
                params.paking_monitoring_enable_status = GWM_DVRStatus::GWM_DVR_STATUS_NULL;
            }
            break;
        case E_SETOSDINFO:
            if (dt.paramConfigOperationDt == E_ON)
            {
                params.set_osd_info_status = GWM_DVRStatus::GWM_DVR_STATUS_ENABLE;
            }
            else if (dt.paramConfigOperationDt == E_OFF)
            {
                params.set_osd_info_status = GWM_DVRStatus::GWM_DVR_STATUS_DISABLE;
            }
            else
            {
                params.set_osd_info_status = GWM_DVRStatus::GWM_DVR_STATUS_NULL;
            }
            break;
        default:
            ALOGW("%s:  dt.paramConfigTypeDt is error !", __FUNCTION__);
            break;
    }
}

void DVRSomeipProxy::setParamCofigStructDT(int32_t i, const GWM_DVRSetParam &params, ParamCofigStruct_DT& dt)
{
    switch (i)
    {
        case 0: // GWM_DVR_RECORD_OUTSIDE_SOUNDS    GWM_DVRRequest     sounds_enable_req;    E_SETTAPERECORDING
            dt.paramConfigTypeDt = E_SETTAPERECORDING;
            if (params.sounds_enable_req == GWM_DVRRequest::GWM_DVR_ENABLE_REQUEST)
            {
                dt.paramConfigOperationDt = E_ON;
            }
            else if (params.sounds_enable_req == GWM_DVRRequest::GWM_DVR_DISABLE_REQUEST)
            {
                dt.paramConfigOperationDt = E_OFF;
            }
            else
            {
                dt.paramConfigOperationDt = E_OFF;
            }
            break;
        case 1: // GWM_DVR_TURN_ON_WIDE_DYNAMIC    GWM_DVRRequest     wide_dynamic_enable_req;    E_SETWIDEDYNAMICMODE
            dt.paramConfigTypeDt = E_SETWIDEDYNAMICMODE;
            if (params.wide_dynamic_enable_req == GWM_DVRRequest::GWM_DVR_ENABLE_REQUEST)
            {
                dt.paramConfigOperationDt = E_ON;
            }
            else if (params.wide_dynamic_enable_req == GWM_DVRRequest::GWM_DVR_DISABLE_REQUEST)
            {
                dt.paramConfigOperationDt = E_OFF;
            }
            else
            {
                dt.paramConfigOperationDt = E_ON;
            }
            break;
        case 2: // GWM_DVR_RECORD_TIME    uint32_t           record_time_req;    E_SETSEGMENTRECORDINGTIME
            dt.configParamValueTypeDt = E_UINT32;
            dt.paramConfigTypeDt = E_SETSEGMENTRECORDINGTIME;
            if (params.record_time_req == 1 || params.record_time_req == 60)
            {
                dt.paramConfigOperationDt = E_60SOR1MINUTE;
            }
            else if (params.record_time_req == 3 || params.record_time_req == 180)
            {
                dt.paramConfigOperationDt = E_3MINUTE;
            }
            else if (params.record_time_req == 5 || params.record_time_req == 300)
            {
                dt.paramConfigOperationDt = E_5MINUTE;
            }
            else
            {
                dt.paramConfigOperationDt = E_3MINUTE;
            }
            ALOGD("%s:  RECORD_TIME:%d->%d", __FUNCTION__, params.record_time_req, dt.paramConfigOperationDt);
            break;
        case 3: // GWM_DVR_DELAY_SHUTDOW     uint32_t           delay_shutdown_req;    E_SETPOWEROFFDELAY
            dt.configParamValueTypeDt = E_UINT32;
            dt.paramConfigTypeDt = E_SETPOWEROFFDELAY;
            if (params.delay_shutdown_req == 0)
            {
                dt.paramConfigOperationDt = E_0S;
            }
            else if (params.delay_shutdown_req == 10)
            {
                dt.paramConfigOperationDt = E_10S;
            }
            else if (params.delay_shutdown_req == 60)
            {
                dt.paramConfigOperationDt = E_60SOR1MINUTE;
            }
            else
            {
                dt.paramConfigOperationDt = E_0S;
            }
            ALOGD("%s:  DELAY_SHUTDOW:%d->%d", __FUNCTION__, params.delay_shutdown_req, dt.paramConfigOperationDt);
            break;
        case 4: // GWM_DVR_RECORD_AUTOMATICAL_OVERWRITE    GWM_DVRRequest     automatical_overwrite__enable_req;    E_SETEVENTVIDEOCYCLECOVERAGE
            dt.paramConfigTypeDt = E_SETEVENTVIDEOCYCLECOVERAGE;
            if (params.automatical_overwrite__enable_req == GWM_DVRRequest::GWM_DVR_ENABLE_REQUEST)
            {
                dt.paramConfigOperationDt = E_ON;
            }
            else if (params.automatical_overwrite__enable_req == GWM_DVRRequest::GWM_DVR_DISABLE_REQUEST)
            {
                dt.paramConfigOperationDt = E_OFF;
            }
            else
            {
                dt.paramConfigOperationDt = E_OFF;
            }
            break;
        case 5: // GWM_DVR_RECORD_SWITCH    GWM_DVRRequest     dvr_enable_req;    E_SETCYCLEVIDEOTAPEMODE
            dt.paramConfigTypeDt = E_SETCYCLEVIDEOTAPEMODE;
            if (params.dvr_enable_req == GWM_DVRRequest::GWM_DVR_ENABLE_REQUEST)
            {
                dt.paramConfigOperationDt = E_ON;
            }
            else if (params.dvr_enable_req == GWM_DVRRequest::GWM_DVR_DISABLE_REQUEST)
            {
                dt.paramConfigOperationDt = E_OFF;
            }
            else
            {
                dt.paramConfigOperationDt = E_ON;
            }
            break;
        case 6: // GWM_DVR_PARKING_MONITORING    GWM_DVRRequest     paking_monitoring_enable_req;    E_SETPARKMONITOR
            dt.paramConfigTypeDt = E_SETPARKMONITOR;
            if (params.paking_monitoring_enable_req == GWM_DVRRequest::GWM_DVR_ENABLE_REQUEST)
            {
                dt.paramConfigOperationDt = E_ON;
            }
            else if (params.paking_monitoring_enable_req == GWM_DVRRequest::GWM_DVR_DISABLE_REQUEST)
            {
                dt.paramConfigOperationDt = E_OFF;
            }
            else
            {
                dt.paramConfigOperationDt = E_OFF;
            }
            break;
        case 9: // GWM_DVR_360_VIDEO_SWITCH    GWM_DVRRequest     avm_enable_req;    E_SET360SURROUNDVIEW
            dt.paramConfigTypeDt = E_SET360SURROUNDVIEW;
            if (params.avm_enable_req == GWM_DVRRequest::GWM_DVR_ENABLE_REQUEST)
            {
                dt.paramConfigOperationDt = E_ON;
            }
            else if (params.avm_enable_req == GWM_DVRRequest::GWM_DVR_DISABLE_REQUEST)
            {
                dt.paramConfigOperationDt = E_OFF;
            }
            else
            {
                dt.paramConfigOperationDt = E_ON;
            }
            break;
        case 10: // GWM_DVR_INCAR_VIDEO_SWITCH    GWM_DVRRequest     incar_camera_enable_req;    E_SETINTERIORCAMERA
            dt.paramConfigTypeDt = E_SETINTERIORCAMERA;
            if (params.incar_camera_enable_req == GWM_DVRRequest::GWM_DVR_ENABLE_REQUEST)
            {
                dt.paramConfigOperationDt = E_ON;
            }
            else if (params.incar_camera_enable_req == GWM_DVRRequest::GWM_DVR_DISABLE_REQUEST)
            {
                dt.paramConfigOperationDt = E_OFF;
            }
            else
            {
                dt.paramConfigOperationDt = E_OFF;
            }
            break;
        case 11: // GWM_DVR_SET_OSD_INFO_SWITCH    GWM_DVRRequest     set_osd_info_req;    E_SETOSDINFO
            dt.paramConfigTypeDt = E_SETOSDINFO;
            if (params.set_osd_info_req == GWM_DVRRequest::GWM_DVR_ENABLE_REQUEST)
            {
                dt.paramConfigOperationDt = E_ON;
            }
            else if (params.set_osd_info_req == GWM_DVRRequest::GWM_DVR_DISABLE_REQUEST)
            {
                dt.paramConfigOperationDt = E_OFF;
            }
            else
            {
                dt.paramConfigOperationDt = E_OFF;
            }
            break;
        default:
            break;
    }
}

void DVRSomeipProxy::setFileCapacityInfo(GWM_Status status, const FileCapacityListArrayOut &out,
        std::vector<GWM_DVRFileCapacity> &vec_file_capacity)
{
    if (status == GWM_Status::GWM_OK)
    {
        for (uint32_t i = 0; i < out.dynamicOutArray.size(); i++)
        {
            GWM_DVRFileCapacity quest_result;
            memset(&quest_result, 0, sizeof(quest_result));
            quest_result.file_type = static_cast<GWM_ParamFileType>(out.dynamicOutArray[i].paramFileTypeEnumDt);
            quest_result.used_capacity = static_cast<int32_t>(out.dynamicOutArray[i].usedCapacity);
            quest_result.total_capacity = static_cast<int32_t>(out.dynamicOutArray[i].totalCapacity);
            vec_file_capacity.push_back(quest_result);
        }
    }
    else
    {
        GWM_DVRFileCapacity quest_result;
        memset(&quest_result, 0, sizeof(quest_result));
        quest_result.file_type = GWM_ParamFileType::GWM_CustomData;
        quest_result.used_capacity = INVALID_VALUE;
        quest_result.total_capacity = INVALID_VALUE;
        vec_file_capacity.push_back(quest_result);
    }
}

void DVRSomeipProxy::setFileListIncludeDate(GWM_Status status, const FileListIncludeDateArrayOut &out,
        std::vector<GWM_FileListIncludeDate> &vec_file_list)
{
    if (status == GWM_Status::GWM_OK)
    {
        for (uint32_t i = 0; i < out.dynamicOutArray.size(); i++)
        {
            GWM_FileListIncludeDate file_list;
            memset(&file_list, 0, sizeof(file_list));
            file_list.file_path = out.dynamicOutArray[i].filePath;
            file_list.thumbnail_path = out.dynamicOutArray[i].thumbnailPath;
            file_list.file_type = (GWM_DVRFileType)out.dynamicOutArray[i].fileTypeDt;
            file_list.camera_id = mDVR->accessTypeToCameraId(out.dynamicOutArray[i].accessTypeDt);
            file_list.event_time = out.dynamicOutArray[i].eventTime;
            file_list.file_number = out.dynamicOutArray[i].fileNumber;
            vec_file_list.push_back(file_list);
        }
    }
    else
    {
        GWM_FileListIncludeDate file_list;
        memset(&file_list, 0, sizeof(file_list));
        file_list.file_path = "";
        file_list.thumbnail_path = "";
        file_list.file_type = GWM_DVRFileType::GWM_DVRFileNormalVideo;
        file_list.camera_id = GWM_DVRCameraId::GWM_DVR_CAMERA_ID_FRONT;
        file_list.event_time = "";
        file_list.file_number = 0;
        vec_file_list.push_back(file_list);
    }
}

}
}
}
}
}
}