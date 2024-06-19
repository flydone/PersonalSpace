/*************************************************************************
* Copyright (C) 2020-2021 GWM Automotive Inc.
*
* The copyright notice above does not evidence any actual
* or intended publication of such source code.
* The code contains GWM Confidential Proprietary Information.
*************************************************************************/

/**************************************************************************
 * @file FdbusClientBase.h
 * FdbusClientBase
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
#ifndef vendor_gwm_hardware_health_V1_0_impl_FdbusClientBase_H_
#define vendor_gwm_hardware_health_V1_0_impl_FdbusClientBase_H_

#include <common_base/fdbus.h>
#include <utils/RefBase.h>

#include <mutex>
#include <string>

typedef const char * cstr8_t;

namespace vendor {
namespace gwm {
namespace hardware {
namespace health {
namespace V1_0 {
namespace implementation {

using namespace std;

class FdbusClientBase : public CBaseClient, public android::RefBase {
 public:
  FdbusClientBase(const string& url, const string& name, CBaseWorker* worker)
      : CBaseClient(name.c_str(), worker), mOnline(false), mUrl(url) {}

  virtual ~FdbusClientBase() {}

  virtual bool isOnline() {
    MuxGuard g(mLock);
    return mOnline;
  }

  virtual void setOnline(bool online) {
    MuxGuard g(mLock);
    mOnline = online;
  }

  virtual string getUrl() {
    return mUrl;
  }

 protected:
  bool mOnline;
  string mUrl;
  using MuxGuard = std::lock_guard<std::mutex>;
  mutable std::mutex mLock;
};
}  // namespace implementation
}  // namespace V1_0
}  // namespace health
}  // namespace hardware
}  // namespace gwm
}  // namespace vendor
#endif
