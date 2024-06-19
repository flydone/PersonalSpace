/*************************************************************************
* Copyright (C) 2020-2021 GWM Automotive Inc.
*
* The copyright notice above does not evidence any actual
* or intended publication of such source code.
* The code contains GWM Confidential Proprietary Information.
*************************************************************************/

/**************************************************************************
 * @file HealthThreadWorker.h
 * HealthThreadWorker
 *
 * @project     v3.5
 * @subsystem
 * @version     0.1
 * @author
 * @date        2020-7-30

 Module-History:
 Date(dd.mm.year)| Author            | Reason
 The latest entry at the head of the history list.
 8/4/2020         Fugen Peng           Init version

***************************************************************************/
#ifndef vendor_gwm_hardware_health_HealthThreadWorker_H_
#define vendor_gwm_hardware_health_HealthThreadWorker_H_

#include <common_base/fdbus.h>
#include <log/log.h>
#include <utils/RefBase.h>

#include <chrono>
#include <condition_variable>
#include <mutex>
#include <thread>

#undef LOG_TAG
#define LOG_TAG "HealthMain_ThreadWorker"

namespace vendor {
namespace gwm {
namespace hardware {
namespace health {
namespace V1_0 {
namespace implementation {

using namespace std;
using namespace android;
class Health;

class HealthThreadWorker : public android::RefBase {
 public:
  HealthThreadWorker(Health *Health) {
    if (Health != nullptr) {
      mHealth = Health;
    }
  }

  virtual ~HealthThreadWorker() {}

  void start_LifeSignThread() {
    mLifeSignThread = std::thread(&HealthThreadWorker::HandleLifeSign, this);
  }

  void stop_LifeSignThread() {
    mStopLifeSign = true;
    mSignCond.notify_one();
    if (mLifeSignThread.joinable()) {
      mLifeSignThread.join();
    }
  }

  void start_ResMonitorThread() {
    mResMonitorThread =
        std::thread(&HealthThreadWorker::HandleResMonitor, this);
  }

  void stop_ResMonitorThread() {
    mStopResMonitor = true;
    mResCond.notify_one();
    if (mResMonitorThread.joinable()) {
      mResMonitorThread.join();
    }
  }

  void initReportInterval(uint32_t lifeSign_interval, uint32_t pid_interval) {
    mlifeSign_interval = lifeSign_interval;
    mpid_interval = pid_interval;
  }

  void initResMonInterval() {
    mresMon_interval =
        (uint32_t)property_get_int32("persist.vendor.nobo.health.resdump.interval", 60);
  }

 private:
  void HandleLifeSign() {
    while (!mStopLifeSign) {
      if (mHealth != nullptr) {
        #ifdef GWM_V4_DV
        mHealth->sendSystemReady();
        #endif
        mHealth->checkSystemStatus(mpid_interval);
        mHealth->sendHeartBeat();
        if (mHealth->getSystemStatus() == GWM_HealthSystemStatus::DEALIVE) {
          mHealth->sendRestartReq(GWM_HealthSystemStatus::DEALIVE);
        }
        std::unique_lock<std::mutex> g(mSignLock);
        mSignCond.wait_for(g, std::chrono::seconds(mlifeSign_interval));
      }
    }
  }

  void HandleResMonitor() {
    while (!mStopResMonitor) {
      if (mHealth != nullptr) {
        initResMonInterval();
        mHealth->ResMonitor();
        std::unique_lock<std::mutex> g(mResLock);
        mResCond.wait_for(g, std::chrono::seconds(mresMon_interval));
      }
    }
  }

 private:
  mutable std::mutex mSignLock;
  mutable std::mutex mResLock;
  std::thread mLifeSignThread;
  std::thread mResMonitorThread;
  std::condition_variable mSignCond;
  std::condition_variable mResCond;
  std::atomic_bool mStopLifeSign{false};
  std::atomic_bool mStopResMonitor{false};
  uint32_t mpid_interval = 1;
  uint32_t mlifeSign_interval = 1;
  uint32_t mresMon_interval = 30;
  Health *mHealth;
};
}  // namespace implementation
}  // namespace V1_0
}  // namespace health
}  // namespace hardware
}  // namespace gwm
}  // namespace vendor
#endif
