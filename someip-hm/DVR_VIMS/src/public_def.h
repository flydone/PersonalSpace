/*************************************************************************
 * Copyright (C) 2022 GWM Automotive Inc.
 *
 * The copyright notice above does not evidence any actual
 * or intended publication of such source code.
 * The code contains GWM Confidential Proprietary Information.
 *************************************************************************/
//
// Created by lingzhenxin on 2022/03/29.
//

#ifndef DVR_VIMS_SOMEIPTEST_PUBLIC_DEF_H
#define DVR_VIMS_SOMEIPTEST_PUBLIC_DEF_H

typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef short __int16_t;
typedef unsigned short __uint16_t;
typedef int __int32_t;
typedef unsigned int __uint32_t;
typedef float __float32_t;
#if defined(__LP64__)
typedef long int64_t;
typedef unsigned long uint64_t;
#else
typedef long long int64_t;
typedef unsigned long long uint64_t;
#endif
typedef __uint32_t Subscription;

typedef __uint32_t TotalCapacity;
typedef __uint32_t RemainingCapacity;
typedef __uint32_t TotalExportCapacity;
typedef __uint32_t FreeExportCapacity;

typedef enum {
    SUCCESS,
    OUT_OF_MEMORY,
    NOT_AVAILABLE,
    CONNECTION_FAILED,
    REMOTE_ERROR,
    UNKNOWN,
    INVALID_VALUE,
    SUBSCRIPTION_REFUSED
} CallStatus_DT;

typedef enum {
    E_EMMCNORMAL = 0,
    E_EMMCFAULT = 1
}EMMCStatus_DT;

typedef enum {
    E_DVR_NOT_FOUND = 0,
    E_DVR_FAULT = 1,
    E_DVR_MEMEORY_FULL = 2,
    E_DVR_OK = 3,
    E_WRITESLOWLY = 4,
    E_DVR_EMERGENCY_SPACE_FULL = 5,
    E_DVR_CAPACITY_NOT_SUPPORTED = 6
}TFCardStatus_DT;

typedef enum {
    E_SUCCESSFUL = 0,
    E_FAILED = 1
}SetResult_DT;

typedef enum {
    E_FORESIGHT = 0,
    E_WITHINSIGNT_OMC = 1,
    E_STREAMINGMEDIA_OR_BACKSIGNT_RESERVED = 2,
    E_360SURROUNDVIEW = 3,
    E_MULTICHANNEL = 4,
    E_WITHINSIGNT_DMC = 5
}AccessType_DT;

typedef enum {
    E_TFCARD1 = 0,
    E_TFCARD2 = 1
}TFCardOption_DT;

typedef enum {
    E_MANUALCAPTURE_BYBUTTON = 0,
    E_MANUALCAPTURE_BYHUT = 1,
    E_MANUALRECORDING_BYBUTTON = 2,
    E_MANUALRECORDING_BYHUT = 3,
    E_TIMELAPSEVIDEO = 4,
    E_PARKINGMONITORVIDEO = 5,
    E_VEHICLECOLLISIONVIDEO = 6,
    E_AIRBAGEJECTIONVIDEO = 7,
    E_AEBVIDEO = 8,
    E_BURGLARALARMVIDEO = 9,
    E_CONTINUOUSCAPTURE = 10,
    E_SHORTVIDEORECORDING_BYBUTTON = 11,
    E_SHORTVIDEORECORDING_BYHUT = 12,
    E_APSVIDEO = 13,
    E_ACC_AEBVIDEO = 14,
    E_WHISTLEVIDEO = 15,
    E_RADARRINGINGVIDEO = 16,
    E_MEBVIDEO = 17,
    E_HANDLEFTVIDEO = 18,
    E_CARINGMODE = 19,
    E_EXPORTFILE = 20,
    E_GUARDIANMODE = 21,
    E_DELETEFILE = 22,
    E_MANUALCAPTURE_BYFINDCAR = 23,
    E_SENTINELMODE_HIGH = 24,
    E_SENTINELMODE_LOW = 25
}EventType_DT;

struct EMMCCapacityStruct_DT{
    TotalCapacity totalCapacity;
    RemainingCapacity  remainingCapacity;
};

struct TFCardCapacity_DT{
    TotalCapacity totalCapacity;
    RemainingCapacity remainingCapacity;
};
#endif // DVR_VIMS_SOMEIPTEST_PUBLIC_DEF_H
