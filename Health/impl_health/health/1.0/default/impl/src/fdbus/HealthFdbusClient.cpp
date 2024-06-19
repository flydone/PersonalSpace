/*************************************************************************
* Copyright (C) 2020-2021 GWM Automotive Inc.
*
* The copyright notice above does not evidence any actual
* or intended publication of such source code.
* The code contains GWM Confidential Proprietary Information.
*************************************************************************/

/**************************************************************************
 * @file HealthFdbusClient.cpp
 * HealthFdbusClient
 *
 * @project     v3.5
 * @subsystem
 * @version     0.1
 * @author
 * @date        2020-8-21

 Module-History:
 Date(dd.mm.year)| Author            | Reason
 The latest entry at the head of the history list.
 21/8/2020         Hong Jiu Jin          Init version

***************************************************************************/

#include "HealthFdbusClient.h"

#include <common_base/CFdbProtoMsgBuilder.h>
#include <log/log.h>
#include <string.h>

#ifdef LOG_TAG
#undef LOG_TAG
#define LOG_TAG "HealthMain_FdbusClient"
#endif

namespace vendor {
namespace gwm {
namespace hardware {
namespace health {
namespace V1_0 {
namespace implementation {

using namespace lifecycle;

static uint32_t HeartBeatCount = 0;

HealthFdbusClient::HealthFdbusClient(const string &url, const string &name,
                                     CBaseWorker *worker, Health *health)
    : FdbusClientBase(url, name, worker),
      mHealth(health),
      mFdbusOnline(false) {}

HealthFdbusClient::~HealthFdbusClient() {}

void HealthFdbusClient::onOnline(FdbSessionId_t sid, bool is_first) {
  ALOGI("%s client session online: %d is_first:%d", __func__, sid, is_first);
  if (is_first) {
    setOnline(true);
    mFdbusOnline = true;
    CFdbMsgSubscribeList subscribe_list;
    addNotifyItem(subscribe_list,
    lifecycle::BroadcastMsgId::BROADCAST_IVI_SHOULD_SHUTDOWN);
    subscribe(subscribe_list);
  }
}

void HealthFdbusClient::onOffline(FdbSessionId_t sid, bool is_last) {
  ALOGI("%s client session offline: %d", __func__, sid);
  setOnline(false);
}

/* Unused features */
void HealthFdbusClient::onBroadcast(CBaseJob::Ptr &msg_ref) {
#if 0
  auto msg = castToMessage<CBaseMessage *>(msg_ref);
  int32_t shutdown_reason = -1;
  /* ALOGD("Broadcast is received: %d; filter: %s", msg->code(),
   * msg->getFilter());*/

  switch (msg->code()) {
    case lifecycle::BroadcastMsgId::BROADCAST_IVI_SHOULD_SHUTDOWN: {
      // even if android support shutdown/restart,
      // to ensure device restart successfully, just inform to shutdown android.
      // qnx will be in charge of restart android.
      BroadcastIviShouldShutdown shutdownMsg;
      CFdbProtoMsgParser parser(shutdownMsg);
      if (msg->deserialize(parser)) {
        shutdown_reason = shutdownMsg.reason();
        if (shutdown_reason == 0) {
          ALOGI("Receive QNX shutdown request due to power key long press");
        } else if (shutdown_reason == 1) {
          ALOGI("Receive QNX shutdown request due to fota update");
        }
        GWM_HealthPowerOffReq req = GWM_HealthPowerOffReq::SHUTDOWN;
        mHealth->onSOCPowerOff(req);
      } else {
        ALOGE("Unable to decode BROADCAST_IVI_SHOULD_SHUTDOWN msg!");
      }
    } break;
    default:
      break;
  }
#endif
}

void HealthFdbusClient::onStatus(CBaseJob::Ptr &msg_ref, int32_t error_code,
                                 cstr8_t description) {
  auto msg = castToMessage<CBaseMessage *>(msg_ref);

  if (msg->isSubscribe()) {
    if (msg->isError()) {
      ALOGE("subscribe has error, Reason: %s\n", description);
    } else {
      ALOGD("subscribe is ok! sn: %d is received.", msg->sn());
    }
  }
}

/* Only Async send */
#if 0
void HealthFdbusClient::onReply(CBaseJob::Ptr &msg_ref) {
  auto msg = castToMessage<CBaseMessage *>(msg_ref);
  ALOGD("%s: response is receieved. sn: %d\n", __func__, msg->sn());

  switch (msg->code()) {
    case EventMsgId::IVI_HEARTBEAT: {
      if (msg->isStatus()) {
        /* Unable to get intended reply from server... Check what happen. */
        if (msg->isError()) {
          int32_t error_code;
          std::string reason;

          if (!msg->decodeStatus(error_code, reason)) {
            ALOGE("%s: fail to decode status!", __func__);
            return;
          }

          ALOGD(
              "%s: status is received: msg code: %d, error_code: %d, reason: "
              "%s",
              __func__, msg->code(), error_code, reason.c_str());
        }
        ALOGD("%s: ignore status code and return", __func__);
        return;
      }

      IviHeartBeatRes beat_res;
      CFdbProtoMsgParser parser(beat_res);
      if (msg->deserialize(parser)) {
        ALOGD("%s: got server IVI_HEARTBEAT reply, heart beat res ack is %d", __func__,
              beat_res.heartbeat_ack());
      } else {
        ALOGE("Unable to decode IVI_HEARTBEAT!\n");
      }
    } break;

    default:
      break;
  }
}
#endif

GWM_StatusCode HealthFdbusClient::sendHeartBeat(int32_t ivi_status) {
  GWM_StatusCode sc = GWM_StatusCode::ERROR;

  if (!mFdbusOnline) {
    ALOGE("%s: fdbus is not online", __func__);
    return sc;
  }

  IviHeartBeat beat_msg;
  beat_msg.set_ivi_status(ivi_status);

  CBaseJob::Ptr ref(new CBaseMessage(IVI_HEARTBEAT));
  CFdbProtoMsgBuilder builder(beat_msg);

  if ((HeartBeatCount % 5U) == 0) {
    ALOGI("%s: sendHeartBeat count=%d", __func__, HeartBeatCount);
  }
  HeartBeatCount++;

  bool ret = invoke(ref, builder, 5*1000);
  if (!ret)  {
    ALOGE("%s: sendHeartBeat failed count=%d",  __func__, HeartBeatCount);
  }

  auto msg = castToMessage<CBaseMessage *>(ref);
  if (msg->isStatus()) {
    /* Unable to get intended reply from server... Check what happen. */
    int32_t error_code;
    std::string reason;

    if (!msg->decodeStatus(error_code, reason)) {
      ALOGE("%s: fail to decode status", __func__);
      return sc;
    }

    if (msg->isError()) {
      ALOGE("%s: msg error - msg code:%d, error_code:%d, reason:%s",
        __func__, msg->code(), error_code, reason.c_str());

      /* fix BUG:B02-8024 2023-05-09 by tangwei-NOBO  reason:fdbus_lifecycle_qnx offline to requestServiceAddress again */
      if(error_code == -17) {
          ALOGE("%s: requestServiceAddress", __func__);
          requestServiceAddress();
      }

    }

    ALOGE("%s: unknown status error", __func__);
    return sc;
  }

  IviHeartBeatRes res;
  CFdbProtoMsgParser parser(res);
  if (msg->deserialize(parser)) {
    if ((HeartBeatCount % 5U) == 1U) {
      ALOGI("%s: ivi heartbeat ack=%d count=%d", __func__, res.heartbeat_ack(), HeartBeatCount);
    }
    sc = GWM_StatusCode::OK;
  } else {
    ALOGE("%s: unable to decode IVI_HEARTBEAT response", __func__);
  }

  return sc;
}

GWM_StatusCode HealthFdbusClient::sendRestartReq(int32_t req) {
  GWM_StatusCode sc = GWM_StatusCode::ERROR;

  if (!mFdbusOnline) {
    ALOGE("%s: fdbus is not line.", __func__);
    return sc;
  }

  IviRestartReq req_msg;
  req_msg.set_reason(req);

  CBaseJob::Ptr ref(new CBaseMessage(IVI_RESTART_REQ));
  CFdbProtoMsgBuilder builder(req_msg);

  invoke(ref, builder);
  auto msg = castToMessage<CBaseMessage *>(ref);

  if (msg->isStatus()) {
    /* Unable to get intended reply from server... Check what happen. */
    int32_t error_code;
    std::string reason;

    if (!msg->decodeStatus(error_code, reason)) {
      ALOGE("%s: fail to decode status!\n", __func__);
      return sc;
    }

    if (msg->isError()) {
      ALOGD(
          "%s: status is received: msg code: %d, error_code: %d, reason: "
          "%s\n",
          __func__, msg->code(), error_code, reason.c_str());
    }
    return sc;
  }

  IviRestartReqRes res;
  CFdbProtoMsgParser parser(res);
  if (msg->deserialize(parser)) {
    ALOGD("%s ivi restart request response %d", __func__, res.res());
    sc = GWM_StatusCode::OK;
  } else {
    ALOGE("Unable to decode IVI_RESTART_REQ response !\n");
  }

  return sc;
}

GWM_StatusCode HealthFdbusClient::sendMessage(FdbMsgCode_t code,
                                              CFdbProtoMsgBuilder builder) {
  bool ret;
  ret = invoke(code, builder);
  if (ret) {
    ALOGE("%s HealthFdbusClient CFdbProtoMsgBuilder sendMessage successful",
          __func__);
    return GWM_StatusCode::OK;
  } else {
    ALOGE("%s HealthFdbusClient CFdbProtoMsgBuilder sendMessage failure",
          __func__);
    return GWM_StatusCode::ERROR;
  }
}

bool HealthFdbusClient::getConnectStatus() {
  return mFdbusOnline;
}

}  // namespace implementation
}  // namespace V1_0
}  // namespace health
}  // namespace hardware
}  // namespace gwm
}  // namespace vendor
