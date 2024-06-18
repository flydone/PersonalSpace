/*************************************************************************
* Copyright (C) 2020-2024 GWM Automotive Inc.
*
* The copyright notice above does not evidence any actual
* or intended publication of such source code.
* The code contains GWM Confidential Proprietary Information.
*************************************************************************/
/**************************************************************************
 * @file CameraFdbClient.h
 * Camera Fdbus Client header
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
#ifndef VENDOR_GWM_HARDWARE_DVR_V1_0_CAMERAFDB_CLIENT_H
#define VENDOR_GWM_HARDWARE_DVR_V1_0_CAMERAFDB_CLIENT_H
#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>
#include <utils/RefBase.h>
#include <common_base/CFdbCJsonMsgBuilder.h>
#include <common_base/CFdbProtoMsgBuilder.h>
#include <common_base/cJSON/cJSON.h>
#include <common_base/fdbus.h>
#include <impl/src/proto/common.base.CameraIviQnx.pb.h>
#include <DVR.h>
#include "PublicDef.h"

namespace vendor {
namespace gwm {
namespace hardware {
namespace camera {
namespace V1_0 {
namespace implementation {

class DVR;
class CameraFdbClient : public CBaseClient, public android::RefBase {
public:
    CameraFdbClient(const char *name, CBaseWorker *worker);
    ~CameraFdbClient();

    virtual void onOffline(FdbSessionId_t sid, bool is_last) override;
    virtual void onOnline(FdbSessionId_t sid, bool is_first) override;
    virtual void onBroadcast(CBaseJob::Ptr &msg_ref) override;
    virtual void onStatus(CBaseJob::Ptr &msg_ref, int error_code,
        const char *description) override;
    virtual void onReply(CBaseJob::Ptr &msg_ref);

    /*DVR IPC interface*/
    GWM_Status sendMessage(FdbMsgCode_t code, CFdbProtoMsgBuilder builder,
        bool is_sync);
    void setDVRClient(android::sp<DVR> drv);
    GWM_DVRIPCStatus isFdbOnline;

private:
    android::sp<DVR> mDVR;
    bool fdb_online = false;
    mutable std::mutex mMutex;

    void subscribeMsg();
    void notifyDVRSystemStatus(const CBaseMessage* msg);
    void notifySetParam(const CBaseMessage* msg);
    void notifyGetParam(const CBaseMessage* msg);
    void notifyFileOperate(const CBaseMessage* msg);
    void notifyVideoOperate(const CBaseMessage* msg);
    void notifyTFCardOperate(const CBaseMessage* msg);
    void notifyFactoryReset(const CBaseMessage* msg);
    void notifyPreviewReply(const CBaseMessage* msg);
    void notifyRecordTimeInfo(const CBaseMessage* msg);
    void notifyRecordStatus(const CBaseMessage* msg);
    void notifyTFStatus(const CBaseMessage* msg);
    void notifyCameraStatus(const CBaseMessage* msg);
    void notifyTFCapacityStatus(const CBaseMessage* msg);
    void notifyTFCapacityCostStatus(const CBaseMessage* msg);
    void notifyDeviceStatus(const CBaseMessage* msg);
    void notifyUploadStatus(const CBaseMessage* msg);
    void notifyUploadFileStatus(const CBaseMessage* msg);
};

}  // namespace implementation
}  // namespace V1_0
}  // namespace rtc
}  // namespace hardware
}  // namespace gwm
}  // namespace vendor
#endif
