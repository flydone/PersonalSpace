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
 * @date        2020-10-12

 Module-History:
 Date(dd.mm.year)| Author            | Reason
 The latest entry at the head of the history list.
 10/10/2020         Hong Jiu Jin Init version
 ***************************************************************************/

#ifndef vendor_gwm_hardware_health_V1_0_impl_VIP_THERMAL_CLIENT_H_
#define vendor_gwm_hardware_health_V1_0_impl_VIP_THERMAL_CLIENT_H_

#include <common_base/cJSON/cJSON.h>
#include <common_base/CFdbCJsonMsgBuilder.h>
#include <common_base/CFdbProtoMsgBuilder.h>
#include <common.base.mcuipcfdbus.pb.h>
#include "FdbusClientBase.h"
#include "Health.h"

#define MAX_VIPMSG_LENGTH 16

namespace vendor {
namespace gwm {
namespace hardware {
namespace health {
namespace V1_0 {
namespace implementation {


typedef std::vector<uint8_t> ByteBuffer;

class Health;

class VIPThermalFdbClient : public FdbusClientBase {
 public:
  VIPThermalFdbClient(const string &url, const string &name,
                      CBaseWorker *worker, Health *health);
  ~VIPThermalFdbClient();

  void onOnline(FdbSessionId_t sid, bool is_first);
  void onOffline(FdbSessionId_t sid, bool is_last);
  void onReply(CBaseJob::Ptr &msg_ref);
  void onBroadcast(CBaseJob::Ptr &msg_ref);
  void onStatus(CBaseJob::Ptr &msg_ref, int32_t error_code,
                cstr8_t description);
  void onReceiveVIPMsg(const ByteBuffer &recData, uint32_t data_len);
  GWM_StatusCode sendMessage(FdbMsgCode_t code, const uint8_t *data,
                             int32_t length);

 private:
  Health *mHealth;
};
}  // namespace implementation
}  // namespace V1_0
}  // namespace health
}  // namespace hardware
}  // namespace gwm
}  // namespace vendor
#endif
