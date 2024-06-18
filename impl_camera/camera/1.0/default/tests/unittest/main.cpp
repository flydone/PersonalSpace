/*************************************************************************
* Copyright (C) 2020 GWM Automotive Inc.
*
* The copyright notice above does not evidence any actual
* or intended publication of such source code.
* The code contains GWM Confidential Proprietary Information.
 *************************************************************************/
/**************************************************************************
 * @file dvt gtest main.cpp
 *
 *
 * @project     v3.5
 * @subsystem
 * @version     1.0
 * @author      HongJiuJin
 * @date        2020-12-2

 Module-History:
 Date(dd.mm.year)| Author            | Reason
 The latest entry at the head of the history list.
 2/12/2020         Hong Jiu Jin   Init version
 ***************************************************************************/

#include <gtest/gtest.h>

#include <iostream>

using namespace std;

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  int status = RUN_ALL_TESTS();
  cout << "Test result = " << status;
  return 0;
}
