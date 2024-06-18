/*************************************************************************
 * Copyright (C) 2020-2023 GWM Automotive Inc.
 *
 * The copyright notice above does not evidence any actual
 * or intended publication of such source code.
 * The code contains GWM Confidential Proprietary Information.
 *************************************************************************/
/**************************************************************************
 * @file DVR.cpp
 * camera DVR function implemention.
 *
 * @project     v3.5
 * @subsystem
 * @version     0.1
 * @author      XiuFang Liu
 * @date        2020-10-13

 Module-History:
 Date(dd.mm.year)| Author            | Reason
 The latest entry at the head of the history list.
 13/10/2020         XiuFang Liu         Init version
 9/12/2020          Hong Jiu Jin        Update, clean code
 ***************************************************************************/
#include <android/log.h>
#include <log/log.h>
#include <thread>
#include <fstream>
#include "DVR.h"
#include "CameraFdbClient.h"
#include "CameraFdbServer.h"
#include "DVRConnectionTimer.h"
#include "DVRFdbProxy.h"
#include "DVRMessageHandler.h"

#undef LOG_TAG
#define LOG_TAG "CameraHAL_DVR"

namespace vendor {
namespace gwm {
namespace hardware {
namespace camera {
namespace V1_0 {
namespace implementation {

using namespace std;
using namespace CameraFdb;
using namespace DVRFdb;
using namespace vendor::gwm::hardware::camera::V1_0;

using ::android::hardware::hidl_array;
using ::android::hardware::hidl_memory;
using ::android::hardware::hidl_string;
using ::android::hardware::hidl_vec;
using ::android::hardware::Return;
using ::android::hardware::Void;
using ::android::sp;
using ::android::wp;
using ::vendor::gwm::common::hardware::psservice::hidl::V1_0::IPSSHidlInterface;
using ::vendor::gwm::common::hardware::psservice::hidl::V1_0::IPSSHidlCallback;
using ::vendor::gwm::common::hardware::psservice::hidl::V1_0::GWM_VCfg_KindID;

bool mDVRInternal = false;
// only for ext dvr.
bool isExDVRReady = false;
/* only for ext dvr front camera.
 * value:
 *  DEFAULT = 0xFF,
 *  STATUS_OK = 0x00,
 *  STATUS_FAULT = 0x01
 */
uint8_t mCameraFrontStatus = 0xFFU;
/* only for ext dvr inner camera.
 * value:
 *  DEFAULT：0
 *  OK:1
 *  FAULT:2
 */
uint8_t mCameraInnerStatus = 0xFFU;
/* only for ext dvr avm camera.
 * value:
 *  DEFAULT = 0xFF,
 *  STATUS_OK = 0x00,
 *  STATUS_FAULT = 0x01
 */
uint8_t mCameraAVMStatus = 0xFFU;
/* only for ext dvr TF1.
 */
TFCardStatus_DT mTfCard1Status = TFCardStatus_DT::E_DVR_NOT_FOUND;
DVRMessage_t mDvrMsg;

class DVRSystemListener : public DVRStatusReportListener,
                          public IDC1_5SystemFunctionsListener
{
public:
    explicit DVRSystemListener(sp<DVR> dvr) : mDVR(dvr)
    {
    }

    ~DVRSystemListener()
    {
    }

    /**
     * @brief VideoUpload comes from IDC1.5SystemFunctions service of someip.
     * serviceid:0x0B01
     * methodid: 0x0001
     */
    virtual void VideoUploadEventListener(DataCollectTriggerStruct_DT dataCollectTriggerStructDt)
    {
        ALOGI("%s:  sysTimeUsDt:%ld, collectBeforeTimeDt:%d, collectAfterTimeDt:%d, triggerTypeDt:%d, trigger_subtypeDt:%d",
            __FUNCTION__,
            (uint64_t)dataCollectTriggerStructDt.sysTimeUsDt,
            (uint32_t)dataCollectTriggerStructDt.collectBeforeTimeDt,
            (uint32_t)dataCollectTriggerStructDt.collectAfterTimeDt,
            (uint32_t)dataCollectTriggerStructDt.triggerTypeDt,
            (uint32_t)dataCollectTriggerStructDt.trigger_subtypeDt);
        std::lock_guard<std::mutex> lock(mDVR->mMutex);
        if (mDVR == nullptr)
        {
            ALOGE("%s:  mDVR == nullptr !", __FUNCTION__);
            return;
        }
        mDVR->onVideoUploadEventListener(dataCollectTriggerStructDt);
    }

    /**
     * @brief DVRSystemStatusReport comes from DVRStatusReport service of someip.
     * serviceid:0x0401
     * methodid: 0x9001
     */
    virtual void DVRSystemStatusReportListener(DVRSystemStatus_DT dVRSystemStatusDt)
    {
        /* dVRSystemStatus:
         *    E_DVR_STATUS_OK = 0,
         *    E_DVR_STATUS_FAULT = 1
         */
        ALOGI("%s:  dVRSystemStatusDt:%d", __FUNCTION__, dVRSystemStatusDt);
        std::lock_guard<std::mutex> lock(mDVR->mMutex);
        if (mDVR == nullptr)
        {
            ALOGE("%s:  mDVR == nullptr !", __FUNCTION__);
            return;
        }
        mDVR->onDVRSystemStatusReportListener(dVRSystemStatusDt);
    }

    //This method had removed from GWM_GEEP_Platform_SOMEIP_Static_InterfaceDescription_V2.2.
    /*
    virtual void OMCStatusReportACKListener(SetResult_DT statusReportACKDt)
    {
        ALOGI("%s:  statusReportACKDt:%d", __FUNCTION__, statusReportACKDt);
        std::lock_guard<std::mutex> lock(mDVR->mMutex);
        if (mDVR == nullptr)
        {
            ALOGE("%s:  mDVR == nullptr !", __FUNCTION__);
            return;
        }
        mDVR->onOMCStatusReportACKListener(statusReportACKDt);
    }
    */

    /**
     * @brief DVRSensorStatusReport comes from DVRStatusReport service of someip.
     * serviceid:0x0401
     * methodid: 0x9002
     */
    virtual void DVRSensorStatusReportListener(DVRSensorStatusStruct_DT dVRSensorStatusStructDt)
    {
        /* accesstype:
         *    E_FORESIGHT = 0,
         *    E_WITHINSIGNT_OMC = 1,
         *    E_STREAMINGMEDIA_OR_BACKSIGNT_RESERVED = 2,
         *    E_360SURROUNDVIEW = 3,
         *    E_MULTICHANNEL = 4,
         *    E_WITHINSIGNT_DMC = 5
         * dvrSensorStatus:
         *     E_SENSOR_OK = 0,
         *     E_SENSOR_FAULT = 1,
         *     E_SENSOR_INIT = 2
         */
        ALOGI("%s:  statusReportACKDt[accesstype:%d, dvrSensorStatus:%d]",
            __FUNCTION__,
            dVRSensorStatusStructDt.accessTypeDt,
            dVRSensorStatusStructDt.dvrSensorStatusDt);
        std::lock_guard<std::mutex> lock(mDVR->mMutex);
        if (mDVR == nullptr)
        {
            ALOGE("%s:  mDVR == nullptr !", __FUNCTION__);
            return;
        }
        //ExtDVR only report E_FORESIGHT, E_WITHINSIGNT_OMC and E_360SURROUNDVIEW.
        mDVR->onDVRSensorStatusReportListener(dVRSensorStatusStructDt);
    }

    /**
     * @brief EventOperationReport comes from DVRStatusReport service of someip.
     * serviceid:0x0401
     * methodid: 0x8001
     */
    virtual void EventOperationReportEventListener(EventOperationType_DT eventOperationTypeDt, EventType_DT eventTypeDt, AccessType_DT accessTypeDt)
    {
        /* eventOperationTypeDt:
         *  E_EVENTSTART = 0,
         *  E_EVENTSTOP = 1,
         *  E_EVENTFAILED = 2
         * eventTypeDt:
         *  E_MANUALCAPTURE_BYBUTTON = 0,
         *  E_MANUALCAPTURE_BYHUT = 1,
         *  E_MANUALRECORDING_BYBUTTON = 2,
         *  E_MANUALRECORDING_BYHUT = 3,
         *  E_TIMELAPSEVIDEO = 4,
         *  E_PARKINGMONITORVIDEO = 5,
         *  E_VEHICLECOLLISIONVIDEO = 6,
         *  E_AIRBAGEJECTIONVIDEO = 7,
         *  E_AEBVIDEO = 8,
         *  E_BURGLARALARMVIDEO = 9,
         *  E_CONTINUOUSCAPTURE = 10,
         *  E_SHORTVIDEORECORDING_BYBUTTON = 11,
         *  E_SHORTVIDEORECORDING_BYHUT = 12,
         *  E_APSVIDEO = 13,
         *  E_ACC_AEBVIDEO = 14,
         *  E_WHISTLEVIDEO = 15,
         *  E_RADARRINGINGVIDEO = 16,
         *  E_MEBVIDEO = 17,
         *  E_HANDLEFTVIDEO = 18,
         *  E_CARINGMODE = 19,
         *  E_EXPORTFILE = 20,
         *  E_GUARDIANMODE = 21,
         *  E_DELETEFILE = 22,
         *  E_MANUALCAPTURE_BYFINDCAR = 23,
         *  E_SENTINELMODE_HIGH = 24,
         *  E_SENTINELMODE_LOW = 25
         */
        ALOGI("%s:  eventOperationTypeDt:%d, eventTypeDt:%d, accessTypeDt:%d",
            __FUNCTION__,
            eventOperationTypeDt,
            eventTypeDt,
            accessTypeDt);
        std::lock_guard<std::mutex> lock(mDVR->mMutex);
        if (mDVR == nullptr) {
            ALOGE("%s:  mDVR == nullptr !", __FUNCTION__);
            return;
        }
        mDVR->onEventOperationReportEventListener(eventOperationTypeDt,eventTypeDt,accessTypeDt);
    }

    /**
     * @brief DVREventReport comes from DVRStatusReport service of someip.
     * serviceid:0x0401
     * methodid: 0x8002
     */
    virtual void DVREventReportEventListener(char *eventTime, EventType_DT eventTypeDt, AccessType_DT accessTypeDt, char *filePath, char *thumbnailPath)
    {
        ALOGI("%s:  eventTime:%s, eventTypeDt:%d, accessTypeDt:%d, filePath:%s, thumbnailPath:%s",
            __FUNCTION__,
            eventTime,
            eventTypeDt,
            accessTypeDt,
            filePath,
            thumbnailPath);
        std::lock_guard<std::mutex> lock(mDVR->mMutex);
        if (mDVR == nullptr)
        {
            ALOGE("%s:  mDVR == nullptr !", __FUNCTION__);
            return;
        }
        mDVR->onDVREventReportEventListener(eventTime, eventTypeDt, accessTypeDt, filePath, thumbnailPath);
    }

    /**
     * @brief DVRTFStatusReport comes from DVRStatusReport service of someip.
     * serviceid:0x0401
     * methodid: 0x8003
     */
    virtual void DVRTFStatusReportEventListener(TFCardOption_DT tFCardOptionDt, TFCardStatus_DT tFCardStatusDt, TFCardCapacity_DT tFCardCapacityDt)
    {
        /* tFCardOption:
         *   E_TFCARD1 = 0,
         *   E_TFCARD2 = 1
         * tFCardStatus:
         *   E_DVR_NOT_FOUND = 0,
         *   E_DVR_FAULT = 1,
         *   E_DVR_MEMEORY_FULL = 2,
         *   E_DVR_OK = 3,
         *   E_WRITESLOWLY = 4,
         *   E_DVR_EMERGENCY_SPACE_FULL = 5,
         *   E_DVR_CAPACITY_NOT_SUPPORTED = 6
         */
        ALOGI("%s:  tFCardOptionDt:%d, tFCardStatusDt:%d, tFCardCapacityDt[totalCapacity:%d, remainingCapacity:%d]",
            __FUNCTION__,
            tFCardOptionDt,
            tFCardStatusDt,
            tFCardCapacityDt.totalCapacity,
            tFCardCapacityDt.remainingCapacity);
        std::lock_guard<std::mutex> lock(mDVR->mMutex);
        if (mDVR == nullptr)
        {
            ALOGE("%s:  mDVR == nullptr !", __FUNCTION__);
            return;
        }
        mDVR->onDVRTFStatusReportEventListener(tFCardOptionDt, tFCardStatusDt, tFCardCapacityDt);
    }

    /**
     * @brief DVREMMCStatusReportEvent comes from DVRStatusReport service of someip.
     * serviceid:0x0401
     * methodid: 0x8004
     */
    virtual void DVREMMCStatusReportEventListener(EMMCStatus_DT eMMCStatusDt, EMMCCapacityStruct_DT eMMCCapacityStructDt)
    {
        /* eMMCStatus:
         *    E_EMMCNORMAL = 0,
         *    E_EMMCFAULT = 1
         */
        ALOGI("%s:  eMMCStatusDt:%d, eMMCCapacityStructDt[totalCapacity:%d, remainingCapacity:%d]",
            __FUNCTION__,
            eMMCStatusDt,
            eMMCCapacityStructDt.totalCapacity,
            eMMCCapacityStructDt.remainingCapacity);
        std::lock_guard<std::mutex> lock(mDVR->mMutex);
        if (mDVR == nullptr)
        {
            ALOGE("%s:  mDVR == nullptr !", __FUNCTION__);
            return;
        }
        mDVR->onDVREMMCStatusReportEventListener(eMMCStatusDt, eMMCCapacityStructDt);
    }

    /**
     * @brief ExportOperationProgressReport comes from DVRStatusReport service of someip.
     * serviceid:0x0401
     * methodid: 0x8005
     */
    virtual void ExportOperationProgressReportEventListener(ExportFileInfoStruct_DT exportFileInfoStructDt, TotalTransProgress totalTransProgress)
    {
        ALOGI("%s:  exportFileInfoStructDt[currentTransProgress:%d, filePath:%s], totalTransProgress:%hhu",
            __FUNCTION__,
            exportFileInfoStructDt.currentTransProgress,
            exportFileInfoStructDt.filePath,
            totalTransProgress);
        std::lock_guard<std::mutex> lock(mDVR->mMutex);
        if (mDVR == nullptr)
        {
            ALOGE("%s:  mDVR == nullptr !", __FUNCTION__);
            return;
        }
        mDVR->onExportOperationProgressReportEventListener(exportFileInfoStructDt, totalTransProgress);
    }

    /**
     * @brief AsyncDeleteOperationProgress comes from DVRStatusReport service of someip.
     * serviceid:0x0401
     * methodid: 0x8007
     */
    virtual void AsyncDeleteOperationProgressEventListener(DeleteProgress deleteProgress)
    {
        ALOGI("%s:  deleteProgress:%hhu",
            __FUNCTION__,
            deleteProgress);
        std::lock_guard<std::mutex> lock(mDVR->mMutex);
        if (mDVR == nullptr)
        {
            ALOGE("%s:  mDVR == nullptr !", __FUNCTION__);
            return;
        }
        mDVR->onAsyncDeleteOperationProgressEventListener(deleteProgress);
    }

private:
    sp<DVR> mDVR;
};

DVR::DVR(const sp<CameraFdbClient> client, const sp<CameraFdbServer> server)
    : mCameraFdbClient(client), mCameraFdbServer(server)
{

    char appName[10] = "DVRHAL";
    char configFile[45] = "/vendor/etc/someip/DVRVIMSFunctions.json";

    IDC1_5SystemFunctionsInit(appName, configFile);
    DVRStatusReportInit(appName, configFile);
    DVRSystemConfigInit(appName, configFile);
    DVRFileOperationInit(appName, configFile);

    static DVRSystemListener listener(this);
    ALOGI("%s:  DVRSystemListener:%p", __FUNCTION__, &listener);
    IDC1_5SystemFunctionsListenerRegister(&listener);
    DVRStatusReportListenerRegister(&listener);

    memset(&mSetupParamResult, 0, sizeof(mSetupParamResult));
    memset(&mSystemStatusInfo, 0, sizeof(mSystemStatusInfo));
    memset(&mDVRSystemStatus, 0, sizeof(mDVRSystemStatus));
    memset(&mOMCStatus, 0, sizeof(mOMCStatus));
    memset(&mDVRSensorStatus, 0, sizeof(mDVRSensorStatus));
    memset(&mEventOperationReport, 0, sizeof(mEventOperationReport));
    memset(&mDVRTFStatus, 0, sizeof(mDVRTFStatus));
    memset(&mDVREMMCStatus, 0, sizeof(mDVREMMCStatus));
    memset(&mDvrMsg, 0, sizeof(mDvrMsg));
    mDVRCallbackList.reserve(5U);
    mDVRCallbackList.clear();

    if(mCameraFdbClient == nullptr)
    {
        ALOGE("%s:  mCameraFdbClient == nullptr!", __FUNCTION__);
        return;
    }
    mCameraFdbClient->setDVRClient(this);

    if(mCameraFdbServer == nullptr)
    {
        ALOGE("%s:  mCameraFdbServer == nullptr!", __FUNCTION__);
        return;
    }
    mCameraFdbServer->setDVRServer(this);

    mConnTimer = new DVRConnectionTimer(this);
    mDVRFdbProxy = new DVRFdbProxy(mCameraFdbClient, mCameraFdbServer);
    mMessageHandler = new DVRMessageHandler(this);

    std::thread([this]{
        getDVRPssCFG();
        if (!mDVRInternal)
        {
            if (mConnTimer == nullptr)
            {
                ALOGE("%s:  mConnTimer is null !", __FUNCTION__);
                return;
            }
            mConnTimer->startTimer();

            if (mMessageHandler == nullptr)
            {
                ALOGE("%s:  mMessageHandler is null !", __FUNCTION__);
                return;
            }
            mMessageHandler->startWorkThread();
        }
    }).detach();
}

DVR::~DVR()
{
    for(auto callback : mDVRCallbackList)
    {
        if (!checkCallbackIsNull(callback))
        {
            callback->unlinkToDeath(this);
        }
    }
    mDVRCallbackList.clear();

    if(mConnTimer == nullptr)
    {
        ALOGE("%s:  mConnTimer is null !", __FUNCTION__);
        return;
    }
    else
    {
        mConnTimer->stopTimer();
    }

    if(mMessageHandler == nullptr)
    {
        ALOGE("%s:  mMessageHandler is null !", __FUNCTION__);
        return;
    }
    else
    {
        mMessageHandler->stopWorkThread();
    }
}

void DVR::serviceDied(uint64_t cookie, const android::wp<IBase> &who)
{
    std::lock_guard<std::mutex> lock(mMutex);
    for(it = mDVRCallbackList.begin(); it != mDVRCallbackList.end(); ++it)
    {
        if (it->get() != nullptr)
        {
            if (cookie == reinterpret_cast<uint64_t>(it->get())) {
                ALOGW("%s:  service:%lx died, remove it !!!", __FUNCTION__, cookie);
                mDVRCallbackList.erase(it);
                break;
            }
        }
        else
        {
            ALOGE("%s:  callback is null!", __FUNCTION__);
        }
    }
}

/**
 * @brief provide the functionality of register callback to FWK.
 * @param callback
 * @return GWM_Status processing status.
 */
Return<GWM_Status> DVR::gwm_registerDVRCallback(const sp<IDVRCallback>& callback)
{
    std::lock_guard<std::mutex> lock(mMutex);
    if (callback == nullptr)
    {
        ALOGE("%s:  callback == nullptr !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    for(auto call : mDVRCallbackList)
    {
        if (call == callback.get())
        {
            ALOGW("%s:  callback:%lx is register already !", __FUNCTION__, reinterpret_cast<uint64_t>(callback.get()));
            return GWM_Status::GWM_ERROR;
        }
    }
    mDVRCallbackList.push_back(callback);
    callback->linkToDeath(this, reinterpret_cast<uint64_t>(callback.get()) /*cookies*/);
    ALOGI("%s:  callback:%lx register, callbackList:%lu !",
        __FUNCTION__,
        reinterpret_cast<uint64_t>(callback.get()),
        mDVRCallbackList.size());

    if (mMessageHandler == nullptr)
    {
        ALOGE("%s:  mMessageHandler == nullptr!", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }
    mMessageHandler->setDVRCallback(mDVRCallbackList);

    if(mCameraFdbClient == nullptr)
    {
        ALOGE("%s:  mCameraFdbClient == nullptr!", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }
    mIPCStatus = mCameraFdbClient->isFdbOnline;
    auto ret = callback->gwm_onDVRIPCStatusNotify(mIPCStatus);
    if (!ret.isOk())
    {
        ALOGW("%s:  has error", __FUNCTION__);
    }

    // send cache event to FWK.
    bool dvrSystemStatusNotify = mDVRSystemStatus.needNotify;
    bool omcStatusNotify = mOMCStatus.needNotify;
    bool dvrSensorStatusNotify = mDVRSensorStatus.needNotify;
    bool eventOperationReportNotify = mEventOperationReport.needNotify;
    bool dvrTFStatusNotify = mDVRTFStatus.needNotify;
    bool dvrEMMCStatusNotify = mDVREMMCStatus.needNotify;
    ALOGI("%s:  dvrSystemStatusNotify:%d, omcStatusNotify:%d, dvrSensorStatusNotify:%d, eventOperationReportNotify:%d, dvrTFStatusNotify:%d, dvrEMMCStatusNotify:%d",
        __FUNCTION__,
        dvrSystemStatusNotify,
        omcStatusNotify,
        dvrSensorStatusNotify,
        eventOperationReportNotify,
        dvrTFStatusNotify,
        dvrEMMCStatusNotify);
    if (dvrSystemStatusNotify)
    {
        onDVRSystemStatusReportListener(mDVRSystemStatus.dVRSystemStatus);
        memset(&mDVRSystemStatus, 0, sizeof(mDVRSystemStatus));
    }

    // This method had removed from GWM_GEEP_Platform_SOMEIP_Static_InterfaceDescription_V2.2.
    /*
    if (omcStatusNotify)
    {
        onOMCStatusReportACKListener(mOMCStatus.statusReportACK);
        memset(&mOMCStatus, 0, sizeof(mOMCStatus));
    }
    */

    if (dvrSensorStatusNotify)
    {
        for (DVRSensorStatusStruct_DT sensorStatus: mDVRSensorStatus.dVRSensorStatusStruct)
        {
            onDVRSensorStatusReportListener(sensorStatus);
        }
        memset(&mDVRSensorStatus, 0, sizeof(mDVRSensorStatus));
    }

    if (eventOperationReportNotify)
    {
        onEventOperationReportEventListener(mEventOperationReport.eventOperationType, mEventOperationReport.eventType, mEventOperationReport.accessType);
        memset(&mEventOperationReport, 0, sizeof(mEventOperationReport));
    }

    if (dvrTFStatusNotify)
    {
        onDVRTFStatusReportEventListener(mDVRTFStatus.tFCardOption, mDVRTFStatus.tFCardStatus, mDVRTFStatus.tFCardCapacity);
        memset(&mDVRTFStatus, 0, sizeof(mDVRTFStatus));
    }

    if (dvrEMMCStatusNotify)
    {
        onDVREMMCStatusReportEventListener(mDVREMMCStatus.eMMCStatus, mDVREMMCStatus.eMMCCapacityStruct);
        memset(&mDVREMMCStatus, 0, sizeof(mDVREMMCStatus));
    }

    return GWM_Status::GWM_OK;
}

/**
 * @brief provide the functionality of start preview to FWK.
 * @param cameraId
 * @return GWM_Status processing status.
 */
Return<GWM_Status> DVR::gwm_startPreview(GWM_DVRCameraId cameraId)
{
    std::lock_guard<std::mutex> lock(mMutex);
    ALOGI("%s:  cameraId:%hu", __FUNCTION__, cameraId);
    GWM_Status status = GWM_Status::GWM_ERROR;
    if (mDVRInternal)
    {
        if(mDVRFdbProxy == nullptr)
        {
            ALOGE("%s:  mDVRFdbProxy == nullptr!", __FUNCTION__);
            return GWM_Status::GWM_ERROR;
        }
        status = mDVRFdbProxy->startPreview(cameraId);
    }
    else
    {
        if (mMessageHandler == nullptr)
        {
            ALOGE("%s:  mMessageHandler == nullptr !", __FUNCTION__);
            return GWM_Status::GWM_ERROR;
        }

        memset(&mDvrMsg, 0, sizeof(mDvrMsg));
        mDvrMsg.id = DVRMessageId::START_PREVIEW;
        mDvrMsg.cameraId = cameraId;
        if (mMessageHandler->sendDVRMessage(mDvrMsg))
        {
            status = GWM_Status::GWM_OK;
        }
    }

    return status;
}

/**
 * @brief provide the functionality of stop preview to FWK.
 * @param cameraId
 * @return GWM_Status processing status.
 */
Return<GWM_Status> DVR::gwm_stopPreview(GWM_DVRCameraId cameraId)
{
    std::lock_guard<std::mutex> lock(mMutex);
    ALOGI("%s:  cameraId:%hu", __FUNCTION__, cameraId);
    GWM_Status status = GWM_Status::GWM_ERROR;
    if (mDVRInternal)
    {
        if(mDVRFdbProxy == nullptr)
        {
            ALOGE("%s:  mDVRFdbProxy == nullptr!", __FUNCTION__);
            return GWM_Status::GWM_ERROR;
        }
        status = mDVRFdbProxy->stopPreview(cameraId);
    }
    else
    {
        if (mMessageHandler == nullptr)
        {
            ALOGE("%s:  mMessageHandler == nullptr !", __FUNCTION__);
            return GWM_Status::GWM_ERROR;
        }

        memset(&mDvrMsg, 0, sizeof(mDvrMsg));
        mDvrMsg.id = DVRMessageId::STOP_PREVIEW;
        mDvrMsg.cameraId = cameraId;
        if (mMessageHandler->sendDVRMessage(mDvrMsg))
        {
            status = GWM_Status::GWM_OK;
        }
    }

    return status;
}

/**
 * @brief provide the functionality of start short video recording or regular video recording to FWK.
 * @param cameraId
 * @param type action type: GWM_DVR_VIDEO_TYPE_SHORT, GWM_DVR_VIDEO_TYPE_LONG
 * @return GWM_Status processing status.
 */
Return<GWM_Status> DVR::gwm_userStartRecord(GWM_DVRCameraId cameraId, GWM_DVR_VIDEO_TYPE type)
{
    std::unique_lock<std::mutex> lock(mMutex);
    ALOGI("%s:  cameraId:%hu, type:%hhu", __FUNCTION__, cameraId, type);
    GWM_Status status = GWM_Status::GWM_ERROR;
    if (mDVRInternal)
    {
        if(mDVRFdbProxy == nullptr)
        {
            ALOGE("%s:  mDVRFdbProxy == nullptr!", __FUNCTION__);
            return GWM_Status::GWM_ERROR;
        }
        status = mDVRFdbProxy->startRecord(cameraId, type);
    }
    else
    {
        sendMsgToQnxForOMSStream(cameraId,
            GWM_DVRVideoOperateType::GWM_DVR_VIDEO_OPERATE_START,
            type);

        if (mMessageHandler == nullptr)
        {
            ALOGE("%s:  mMessageHandler == nullptr !", __FUNCTION__);
            return GWM_Status::GWM_ERROR;
        }

        memset(&mDvrMsg, 0, sizeof(mDvrMsg));
        mDvrMsg.id = DVRMessageId::START_RECORD;
        mDvrMsg.cameraId = cameraId;
        mDvrMsg.videoType = type;
        if (mMessageHandler->sendDVRMessage(mDvrMsg))
        {
            status = GWM_Status::GWM_OK;
        }
    }
    return status;
}

/**
 * @brief provide the functionality of start short video recording or regular video recording to FWK.
 *        this is a synchronous method, it carries the risk of being time-consuming.
 * @param cameraId
 * @param type action type: GWM_DVR_VIDEO_TYPE_SHORT, GWM_DVR_VIDEO_TYPE_LONG
 * @return GWM_Status processing status.
 */
Return<GWM_Status> DVR::gwm_userStartRecord_sync(GWM_DVRCameraId cameraId, GWM_DVR_VIDEO_TYPE type)
{
    std::unique_lock<std::mutex> lock(mMutex);
    ALOGI("%s:  cameraId:%hu, type:%hhu", __FUNCTION__, cameraId, type);
    GWM_Status status = GWM_Status::GWM_ERROR;
    if (mDVRInternal)
    {
        if(mDVRFdbProxy == nullptr)
        {
            ALOGE("%s:  mDVRFdbProxy == nullptr!", __FUNCTION__);
            return GWM_Status::GWM_ERROR;
        }
        status = mDVRFdbProxy->startRecord(cameraId, type);
    }
    else
    {
        sendMsgToQnxForOMSStream(cameraId,GWM_DVRVideoOperateType::GWM_DVR_VIDEO_OPERATE_START,type);
        status = startRecord(cameraId, type);
    }
    return status;
}

/**
 * @brief provide the functionality of stop short video recording or regular video recording to FWK.
 * @param cameraId
 * @param type action type: GWM_DVR_VIDEO_TYPE_SHORT, GWM_DVR_VIDEO_TYPE_LONG
 * @return GWM_Status processing status.
 */
Return<GWM_Status> DVR::gwm_userStopRecord(GWM_DVRCameraId cameraId, GWM_DVR_VIDEO_TYPE type)
{
    std::unique_lock<std::mutex> lock(mMutex);
    ALOGI("%s:  cameraId:%hu, type:%hhu", __FUNCTION__, cameraId, type);
    GWM_Status status = GWM_Status::GWM_ERROR;
    if (mDVRInternal)
    {
        if(mDVRFdbProxy == nullptr)
        {
            ALOGE("%s:  mDVRFdbProxy == nullptr!", __FUNCTION__);
            return GWM_Status::GWM_ERROR;
        }
        status = mDVRFdbProxy->stopRecord(cameraId, type);
    }
    else
    {
        if (mMessageHandler == nullptr)
        {
            ALOGE("%s:  mMessageHandler == nullptr !", __FUNCTION__);
            return GWM_Status::GWM_ERROR;
        }

        memset(&mDvrMsg, 0, sizeof(mDvrMsg));
        mDvrMsg.id = DVRMessageId::STOP_RECORD;
        mDvrMsg.cameraId = cameraId;
        mDvrMsg.videoType = type;
        if (mMessageHandler->sendDVRMessage(mDvrMsg))
        {
            status = GWM_Status::GWM_OK;
        }
    }
    return status;
}

/**
 * @brief provide the functionality of stop short video recording or regular video recording to FWK.
 *        this is a synchronous method, it carries the risk of being time-consuming.
 * @param cameraId
 * @param type action type: GWM_DVR_VIDEO_TYPE_SHORT, GWM_DVR_VIDEO_TYPE_LONG
 * @return GWM_Status processing status.
 */
Return<GWM_Status> DVR::gwm_userStopRecord_sync(GWM_DVRCameraId cameraId, GWM_DVR_VIDEO_TYPE type)
{
    std::unique_lock<std::mutex> lock(mMutex);
    ALOGI("%s:  cameraId:%hu, type:%hhu", __FUNCTION__, cameraId, type);
    GWM_Status status = GWM_Status::GWM_ERROR;
    if (mDVRInternal)
    {
        if(mDVRFdbProxy == nullptr)
        {
            ALOGE("%s:  mDVRFdbProxy == nullptr!", __FUNCTION__);
            return GWM_Status::GWM_ERROR;
        }
        status = mDVRFdbProxy->stopRecord(cameraId, type);
    }
    else
    {
        status = stopRecord(cameraId, type);
    }
    return status;
}

/**
 * @brief provide the functionality of start capture to FWK.
 * @param cameraId
 * @param type action type: GWM_DVR_CAPTURE, GWM_DVR_CAPTURE_CONTINUOUS
 * @return GWM_Status processing status.
 */
Return<GWM_Status> DVR::gwm_startCapture(GWM_DVRCameraId cameraId, GWM_DVR_VIDEO_TYPE type)
{
    std::unique_lock<std::mutex> lock(mMutex);
    ALOGI("%s:  cameraId:%hu, type:%hhu", __FUNCTION__, cameraId, type);
    GWM_Status status = GWM_Status::GWM_ERROR;
    if (mDVRInternal)
    {
        if(mDVRFdbProxy == nullptr)
        {
            ALOGE("%s:  mDVRFdbProxy == nullptr!", __FUNCTION__);
            return GWM_Status::GWM_ERROR;
        }
        status = mDVRFdbProxy->startCapture(cameraId, type);
    }
    else
    {
        if (mMessageHandler == nullptr)
        {
            ALOGE("%s:  mMessageHandler == nullptr !", __FUNCTION__);
            return GWM_Status::GWM_ERROR;
        }

        memset(&mDvrMsg, 0, sizeof(mDvrMsg));
        mDvrMsg.id = DVRMessageId::START_CAPTURE;
        mDvrMsg.cameraId = cameraId;
        mDvrMsg.videoType = type;
        if (mMessageHandler->sendDVRMessage(mDvrMsg))
        {
            status = GWM_Status::GWM_OK;
        }
    }
    return status;
}

/**
 * @brief provide the functionality of stop capture to FWK.
 *        this is a synchronous method, it carries the risk of being time-consuming.
 * @param cameraId
 * @param type action type: GWM_DVR_CAPTURE, GWM_DVR_CAPTURE_CONTINUOUS
 * @return GWM_Status processing status.
 */
Return<GWM_Status> DVR::gwm_startCapture_sync(GWM_DVRCameraId cameraId, GWM_DVR_VIDEO_TYPE type)
{
    std::unique_lock<std::mutex> lock(mMutex);
    ALOGI("%s:  cameraId:%hu, type:%hhu", __FUNCTION__, cameraId, type);
    GWM_Status status = GWM_Status::GWM_ERROR;
    if (mDVRInternal)
    {
        if(mDVRFdbProxy == nullptr)
        {
            ALOGE("%s:  mDVRFdbProxy == nullptr!", __FUNCTION__);
            return GWM_Status::GWM_ERROR;
        }
        status = mDVRFdbProxy->startCapture(cameraId, type);
    }
    else
    {
        status = startCapture(cameraId, type);
    }
    return status;
}

/**
 * @brief provide the functionality of start LapseVideo to FWK.
 * @param cameraId
 * @param timeLapseVideoInteval
 * @param totalFrameNumber
 * @param playFrameNumber
 * @return GWM_Status processing status.
 */
Return<GWM_Status> DVR::gwm_startLapseVideo(GWM_DVRCameraId cameraId,
                                            int64_t timeLapseVideoInteval,
                                            int16_t totalFrameNumber,
                                            int16_t playFrameNumber)
{
    std::unique_lock<std::mutex> lock(mMutex);
    ALOGI("%s:  cameraId:%hu, timeLapseVideoInteval:%ld, totalFrameNumber:%hu, playFrameNumber:%hu",
        __FUNCTION__,
        cameraId,
        timeLapseVideoInteval,
        totalFrameNumber,
        playFrameNumber);
    GWM_Status status = GWM_Status::GWM_ERROR;
    if (mDVRInternal)
    {
        if(mDVRFdbProxy == nullptr)
        {
            ALOGE("%s:  mDVRFdbProxy == nullptr!", __FUNCTION__);
            return GWM_Status::GWM_ERROR;
        }
        status = mDVRFdbProxy->startLapseVideo(cameraId, timeLapseVideoInteval, totalFrameNumber, playFrameNumber);
    }
    else
    {
        sendMsgToQnxForOMSStream(cameraId,GWM_DVRVideoOperateType::GWM_DVR_VIDEO_OPERATE_START,GWM_DVR_VIDEO_TYPE::GWM_DVR_VIDEO_TIME_LAPSE);

        if (mMessageHandler == nullptr)
        {
            ALOGE("%s:  mMessageHandler == nullptr !", __FUNCTION__);
            return GWM_Status::GWM_ERROR;
        }

        memset(&mDvrMsg, 0, sizeof(mDvrMsg));
        mDvrMsg.id = DVRMessageId::START_LAPSEVIDEO;
        mDvrMsg.cameraId = cameraId;
        mDvrMsg.timeLapseVideoInteval = timeLapseVideoInteval;
        mDvrMsg.totalFrameNumber = totalFrameNumber;
        mDvrMsg.playFrameNumber = playFrameNumber;
        if (mMessageHandler->sendDVRMessage(mDvrMsg))
        {
            status = GWM_Status::GWM_OK;
        }
    }
    return status;
}

/**
 * @brief provide the functionality of start LapseVideo to FWK.
 *        this is a synchronous method, it carries the risk of being time-consuming.
 * @param cameraId
 * @param timeLapseVideoInteval
 * @param totalFrameNumber
 * @param playFrameNumber
 * @return GWM_Status processing status.
 */
Return<GWM_Status> DVR::gwm_startLapseVideo_sync(GWM_DVRCameraId cameraId,
                                            int64_t timeLapseVideoInteval,
                                            int16_t totalFrameNumber,
                                            int16_t playFrameNumber)
{
    std::unique_lock<std::mutex> lock(mMutex);
    ALOGI("%s:  cameraId:%hu, timeLapseVideoInteval:%ld, totalFrameNumber:%hu, playFrameNumber:%hu",
        __FUNCTION__,
        cameraId,
        timeLapseVideoInteval,
        totalFrameNumber,
        playFrameNumber);
    GWM_Status status = GWM_Status::GWM_ERROR;
    if (mDVRInternal)
    {
        if(mDVRFdbProxy == nullptr)
        {
            ALOGE("%s:  mDVRFdbProxy == nullptr!", __FUNCTION__);
            return GWM_Status::GWM_ERROR;
        }
        status = mDVRFdbProxy->startLapseVideo(cameraId, timeLapseVideoInteval, totalFrameNumber, playFrameNumber);
    }
    else
    {
        sendMsgToQnxForOMSStream(cameraId,GWM_DVRVideoOperateType::GWM_DVR_VIDEO_OPERATE_START,GWM_DVR_VIDEO_TYPE::GWM_DVR_VIDEO_TIME_LAPSE);
        status = startLapseVideo(cameraId, timeLapseVideoInteval, totalFrameNumber, playFrameNumber);
    }
    return status;
}

/**
 * @brief provide the functionality of stop LapseVideo to FWK.
 * @param cameraId
 * @return GWM_Status processing status.
 */
Return<GWM_Status> DVR::gwm_stopLapseVideo(GWM_DVRCameraId cameraId)
{
    std::unique_lock<std::mutex> lock(mMutex);
    ALOGI("%s:  cameraId:%hu", __FUNCTION__, cameraId);
    GWM_Status status = GWM_Status::GWM_ERROR;
    if (mDVRInternal)
    {
        if(mDVRFdbProxy == nullptr)
        {
            ALOGE("%s:  mDVRFdbProxy == nullptr!", __FUNCTION__);
            return GWM_Status::GWM_ERROR;
        }
        status = mDVRFdbProxy->stopLapseVideo(cameraId);
    }
    else
    {
        if (mMessageHandler == nullptr)
        {
            ALOGE("%s:  mMessageHandler == nullptr !", __FUNCTION__);
            return GWM_Status::GWM_ERROR;
        }

        memset(&mDvrMsg, 0, sizeof(mDvrMsg));
        mDvrMsg.id = DVRMessageId::STOP_LAPSEVIDEO;
        mDvrMsg.cameraId = cameraId;
        if (mMessageHandler->sendDVRMessage(mDvrMsg))
        {
            status = GWM_Status::GWM_OK;
        }
    }
    return status;
}

/**
 * @brief provide the functionality of stop LapseVideo to FWK.
 *        this is a synchronous method, it carries the risk of being time-consuming.
 * @param cameraId
 * @return GWM_Status processing status.
 */
Return<GWM_Status> DVR::gwm_stopLapseVideo_sync(GWM_DVRCameraId cameraId)
{
    std::unique_lock<std::mutex> lock(mMutex);
    ALOGI("%s:  cameraId:%hu", __FUNCTION__, cameraId);
    GWM_Status status = GWM_Status::GWM_ERROR;
    if (mDVRInternal)
    {
        if(mDVRFdbProxy == nullptr)
        {
            ALOGE("%s:  mDVRFdbProxy == nullptr!", __FUNCTION__);
            return GWM_Status::GWM_ERROR;
        }
        status = mDVRFdbProxy->stopLapseVideo(cameraId);
    }
    else
    {
        status = stopLapseVideo(cameraId);
    }
    return status;
}

/**
 * @brief provide the functionality of format TFCard to FWK.
 * @param tfcard_id
 * @return GWM_Status processing status.
 */
Return<GWM_Status> DVR::gwm_formatTFCard(GWM_DVR_TFCardId tfcard_id)
{
    std::unique_lock<std::mutex> lock(mMutex);
    ALOGI("%s:  tfcard_id:%hhu", __FUNCTION__, tfcard_id);
    GWM_Status status = GWM_Status::GWM_ERROR;
    if (mDVRInternal)
    {
        if(mDVRFdbProxy == nullptr)
        {
            ALOGE("%s:  mDVRFdbProxy == nullptr!", __FUNCTION__);
            return GWM_Status::GWM_ERROR;
        }
        status = mDVRFdbProxy->formatTFCard(tfcard_id);
    }
    else
    {
        if (mMessageHandler == nullptr)
        {
            ALOGE("%s:  mMessageHandler == nullptr !", __FUNCTION__);
            return GWM_Status::GWM_ERROR;
        }

        memset(&mDvrMsg, 0, sizeof(mDvrMsg));
        mDvrMsg.id = DVRMessageId::FORMAT_TFCARD;
        mDvrMsg.tfCardId = tfcard_id;
        if (mMessageHandler->sendDVRMessage(mDvrMsg))
        {
            status = GWM_Status::GWM_OK;
        }
    }
    return status;
}

/**
 * @brief provide the functionality of reset factory to FWK.
 * @return GWM_Status processing status.
 */
Return<GWM_Status> DVR::gwm_resetFactory()
{
    ALOGI("%s:  ", __FUNCTION__);
    std::unique_lock<std::mutex> lock(mMutex);
    GWM_Status status = GWM_Status::GWM_ERROR;
    if (mDVRInternal)
    {
        if(mDVRFdbProxy == nullptr)
        {
            ALOGE("%s:  mDVRFdbProxy == nullptr!", __FUNCTION__);
            return GWM_Status::GWM_ERROR;
        }
        status = mDVRFdbProxy->resetFactory();
    }
    else
    {
        if (mMessageHandler == nullptr)
        {
            ALOGE("%s:  mMessageHandler == nullptr !", __FUNCTION__);
            return GWM_Status::GWM_ERROR;
        }

        if (mMessageHandler->sendDVRMessage(DVRMessageId::RESET_FACTORY))
        {
            status = GWM_Status::GWM_OK;
        }
    }
    return status;
}

/**
 * @brief provide the functionality of query systemstatus to FWK.
 *        it contains TFCardInfo, TFCardExportCapacity, DVRSystemStatus, DVRSensorStatus.
 * @return GWM_Status processing status.
 */
Return<GWM_Status> DVR::gwm_querySystemStatus()
{
    std::lock_guard<std::mutex> lock(mMutex);
    ALOGI("%s:  ", __FUNCTION__);
    GWM_Status result = GWM_Status::GWM_ERROR;

    if(mDVRFdbProxy == nullptr)
    {
        ALOGE("%s:  mDVRFdbProxy == nullptr!", __FUNCTION__);
        result = GWM_Status::GWM_ERROR;
    }
    else
    {
        result = mDVRFdbProxy->querySystemInfoFromQNX();
    }

    if (!mDVRInternal)
    {
        if (mMessageHandler == nullptr)
        {
            ALOGE("%s:  mMessageHandler == nullptr !", __FUNCTION__);
            return GWM_Status::GWM_ERROR;
        }

        if (mMessageHandler->sendDVRMessage(DVRMessageId::QUERY_SYSTEMSTATUS))
        {
            result = GWM_Status::GWM_OK;
        }
    }
    return result;
}

/**
 * @brief provide the functionality of operate file to FWK.
 *        this method is only used to built-in DVR.
 * @param operation it contains operation_type, camera_id, tfcard_id, src_file_name, dst_file_name.
 *                  operation_type contains GWM_DVR_FILE_NULL, GWM_DVR_FILE_DELETE, GWM_DVR_FILE_ADD, GWM_DVR_FILE_MOVE.
 * @return GWM_Status processing status.
 */
Return<GWM_Status> DVR::gwm_operateFile(const GWM_DVR_FileOperateAction &operation)
{
    ALOGI("%s:  ", __FUNCTION__);
    std::lock_guard<std::mutex> lock(mMutex);
    if(mDVRFdbProxy == nullptr)
    {
        ALOGE("%s:  mDVRFdbProxy == nullptr!", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }
    return mDVRFdbProxy->operateFile(operation);
}

/**
 * @brief provide the functionality of modify settings to FWK.
 * @param params
 * @return GWM_Status processing status.
 */
Return<GWM_Status> DVR::gwm_setParam(const GWM_DVRSetParam &params)
{
    std::lock_guard<std::mutex> lock(mMutex);
    ALOGI("%s:  ", __FUNCTION__);
    GWM_Status status = GWM_Status::GWM_ERROR;
    if (mDVRInternal)
    {
        if(mDVRFdbProxy == nullptr)
        {
            ALOGE("%s:  mDVRFdbProxy == nullptr!", __FUNCTION__);
            return GWM_Status::GWM_ERROR;
        }
        status = mDVRFdbProxy->setParam(params);
        ALOGI("%s:  DVR_FDB_ANDROID_SETUP_SET, status:%d", __FUNCTION__, status);
    }
    else
    {
        if (mMessageHandler == nullptr)
        {
            ALOGE("%s:  mMessageHandler == nullptr !", __FUNCTION__);
            return GWM_Status::GWM_ERROR;
        }

        memset(&mDvrMsg, 0, sizeof(mDvrMsg));
        mDvrMsg.id = DVRMessageId::SET_PARAM;
        memset(&mDvrMsg.param, 0, sizeof(GWM_DVRSetParam));
        memcpy(&mDvrMsg.param, &params, sizeof(GWM_DVRSetParam));
        if (mMessageHandler->sendDVRMessage(mDvrMsg))
        {
            status = GWM_Status::GWM_OK;
        }
    }

    return status;
}

/**
 * @brief provide the functionality of get settings to FWK.
 * @return GWM_Status processing status.
 */
Return<GWM_Status> DVR::gwm_getParam()
{
    std::lock_guard<std::mutex> lock(mMutex);
    ALOGI("%s:  ", __FUNCTION__);
    GWM_Status status = GWM_Status::GWM_ERROR;
    if (mDVRInternal)
    {
        if(mDVRFdbProxy == nullptr)
        {
            ALOGE("%s:  mDVRFdbProxy == nullptr!", __FUNCTION__);
            return GWM_Status::GWM_ERROR;
        }
        status = mDVRFdbProxy->getParam();
        ALOGI("%s:  DVR_FDB_ANDROID_SETUP_GET, status:%d", __FUNCTION__, status);
    }
    else
    {
        if (mMessageHandler == nullptr)
        {
            ALOGE("%s:  mMessageHandler == nullptr !", __FUNCTION__);
            return GWM_Status::GWM_ERROR;
        }

        if (mMessageHandler->sendDVRMessage(DVRMessageId::GET_PARAM))
        {
            status = GWM_Status::GWM_OK;
        }
    }

    return status;
}

/**
 * @brief provide the functionality of request upload to FWK.
 *        this method is only used to built-in DVR.
 * @return GWM_Status processing status.
 */
Return<GWM_Status> DVR::gwm_uploadRequset()
{
    std::lock_guard<std::mutex> lock(mMutex);
    ALOGI("%s:  ", __FUNCTION__);
    if(mDVRFdbProxy == nullptr)
    {
        ALOGE("%s:  mDVRFdbProxy == nullptr!", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }
    return mDVRFdbProxy->uploadRequset();
}

/**
 * @brief provide the functionality of upload result to FWK.
 *        this method is only used to built-in DVR.
 * @param uploadResult it contains file_path, sequence and uploadstatus.
 *                     uploadstatus contains GWM_DVR_STATUS_NULL, GWM_DVR_STATUS_OK, GWM_DVR_STATUS_FAIL.
 * @return GWM_Status processing status.
 */
Return<GWM_Status> DVR::gwm_uploadResult(const GWM_DVRUploadFileResult &uploadResult)
{
    std::unique_lock<std::mutex> lock(mMutex);
    ALOGI("%s:  ", __FUNCTION__);
    if(mDVRFdbProxy == nullptr)
    {
        ALOGE("%s:  mDVRFdbProxy == nullptr!", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }
    GWM_Status status = mDVRFdbProxy->uploadResult(uploadResult);
    ALOGI("%s:  DVR_FDB_ANDROID_UPLOAD_RESEULT, status:%d", __FUNCTION__, status);
    return status;
}

/**
 * @brief provide the functionality of send action cmd to FWK.
 *        this method is only used to built-in DVR.
 * @param boardcastActions it contains act_module, act_cmd and sequence.
 *                         act_module contains GWM_DVR_MIAO_CALL, GWM_DVR_REMOTE_MONITOR, GWM_DVR_GUARD_MODE.
 *                         act_cmd contains GWM_OPEN, GWM_CLOSE.
 * @return GWM_Status processing status.
 */
Return<GWM_Status> DVR::gwm_sendActCommd(const GWM_DVRBroadcastActCommand &boardcastActions)
{
    std::lock_guard<std::mutex> lock(mMutex);
    ALOGI("%s:  operationType:%hhu, actionType:%hhu, sequence:%lu",
        __FUNCTION__,
        boardcastActions.act_module,
        boardcastActions.act_cmd,
        boardcastActions.sequence);
    if(mDVRFdbProxy == nullptr)
    {
        ALOGE("%s:  mDVRFdbProxy == nullptr!", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }
    return mDVRFdbProxy->sendActCommd(boardcastActions);
}

/**
 * @brief provide the functionality of send module event to FWK.
 *        this method is only used to built-in DVR.
 * @param moduleEvent it contains act_module, event, sequence.
 *                    act_module contains GWM_DVR_MIAO_CALL, GWM_DVR_REMOTE_MONITOR, GWM_DVR_GUARD_MODE
 *                    event contains GWM_NULL, GWM_CRASH.
 * @return GWM_Status processing status.
 */
Return<GWM_Status> DVR::gwm_sendModuleEvent(const GWM_DVRSendModuleEvent &moduleEvent)
{
    std::lock_guard<std::mutex> lock(mMutex);
    ALOGI("%s:  act_module:%d, event:%d, sequence:%lu",
        __FUNCTION__,
        (uint32_t)moduleEvent.act_module,
        (uint32_t)moduleEvent.event,
        (uint64_t)moduleEvent.sequence);
    if(mDVRFdbProxy == nullptr)
    {
        ALOGE("%s:  mDVRFdbProxy == nullptr!", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }
    return mDVRFdbProxy->sendModuleEvent(moduleEvent);
}

/**
 * @brief provide the functionality of reqeust file list to FWK.
 *        this method is only used to ext DVR.
 * @param query_file_list it contains file_type, camera_id, file_sum, last_file_name.
 *                        file_type contains GWM_DVRFileNormalVideo, GWM_DVRFileEventVideo, GWM_DVRFileUserData, GWM_DVRFileExportData.
 * @return GWM_Status processing status.
 */
Return<GWM_Status> DVR::gwm_FileListRequest(const GWM_DVRFileListREQ &query_file_list)
{
    std::lock_guard<std::mutex> lock(mMutex);
    ALOGI("%s:  ", __FUNCTION__);
    if (mMessageHandler == nullptr)
    {
        ALOGE("%s:  mMessageHandler == nullptr !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    memset(&mDvrMsg, 0, sizeof(mDvrMsg));
    mDvrMsg.id = DVRMessageId::FILELIST_REQUEST;
    memset(&mDvrMsg.fileListREQ, 0, sizeof(GWM_DVRFileListREQ));
    memcpy(&mDvrMsg.fileListREQ, &query_file_list, sizeof(GWM_DVRFileListREQ));
    GWM_Status status = GWM_Status::GWM_ERROR;
    if (mMessageHandler->sendDVRMessage(mDvrMsg))
    {
        status = GWM_Status::GWM_OK;
    }

    return status;
}

/**
 * @brief provide the functionality of delete file list to FWK.
 *        this method is only used to ext DVR.
 * @param file_path_url
 * @return GWM_Status processing status.
 */
Return<GWM_Status> DVR::gwm_deleteFileList(const hidl_vec<hidl_string> &file_path_url)
{
    std::lock_guard<std::mutex> lock(mMutex);
    ALOGI("%s:  ", __FUNCTION__);
    if (file_path_url == NULL)
    {
        ALOGE("%s:  file_path_url is null !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    if (mMessageHandler == nullptr)
    {
        ALOGE("%s:  mMessageHandler == nullptr !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    memset(&mDvrMsg, 0, sizeof(mDvrMsg));
    mDvrMsg.id = DVRMessageId::DELETE_FILELIST;
    mDvrMsg.file_path_url.assign(file_path_url.begin(),file_path_url.end());
    GWM_Status status = GWM_Status::GWM_ERROR;
    if (mMessageHandler->sendDVRMessage(mDvrMsg))
    {
        status = GWM_Status::GWM_OK;
    }

    return status;
}

/**
 * @brief provide the functionality of delete all file to FWK.
 *        this method is only used to ext DVR.
 * @param camera_id
 * @param file_type
 * @return GWM_Status processing status.
 */
Return<GWM_Status> DVR::gwm_AllFiledelete(const GWM_DVRCameraId camera_id,
    const GWM_DVRFileType file_type)
{
    std::lock_guard<std::mutex> lock(mMutex);
    ALOGI("%s:  ", __FUNCTION__);
    if (mMessageHandler == nullptr)
    {
        ALOGE("%s:  mMessageHandler == nullptr !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    memset(&mDvrMsg, 0, sizeof(mDvrMsg));
    mDvrMsg.id = DVRMessageId::ALLFILE_DELETE;
    mDvrMsg.cameraId = camera_id;
    mDvrMsg.fileType = file_type;
    GWM_Status status = GWM_Status::GWM_ERROR;
    if (mMessageHandler->sendDVRMessage(mDvrMsg))
    {
        status = GWM_Status::GWM_OK;
    }
    return status;
}

/**
 * @brief provide the functionality of async delete all file to FWK.
 *        this method is only used to ext DVR.
 * @param camera_id
 * @param file_type
 * @return GWM_Status processing status.
 */
Return<GWM_Status> DVR::gwm_AsyncAllFiledelete(const GWM_DVRCameraId camera_id,
    const GWM_DVRFileType file_type)
{
    std::lock_guard<std::mutex> lock(mMutex);
    ALOGI("%s:  ", __FUNCTION__);
    if (mMessageHandler == nullptr)
    {
        ALOGE("%s:  mMessageHandler == nullptr !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    memset(&mDvrMsg, 0, sizeof(mDvrMsg));
    mDvrMsg.id = DVRMessageId::ASYNC_ALLFILE_DELETE;
    mDvrMsg.cameraId = camera_id;
    mDvrMsg.fileType = file_type;
    GWM_Status status = GWM_Status::GWM_ERROR;
    if (mMessageHandler->sendDVRMessage(mDvrMsg))
    {
        status = GWM_Status::GWM_OK;
    }
    return status;
}

/**
 * @brief provide the functionality of stop async delete all file to FWK.
 *        this method is only used to ext DVR.
 * @param camera_id
 * @return GWM_Status processing status.
 */
Return<GWM_Status> DVR::gwm_StopAsyncAllFiledelete(const GWM_DVRCameraId camera_id)
{
    std::lock_guard<std::mutex> lock(mMutex);
    ALOGI("%s:  ", __FUNCTION__);
    if (mMessageHandler == nullptr)
    {
        ALOGE("%s:  mMessageHandler == nullptr !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    memset(&mDvrMsg, 0, sizeof(mDvrMsg));
    mDvrMsg.id = DVRMessageId::STOP_ASYNC_ALLFILE_DELETE;
    mDvrMsg.cameraId = camera_id;
    GWM_Status status = GWM_Status::GWM_ERROR;
    if (mMessageHandler->sendDVRMessage(mDvrMsg))
    {
        status = GWM_Status::GWM_OK;
    }
    return status;
}

/**
 * @brief provide the functionality of export file list to FWK.
 *        this method is only used to ext DVR.
 * @param export_type
 * @param file_path_url
 * @return GWM_Status processing status.
 */
Return<GWM_Status> DVR::gwm_ExportFileList(const GWM_DVRExportType export_type,
    const hidl_vec<hidl_string> &file_path_url)
{
    std::lock_guard<std::mutex> lock(mMutex);
    ALOGI("%s:  ", __FUNCTION__);
    if (file_path_url == NULL)
    {
        ALOGE("%s:  file_path_url is null !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    if (mMessageHandler == nullptr)
    {
        ALOGE("%s:  mMessageHandler == nullptr !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    memset(&mDvrMsg, 0, sizeof(mDvrMsg));
    mDvrMsg.id = DVRMessageId::EXPORT_FILELIST;
    mDvrMsg.exportType = export_type;
    mDvrMsg.file_path_url.assign(file_path_url.begin(),file_path_url.end());
    GWM_Status status = GWM_Status::GWM_ERROR;
    if (mMessageHandler->sendDVRMessage(mDvrMsg))
    {
        status = GWM_Status::GWM_OK;
    }
    return status;
}

/**
 * @brief provide the functionality of cancel export file to FWK.
 *        this method is only used to ext DVR.
 * @param camera_id
 * @return GWM_Status processing status.
 */
Return<GWM_Status> DVR::gwm_CancelFilesExport(GWM_DVRCameraId camera_id)
{
    std::lock_guard<std::mutex> lock(mMutex);
    ALOGI("%s:  camera_id:%hu", __FUNCTION__, camera_id);
    if (mMessageHandler == nullptr)
    {
        ALOGE("%s:  mMessageHandler == nullptr !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    memset(&mDvrMsg, 0, sizeof(mDvrMsg));
    mDvrMsg.id = DVRMessageId::CANCEL_FILESEXPORT;
    mDvrMsg.cameraId = camera_id;
    GWM_Status status = GWM_Status::GWM_ERROR;
    if (mMessageHandler->sendDVRMessage(mDvrMsg))
    {
        status = GWM_Status::GWM_OK;
    }
    return status;
}

/**
 * @brief provide the functionality of exportFile capacity to FWK.
 *        this method is only used to ext DVR.
 * @param file_path_url
 * @return GWM_Status processing status.
 */
Return<GWM_Status> DVR::gwm_ExportFileCapacity(const ::android::hardware::hidl_vec<hidl_string> &file_path_url)
{
    std::lock_guard<std::mutex> lock(mMutex);
    ALOGI("%s:  ", __FUNCTION__);
    if (file_path_url == NULL)
    {
        ALOGE("%s:  file_path_url is null !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    if (mMessageHandler == nullptr)
    {
        ALOGE("%s:  mMessageHandler == nullptr !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    memset(&mDvrMsg, 0, sizeof(mDvrMsg));
    mDvrMsg.id = DVRMessageId::EXPORT_FILECAPACITY;
    mDvrMsg.file_path_url.assign(file_path_url.begin(),file_path_url.end());
    GWM_Status status = GWM_Status::GWM_ERROR;
    if (mMessageHandler->sendDVRMessage(mDvrMsg))
    {
        status = GWM_Status::GWM_OK;
    }
    return status;
}

/**
 * @brief provide the functionality of exportFile capacity to FWK.
 *        this is a synchronous method, it carries the risk of being time-consuming.
 *        this method is only used to ext DVR.
 * @param file_path_url
 * @return int32_t  exportFile capacity.
 */
Return<int32_t> DVR::gwm_ExportFileCapacity_sync(const ::android::hardware::hidl_vec<hidl_string> &file_path_url)
{
    std::lock_guard<std::mutex> lock(mMutex);
    ALOGI("%s:  ", __FUNCTION__);
    if (file_path_url == NULL)
    {
        ALOGE("%s:  file_path_url is null !", __FUNCTION__);
        return -1;
    }

    std::vector<std::string> v_path;
    v_path.clear();
    for (uint32_t i = 0; i < file_path_url.size(); i++)
    {
        v_path.push_back(std::string(file_path_url[i].c_str()));
    }
    return exportFileCapacity(v_path, true);
}

/**
 * @brief provide the functionality of request EMMC status to FWK.
 *        this method is only used to ext DVR.
 * @return GWM_Status processing status.
 */
Return<GWM_Status> DVR::gwm_EMMCStatusRequest()
{
    std::lock_guard<std::mutex> lock(mMutex);
    ALOGI("%s:  ", __FUNCTION__);
    if (mMessageHandler == nullptr)
    {
        ALOGE("%s:  mMessageHandler == nullptr !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    GWM_Status status = GWM_Status::GWM_ERROR;
    if (mMessageHandler->sendDVRMessage(DVRMessageId::EMMCSTATUS_REQUEST))
    {
        status = GWM_Status::GWM_OK;
    }
    return status;
}

/**
 * @brief provide the functionality of request TFCard status to FWK.
 *        this method is only used to ext DVR.
 * @param tfcard_id
 * @return GWM_Status processing status.
 */
Return<GWM_Status> DVR::gwm_TFCardStatusRequest(const GWM_DVR_TFCardId tfcard_id)
{
    std::lock_guard<std::mutex> lock(mMutex);
    ALOGI("%s:  tfcard_id:%hhu", __FUNCTION__, tfcard_id);
    if (mMessageHandler == nullptr)
    {
        ALOGE("%s:  mMessageHandler == nullptr !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    memset(&mDvrMsg, 0, sizeof(mDvrMsg));
    mDvrMsg.id = DVRMessageId::TFCARDSTATUS_REQUEST;
    mDvrMsg.tfCardId = tfcard_id;
    GWM_Status status = GWM_Status::GWM_ERROR;
    if (mMessageHandler->sendDVRMessage(mDvrMsg))
    {
        status = GWM_Status::GWM_OK;
    }
    return status;
}

/**
 * @brief provide the functionality of request TFCard capacity to FWK.
 *        this method is only used to ext DVR.
 * @param tfcard_id
 * @return GWM_Status processing status.
 */
Return<GWM_Status> DVR::gwm_TFCardCapacityRequest(const GWM_DVR_TFCardId tfcard_id)
{
    std::lock_guard<std::mutex> lock(mMutex);
    ALOGI("%s:  tfcard_id:%hhu", __FUNCTION__, tfcard_id);
    if (mMessageHandler == nullptr)
    {
        ALOGE("%s:  mMessageHandler == nullptr !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    memset(&mDvrMsg, 0, sizeof(mDvrMsg));
    mDvrMsg.id = DVRMessageId::TFCARDCAPACITY_REQUEST;
    mDvrMsg.tfCardId = tfcard_id;
    GWM_Status status = GWM_Status::GWM_ERROR;
    if (mMessageHandler->sendDVRMessage(mDvrMsg))
    {
        status = GWM_Status::GWM_OK;
    }
    return status;
}

/**
 * @brief provide the functionality of export all file to FWK.
 *        this method is only used to ext DVR.
 * @param export_type
 * @param camera_id
 * @param file_type
 * @return GWM_Status processing status.
 */
Return<GWM_Status> DVR::gwm_AllFileExport(const GWM_DVRExportType export_type,
    const GWM_DVRCameraId camera_id,
    const GWM_DVRFileType file_type)
{
    std::lock_guard<std::mutex> lock(mMutex);
    ALOGI("%s:  export_type:%hhu, camera_id:%hu, file_type:%hhu",
        __FUNCTION__,
        export_type,
        camera_id,
        file_type);
    if (mMessageHandler == nullptr)
    {
        ALOGE("%s:  mMessageHandler == nullptr !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    memset(&mDvrMsg, 0, sizeof(mDvrMsg));
    mDvrMsg.id = DVRMessageId::ALLFILE_EXPORT;
    mDvrMsg.exportType = export_type;
    mDvrMsg.cameraId = camera_id;
    mDvrMsg.fileType = file_type;
    GWM_Status status = GWM_Status::GWM_ERROR;
    if (mMessageHandler->sendDVRMessage(mDvrMsg))
    {
        status = GWM_Status::GWM_OK;
    }

    return status;
}

/**
 * @brief provide the functionality of request record state to FWK.
 *        this method is only used to ext DVR.
 * @param camera_id
 * @return GWM_Status processing status.
 */
Return<GWM_Status> DVR::gwm_RecordStateRequest(const GWM_DVRCameraId camera_id)
{
    std::lock_guard<std::mutex> lock(mMutex);
    ALOGI("%s:  camera_id:%hu", __FUNCTION__, camera_id);
    if (mMessageHandler == nullptr)
    {
        ALOGE("%s:  mMessageHandler == nullptr !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    memset(&mDvrMsg, 0, sizeof(mDvrMsg));
    mDvrMsg.id = DVRMessageId::RECORDSTATE_REQUEST;
    mDvrMsg.cameraId = camera_id;
    GWM_Status status = GWM_Status::GWM_ERROR;
    if (mMessageHandler->sendDVRMessage(mDvrMsg))
    {
        status = GWM_Status::GWM_OK;
    }
    return status;
}

/**
 * @brief provide the functionality of request omc capture to FWK.
 *        this method is only used to ext DVR.
 * @param eventTime
 * @param eventType
 * @param fileId
 * @param fileSize
 * @return GWM_Status processing status.
 */
Return<GWM_Status> DVR::gwm_OMCCaptureRequest(const hidl_string &eventTime,
    const GWM_DVREventType eventType,
    uint32_t fileId,
    uint32_t fileSize)
{
    std::lock_guard<std::mutex> lock(mMutex);
    ALOGI("%s:  eventTime:%s, eventType:%hhu, fileId:%d, fileSize:%d",
        __FUNCTION__,
        eventTime.c_str(),
        eventType,
        fileId,
        fileSize);
    if (mMessageHandler == nullptr)
    {
        ALOGE("%s:  mMessageHandler == nullptr !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    memset(&mDvrMsg, 0, sizeof(mDvrMsg));
    mDvrMsg.id = DVRMessageId::OMCCAPTURE_REQUEST;
    mDvrMsg.eventTime.append(std::string(eventTime.c_str()));
    mDvrMsg.eventType = eventType;
    mDvrMsg.fileId = fileId;
    mDvrMsg.fileSize = fileSize;
    GWM_Status status = GWM_Status::GWM_ERROR;
    if (mMessageHandler->sendDVRMessage(mDvrMsg))
    {
        status = GWM_Status::GWM_OK;
    }

    return status;
}

/**
 * @brief provide the functionality of request omc capture to FWK.
 *        this is a synchronous method, it carries the risk of being time-consuming.
 *        this method is only used to ext DVR.
 * @param eventTime
 * @param eventType
 * @param fileId
 * @param fileSize
 * @return GWM_DVROMCCaptureStatus omc capture status.
 */
Return<GWM_DVROMCCaptureStatus> DVR::gwm_OMCCaptureRequest_sync(const hidl_string &eventTime,
    const GWM_DVREventType eventType,
    uint32_t fileId,
    uint32_t fileSize)
{
    std::lock_guard<std::mutex> lock(mMutex);
    ALOGI("%s:  eventTime:%s, eventType:%hhu, fileId:%u, fileSize:%u",
        __FUNCTION__,
        eventTime.c_str(),
        eventType,
        fileId,
        fileSize);
    return dvrCaptureRequest(AccessType_DT::E_WITHINSIGNT_OMC, std::string(eventTime.c_str()), eventType, fileId, fileSize, true, true);
}

/**
 * @brief provide the functionality of request omc capture transfer to FWK.
 *        this method is only used to ext DVR.
 * @param eventTime
 * @param eventType
 * @param fileId
 * @param fileSize
 * @param filePath
 * @return GWM_Status processing status.
 */
Return<GWM_Status> DVR::gwm_OMCCaptureTransferRequest(const hidl_string &eventTime,
    const GWM_DVREventType eventType,
    uint32_t fileId,
    uint32_t fileSize,
    const hidl_string &filePath)
{
    std::lock_guard<std::mutex> lock(mMutex);
    ALOGI("%s:  eventTime:%s, eventType:%hhu, fileId:%d, fileSize:%d, filePath:%s",
        __FUNCTION__,
        eventTime.c_str(),
        eventType,
        fileId,
        fileSize,
        filePath.c_str());
    if (mMessageHandler == nullptr)
    {
        ALOGE("%s:  mMessageHandler == nullptr !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    memset(&mDvrMsg, 0, sizeof(mDvrMsg));
    mDvrMsg.id = DVRMessageId::OMCCAPTURETRANSFER_REQUEST;
    mDvrMsg.eventTime.clear();
    mDvrMsg.eventTime.append(std::string(eventTime.c_str()));
    mDvrMsg.fileId = fileId;
    mDvrMsg.fileSize = fileSize;
    mDvrMsg.filePath.clear();
    mDvrMsg.filePath.append(std::string(filePath.c_str()));
    GWM_Status status = GWM_Status::GWM_ERROR;
    if (mMessageHandler->sendDVRMessage(mDvrMsg))
    {
        status = GWM_Status::GWM_OK;
    }
    return status;
}

/**
 * @brief provide the functionality of request omc capture transfer to FWK.
 *        this is a synchronous method, it carries the risk of being time-consuming.
 *        this method is only used to ext DVR.
 * @param eventTime
 * @param eventType
 * @param fileId
 * @param fileSize
 * @param filePath
 * @return GWM_DVROMCCaptureStatus omc capture transfer status.
 */
Return<GWM_DVROMCCaptureStatus> DVR::gwm_OMCCaptureTransferRequest_sync(const hidl_string &eventTime,
    const GWM_DVREventType eventType,
    uint32_t fileId,
    uint32_t fileSize,
    const hidl_string &filePath)
{
    std::lock_guard<std::mutex> lock(mMutex);
    ALOGI("%s:  eventTime:%s, eventType:%hhu, fileId:%d, fileSize:%d, filePath:%s",
        __FUNCTION__,
        eventTime.c_str(),
        eventType,
        fileId,
        fileSize,
        filePath.c_str());
    return dvrCaptureTransferRequest(AccessType_DT::E_WITHINSIGNT_OMC, std::string(eventTime.c_str()), eventType, fileId, fileSize, std::string(filePath.c_str()), true, true);
}

/**
 * @brief provide the functionality of request dvr capture to FWK.
 *        this method is only used to ext DVR.
 * @param eventTime
 * @param eventType
 * @param fileId
 * @param fileSize
 * @return GWM_Status processing status.
 */
Return<GWM_Status> DVR::gwm_DVRCaptureRequest(
    const GWM_DVRCameraId camera_id, 
    const hidl_string &eventTime,
    const GWM_DVREventType eventType,
    uint32_t fileId,
    uint32_t fileSize)
{
    std::lock_guard<std::mutex> lock(mMutex);
    ALOGI("%s:  camera_id:%hu, eventTime:%s, eventType:%hhu, fileId:%d, fileSize:%d",
        __FUNCTION__,
        camera_id,
        eventTime.c_str(),
        eventType,
        fileId,
        fileSize);
    if (mMessageHandler == nullptr)
    {
        ALOGE("%s:  mMessageHandler == nullptr !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    memset(&mDvrMsg, 0, sizeof(mDvrMsg));
    mDvrMsg.id = DVRMessageId::DVRCAPTURE_REQUEST;
    mDvrMsg.cameraId = camera_id;
    mDvrMsg.eventTime.append(std::string(eventTime.c_str()));
    mDvrMsg.eventType = eventType;
    mDvrMsg.fileId = fileId;
    mDvrMsg.fileSize = fileSize;
    GWM_Status status = GWM_Status::GWM_ERROR;
    if (mMessageHandler->sendDVRMessage(mDvrMsg))
    {
        status = GWM_Status::GWM_OK;
    }

    return status;
}

/**
 * @brief provide the functionality of request dvr capture to FWK.
 *        this is a synchronous method, it carries the risk of being time-consuming.
 *        this method is only used to ext DVR.
 * @param cameraId
 * @param eventTime
 * @param eventType
 * @param fileId
 * @param fileSize
 * @return GWM_DVROMCCaptureStatus dvr capture status.
 */
Return<GWM_DVROMCCaptureStatus> DVR::gwm_DVRCaptureRequest_sync(const GWM_DVRCameraId camera_id,
    const hidl_string &eventTime,
    const GWM_DVREventType eventType,
    uint32_t fileId,
    uint32_t fileSize)
{
    std::lock_guard<std::mutex> lock(mMutex);
    ALOGI("%s:  camera_id:%hu, eventTime:%s, eventType:%hhu, fileId:%d, fileSize:%d",
        __FUNCTION__,
        camera_id,
        eventTime.c_str(),
        eventType,
        fileId,
        fileSize);
    return dvrCaptureRequest(switch_cameraid(camera_id), eventTime, eventType, fileId, fileSize, false, true);
}

/**
 * @brief provide the functionality of request dvr capture transfer to FWK.
 *        this method is only used to ext DVR.
 * @param camera_id
 * @param eventType
 * @param fileId
 * @param fileSize
 * @param filePath
 * @return GWM_Status processing status.
 */
Return<GWM_Status> DVR::gwm_DVRCaptureTransferRequest(const GWM_DVRCameraId camera_id,
    const hidl_string &eventTime,
    const GWM_DVREventType eventType,
    uint32_t fileId,
    uint32_t fileSize,
    const hidl_string &filePath)
{
    std::lock_guard<std::mutex> lock(mMutex);
    ALOGI("%s:   camera_id:%hu, eventTime:%s, eventType:%hhu, fileId:%d, fileSize:%d, filePath:%s",
        __FUNCTION__,
        camera_id,
        eventTime.c_str(),
        eventType,
        fileId,
        fileSize,
        filePath.c_str());
    if (mMessageHandler == nullptr)
    {
        ALOGE("%s:  mMessageHandler == nullptr !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    memset(&mDvrMsg, 0, sizeof(mDvrMsg));
    mDvrMsg.id = DVRMessageId::DVRCAPTURETRANSFER_REQUEST;
    mDvrMsg.cameraId = camera_id;
    mDvrMsg.eventTime.clear();
    mDvrMsg.eventTime.append(std::string(eventTime.c_str()));
    mDvrMsg.fileId = fileId;
    mDvrMsg.fileSize = fileSize;
    mDvrMsg.filePath.clear();
    mDvrMsg.filePath.append(std::string(filePath.c_str()));
    GWM_Status status = GWM_Status::GWM_ERROR;
    if (mMessageHandler->sendDVRMessage(mDvrMsg))
    {
        status = GWM_Status::GWM_OK;
    }
    return status;
}

/**
 * @brief provide the functionality of request dvr file capacity info to FWK.
 *        this method is only used to ext DVR.
 * @param file_capacity_type
 * @param file_type_list
 * @return GWM_Status processing status.
 */
Return<GWM_Status> DVR::gwm_DVRFileCapacityInfoReq(const GWM_TFAllFileCapacity file_capacity_type,
    const hidl_vec<GWM_ParamFileType> &file_type_list)
{
    std::lock_guard<std::mutex> lock(mMutex);
    if (file_type_list == NULL)
    {
        ALOGE("%s:  file_type_list is null !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    ALOGI("%s:   file_capacity_type:%hhu, file_type_list.size:%zu",
        __FUNCTION__,
        file_capacity_type,
        file_type_list.size());

    if (mMessageHandler == nullptr)
    {
        ALOGE("%s:  mMessageHandler == nullptr !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    memset(&mDvrMsg, 0, sizeof(mDvrMsg));
    mDvrMsg.id = DVRMessageId::DVRFILECAPACITYINFO_REQUEST;
    mDvrMsg.fileCapacityType = file_capacity_type;
    mDvrMsg.fileTypeList.assign(file_type_list.begin(),file_type_list.end());
    GWM_Status status = GWM_Status::GWM_ERROR;
    if (mMessageHandler->sendDVRMessage(mDvrMsg))
    {
        status = GWM_Status::GWM_OK;
    }
    return status;
}

/**
 * @brief provide the functionality of request dvr file list include date to FWK.
 *        this method is only used to ext DVR.
 * @param file_req
 * @return GWM_Status processing status.
 */
Return<GWM_Status> DVR::gwm_FileListIncludeDateReq(const GWM_DVRFileIncludeDateREQ &file_req)
{
    std::lock_guard<std::mutex> lock(mMutex);
    ALOGI("%s:   file_type:%hhu, camera_id:%hu, file_sum:%hhu, file_name:%s",
        __FUNCTION__,
        file_req.file_type,
        file_req.camera_id,
        file_req.file_sum,
        file_req.file_name.c_str());

    if (mMessageHandler == nullptr)
    {
        ALOGE("%s:  mMessageHandler == nullptr !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    memset(&mDvrMsg, 0, sizeof(mDvrMsg));
    mDvrMsg.id = DVRMessageId::FILELISTINCLUDEDATE_REQUEST;
    mDvrMsg.fileType = file_req.file_type;
    mDvrMsg.cameraId = file_req.camera_id;
    mDvrMsg.fileNumber = file_req.file_sum;
    mDvrMsg.fileName.clear();
    mDvrMsg.fileName.append(std::string(file_req.file_name.c_str()));
    GWM_Status status = GWM_Status::GWM_ERROR;
    if (mMessageHandler->sendDVRMessage(mDvrMsg))
    {
        status = GWM_Status::GWM_OK;
    }
    return status;
}

/**
 * @brief provide the functionality of request dvr capture transfer to FWK.
 *        this is a synchronous method, it carries the risk of being time-consuming.
 *        this method is only used to ext DVR.
 * @param cameraId
 * @param eventTime
 * @param eventType
 * @param fileId
 * @param fileSize
 * @param filePath
 * @return GWM_DVROMCCaptureStatus dvr capture transfer status.
 */
Return<GWM_DVROMCCaptureStatus> DVR::gwm_DVRCaptureTransferRequest_sync(const GWM_DVRCameraId camera_id,
    const hidl_string &eventTime,
    const GWM_DVREventType eventType,
    uint32_t fileId,
    uint32_t fileSize,
    const hidl_string &filePath)
{
    std::lock_guard<std::mutex> lock(mMutex);
    ALOGI("%s:   camera_id:%hu, eventTime:%s, eventType:%hhu, fileId:%d, fileSize:%d, filePath:%s",
        __FUNCTION__,
        camera_id,
        eventTime.c_str(),
        eventType,
        fileId,
        fileSize,
        filePath.c_str());
    return dvrCaptureTransferRequest(switch_cameraid(camera_id), eventTime, eventType, fileId, fileSize, filePath, false, true);
}

/**
 * @brief provide the functionality of select all file capacity to FWK.
 *        this method is only used to ext DVR.
 * @param camera_id
 * @param file_type
 * @return GWM_Status processing status.
 */
Return<GWM_Status> DVR::gwm_SelectAllFileCapacity(GWM_DVRCameraId camera_id, GWM_DVRFileType file_type)
{
    std::lock_guard<std::mutex> lock(mMutex);
    ALOGI("%s:  camera_id:%hu, file_type:%hhu", __FUNCTION__, camera_id, file_type);
    if (mMessageHandler == nullptr)
    {
        ALOGE("%s:  mMessageHandler == nullptr !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    memset(&mDvrMsg, 0, sizeof(mDvrMsg));
    mDvrMsg.id = DVRMessageId::SELECT_ALLFILECAPACITY;
    mDvrMsg.cameraId = camera_id;
    mDvrMsg.fileType = file_type;
    GWM_Status status = GWM_Status::GWM_ERROR;
    if (mMessageHandler->sendDVRMessage(mDvrMsg))
    {
        status = GWM_Status::GWM_OK;
    }
    return status;
}

/**
 * @brief provide the functionality of select all file capacity to FWK.
 *        this is a synchronous method, it carries the risk of being time-consuming.
 *        this method is only used to ext DVR.
 * @param camera_id
 * @param file_type
 * @return exportFile capacity.
 */
Return<int32_t> DVR::gwm_SelectAllFileCapacity_sync(GWM_DVRCameraId camera_id, GWM_DVRFileType file_type)
{
    std::lock_guard<std::mutex> lock(mMutex);
    ALOGI("%s:  camera_id:%hu, file_type:%hhu", __FUNCTION__, camera_id, file_type);
    return selectAllFileCapacity(camera_id, file_type, true);
}

void DVR::onQNXReplyData(GWM_Status status, FdbMsgCode_t code)
{
    ALOGD("%s:  ", __FUNCTION__);
}

//notify fdbus event to FWK.
void DVR::onQNXBoardcastData(FdbMsgCode_t code)
{
    std::lock_guard<std::mutex> lock(mMutex);
    if (mDVRCallbackList.size() == 0)
    {
        ALOGW("%s:  mDVRCallbackList is null ! !", __FUNCTION__);
        return;
    }

    it = mDVRCallbackList.begin();
    switch (code)
    {
        case CameraFdb::FdbCameraManagerMsgId::DVR_FDB_ANDROID_GET_SYSTEM_INFRO:
        case CameraFdb::FdbCameraManagerMsgId::DVR_FDB_QNX_BROADCAST_SYSTEM_INFRO:
        {
            ALOGI("%s:  DVR_FDB_ANDROID_GET/QNX BROADCAST SYSTEM_INFRO ", __FUNCTION__);
            for(auto callback : mDVRCallbackList)
            {
                if(!checkCallbackIsNull(callback))
                {
                    auto ret = callback->gwm_onDVRSystemStatusNotify(mSystemStatusInfo);
                    if (!ret.isOk())
                    {
                        ALOGW("%s:  has error", __FUNCTION__);
                    }
                }
            }
        }
        break;
        case CameraFdb::FdbCameraManagerMsgId::DVR_FDB_QNX_BROADCAST_SETUP_SET_RESULT:
        {
            ALOGI("%s:  DVR_FDB_QNX_BROADCAST_SETUP_SET_RESULT ", __FUNCTION__);
            for(auto callback : mDVRCallbackList)
            {
                if(!checkCallbackIsNull(callback))
                {
                    auto ret = callback->gwm_onSetParameterNotify(mSetParamReply);
                    if (!ret.isOk())
                    {
                        ALOGW("%s:  has error", __FUNCTION__);
                    }
                }
            }
        }
        break;
        case CameraFdb::FdbCameraManagerMsgId::DVR_FDB_ANDROID_SETUP_GET_RESULT:
        {
            ALOGI("%s:  DVR_FDB_ANDROID_SETUP_GET_RESULT", __FUNCTION__);
            for(auto callback : mDVRCallbackList)
            {
                if(!checkCallbackIsNull(callback))
                {
                    auto ret = callback->gwm_onGetParameterNotify(mGetParam);
                    if (!ret.isOk())
                    {
                        ALOGW("%s:  has error", __FUNCTION__);
                    }
                }
            }
        }
        break;
        case CameraFdb::FdbCameraManagerMsgId::DVR_FDB_QNX_BROADCAST_OPERATE_RECORD_RESULT:
        {
            ALOGI("%s:  DVR_FDB_QNX_BROADCAST_OPERATE_RECORD_RESULT ", __FUNCTION__);
            for(auto callback : mDVRCallbackList)
            {
                if(!checkCallbackIsNull(callback))
                {
                    /*Notify action complete event to application*/
                    auto ret = callback->gwm_onVideoOperateEventNotify(mVideoOperateEvent);
                    if (!ret.isOk())
                    {
                        ALOGW("%s:  has error", __FUNCTION__);
                    }
                }
            }
        }
        break;
        case CameraFdb::FdbCameraManagerMsgId::DVR_FDB_QNX_BROADCAST_OPERATE_FILE:
        {
            ALOGI("%s:  DVR_FDB_QNX_BROADCAST_OPERATE_FILE ", __FUNCTION__);
            for(auto callback : mDVRCallbackList)
            {
                if(!checkCallbackIsNull(callback))
                {
                    auto ret = callback->gwm_onDVRFileOperateNotify(mFileOperateEvent);
                    if (!ret.isOk())
                    {
                        ALOGW("%s:  has error", __FUNCTION__);
                    }
                }
            }
        }
        break;
        case CameraFdb::FdbCameraManagerMsgId::DVR_FDB_QNX_BROADCAST_OPERATE_SDCARD_RESULT:
        {
            ALOGI("%s:  DVR_FDB_QNX_BROADCAST_OPERATE_SDCARD_RESULT ", __FUNCTION__);
            for(auto callback : mDVRCallbackList)
            {
                if(!checkCallbackIsNull(callback))
                {
                    auto ret = callback->gwm_onDVRTFCardOperateNotify(mTfCardOperateEvent);
                    if (!ret.isOk())
                    {
                        ALOGW("%s:  has error", __FUNCTION__);
                    }
                }
            }
        }
        break;
        case CameraFdb::FdbCameraManagerMsgId::DVR_FDB_QNX_BROADCAST_RESTORE_FACTORY_SETUP_RESULT:
        {
            ALOGI("%s:  DVR_FDB_QNX_BROADCAST_RESTORE_FACTORY_SETUP_RESULT ", __FUNCTION__);
            for(auto callback : mDVRCallbackList)
            {
                if(!checkCallbackIsNull(callback))
                {
                    auto ret = callback->gwm_onDVRResetFactoryNotify(mfactoryreset_result);
                    if (!ret.isOk())
                    {
                        ALOGW("%s:  has error", __FUNCTION__);
                    }
                }
            }
        }
        break;
        case CameraFdb::FdbCameraManagerMsgId::DVR_FDB_ANDROID_OPERATE_PREVIEW_RESULT:
        {
            ALOGI("%s:  DVR_FDB_ANDROID_OPERATE_PREVIEW_RESULT", __FUNCTION__);
            for(auto callback : mDVRCallbackList)
            {
                if(!checkCallbackIsNull(callback))
                {
                    auto ret = callback->gwm_onDVRPreviewNotify(mPreviewReply);
                    if (!ret.isOk())
                    {
                        ALOGW("%s:  has error", __FUNCTION__);
                    }
                }
            }
        }
        break;
        case CameraFdb::FdbCameraManagerMsgId::DVR_FDB_QNX_BROADCAST_RECORD_TIME:
        {
            ALOGI("%s:  DVR_FDB_QNX_BROADCAST_RECORD_TIME", __FUNCTION__);
            for(auto callback : mDVRCallbackList)
            {
                if(!checkCallbackIsNull(callback))
                {
                    auto ret = callback->gwm_onDVRRecordTimeNotify(mRecordTimeInfo);
                    if (!ret.isOk())
                    {
                        ALOGW("%s:  has error", __FUNCTION__);
                    }
                }
            }
        }
        break;
        case CameraFdb::FdbCameraManagerMsgId::DVR_FDB_QNX_BROADCAST_RECORD_STATUS:
        {
            ALOGI("%s:  DVR_FDB_QNX_BROADCAST_RECORD_STATUS", __FUNCTION__);
            for(auto callback : mDVRCallbackList)
            {
                if(!checkCallbackIsNull(callback))
                {
                    auto ret = callback->gwm_onDVRRecordStatusNotify(mRecordStatus);
                    if (!ret.isOk())
                    {
                        ALOGW("%s:  has error", __FUNCTION__);
                    }
                }
            }
        }
        break;
        case CameraFdb::FdbCameraManagerMsgId::DVR_FDB_QNX_BROADCAST_TF_STATUS_CHANGED:
        {
            ALOGI("%s:  DVR_FDB_QNX_BROADCAST_TF_STATUS_CHANGED", __FUNCTION__);
            for(auto callback : mDVRCallbackList)
            {
                if(!checkCallbackIsNull(callback))
                {
                    auto ret = callback->gwm_onDVRTFCardStatusNotify(mTfcardStatus);
                    if (!ret.isOk())
                    {
                        ALOGW("%s:  has error", __FUNCTION__);
                    }
                }
            }
        }
        break;
        case CameraFdb::FdbCameraManagerMsgId::DVR_FDB_QNX_BROADCAST_CAMERA_STATUS_CHANGED:
        {
            ALOGI("%s:  DVR_FDB_QNX_BROADCAST_CAMERA_STATUS_CHANGED camera_id:%hu, camera_status:%hhu",
                __FUNCTION__,
                mCameraStatus.camera_id,
                mCameraStatus.camera_status);
            if (mCameraStatus.camera_id == GWM_DVRCameraId::GWM_DVR_CAMERA_ID_INCAR)
            {
                mCameraInnerStatus = static_cast<uint8_t>(mCameraStatus.camera_status);
            }

            for(auto callback : mDVRCallbackList)
            {
                if(!checkCallbackIsNull(callback))
                {
                    auto ret = callback->gwm_onDVRCameraStatusNotify(mCameraStatus);
                    if (!ret.isOk())
                    {
                        ALOGW("%s:  has error", __FUNCTION__);
                    }
                }
            }
        }
        break;
        case CameraFdb::FdbCameraManagerMsgId::DVR_FDB_QNX_BROADCAST_TF_CAPACITY_STATUS_CHANGED:
        {
            ALOGI("%s:  DVR_FDB_QNX_BROADCAST_TF_CAPACITY_STATUS_CHANGED", __FUNCTION__);
            for(auto callback : mDVRCallbackList)
            {
                if(!checkCallbackIsNull(callback))
                {
                    auto ret = callback->gwm_onDVRTFCardCapacityNotify(mCapacityStatus);
                    if (!ret.isOk())
                    {
                        ALOGW("%s:  has error", __FUNCTION__);
                    }
                }
            }
        }
        break;
        case CameraFdb::FdbCameraManagerMsgId::DVR_FDB_QNX_BROADCAST_TF_CAPACITY_COST_CHANGED:
        {
            ALOGI("%s:  DVR_FDB_QNX_BROADCAST_TF_CAPACITY_COST_CHANGED", __FUNCTION__);
            for(auto callback : mDVRCallbackList)
            {
                if(!checkCallbackIsNull(callback))
                {
                    auto ret = callback->gwm_onDVRTFCardCapacityCostNotify(mCapacityCostStatus);
                    if (!ret.isOk())
                    {
                        ALOGW("%s:  has error", __FUNCTION__);
                    }
                }
            }
        }
        break;
        case CameraFdb::FdbCameraManagerMsgId::DVR_FDB_QNX_BROADCAST_DEVICE_STATUS_CHANGED:
        {
            ALOGI("%s:  DVR_FDB_QNX_BROADCAST_DEVICE_STATUS_CHANGED", __FUNCTION__);
            for(auto callback : mDVRCallbackList)
            {
                if(!checkCallbackIsNull(callback))
                {
                    auto ret = callback->gwm_onDVRDeviceStatusNotify(mDeviceStatus);
                    if (!ret.isOk())
                    {
                        ALOGW("%s:  has error", __FUNCTION__);
                    }
                }
            }
        }
        break;
        // add by dingyu
        case CameraFdb::FdbCameraManagerMsgId::DVR_FDB_QNX_UPLOAD_REQUEST_ACK:
        {
            ALOGI("%s:  DVR_FDB_QNX_UPLOAD_REQUEST_ACK", __FUNCTION__);
            for(auto callback : mDVRCallbackList)
            {
                if(!checkCallbackIsNull(callback))
                {
                    auto ret = callback->gwm_onDVRReqUploadStatusNotify(mUploadStatus);
                    if (!ret.isOk())
                    {
                        ALOGW("%s:  has error", __FUNCTION__);
                    }
                }
            }
        }
        break;
        case CameraFdb::FdbCameraManagerMsgId::DVR_FDB_QNX_UPLOAD_ADD:
        {
            ALOGI("%s:  DVR_FDB_QNX_UPLOAD_ADD", __FUNCTION__);
            for(auto callback : mDVRCallbackList)
            {
                if(!checkCallbackIsNull(callback))
                {
                    auto ret = callback->gwm_onDVRUploadFileStatusNotify(mFileStatus);
                    if (!ret.isOk())
                    {
                        ALOGW("%s:  has error", __FUNCTION__);
                    }
                }
            }
        }
        break;
        default:
            ALOGD("%s:  code:%#X", __FUNCTION__, code);
            break;
    }
}

//notify fdbus connect status to FWK.
void DVR::onReportIPCStatus(GWM_DVRIPCStatus status)
{
    std::lock_guard<std::mutex> lock(mMutex);
    if (mDVRCallbackList.size() == 0)
    {
        ALOGE("%s:  mDVRCallbackList is null !", __FUNCTION__);
        return;
    }

    for(auto callback : mDVRCallbackList)
    {
        if(!checkCallbackIsNull(callback))
        {
            ALOGI("%s:  gwm_onDVRIPCStatusNotify", __FUNCTION__);
            auto ret = callback->gwm_onDVRIPCStatusNotify(status);
            if (!ret.isOk())
            {
                ALOGW("%s:  has error", __FUNCTION__);
            }
        }
    }
}

void DVR::onVideoUploadEventListener(DataCollectTriggerStruct_DT dataCollectTriggerStructDt)
{
    GWM_Status status = GWM_Status::GWM_ERROR;
    if(mCameraFdbClient == nullptr) {
        ALOGE("%s:  mCameraFdbClient == nullptr!", __FUNCTION__);
        return;
    }

    // build dvr message
    CameraFdb::DVREventRecordDataCollectTrigger upload_event;
    upload_event.set_sys_time_us(static_cast<uint32_t>(dataCollectTriggerStructDt.sysTimeUsDt));
    upload_event.set_collect_before_time(static_cast<uint32_t>(dataCollectTriggerStructDt.collectBeforeTimeDt));
    upload_event.set_collect_after_time(static_cast<uint32_t>(dataCollectTriggerStructDt.collectAfterTimeDt));
    upload_event.set_trigger_type(static_cast<CameraFdb::DVREventRecordTriggerType>(dataCollectTriggerStructDt.triggerTypeDt));
    upload_event.set_trigger_subtype(static_cast<CameraFdb::DVREventRecordTriggerType>(dataCollectTriggerStructDt.trigger_subtypeDt));
    CFdbProtoMsgBuilder builder(upload_event);
    status = mCameraFdbClient->sendMessage(
        CameraFdb::FdbCameraManagerMsgId::DVR_FDB_ANDROID_SOMEIP_SIGN, builder,
        true);
}

// add for out side DVR
void DVR::onDVRSystemStatusReportListener(DVRSystemStatus_DT dVRSystemStatusDt)
{
    /* DVRDeviceStatus:
     *  DVR_STATUS_NULL            = 0,
     *  DVR_STATUS_NORMAL          = 1,
     *  DVR_STATUS_EXCEPTION       = 2,
     *  DVR_STATUS_NET_FAILURE     = 3,
     *  DVR_STATUS_COMM_FAILURE    = 4,
     *  DVR_STATUS_CAN_SIGNAL_LOSS = 5
     */
    GWM_DVRDeviceStatus reply = GWM_DVRDeviceStatus::DVR_STATUS_NULL;

    if (dVRSystemStatusDt == E_DVR_STATUS_OK)
    {
        isExDVRReady = true;
        reply = GWM_DVRDeviceStatus::DVR_STATUS_NORMAL;
    }
    else if (dVRSystemStatusDt == E_DVR_STATUS_FAULT)
    {
        isExDVRReady = false;
        reply = GWM_DVRDeviceStatus::DVR_STATUS_EXCEPTION;
    }

    replyDVRStatusReportACKFunc(E_SUCCESSFUL);

    if (mDVRCallbackList.size() == 0)
    {
        mDVRSystemStatus.needNotify = true;
        mDVRSystemStatus.dVRSystemStatus = dVRSystemStatusDt;
        ALOGW("%s:  mDVRCallbackList is null ! !", __FUNCTION__);
        return;
    }

    for(auto callback : mDVRCallbackList)
    {
        if(!checkCallbackIsNull(callback))
        {
            ALOGD("%s:  gwm_onDVRStatusNotify, isExDVRReady:%d, DVRDeviceStatus:%hhu",
                __FUNCTION__,
                isExDVRReady,
                reply);
            auto ret = callback->gwm_onDVRStatusNotify(reply);
            if (!ret.isOk())
            {
                ALOGW("%s:  has error", __FUNCTION__);
            }
        }
    }
}

// This method had removed from GWM_GEEP_Platform_SOMEIP_Static_InterfaceDescription_V2.2.
/*
void DVR::onOMCStatusReportACKListener(SetResult_DT statusReportACKDt)
{
    if (mDVRCallbackList.size() == 0)
    {
        mOMCStatus.needNotify = true;
        mOMCStatus.statusReportACK = statusReportACKDt;
        ALOGW("%s:  mDVRCallbackList is null !", __FUNCTION__);
        return;
    }
}
*/

void DVR::onDVRSensorStatusReportListener(DVRSensorStatusStruct_DT dVRSensorStatusStructDt)
{
    /* GWM_DVRSystemStatus:
     *  GWM_DVR_SYSTEM_STATUS_NULL  = 0,
     *  GWM_DVR_SYSTEM_NORMAL       = 1,
     *  GWM_DVR_SYSTEM_EXCEPTION    = 2,
     *  GWM_DVR_SYSTEM_NET_FAILURE  = 3,
     *  GWM_DVR_SYSTEM_COMM_FAILURE = 4,
     *  GWM_DVR_SYSTEM_CAN_SIGNAL_LOSS = 5,
     *  GWM_DVR_SYSTEM_SENSOR_INIT = 6
     * GWM_DVRCameraId:
     *  GWM_DVR_CAMERA_ID_NULL  = 0,                         NULL
     *  GWM_DVR_CAMERA_ID_FRONT = 1,                         Front DVR Camera
     *  GWM_DVR_CAMERA_ID_INCAR = 2,                         INCAR DVR Camera
     *  GWM_DVR_CAMERA_ID_AVM   = 3,                         AVM Camera
     *  GWM_DVR_CAMERA_ID_FRONT_AND_AVM  =4,                 Front and AVM Camera
     *  GWM_DVR_CAMERA_ID_ALL   = 5,                         ALL
     *  GWM_DVR_StreamingMedia_or_BackSignt_reserved   = 6,  Back Camera
     *  GWM_DVR_MultiChannel   = 7,
     *  GWM_DVR_WithinSignt_DMC   = 8,
     */
    if (dVRSensorStatusStructDt.accessTypeDt == E_WITHINSIGNT_OMC)
    {
        ALOGW("%s:  not use oms status by ext-dvr !", __FUNCTION__);
        return;
    }

    GWM_DVRCameraStatus dvr_camera_status;
    memset(&dvr_camera_status, 0, sizeof(dvr_camera_status));
    if (dVRSensorStatusStructDt.dvrSensorStatusDt == E_SENSOR_OK)
    {
        dvr_camera_status.camera_status = GWM_DVRSystemStatus::GWM_DVR_SYSTEM_NORMAL;
    }
    else if (dVRSensorStatusStructDt.dvrSensorStatusDt == E_SENSOR_FAULT)
    {
        dvr_camera_status.camera_status = GWM_DVRSystemStatus::GWM_DVR_SYSTEM_EXCEPTION;
    }

    switch (dVRSensorStatusStructDt.accessTypeDt)
    {
        case E_FORESIGHT:
            dvr_camera_status.camera_id = GWM_DVRCameraId::GWM_DVR_CAMERA_ID_FRONT;
            if (dVRSensorStatusStructDt.dvrSensorStatusDt == E_SENSOR_OK)
            {
                mCameraFrontStatus = E_SENSOR_OK;
            }
            else
            {
                mCameraFrontStatus = E_SENSOR_FAULT;
            }
            break;

        /* Do not use oms status by ext-dvr.We can get oms status by QNX.
        case E_WITHINSIGNT_OMC:
            dvr_camera_status.camera_id = GWM_DVRCameraId::GWM_DVR_CAMERA_ID_INCAR;
            if (dVRSensorStatusStructDt.dvrSensorStatusDt == E_SENSOR_OK)
            {
                mCameraInnerStatus = E_SENSOR_OK;
            }
            else
            {
                mCameraInnerStatus = E_SENSOR_FAULT;
            }
            break;
        */
        case E_STREAMINGMEDIA_OR_BACKSIGNT_RESERVED:
            dvr_camera_status.camera_id = GWM_DVRCameraId::GWM_DVR_StreamingMedia_or_BackSignt_reserved;
            break;
        case E_360SURROUNDVIEW:
            dvr_camera_status.camera_id = GWM_DVRCameraId::GWM_DVR_CAMERA_ID_AVM;
            if (dVRSensorStatusStructDt.dvrSensorStatusDt == E_SENSOR_OK)
            {
                mCameraAVMStatus = E_SENSOR_OK;
            }
            else
            {
                mCameraAVMStatus = E_SENSOR_FAULT;
            }
            break;
        case E_MULTICHANNEL:
            dvr_camera_status.camera_id = GWM_DVRCameraId::GWM_DVR_MultiChannel;
            break;
        case E_WITHINSIGNT_DMC:
            dvr_camera_status.camera_id = GWM_DVRCameraId::GWM_DVR_WithinSignt_DMC;
            break;
        default:
            break;
    }

    replyDVRStatusReportACKFunc(E_SUCCESSFUL);

    if (mDVRCallbackList.size() == 0)
    {
        mDVRSensorStatus.needNotify = true;
        mDVRSensorStatus.dVRSensorStatusStruct.push_back(dVRSensorStatusStructDt);
        ALOGW("%s:  mDVRCallbackList is null !", __FUNCTION__);
        return;
    }

    for(auto callback : mDVRCallbackList)
    {
        if(!checkCallbackIsNull(callback))
        {
            ALOGD("%s:  gwm_onDVRCameraStatusNotify, dVRSensorStatusStructDt[accessType:%d, sensorStatus:%d], camera_id:%hu",
                __FUNCTION__,
                dVRSensorStatusStructDt.accessTypeDt,
                dVRSensorStatusStructDt.dvrSensorStatusDt,
                dvr_camera_status.camera_id);
            auto ret = callback->gwm_onDVRCameraStatusNotify(dvr_camera_status);
            if (!ret.isOk())
            {
                ALOGW("%s:  has error", __FUNCTION__);
            }
        }
    }
}

void DVR::onEventOperationReportEventListener(EventOperationType_DT eventOperationTypeDt, EventType_DT eventTypeDt, AccessType_DT accessTypeDt)
{
    if (eventOperationTypeDt == EventOperationType_DT::E_EVENTSTOP)
    {
        if (eventTypeDt == EventType_DT::E_SHORTVIDEORECORDING_BYBUTTON
            || eventTypeDt == EventType_DT::E_SHORTVIDEORECORDING_BYHUT)
        {
            sendMsgToQnxForOMSStream(accessTypeToCameraId(accessTypeDt),
                GWM_DVRVideoOperateType::GWM_DVR_VIDEO_OPERATE_STOP,
                GWM_DVR_VIDEO_TYPE::GWM_DVR_VIDEO_TYPE_SHORT);
        }
        else if (eventTypeDt == EventType_DT::E_TIMELAPSEVIDEO)
        {
            sendMsgToQnxForOMSStream(accessTypeToCameraId(accessTypeDt),
                GWM_DVRVideoOperateType::GWM_DVR_VIDEO_OPERATE_STOP,
                GWM_DVR_VIDEO_TYPE::GWM_DVR_VIDEO_TIME_LAPSE);
        }
        else if (eventTypeDt == EventType_DT::E_GUARDIANMODE)
        {
            sendMsgToQnxForOMSStream(accessTypeToCameraId(accessTypeDt),
                GWM_DVRVideoOperateType::GWM_DVR_VIDEO_OPERATE_STOP,
                GWM_DVR_VIDEO_TYPE::GWM_DVR_VIDEO_TYPE_GUARDIANMODE);
        }
        else
        {
            ALOGW("%s:  eventTypeD:%d is error!", __FUNCTION__, eventTypeDt);
        }
    }

    GWM_DVROperationReport dvr_operation_status;
    memset(&dvr_operation_status, 0, sizeof(dvr_operation_status));
    dvr_operation_status.operation_type = (GWM_DVREventOperationTypes)eventOperationTypeDt;
    dvr_operation_status.event_type = (GWM_DVREventType)eventTypeDt;
    dvr_operation_status.camera_id = accessTypeToCameraId(accessTypeDt);

    replyDVRStatusReportACKFunc(E_SUCCESSFUL);

    if (mDVRCallbackList.size() == 0) {
        mEventOperationReport.needNotify = true;
        mEventOperationReport.eventOperationType = eventOperationTypeDt;
        mEventOperationReport.eventType = eventTypeDt;
        mEventOperationReport.accessType = accessTypeDt;
        ALOGW("%s:  mDVRCallbackList is null !", __FUNCTION__);
        return;
    }

    for(auto callback : mDVRCallbackList)
    {
        if(!checkCallbackIsNull(callback))
        {
            ALOGD("%s:  gwm_onDVREventOperationNotify, operation_type:%hhu, event_type:%hhu",
                __FUNCTION__,
                dvr_operation_status.operation_type,
                dvr_operation_status.event_type);
            auto ret = callback->gwm_onDVREventOperationNotify(dvr_operation_status);
            if (!ret.isOk())
            {
                ALOGW("%s:  has error", __FUNCTION__);
            }
        }
    }
}

void DVR::onDVREventReportEventListener(std::string eventTime, EventType_DT eventTypeDt, AccessType_DT accessTypeDt, std::string filePath, std::string thumbnailPath)
{
    GWM_DVREventReport dvr_event_status;
    memset(&dvr_event_status, 0, sizeof(dvr_event_status));
    dvr_event_status.EventTime = eventTime;
    dvr_event_status.event_type = (GWM_DVREventType)eventTypeDt;
    dvr_event_status.camera_id = accessTypeToCameraId(accessTypeDt);
    dvr_event_status.FilePath = filePath;
    dvr_event_status.ThumbnailPath = thumbnailPath;

    replyDVRStatusReportACKFunc(E_SUCCESSFUL);

    if (mDVRCallbackList.size() == 0) {
        ALOGE("%s:  mDVRCallbackList is null !", __FUNCTION__);
        return;
    }

    for(auto callback : mDVRCallbackList)
    {
        if(!checkCallbackIsNull(callback))
        {
            ALOGD("%s:  gwm_onDVREventReportNotify, eventTime:%s, event_type:%hhu, filePath:%s, thumbnailPath:%s",
                __FUNCTION__,
                dvr_event_status.EventTime.c_str(),
                dvr_event_status.event_type,
                dvr_event_status.FilePath.c_str(),
                dvr_event_status.ThumbnailPath.c_str());
            auto ret = callback->gwm_onDVREventReportNotify(dvr_event_status);
            if (!ret.isOk())
            {
                ALOGW("%s:  has error", __FUNCTION__);
            }
        }
    }
}

void DVR::onDVRTFStatusReportEventListener(TFCardOption_DT tFCardOptionDt, TFCardStatus_DT tFCardStatusDt, TFCardCapacity_DT tFCardCapacityDt)
{
    /* GWM_DVR_TFCardStatus:
     *  GWM_DVR_TFCARD_NULL        = 0,
     *  GWM_DVR_TFCARD_NOT_EXIST   = 1,
     *  GWM_DVR_TFCARD_EXCEPTION   = 2,
     *  GWM_DVR_TFCARD_FULL        = 3,
     *  GWM_DVR_TFCARD_WRITE_SLOW  = 4,
     *  GWM_DVR_TFCARD_PLUGIN      = 5,
     *  GWM_DVR_TFCARD_Capacity_Not_Supported   = 6,
     *  GWM_DVR_TFCARD_Emergency_Space_Full = 7,
     *
     * GWM_DVR_TFCardId:
     *  GWM_DVR_TFCARD_NULL   = 0,
     *  GWM_DVR_TFCARD_FRONT  = 1,
     *  GWM_DVR_TFCARD_INCAR  = 2,
     *  GWM_DVR_TFCARD_ALL    = 3,
     */
    GWM_DVRTFCardStatus dvr_tfcard_status;
    memset(&dvr_tfcard_status, 0, sizeof(dvr_tfcard_status));
    switch(tFCardOptionDt){
        case E_TFCARD1:
            dvr_tfcard_status.tfcard_id = GWM_DVR_TFCardId::GWM_DVR_TFCARD_FRONT;
            break;
        case E_TFCARD2:
            dvr_tfcard_status.tfcard_id = GWM_DVR_TFCardId::GWM_DVR_TFCARD_INCAR;
            break;
        default:
            dvr_tfcard_status.tfcard_id = GWM_DVR_TFCardId::GWM_DVR_TFCARD_NULL;
            break;
    }

    switch (tFCardStatusDt)
    {
        case E_DVR_NOT_FOUND:
            dvr_tfcard_status.tfcard_status = GWM_DVR_TFCardStatus::GWM_DVR_TFCARD_NOT_EXIST;
            break;
        case E_DVR_FAULT:
            dvr_tfcard_status.tfcard_status = GWM_DVR_TFCardStatus::GWM_DVR_TFCARD_EXCEPTION;
            break;
        case E_DVR_MEMEORY_FULL:
            dvr_tfcard_status.tfcard_status = GWM_DVR_TFCardStatus::GWM_DVR_TFCARD_FULL;
            break;
        case E_DVR_OK:
            dvr_tfcard_status.tfcard_status = GWM_DVR_TFCardStatus::GWM_DVR_TFCARD_PLUGIN;
            break;
        case E_WRITESLOWLY:
            dvr_tfcard_status.tfcard_status = GWM_DVR_TFCardStatus::GWM_DVR_TFCARD_WRITE_SLOW;
            break;
        case E_DVR_EMERGENCY_SPACE_FULL:
            dvr_tfcard_status.tfcard_status = GWM_DVR_TFCardStatus::GWM_DVR_TFCARD_Emergency_Space_Full;
            break;
        case E_DVR_CAPACITY_NOT_SUPPORTED:
            dvr_tfcard_status.tfcard_status = GWM_DVR_TFCardStatus::GWM_DVR_TFCARD_Capacity_Not_Supported;
            break;
        default:
            dvr_tfcard_status.tfcard_status = GWM_DVR_TFCardStatus::GWM_DVR_TFCARD_NULL;
            break;
    }

    replyDVRStatusReportACKFunc(E_SUCCESSFUL);

    if (tFCardOptionDt == TFCardOption_DT::E_TFCARD1)
    {
        mTfCard1Status = tFCardStatusDt;
    }

    if (mDVRCallbackList.size() == 0) {
        mDVRTFStatus.needNotify = true;
        mDVRTFStatus.tFCardOption = tFCardOptionDt;
        mDVRTFStatus.tFCardStatus = tFCardStatusDt;
        mDVRTFStatus.tFCardCapacity = tFCardCapacityDt;
        ALOGE("%s:  mDVRCallbackList is null !", __FUNCTION__);
        return;
    }

    for(auto callback : mDVRCallbackList)
    {
        if(!checkCallbackIsNull(callback))
        {
            ALOGD("%s:  gwm_onDVRTFCardStatusNotify, GWM_DVR_TFCardId:%hhu, GWM_DVR_TFCardStatus:%hhu",
                __FUNCTION__,
                dvr_tfcard_status.tfcard_id,
                dvr_tfcard_status.tfcard_status);
            auto ret = callback->gwm_onDVRTFCardStatusNotify(dvr_tfcard_status);
            if (!ret.isOk())
            {
                ALOGW("%s:  has error", __FUNCTION__);
            }
        }
    }
}

void DVR::onDVREMMCStatusReportEventListener(EMMCStatus_DT eMMCStatusDt, EMMCCapacityStruct_DT eMMCCapacityStructDt)
{
    GWM_DVREMMCReport emmc_status_report;
    memset(&emmc_status_report, 0, sizeof(emmc_status_report));
    emmc_status_report.emmc_status = (GWM_DVREMMCStatus)eMMCStatusDt;
    emmc_status_report.TotalCapacity = eMMCCapacityStructDt.totalCapacity;
    emmc_status_report.RemainingCapacity = eMMCCapacityStructDt.remainingCapacity;

    replyDVRStatusReportACKFunc(E_SUCCESSFUL);

    if (mDVRCallbackList.size() == 0)
    {
        mDVREMMCStatus.needNotify = true;
        mDVREMMCStatus.eMMCStatus = eMMCStatusDt;
        mDVREMMCStatus.eMMCCapacityStruct = eMMCCapacityStructDt;
        ALOGW("%s:  mDVRCallbackList is null !", __FUNCTION__);
        return;
    }

    for(auto callback : mDVRCallbackList)
    {
        if(!checkCallbackIsNull(callback))
        {
            ALOGD("%s:  gwm_onDVREMMCStatusNotify, emmc_status:%hhu, TotalCapacity:%d, RemainingCapacity:%d",
                __FUNCTION__,
                emmc_status_report.emmc_status,
                emmc_status_report.TotalCapacity,
                emmc_status_report.RemainingCapacity);
            auto ret = callback->gwm_onDVREMMCStatusNotify(emmc_status_report);
            if (!ret.isOk())
            {
                ALOGW("%s:  has error", __FUNCTION__);
            }
        }
    }
}

void DVR::onExportOperationProgressReportEventListener(ExportFileInfoStruct_DT exportFileInfoStructDt, TotalTransProgress totalTransProgress)
{
    replyDVRStatusReportACKFunc(E_SUCCESSFUL);

    if (mDVRCallbackList.size() == 0)
    {
        ALOGE("%s:  mDVRCallbackList is null !", __FUNCTION__);
        return;
    }

    for(auto callback : mDVRCallbackList)
    {
        if(!checkCallbackIsNull(callback))
        {
            auto ret = callback->gwm_onDVRFileExportProcessNotify(totalTransProgress);
            if (!ret.isOk())
            {
                ALOGW("%s:  has error", __FUNCTION__);
            }
        }
    }
}

void DVR::onAsyncDeleteOperationProgressEventListener(DeleteProgress deleteProgress)
{
    replyDVRStatusReportACKFunc(E_SUCCESSFUL);

    if (mDVRCallbackList.size() == 0)
    {
        ALOGE("%s:  mDVRCallbackList is null !", __FUNCTION__);
        return;
    }

    for(auto callback : mDVRCallbackList)
    {
        if(!checkCallbackIsNull(callback))
        {
            auto ret = callback->gwm_onAsyncDeleteOperationProgressNotify(deleteProgress);
            if (!ret.isOk())
            {
                ALOGW("%s:  has error", __FUNCTION__);
            }
        }
    }
}

// check external dvr related someip service is ready.
bool DVR::checkIsReady(InterfaceType type, string method_name)
{
    bool result = false;
    /* type:
     *  FILE_OPERATION = 0,
     *  STATUS_REPORT = 1,
     *  SYSTEM_CONFIG = 2
     */
    switch (type)
    {
        case InterfaceType::FILE_OPERATION:
            if (DVRFileOperationIsReady())
            {
                result = true;
            }
            break;
        case InterfaceType::STATUS_REPORT:
            if (DVRStatusReportIsReady())
            {
                result = true;
            }
            break;
        case InterfaceType::SYSTEM_CONFIG:
            if (DVRSystemConfigIsReady())
            {
                result = true;
            }
            break;
        default:
            ALOGW("%s:  InterfaceType is error !", __FUNCTION__);
            break;
    }

    if (!result)
    {
        ALOGW("%s:  type:%hhu, method_name:%s, result:%d", __FUNCTION__, type, method_name.c_str(), result);
    }

    return result;
}

// convert cameraId to accessType.
AccessType_DT DVR::switch_cameraid(const GWM_DVRCameraId cameraId)
{
    AccessType_DT accessType = E_FORESIGHT;
    switch (cameraId)
    {
        case GWM_DVRCameraId::GWM_DVR_CAMERA_ID_FRONT:
            accessType = E_FORESIGHT;
            break;
        case GWM_DVRCameraId::GWM_DVR_CAMERA_ID_INCAR:
            accessType = E_WITHINSIGNT_OMC;
            break;
        case GWM_DVRCameraId::GWM_DVR_StreamingMedia_or_BackSignt_reserved:
            accessType = E_STREAMINGMEDIA_OR_BACKSIGNT_RESERVED;
            break;
        case GWM_DVRCameraId::GWM_DVR_CAMERA_ID_AVM:
            accessType = E_360SURROUNDVIEW;
            break;
        case GWM_DVRCameraId::GWM_DVR_MultiChannel:
            accessType = E_MULTICHANNEL;
            break;
        case GWM_DVRCameraId::GWM_DVR_WithinSignt_DMC:
            accessType = E_WITHINSIGNT_DMC;
            break;
        default:
            ALOGW("%s:  cameraId is error !", __FUNCTION__);
            break;
    }

    ALOGD("%s:  cameraId:%hu, accessType:%d", __FUNCTION__, cameraId, accessType);

    return accessType;
}

/**
 * @brief provide the functionality of send action cmd ACK to FWK.
 *        this method is only used to built-in DVR.
 * @param act_result it contains modules_name, act_module
 */
void DVR::sendActCommdAck(GWM_DVRBroadcastActionsResult act_result)
{
    std::lock_guard<std::mutex> lock(mMutex);
    ALOGI("%s:  ", __FUNCTION__);
    if (mDVRCallbackList.size() == 0)
    {
        ALOGE("%s:  mDVRCallbackList is null !", __FUNCTION__);
        return;
    }

    for(auto callback : mDVRCallbackList)
    {
        if(!checkCallbackIsNull(callback))
        {
            auto ret = callback->gwm_onDVRBroadcastActionsStatusNotify(act_result);
            if (!ret.isOk())
            {
                ALOGW("%s:  has error", __FUNCTION__);
            }
        }
    }
}

/**
 * @brief provide the functionality of send module event ACK to FWK.
 *        this method is only used to built-in DVR.
 * @param moduleEvent
 */
void DVR::sendModuleEventAck(GWM_DVRModulesEventResult moduleEvent)
{
    std::lock_guard<std::mutex> lock(mMutex);
    ALOGI("%s:  modules_name:%d, act_module:%d, event:%d, sequence:%lu",
        __FUNCTION__,
        (uint32_t)moduleEvent.modules_name,
        (uint32_t)moduleEvent.act_module,
        (uint32_t)moduleEvent.event,
        (uint64_t)moduleEvent.sequence);
    if (mDVRCallbackList.size() == 0)
    {
        ALOGE("%s:  mDVRCallbackList is null !", __FUNCTION__);
        return;
    }

    for(auto callback : mDVRCallbackList)
    {
        if(!checkCallbackIsNull(callback))
        {
            auto ret = callback->gwm_onDVRBroadcastEventsNotify(moduleEvent);
            if (!ret.isOk())
            {
                ALOGW("%s:  has error", __FUNCTION__);
            }
        }
    }
}

// notify the connection status of the DVR to FWK.
void DVR::notifyDVRConnectStatus(bool status) {
    std::lock_guard<std::mutex> lock(mMutex);
    if (mDVRCallbackList.size() == 0)
    {
        ALOGE("%s:  mDVRCallbackList is null !", __FUNCTION__);
        return;
    }

    GWM_DVRDeviceStatus deviceStatus = GWM_DVRDeviceStatus::DVR_STATUS_COMM_FAILURE;
    if (status)
    {
        deviceStatus = GWM_DVRDeviceStatus::DVR_STATUS_NORMAL;
    }
    else
    {
        if (!mDVRInternal)
        {
            sendMsgToQnxForOMSStream(GWM_DVRCameraId::GWM_DVR_CAMERA_ID_INCAR,GWM_DVRVideoOperateType::GWM_DVR_VIDEO_OPERATE_STOP,GWM_DVR_VIDEO_TYPE::GWM_DVR_VIDEO_TYPE_SHORT);
        }
    }

    for (auto callback : mDVRCallbackList)
    {
        if(!checkCallbackIsNull(callback))
        {
            ALOGI("%s:  gwm_onDVRStatusNotify, deviceStatus:%hhu",
                __FUNCTION__,
                deviceStatus);
            auto ret = callback->gwm_onDVRStatusNotify(deviceStatus);
            if (!ret.isOk())
            {
                ALOGW("%s:  has error !", __FUNCTION__);
            }
        }
    }
}

GWM_Status DVR::startRecord(GWM_DVRCameraId cameraId, GWM_DVR_VIDEO_TYPE type)
{
    GWM_Status status = GWM_Status::GWM_ERROR;
    CallStatus_DT callStatus = CallStatus_DT::UNKNOWN;
    SetResultManualOperationACKOut out;
    memset(&out, 0, sizeof(out));
    SetResultVideoRecordingACKOut recording_out;
    memset(&recording_out, 0, sizeof(recording_out));
    AccessType_DT accessTypeDt = switch_cameraid(cameraId);
    switch (type)
    {
        case GWM_DVR_VIDEO_TYPE::GWM_DVR_VIDEO_TYPE_SHORT: // pre recording duration is 0, and the total duration is 10.
            if (!checkIsReady(InterfaceType::STATUS_REPORT, __FUNCTION__))
            {
                onEventOperationReportEventListener(EventOperationType_DT::E_EVENTFAILED,
                    EventType_DT::E_SHORTVIDEORECORDING_BYHUT,
                    switch_cameraid(cameraId));
                return status;
            }

            /**
             * @brief StartShortVideoRecording comes from DVRStatusReport service of someip.
             * serviceid:0x0401
             * methodid: 0x0005
             */
            callStatus = StartShortVideoRecordingFunc(accessTypeDt, 0, 10, recording_out);
            ALOGI("%s:  StartShortVideoRecordingFunc callStatus:%d, SetResultVideoRecordingACKOut:%d",
                __FUNCTION__,
                callStatus,
                recording_out.videoRecordingACK);
            if (callStatus == CallStatus_DT::SUCCESS
                && recording_out.videoRecordingACK == SetResult_DT::E_SUCCESSFUL)
            {
                status = GWM_Status::GWM_OK;
            }
            else
            {
                onEventOperationReportEventListener(EventOperationType_DT::E_EVENTFAILED,
                    EventType_DT::E_SHORTVIDEORECORDING_BYHUT,
                    switch_cameraid(cameraId));
                return status;
            }
            break;
        case GWM_DVR_VIDEO_TYPE::GWM_DVR_VIDEO_TYPE_LONG:
            if (!checkIsReady(InterfaceType::STATUS_REPORT, __FUNCTION__))
            {
                onEventOperationReportEventListener(EventOperationType_DT::E_EVENTFAILED,
                    EventType_DT::E_MANUALRECORDING_BYHUT,
                    switch_cameraid(cameraId));
                return status;
            }

            /**
             * @brief DVRManualOperation comes from DVRStatusReport service of someip.
             * serviceid:0x0401
             * methodid: 0x0002
             */
            callStatus = DVRManualOperationFunc(ManualOperation_DT::E_MANUALRECORDING, accessTypeDt, out);
            ALOGI("%s:  DVRManualOperationFunc callStatus:%d, SetResultManualOperationACKOut:%d",
                __FUNCTION__,
                callStatus,
                out.manualOperationACK);
            if (callStatus == CallStatus_DT::SUCCESS
                && out.manualOperationACK == SetResult_DT::E_SUCCESSFUL)
            {
                status = GWM_Status::GWM_OK;
            }
            else
            {
                onEventOperationReportEventListener(EventOperationType_DT::E_EVENTFAILED,
                    EventType_DT::E_MANUALRECORDING_BYHUT,
                    switch_cameraid(cameraId));
                return status;
            }
            break;
        default:
            ALOGW("%s:  type:%hhu is error !", __FUNCTION__, type);
            break;
    }
    return status;
}

GWM_Status DVR::stopRecord(GWM_DVRCameraId cameraId, GWM_DVR_VIDEO_TYPE type)
{
    GWM_Status status = GWM_Status::GWM_ERROR;
    CallStatus_DT callStatus = CallStatus_DT::UNKNOWN;
    SetResultManualOperationACKOut out;
    memset(&out, 0, sizeof(out));
    SetResultVideoRecordingACKOut recording_out;
    memset(&recording_out, 0, sizeof(recording_out));
    AccessType_DT accessTypeDt = switch_cameraid(cameraId);
    switch (type)
    {
        case GWM_DVR_VIDEO_TYPE::GWM_DVR_VIDEO_TYPE_SHORT: // pre recording duration is 0, and the total duration is 10.
            if (!checkIsReady(InterfaceType::STATUS_REPORT, __FUNCTION__))
            {
                onEventOperationReportEventListener(EventOperationType_DT::E_EVENTFAILED,
                    EventType_DT::E_SHORTVIDEORECORDING_BYHUT,
                    switch_cameraid(cameraId));
                return GWM_Status::GWM_ERROR;
            }

            /**
             * @brief StopShortVideoRecording comes from DVRStatusReport service of someip.
             * serviceid:0x0401
             * methodid: 0x0006
             */
            callStatus = StopShortVideoRecordingFunc(accessTypeDt, recording_out);
            ALOGI("%s:  StopShortVideoRecordingFunc callStatus:%d, SetResultVideoRecordingACKOut:%d",
                __FUNCTION__,
                callStatus,
                recording_out.videoRecordingACK);
            if (callStatus == CallStatus_DT::SUCCESS
                && recording_out.videoRecordingACK == SetResult_DT::E_SUCCESSFUL)
            {
                status = GWM_Status::GWM_OK;
            }
            else
            {
                onEventOperationReportEventListener(EventOperationType_DT::E_EVENTFAILED,
                    EventType_DT::E_SHORTVIDEORECORDING_BYHUT,
                    switch_cameraid(cameraId));
                return status;
            }
            break;
        case GWM_DVR_VIDEO_TYPE::GWM_DVR_VIDEO_TYPE_LONG:
            if (!checkIsReady(InterfaceType::STATUS_REPORT, __FUNCTION__))
            {
                onEventOperationReportEventListener(EventOperationType_DT::E_EVENTFAILED,
                    EventType_DT::E_MANUALRECORDING_BYHUT,
                    switch_cameraid(cameraId));
                return GWM_Status::GWM_ERROR;
            }

            /**
             * @brief DVRManualOperation comes from DVRStatusReport service of someip.
             * serviceid:0x0401
             * methodid: 0x0002
             */
            callStatus = DVRManualOperationFunc(ManualOperation_DT::E_MANUALRECORDING, accessTypeDt, out);
            ALOGI("%s:  DVRManualOperationFunc callStatus:%d, SetResultManualOperationACKOut:%d",
                __FUNCTION__,
                callStatus,
                out.manualOperationACK);
            if (callStatus == CallStatus_DT::SUCCESS
                && out.manualOperationACK == SetResult_DT::E_SUCCESSFUL)
            {
                status = GWM_Status::GWM_OK;
            }
            else
            {
                onEventOperationReportEventListener(EventOperationType_DT::E_EVENTFAILED,
                    EventType_DT::E_MANUALRECORDING_BYHUT,
                    switch_cameraid(cameraId));
                return status;
            }
            break;
        default:
            ALOGW("%s:  type:%hhu is error !", __FUNCTION__, type);
            break;
    }
    return status;
}

GWM_Status DVR::startCapture(GWM_DVRCameraId cameraId, GWM_DVR_VIDEO_TYPE type)
{
    GWM_Status status = GWM_Status::GWM_ERROR;
    CallStatus_DT callStatus = CallStatus_DT::UNKNOWN;
    switch(type)
    {
        case GWM_DVR_VIDEO_TYPE::GWM_DVR_CAPTURE_CONTINUOUS:
            if (!checkIsReady(InterfaceType::STATUS_REPORT, __FUNCTION__))
            {
                onEventOperationReportEventListener(EventOperationType_DT::E_EVENTFAILED,
                    EventType_DT::E_CONTINUOUSCAPTURE,
                    switch_cameraid(cameraId));
                return status;
            }

            SetResultContinuousCaptureACKOut continuousOut;
            memset(&continuousOut, 0, sizeof(continuousOut));
            /**
             * @brief DVRContinuousCapture comes from DVRStatusReport service of someip.
             * serviceid:0x0401
             * methodid: 0x0004
             */
            callStatus = DVRContinuousCaptureFunc(switch_cameraid(cameraId), 3, 1, continuousOut);
            ALOGI("%s:  DVRContinuousCaptureFunc callStatus:%d, SetResultContinuousCaptureACKOut:%d",
                    __FUNCTION__,
                    callStatus,
                    continuousOut.continuousCaptureACK);
            if (callStatus != CallStatus_DT::SUCCESS)
            {
                onEventOperationReportEventListener(EventOperationType_DT::E_EVENTFAILED,
                    EventType_DT::E_CONTINUOUSCAPTURE,
                    switch_cameraid(cameraId));
                return status;
            }

            if (continuousOut.continuousCaptureACK == SetResult_DT::E_SUCCESSFUL)
            {
                status = GWM_Status::GWM_OK;
            }
            break;
        case GWM_DVR_VIDEO_TYPE::GWM_DVR_CAPTURE:
            if (!checkIsReady(InterfaceType::STATUS_REPORT, __FUNCTION__))
            {
                onEventOperationReportEventListener(EventOperationType_DT::E_EVENTFAILED,
                    EventType_DT::E_MANUALCAPTURE_BYHUT,
                    switch_cameraid(cameraId));
                return status;
            }

            SetResultManualOperationACKOut out;
            memset(&out, 0, sizeof(out));
            /**
             * @brief DVRManualOperation comes from DVRStatusReport service of someip.
             * serviceid:0x0401
             * methodid: 0x0002
             */
            callStatus = DVRManualOperationFunc(E_MANUALCAPTURE, switch_cameraid(cameraId), out);
            ALOGI("%s:  DVRManualOperationFunc callStatus:%d, SetResultManualOperationACKOut:%d",
                __FUNCTION__,
                callStatus,
                out.manualOperationACK);
            if (callStatus != CallStatus_DT::SUCCESS)
            {
                onEventOperationReportEventListener(EventOperationType_DT::E_EVENTFAILED,
                    EventType_DT::E_MANUALCAPTURE_BYHUT,
                    switch_cameraid(cameraId));
                return GWM_Status::GWM_ERROR;
            }

            if (out.manualOperationACK == SetResult_DT::E_SUCCESSFUL)
            {
                status = GWM_Status::GWM_OK;
            }
            break;
        case GWM_DVR_VIDEO_TYPE::GWM_DVR_CAPTURE_FINDCAR:
            SetResultManualOperationACKOut findCarOut;
            memset(&findCarOut, 0, sizeof(findCarOut));
            /**
             * @brief DVRManualOperation comes from DVRStatusReport service of someip.
             * serviceid:0x0401
             * methodid: 0x0002
             */
            // callStatus = DVRManualOperationFunc(E_FINDCARCAPTURE, switch_cameraid(cameraId), findCarOut);
            ALOGI("%s:  DVRManualOperationFunc callStatus:%d, SetResultManualOperationACKOut:%d",
                __FUNCTION__,
                callStatus,
                findCarOut.manualOperationACK);
            if (callStatus != CallStatus_DT::SUCCESS)
            {
                onEventOperationReportEventListener(EventOperationType_DT::E_EVENTFAILED,
                    EventType_DT::E_MANUALCAPTURE_BYFINDCAR,
                    switch_cameraid(cameraId));
                return GWM_Status::GWM_ERROR;
            }

            if (findCarOut.manualOperationACK == SetResult_DT::E_SUCCESSFUL)
            {
                status = GWM_Status::GWM_OK;
            }
            break;
        default:
            ALOGW("%s:  type:%hhu is error !", __FUNCTION__, type);
            break;
    }
    return status;
}

GWM_Status DVR::startLapseVideo(GWM_DVRCameraId cameraId,
                            int64_t timeLapseVideoInteval,
                            int16_t totalFrameNumber,
                            int16_t playFrameNumber)
{
    GWM_Status status = GWM_Status::GWM_ERROR;
    if (!checkIsReady(InterfaceType::STATUS_REPORT, __FUNCTION__))
    {
        onEventOperationReportEventListener(EventOperationType_DT::E_EVENTFAILED,
            EventType_DT::E_TIMELAPSEVIDEO,
            switch_cameraid(cameraId));
        return status;
    }

    SetResultTimelapseVideoTapeACKOut out;
    memset(&out, 0, sizeof(out));
    /**
     * @brief DVRTimelapseVideoTape comes from DVRStatusReport service of someip.
     * serviceid:0x0401
     * methodid: 0x0003
     */
    CallStatus_DT callStatus = DVRTimelapseVideoTapeFunc(timeLapseVideoInteval, totalFrameNumber, playFrameNumber, switch_cameraid(cameraId), out);
    ALOGI("%s:  DVRTimelapseVideoTapeFunc callStatus:%d, SetResultTimelapseVideoTapeACKOut:%d",
        __FUNCTION__,
        callStatus,
        out.timelapseVideoTapeACK);
    if (callStatus == CallStatus_DT::SUCCESS
        && out.timelapseVideoTapeACK == SetResult_DT::E_SUCCESSFUL)
    {
        status = GWM_Status::GWM_OK;
    }
    else
    {
        onEventOperationReportEventListener(EventOperationType_DT::E_EVENTFAILED,
                EventType_DT::E_TIMELAPSEVIDEO,
                switch_cameraid(cameraId));
        return status;
    }
    return status;
}

GWM_Status DVR::stopLapseVideo(GWM_DVRCameraId cameraId)
{
    GWM_Status status = GWM_Status::GWM_ERROR;
    if (!checkIsReady(InterfaceType::STATUS_REPORT, __FUNCTION__))
    {
        onEventOperationReportEventListener(EventOperationType_DT::E_EVENTFAILED,
            EventType_DT::E_TIMELAPSEVIDEO,
            switch_cameraid(cameraId));
        return status;
    }

    SetResultManualOperationACKOut out;
    memset(&out, 0, sizeof(out));
    /**
     * @brief DVRManualOperation comes from DVRStatusReport service of someip.
     * serviceid:0x0401
     * methodid: 0x0002
     */
    CallStatus_DT callStatus = DVRManualOperationFunc(E_STOPTIMELAPSEVIDEOTAPE, switch_cameraid(cameraId), out);
    ALOGI("%s:  DVRManualOperationFunc callStatus:%d, SetResultManualOperationACKOut:%d",
        __FUNCTION__,
        callStatus,
        out.manualOperationACK);
    if (callStatus == CallStatus_DT::SUCCESS
        && out.manualOperationACK == SetResult_DT::E_SUCCESSFUL)
    {
        status = GWM_Status::GWM_OK;
    }
    else
    {
        onEventOperationReportEventListener(EventOperationType_DT::E_EVENTFAILED,
                EventType_DT::E_TIMELAPSEVIDEO,
                switch_cameraid(cameraId));
        return status;
    }
    return status;
}

GWM_Status DVR::querySystemStatus()
{
    GWM_Status result = GWM_Status::GWM_ERROR;
    TFCardStatus_DT dt_status = TFCardStatus_DT::E_DVR_NOT_FOUND;
    TFCardCapacity_DT dt_capa;
    memset(&dt_capa, 0, sizeof(dt_capa));
    result = queryTFCardInfo(dt_status, dt_capa);

    TotalExportCapacity totalExportCapacity = 0;
    FreeExportCapacity freeExportCapacity = 0;
    CallStatus_DT tfCardExportcallStatus = CallStatus_DT::UNKNOWN;
    result = queryTFCardExportCapacity(totalExportCapacity, freeExportCapacity, tfCardExportcallStatus);

    GWM_DVR_TFCardStatus dvr_tfcard_status;
    switch (dt_status)
    {
        case E_DVR_NOT_FOUND:
            dvr_tfcard_status = GWM_DVR_TFCardStatus::GWM_DVR_TFCARD_NOT_EXIST;
            break;
        case E_DVR_FAULT:
            dvr_tfcard_status = GWM_DVR_TFCardStatus::GWM_DVR_TFCARD_EXCEPTION;
            break;
        case E_DVR_MEMEORY_FULL:
            dvr_tfcard_status = GWM_DVR_TFCardStatus::GWM_DVR_TFCARD_FULL;
            break;
        case E_DVR_OK:
            dvr_tfcard_status = GWM_DVR_TFCardStatus::GWM_DVR_TFCARD_PLUGIN;
            break;
        case E_WRITESLOWLY:
            dvr_tfcard_status = GWM_DVR_TFCardStatus::GWM_DVR_TFCARD_WRITE_SLOW;
            break;
        case E_DVR_EMERGENCY_SPACE_FULL:
            dvr_tfcard_status = GWM_DVR_TFCardStatus::GWM_DVR_TFCARD_Emergency_Space_Full;
            break;
        case E_DVR_CAPACITY_NOT_SUPPORTED:
            dvr_tfcard_status = GWM_DVR_TFCardStatus::GWM_DVR_TFCARD_Capacity_Not_Supported;
            break;
        default:
            dvr_tfcard_status = GWM_DVR_TFCardStatus::GWM_DVR_TFCARD_NULL;
            break;
    }
    GWM_DVR_SystemStatus status;
    memset(&status, 0, sizeof(status));
    status.front_sdcard_status = dvr_tfcard_status;
    GWM_DVRTFCardInfor capacity_status;
    capacity_status.tfcard_total_capacity = (float)dt_capa.totalCapacity;
    capacity_status.tfcard_used_capacity = (float)(dt_capa.totalCapacity - dt_capa.remainingCapacity);
    capacity_status.total_export_capacity = (float)totalExportCapacity;
    capacity_status.free_export_capacity = (float)freeExportCapacity;
    capacity_status.tfcard_loop_capacity = 0;
    capacity_status.tfcard_emergency_capacity = 0;
    capacity_status.tfcard_normal_capacity = 0;
    capacity_status.tfcard_format_type = GWM_DVR_TFType::DVR_TF_TYPE_UNKOWN;
    capacity_status.tfcard_loop_capacity_status = GWM_DVRCapacityStatus::GWM_DVR_CAPACITY_STATUS_UNKNOWN;
    capacity_status.tfcard_emergency_capacity_status = GWM_DVRCapacityStatus::GWM_DVR_CAPACITY_STATUS_UNKNOWN;
    capacity_status.tfcard_normal_capacity_status = GWM_DVRCapacityStatus::GWM_DVR_CAPACITY_STATUS_UNKNOWN;
    status.front_infor = capacity_status;

    DVRSystemStatusOut systemStatusOut;
    memset(&systemStatusOut, 0, sizeof(systemStatusOut));
    DVRSensorStatusStruct_DT sensorStatusOut;
    memset(&sensorStatusOut, 0, sizeof(sensorStatusOut));
    CallStatus_DT dvrSystemcallStatus = CallStatus_DT::UNKNOWN;
    CallStatus_DT dvrSensorcallStatus = CallStatus_DT::UNKNOWN;
    result = queryDVRSystemStatus(systemStatusOut, dvrSystemcallStatus);
    result = queryDVRSensorStatus(sensorStatusOut, dvrSensorcallStatus);

    ALOGI("%s:  dvrSystemStatus:%d, accessType:%d, frontSensorStatus:%d, mCameraInnerStatus:%d, mCameraAVMStatus:%d",
        __FUNCTION__,
        systemStatusOut.dvrSystemStatusDt,
        sensorStatusOut.accessTypeDt,
        sensorStatusOut.dvrSensorStatusDt,
        mCameraInnerStatus,
        mCameraAVMStatus);
    if (dvrSystemcallStatus == CallStatus_DT::SUCCESS)
    {
        if (systemStatusOut.dvrSystemStatusDt == DVRSystemStatus_DT::E_DVR_STATUS_OK)
        {
            status.device_status = GWM_DVRSystemStatus::GWM_DVR_SYSTEM_NORMAL;
        }
        else
        {
            status.device_status = GWM_DVRSystemStatus::GWM_DVR_SYSTEM_EXCEPTION;
        }
    }
    else
    {
        if (isExDVRReady)
        {
            status.device_status = GWM_DVRSystemStatus::GWM_DVR_SYSTEM_NORMAL;
        }
        else
        {
            status.device_status = GWM_DVRSystemStatus::GWM_DVR_SYSTEM_EXCEPTION;
        }
    }

    if (dvrSensorcallStatus == CallStatus_DT::SUCCESS)
    {
        if (sensorStatusOut.accessTypeDt == AccessType_DT::E_FORESIGHT
            && sensorStatusOut.dvrSensorStatusDt == DVRSensorStatus_DT::E_SENSOR_OK)
        {
            status.front_camera_status = GWM_DVRSystemStatus::GWM_DVR_SYSTEM_NORMAL;
        }
        else
        {
            status.front_camera_status = GWM_DVRSystemStatus::GWM_DVR_SYSTEM_EXCEPTION;
        }
    }
    else
    {
        if (mCameraFrontStatus == E_SENSOR_OK)
        {
            status.front_camera_status = GWM_DVRSystemStatus::GWM_DVR_SYSTEM_NORMAL;
        }
        else if (mCameraFrontStatus == E_SENSOR_FAULT)
        {
            status.front_camera_status = GWM_DVRSystemStatus::GWM_DVR_SYSTEM_EXCEPTION;
        }
        else
        {
            status.front_camera_status = GWM_DVRSystemStatus::GWM_DVR_SYSTEM_STATUS_NULL;
        }
    }

    if (mCameraInnerStatus == static_cast<uint8_t>(GWM_DVRSystemStatus::GWM_DVR_SYSTEM_NORMAL))
    {
        status.incar_camera_status = GWM_DVRSystemStatus::GWM_DVR_SYSTEM_NORMAL;
    }
    else if (mCameraInnerStatus == static_cast<uint8_t>(GWM_DVRSystemStatus::GWM_DVR_SYSTEM_EXCEPTION))
    {
        status.incar_camera_status = GWM_DVRSystemStatus::GWM_DVR_SYSTEM_EXCEPTION;
    }
    else
    {
        status.incar_camera_status = GWM_DVRSystemStatus::GWM_DVR_SYSTEM_STATUS_NULL;
    }

    if (mCameraAVMStatus == E_SENSOR_OK)
    {
        status.avm_camera_status = GWM_DVRSystemStatus::GWM_DVR_SYSTEM_NORMAL;
    }
    else if (mCameraAVMStatus == E_SENSOR_FAULT)
    {
        status.avm_camera_status = GWM_DVRSystemStatus::GWM_DVR_SYSTEM_EXCEPTION;
    }
    else
    {
        status.avm_camera_status = GWM_DVRSystemStatus::GWM_DVR_SYSTEM_STATUS_NULL;
    }

    if (mDVRCallbackList.size() == 0)
    {
        ALOGE("%s:  mDVRCallbackList is null !", __FUNCTION__);
        return GWM_Status::GWM_ERROR;
    }

    for(auto callback : mDVRCallbackList)
    {
        if(!checkCallbackIsNull(callback))
        {
            ALOGI("%s:  gwm_onDVRSystemStatusNotify, tfcard_status:%hhu, total_capacity:%f, used_capacity:%f, totalExportCapacity:%f, freeExportCapacity:%f",
                __FUNCTION__,
                dvr_tfcard_status,
                capacity_status.tfcard_total_capacity,
                capacity_status.tfcard_used_capacity,
                capacity_status.total_export_capacity,
                capacity_status.free_export_capacity);
            auto ret = callback->gwm_onDVRSystemStatusNotify(status);
            if (!ret.isOk())
            {
                ALOGW("%s:  gwm_onDVRSystemStatusNotify has error, description:%s !", __FUNCTION__, ret.description().c_str());
            }
        }
    }
    return result;
}

int32_t DVR::exportFileCapacity(const std::vector<std::string>& file_path_url, bool isSync)
{
    FileListPath_DT dt;
    memset(&dt, 0, sizeof(dt));
    for (uint32_t i = 0; i < file_path_url.size(); i++)
    {
        ALOGD("%s:  file_path_url-size:%lu, path:%s",
            __FUNCTION__,
            file_path_url.size(),
            file_path_url[i].c_str());
        dt.filePath.push_back(file_path_url[i]);
    }

    bool isSuccess = false;
    FileCapacity fileCapacity = -1;
    if (checkIsReady(InterfaceType::FILE_OPERATION, __FUNCTION__))
    {
        SetResult_DT setResultDt = SetResult_DT::E_FAILED;
        /**
         * @brief SelectFileCapacityRequest comes from DVRFileOperation service of someip.
         * serviceid:0x0402
         * methodid: 0x000E
         */
        CallStatus_DT callStatus = SelectFileCapacityRequestFuc(dt, setResultDt, fileCapacity);
        ALOGI("%s:  SelectFileCapacityRequestFuc callStatus:%d, setResultDt:%d, fileCapacity:%u",
            __FUNCTION__,
            callStatus,
            setResultDt,
            fileCapacity);
        if (callStatus == CallStatus_DT::SUCCESS
            && setResultDt == SetResult_DT::E_SUCCESSFUL)
        {
            isSuccess = true;
        }
    }

    if (isSync)
    {
        if (isSuccess)
        {
            return fileCapacity;
        }
        else
        {
            return -1;
        }
    }
    else
    {
        if (mDVRCallbackList.size() == 0)
        {
            ALOGE("%s:  mDVRCallbackList is null !", __FUNCTION__);
            return -1;
        }

        hidl_vec<hidl_string> vec_url;
        vec_url.resize(file_path_url.size());
        vec_url.setToExternal(new hidl_string(*(file_path_url.data())), file_path_url.size());
        if (isSuccess)
        {
            for(auto callback : mDVRCallbackList)
            {
                if(!checkCallbackIsNull(callback))
                {
                    ALOGI("%s:  gwm_onExportFileCapacityNotify, fileCapacity:%d", __FUNCTION__, fileCapacity);
                    auto ret = callback->gwm_onExportFileCapacityNotify(fileCapacity, vec_url);
                    if (!ret.isOk())
                    {
                        ALOGW("%s:  has error", __FUNCTION__);
                    }
                }
            }
            return fileCapacity;
        }
        else
        {
            for(auto callback : mDVRCallbackList)
            {
                if(!checkCallbackIsNull(callback))
                {
                    ALOGI("%s:  gwm_onExportFileCapacityNotify, error !", __FUNCTION__);
                    auto ret = callback->gwm_onExportFileCapacityNotify(-1, vec_url);
                    if (!ret.isOk())
                    {
                        ALOGW("%s:  has error", __FUNCTION__);
                    }
                }
            }
            return -1;
        }
    }
}

int32_t DVR::selectAllFileCapacity(GWM_DVRCameraId camera_id, GWM_DVRFileType file_type, bool isSync)
{
    int32_t file_capacity = -1;
    bool isSuccess = false;
    if (checkIsReady(InterfaceType::FILE_OPERATION, __FUNCTION__))
    {
        AccessTypeOut accessType_Out;
        memset(&accessType_Out, 0, sizeof(accessType_Out));
        FileTypeOut fileType_Out;
        memset(&fileType_Out, 0, sizeof(fileType_Out));
        /**
         * @brief SelectAllFileCapacityRequest comes from DVRFileOperation service of someip.
         * serviceid:0x0402
         * methodid: 0x000C
         */
        CallStatus_DT callStatus = SelectAllFileCapacityRequestFunc(switch_cameraid(camera_id),
            (FileType_DT)file_type,
            accessType_Out,
            fileType_Out,
            file_capacity);
        ALOGI("%s:  SelectAllFileCapacityRequestFunc callStatus:%d, accessType_Out:%d, fileType_Out:%d, file_capacity:%d",
            __FUNCTION__,
            callStatus,
            accessType_Out.accessTypeDT,
            fileType_Out.fileTypeDt,
            file_capacity);
        if (callStatus == CallStatus_DT::SUCCESS)
        {
            isSuccess = true;
        }
    }

    if (isSync)
    {
        if (isSuccess)
        {
            return file_capacity;
        }
        else
        {
            return -1;
        }
    }
    else
    {
        if (mDVRCallbackList.size() == 0)
        {
            ALOGE("%s:  mDVRCallbackList is null !", __FUNCTION__);
            return -1;
        }

        if (isSuccess)
        {
            for(auto callback : mDVRCallbackList)
            {
                if(!checkCallbackIsNull(callback))
                {
                    ALOGI("%s:  gwm_onAllFileCapacityNotify, file_capacity:%d", __FUNCTION__, file_capacity);
                    auto ret = callback->gwm_onAllFileCapacityNotify(file_capacity, camera_id, file_type);
                    if (!ret.isOk())
                    {
                        ALOGW("%s:  has error", __FUNCTION__);
                    }
                }
            }
            return file_capacity;
        }
        else
        {
            for(auto callback : mDVRCallbackList)
            {
                if(!checkCallbackIsNull(callback))
                {
                    ALOGW("%s:  gwm_onAllFileCapacityNotify, file_capacity:-1", __FUNCTION__);
                    auto ret = callback->gwm_onAllFileCapacityNotify(-1, camera_id, file_type);
                    if (!ret.isOk())
                    {
                        ALOGW("%s:  has error", __FUNCTION__);
                    }
                }
            }
            return -1;
        }
    }
}

GWM_DVROMCCaptureStatus DVR::dvrCaptureRequest(const AccessType_DT access_type,
    const std::string& eventTime,
    GWM_DVREventType eventType,
    uint32_t fileId,
    uint32_t fileSize,
    bool isOmc,
    bool isSync)
{
    GWM_DVROMCCaptureStatus status = GWM_DVROMCCaptureStatus::GWM_OMCCapture_Unknow;
    if (checkIsReady(InterfaceType::STATUS_REPORT, __FUNCTION__))
    {
        OMCCaptureFaileCodeOut out;
        memset(&out, 0, sizeof(out));
        /**
         * @brief OMCCaptureRequest comes from DVRStatusReport service of someip.
         * serviceid:0x0401
         * methodid: 0x000A
         */
        CallStatus_DT callStatus = OMCCaptureRequestFuc(eventTime.c_str(),
            (EventType_DT)eventType,
            access_type,
            (FileID)fileId,
            (FileSize)fileSize,
            out);
        ALOGI("%s:  OMCCaptureRequestFuc callStatus:%d, OMCCaptureFaileCodeOut:%d",
            __FUNCTION__,
            callStatus,
            out.omcCaptureFaileCode);
        if (callStatus == CallStatus_DT::SUCCESS)
        {
            status = (GWM_DVROMCCaptureStatus)out.omcCaptureFaileCode;
        }
    }

    if (!isSync)
    {
        if (mDVRCallbackList.size() == 0)
        {
            ALOGE("%s:  mDVRCallbackList is null !", __FUNCTION__);
            return GWM_DVROMCCaptureStatus::GWM_OMCCapture_Unknow;
        }

        for(auto callback : mDVRCallbackList)
        {
            if(!checkCallbackIsNull(callback))
            {
                if (isOmc)
                {
                    ALOGI("%s:  gwm_onOMCCaptureStatusNotify, status:%hhu",
                        __FUNCTION__,
                        status);
                    auto ret = callback->gwm_onOMCCaptureStatusNotify(status, hidl_string(eventTime), eventType, fileId, fileSize);
                    if (!ret.isOk())
                    {
                        ALOGW("%s:  has error", __FUNCTION__);
                    }
                }
                else
                {
                    ALOGI("%s:  gwm_onDVRCaptureStatusNotify, status:%hhu",
                        __FUNCTION__,
                        status);
                    auto ret = callback->gwm_onDVRCaptureStatusNotify(status, hidl_string(eventTime), eventType, fileId, fileSize);
                    if (!ret.isOk())
                    {
                        ALOGW("%s:  has error", __FUNCTION__);
                    }
                }
            }
        }
    }
    return status;
}

GWM_DVROMCCaptureStatus DVR::dvrCaptureTransferRequest(const AccessType_DT access_type,
    const std::string& eventTime,
    GWM_DVREventType eventType,
    uint32_t fileId,
    uint32_t fileSize,
    const std::string& filePath,
    bool isOmc,
    bool isSync)
{
    std::ifstream is(filePath.c_str(), std::ifstream::binary);
    vector<uint8_t> fileContentArray;
    if (is)
    {
        is.seekg(0, is.end);
        uint32_t length = is.tellg();
        is.seekg(0, is.beg);
        uint8_t *buffer = new uint8_t[length];
        is.read(reinterpret_cast<char *>(buffer), length);
        is.close();
        for (uint32_t i = 0; i < length; i++)
        {
            fileContentArray.push_back(buffer[i]);
        }
        delete[] buffer;
        ALOGD("%s:  filelength:%d", __FUNCTION__, length);
    }
    FileContentArray_DT dt;
    memset(&dt, 0, sizeof(dt));
    for (uint32_t i = 0; i < fileContentArray.size(); i++)
    {
        dt.dynamicBYTE.push_back(fileContentArray[i]);
    }

    GWM_DVROMCCaptureStatus status = GWM_DVROMCCaptureStatus::GWM_OMCCapture_Unknow;
    if (checkIsReady(InterfaceType::STATUS_REPORT, __FUNCTION__))
    {
        OMCCaptureFaileCodeOut out;
        memset(&out, 0, sizeof(out));
        /**
         * @brief PictureTransferRequest comes from DVRStatusReport service of someip.
         * serviceid:0x0401
         * methodid: 0x000B
         */
        CallStatus_DT callStatus = PictureTransferRequestFuc(eventTime.c_str(),
            (EventType_DT)eventType,
            access_type,
            (FileID)fileId,
            (FileSize)fileSize,
            dt,
            out);
        ALOGI("%s:  PictureTransferRequestFuc callStatus:%d, OMCCaptureFaileCodeOut:%d",
            __FUNCTION__,
            callStatus,
            out.omcCaptureFaileCode);
        if (callStatus == CallStatus_DT::SUCCESS)
        {
            status = (GWM_DVROMCCaptureStatus)out.omcCaptureFaileCode;
        }
    }

    if (!isSync)
    {
        if (mDVRCallbackList.size() == 0)
        {
            ALOGE("%s:  mDVRCallbackList is null !", __FUNCTION__);
            return GWM_DVROMCCaptureStatus::GWM_OMCCapture_Unknow;
        }

        for(auto callback : mDVRCallbackList)
        {
            if(!checkCallbackIsNull(callback))
            {
                if (isOmc)
                {
                    ALOGI("%s:  gwm_onOMCCaptureTransferStatusNotify, status:%hhu",
                        __FUNCTION__,
                        status);

                    auto ret = callback->gwm_onOMCCaptureTransferStatusNotify(status,
                        hidl_string(eventTime),
                        eventType,
                        fileId,
                        fileSize,
                        hidl_string(filePath));
                    if (!ret.isOk())
                    {
                        ALOGW("%s:  has error", __FUNCTION__);
                    }
                }
                else
                {
                    ALOGI("%s:  gwm_onDVRCaptureTransferStatusNotify, status:%hhu",
                        __FUNCTION__,
                        status);

                    auto ret = callback->gwm_onDVRCaptureTransferStatusNotify(status,
                        hidl_string(eventTime),
                        eventType,
                        fileId,
                        fileSize,
                        hidl_string(filePath));
                    if (!ret.isOk())
                    {
                        ALOGW("%s:  has error", __FUNCTION__);
                    }
                }
            }
        }
    }
    return status;
}

// get pss for DVR.
void DVR::getDVRPssCFG()
{
    int32_t value = INVALID_VALUE;
    sp<IPSSHidlInterface> mPSSSerivce = nullptr;
    for (int32_t count = 0; count < RETRY_COUNT; count++)
    {
        mPSSSerivce = IPSSHidlInterface::getService();
        if (mPSSSerivce != nullptr)
        {
            // KIND_DVR << Byte61 Bit7-Bit4 >>
            // 0000--No DVR, 0001--Internal DVR, 0010--External DVR, 0011--Internal DVR_AVP, 0100--Law DVR.
            value = mPSSSerivce->gwm_getVehicleCfg(GWM_VCfg_KindID::KIND_DVR);
            ALOGD("%s:  gwm_getVehicleCfg, kindId:%d, value:%d",
                __FUNCTION__,
                GWM_VCfg_KindID::KIND_DVR,
                value);
            if (value == INVALID_VALUE)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(INTERVAL_TIME));
            }
            else if (value == 1 || value == 3)
            {
                mDVRInternal = true;
                break;
            }
            else if (value == 4)
            {
                mDVRInternal = false;
                break;
            }
            else
            {
                ALOGE("%s:  No DVR !!!", __FUNCTION__);
                break;
            }
        }
        else
        {
            ALOGE("%s:  mPSSSerivce is null !", __FUNCTION__);
            std::this_thread::sleep_for(std::chrono::milliseconds(INTERVAL_TIME));
        }
    }
    ALOGI("%s:  isInternal:%d", __FUNCTION__, mDVRInternal);
}

// convert accessType to cameraId.
GWM_DVRCameraId DVR::accessTypeToCameraId(AccessType_DT accessType)
{
    GWM_DVRCameraId camera_id = GWM_DVRCameraId::GWM_DVR_CAMERA_ID_NULL;
    switch (accessType)
    {
        case AccessType_DT::E_FORESIGHT:
            camera_id = GWM_DVRCameraId::GWM_DVR_CAMERA_ID_FRONT;
            break;
        case AccessType_DT::E_WITHINSIGNT_OMC:
            camera_id = GWM_DVRCameraId::GWM_DVR_CAMERA_ID_INCAR;
            break;
        case AccessType_DT::E_STREAMINGMEDIA_OR_BACKSIGNT_RESERVED:
            camera_id = GWM_DVRCameraId::GWM_DVR_StreamingMedia_or_BackSignt_reserved;
            break;
        case AccessType_DT::E_360SURROUNDVIEW:
            camera_id = GWM_DVRCameraId::GWM_DVR_CAMERA_ID_AVM;
            break;
        case AccessType_DT::E_MULTICHANNEL:
            camera_id = GWM_DVRCameraId::GWM_DVR_MultiChannel;
            break;
        case AccessType_DT::E_WITHINSIGNT_DMC:
            camera_id = GWM_DVRCameraId::GWM_DVR_WithinSignt_DMC;
            break;
        default:
            ALOGW("%s:  accessType is error !", __FUNCTION__);
            break;
    }
    ALOGD("%s:  accessType:%u, camera_id:%hu", __FUNCTION__, accessType, camera_id);
    return camera_id;
}

/**
 * @brief send msg to dvr_service for OMS stream.
 *
 * @param cameraId      camera id, such as: DVR_CAMERA_ID_INCAR(2)
 * @param operateType   operate type, such as: DVR_RECORD_OPERATE_START(1) or DVR_RECORD_OPERATE_STOP(2)
 * @param videoType     video type, such as: DVR_VIDEO_TYPE_SHORT(3) or DVR_VIDEO_TYPE_TIME_LAPSE(4) or GWM_DVR_VIDEO_TYPE_GUARDIANMODE(8)
 */
void DVR::sendMsgToQnxForOMSStream(GWM_DVRCameraId cameraId, GWM_DVRVideoOperateType operateType, GWM_DVR_VIDEO_TYPE videoType)
{
    ALOGI("%s:  cameraId[%hu], operateType[%hhu], videoType[%hhu]", __FUNCTION__, cameraId, operateType, videoType);
    if (cameraId != GWM_DVRCameraId::GWM_DVR_CAMERA_ID_INCAR)
    {
        ALOGE("%s:  params check: cameraId is error !", __FUNCTION__);
        return;
    }

    if (operateType != GWM_DVRVideoOperateType::GWM_DVR_VIDEO_OPERATE_START
        && operateType != GWM_DVRVideoOperateType::GWM_DVR_VIDEO_OPERATE_STOP)
    {
        ALOGE("%s:  params check: operateType is error !", __FUNCTION__);
        return;
    }

    if (videoType != GWM_DVR_VIDEO_TYPE::GWM_DVR_VIDEO_TYPE_SHORT
        && videoType != GWM_DVR_VIDEO_TYPE::GWM_DVR_VIDEO_TIME_LAPSE
        && videoType != GWM_DVR_VIDEO_TYPE::GWM_DVR_VIDEO_TYPE_GUARDIANMODE)
    {
        ALOGE("%s:  params check: videoType is error !", __FUNCTION__);
        return;
    }

    CameraFdb::DVRFdbDvrAndroidOperateRecord videoCmd;
    videoCmd.set_drv_id(static_cast<CameraFdb::DVRCameraID>(cameraId));
    videoCmd.set_sdcard_id(CameraFdb::DVRSDCardID::DVR_SDCARD_ID_INCAR);
    videoCmd.set_operation_type(static_cast<CameraFdb::DVRRecordOperateType>(operateType));
    videoCmd.set_video_type(static_cast<CameraFdb::DVRVideoType>(videoType));
    // build drv message
    CFdbProtoMsgBuilder builder(videoCmd);
    mCameraFdbClient->sendMessage(
        CameraFdb::FdbCameraManagerMsgId::DVR_FDB_ANDROID_OPERATE_RECORD,
        builder, true);
}

// reply ACK to DVR with someip.
bool DVR::replyDVRStatusReportACKFunc(SetResult_DT statusReportACKDt) {
    if (!checkIsReady(InterfaceType::STATUS_REPORT, __FUNCTION__))
    {
        return false;
    }

    /**
     * @brief DVRStatusReportACK comes from DVRStatusReport service of someip.
     * serviceid:0x0401
     * methodid: 0x0001
     */
    CallStatus_DT callStatus = DVRStatusReportACKFunc(statusReportACKDt);
    if (callStatus != CallStatus_DT::SUCCESS)
    {
        ALOGW("%s:  DVRStatusReportACKFunc, callStatus:%d !", __FUNCTION__, static_cast<CallStatus_DT>(callStatus));
        return false;
    }
    return true;
}

GWM_Status DVR::queryTFCardInfo(TFCardStatus_DT &tfCardStatusOut, TFCardCapacity_DT &tfCardCapacityOut)
{
    GWM_Status status = GWM_Status::GWM_ERROR;
    if (checkIsReady(InterfaceType::FILE_OPERATION, __FUNCTION__))
    {
        TFCardOptionList list;
        memset(&list, 0, sizeof(list));
        TFCardOptionList_DT dt;
        memset(&dt, 0, sizeof(dt));
        dt.tfCardOptionDt = TFCardOption_DT::E_TFCARD1;
        list.dynamicList.push_back(dt);
        TFCardInfoListOut out;
        memset(&out, 0, sizeof(out));
        /**
         * @brief TFCardInfoQuery comes from DVRFileOperation service of someip.
         * serviceid:0x0402
         * methodid: 0x0006
         */
        CallStatus_DT callStatus = TFCardInfoQueryFunc(E_GET_ARRAY_INFO, list, out);
        if (callStatus == CallStatus_DT::SUCCESS
            && out.dynamicList.size() != 0)
        {
            status = GWM_Status::GWM_OK;
            tfCardStatusOut = out.dynamicList[0].tfCardStatusDt;
            tfCardCapacityOut = out.dynamicList[0].tfCardCapacityDt;
        }
        else
        {
            status = GWM_Status::GWM_ERROR;
            tfCardStatusOut = mTfCard1Status;
        }
        ALOGI("%s:  TFCardInfoQueryFunc callStatus:%d, status:%d, TFCardInfoListSize:%lu, tfCardStatusOut:%d, totalCapacity:%u, remainingCapacity:%u !",
            __FUNCTION__,
            callStatus,
            status,
            out.dynamicList.size(),
            tfCardStatusOut,
            tfCardCapacityOut.totalCapacity,
            tfCardCapacityOut.remainingCapacity);
    }
    return status;
}

GWM_Status DVR::queryTFCardExportCapacity(TotalExportCapacity &totalExportCapacity, FreeExportCapacity &freeExportCapacity, CallStatus_DT &callStatus)
{
    GWM_Status status = GWM_Status::GWM_ERROR;
    if (checkIsReady(InterfaceType::STATUS_REPORT, __FUNCTION__))
    {
        /**
         * @brief TFCardExportCapacityQuery comes from DVRStatusReport service of someip.
         * serviceid:0x0401
         * methodid: 0x0008
         */
        callStatus = TFCardExportCapacityQueryFuc(E_TFCARD1, totalExportCapacity, freeExportCapacity);
        if (callStatus == CallStatus_DT::SUCCESS)
        {
            status = GWM_Status::GWM_OK;
        }
        else
        {
            status = GWM_Status::GWM_ERROR;
        }
        ALOGI("%s:  TFCardExportCapacityQueryFuc callStatus:%d, status:%d, totalExportCapacity:%u, freeExportCapacity:%u !",
            __FUNCTION__,
            callStatus,
            status,
            totalExportCapacity,
            freeExportCapacity);
    }
    return status;
}

GWM_Status DVR::queryDVRSystemStatus(DVRSystemStatusOut &systemStatusOut, CallStatus_DT &dvrSystemcallStatus)
{
    GWM_Status status = GWM_Status::GWM_ERROR;
    if (checkIsReady(InterfaceType::STATUS_REPORT, __FUNCTION__))
    {
        /**
         * @brief DVRSystemStatusReportFunc comes from DVRStatusReport service of someip.
         * serviceid:0x0401
         * methodid: 0x1001
         */
        dvrSystemcallStatus = DVRSystemStatusReportFunc(systemStatusOut);
        if (dvrSystemcallStatus == CallStatus_DT::SUCCESS)
        {
            status = GWM_Status::GWM_OK;
        }
        else
        {
            status = GWM_Status::GWM_ERROR;
        }
        ALOGI("%s:  DVRSystemStatusReportFunc dvrSystemcallStatus:%d, status:%d, DVRSystemStatusOut:%d",
            __FUNCTION__,
            dvrSystemcallStatus,
            status,
            systemStatusOut.dvrSystemStatusDt);
    }
    return status;
}

GWM_Status DVR::queryDVRSensorStatus(DVRSensorStatusStruct_DT &sensorStatusOut, CallStatus_DT &dvrSensorcallStatus)
{
    GWM_Status status = GWM_Status::GWM_ERROR;
    if (checkIsReady(InterfaceType::STATUS_REPORT, __FUNCTION__))
    {
        /**
         * @brief DVRSensorStatusReportFunc comes from DVRStatusReport service of someip.
         * serviceid:0x0401
         * methodid: 0x1002
         */
        dvrSensorcallStatus = DVRSensorStatusReportFunc(sensorStatusOut);
        if (dvrSensorcallStatus == CallStatus_DT::SUCCESS)
        {
            status = GWM_Status::GWM_OK;
        }
        else
        {
            status = GWM_Status::GWM_ERROR;
        }
        ALOGI("%s:  DVRSensorStatusReportFunc dvrSensorcallStatus:%d, status:%d, accessTypeDt:%d, dvrSensorStatusDt:%d",
            __FUNCTION__,
            dvrSensorcallStatus,
            status,
            sensorStatusOut.accessTypeDt,
            sensorStatusOut.dvrSensorStatusDt);
    }
    return status;
}

bool DVR::checkCallbackIsNull(android::sp<IDVRCallback> callback)
{
    if (callback == nullptr)
    {
        ALOGW("%s:  callback is null!", __FUNCTION__);
	return true;
    }
    else
    {
        return false;
    }
}

} // namespace implementation
}  // namespace V1_0
}  // namespace camera
}  // namespace hardware
}  // namespace gwm
}  // namespace vendor
