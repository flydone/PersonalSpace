/*************************************************************************
* Copyright (C) 2022 GWM Automotive Inc.
*
* The copyright notice above does not evidence any actual
* or intended publication of such source code.
* The code contains GWM Confidential Proprietary Information.
*************************************************************************/

/**************************************************************************
 * @file EthconfigMonitor.cpp
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

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "HealthMain_EthconfigMonitor"

#include "EthconfigMonitor.h"

#include <android-base/file.h>
#include <android-base/logging.h>
#include <android-base/properties.h>
#include <android-base/stringprintf.h>
#include <android-base/strings.h>
#include <log/log.h>
#include <string.h>
#include <cutils/properties.h>
#include <regex>


namespace vendor {
namespace gwm {
namespace hardware {
namespace health {
namespace V1_0 {
namespace implementation {

  static bool ethconfigdump = true;
  static bool mEthconfigReady = false;

  EthconfigMonitor::EthconfigMonitor()
  : MonitorBase() {}

  EthconfigMonitor::~EthconfigMonitor() {}

  void EthconfigMonitor::dumpResource() {
    if (monitorEthconfigEnable()) {
        if(ethconfigReady()) {
            monitorEthconfig();
        }
    }
  }

  bool EthconfigMonitor::monitorEthconfigEnable() {
    return ethconfigdump;
  }

  bool EthconfigMonitor::ethconfigReady() {
    mEthconfigReady = property_get_bool("vendor.nobo.eth.arp", false);
    return mEthconfigReady;
  }

  /* check /vendor/bin/eth_config.sh arp */
  void EthconfigMonitor::monitorEthconfig() {
    ALOGI("###MonitorEthconfig###:");
    char arpProperty[PROPERTY_VALUE_MAX] = {};
    property_get("vendor.nobo.arp.check", arpProperty, "172.16.13.97");
    static const std::string dumpsys_cmd = "/vendor/bin/busybox";
    static const std::string arpinfo_args = "arp -a";
    static const std::string eth13ARP(arpProperty);
    ALOGW("arp check %s", eth13ARP.c_str());

    std::string content = readCommand({dumpsys_cmd, arpinfo_args});
    if(content.find(eth13ARP) != std::string :: npos) {
        ethconfigdump = false;
        ALOGE("eth arp is OK");
    }
    else {
        ALOGE("eth arp is ERROR");
        readCommand({"/system/bin/sh", "/vendor/bin/eth_arp.sh"});
    }

    std::regex ipRegex(R"((\d+)\.(\d+)\.(\d+)\.(\d+))");
    std::string ipRegexString = std::regex_replace(content, ipRegex, "*.*.*.$4");

    std::regex macRegex(R"((\w{2}:\w{2}:\w{2}:\w{2}:\w{2}:)(\w{2}))");
    std::string macRegexString = std::regex_replace(ipRegexString, macRegex, "*:*:*:*:*:$2");

    content = macRegexString;
    line_print(LOG_TAG, content);
  }

}  // namespace implementation
}  // namespace V1_0
}  // namespace health
}  // namespace hardware
}  // namespace gwm
}  // namespace vendor
