/*************************************************************************
 * Copyright (C) 2023 GWM Automotive Inc.
 *
 * The copyright notice above does not evidence any actual
 * or intended publication of such source code.
 * The code contains GWM Confidential Proprietary Information.
 *************************************************************************/
/**************************************************************************
 * @file DVRMessageHandler.h
 * DVRMessageHandler
 *
 * @project     v3.5
 * @subsystem
 * @version     0.1
 * @author
 * @date        2022-9-28

 Module-History:
 Date(dd.mm.year)| Author            | Reason
 The latest entry at the head of the history list.
 16/6/2023         Zhao Ying           Init version

***************************************************************************/
#ifndef VENDOR_GWM_HARDWARE_DVR_V1_0_DVRMESSAGEHANDLER_H
#define VENDOR_GWM_HARDWARE_DVR_V1_0_DVRMESSAGEHANDLER_H

#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <log/log.h>
#include <utils/RefBase.h>
#include "DVR.h"
#include "DVRSomeipProxy.h"

#undef LOG_TAG
#define LOG_TAG "CameraHAL_DVRMessageHandler"

namespace vendor {
namespace gwm {
namespace hardware {
namespace camera {
namespace V1_0 {
namespace implementation {

class DVRSomeipProxy;
class DVRMessageHandler : public android::RefBase
{
public:
    DVRMessageHandler(android::sp<DVR> dvr)
    {
        mDVRSomeipProxy = new DVRSomeipProxy(dvr);
    }

    virtual ~DVRMessageHandler()
    {
        mIsActive = false;
    }

    void setDVRCallback(const std::vector<android::sp<IDVRCallback>>& callbackList)
    {
        if (mDVRSomeipProxy == nullptr)
        {
            ALOGE("%s:  mDVRSomeipProxy is null !", __FUNCTION__);
            return;
        }
        mDVRSomeipProxy->setDVRCallback(callbackList);
    }

    void startWorkThread()
    {
        ALOGI("%s:  ", __FUNCTION__);
        mIsActive = true;
        mWorkThread = std::thread(&DVRMessageHandler::loop, this);
    }

    void stopWorkThread()
    {
        ALOGI("%s:  ", __FUNCTION__);
        mIsActive = false;
        mStopRequested = true;
        mCond.notify_one();
        if (mWorkThread.joinable())
        {
            mWorkThread.join();
        }
    }

    bool isDeactive()
    {
        return !mIsActive;
    }

    bool sendDVRMessage(DVRMessageId msgId)
    {
        if (msgId < START_PREVIEW
            || msgId > FILELISTINCLUDEDATE_REQUEST)
        {
            ALOGW("%s:  msgId is invalid !", __FUNCTION__);
            return false;
        }

        std::unique_lock<std::mutex> lock(mLock);
        ALOGI("%s:  msgId:%d", __FUNCTION__, msgId);
        DVRMessage_t message;
        message.id = msgId;
        mQueue.push(message);
        mCond.notify_one();
        return true;
    }

    bool sendDVRMessage(const DVRMessage_t& message)
    {
        if (message.id < START_PREVIEW
            || message.id > FILELISTINCLUDEDATE_REQUEST)
        {
            ALOGW("%s:  message.id is invalid !", __FUNCTION__);
            return false;
        }

        std::unique_lock<std::mutex> lock(mLock);
        ALOGI("%s:  message.id:%d", __FUNCTION__, message.id);
        mQueue.push(message);
        mCond.notify_one();
        return true;
    }

private:
    android::sp<DVRSomeipProxy> mDVRSomeipProxy;
    mutable std::mutex mLock;
    std::thread mWorkThread;
    std::queue<DVRMessage_t> mQueue;
    std::condition_variable mCond;
    std::atomic_bool mStopRequested { false };
    std::atomic_bool mIsActive { false };

    void loop()
    {
        while (!mStopRequested)
        {
            DVRMessage_t msg = popDVRMessage();
            if (msg.id >= START_PREVIEW && msg.id <= FILELISTINCLUDEDATE_REQUEST) {
                handleMessage(msg);
                // mCond.wait_for(lock, std::chrono::milliseconds(50));
            }
        }
    }

    DVRMessage_t popDVRMessage()
    {
        std::unique_lock<std::mutex> lock(mLock);
        ALOGI("%s:  mQueue.size:%lu", __FUNCTION__, mQueue.size());
        DVRMessage_t message;
        message.id = static_cast<DVRMessageId>(INVALID_VALUE);
        if (mQueue.empty())
        {
            mCond.wait(lock, [this] { return !mQueue.empty(); });
        } else {
            message = mQueue.front();
            mQueue.pop();
        }
        return message;
    }

    void handleMessage(DVRMessage_t message)
    {
        ALOGI("%s:  message[id:%d name:%s]", __FUNCTION__, message.id, convertMsgIdToString(message.id).c_str());
        if (mDVRSomeipProxy == nullptr)
        {
            ALOGE("%s:  mDVRSomeipProxy is null !", __FUNCTION__);
            return;
        }

        switch (message.id) {
            case DVRMessageId::START_PREVIEW:
            {
                mDVRSomeipProxy->startPreview(message.cameraId);
            }
            break;
            case DVRMessageId::STOP_PREVIEW:
            {
                mDVRSomeipProxy->stopPreview(message.cameraId);
            }
            break;
            case DVRMessageId::START_RECORD:
            {
                mDVRSomeipProxy->startRecord(message.cameraId, message.videoType);
            }
            break;
            case DVRMessageId::STOP_RECORD:
            {
                mDVRSomeipProxy->stopRecord(message.cameraId, message.videoType);
            }
            break;
            case DVRMessageId::START_CAPTURE:
            {
                mDVRSomeipProxy->startCapture(message.cameraId, message.videoType);
            }
            break;
            case DVRMessageId::START_LAPSEVIDEO:
            {
                mDVRSomeipProxy->startLapseVideo(message.cameraId,
                                    message.timeLapseVideoInteval,
                                    message.totalFrameNumber,
                                    message.playFrameNumber);
            }
            break;
            case DVRMessageId::STOP_LAPSEVIDEO:
            {
                mDVRSomeipProxy->stopLapseVideo(message.cameraId);
            }
            break;
            case DVRMessageId::FORMAT_TFCARD:
            {
                mDVRSomeipProxy->formatTFCard(message.tfCardId);
            }
            break;
            case DVRMessageId::QUERY_SYSTEMSTATUS:
            {
                mDVRSomeipProxy->querySystemInfoFromExtDVR();
            }
            break;
            case DVRMessageId::GET_PARAM:
            {
                mDVRSomeipProxy->getParam();
            }
            break;
            case DVRMessageId::SET_PARAM:
            {
                mDVRSomeipProxy->setParam(message.param);
            }
            break;
            case DVRMessageId::RESET_FACTORY:
            {
                mDVRSomeipProxy->resetFactory();
            }
            break;
            case DVRMessageId::FILELIST_REQUEST:
            {
                mDVRSomeipProxy->fileListRequest(message.fileListREQ);
            }
            break;
            case DVRMessageId::DELETE_FILELIST:
            {
                mDVRSomeipProxy->deleteFileList(message.file_path_url);
            }
            break;
            case DVRMessageId::ALLFILE_DELETE:
            {
                mDVRSomeipProxy->allFiledelete(message.cameraId, message.fileType);
            }
            break;
            case DVRMessageId::ASYNC_ALLFILE_DELETE:
            {
                mDVRSomeipProxy->asyncAllFiledelete(message.cameraId, message.fileType);
            }
            break;
            case DVRMessageId::STOP_ASYNC_ALLFILE_DELETE:
            {
                mDVRSomeipProxy->stopAsyncAllFiledelete(message.cameraId);
            }
            break;
            case DVRMessageId::EXPORT_FILELIST:
            {
                mDVRSomeipProxy->exportFileList(message.exportType, message.file_path_url);
            }
            break;
            case DVRMessageId::ALLFILE_EXPORT:
            {
                mDVRSomeipProxy->allFileExport(message.exportType,
                    message.cameraId,
                    message.fileType);
            }
            break;
            case DVRMessageId::CANCEL_FILESEXPORT:
            {
                mDVRSomeipProxy->cancelFilesExport(message.cameraId);
            }
            break;
            case DVRMessageId::EXPORT_FILECAPACITY:
            {
                mDVRSomeipProxy->exportFileCapacity(message.file_path_url);
            }
            break;
            case DVRMessageId::SELECT_ALLFILECAPACITY:
            {
                mDVRSomeipProxy->selectAllFileCapacity(message.cameraId, message.fileType);
            }
            break;
            case DVRMessageId::EMMCSTATUS_REQUEST:
            {
                mDVRSomeipProxy->emmcStatusRequest();
            }
            break;
            case DVRMessageId::TFCARDSTATUS_REQUEST:
            {
                mDVRSomeipProxy->tfCardStatusRequest(message.tfCardId);
            }
            break;
            case DVRMessageId::TFCARDCAPACITY_REQUEST:
            {
                mDVRSomeipProxy->tfCardCapacityRequest(message.tfCardId);
            }
            break;
            case DVRMessageId::RECORDSTATE_REQUEST:
            {
                mDVRSomeipProxy->recordStateRequest(message.cameraId);
            }
            break;
            case DVRMessageId::OMCCAPTURE_REQUEST:
            {
                mDVRSomeipProxy->dvrCaptureRequest(GWM_DVRCameraId::GWM_DVR_CAMERA_ID_INCAR,
                    message.eventTime,
                    message.eventType,
                    message.fileId,
                    message.fileSize,
                    true);
            }
            break;
            case DVRMessageId::OMCCAPTURETRANSFER_REQUEST:
            {
                mDVRSomeipProxy->dvrCaptureTransferRequest(GWM_DVRCameraId::GWM_DVR_CAMERA_ID_INCAR,
                    message.eventTime,
                    message.eventType,
                    message.fileId,
                    message.fileSize,
                    message.filePath,
                    true);
            }
            break;
            case DVRMessageId::DVRCAPTURE_REQUEST:
            {
                mDVRSomeipProxy->dvrCaptureRequest(message.cameraId,
                    message.eventTime,
                    message.eventType,
                    message.fileId,
                    message.fileSize,
                    false);
            }
            break;
            case DVRMessageId::DVRCAPTURETRANSFER_REQUEST:
            {
                mDVRSomeipProxy->dvrCaptureTransferRequest(message.cameraId,
                    message.eventTime,
                    message.eventType,
                    message.fileId,
                    message.fileSize,
                    message.filePath,
                    false);
            }
            break;
            case DVRMessageId::DVRFILECAPACITYINFO_REQUEST:
            {
                mDVRSomeipProxy->dvrFileCapacityInfoReq(message.fileCapacityType, message.fileTypeList);
            }
            break;
            case DVRMessageId::FILELISTINCLUDEDATE_REQUEST:
            {
                mDVRSomeipProxy->fileListIncludeDateReq(message.fileType,
                    message.cameraId,
                    message.fileNumber,
                    message.fileName);
            }
            break;
            default:
            break;
        }
    }

    void clear(std::queue<DVRMessage_t>& q)
    {
        std::queue<DVRMessage_t> empty;
        swap(empty, q);
    }

    std::string convertMsgIdToString(DVRMessageId msgId)
    {
        std::string message_name = "";
        switch (msgId)
        {
            case DVRMessageId::START_PREVIEW:
                message_name = "START_PREVIEW";
                break;
            case DVRMessageId::STOP_PREVIEW:
                message_name = "STOP_PREVIEW";
                break;
            case DVRMessageId::START_RECORD:
                message_name = "START_RECORD";
                break;
            case DVRMessageId::STOP_RECORD:
                message_name = "STOP_RECORD";
                break;
            case DVRMessageId::START_CAPTURE:
                message_name = "START_CAPTURE";
                break;
            case DVRMessageId::START_LAPSEVIDEO:
                message_name = "START_LAPSEVIDEO";
                break;
            case DVRMessageId::STOP_LAPSEVIDEO:
                message_name = "STOP_LAPSEVIDEO";
                break;
            case DVRMessageId::FORMAT_TFCARD:
                message_name = "FORMAT_TFCARD";
                break;
            case DVRMessageId::QUERY_SYSTEMSTATUS:
                message_name = "QUERY_SYSTEMSTATUS";
                break;
            case DVRMessageId::GET_PARAM:
                message_name = "GET_PARAM";
                break;
            case DVRMessageId::SET_PARAM:
                message_name = "SET_PARAM";
                break;
            case DVRMessageId::RESET_FACTORY:
                message_name = "RESET_FACTORY";
                break;
            case DVRMessageId::FILELIST_REQUEST:
                message_name = "FILELIST_REQUEST";
                break;
            case DVRMessageId::DELETE_FILELIST:
                message_name = "DELETE_FILELIST";
                break;
            case DVRMessageId::ALLFILE_DELETE:
                message_name = "ALLFILE_DELETE";
                break;
            case DVRMessageId::ASYNC_ALLFILE_DELETE:
                message_name = "ASYNC_ALLFILE_DELETE";
                break;
            case DVRMessageId::STOP_ASYNC_ALLFILE_DELETE:
                message_name = "STOP_ASYNC_ALLFILE_DELETE";
                break;
            case DVRMessageId::EXPORT_FILELIST:
                message_name = "EXPORT_FILELIST";
                break;
            case DVRMessageId::ALLFILE_EXPORT:
                message_name = "ALLFILE_EXPORT";
                break;
            case DVRMessageId::CANCEL_FILESEXPORT:
                message_name = "CANCEL_FILESEXPORT";
                break;
            case DVRMessageId::EXPORT_FILECAPACITY:
                message_name = "EXPORT_FILECAPACITY";
                break;
            case DVRMessageId::SELECT_ALLFILECAPACITY:
                message_name = "SELECT_ALLFILECAPACITY";
                break;
            case DVRMessageId::EMMCSTATUS_REQUEST:
                message_name = "EMMCSTATUS_REQUEST";
                break;
            case DVRMessageId::TFCARDSTATUS_REQUEST:
                message_name = "TFCARDSTATUS_REQUEST";
                break;
            case DVRMessageId::TFCARDCAPACITY_REQUEST:
                message_name = "TFCARDCAPACITY_REQUEST";
                break;
            case DVRMessageId::RECORDSTATE_REQUEST:
                message_name = "RECORDSTATE_REQUEST";
                break;
            case DVRMessageId::OMCCAPTURE_REQUEST:
                message_name = "OMCCAPTURE_REQUEST";
                break;
            case DVRMessageId::OMCCAPTURETRANSFER_REQUEST:
                message_name = "OMCCAPTURETRANSFER_REQUEST";
                break;
            case DVRMessageId::DVRCAPTURE_REQUEST:
                message_name = "DVRCAPTURE_REQUEST";
                break;
            case DVRMessageId::DVRCAPTURETRANSFER_REQUEST:
                message_name = "DVRCAPTURETRANSFER_REQUEST";
                break;
            case DVRMessageId::DVRFILECAPACITYINFO_REQUEST:
                message_name = "DVRFILECAPACITYINFO_REQUEST";
                break;
            case DVRMessageId::FILELISTINCLUDEDATE_REQUEST:
                message_name = "FILELISTINCLUDEDATE_REQUEST";
                break;
            default:
                ALOGW("%s:  msgId:%d is invalid !", __FUNCTION__, msgId);
                break;
        }
        return message_name;
    }

};

}
}
}
}
}
}
#endif