/*************************************************************************
 * Copyright (C) 2020-2023 GWM Automotive Inc.
 *
 * The copyright notice above does not evidence any actual
 * or intended publication of such source code.
 * The code contains GWM Confidential Proprietary Information.
 *************************************************************************/
/**************************************************************************
 * @file DVRConnectionTimer.h
 * DVRConnectionTimer
 *
 * @project     v3.5
 * @subsystem
 * @version     0.1
 * @author
 * @date        2022-9-28

 Module-History:
 Date(dd.mm.year)| Author            | Reason
 The latest entry at the head of the history list.
 9/28/2022         QIAN KANG           Init version

***************************************************************************/
#ifndef VENDOR_GWM_HARDWARE_DVR_V1_0_DVRCONNECTIONTIMER_H
#define VENDOR_GWM_HARDWARE_DVR_V1_0_DVRCONNECTIONTIMER_H

#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <log/log.h>
#include <utils/RefBase.h>
#include "DVR.h"

#undef LOG_TAG
#define LOG_TAG "CameraHAL_DVRConnectionTimer"

namespace vendor {
namespace gwm {
namespace hardware {
namespace camera {
namespace V1_0 {
namespace implementation {

class DVRConnectionTimer : public android::RefBase{
public:
    DVRConnectionTimer(android::sp<DVR> dvr)
    {
        mDVR = dvr;
    }

    virtual ~DVRConnectionTimer() {
        mIsActive = false;
    }

    void startTimer() {
        ALOGI("%s:  ", __func__);
        mIsActive = true;
        mTimerThread = std::thread(&DVRConnectionTimer::loop, this);
    }

    void stopTimer() {
        ALOGI("%s:  ", __func__);
        mIsActive = false;
        mStopRequested = true;
        mCond.notify_one();
        if (mTimerThread.joinable()) {
            mTimerThread.join();
        }
    }

    bool isDeactive() {
        return !mIsActive;
    }

private:
    void loop() {
        int32_t retryCount = 0;
        bool hasNotifyException = false;
        while (!mStopRequested) {
            std::unique_lock<std::mutex> g(mLock);
            if(isFirst) {
                mCond.wait_for(g, std::chrono::milliseconds(25 * 1000));    // wait 25s
                isFirst = false;
            } else {
                mCond.wait_for(g, std::chrono::milliseconds(STATUS_REPORT_INTERNAL));   // wait 1s
            }

            if(mDVR.get()) {
                bool dvrStatus = mDVR->checkIsReady(InterfaceType::STATUS_REPORT, "DVR_TIMER_CHECK");
                ALOGI("%s:  DVR Timer called dvrStatus:%d", __func__, dvrStatus);
                if (!dvrStatus) {
                    retryCount++;
                    if (retryCount >= STATUS_REPORT_LMT && !hasNotifyException) {
                        retryCount = 0;
                        mDVR->notifyDVRConnectStatus(false);
                        hasNotifyException = true;
                    }
                } else {
                    retryCount = 0;
                    if (mLastDVRStatus != dvrStatus) {
                        mDVR->notifyDVRConnectStatus(true);
                        hasNotifyException = false;
                    }
                }
                mLastDVRStatus = dvrStatus;
            }
        }
    }

private:
    android::sp<DVR> mDVR;
    using MuxGuard = std::lock_guard<std::mutex>;
    mutable std::mutex mLock;
    std::thread mTimerThread;
    std::condition_variable mCond;
    std::atomic_bool mStopRequested { false };
    std::atomic_bool mIsActive { false };
    std::atomic_bool mLastDVRStatus {true};
    std::atomic_bool isFirst {true};
};

}
}
}
}
}
}
#endif