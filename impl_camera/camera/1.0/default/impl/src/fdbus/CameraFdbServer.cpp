/*************************************************************************
 * Copyright (C) 2020 GWM Automotive Inc.
 *
 * The copyright notice above does not evidence any actual
 * or intended publication of such source code.
 * The code contains GWM Confidential Proprietary Information.
 *************************************************************************/
/**************************************************************************
 * @file CameraFdbServer.cpp
 * CameraFdbServer
 *
 * @project     v3.5
 * @subsystem
 * @version     0.1
 * @author
 * @date        2020-6-28

 Module-History:
 Date(dd.mm.year)| Author            | Reason
 The latest entry at the head of the history list.
 12/6/2020         Fugen Peng           Init version

***************************************************************************/
#include <android/log.h>
#include <log/log.h>
#include "CameraFdbServer.h"

#undef LOG_TAG
#define LOG_TAG "CameraHAL_CameraFdbServer"

namespace vendor{
namespace gwm{
namespace hardware{
namespace camera{
namespace V1_0{
namespace implementation{

using ::android::sp;
using namespace std;
using namespace DVRFdb;

CameraFdbServer::CameraFdbServer(const char *name, CBaseWorker *worker)
    : CBaseServer(name, worker)
{
}

CameraFdbServer::~CameraFdbServer()
{
}

void CameraFdbServer::onOnline(FdbSessionId_t sid, bool is_first)
{
    ALOGD("%s:  server session up:%d", __func__, sid);
}

void CameraFdbServer::onOffline(FdbSessionId_t sid, bool is_last)
{
    ALOGD("%s:  server session offline:%d", __func__, sid);
}

GWM_Status CameraFdbServer::sendMessage(
    FdbMsgCode_t code, CFdbProtoMsgBuilder builder)
{
    bool ret;
    ret = broadcast(code, builder);
    if (ret)
    {
        ALOGI("%s msg:%#X has successfully sent to fdbus tx queue(async).",
            __FUNCTION__,
            code);
        return GWM_Status::GWM_OK;
    }
    else
    {
        ALOGE("%s msg:%#X has failed to send to fdbus queue(async).",
            __FUNCTION__,
            code);
        return GWM_Status::GWM_ERROR;
    }
}

GWM_Status CameraFdbServer::sendMessage(FdbMsgCode_t code)
{
    bool ret;
    ret = broadcast(code);
    if (ret)
    {
        ALOGI("%s msg:%#X has successfully sent to fdbus tx queue(async).",
            __FUNCTION__,
            code);
        return GWM_Status::GWM_OK;
    }
    else
    {
        ALOGE("%s msg:%#X has failed to send to fdbus queue(async).",
            __FUNCTION__,
            code);
        return GWM_Status::GWM_ERROR;
    }
}

void CameraFdbServer::onSubscribe(CBaseJob::Ptr &msg_ref)
{
    auto msg = castToMessage<CFdbMessage *>(msg_ref);
    const CFdbMsgSubscribeItem *sub_item;
    /* iterate all message id subscribed */
    FDB_BEGIN_FOREACH_SIGNAL(msg, sub_item)
    {
        FdbMsgCode_t msg_code = sub_item->msg_code();
        std::string filter = "";
        if (sub_item->has_filter())
        {
            filter = sub_item->filter().c_str();
        }
        FdbSessionId_t sid = msg->session();
        ALOGD("%s:  single message:%d, filter:%s of session:%d is registered!", __func__, msg_code, filter.c_str(), sid);
    }
    FDB_END_FOREACH_SIGNAL()
}

void CameraFdbServer::onInvoke(CBaseJob::Ptr &msg_ref)
{
    auto msg = castToMessage<CBaseMessage *>(msg_ref);
    switch (msg->code())
    {
    case DVRFdb::FdbCameraServerMsgId::DVR_FDB_QNX_UPLOAD_Operation_ACK:
    {
        ALOGD("%s:  DVR_FDB_QNX_UPLOAD_Operation_ACK", __func__);
        DVRFdbBroadcastOperationStatus operation_result;
        CFdbProtoMsgParser parser(operation_result);
        if (msg->deserialize(parser))
        {
        }
        else
        {
            msg->status(msg_ref, NFdbBase::FDB_ST_MSG_DECODE_FAIL,
                        "Fail to decode REQ_SEND_LOG!");
            return;
        }
        msg->reply(msg_ref);
        // GWM_MDisplay_CardID id;
        // ALOGD("%s Receive cardId = %d", __func__, (int32_t)cardMsg.card_id());
        // id = (GWM_MDisplay_CardID)cardMsg.card_id();
        if (m_DVR != nullptr)
        {
            m_DVR->mActResult.modules_name = (GWM_QNXModuleName)(operation_result.client_name());
            m_DVR->mActResult.act_module = (GWM_DVRActModules)operation_result.operation_type();
            m_DVR->mActResult.act_cmd = (GWM_DVRActCommand)operation_result.action_type();
            m_DVR->mActResult.operation_status = (GWM_OperationStatus)(operation_result.operation_status());
            m_DVR->mActResult.sequence = operation_result.sequence();
            m_DVR->sendActCommdAck(m_DVR->mActResult);
        }
    }
    break;
    case DVRFdb::FdbCameraServerMsgId::DVR_FDB_QNX_Modules_Event_ACK:
    {
        ALOGD("%s:  DVR_FDB_QNX_Modules_Event_ACK", __func__);
        DVRFdbSendModuleEventStatus event_result;
        CFdbProtoMsgParser parser(event_result);
        if (msg->deserialize(parser))
        {
        }
        else
        {
            msg->status(msg_ref, NFdbBase::FDB_ST_MSG_DECODE_FAIL,
                        "Fail to decode REQ_SEND_LOG!");
            return;
        }
        msg->reply(msg_ref);
        if (m_DVR != nullptr)
        {
            m_DVR->mEventResult.modules_name = (GWM_DVRActModules)(event_result.client_name());
            m_DVR->mEventResult.act_module = (GWM_QNXModuleName)(event_result.operation_type());
            m_DVR->mEventResult.event = (GWM_ModuleEvent)event_result.act_event();
            m_DVR->mEventResult.sequence = (uint64_t)event_result.sequence();
            m_DVR->sendModuleEventAck(m_DVR->mEventResult);
        }
    }
    break;
    default:
        break;
    }
}

void CameraFdbServer::setDVRServer(sp<DVR> drv) { m_DVR = drv; }

}
}
}
}
}
}