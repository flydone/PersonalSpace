/*************************************************************************
* Copyright (C) 2020-2021 GWM Automotive Inc.
*
* The copyright notice above does not evidence any actual
* or intended publication of such source code.
* The code contains GWM Confidential Proprietary Information.
*************************************************************************/
/**************************************************************************
 * @file Camera.cpp
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
 17/7/2020         XiuFang Liu         Init version
 ***************************************************************************/
#include <android/log.h>
#include <log/log.h>
#include <sys/time.h>
#include <vendor/gwm/hardware/camera/1.0/ICamera.h>
#include <Camera.h>
#include <CameraFdbClient.h>
#include <CameraFdbServer.h>

#undef LOG_TAG
#define LOG_TAG "CameraHAL_Camera"

static CBaseWorker main_worker;

namespace vendor {
namespace gwm {
namespace hardware {
namespace camera {
namespace V1_0 {
namespace implementation {

using namespace std;
using namespace vendor::gwm::hardware::camera::V1_0;

using ::android::sp;
using ::android::hardware::Return;

Camera::Camera() : mCameraFdbClient(nullptr), mDVRInterface(nullptr) {
    init_fdbus();
}

Camera::~Camera() {}

void Camera::init_fdbus() {
    /* start fdbus context thread */
    FDB_CONTEXT->start();

    /* start worker thread */
    CBaseWorker* worker_ptr = &main_worker;
    worker_ptr->start();

    /* create client to connect mcuipc server */
    std::string cameraipcsrv_name = "fdbus_dvr_service";
    std::string cameraipcsrv_url(FDB_URL_SVC);
    cameraipcsrv_url += cameraipcsrv_name;

    mCameraFdbClient = new CameraFdbClient(cameraipcsrv_name.c_str(), worker_ptr);
    if (mCameraFdbClient == nullptr)
    {
        ALOGE("%s:  mCameraFdbClient == nullptr !", __FUNCTION__);
        return;
    }

    mCameraFdbClient->enableReconnect(true);
    mCameraFdbClient->connect(cameraipcsrv_url.c_str());

    std::string dvr_fdbus_server_name = "dvr_fdbus_interaction";
    string dvr_fdbus_server_url(FDB_URL_SVC);
    dvr_fdbus_server_url += dvr_fdbus_server_name;
    mCameraFdbServer = new CameraFdbServer(dvr_fdbus_server_name.c_str(), worker_ptr);
    if (mCameraFdbServer == nullptr)
    {
        ALOGE("%s:  mCameraFdbServer == nullptr !", __FUNCTION__);
        return;
    }
    mCameraFdbServer->bind(dvr_fdbus_server_url.c_str());
}

Return<sp<::vendor::gwm::hardware::camera::V1_0::IDVR>> Camera::gwm_getDVRInterface() {
    ALOGD("%s:  enter.", __FUNCTION__);
    if (mDVRInterface == nullptr) {
        mDVRInterface = new DVR(mCameraFdbClient,mCameraFdbServer);
    }
    return mDVRInterface;
}

}  // namespace implementation
}  // namespace V1_0
}  // namespace camera
}  // namespace hardware
}  // namespace gwm
}  // namespace vendor
