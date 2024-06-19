/*************************************************************************
 * Copyright (C) 2022 Noch Automotive Inc.
 *
 * The copyright notice above does not evidence any actual
 * or intended publication of such source code.
 * The code contains Noch Confidential Proprietary Information.
 *************************************************************************/
/**************************************************************************
 * @file IptableMonitor.h
 * IptableMonitor
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
#ifndef vendor_gwm_hardware_health_V1_0_IptableMonitor_H_
#define vendor_gwm_hardware_health_V1_0_IptableMonitor_H_

#include <log/log.h>
#include "MonitorBase.h"

namespace vendor {
namespace gwm {
namespace hardware {
namespace health {
namespace V1_0 {
namespace implementation {

class IptableMonitor : public MonitorBase {
 public:
  IptableMonitor();
  ~IptableMonitor();

  virtual void dumpResource() override;

 private:
  bool monitorIptableEnable();
  bool iptableReady();
  bool iptableDebug();
  bool iptableCUXReady();
  void monitorIptable();
  void monitorCUXIptable();
  std::string readIptables(const std::string& marker);
  int32_t getIptableLine(const std::string& str, const std::string& marker);
  std::vector<std::string> stringSplit(const std::string& str, char delim);

};
}  // namespace implementation
}  // namespace V1_0
}  // namespace health
}  // namespace hardware
}  // namespace gwm
}  // namespace vendor
#endif
