/*************************************************************************
 * Copyright (C) 2020 GWM Automotive Inc.
 *
 * The copyright notice above does not evidence any actual
 * or intended publication of such source code.
 * The code contains GWM Confidential Proprietary Information.
 *************************************************************************/
//
// Created by zhaoying on 2021/5/10.
//

#ifndef AVP_SOMEIPTEST_PUBLIC_DEF_H
#define AVP_SOMEIPTEST_PUBLIC_DEF_H

typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef short __int16_t;
typedef unsigned short __uint16_t;
typedef int __int32_t;
typedef unsigned int __uint32_t;
typedef float __float32_t;
#if defined(__LP64__)
typedef long __int64_t;
typedef unsigned long __uint64_t;
#else
typedef long long __int64_t;
typedef unsigned long long __uint64_t;
#endif

typedef enum {
    AVP_SUCCESS,
    AVP_OUT_OF_MEMORY,
    AVP_NOT_AVAILABLE,
    AVP_CONNECTION_FAILED,
    AVP_REMOTE_ERROR,
    AVP_UNKNOWN,
    AVP_INVALID_VALUE,
    AVP_SUBSCRIPTION_REFUSED
} AVPCallStatus_DT;

#endif // AVP_SOMEIPTEST_PUBLIC_DEF_H
