/*************************************************************************
 * Copyright (C) 2022 Noch Automotive Inc.
 *
 * The copyright notice above does not evidence any actual
 * or intended publication of such source code.
 * The code contains Noch Confidential Proprietary Information.
 *************************************************************************/
/**************************************************************************
 * @file MemoryMonitor.h
 * MemoryMonitor
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
#ifndef vendor_gwm_hardware_health_V1_0_MemoryMonitor_H_
#define vendor_gwm_hardware_health_V1_0_MemoryMonitor_H_

#include <log/log.h>
#include "MonitorBase.h"

namespace vendor {
namespace gwm {
namespace hardware {
namespace health {
namespace V1_0 {
namespace implementation {

class MemoryMonitor : public MonitorBase {
 public:
  MemoryMonitor();
  ~MemoryMonitor();

  virtual void dumpResource() override;

 private:
  void line_print_mem(const std::string& printString);
  std::string readMemoryUsage(const std::string& marker);
  std::string readMemoryByPs();
  std::string readMeminfo();
  std::string readDmaUsage();
  std::string readGpuMemoryInfo();
  std::string readDmaBuf();
  void dumpDma(const std::string& str);
  void changeLogPermission(const std::string& str);
  std::string getLogDirAndCreateDir();
  bool createDirIfNotExist(const std::string& logDir);
  std::string getFileName(const std::string& type);
  bool isSupportDumpsys();

};
}  // namespace implementation
}  // namespace V1_0
}  // namespace health
}  // namespace hardware
}  // namespace gwm
}  // namespace vendor
#endif
