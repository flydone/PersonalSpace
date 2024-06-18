/*************************************************************************
 * Copyright (C) 2022 GWM Automotive Inc.
 *
 * The copyright notice above does not evidence any actual
 * or intended publication of such source code.
 * The code contains GWM Confidential Proprietary Information.
 *************************************************************************/
//
// Created by Song Yajing on 2022/09/20.
//

#ifndef SOMEIPTEST_ADASDISPLAYINFORMATION_H
#define SOMEIPTEST_ADASDISPLAYINFORMATION_H

#include <stdint.h>
#include <iostream>
#include <vector>

class ADASDisplayInformationListener {
public:
  typedef float Guide_Line_Point_x_DT;
  typedef float Guide_Line_Point_y_DT;

  typedef struct Guide_Line_PointStruct_DT {
    Guide_Line_Point_x_DT guide_Line_Point_xDt;
    Guide_Line_Point_y_DT guide_Line_Point_yDt;
  } Guide_Line_PointStruct_DT;
  typedef std::vector<Guide_Line_PointStruct_DT> Guide_Line_PointStructArray;
  typedef struct Guide_Line_Points_ArrayOut {
    Guide_Line_PointStructArray dynamicArray;
    int len;
  } Guide_Line_Points_ArrayOut;

  typedef enum {
    E_NO_DISPLAY = 0,
    E_LEFT_SATISFIED = 1,
    E_RIGHT_SATISFIED = 2,
    E_LEFT_NOT_SATISFIED = 3,
    E_RIGHT_NOT_SATISFIED = 4,
  } LaneChangeZone_DT;

public:
  ADASDisplayInformationListener() {}
  virtual ~ADASDisplayInformationListener() {}
  virtual void GuideLineCoordinateEventListener(
      Guide_Line_Points_ArrayOut &guide_Line_Points_Array);
  virtual void LocationDispEventListener(LaneChangeZone_DT laneChangeZone);
};

#endif // SOMEIPTEST_ADASDISPLAYINFORMATION_H