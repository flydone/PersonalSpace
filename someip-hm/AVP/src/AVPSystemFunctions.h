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

#ifndef SOMEIPTEST_AVPSYSTEMFUNCTIONS_H
#define SOMEIPTEST_AVPSYSTEMFUNCTIONS_H

#include "public_def.h"

typedef __uint8_t PathId_DT;
typedef __uint8_t PathNum_DT;
typedef __uint8_t PathLearnRate_DT;
typedef __uint8_t PathDistance_DT;
typedef __uint16_t Id_DT;
typedef __uint16_t IdleNum_DT;
typedef __uint16_t TotalNum_DT;
typedef __float32_t Lon_DT;
typedef __float32_t Lat_DT;
typedef __float32_t Distance_DT;

typedef enum {
    E_IDLE_PATHLOTTYPE = 0,
    E_FIXEDPARKINGLOT = 1,
    E_RANDOMPARKINGLOT = 2,
    E_RESERVED_PATHLOTTYPE = 3
} PathLotType_DT;

typedef enum {
    E_RESERVED_HUTREQUEST = 0,
    E_REQUEST_HUTREQUEST = 1
} HUTRequest_DT;

typedef enum {
    E_FAILED_NETWORK = 0,
    E_RESERVED_PARKINGLISTRESPONSE = 1
} ParkingListResponseNACK_DT;

typedef enum {
    E_IDLE_PATHTYPE = 0,
    E_PARKINGINTYPE = 1,
    E_PARKINGOUTTYPE = 2,
    E_RESERVED_PATHTYPE = 3
} PathType_DT;

typedef enum {
    E_DELETE = 0,
    E_SETTOP = 1,
    E_RENAME = 2
} PathInfoOperation_DT;

typedef enum {
    E_IDLE_PATHSTATUS = 0,
    E_VALIDPATH = 1,
    E_LEARNINGINPROCESSPATH = 2,
    E_INVALIDPATH = 3
} PathStatus_DT;

typedef enum {
    E_OUTSIDE = 0,
    E_INSIDE = 1,
    E_PAVPSYSTEMUNAVALIABLE = 2
} GeoFenceResponse_DT;

struct GeoFenceResponseOut {
    GeoFenceResponse_DT geoFenceResponseDt;
};

struct PathPic_DT {
  public:
    PathPic_DT() {
    };
    ~PathPic_DT() {
    }

    public:
        std::vector<uint8_t> dynamicBYTE;
};

struct ParkingListStruct_DT {
    public:
        ParkingListStruct_DT() { 
        }
        ~ParkingListStruct_DT() {
        }

    public:
        Id_DT idDt;
        std::string name = "";
        std::string address = "";
        Lon_DT lonDt;
        Lat_DT latDt;
        Distance_DT distanceDt;
        IdleNum_DT idleNumDt;
        TotalNum_DT totalNumDt;
        std::string floors = "";
};

struct PathInfoStruct_DT {
    public:
        PathInfoStruct_DT() {
        }
        ~PathInfoStruct_DT() {
        }

    public:
        PathId_DT pathIdDt;
        PathNum_DT pathNumDt;
        PathType_DT pathTypeDt;
        PathLotType_DT pathLotTypeDt;
        PathStatus_DT pathStatusDt;
        PathLearnRate_DT pathLearnRateDt;
        PathDistance_DT pathDistanceDt;
        std::string pathName = "";
        PathPic_DT pathPicDt;
};

struct ParkingListStructArrayOut {
    public:
        ParkingListStructArrayOut() {
        };
        ~ParkingListStructArrayOut() {
        }

    public:
        std::vector<ParkingListStruct_DT> dynamicArray;
};

struct PathInfoStructArrayOut {
    public:
        PathInfoStructArrayOut() {
        };
        ~PathInfoStructArrayOut() {
        }

    public:
        std::vector<PathInfoStruct_DT> dynamicArray;
};

class AVPSystemFuntionsListener {
  public:
    virtual ~AVPSystemFuntionsListener(){};
    virtual void ParkingListResponseNACKEventListener(ParkingListResponseNACK_DT parkingListResponseNACK){}
    virtual void ParkingListResponseACKEventListener(ParkingListStructArrayOut &parkingListStructArray){}
};

void AVPSystemFunctionsInit(char *appName, char *configFile);
bool AVPSystemFunctionsIsReady();
AVPCallStatus_DT GeoFenceRequestFunc(HUTRequest_DT geoFenceRequest, GeoFenceResponseOut &out);
AVPCallStatus_DT PAVPFunctionFunc(HUTRequest_DT pAVPFunctionOpen);
AVPCallStatus_DT PathInfoRequestFunc(HUTRequest_DT pathInfoRequest, PathInfoStructArrayOut &out);
AVPCallStatus_DT PathInfoOperationFunc(PathInfoOperation_DT pathInfoOperation, PathNum_DT pathNum, PathInfoStructArrayOut &out);
AVPCallStatus_DT PathInfoAddFunc(PathType_DT pathType, PathLotType_DT pathLotType, PathNum_DT pathNum, const char *pathName, PathInfoStructArrayOut &out);
AVPCallStatus_DT PathInfoRenameFunc(PathNum_DT pathNum, const char *pathName, PathInfoStructArrayOut &out);
AVPCallStatus_DT PathInfoSelectFunc(PathNum_DT pathNum);
AVPCallStatus_DT ParkingListRequestFunc(HUTRequest_DT parkingListRequest);
void AVPSystemFuntionsListenerRegister(AVPSystemFuntionsListener *listener);

#endif //SOMEIPTEST_AVPSYSTEMFUNCTIONS_H