/*************************************************************************
* Copyright (C) 2022 GWM Automotive Inc.
*
* The copyright notice above does not evidence any actual
* or intended publication of such source code.
* The code contains GWM Confidential Proprietary Information.
*************************************************************************/

/**************************************************************************
 * @file CPUMonitor.cpp
 * CPUMonitor
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

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "HealthMain_CPUMonitor"

#include "CPUMonitor.h"

#include <android-base/file.h>
#include <android-base/logging.h>
#include <android-base/properties.h>
#include <android-base/stringprintf.h>
#include <android-base/strings.h>
#include <log/log.h>
#include <string.h>
#include <cutils/properties.h>

namespace vendor {
namespace gwm {
namespace hardware {
namespace health {
namespace V1_0 {
namespace implementation {

  CPUMonitor::CPUMonitor()
  : MonitorBase() {}

  CPUMonitor::~CPUMonitor() {}

  void CPUMonitor::dumpResource() {
    if (resMonitorEnable()) {
    std::string marker = "CPU usage from";
    std::string cpuUsage;
    cpuUsage = readCpuUsage(marker);
    ALOGI("###CpuUsage###:");
    line_print_cpu(cpuUsage);
    }
  }

  std::string CPUMonitor::readCpuUsage(const std::string& marker) {
    static const std::string dumpsys_cmd = "/system/bin/dumpsys";
    static const std::string cpuinfo_args = "cpuinfo";
    std::string content = readCommand({dumpsys_cmd, cpuinfo_args});
    size_t pos = content.find(marker);
    if (pos == std::string::npos) {
        return "";
    }
    return content;
  }

  void CPUMonitor::line_print_cpu(const std::string& str) {
    std::stringstream ss(str);
    std::string line;
    int32_t line_num = 0;
    int32_t line_header_max = 12; // 1 Load + 1 Title + 10 Top
    static const std::string line_footer = "TOTAL:";
    while (std::getline(ss, line, '\n')) {
      line_num++;
      if (line_num <= line_header_max) {
        ALOGI("%s", line.c_str());
        continue;
      }
      if (line.find(line_footer) != std::string::npos) {
        ALOGI("%s", line.c_str());
      }
    }
    ss.clear();
    ss.str("");
  }

}  // namespace implementation
}  // namespace V1_0
}  // namespace health
}  // namespace hardware
}  // namespace gwm
}  // namespace vendor
