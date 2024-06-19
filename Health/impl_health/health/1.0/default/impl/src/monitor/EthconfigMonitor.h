/*************************************************************************
 * Copyright (C) 2022 Noch Automotive Inc.
 *
 * The copyright notice above does not evidence any actual
 * or intended publication of such source code.
 * The code contains Noch Confidential Proprietary Information.
 *************************************************************************/
/**************************************************************************
 * @file EthconfigMonitor.h
 * EthconfigMonitor
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
#ifndef vendor_gwm_hardware_health_V1_0_EthconfigMonitor_H_
#define vendor_gwm_hardware_health_V1_0_EthconfigMonitor_H_

#include <log/log.h>
#include "MonitorBase.h"

namespace vendor {
namespace gwm {
namespace hardware {
namespace health {
namespace V1_0 {
namespace implementation {

class EthconfigMonitor : public MonitorBase {
 public:
  EthconfigMonitor();
  ~EthconfigMonitor();

  virtual void dumpResource() override;

 private:
  bool monitorEthconfigEnable();
  bool ethconfigReady();
  void monitorEthconfig();

};
}  // namespace implementation
}  // namespace V1_0
}  // namespace health
}  // namespace hardware
}  // namespace gwm
}  // namespace vendor
#endif
