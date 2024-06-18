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

#include "public_util.h"
#include "AVPSystemFunctions.h"

AVPSystemFuntionsListener *gAVPSystemFuntionsListener = NULL;

void fillPathInfoStruct(AVPSystemFunctions::PathInfoStructArray &array,PathInfoStructArrayOut &out) {
    LOGD("fillPathInfoStruct: enter");

    for (int i = 0; i < array.size(); i++) {
        PathInfoStruct_DT pathInfo;
        pathInfo.pathIdDt = array[i].getPathId();
        pathInfo.pathNumDt = array[i].getPathNum();
        pathInfo.pathTypeDt = static_cast<PathType_DT>(array[i].getPathType().value_);
        pathInfo.pathLotTypeDt = static_cast<PathLotType_DT>(array[i].getPathLotType().value_);
        pathInfo.pathStatusDt = static_cast<PathStatus_DT>(array[i].getPathStatus().value_);
        pathInfo.pathLearnRateDt = array[i].getPathLearnRate();
        pathInfo.pathDistanceDt = array[i].getPathDistance();
        pathInfo.pathName = array[i].getPathName();
        std::vector<uint8_t> pic = array[i].getPathPic();
        for (int k = 0; k < array[i].getPathPic().size(); k++) {
            pathInfo.pathPicDt.dynamicBYTE.push_back(pic[k]);
        }
        out.dynamicArray.push_back(std::move(pathInfo));
        LOGD("fillPathInfoStruct: pathId = %d, pathNum = %d, pathType = %d, pathLotType = %d, pathStatus = %d, pathLearnRate = %d, pathDistance = %d, pathName = %s, len = %lu",
            out.dynamicArray[i].pathIdDt, out.dynamicArray[i].pathNumDt, out.dynamicArray[i].pathTypeDt, out.dynamicArray[i].pathLotTypeDt,
            out.dynamicArray[i].pathStatusDt, out.dynamicArray[i].pathLearnRateDt, out.dynamicArray[i].pathDistanceDt, out.dynamicArray[i].pathName.c_str(), out.dynamicArray[i].pathPicDt.dynamicBYTE.size());
    }
}

void AVPSystemFunctionsInit(char *appName, char *configFile) {
    if (configFile) {
        setenv("VSOMEIP_CONFIGURATION", configFile, 1);
    }
    if (gRuntime == NULL) {
        gRuntime = CommonAPI::Runtime::get();
    }
    gAVPSystemFunctionsProxy = gRuntime->buildProxy<AVPSystemFunctionsProxy>(
        "local", "AVPSystemFunctions01", appName);
    std::string versionInfo = gRuntime->get_version();
    std::string version = versionInfo.substr(versionInfo.rfind(" ") + 1);

    LOGD("AVPSystemFunctionsInit: appName = %s version = %s", appName, version.c_str());
    __system_property_set("vendor.gwm.someip.version", version.c_str());
}

bool AVPSystemFunctionsIsReady() {
    bool ret = gAVPSystemFunctionsProxy->isAvailable();
    LOGD("AVPSystemFunctionsIsReady: %d",ret);
    return ret;
}

AVPCallStatus_DT GeoFenceRequestFunc(HUTRequest_DT geoFenceRequest, GeoFenceResponseOut &out) {
    LOGD("GeoFenceRequestFunc: geoFenceRequest = %d",geoFenceRequest);
    CommonAPI::CallStatus callStatus;

    AVPSystemFunctions::HUTRequest hutRequest;
    hutRequest.value_ = geoFenceRequest;

    AVPSystemFunctions::GeoFenceResponse response;
    gAVPSystemFunctionsProxy->GeoFenceRequest(hutRequest, callStatus, response);

    out.geoFenceResponseDt = static_cast<GeoFenceResponse_DT>(response.value_);
    LOGD("GeoFenceRequestFunc: out = %d, callStatus = %d",out.geoFenceResponseDt, static_cast<AVPCallStatus_DT>(callStatus));
    return static_cast<AVPCallStatus_DT>(callStatus);
}

AVPCallStatus_DT PAVPFunctionFunc(HUTRequest_DT pAVPFunctionOpen) {
    LOGD("PAVPFunctionFunc: pAVPFunctionOpen = %d",pAVPFunctionOpen);
    CommonAPI::CallStatus callStatus;
    AVPSystemFunctions::HUTRequest hutRequest;
    hutRequest.value_ = pAVPFunctionOpen;
    gAVPSystemFunctionsProxy->PAVPFunction(hutRequest, callStatus);
    LOGD("PAVPFunctionFunc: callStatus = %d", static_cast<AVPCallStatus_DT>(callStatus));
    return static_cast<AVPCallStatus_DT>(callStatus);
}

AVPCallStatus_DT PathInfoRequestFunc(HUTRequest_DT pathInfoRequest, PathInfoStructArrayOut &out) {
    LOGD("PathInfoRequestFunc: pathInfoRequest = %d",pathInfoRequest);
    CommonAPI::CallStatus callStatus;

    AVPSystemFunctions::HUTRequest hutRequest;
    hutRequest.value_ = pathInfoRequest;

    AVPSystemFunctions::PathInfoStructArray array;
    gAVPSystemFunctionsProxy->PathInfoRequest(hutRequest, callStatus, array);

    fillPathInfoStruct(array,out);
    LOGD("PathInfoRequestFunc: callStatus = %d, out.len = %lu",static_cast<AVPCallStatus_DT>(callStatus), out.dynamicArray.size());
    return static_cast<AVPCallStatus_DT>(callStatus);
}

AVPCallStatus_DT PathInfoOperationFunc(PathInfoOperation_DT pathInfoOperation, PathNum_DT pathNum, PathInfoStructArrayOut &out) {
    LOGD("PathInfoOperationFunc: pathInfoOperation = %d, pathNum = %d",pathInfoOperation, pathNum);
    CommonAPI::CallStatus callStatus;

    AVPSystemFunctions::PathInfoOperation operation;
    operation.value_ = pathInfoOperation;

    AVPSystemFunctions::PathInfoStructArray array;
    gAVPSystemFunctionsProxy->PathInfoOperation(operation, pathNum, callStatus, array);

    fillPathInfoStruct(array,out);
    LOGD("PathInfoOperationFunc: callStatus = %d, out.len = %lu",static_cast<AVPCallStatus_DT>(callStatus), out.dynamicArray.size());
    return static_cast<AVPCallStatus_DT>(callStatus);
}

AVPCallStatus_DT PathInfoAddFunc(PathType_DT pathType, PathLotType_DT pathLotType, PathNum_DT pathNum, const char *pathName, PathInfoStructArrayOut &out) {
    LOGD("PathInfoAddFunc: pathType = %d, pathLotType = %d, pathNum = %d, pathName = %s",pathType, pathLotType, pathNum, pathName);
    CommonAPI::CallStatus callStatus;

    AVPSystemFunctions::PathType type;
    type.value_ = pathType;

    AVPSystemFunctions::PathLotType lotType;
    lotType.value_ = pathLotType;

    AVPSystemFunctions::PathInfoStructArray array;
    gAVPSystemFunctionsProxy->PathInfoAdd(type, lotType, pathNum, pathName, callStatus, array);

    fillPathInfoStruct(array, out);
    LOGD("PathInfoAddFunc: callStatus = %d, out.len = %lu",static_cast<AVPCallStatus_DT>(callStatus), out.dynamicArray.size());
    return static_cast<AVPCallStatus_DT>(callStatus);
}

AVPCallStatus_DT PathInfoRenameFunc(PathNum_DT pathNum, const char *pathName, PathInfoStructArrayOut &out) {
    LOGD("PathInfoRenameFunc: pathNum = %d, pathName = %s", pathNum, pathName);
    CommonAPI::CallStatus callStatus;
    AVPSystemFunctions::PathInfoStructArray array;
    gAVPSystemFunctionsProxy->PathInfoRename(pathNum,pathName,callStatus,array);

    fillPathInfoStruct(array, out);
    LOGD("PathInfoRenameFunc: callStatus = %d, out.len = %lu",static_cast<AVPCallStatus_DT>(callStatus), out.dynamicArray.size());
    return static_cast<AVPCallStatus_DT>(callStatus);
}

AVPCallStatus_DT PathInfoSelectFunc(PathNum_DT pathNum) {
    LOGD("PathInfoSelectFunc: pathNum = %d",pathNum);
    CommonAPI::CallStatus callStatus;
    gAVPSystemFunctionsProxy->PathInfoSelect(pathNum, callStatus);
    LOGD("PathInfoSelectFunc: callStatus = %d",static_cast<AVPCallStatus_DT>(callStatus));
    return static_cast<AVPCallStatus_DT>(callStatus);
}

AVPCallStatus_DT ParkingListRequestFunc(HUTRequest_DT parkingListRequest) {
    LOGD("ParkingListRequestFunc: parkingListRequest = %d",parkingListRequest);
    CommonAPI::CallStatus callStatus;

    AVPSystemFunctions::HUTRequest hutRequest;
    hutRequest.value_ = parkingListRequest;

    gAVPSystemFunctionsProxy->ParkingListRequest(hutRequest, callStatus);
    LOGD("ParkingListRequestFunc: callStatus = %d",static_cast<AVPCallStatus_DT>(callStatus));
    return static_cast<AVPCallStatus_DT>(callStatus);
}

void AVPSystemFuntionsListenerRegister(AVPSystemFuntionsListener *listener) {
    LOGD("AVPSystemFuntionsListenerRegister: enter");
    gAVPSystemFuntionsListener = listener;

    gAVPSystemFunctionsProxy->getParkingListResponseNACKEvent().subscribe([&](AVPSystemFunctions::ParkingListResponseNACK responseNACK) {
        if (gAVPSystemFuntionsListener) {
            ParkingListResponseNACK_DT parkingListResponseNACKDt;
            parkingListResponseNACKDt =
            static_cast<ParkingListResponseNACK_DT>(responseNACK.value_);
            LOGD("parkingListResponseNACKDt = %d",parkingListResponseNACKDt);
            gAVPSystemFuntionsListener->ParkingListResponseNACKEventListener(parkingListResponseNACKDt);
        }
    });

    gAVPSystemFunctionsProxy->getParkingListResponseACKEvent().subscribe([&](AVPSystemFunctions::ParkingListStructArray array) {
        if (gAVPSystemFuntionsListener) {
            ParkingListStructArrayOut out;
            int len = array.size();
            for (int i = 0; i < len; i++) {
                ParkingListStruct_DT item;
                item.idDt = array[i].getId();
                item.name = array[i].getName();
                item.address = array[i].getAddress();
                item.lonDt = array[i].getLon();
                item.latDt = array[i].getLat();
                item.distanceDt = array[i].getDistance();
                item.idleNumDt = array[i].getIdle_num();
                item.totalNumDt = array[i].getTotal_num();
                item.floors = array[i].getFloors();
                out.dynamicArray.push_back(std::move(item));
            }

            LOGD("parkingListStructArray: out.len:%lu", out.dynamicArray.size());
            gAVPSystemFuntionsListener->ParkingListResponseACKEventListener(out);
        }
    });
}