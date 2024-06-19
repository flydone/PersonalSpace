/*************************************************************************
* Copyright (C) 2020-2021 GWM Automotive Inc.
*
* The copyright notice above does not evidence any actual
* or intended publication of such source code.
* The code contains GWM Confidential Proprietary Information.
*************************************************************************/

/**************************************************************************
 * @file SOCThermalFdbClient.cpp
 * SOC Thermal Fdbus Client class implementation
 *
 * @project     v3.5
 * @subsystem
 * @version     0.1
 * @author      Hong Jiu Jin
 * @date        2020-10-10

 Module-History:
 Date(dd.mm.year)| Author            | Reason
 The latest entry at the head of the history list.
 10/10/2020         Hong Jiu Jin Init version
 ***************************************************************************/

#define LOG_TAG "HealthMain_SOCThermal"
#include <log/log.h>
#include <android/log.h>
#include "SOCThermalFdbClient.h"

namespace vendor {
namespace gwm {
namespace hardware {
namespace health {
namespace V1_0 {
namespace implementation {

SOCThermalFdbClient::SOCThermalFdbClient(const string &url, const string &name,
                                         CBaseWorker *worker, Health *health)
    : FdbusClientBase(url, name, worker), mHealth(health) {}

SOCThermalFdbClient::~SOCThermalFdbClient() {}

/* called when connected to the server */
void SOCThermalFdbClient::onOnline(FdbSessionId_t sid, bool is_first) {
  ALOGI("%s client session online: %d\n", __func__, sid);
  setOnline(true);
  CFdbMsgSubscribeList subscribe_list;
  addNotifyItem(subscribe_list, infrainfo::CodeId::BROADCAST_SOC_TEMPERATURE);
  subscribe(subscribe_list);
}

/* called when disconnected from server */
void SOCThermalFdbClient::onOffline(FdbSessionId_t sid, bool is_last) {
  ALOGI("%s client session offline: %d\n", __func__, sid);
  setOnline(false);
}

/* called when events broadcasted from server is received */
void SOCThermalFdbClient::onBroadcast(CBaseJob::Ptr &msg_ref) {
  int32_t res_size;
  uint8_t *res_buffer;
  uint8_t recBuff[16] = {0};
  auto msg = castToMessage<CBaseMessage *>(msg_ref);
  /* ALOGI("SOCThermal Server Broadcast is received: %d; filter: %s\n",
     msg->code(),
        msg->getFilter());*/

  switch (msg->code()) {
    case infrainfo::CodeId::BROADCAST_SOC_TEMPERATURE: {
      res_buffer = (uint8_t *)msg->getPayloadBuffer();
      res_size = msg->getPayloadSize();
      /* ALOGI("%s received broadcast %x  len:%d.", __func__, res_buffer[0],
            res_size);*/
      memcpy(recBuff, res_buffer, res_size);
      /* ALOGI("%s: get_Soc_Temperature: %x, %x %x %x   %u", __func__,
       * recBuff[0],recBuff[1],recBuff[2],recBuff[3],res_size);*/

      /*
       * onBroadcast: get_Soc_Temperature: 0, 0 0 42   4
       *
       */
#if 0
      mHealth->onSOCChipTemperature(recBuff[3]);
#endif
    } break;
    default:
      break;
  }
}

GWM_StatusCode SOCThermalFdbClient::sendMessage(FdbMsgCode_t code, uint8_t *buf,
                                                int32_t size) {
  bool ret;

  if (buf == nullptr || size <= 0) {
    ALOGE("%s input error!.", __func__);
    return GWM_StatusCode::ERROR;
  }

  if (!isOnline()) {
    ALOGE("%s: fdbus is not line.", __func__);
    return GWM_StatusCode::ERROR;
  }

  ret = invoke(code, buf, size);
  if (ret) {
    ALOGE("%s msg has successfully sent to fdbus tx queue(async).", __func__);
    return GWM_StatusCode::OK;
  } else {
    ALOGE("%s msg has failed to send to fdbus queue(async).", __func__);
    return GWM_StatusCode::ERROR;
  }
  return GWM_StatusCode::OK;
}

void SOCThermalFdbClient::onStatus(CBaseJob::Ptr &msg_ref, int32_t error_code,
                                   cstr8_t description) {
  auto msg = castToMessage<CBaseMessage *>(msg_ref);
  if (msg->isSubscribe()) {
    if (msg->isError()) {
      ALOGI(" %s is error!\n", __func__);
    } else {
      ALOGI("subscribe is ok! sn: %d is received.\n", msg->sn());
    }
  }
  ALOGI("Reason: %s\n", description);
}

/* called when client call asynchronous version of invoke() and reply() is
 * called at server */
void SOCThermalFdbClient::onReply(CBaseJob::Ptr &msg_ref) {
  int32_t res_size;
  uint8_t *res_buffer;
  uint8_t recBuff[16] = {0};

  auto msg = castToMessage<CBaseMessage *>(msg_ref);
  ALOGD("%s response is receieved. sn: %d\n", __func__, msg->sn());
  switch (msg->code()) {
    // to define message code
    case infrainfo::CodeId::RQ_DISPLAY_INFO: {
      if (msg->isStatus()) {
        /* Unable to get intended reply from server... Check what happen. */
        if (msg->isError()) {
          int32_t error_code;
          std::string reason;

          if (!msg->decodeStatus(error_code, reason)) {
            ALOGE("%s: fail to decode status!\n", __func__);
            return;
          }
          ALOGD(
              "%s: status is received: msg code: %d, error_code: %d, reason: "
              "%s\n",
              __func__, msg->code(), error_code, reason.c_str());
        }
        ALOGD("%s: ignore status code and return", __func__);
        return;
      }
      res_buffer = (uint8_t *)msg->getPayloadBuffer();
      res_size = msg->getPayloadSize();
      ALOGI("%s received QNX msg %x  len:%d.", __func__, res_buffer[0],
            res_size);
      memcpy(recBuff, res_buffer, res_size);
      // mHealth->onReceiveQNXMsg(recBuff, res_size);
    } break;
    default:
      ALOGE("%s get wrong reply.", __func__);
      break;
  }
}

}  // namespace implementation
}  // namespace V1_0
}  // namespace health
}  // namespace hardware
}  // namespace gwm
}  // namespace vendor
