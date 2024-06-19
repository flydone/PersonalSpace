/*************************************************************************
 * Copyright (C) 2022 Noch Automotive Inc.
 *
 * The copyright notice above does not evidence any actual
 * or intended publication of such source code.
 * The code contains Noch Confidential Proprietary Information.
 *************************************************************************/
/**************************************************************************
 * @file MonitorBase.h
 * MonitorBase
 *
 * @project     v3.5
 * @subsystem
 * @version     0.1
 * @author
 * @date        2022-7-12

 Module-History:
 Date(dd.mm.year)| Author            | Reason
 The latest entry at the head of the history list.
 7/12/2022         tangwei           Init version

***************************************************************************/
#ifndef vendor_gwm_hardware_health_V1_0_MonitorBase_H_
#define vendor_gwm_hardware_health_V1_0_MonitorBase_H_

#include <android-base/file.h>
#include <android-base/logging.h>
#include <android-base/properties.h>
#include <android-base/stringprintf.h>
#include <android-base/strings.h>
#include <log/log.h>
#include <string.h>
#include <cutils/properties.h>
#include <utils/RefBase.h>

typedef const char* conststr_t;

namespace vendor {
namespace gwm {
namespace hardware {
namespace health {
namespace V1_0 {
namespace implementation {

class Health;
class MonitorBase : public android::RefBase {
 public:
  MonitorBase() {}
  virtual ~MonitorBase() {}

  virtual void dumpResource();

  void line_print(conststr_t tag, const std::string& str) {
    std::stringstream ss(str);
    std::string line;
    while (std::getline(ss, line, '\n')) {
       __android_log_print(ANDROID_LOG_INFO, tag, "%s", line.c_str());
    }
    ss.clear();
    ss.str("");
  }

  /* Utility functions */
  std::string readCommand(const std::vector<std::string>& commands) {
    std::string cmds_str = android::base::Join(commands, ' ');
    /* ALOGD("%s: cmds_str: %s", __func__, cmds_str.c_str());*/
    FILE* fp = popen(cmds_str.c_str(), "r");
    std::string content;
    android::base::ReadFdToString(fileno(fp), &content);
    pclose(fp);
    return content;
  }

  bool resMonitorEnable() {
    resdump = property_get_bool("vendor.nobo.health.resdump", true);
    return resdump;
  }

 protected:
  bool resdump = true;
};
}  // namespace implementation
}  // namespace V1_0
}  // namespace health
}  // namespace hardware
}  // namespace gwm
}  // namespace vendor
#endif
