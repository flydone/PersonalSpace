/*************************************************************************
 * Copyright (C) 2022 GWM Automotive Inc.
 *
 * The copyright notice above does not evidence any actual
 * or intended publication of such source code.
 * The code contains GWM Confidential Proprietary Information.
 *************************************************************************/
//
// Created by Xu Feifei on 2023/07/10.
//

#ifndef SOMEIPTEST_NAVIGATION_MAPINFORMATION_H
#define SOMEIPTEST_NAVIGATION_MAPINFORMATION_H

#include <stdint.h>
#include <iostream>
#include <vector>
#include <string>

typedef enum
{
    SUCCESS,
    OUT_OF_MEMORY,
    NOT_AVAILABLE,
    CONNECTION_FAILED,
    REMOTE_ERROR,
    UNKNOWN,
    INVALID_VALUE,
    SUBSCRIPTION_REFUSED
} CallStatus_DT;

class NavigationMapInformation
{
public:
    typedef std::string RouteODD_DT;
    typedef std::string SDRoute_DT;

public:
    NavigationMapInformation();
    virtual ~NavigationMapInformation();
    virtual CallStatus_DT NavPathInfoReq(const SDRoute_DT &_SDRoute);
};

#endif // SOMEIPTEST_NAVIGATION_MAPINFORMATION_H