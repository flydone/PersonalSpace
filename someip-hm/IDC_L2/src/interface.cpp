#include "interface.hpp"
#include "ADASDisplayInformation.hpp"
#include "NavigationMapInformation.hpp"
#include "listener.hpp"
#include <CommonAPI/CommonAPI.hpp>
#include <iostream>
#include <stdint.h>
#include <string>
#include <unistd.h>
#include <v1/GREATWALL/IDC_L2_IDC1_5_IDC3_0_MDC_A/ADASDisplayInformationProxy.hpp>
#include <v1/GREATWALL/IDC_L2_IDC1_5_IDC3_0_MDC_A/IDC_L2SystemFunctionsProxy.hpp>
#include <v1/GREATWALL/MDC_A_IDC3_0/NavigationMapInformationProxy.hpp>
using namespace v1::GREATWALL::IDC_L2_IDC1_5_IDC3_0_MDC_A;

std::shared_ptr<IDC_L2SystemFunctionsProxy<> > systemFunctionsProxy;
Listener *globalListener = nullptr;
std::shared_ptr<ADASDisplayInformationProxy<> > gADASDisplayInformationProxy;
ADASDisplayInformationListener *gADASDisplayInformationListener = nullptr;
std::shared_ptr<v1::GREATWALL::MDC_A_IDC3_0::NavigationMapInformationProxy<> > gNavigationMapInformationProxy;

static void LocationInfoStruct_Convert(Listener::LocationInfoStruct &desValue,
                                       const IDC_L2SystemFunctions::LocationInfoStruct &srcValue)
{
    desValue._Loc_Con_lane = (srcValue.getLoc_Con_lane()).value_;
    desValue._Loc_head_right = srcValue.getLoc_head_right();
    desValue._Loc_head_left = srcValue.getLoc_head_left();
    desValue._Loc_heading_Con = srcValue.getLoc_heading_Con();
    desValue._Loc_TimeStamp = srcValue.getLoc_TimeStamp();
    desValue._Loc_current_lane = srcValue.getLoc_current_lane();
    desValue._Loc_speed = srcValue.getLoc_speed();
    desValue._Loc_Altitude_pos_Con = srcValue.getLoc_Altitude_pos_Con();
    desValue._Loc_lateral_pos = srcValue.getLoc_lateral_pos();
    desValue._Loc_Altitude_pos = srcValue.getLoc_Altitude_pos();
    desValue._Loc_speed_Con = srcValue.getLoc_speed_Con();
    desValue._Loc_heading = srcValue.getLoc_heading();
    desValue._Loc_dis_left = srcValue.getLoc_dis_left();
    desValue._Loc_dis_right = srcValue.getLoc_dis_right();
    desValue._Loc_longitudinal_pos = srcValue.getLoc_longitudinal_pos();
}
static void OBJPptyInfoStruct_Convert(Listener::OBJPptyInfoStruct &desValue,
                                      const IDC_L2SystemFunctions::OBJPptyInfoStruct &srcValue)
{
    desValue._OBJ_TimeStamp = srcValue.getOBJ_TimeStamp();
    for (int i = 0; i < srcValue.getOBJInfoStructArray().size(); i++)
    {
        Listener::OBJInfoStruct desStruct;
        desStruct._OBJ_ID = (srcValue.getOBJInfoStructArray())[i].getOBJ_ID();
        desStruct._OBJ_Type = (srcValue.getOBJInfoStructArray())[i].getOBJ_Type().value_;
        desStruct._OBJ_Hight = (srcValue.getOBJInfoStructArray())[i].getOBJ_Hight();
        desStruct._OBJ_HeadingAngle = (srcValue.getOBJInfoStructArray())[i].getOBJ_HeadingAngle();
        desStruct._OBJ_DX = (srcValue.getOBJInfoStructArray())[i].getOBJ_DX();
        desStruct._OBJ_DY = (srcValue.getOBJInfoStructArray())[i].getOBJ_DY();
        desStruct._OBJ_ExistProb = (srcValue.getOBJInfoStructArray())[i].getOBJ_ExistProb();
        desStruct._OBJ_Age = (srcValue.getOBJInfoStructArray())[i].getOBJ_Age();
        desValue._OBJInfoStructArray.push_back(desStruct);
    }

    desValue._OBJ_DispProperty._Target_Obj._OBJ_ID = srcValue.getOBJ_DispProperty().getTarget_Obj().getOBJ_ID();
    desValue._OBJ_DispProperty._Target_Obj._ObjBarDisp =
        srcValue.getOBJ_DispProperty().getTarget_Obj().getObjBarDisp().value_;

    desValue._OBJ_DispProperty._Left_Target_Obj._OBJ_ID =
        srcValue.getOBJ_DispProperty().getLeft_Target_Obj().getOBJ_ID();
    desValue._OBJ_DispProperty._Left_Target_Obj._ObjBarDisp =
        srcValue.getOBJ_DispProperty().getLeft_Target_Obj().getObjBarDisp().value_;

    desValue._OBJ_DispProperty._Right_Target_Obj._OBJ_ID =
        srcValue.getOBJ_DispProperty().getRight_Target_Obj().getOBJ_ID();
    desValue._OBJ_DispProperty._Right_Target_Obj._ObjBarDisp =
        srcValue.getOBJ_DispProperty().getRight_Target_Obj().getObjBarDisp().value_;

    desValue._OBJ_DispProperty._Target_Obj_2._OBJ_ID = srcValue.getOBJ_DispProperty().getTarget_Obj_2().getOBJ_ID();
    desValue._OBJ_DispProperty._Target_Obj_2._ObjBarDisp =
        srcValue.getOBJ_DispProperty().getTarget_Obj_2().getObjBarDisp().value_;

    desValue._OBJ_DispProperty._Left_Target_Obj_2._OBJ_ID =
        srcValue.getOBJ_DispProperty().getLeft_Target_Obj_2().getOBJ_ID();
    desValue._OBJ_DispProperty._Left_Target_Obj_2._ObjBarDisp =
        srcValue.getOBJ_DispProperty().getLeft_Target_Obj_2().getObjBarDisp().value_;

    desValue._OBJ_DispProperty._Right_Target_Obj_2._OBJ_ID =
        srcValue.getOBJ_DispProperty().getRight_Target_Obj_2().getOBJ_ID();
    desValue._OBJ_DispProperty._Right_Target_Obj_2._ObjBarDisp =
        srcValue.getOBJ_DispProperty().getRight_Target_Obj_2().getObjBarDisp().value_;

    desValue._OBJ_DispProperty._Target_Obj_3._OBJ_ID = srcValue.getOBJ_DispProperty().getTarget_Obj_3().getOBJ_ID();
    desValue._OBJ_DispProperty._Target_Obj_3._ObjBarDisp =
        srcValue.getOBJ_DispProperty().getTarget_Obj_3().getObjBarDisp().value_;

    desValue._OBJ_DispProperty._Left_Target_Obj_3._OBJ_ID =
        srcValue.getOBJ_DispProperty().getLeft_Target_Obj_3().getOBJ_ID();
    desValue._OBJ_DispProperty._Left_Target_Obj_3._ObjBarDisp =
        srcValue.getOBJ_DispProperty().getLeft_Target_Obj_3().getObjBarDisp().value_;

    desValue._OBJ_DispProperty._Right_Target_Obj_3._OBJ_ID =
        srcValue.getOBJ_DispProperty().getRight_Target_Obj_3().getOBJ_ID();
    desValue._OBJ_DispProperty._Right_Target_Obj_3._ObjBarDisp =
        srcValue.getOBJ_DispProperty().getRight_Target_Obj_3().getObjBarDisp().value_;
}

void listener_init_(char *appName, char *configFile)
{
    LOGI("listener_init_: enter,appName = %s configFile = %s", appName, configFile);
    setenv("VSOMEIP_CONFIGURATION", configFile, 1);
    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();
    systemFunctionsProxy = runtime->buildProxy<IDC_L2SystemFunctionsProxy>("local", "IDC_L2SystemFunctions01", appName);
}
bool listenerIsReady()
{
    if (systemFunctionsProxy == nullptr)
    {
        LOGE("listenerIsReady systemFunctionsProxy is null");
        return false;
    }
    bool ret = systemFunctionsProxy->isAvailable();
    LOGI("listenerIsReady: %d", ret);
    return ret;
}
void setListener_(Listener *listener)
{
    LOGD("setListener_");
    if (nullptr != globalListener)
    {
        delete globalListener;
        globalListener = nullptr;
    }
    if (nullptr == listener)
    {
        LOGE("setListener_: globalListener is null.");
        return;
    }
    globalListener = listener;
    // IDC_L2SystemFunctions
    systemFunctionsProxy->getLocationInfoDataAttribute().getChangedEvent().subscribe(
        [&](const IDC_L2SystemFunctions::LocationInfoStruct &value)
        {
            Listener::LocationInfoStruct myStruct;
            LocationInfoStruct_Convert(myStruct, value);
            globalListener->LocationInfoStructOnChange(myStruct);
        },
        [&](const CommonAPI::CallStatus &cs)
        {
            std::cout << "systemFunctionsProxy::LocationInfoData.subscribe error: " << static_cast<int>(cs)
                      << std::endl;
        });
    systemFunctionsProxy->getOBJPptyInfoDataAttribute().getChangedEvent().subscribe(
        [&](const IDC_L2SystemFunctions::OBJPptyInfoStruct &value)
        {
            Listener::OBJPptyInfoStruct myStruct;
            OBJPptyInfoStruct_Convert(myStruct, value);
            globalListener->OBJPptyInfoStructOnChange(myStruct);
        },
        [&](const CommonAPI::CallStatus &cs)
        {
            std::cout << "systemFunctionsProxy::OBJPptyInfoData.subscribe error: " << static_cast<int>(cs) << std::endl;
        });
}

void ADASDisplayInformationInit(char *appName, char *configFile)
{
    LOGI("ADASDisplayInformationInit: enter,appName = %s configFile = %s", appName, configFile);
    if (configFile)
    {
        setenv("VSOMEIP_CONFIGURATION", configFile, 1);
    }
    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();
    gADASDisplayInformationProxy =
        runtime->buildProxy<ADASDisplayInformationProxy>("local", "ADASDisplayInformation01", appName);
    std::string versionInfo = runtime->get_version();
    std::string version = versionInfo.substr(versionInfo.rfind(" ") + 1);

    LOGD("ADASDisplayInformationInit: appName = %s version = %s", appName, version.c_str());
    __system_property_set("vendor.gwm.someip.version", version.c_str());
}

bool ADASDisplayInformationIsReady()
{
    if (nullptr == gADASDisplayInformationProxy)
    {
        LOGE("ADASDisplayInformationIsReady gADASDisplayInformationProxy is null");
        return false;
    }
    bool ret = gADASDisplayInformationProxy->isAvailable();
    LOGI("ADASDisplayInformationIsReady: %d", ret);
    return ret;
}

void ADASDisplayInformationListenerRegister(ADASDisplayInformationListener *listener)
{
    if (nullptr != gADASDisplayInformationListener)
    {
        delete gADASDisplayInformationListener;
        gADASDisplayInformationListener = nullptr;
    }
    LOGI("ADASDisplayInformationListenerRegister: enter");
    if (nullptr == listener)
    {
        LOGE("ADASDisplayInformationListenerRegister: gADASDisplayInformationListener is null.");
        return;
    }
    gADASDisplayInformationListener = listener;
    gADASDisplayInformationProxy->getGuideLineCoordinateEvent().subscribe(
        [&](const ADASDisplayInformation::Guide_Line_Points_Array array)
        {
            ADASDisplayInformationListener::Guide_Line_Points_ArrayOut out;
            out.len = array.size();

            for (int i = 0; i < array.size(); i++)
            {
                ADASDisplayInformationListener::Guide_Line_PointStruct_DT desStruct;
                desStruct.guide_Line_Point_xDt = array[i].getGuide_Line_Point_x();
                desStruct.guide_Line_Point_yDt = array[i].getGuide_Line_Point_y();
                out.dynamicArray.push_back(desStruct);
            }
            LOGD("Guide_Line_Points_Array: out.len:%d,%p", out.len,
                 gADASDisplayInformationListener);
            gADASDisplayInformationListener->GuideLineCoordinateEventListener(
                out);
        },
        [&](const CommonAPI::CallStatus &cs)
        {
            std::cout << "gADASDisplayInformationListener::Guide_Line_Points_"
                         "Array.subscribe error: "
                      << static_cast<int>(cs) << std::endl;
        });
    gADASDisplayInformationProxy->getLocationDispEvent().subscribe(
        [&](const ADASDisplayInformation::LaneChangeZone laneChangeZone)
        {
            ADASDisplayInformationListener::LaneChangeZone_DT laneChangeZoneDt;
            laneChangeZoneDt =
                static_cast<ADASDisplayInformationListener::LaneChangeZone_DT>(
                    laneChangeZone.value_);
            LOGD("laneChangeZoneDt = %d", laneChangeZoneDt);
            gADASDisplayInformationListener->LocationDispEventListener(
                laneChangeZoneDt);
        },
        [&](const CommonAPI::CallStatus &cs)
        {
            std::cout << "gADASDisplayInformationListener::getLocationDispEvent."
                         "subscribe error: "
                      << static_cast<int>(cs) << std::endl;
        });
}

void navigationMap_init(char *appName, char *configFile)
{
    LOGI("navigationMap_init: enter,appName = %s configFile = %s", appName, configFile);
    if (configFile)
    {
        setenv("VSOMEIP_CONFIGURATION", configFile, 1);
    }
    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();
    gNavigationMapInformationProxy = runtime->buildProxy<v1::GREATWALL::MDC_A_IDC3_0::NavigationMapInformationProxy>(
        "local", "NavigationMapInformation01", appName);
    std::string versionInfo = runtime->get_version();
    std::string version = versionInfo.substr(versionInfo.rfind(" ") + 1);

    LOGD("navigationMap_init: appName = %s version = %s", appName, version.c_str());
    __system_property_set("vendor.gwm.someip.version", version.c_str());
}

bool navigationMapIsReady()
{
    if (nullptr == gNavigationMapInformationProxy)
    {
        LOGE("navigationMapIsReady gNavigationMapInformationProxy is null");
        return false;
    }
    bool ret = gNavigationMapInformationProxy->isAvailable();
    LOGI("navigationMapIsReady: %d", ret);
    return ret;
}
CallStatus_DT navPathInfoReq(const char *_SDRoute)
{
    CommonAPI::CallStatus callStatus = CommonAPI::CallStatus::UNKNOWN;
    if (nullptr != gNavigationMapInformationProxy)
    {
        std::string temp_Route = _SDRoute;
        gNavigationMapInformationProxy->NavPathInfoReq(temp_Route, callStatus);
    }
    LOGI("navPathInfoReq: CallStatus = %d ", callStatus);
    return static_cast<CallStatus_DT>(callStatus);
}