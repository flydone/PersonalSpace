/*************************************************************************
* Copyright (C) 2020-2021 GWM Automotive Inc.
*
* The copyright notice above does not evidence any actual
* or intended publication of such source code.
* The code contains GWM Confidential Proprietary Information.
*************************************************************************/
/**************************************************************************
 * @file Camera.h
 * vendor camera hal implimentation
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
#ifndef VENDOR_GWM_HARDWARE_CAMERA_V1_0_CAMERA_H
#define VENDOR_GWM_HARDWARE_CAMERA_V1_0_CAMERA_H

#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>
#include <vendor/gwm/hardware/camera/1.0/ICamera.h>
#include <utils/RefBase.h>
#include <common_base/fdbus.h>
#include <mutex>
#include <condition_variable>
#include <impl/src/proto/common.base.CameraIviQnx.pb.h>
#include <impl/src/proto/common.base.CameraIVIServer.pb.h>
#include <DVR.h>

namespace vendor {
namespace gwm {
namespace hardware {
namespace camera {
namespace V1_0 {
namespace implementation {

class CameraFdbServer;
class Camera : public ICamera
{
public:
    Camera();
    ~Camera();

    // Methods from ::vendor::gwm::hardware::camera::V1_0::ICamera follow.
    /* DVR interface*/
    android::hardware::Return<android::sp<::vendor::gwm::hardware::camera::V1_0::IDVR>> gwm_getDVRInterface() override;

    /**
     *  @brief initial fdbus
     */
    void init_fdbus();

private:
    android::sp<CameraFdbClient> mCameraFdbClient;
    android::sp<CameraFdbServer> mCameraFdbServer;
    android::sp<IDVR> mDVRInterface;
};

}  // namespace implementation
}  // namespace V1_0
}  // namespace camera
}  // namespace hardware
}  // namespace gwm
}  // namespace vendor
#endif
