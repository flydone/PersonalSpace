/*************************************************************************
 * Copyright (C) 2020 GWM Automotive Inc.
 *
 * The copyright notice above does not evidence any actual
 * or intended publication of such source code.
 * The code contains GWM Confidential Proprietary Information.
 *************************************************************************/
//
// Created by liangyu on 2023/8/20.
//

#ifndef SOMEIP_HAVPFUNCTIONS_H
#define SOMEIP_HAVPFUNCTIONS_H

#include "public_def.h"
#include <string>
#include <vector>
#include <unistd.h>
#include <stdint.h>
using namespace std;
struct LearningWorldArray {

    public:
        LearningWorldArray() {
        };
        ~LearningWorldArray() {
        }
        
    public:
        std::vector< uint8_t> dynamicBYTE;
};

struct VehDataArray {
    public:
        VehDataArray() {
        };
        ~VehDataArray() {
        }

    public:
        std::vector< uint8_t> dynamicBYTE;
};

struct MapFileArray {
    public:
        MapFileArray() {
        };
        ~MapFileArray() {
        }

    public:
        std::vector< uint8_t> dynamicBYTE;
};

class HAVPSystemFunctionsListener {
    public:
        virtual ~HAVPSystemFunctionsListener() {};
        virtual void PathMapEventListener(MapFileArray &hapMapFileArray){};
        virtual void RendergInfoEventListener(VehDataArray &hapVehDataArray){};
        virtual void PathInfoEventListener(LearningWorldArray &hapLearningWorldArray){};
};

void HAVPSystemFunctionInit(char *appName, char *configFile);
bool HAVPSystemFunctionsIsReady();
void HAVPSystemFunctionsListenerRegister(HAVPSystemFunctionsListener *listener);





#endif //SOMEIP_HAVPFUNCTIONS_H