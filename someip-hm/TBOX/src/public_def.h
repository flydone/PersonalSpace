/*************************************************************************
 * Copyright (C) 2020 GWM Automotive Inc.
 *
 * The copyright notice above does not evidence any actual
 * or intended publication of such source code.
 * The code contains GWM Confidential Proprietary Information.
 *************************************************************************/
//
// Created by yuzhengyang on 2020/8/7.
//

#ifndef SOMEIPTEST_PUBLIC_DEF_H
#define SOMEIPTEST_PUBLIC_DEF_H

typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef short __int16_t;
typedef unsigned short __uint16_t;
typedef int __int32_t;
typedef unsigned int __uint32_t;
#if defined(__LP64__)
typedef long __int64_t;
typedef unsigned long __uint64_t;
#else
typedef long long __int64_t;
typedef unsigned long long __uint64_t;
#endif
typedef __uint32_t Subscription;

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
    E_ACTIONFAILED = 0,
    E_ACTIONSUCCEED = 1,
    E_ACTIONNOTALLOWED = 2
} TBoxResponse_DT;

#endif // SOMEIPTEST_PUBLIC_DEF_H
