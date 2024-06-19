/*************************************************************************
* Copyright (C) 2020-2021 GWM Automotive Inc.
*
* The copyright notice above does not evidence any actual
* or intended publication of such source code.
* The code contains GWM Confidential Proprietary Information.
*************************************************************************/

/**************************************************************************
 * @file VIPThermalFdbClient.cpp
 * VIP Thermal Fdbus Client class implementation
 *
 * @project     v3.5
 * @subsystem
 * @version     0.1
 * @author      Hong Jiu Jin
 * @date        2020-10-28

 Module-History:
 Date(dd.mm.year)| Author            | Reason
 The latest entry at the head of the history list.
 10/10/2020         Hong Jiu Jin Init version
 ***************************************************************************/

#define LOG_TAG "HealthMain_VIPThermal"
#include <log/log.h>
#include <android/log.h>
#include "VIPThermalFdbClient.h"
#include "IPC_POWER.h"
//#include "Health.h"

namespace vendor {
namespace gwm {
namespace hardware {
namespace health {
namespace V1_0 {
namespace implementation {

using namespace mcugateway;

VIPThermalFdbClient::VIPThermalFdbClient(const string &url, const string &name,
                                         CBaseWorker *worker, Health *health)
    : FdbusClientBase(url, name, worker), mHealth(health) {}

VIPThermalFdbClient::~VIPThermalFdbClient() {}

/* called when connected to the server */
void VIPThermalFdbClient::onOnline(FdbSessionId_t sid, bool is_first) {
  ALOGI("%s QNX client session online: %d\n", __func__, sid);
  setOnline(true);
  CFdbMsgSubscribeList subscribe_list;
  addNotifyItem(subscribe_list, CodeId::BROADCAST_POWER_INFO);
  subscribe(subscribe_list);
}

/* called when disconnected from server */
void VIPThermalFdbClient::onOffline(FdbSessionId_t sid, bool is_last) {
  ALOGI("%s QNX client session offline: %d\n", __func__, sid);
  setOnline(false);
}

/* called when events broadcasted from server is received */
void VIPThermalFdbClient::onBroadcast(CBaseJob::Ptr &msg_ref) {
  auto msg = castToMessage<CBaseMessage *>(msg_ref);
  /*ALOGD("Broadcast is received: %d; filter: %s", msg->code(),
   * msg->getFilter());*/
  FdbMsgCode_t code = msg->code();

  switch (code) {
    case CodeId::BROADCAST_POWER_INFO: {
      FdbBroadcastMessage pwrInfo;
      CFdbProtoMsgParser parser(pwrInfo);
      if (msg->deserialize(parser) && (pwrInfo.data_len() > 0)) {
        ByteBuffer data(&(pwrInfo.mcu_data())[0],
                        &(pwrInfo.mcu_data())[0] + pwrInfo.data_len());
        onReceiveVIPMsg(data, (uint32_t)(pwrInfo.data_len()));
      } else {
        ALOGE("Unable to decode BROADCAST_POWER_INFO msg!");
      }
    } break;
    default:
      break;
  }
}

void VIPThermalFdbClient::onReceiveVIPMsg(const ByteBuffer &recData,
                                          uint32_t data_len) {
  uint8_t recBuff[MAX_VIPMSG_LENGTH] = {0};
  memcpy(recBuff, recData.data(), data_len);
  uint16_t subMsg = recBuff[0];

  switch (subMsg) {
    case IPC_M2S_POWER_POWERINFO_MSGSUB_TEMPERATURE_ID: {
      int32_t ret = 0;
      IPC_M2S_POWERPowerInfoTemperature_t temperInfo;
      ret = IPC_M2S_POWERPowerInfoTemperature_Parse(
          &temperInfo, &recBuff[1],
          IPC_M2S_POWER_POWERINFO_MSGSUB_TEMPERATURE_LENGTH);
      if (ret < 0) {
        ALOGE("%s: vip powerinfo temperature parse fail", __func__);
        return;
      }

      /* ALOGD("%s: VIP Board temperature:%f, temperature state:%x", __func__,
            temperInfo.Temperature, temperInfo.TemperatureState);*/
#if 0
      if (mHealth != nullptr) {
        mHealth->onVIPBoardTemperature(temperInfo.Temperature,
                                       temperInfo.TemperatureState);
      }
#endif

    } break;
    default:
      /* ALOGI("%s unknown vip powerinfo msg:%d", __func__, recBuff[0]); */
      break;
  }
}

GWM_StatusCode VIPThermalFdbClient::sendMessage(FdbMsgCode_t code,
                                                const uint8_t *data,
                                                int32_t length) {
  if (data == nullptr || length <= 0) {
    ALOGE("%s: buf is null or lenght is 0", __func__);
    return GWM_StatusCode::ERROR;
  }

  if (!isOnline()) {
    ALOGE("%s: fdbus is not line.", __func__);
    return GWM_StatusCode::ERROR;
  }

  ByteBuffer buffer(data, data + length);
  std::string msg_data = "";
  msg_data.assign(buffer.begin(), buffer.end());

  FdbSendMessageRequest req_msg;
  req_msg.set_priority(FdbSendMessageRequest::HIGH);
  req_msg.set_app_data(msg_data);

  CFdbProtoMsgBuilder builder(req_msg);

  /* Async send */
  int32_t ret = invoke(CodeId::SEND_MESSAGE, builder);
  if (ret) {
    ALOGD("%s msg has successfully sent to fdbus tx queue(async).", __func__);
    return GWM_StatusCode::OK;
  } else {
    ALOGE("%s msg has failed to send to fdbus queue(async).", __func__);
    return GWM_StatusCode::ERROR;
  }
}

void VIPThermalFdbClient::onStatus(CBaseJob::Ptr &msg_ref, int32_t error_code,
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
void VIPThermalFdbClient::onReply(CBaseJob::Ptr &msg_ref) {
  auto msg = castToMessage<CBaseMessage *>(msg_ref);
  /* ALOGD("%s: response is receieved. sn: %d\n", __func__, msg->sn());*/

  switch (msg->code()) {
    case CodeId::SEND_MESSAGE: {
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

      FdbSendMessageResponse srv_reply;
      CFdbProtoMsgParser parser(srv_reply);
      if (msg->deserialize(parser)) {
        ALOGD("%s: got server SEND_MESSAGE reply, ipc result is %d", __func__,
              srv_reply.return_enum());
      } else {
        ALOGE("Unable to decode SEND_MESSAGE!\n");
      }
    } break;
    default:
      break;
  }
}

}  // namespace implementation
}  // namespace V1_0
}  // namespace health
}  // namespace hardware
}  // namespace gwm
}  // namespace vendor
