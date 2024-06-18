/*************************************************************************
* Copyright (C) 2020-2023 GWM Automotive Inc.
*
* The copyright notice above does not evidence any actual
* or intended publication of such source code.
* The code contains GWM Confidential Proprietary Information.
*************************************************************************/
/**************************************************************************
 * @file CameraFdbServer.h
 * Camera Fdbus server header
 *
 * @project     v3.5
 * @subsystem
 * @version     0.1
 * @author      XiuFang Liu
 * @date        2020-7-17

 Module-History:
 Date(dd.mm.year)| Author            | Reason
 The latest entry at the head of the history list.
 17/7/2020         XiuFang Liu          Init version
 ***************************************************************************/
#ifndef VENDOR_GWM_HARDWARE_DVR_V1_0_CAMERAFDB_SERVER_H
#define VENDOR_GWM_HARDWARE_DVR_V1_0_CAMERAFDB_SERVER_H

#include <common_base/CFdbCJsonMsgBuilder.h>
#include <common_base/CFdbProtoMsgBuilder.h>
#include <common_base/cJSON/cJSON.h>
#include <common_base/fdbus.h>
#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>
#include <utils/RefBase.h>
#include <DVR.h>
#include <impl/src/proto/common.base.CameraIVIServer.pb.h>

namespace vendor {
namespace gwm {
namespace hardware {
namespace camera {
namespace V1_0 {
namespace implementation {

class CameraFdbServer : public CBaseServer, public android::RefBase {
public:
    CameraFdbServer(const char *name, CBaseWorker *worker);
    ~CameraFdbServer();

    void onOnline(FdbSessionId_t sid, bool is_first);
    void onOffline(FdbSessionId_t sid, bool is_last);
    void onSubscribe(CBaseJob::Ptr &msg_ref);
    void onInvoke(CBaseJob::Ptr &msg_ref);
    GWM_Status sendMessage(FdbMsgCode_t code, CFdbProtoMsgBuilder builder);
    GWM_Status sendMessage(FdbMsgCode_t code);
    void setDVRServer(android::sp<DVR> drv);

private:
    android::sp<DVR> m_DVR;
};

}  // namespace implementation
}  // namespace V1_0
}  // namespace camera
}  // namespace hardware
}  // namespace gwm
}  // namespace vendor
#endif