/*************************************************************************
* Copyright (C) 2022 GWM Automotive Inc.
*
* The copyright notice above does not evidence any actual
* or intended publication of such source code.
* The code contains GWM Confidential Proprietary Information.
*************************************************************************/

/**************************************************************************
 * @file IptableMonitor.cpp
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

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "HealthMain_IptableMonitor"

#include "IptableMonitor.h"

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

  static bool iptabledump = true;
  static bool iptabledebug = false;
  static bool mIptableReady = false;

  IptableMonitor::IptableMonitor()
  : MonitorBase() {}

  IptableMonitor::~IptableMonitor() {}

  void IptableMonitor::dumpResource() {
    if (monitorIptableEnable()) {
        if(iptableReady()) {
            monitorIptable();
        }
        if(iptableCUXReady()) {
            monitorCUXIptable();
        }
    }
    if (iptableDebug()) {
        if(iptableReady()) {
            monitorIptable();
        }
        if(iptableCUXReady()) {
            monitorCUXIptable();
        }
    }
  }

  bool IptableMonitor::monitorIptableEnable() {
    return iptabledump;
  }

  bool IptableMonitor::iptableDebug() {
    iptabledebug = property_get_bool("vendor.nobo.iptables.debug", false);
    return iptabledebug;
  }

  bool IptableMonitor::iptableReady() {
    mIptableReady = property_get_bool("vendor.nobo.iptables.ready", false);
    return mIptableReady;
  }

  bool IptableMonitor::iptableCUXReady() {
    mIptableReady = property_get_bool("vendor.nobo.iptables.cux.ready", false);
    return mIptableReady;
  }

  /* check /vendor/bin/iptable_set.sh */
  void IptableMonitor::monitorIptable() {
    ALOGI("###MonitorIptable###:");
    static const std::string uid = "0-11000";
    static const std::string markerUidWhitelist = "fw_UidWhitelist";
    static const std::string markerUrlWhitelist = "fw_UrlWhitelist";
    static const std::string markerOUTPUT = "fw_OUTPUT";
    std::string contentUid = readIptables(markerUidWhitelist);
    //ALOGI("fw_UidWhitelist %s", contentUid.c_str());
    std::string contentUrl = readIptables(markerUrlWhitelist);
    //ALOGI("fw_UrlWhitelist %s", contentUrl.c_str());
    std::string contentOUTPUT = readIptables(markerOUTPUT);
    ALOGI("fw_OUTPUT %s", contentOUTPUT.c_str());
    for(int32_t i=0; i<4; i++) {
        if(contentUid.find(markerUidWhitelist) != std::string :: npos) {
            if(contentUid.find(uid) != std::string :: npos) {
                if(contentUrl.find(markerUrlWhitelist) != std::string :: npos) {
                    if(contentOUTPUT.find(markerUidWhitelist) == std::string :: npos) {
                        if(contentOUTPUT.find(markerUrlWhitelist) == std::string :: npos) {
                            ALOGE("Iptable fw_OUTPUT fw_UidWhitelist get failed");
                            ALOGE("%s", contentOUTPUT.c_str());
                            std::string dumpsys_cmd = "/system/bin/iptables";
                            std::string uid_args = "-A fw_OUTPUT -j fw_UidWhitelist";
                            std::string content = readCommand({dumpsys_cmd, uid_args});
                            contentOUTPUT = readIptables(markerOUTPUT);
                        }
                        else {
                            int32_t tempLine = getIptableLine(contentOUTPUT, markerUrlWhitelist);
                            if(tempLine > 0) {
                                ALOGE("Iptable fw_OUTPUT fw_UidWhitelist line error");
                                ALOGE("%s", contentOUTPUT.c_str());
                                std::string dumpsys_cmd = "/system/bin/iptables";
                                std::string uid_args = "-I fw_OUTPUT " + std::to_string(tempLine) + " -j fw_UidWhitelist";
                                std::string content = readCommand({dumpsys_cmd, uid_args});
                                contentOUTPUT = readIptables(markerOUTPUT);
                                break;
                            }
                        }
                    }
                    if(contentOUTPUT.find(markerUidWhitelist) != std::string :: npos) {
                        if(contentOUTPUT.find(markerUrlWhitelist) == std::string :: npos) {
                            ALOGE("Iptable fw_OUTPUT fw_UrlWhitelist get failed");
                            ALOGE("%s", contentOUTPUT.c_str());
                            std::string dumpsys_cmd = "/system/bin/iptables";
                            std::string uid_args = "-A fw_OUTPUT -j fw_UrlWhitelist";
                            std::string content = readCommand({dumpsys_cmd, uid_args});
                            contentOUTPUT = readIptables(markerOUTPUT);
                        }
                        if(contentOUTPUT.find(markerUrlWhitelist) != std::string :: npos) {
                            ALOGI("Iptable get success");
                            iptabledump = false;
                            break;
                        }
                    }
                }
                else {
                    ALOGE("Iptable fw_UrlWhitelist get failed");
                    //ALOGE("%s", contentUrl.c_str());
                    std::string dumpsys_cmd = "/system/bin/iptables";
                    std::string uid_args = "-N fw_UrlWhitelist";
                    std::string content = readCommand({dumpsys_cmd, uid_args});
                    contentUrl = readIptables(markerUrlWhitelist);
                    continue;
                }
            }
            else {
                ALOGE("Iptable uid get failed");
                //ALOGE("%s", contentUid.c_str());
                std::string dumpsys_cmd = "/system/bin/iptables";
                std::string uid_args = "-A fw_UidWhitelist -m owner --uid-owner 0-11000 -j ACCEPT";
                std::string content = readCommand({dumpsys_cmd, uid_args});
                contentUid = readIptables(markerUidWhitelist);
                continue;
            }
        }
        else {
            ALOGE("Iptable fw_UidWhitelist get failed");
            //ALOGE("%s", contentUid.c_str());
            std::string dumpsys_cmd = "/system/bin/iptables";
            std::string uid_args = "-N fw_UidWhitelist";
            std::string content = readCommand({dumpsys_cmd, uid_args});
            contentUid = readIptables(markerUidWhitelist);
            continue;
        }
    }
  }

  void IptableMonitor::monitorCUXIptable() {
      ALOGI("###MonitorIptable###:");
      static const std::string markerINPUT = "INPUT";

      static const std::string markerIP192 = "ACCEPT     all  --  192.168.0.0/16       0.0.0.0/0";
      static const std::string markerACCEPTALL = "ACCEPT     all  --  0.0.0.0/0            0.0.0.0/0            ctstate RELATED,ESTABLISHED";
      static const std::string markerDROPALL =  "DROP       all  --  0.0.0.0/0            0.0.0.0/0            ctstate INVALID";
      static const std::string markerDROPTCP = "DROP       tcp  --  0.0.0.0/0            0.0.0.0/0            ctstate NEW";
      static const std::string markerIP1931 = "ACCEPT     all  --  193.18.1.0/24        0.0.0.0/0";
      static const std::string markerIP1932 = "ACCEPT     all  --  193.18.2.0/24        0.0.0.0/0";
      static const std::string markerIP172 = "ACCEPT     all  --  172.16.0.0/16        0.0.0.0/0";

      static const std::string markerIP224 = "DROP       all  --  172.16.0.0/16        224.0.0.0/3";
      static const std::string markerIP240 = "ACCEPT     all  --  172.16.0.0/16        240.0.0.0/4";
      static const std::string markerIP251 = "ACCEPT     all  --  0.0.0.0/0            239.192.255.251";

      std::string contentINPUT = readIptables(markerINPUT);
      for(int32_t i=0; i<2; i++) {
          if(contentINPUT.find(markerIP251) == std::string :: npos) {
              ALOGE("Iptable ACCEPT 251 get failed");
              std::string dumpsys_cmd = "/system/bin/iptables";
              std::string uid_args = "-t filter -I INPUT 3 -d 239.192.255.251 -j ACCEPT";
              std::string content = readCommand({dumpsys_cmd, uid_args});
              contentINPUT = readIptables(markerINPUT);
              if(contentINPUT.find(markerIP240) == std::string :: npos) {
                  ALOGE("Iptable ACCEPT 240 get failed");
                  dumpsys_cmd = "/system/bin/iptables";
                  uid_args = "-t filter -I INPUT 4 -s 172.16.0.0/16 -d 240.0.0.0/240.0.0.0 -j ACCEPT";
                  content = readCommand({dumpsys_cmd, uid_args});
                  contentINPUT = readIptables(markerINPUT);
              }
              if(contentINPUT.find(markerIP224) == std::string :: npos) {
                  ALOGE("Iptable ACCEPT 224 get failed");
                  dumpsys_cmd = "/system/bin/iptables";
                  uid_args = "-t filter -I INPUT 5 -s 172.16.0.0/16 -d 224.0.0.0/224.0.0.0 -j DROP";
                  content = readCommand({dumpsys_cmd, uid_args});
                  contentINPUT = readIptables(markerINPUT);
              }
          }
          if(contentINPUT.find(markerACCEPTALL) == std::string :: npos) {
              int32_t tempLine1 = getIptableLine(contentINPUT, markerDROPALL);
              int32_t tempLine2 = getIptableLine(contentINPUT, markerDROPTCP);
              if(tempLine1 > tempLine2) {
                  tempLine1 = tempLine2;
              }
              if(tempLine1 > 0) {
                  ALOGE("Iptable ACCEPT ALL get failed");
                  std::string dumpsys_cmd = "/system/bin/iptables";
                  std::string uid_args = "-I INPUT " + std::to_string(tempLine1) + " -m conntrack --ctstate ESTABLISHED,RELATED -j ACCEPT";
                  std::string content = readCommand({dumpsys_cmd, uid_args});
                  contentINPUT = readIptables(markerINPUT);
              }
          }
          if(contentINPUT.find(markerIP192) == std::string :: npos) {
              int32_t tempLine = getIptableLine(contentINPUT, markerACCEPTALL);
              if(tempLine >= 0) {
                  ALOGE("Iptable IP192 get failed");
                  std::string dumpsys_cmd = "/system/bin/iptables";
                  std::string uid_args = "-I INPUT " + std::to_string(tempLine) + " -s 192.168.0.0/16 -j ACCEPT";
                  std::string content = readCommand({dumpsys_cmd, uid_args});
                  contentINPUT = readIptables(markerINPUT);
              }
          }
          if(contentINPUT.find(markerIP1931) == std::string :: npos) {
              ALOGE("Iptable IP1931 get failed");
              std::string dumpsys_cmd = "/system/bin/iptables";
              std::string uid_args = "-A INPUT -s 193.18.1.0/24 -j ACCEPT";
              std::string content = readCommand({dumpsys_cmd, uid_args});
              contentINPUT = readIptables(markerINPUT);
          }
          if(contentINPUT.find(markerIP1932) == std::string :: npos) {
              ALOGE("Iptable IP1932 get failed");
              std::string dumpsys_cmd = "/system/bin/iptables";
              std::string uid_args = "-A INPUT -s 193.18.2.0/24 -j ACCEPT";
              std::string content = readCommand({dumpsys_cmd, uid_args});
              contentINPUT = readIptables(markerINPUT);
          }
          if(contentINPUT.find(markerIP172) == std::string :: npos) {
              ALOGE("Iptable IP172 get failed");
              std::string dumpsys_cmd = "/system/bin/iptables";
              std::string uid_args = "-A INPUT -s 172.16.0.0/16 -j ACCEPT";
              std::string content = readCommand({dumpsys_cmd, uid_args});
              contentINPUT = readIptables(markerINPUT);
          }
          if(contentINPUT.find(markerACCEPTALL) != std::string :: npos && contentINPUT.find(markerIP192) != std::string :: npos && contentINPUT.find(markerIP1931) != std::string :: npos && contentINPUT.find(markerIP1932) != std::string :: npos && contentINPUT.find(markerIP172) != std::string :: npos && contentINPUT.find(markerIP251) != std::string :: npos) {
              ALOGI("Iptable get success");
              iptabledump = false;
              break;
          }
      }
  }

  int32_t IptableMonitor::getIptableLine(const std::string& str, const std::string& marker) {
      std::vector<std::string> vec = stringSplit(str, '\n');
      int32_t urlWhitelistLine=-2;
      for (auto var:vec) {
          urlWhitelistLine++;
          if(var.find(marker) != std::string :: npos) {
              return urlWhitelistLine;
          }
      }
      return (urlWhitelistLine+1);
  }

  std::vector<std::string> IptableMonitor::stringSplit(const std::string& str, char delim) {
      std::stringstream ss(str);
      std::string item;
      std::vector<std::string> elems;
      while (std::getline(ss, item, delim)) {
          if (!item.empty()) {
              elems.push_back(item);
          }
      }
      return elems;
  }

  std::string IptableMonitor::readIptables(const std::string& marker) {
    static const std::string dumpsys_cmd = "/system/bin/iptables";
  
    std::string content = readCommand({dumpsys_cmd, "-nL '" + marker + "'"});
  
    return content;
  }

}  // namespace implementation
}  // namespace V1_0
}  // namespace health
}  // namespace hardware
}  // namespace gwm
}  // namespace vendor
