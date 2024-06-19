/*************************************************************************
* Copyright (C) 2020-2021 GWM Automotive Inc.
*
* The copyright notice above does not evidence any actual
* or intended publication of such source code.
* The code contains GWM Confidential Proprietary Information.
*************************************************************************/

/**************************************************************************
 * @file HealthFdbusClient.h
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
 21/8/2020         Hong Jiu Jin           Init version

***************************************************************************/
#ifndef vendor_gwm_hardware_health_V1_0_impl_Health_FDBUS_CLIENT_H_
#define vendor_gwm_hardware_health_V1_0_impl_Health_FDBUS_CLIENT_H_

#include <common.base.lifecycle.pb.h>
#include <common_base/CFdbCJsonMsgBuilder.h>
#include <common_base/CFdbProtoMsgBuilder.h>
#include <common_base/cJSON/cJSON.h>
#include <common_base/fdbus.h>
#include "FdbusClientBase.h"
#include "Health.h"

namespace vendor {
namespace gwm {
namespace hardware {
namespace health {
namespace V1_0 {
namespace implementation {


class Health;
class HealthFdbusClient : public FdbusClientBase {
 public:
  HealthFdbusClient(const string &url, const string &name, CBaseWorker *worker,
                    Health *health);
  ~HealthFdbusClient();
  GWM_StatusCode sendHeartBeat(int32_t ivi_status);
  GWM_StatusCode sendRestartReq(int32_t ivi_status);
  virtual void onOffline(FdbSessionId_t sid, bool is_last) override;
  virtual void onOnline(FdbSessionId_t sid, bool is_first) override;
  virtual void onBroadcast(CBaseJob::Ptr &msg_ref) override;
  virtual void onStatus(CBaseJob::Ptr &msg_ref, int32_t error_code,
                        cstr8_t description) override;
  GWM_StatusCode sendMessage(FdbMsgCode_t code, CFdbProtoMsgBuilder builder);
  bool getConnectStatus();
#if 0
  virtual void onReply(CBaseJob::Ptr &msg_ref);
#endif

 private:
  Health *mHealth;
  bool mFdbusOnline;
};
}  // namespace implementation
}  // namespace V1_0
}  // namespace health
}  // namespace hardware
}  // namespace gwm
}  // namespace vendor
#endif
