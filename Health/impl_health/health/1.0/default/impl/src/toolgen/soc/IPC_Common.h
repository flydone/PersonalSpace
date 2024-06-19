/*************************************************************************
* Copyright (C) 2020 GWM Automotive Inc.
*
* The copyright notice above does not evidence any actual
* or intended publication of such source code.
* The code contains GWM Confidential Proprietary Information.
*************************************************************************/

/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *                 File:  IPC_Common.h
 *            Generator:  IPC Code Generator V1.3.0
 *     Description file:  IPC_Common.h.tem
 *          Description:  IPC common header file
 *               Author:  IPC Code Generator V1.3.0
 *********************************************************************************************************************/

#ifndef _IPC_COMMON_H_
#define _IPC_COMMON_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <stdint.h>

#define IPC_PRIORITY_LOW                (0u)
#define IPC_PRIORITY_HIGH               (1u)

#define IPC_GET_BYTE(data, index) ((uint8_t *)(&(data)))[index]

#define IPC_TRANSPORT_OVERHEAD          (3u)
#define IPC_FLEX_LENGTH_FIELD_LENGTH    (2u)

#ifdef __cplusplus
}
#endif

#endif
