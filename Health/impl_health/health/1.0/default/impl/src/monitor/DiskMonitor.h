/*************************************************************************
 * Copyright (C) 2022 Noch Automotive Inc.
 *
 * The copyright notice above does not evidence any actual
 * or intended publication of such source code.
 * The code contains Noch Confidential Proprietary Information.
 *************************************************************************/
/**************************************************************************
 * @file DiskMonitor.h
 * DiskMonitor
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
#ifndef vendor_gwm_hardware_health_V1_0_DiskMonitor_H_
#define vendor_gwm_hardware_health_V1_0_DiskMonitor_H_

#include <log/log.h>
#include "MonitorBase.h"

namespace vendor {
namespace gwm {
namespace hardware {
namespace health {
namespace V1_0 {
namespace implementation {

class DiskMonitor : public MonitorBase {
 public:
  DiskMonitor();
  ~DiskMonitor();

  virtual void dumpResource() override;

 private:
  std::string readDiskUsage(const std::string& marker);
  std::string readDiskUsageTop(bool top);
  bool createPileFile(std::string filePath,std::string filePathName,int32_t fileSize);
  void monitorDiskReserve();


};
}  // namespace implementation
}  // namespace V1_0
}  // namespace health
}  // namespace hardware
}  // namespace gwm
}  // namespace vendor
#endif
