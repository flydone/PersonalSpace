/*************************************************************************
* Copyright (C) 2022 GWM Automotive Inc.
*
* The copyright notice above does not evidence any actual
* or intended publication of such source code.
* The code contains GWM Confidential Proprietary Information.
*************************************************************************/

/**************************************************************************
 * @file DiskMonitor.cpp
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

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "HealthMain_DiskMonitor"

#include "DiskMonitor.h"

#include <android-base/file.h>
#include <android-base/logging.h>
#include <android-base/properties.h>
#include <android-base/stringprintf.h>
#include <android-base/strings.h>
#include <log/log.h>
#include <string.h>
#include <cutils/properties.h>
#include <sys/vfs.h>
#include <sys/statfs.h>
#include <unistd.h>
#include <fcntl.h>

namespace vendor {
namespace gwm {
namespace hardware {
namespace health {
namespace V1_0 {
namespace implementation {

  static bool neeDumpDataPartition = true;

  DiskMonitor::DiskMonitor()
  : MonitorBase() {}

  DiskMonitor::~DiskMonitor() {}

  void DiskMonitor::dumpResource() {
    if (resMonitorEnable()) {
    std::string marker = "";
    std::string diskUsage;
    diskUsage = readDiskUsage(marker);
    ALOGI("###DiskUsage###:");
    line_print(LOG_TAG, diskUsage);

    monitorDiskReserve();
    }
  }

  /* disk space usage of the file system */
  std::string DiskMonitor::readDiskUsage(const std::string& marker) {
    static const std::string get_part_info_cmd = std::string("/system/bin/df -h /data /persist");
    std::string content = readCommand({get_part_info_cmd});
    size_t pos = content.find(marker);
    if (pos == std::string::npos) {
        return "";
    }
    content.erase(0, pos);
    return content;
  }

  /* files and directory capacity */
  std::string DiskMonitor::readDiskUsageTop(bool top) {
    static const std::string get_part_top_info_cmd = std::string("/system/bin/du -a /data | sort -nr | head -20");
    static const std::string get_part_info_cmd = std::string("/system/bin/du -a /data | sort -nr > /mnt/log/dump/data_partition_dump.txt");
    std::string content;
    std::string marker = "";

    if(top){
      content = readCommand({get_part_top_info_cmd});
    }else{
      content = readCommand({get_part_info_cmd});
    }

    size_t pos = content.find(marker);
    if (pos == std::string::npos) {
        return "";
    }
    content.erase(0, pos);
    return content;
  }

  bool DiskMonitor::createPileFile(std::string filePath,std::string filePathName,int32_t size){

    int32_t fd = open(filePathName.c_str(),O_CREAT | O_RDWR,0640);

    if( fd < 0) {
      ALOGW("createPileFile %s open fail ,df=%d ",filePathName.c_str(),fd);
      return false;
    } else {
      if(0 != fallocate(fd, 0, 0, size<<20 )){
        ALOGW("createPileFile fallocate fail ");
        return false;
      } else{
        if(close(fd) < 0){
          ALOGW("createPileFile close fail ");
          return false;
        }else {
          return true;
        }
      }
    }
  }

  /* B16-6779 Health Data partition resever monitor */
  void DiskMonitor::monitorDiskReserve(){
    //int ret = 0;
    uint32_t availableDisk = 0;
    struct statfs diskInfo;
    static const std::string diskPathName = "/data";
    static const uint32_t minDiskSpaceThreshold = 150U; //MB
    static const std::string pilePathName = "/data/odm/health/reserve/pile";
    static const std::string pile1PathName = "/data/odm/health/reserve/pile/pile1";
    static const std::string pile2PathName = "/data/odm/health/reserve/pile/pile2";

     char buildType[PROPERTY_VALUE_MAX] = {};

    if (0 != statfs(diskPathName.c_str(),&diskInfo)){
      ALOGW("monitorDiskReserve can not get the disk info");
      return;
    } else {
      availableDisk = ((diskInfo.f_bsize * diskInfo.f_bavail) >> 20);
      ALOGI("monitorDiskReserve available data space  %d MB", availableDisk);
    }

    property_get("ro.build.type", buildType, "");

    if (0 == strcmp(buildType, "userdebug")) {
      //data space may be enough,just need monitor the disk usage
      if((availableDisk < (3u<<10)) && (availableDisk > (1u<<10))){
        std::string diskUsageTop;
        diskUsageTop = readDiskUsageTop(true);
        ALOGI("###DiskUsageTOP20###:");
        line_print(LOG_TAG, diskUsageTop);
        //du -a /data | sort -nr | head -20

      }else if(availableDisk < (1u<<10)){

        // data space available < 1GB
        if (neeDumpDataPartition == true){
          std::string diskUsageAll;
          diskUsageAll = readDiskUsageTop(false);
          ALOGI("###DiskUsageAll###:");
          //du -a /data | sort -nr > /mnt/log/dump/data_partition_dump.txt

          neeDumpDataPartition = false;
        } else {
          //do nothing
        }
      }else {

        //do nothing
      }
    }else { //  if (0 == strcmp(buildType, "userdebug"))
      //user build,can not run du command
    }

    if (availableDisk > (2U * minDiskSpaceThreshold)){
      //create pile1 and pile2
      if(0 != access(pile1PathName.c_str(),0)){
        createPileFile(pilePathName,pile1PathName,minDiskSpaceThreshold);
      } else {
        //file already exist,do nothing
      }

      if(0 != access(pile2PathName.c_str(),0)){
        createPileFile(pilePathName,pile2PathName,minDiskSpaceThreshold);
      } else {
        //file already exist,do nothing
      }

    }else if ((availableDisk > minDiskSpaceThreshold ) && (availableDisk < (2U * minDiskSpaceThreshold ))){

      //keep pile1 ,del pile2
      if(0 != access(pile1PathName.c_str(),0)){
        createPileFile(pilePathName,pile1PathName,minDiskSpaceThreshold);
      } else {
        //file already exist,do nothing
      }

      if(0 != access(pile2PathName.c_str(),0)){
        //file not exist,do nothing
      } else {
        if(0 != remove(pile2PathName.c_str())){
          ALOGW("monitorDiskReserve can not del file %s",pile2PathName.c_str());
        } else {
          //del success ,do nothing
        }
      }
    } else if (availableDisk < minDiskSpaceThreshold){
      //del pile1 and pile2
      if(0 != access(pile1PathName.c_str(),0)){
        //file not exist,do nothing
      } else {
        if(0 != remove(pile1PathName.c_str())){
          ALOGW("monitorDiskReserve can not del file %s",pile1PathName.c_str());
        } else {
          //del success ,do nothing
        }
      }

      if(0 != access(pile2PathName.c_str(),0)){
        //file not exist,do nothing
      } else {
        if(0 != remove(pile2PathName.c_str())){
          ALOGW("monitorDiskReserve can not del file %s",pile2PathName.c_str());
        } else {
          //del success ,do nothing
        }
      }
    }else {
      //do nothing
    }
  }

}  // namespace implementation
}  // namespace V1_0
}  // namespace health
}  // namespace hardware
}  // namespace gwm
}  // namespace vendor
