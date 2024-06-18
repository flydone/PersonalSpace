/*************************************************************************
 * Copyright (C) 2023 GWM Automotive Inc.
 *
 * The copyright notice above does not evidence any actual
 * or intended publication of such source code.
 * The code contains GWM Confidential Proprietary Information.
 *************************************************************************/
/**************************************************************************
 * @file DVRFdbProxy.h
 * DVRFdbProxy
 *
 * @project     v3.5
 * @subsystem
 * @version     0.1
 * @author
 * @date        2023-9-8

 Module-History:
 Date(dd.mm.year)| Author            | Reason
 The latest entry at the head of the history list.
 8/9/2023         Zhao Ying           Init version
***************************************************************************/
#ifndef VENDOR_GWM_HARDWARE_DVR_V1_0_DVR_FDB_PROXY_H
#define VENDOR_GWM_HARDWARE_DVR_V1_0_DVR_FDB_PROXY_H

#include <utils/RefBase.h>
#include <vendor/gwm/hardware/camera/1.0/IDVR.h>
#include "CameraFdbClient.h"
#include "CameraFdbServer.h"

namespace vendor {
namespace gwm {
namespace hardware {
namespace camera {
namespace V1_0 {
namespace implementation {

class CameraFdbClient;
class CameraFdbServer;
class DVRFdbProxy : public android::RefBase
{
public:
    DVRFdbProxy(android::sp<CameraFdbClient> fdbClient, android::sp<CameraFdbServer> fdbServer);
    ~DVRFdbProxy();

    GWM_Status startPreview(::vendor::gwm::hardware::camera::V1_0::GWM_DVRCameraId cameraId);
    GWM_Status stopPreview(::vendor::gwm::hardware::camera::V1_0::GWM_DVRCameraId cameraId);
    GWM_Status startRecord(::vendor::gwm::hardware::camera::V1_0::GWM_DVRCameraId cameraId,
        ::vendor::gwm::hardware::camera::V1_0::GWM_DVR_VIDEO_TYPE type);
    GWM_Status stopRecord(::vendor::gwm::hardware::camera::V1_0::GWM_DVRCameraId cameraId,
        ::vendor::gwm::hardware::camera::V1_0::GWM_DVR_VIDEO_TYPE type);
    GWM_Status startCapture(::vendor::gwm::hardware::camera::V1_0::GWM_DVRCameraId cameraId,
        ::vendor::gwm::hardware::camera::V1_0::GWM_DVR_VIDEO_TYPE type);
    GWM_Status startLapseVideo(::vendor::gwm::hardware::camera::V1_0::GWM_DVRCameraId cameraId,
                                int64_t timeLapseVideoInteval,
                                int16_t totalFrameNumber,
                                int16_t playFrameNumber);
    GWM_Status stopLapseVideo(::vendor::gwm::hardware::camera::V1_0::GWM_DVRCameraId cameraId);
    GWM_Status formatTFCard(::vendor::gwm::hardware::camera::V1_0::GWM_DVR_TFCardId tfcard_id);
    GWM_Status resetFactory();
    GWM_Status querySystemInfoFromQNX();
    GWM_Status operateFile(const ::vendor::gwm::hardware::camera::V1_0::GWM_DVR_FileOperateAction &operation);
    GWM_Status setParam(const ::vendor::gwm::hardware::camera::V1_0::GWM_DVRSetParam &params);
    GWM_Status getParam();
    GWM_Status uploadRequset();
    GWM_Status uploadResult(const ::vendor::gwm::hardware::camera::V1_0::GWM_DVRUploadFileResult &uploadResult);
    GWM_Status sendActCommd(const ::vendor::gwm::hardware::camera::V1_0::GWM_DVRBroadcastActCommand &boardcastActions);
    GWM_Status sendModuleEvent(const ::vendor::gwm::hardware::camera::V1_0::GWM_DVRSendModuleEvent &moduleEvent);

private:
    android::sp<CameraFdbClient> mCameraFdbClient;
    android::sp<CameraFdbServer> mCameraFdbServer;
};

}
}
}
}
}
}
#endif // VENDOR_GWM_HARDWARE_DVR_V1_0_DVR_FDB_PROXY_H