/*************************************************************************
 * Copyright (C) 2022 GWM Automotive Inc.
 *
 * The copyright notice above does not evidence any actual
 * or intended publication of such source code.
 * The code contains GWM Confidential Proprietary Information.
 *************************************************************************/
//
// Created by LZX on 2022/4/3.
//

#ifndef DVR_VIMS_DVRSYSTEMCONFIG_H
#define DVR_VIMS_DVRSYSTEMCONFIG_H


#include "public_def.h"

typedef enum {
    E_GET_ALL_CONFIG = 0,
    E_GET_ARRAY_CONFIG = 1
}GetAllConfig_DT;

typedef enum {
    E_RESUMEFACTORY = 0,
    E_PATCHUPGRADE = 1
}ResetConfigType_DT;

typedef enum {
    E_ON = 0,
    E_OFF = 1,
    E_0S = 2,
    E_10S = 3,
    E_60SOR1MINUTE = 4,
    E_3MINUTE = 5,
    E_5MINUTE = 6
}ParamConfigOperation_DT;

typedef enum {
    E_SETWIDEDYNAMICMODE = 0,
    E_SETSEGMENTRECORDINGTIME = 1,
    E_SETPOWEROFFDELAY = 2,
    E_SETEVENTVIDEOCYCLECOVERAGE = 3,
    E_SETTAPERECORDING = 4,
    E_SETCYCLEVIDEOTAPEMODE = 5,
    E_SETINTERIORCAMERA = 6,
    E_SET360SURROUNDVIEW = 7,
    E_SETPARKMONITOR = 8,
    E_SETOSDINFO = 9
}ParamConfigType_DT;

typedef enum {
    E_UINT8 = 0,
    E_UINT16 = 1,
    E_UINT32 = 2,
    E_UINT64 = 3,
    E_UTF8 = 4,
    E_ENUM = 5,
    E_BOOL = 6
}ConfigParamValueType_DT;

struct ParamCofigStruct_DT{
    public:
        ParamCofigStruct_DT(){
        }
        ~ParamCofigStruct_DT(){
        }

    public:
        ConfigParamValueType_DT configParamValueTypeDt;
        ParamConfigType_DT paramConfigTypeDt;
        ParamConfigOperation_DT paramConfigOperationDt;
};

struct ConfigListArrayOut{
    public:
        ConfigListArrayOut(){
        }
        ~ConfigListArrayOut(){
        }

    public:
        std::vector<ParamCofigStruct_DT> dynamicArray;
};

struct ConfigListArrayInput{
    public:
        ConfigListArrayInput(){
        }
        ~ConfigListArrayInput(){
        }

    public:
        std::vector<ParamCofigStruct_DT> dynamicArray;
};

struct ConfigTypeList_DT{
    ParamConfigType_DT ParamConfigType;
};

struct ConfigTypeList{
    public:
        ConfigTypeList(){
        }
        ~ConfigTypeList(){
        }

    public:
        std::vector<ConfigTypeList_DT> dynamicList;
};

struct SetResultOut{
    SetResult_DT ParamConfigResult;
};

struct SetResultResetConfigOut{
    SetResult_DT ResetConfigACK;
};


void DVRSystemConfigInit(char *appName, char *configFile);
bool DVRSystemConfigIsReady();
CallStatus_DT DVRGetConfigFunc(GetAllConfig_DT GetAllConfig,ConfigTypeList &list,ConfigListArrayOut &out);
CallStatus_DT DVRSetConfig(ConfigListArrayInput &array,SetResultOut &out);
CallStatus_DT ResetDefaultConfigFunc(ResetConfigType_DT ResetConfigType,SetResultResetConfigOut &out);

#endif //DVR_VIMS_DVRSYSTEMCONFIG_H
