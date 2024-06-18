/*************************************************************************
 * Copyright (C) 2020 GWM Automotive Inc.
 *
 * The copyright notice above does not evidence any actual
 * or intended publication of such source code.
 * The code contains GWM Confidential Proprietary Information.
 *************************************************************************/
//
// Created by Song Yajing on 2021/11/24.
//

#ifndef SOMEIPTEST_IDC1_5SYSTEMFUNCTIONS_H
#define SOMEIPTEST_IDC1_5SYSTEMFUNCTIONS_H

#include "public_def.h"

typedef __uint64_t Sys_time_us_DT;
typedef __uint64_t Collect_before_time_DT;
typedef __uint64_t Collect_after_time_DT;

typedef enum {
    E_TRI_NONE = 0,
    E_TRI_DIAGNOSIS = 1,
    E_TRI_DIAGNOSIS_HARDWARE = 2,
    E_TRI_DIAGNOSIS_SOFTWARE = 3,
    E_TRI_DIAGNOSIS_NETWORK = 4,
    E_TRI_ACCIDENT = 5,
    E_TRI_REMOTE = 6,
    E_TRI_EBRAKE = 7,
    E_TRI_PBRAKE = 8,
    E_TRI_BLOCK = 9,
    E_TRI_AEB = 10,
    E_TRI_SAFESTOP = 11,
    E_TRI_SMART_DODGE = 12,
    E_TRI_ELK = 13,
    E_TRI_ESS = 14,
    E_TRI_SHARP_TURN = 15,
    E_TRI_CHANGE_LANE = 16,
    E_TRI_URGENT_ACCELERATE = 17,
    E_TRI_HMI = 18,
    E_TRI_CAMERA_BUMPY = 19,
    E_TRI_ROAD_UNDULATION = 20,
    E_TRI_FISHBONE_LINE = 21,
    E_TRI_NO_LANE_LINE = 22,
    E_TRI_SPECIAL_ROAD = 23,
    E_TRI_SPECIAL_WEATHER_SCENE = 24,
    E_TRI_LANE_LINE_COVERED = 25,
    E_TRI_ANIMAL = 26,
    E_TRI_GENERAL_OBSTACLE = 27,
    E_TRI_MINI_CAR = 28,
    E_TRI_LARGE_TRUCK = 29,
    E_TRI_RAMP = 30,
    E_TRI_ADAS_OPEN = 31,
    E_TRI_CHANGE_LANE_CANCELED = 32,
    E_TRI_ADAS_CLOSE = 33,
    E_TRI_INTERVENE = 34,
    E_TRI_TRAFFIC_JAM = 35,
    E_TRI_ME_FAILSAFE = 36,
    E_TRI_CHANGE_LANE_FAILURE = 37,
    E_CUSTOMTRIGGER = 100
} TriggerType_DT;

struct DataCollectTriggerStruct_DT {
    Sys_time_us_DT sysTimeUsDt;
    Collect_before_time_DT collectBeforeTimeDt;
    Collect_after_time_DT collectAfterTimeDt;
    TriggerType_DT triggerTypeDt;
    TriggerType_DT trigger_subtypeDt;
};

class IDC1_5SystemFunctionsListener {
  public:
    virtual ~IDC1_5SystemFunctionsListener(){};
    virtual void VideoUploadEventListener(DataCollectTriggerStruct_DT dataCollectTriggerStructDt){}
};

void IDC1_5SystemFunctionsInit(char *appName, char *configFile);
bool IDC1_5SystemFunctionsIsReady();
void IDC1_5SystemFunctionsListenerRegister(IDC1_5SystemFunctionsListener *listener);

#endif //SOMEIPTEST_IDC1_5SYSTEMFUNCTIONS_H