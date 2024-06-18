/*************************************************************************
* Copyright (C) 2020-2021 GWM Automotive Inc.
*
* The copyright notice above does not evidence any actual
* or intended publication of such source code.
* The code contains GWM Confidential Proprietary Information.
*************************************************************************/
/**************************************************************************
 * @file camera gtest cpp
 *
 *
 * @project     v3.5
 * @subsystem
 * @version     0.1
 * @author
 * @date        2020-12-2

 Module-History:
 Date(dd.mm.year)| Author            | Reason
 The latest entry at the head of the history list.
 2/12/2020         Hong Jiu Jin   Init version

***************************************************************************/
#include <functional>
#include <iostream>
#include <gtest/gtest.h>
#include <log/log.h>
#include <memory>
#include <vector>
#include <utils/RefBase.h>
#include <Camera.h>

#undef LOG_TAG
#define LOG_TAG "CameraTest"

namespace vendor {
namespace gwm {
namespace hardware {
namespace camera {
namespace V1_0 {
namespace implementation {

using namespace std;
using namespace android;
using namespace android::hardware;

class CameraTest : public ::testing::Test {
 public:
  CameraTest() { mCamera = new Camera(); }

  virtual ~CameraTest() {
    ALOGI("%s called", __func__);
    delete mCamera;
  }

  Return<sp<::vendor::gwm::hardware::camera::V1_0::IDVR>>
  gwm_getDVRInterface() {
    return mCamera->gwm_getDVRInterface();
  }

 public:
  Camera* mCamera;
};

TEST_F(CameraTest, gwm_getDVRInterface) {
  sp<::vendor::gwm::hardware::camera::V1_0::IDVR> dvr = gwm_getDVRInterface();
  ASSERT_NE(dvr, nullptr);
}
}
}
}
}
}
}
