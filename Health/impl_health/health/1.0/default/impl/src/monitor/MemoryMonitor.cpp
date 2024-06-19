/*************************************************************************
* Copyright (C) 2022 GWM Automotive Inc.
*
* The copyright notice above does not evidence any actual
* or intended publication of such source code.
* The code contains GWM Confidential Proprietary Information.
*************************************************************************/

/**************************************************************************
 * @file MemoryMonitor.cpp
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

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "HealthMain_MemoryMonitor"

#include "MemoryMonitor.h"

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

  static bool mIsSupportDumpsys = true;
  static bool dmadump = true;
  static std::string tempFile = "";

  MemoryMonitor::MemoryMonitor()
  : MonitorBase() {}

  MemoryMonitor::~MemoryMonitor() {}

  void MemoryMonitor::dumpResource() {
      if (resMonitorEnable()) {
          if (!isSupportDumpsys()) {
              /* user product */
              std::string memPs = readMemoryByPs();
              std::string memInfo = readMeminfo();
              ALOGI("###MemoryUsage###:");
              line_print(LOG_TAG, memPs);
              line_print(LOG_TAG, memInfo);
              ALOGI("###DmaUsage###:");
              std::string dmaUsage;
              dmaUsage = readDmaUsage();
              line_print(LOG_TAG, dmaUsage);
          } else {
              /* userdebug or eng product*/
              std::string marker = "Total PSS by process";
              std::string memUsage;
              memUsage = readMemoryUsage(marker);
              ALOGI("###MemoryUsage###:");
              line_print_mem(memUsage);
              ALOGI("###DmaUsage###:");
              std::string dmaUsage;
              dmaUsage = readDmaUsage();
              line_print(LOG_TAG, dmaUsage);
          }

          if (property_get_int32("ro.build.version.sdk",32) >= 32) {
              //Android S or newer version
              ALOGI("###GpuMemoryUsage###:");
              std::string gpuMemoryUsage = readGpuMemoryInfo();
              line_print(LOG_TAG,gpuMemoryUsage);
          } else{
              //do nothing
          }

          if (property_get_int32("ro.build.version.sdk",30) >= 30) {
              //Android R or newer version
              ALOGI("###DmaBufDump###:");
              std::string dmaBufUsage = readDmaBuf();
              line_print(LOG_TAG,dmaBufUsage);
            } else{
              //do nothing
            }
      }
  }

  bool MemoryMonitor::isSupportDumpsys() {
    static char build_type[PROPERTY_VALUE_MAX] = {};
    static int32_t ret = property_get("ro.build.type", build_type, NULL);

    static char product_b16[] = "sa8155_v35_b16";
    static char product_name[PROPERTY_VALUE_MAX] = {};
    static int32_t ret2 = property_get("ro.product.name", product_name, NULL);

    if (ret != 0 && !strcasecmp(build_type, "user")) {
        mIsSupportDumpsys = false;
    }
    else if (ret2 != 0 && !strcasecmp(product_name, product_b16)) {
        mIsSupportDumpsys = false;
    }
    else {
        mIsSupportDumpsys = true;
    }
    return mIsSupportDumpsys;
  }

  /* userdebug or eng to get memoryinfo */
  std::string MemoryMonitor::readMemoryUsage(const std::string& marker) {
    static const std::string dumpsys_cmd = "/system/bin/dumpsys";
    static const std::string meminfo_args = "meminfo";
    std::string content = readCommand({dumpsys_cmd, meminfo_args});
    size_t pos = content.find(marker);
    if (pos == std::string::npos) {
        return "";
    }
    content.erase(0, pos);
    return content;
  }

  /* user to get memoryinfo */
  std::string MemoryMonitor::readMemoryByPs() {
    static const std::string dumpsys_cmd = "/system/bin/ps";
    static const std::string meminfo_args = "-A -o PID -o RSS -o VSZ -o %VSZ -o SZ -o NAME --sort -rss | head -10";

    std::string content = readCommand({dumpsys_cmd, meminfo_args});

    return content;
  }

  /* user to get memoryinfo */
  std::string MemoryMonitor::readMeminfo() {
    static const std::string dumpsys_cmd = "/system/bin/cat";
    static const std::string meminfo_args = "/proc/meminfo";

    std::string content = readCommand({dumpsys_cmd, meminfo_args});

    return content;
  }

  /* user to get memoryinfo */
  std::string MemoryMonitor::readDmaUsage() {
    static const std::string dumpsys_cmd = "/system/bin/cat";
    static const std::string dmaprocs_args = "/sys/kernel/debug/dma_buf/dmaprocs | grep PID";
    std::string dmaprocs_content = readCommand({dumpsys_cmd, dmaprocs_args});
    static const std::string bufinfo_args = "/sys/kernel/debug/dma_buf/bufinfo | grep objects";
    std::string bufinfo_content = readCommand({dumpsys_cmd, bufinfo_args});
    std::string content;
    content = "Dmaprocs info: \n" + dmaprocs_content + "Dma-buf Objects: \n" + bufinfo_content;
    dumpDma(bufinfo_content);
    return content;
  }

  /* userdebug or eng to get dma */
  void MemoryMonitor::dumpDma(const std::string &str) {
      if (!str.empty()) {
      static const uint32_t dmaSize = 1073741824U;
      std::vector<std::string> ret;
      std::string sep = " ";
      std::string temp;
      std::string::size_type begin = str.find_first_not_of(sep);
      std::string::size_type pos = 0;

      while (begin != std::string::npos) {
          pos = str.find(sep, begin);
          if (pos != std::string::npos) {
              temp = str.substr(begin, pos - begin);
              begin = pos + sep.length();
          } else {
              temp = str.substr(begin);
              begin = pos;
          }

          if (!temp.empty()) {
              ret.push_back(temp);
              temp.clear();
          }
      }

      uint32_t tempSize = std::stoul(ret.at(3));

      if(dmaSize < tempSize) {
        ALOGI("Dma-buf Objects is large and Size: %s",ret.at(3).c_str());
        if(dmadump) {
            static const std::string dumpsys_cmd = "/system/bin/cat";
            static const std::string dmaprocs_args = "/sys/kernel/debug/dma_buf/dmaprocs";
            std::string dmaprocs_content = readCommand({dumpsys_cmd, dmaprocs_args});
            static const std::string bufinfo_args = "/sys/kernel/debug/dma_buf/bufinfo";
            std::string bufinfo_content = readCommand({dumpsys_cmd, bufinfo_args});
            std::string logMsg;
            logMsg = dmaprocs_content + "\n" + bufinfo_content;

            changeLogPermission("/mnt/ext/logdatabr/dump/");
            if(!tempFile.empty()) {
                remove(tempFile.c_str());
            }
            FILE* andrNormalFile = fopen(getFileName("dma").c_str(), "a+");
            if (andrNormalFile == nullptr) {
                ALOGE("%s Open Android normal file failed!",__func__);
            }

            if(andrNormalFile != nullptr) {
                fwrite(logMsg.c_str(), 1, logMsg.size(), andrNormalFile);
                fflush(andrNormalFile);
                fclose(andrNormalFile);
                dmadump = false;
            }
        }
      } else {
          dmadump = true;
      }
      }
  }


  /* Android S or new version get the GPU memory info */
  std::string MemoryMonitor::readGpuMemoryInfo() {
      static const std::string dumpsys_cmd = "/system/bin/dumpsys";
      static const std::string gpumemory_args = "gpu --gpumem";
      std::string content = readCommand({dumpsys_cmd, gpumemory_args});

      return content;
  }


  /* Android R or new version get the  DMA buf info */
  std::string MemoryMonitor::readDmaBuf() {
      static const std::string dumpDmaBuf_cmd = "/system/bin/dmabuf_dump";
      static const std::string dmaBuf_args = "-s";
      std::string content = readCommand({dumpDmaBuf_cmd, dmaBuf_args});

          return content;
  }


  void MemoryMonitor::changeLogPermission(const std::string& path) {
      std::string rolecmd = "chown -R system:system ";
      rolecmd.append(path).append("*");
      int32_t ret = system(rolecmd.c_str());
      if(ret != 0) {
          ALOGE("%s chown failed! rolecmd:%s",__func__, rolecmd.c_str());
      }
      std::string chmodcmd = "chmod -R 0775 ";
      chmodcmd.append(path).append("*");
      ret = system(chmodcmd.c_str());
      if(ret != 0) {
          ALOGE("%s chmod failed! chmodcmd:%s",__func__, chmodcmd.c_str());
      }
  }

  std::string MemoryMonitor::getLogDirAndCreateDir() {
      std::string logDir = "/mnt/ext/logdatabr/dump/";
      if(!createDirIfNotExist(logDir)) {
          logDir = "";
      }
      return logDir;
  }

  bool MemoryMonitor::createDirIfNotExist(const std::string& logDir) {
      if(logDir.empty()) {
          ALOGE("%s logDir is empty", __func__);
          return false;
      }
      if(access(logDir.c_str(), F_OK) != 0) {  // DIR is not exist
          if(mkdir(logDir.c_str(), 0766) != 0) {
              ALOGE("%s create dir:%s failed, errorno:%d", __func__, logDir.c_str(), errno);
              return false;
          } else {
              return true;
          }
      } else {
          return true;
      }
  }

  std::string MemoryMonitor::getFileName(const std::string& type) {
      std::string logDir = getLogDirAndCreateDir();
      if(logDir.empty()) {
          ALOGE("%s The log dir:%s is empty", __func__, logDir.c_str());
          return "";
      }
      struct timespec ts;
      char timeBuf[25];//Used to store time strings,25 characters
      clock_gettime(CLOCK_REALTIME, &ts);
      struct tm tmBuf;
      struct tm* ptm = localtime_r(&ts.tv_sec, &tmBuf);
      strftime(timeBuf, sizeof(timeBuf), &"%Y%m%d%H%M%S"[0], ptm);
      std::string newFileName = "";
      newFileName.append(logDir).append(type).append("_").append(timeBuf);
	  tempFile = newFileName;
      return newFileName;
  }

  void MemoryMonitor::line_print_mem(const std::string& str) {
    std::stringstream ss(str);
    std::string line;
    int32_t line_num = 0;
    int32_t line_header_max = 11; // 1 Title + 10 Top
    static const std::string line_footer = "Total RAM:";
    bool footer_found = false;
    while (std::getline(ss, line, '\n')) {
      line_num++;
      if (line_num <= line_header_max) {
        ALOGI("%s", line.c_str());
        continue;
      }
      if (footer_found) {
        ALOGI("%s", line.c_str());
        continue;
      }
      if (line.find(line_footer) != std::string::npos) {
        footer_found = true;
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
