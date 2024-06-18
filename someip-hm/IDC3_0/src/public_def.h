/*************************************************************************
 * Copyright (C) 2022 GWM Automotive Inc.
 *
 * The copyright notice above does not evidence any actual
 * or intended publication of such source code.
 * The code contains GWM Confidential Proprietary Information.
 *************************************************************************/
//
// Created by Zengweifeng on 2022/2/14.
//

#ifndef HAVPANDAVP_FUNCTIONS_SOMEIPTEST_PUBLIC_DEF_H
#define HAVPANDAVP_FUNCTIONS_SOMEIPTEST_PUBLIC_DEF_H

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
typedef __uint32_t Subscription;

#endif // HAVPANDAVP_FUNCTIONS_SOMEIPTEST_PUBLIC_DEF_H
