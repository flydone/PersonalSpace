/*************************************************************************
 * Copyright (C) 2022 GWM Automotive Inc.
 *
 * The copyright notice above does not evidence any actual
 * or intended publication of such source code.
 * The code contains GWM Confidential Proprietary Information.
 *************************************************************************/
//
// Created by Zeng weifeng on 2022/2/14.
//

#ifndef SOMEIPTEST_HAVPANDAVP_FUNCTIONS_H
#define SOMEIPTEST_HAVPANDAVP_FUNCTIONS_H

#include "public_def.h"

typedef __uint8_t MapBuildProcBar;
typedef __uint8_t ActualPrkgArea;
typedef __uint8_t CurrLeavingPOI;
typedef __int8_t ActualMapFlr;
typedef __uint8_t SetLvngPOI;
typedef __int8_t SetMapFlr;
typedef __uint8_t SelNearSlotID;
typedef __uint8_t SetPrkgArea;
typedef __uint16_t CurrMAPID;
typedef __uint16_t ActualPrkgSlot;
typedef __uint16_t TarMapID;
typedef __uint16_t SetPrkgSlot;

typedef enum {
    E_NO_REQUEST_SVPFUNCTIONREQ = 0,
    E_REQUEST_SVPFUNCTIONREQ = 1
}SVPfunctionReq;

typedef enum {
    E_NONE_BTNENAREQ = 0,
    E_CONTINUE_SEARCH_SLOT = 1,
    E_ACTIVE_SIGNAL = 2,
    E_START_HAVP_VR = 3,
    E_CONFRIM_MAPBUILT = 4,
    E_CANCEL = 5,
    E_CONFRIM_START_PARKING = 6,
    E_SEARCH_SLOT_ALONG_WAY_BTNENAREQ = 7,
    E_HAVP_COMPLETED = 8,
    E_TRY_BTNENAREQ = 9,
    E_LEARNING_COMPLETED = 10,
    E_CONTINUE_LEARN = 11,
    E_START_SVP_VR = 12
}BtnEnaReq;

typedef enum {
    E_NONE_MAPUPDST = 0,
    E_UNSUCCESS = 1,
    E_UPDATE_SUCCESS = 2,
    E_UPDATING = 3
}MapUpdSt;

typedef enum {
    E_UNAVAILABLE_FUNCTBTNSTS = 0,
    E_AVAILABLE_FUNCTBTNSTS = 1,
    E_HIGHLIGHT = 2
}FunctBtnSts;

typedef enum {
    E_NO_SET_ACTUALPRKGSLOTTYP = 0,
    E_SET_PRKING_SLOT_ACTUALPRKGSLOTTYP = 1,
    E_SET_PRKING_SLOT_AREA_ACTUALPRKGSLOTTYP = 2,
    E_RANDOM_ACTUALPRKGSLOTTYP = 3
}ActualPrkgSlotTyp;

typedef enum {
    E_NONE_SVPFUNCTTEXTDISP = 0,
    E_PLEASE_CONFIRM_FINAL_POSITION_CLICK_START = 1,
    E_RELEASE_THE_BRAKES_AND_WE_SET_OFF_SVPFUNCTTEXTDISP = 2,
    E_DRIVE_TO_YOUR_TERMINAL_SLOT_SVPFUNCTTEXTDISP = 3,
    E_DRIVE_TO_YOUR_TERMINAL_EXIT_SVPFUNCTTEXTDISP = 4,
    E_PARK_IN_CRUISING_SVPFUNCTTEXTDISP = 5,
    E_TURN_LEFT_SVPFUNCTTEXTDISP = 6,
    E_TURN_RIGHT_SVPFUNCTTEXTDISP = 7,
    E_CROSSING_SVPFUNCTTEXTDISP = 8,
    E_NARROW_ROAD_SVPFUNCTTEXTDISP = 9,
    E_ROAD_DIFFICULT_HELP_ME_DRIVE_SVPFUNCTTEXTDISP = 10,
    E_INTO_THE_RAMP = 11,
    E_OUT_OF_THE_RAMP = 12,
    E_WAIT_FOR_THE_CAR_AHEAD_SVPFUNCTTEXTDISP = 13,
    E_GO_AROUND_THE_VEHICLE_AHEAD_SVPFUNCTTEXTDISP = 14,
    E_THE_REAR_VEHICLE_FOLLOW_SVPFUNCTTEXTDISP = 15,
    E_THE_REAR_VEHICLE_SVPFUNCTTEXTDISP = 16,
    E_PEDESTRIAN_SVPFUNCTTEXTDISP = 17,
    E_PEDESTRIAN_CROSSING_SVPFUNCTTEXTDISP = 18,
    E_AVOID_NEARBY_OBSTACLES_SVPFUNCTTEXTDISP = 19,
    E_ARRIVING_YOUR_SLOT_SVPFUNCTTEXTDISP = 20,
    E_PARK_IN_PARKING_SVPFUNCTTEXTDISP = 21,
    E_ENGINE_HOOD_OPEN = 22,
    E_TRUNK_OPEN = 23,
    E_DOOR_OPEN = 24,
    E_REARVIEW_MIRROR_FOLD = 25,
    E_SEAT_BELT_LOOSEN = 26,
    E_DRIVE_NOT_INSIDE_SVPFUNCTTEXTDISP = 27,
    E_TIMEOUT_SVPFUNCTTEXTDISP = 28,
    E_STATISTIC_OBSTACLE_30S_SVPFUNCTTEXTDISP = 29,
    E_TARGET_SLOT_OCCUPIED_PLOT_AVAILABLE_NEARBY_SVPFUNCTTEXTDISP = 30,
    E_POSITIONING_UNSUCCESSFUL_SVPFUNCTTEXTDISP = 31,
    E_ILLUMINATION_CONDITIONS = 32,
    E_RAINING_CONDITIONS = 33,
    E_SVP_FAILURE = 34,
    E_ASSOCIATED_SYSTEM_FAILURE = 35,
    E_CRUSING_TIME_OUT_SVPFUNCTTEXTDISP = 36,
    E_PARKING_TIME_OUT_SVPFUNCTTEXTDISP = 37,
    E_NUMBER_OF_PAUSES_EXCEEDED_SVPFUNCTTEXTDISP = 38,
    E_VEHICLE_RANGE_TOO_LOW_SVPFUNCTTEXTDISP = 39,
    E_RCTB_FCTB_ACTIVATION = 40,
    E_AEB_ACTIVATION = 41,
    E_ESP_ACTIVATION = 42,
    E_TCS_ABS_ACTIVATION = 43,
    E_HDC_ACTIVATION = 44,
    E_TIRE_PRESSURE_IS_TOO_LOW_SVPFUNCTTEXTDISP = 45,
    E_TARGET_SLOT_OCCUPIED_NO_SLOT_NEARBY_SVPFUNCTTEXTDISP = 46,
    E_PHONE_DISCONNECTED = 47,
    E_VIDEO_MONITOR_ABNORMAL = 48,
    E_REMOTE_DEVICE_ERROR = 49,
    E_OBSTACLE_TIMEOUT = 50,
    E_PARKINGIN_FAILURE_SVPFUNCTTEXTDISP = 51,
    E_ROUTE_MATCHING_TIMEOUT_SVPFUNCTTEXTDISP = 52,
    E_ACTIVATION_FAILED_SVPFUNCTTEXTDISP = 53,
    E_CAMERA_BLOCKED = 54,
    E_THE_LOOP_CAMERA_FAULTY = 55,
    E_RADAR_FAULTY = 56,
    E_BERTH_IN_COMPLETE_SVPFUNCTTEXTDISP = 57,
    E_BERTH_OUT_COMPLETE_SVPFUNCTTEXTDISP = 58,
    E_PULL_UP_EPB_SVPFUNCTTEXTDISP = 59,
    E_GEAR_INTERVENE_SVPFUNCTTEXTDISP = 60,
    E_STEERING_INTERVENE_SVPFUNCTTEXTDISP = 61,
    E_BRAKE_INTERVENE_SVPFUNCTTEXTDISP = 62,
    E_CRUSING_USER_EXIT_SVPFUNCTTEXTDISP = 63,
    E_CRUSING_EXCESSIVE_SLOPE_SVPFUNCTTEXTDISP = 64,
    E_VEHICLE_BACK_SVPFUNCTTEXTDISP = 65,
    E_HANDS_OFF_THE_STEERING_WHEEL_SVPFUNCTTEXTDISP = 66,
    E_DRIVING_MODE_NOT_SUPPORTED_SVPFUNCTTEXTDISP = 67,
    E_GO_AROUND_NEARBY_OBSTACLES_SVPFUNCTTEXTDISP = 68,
    E_GO_AROUND_THE_COMING_VEHICLE_SVPFUNCTTEXTDISP = 69,
    E_RELEASE_THE_BRAKE_PARKING_START_SVPFUNCTTEXTDISP = 70,
    E_AUTO_PARKING_BE_READY_TO_BRAKE_SVPFUNCTTEXTDISP = 71,
    E_PAY_ATTENTION_TO_THE_RISK_OF_SCRATCHES_SVPFUNCTTEXTDISP = 72,
    E_DETECTING_PARKING_SPACE_SVPFUNCTTEXTDISP = 73,
    E_PARKING_SUSPENDED_CLOSE_TRUNK_SVPFUNCTTEXTDISP = 74,
    E_PARKING_SUSPENDED_CLOSE_DOOR_SVPFUNCTTEXTDISP = 75,
    E_PARKING_SUSPENDED_FASTEN_SEAT_BELT_SVPFUNCTTEXTDISP = 76,
    E_PARKING_SUSPENDED_FOLD_THE_MIRROR_SVPFUNCTTEXTDISP = 77,
    E_PARKING_SUSPENDED_CLOSE_CABIN_COVER_SVPFUNCTTEXTDISP = 78,
    E_PARKING_SUSPENDED_OBSTACLES_DETECTED_SVPFUNCTTEXTDISP = 79,
    E_PARKING_SUSPENDED_PEDESTRIAN_DETECTED_SVPFUNCTTEXTDISP = 80,
    E_PARKING_SUSPENDED_VEHICLE_DETECTED_SVPFUNCTTEXTDISP = 81,
    E_PARKING_CONTINUES_SVPFUNCTTEXTDISP = 82,
    E_BRAKE_RECOVERED_CONFIRM_TO_CONTINUE_SVPFUNCTTEXTDISP = 83,
    E_CRUSING_SPEED_TOO_HIGH_SVPFUNCTTEXTDISP = 84,
    E_PARKING_SUSPENDED_PLEASE_RELEASE_THE_BREAK_PEDAL_CRUSING_SPEED_TOO_HIGH_SVPFUNCTTEXTDISP = 85,
    E_PARKING_SUSPENDED_PLEASE_RELEASE_THE_ACCELERATOR_PEDAL_SVPFUNCTTEXTDISP = 86,
    E_PLEASE_KEEP_BRAKING_SVPFUNCTTEXTDISP = 87
}SVPFunctTextDisp;

typedef enum  {
    E_NO_REQUEST_MAPUPDATEREQ = 0,
    E_REQUEST_MAPUPDATEREQ = 1
}MapUpdateReq;

typedef enum {
    E_OFF_SVPFUNCTIONSTS = 0,
    E_ON_SVPFUNCTIONSTS = 1
}SVPfunctionSts;
typedef enum {
    E_NO_DISPLAY_STARTPRKBTNDISP = 0,
    E_AVAILABLE_STARTPRKBTNDISP = 1,
    E_UNAVAILABLE_STARTPRKBTNDISP = 2
}StartPrkBtnDisp;
typedef enum {
    E_NONE = 0,
    E_START_LEARNING = 1,
    E_LEARN_ROUTE_CONFIRM = 2,
    E_TURN_ON_BACKGROUND_FUNCTIONS = 3,
    E_PLEASE_ADJUST_UNDER_P = 4,
    E_HAVP_RAMPWAY = 5,
    E_HAVP_ENVIRONMENT_EMPTY = 6,
    E_OUTSIDE_THE_UNDERGROUND_CAR_PARK = 7,
    E_HAVP_CAMERA_BLOCKED = 8,
    E_HAVP_LOOP_CAMERA_FAULTY = 9,
    E_HAVP_RADAR_FAULTY = 10,
    E_HAVP_ASSOCIATED_SYSTEM_FAULTY = 11,
    E_HAVP_SYSTEM_FAULTY = 12,
    E_HAVP_DOOR_OPEN = 13,
    E_HAVP_REAR_DOOR_OPEN = 14,
    E_HAVP_SAFETY_BELT_UNFASTENED = 15,
    E_HAVP_ENGINE_COVER_OPEN = 16,
    E_HAVP_RCTB_FCTB_ACTIVATION = 17,
    E_HAVP_AEB_ACTIVATION = 18,
    E_HAVP_TCS_ABS_ACTIVATION = 19,
    E_HAVP_ESP_ACTIVATION = 20,
    E_HAVP_HDC_ACTIVATION = 21,
    E_HAVP_TIRE_PRESSURE_IS_TOO_LOW = 22,
    E_HAVP_ILLUMINATION_CONDITIONS = 23,
    E_HAVP_RAINING_CONDITIONS = 24,
    E_CLICK_FINISH = 25,
    E_THE_LEARNING_ROUTE_IS_NOT_LOCATED = 26,
    E_PLEASE_SWITCH_TO_D_GEAR = 27,
    E_HAVP_PUSH_REQUEST_MAP_BUILDING = 28,
    E_HAVP_PUSH_REQUEST_ROUTE_REPLAY = 29,
    E_SVP_PUSH_REQUEST = 30,
    E_ACCELERATOR_PEDAL = 31,
    E_TAKE_OVER_IMMEDIATELY = 32,
    E_REQUEST_STOP = 33,
    E_SVP_REQUEST_CLOSE_ENGINE_HOOD = 34,
    E_SVP_REQUEST_CLOSE_TRUNK = 35,
    E_SVP_REQUEST_UNFOLD_REARVIEW_MIRROR = 36,
    E_SVP_REQUEST_CLOSE_DOOR = 37,
    E_SVP_REQUEST_FASTEN_SEATBELT = 38,
    E_SVP_RCTB_FCTB_ACTIVATION = 39,
    E_SVP_AEB_ACTIVATION = 40,
    E_SVP_TCS_ABS_ACTIVATION = 41,
    E_SVP_ESP_ACTIVATION = 42,
    E_SVP_HDC_ACTIVATION = 43,
    E_SVP_TIRE_PRESSURE_IS_TOO_LOW = 44,
    E_SVP_ILLUMINATION_CONDITIONS = 45,
    E_SVP_RAINING_CONDITIONS = 46,
    E_EXCESSIVE_SLOPE_POPUPDISP = 47,
    E_SVP_VEHICLE_RANGE_TOO_LOW = 48,
    E_SVP_CAMERA_BLOCKED = 49,
    E_SVP_THE_LOOP_CAMERA_FAULTY = 50,
    E_SVP_RADAR = 51,
    E_SVP_ASSOCIATED_SYSTEM_FAULTY = 52,
    E_SVP_SYSTEM_FAULTY = 53,
    E_NEED_UPDATE = 54,
    E_MAP_UPDATING = 55,
    E_MAP_UPDATE_SUCCESS = 56,
    E_MAP_UPDATE_FAIL = 57,
    E_SVP_TURN_ON_BACKGROUND_FUNCTIONS = 58,
    E_HAVP_DRIVING_MODE_NOT_SUPPORTED = 59,
    E_SVP_DRIVING_MODE_NOT_SUPPORTED = 60,
    E_HAVP_REARVIEW_MIRROR_FOLDED = 61
}PopupDisp;

typedef enum {
     E_NONE_HAVPFUNCTTEXTDISP = 0,
    E_START_PARKING_IN = 1,
    E_ROUTE_LEARNING = 2,
    E_PLEASE_SELECT_SLOT_USE_AUTOMATIC_PARKING_AFTER_BRAKING = 3,
    E_PLEASE_USE_AUTOMATIC_PARKING_AFTER_BRAKING = 4,
    E_POUR_INTO_YOUR_PARKING_SLOT = 5,
    E_SPEED_BUMP = 6,
    E_EXCEEDS_DISTANCE = 7,
    E_LEARNING_INTO_THE_RAMP = 8,
    E_LEARNING_OFF_THE_RAMP = 9,
    E_START_PARKING_OUT = 10,
    E_ROUTE_LEARNING_PARKING_OUT = 11,
    E_FOLLOW_INSTRUCTIONS = 12,
    E_LEARNING_CAMERA_BLOCKED = 13,
    E_LEARNING_THE_LOOP_CAMERA_FAULTY = 14,
    E_LEARNING_RADAR_FAULTY = 15,
    E_LEARNING_ASSOCIATED_SYSTEM_FAULTY = 16,
    E_LEARNING_SYSTEM_FAULTY = 17,
    E_LEARNING_ILLUMINATION_CONDITIONS = 18,
    E_LEARNING_RAINING_CONDITIONS = 19,
    E_LEARNING_ENVIRONMENT_TOO_EMPTY = 20,
    E_ROUTE_REPEAT = 21,
    E_EXCESSIVE_SLOPE = 22,
    E_TIME_OUT = 23,
    E_DISTANCE_TOO_LONG = 24,
    E_SPEED_OVER_15 = 25,
    E_SPEED_TOO_HIGH = 26,
    E_LEARNING_USER_EXIT = 27,
    E_LEARNING_DOOR_OPEN = 28,
    E_LEARNING_REAR_DOOR_OPEN = 29,
    E_LEARNING_REARVIEW_MIRROR_FOLDED = 30,
    E_LEARNING_LOOSEN_SEAT_BELT = 31,
    E_BACKWARD = 32,
    E_BACKWARD_EXIT = 33,
    E_MAP_BUILDING = 34,
    E_NOT_IN_SLOT = 35,
    E_TAIL_IN_SLOT = 36,
    E_MAP_BUILD_SUCCESS = 37,
    E_MAP_BUILD_FAIL = 38,
    E_INSUFFICIENT_STORAGE_SPACE = 39,
    E_DISTANCE_TOO_SHORT = 40,
    E_HAVP_READY_TO_START = 41,
    E_KEEP_GOING = 42,
    E_RELEASE_THE_BRAKES_AND_WE_SET_OFF = 43,
    E_DRIVE_TO_YOUR_TERMINAL_SLOT = 44,
    E_DRIVE_TO_YOUR_TERMINAL_EXIT = 45,
    E_PARK_IN_CRUISING = 46,
    E_TURN_LEFT = 47,
    E_TURN_RIGHT = 48,
    E_CROSSING = 49,
    E_NARROW_ROAD = 50,
    E_ROAD_DIFFICULT_HELP_ME_DRIVE = 51,
    E_CRUSING_INTO_THE_RAMP = 52,
    E_CRUSING_OUT_OF_THE_RAMP = 53,
    E_WAIT_FOR_THE_CAR_AHEAD = 54,
    E_GO_AROUND_THE_VEHICLE_AHEAD = 55,
    E_THE_REAR_VEHICLE_FOLLOW = 56,
    E_THE_REAR_VEHICLE = 57,
    E_PEDESTRIAN = 58,
    E_PEDESTRIAN_CROSSING = 59,
    E_AVOID_NEARBY_OBSTACLES = 60,
    E_ARRIVING_YOUR_SLOT = 61,
    E_PARK_IN_PARKING = 62,
    E_CRUSING_ENGINE_HOOD_OPEN = 63,
    E_CRUSING_TRUNK_OPEN = 64,
    E_CRUSING_DOOR_OPEN = 65,
    E_CRUSING_REARVIEW_MIRROR_FOLD = 66,
    E_CRUSING_SEAT_BELT_LOOSEN = 67,
    E_DRIVE_NOT_INSIDE = 68,
    E_TIMEOUT = 69,
    E_STATISTIC_OBSTACLE_30S = 70,
    E_TARGET_SLOT_OCCUPIED_PLOT_AVAILABLE_NEARBY = 71,
    E_POSITIONING_UNSUCCESSFUL = 72,
    E_CRUSING_ILLUMINATION_CONDITIONS = 73,
    E_CRUSING_RAINING_CONDITIONS = 74,
    E_CRUSING_LVP_FAILURE = 75,
    E_CRUSING_ASSOCIATED_SYSTEM_FAILURE = 76,
    E_CRUSING_TIME_OUT = 77,
    E_PARKING_TIME_OUT = 78,
    E_NUMBER_OF_PAUSES_EXCEEDED = 79,
    E_VEHICLE_RANGE_TOO_LOW = 80,
    E_CRUSING_RCTB_FCTB_ACTIVATION = 81,
    E_CRUSING_AEB_ACTIVATION = 82,
    E_CRUSING_ESP_ACTIVATION = 83,
    E_CRUSING_TCS_ABS_ACTIVATION = 84,
    E_CRUSING_HDC_ACTIVATION = 85,
    E_TIRE_PRESSURE_IS_TOO_LOW = 86,
    E_TARGET_SLOT_OCCUPIED_NO_SLOT_NEARBY = 87,
    E_PARKINGIN_FAILURE = 88,
    E_ROUTE_MATCHING_TIMEOUT = 89,
    E_ACTIVATION_FAILED = 90,
    E_CRUISING_CAMERA_BLOCKED = 91,
    E_CRUISING_THE_LOOP_CAMERA_FAULTY = 92,
    E_CRUISING_RADAR_FAULTY = 93,
    E_SEARCH_SLOT_ALONG_WAY = 94,
    E_BERTH_IN_COMPLETE = 95,
    E_BERTH_OUT_COMPLETE = 96,
    E_PULL_UP_EPB = 97,
    E_GEAR_INTERVENE = 98,
    E_STEERING_INTERVENE = 99,
    E_BRAKE_INTERVENE = 100,
    E_CRUSING_USER_EXIT = 101,
    E_CRUSING_EXCESSIVE_SLOPE = 102,
    E_CRUSING_SPEED_TOO_HIGH = 103,
    E_VEHICLE_BACK = 104,
    E_HANDS_OFF_THE_STEERING_WHEEL = 105,
    E_DRIVING_MODE_NOT_SUPPORTED = 106,
    E_PARKING_QUIT_PARKING_SLOT_BY_YOURSELF = 107,
    E_GO_AROUND_NEARBY_OBSTACLES = 108,
    E_GO_AROUND_THE_COMING_VEHICLE = 109,
    E_RELEASE_THE_BRAKE_PARKING_START = 110,
    E_AUTO_PARKING_BE_READY_TO_BRAKE = 111,
    E_PAY_ATTENTION_TO_THE_RISK_OF_SCRATCHES = 112,
    E_DETECTING_PARKING_SPACE = 113,
    E_PARKING_SUSPENDED_CLOSE_TRUNK = 114,
    E_PARKING_SUSPENDED_CLOSE_DOOR = 115,
    E_PARKING_SUSPENDED_FASTEN_SEAT_BELT = 116,
    E_PARKING_SUSPENDED_FOLD_THE_MIRROR = 117,
    E_PARKING_SUSPENDED_CLOSE_CABIN_COVER = 118,
    E_PARKING_SUSPENDED_OBSTACLES_DETECTED = 119,
    E_PARKING_SUSPENDED_PEDESTRIAN_DETECTED = 120,
    E_PARKING_SUSPENDED_VEHICLE_DETECTED = 121,
    E_PARKING_CONTINUES = 122,
    E_BRAKE_RECOVERED_CONFIRM_TO_CONTINUE = 123,
    E_PARKING_SUSPENDED_PLEASE_RELEASE_THE_BREAK_PEDAL = 124,
    E_PARKING_SUSPENDED_PLEASE_RELEASE_THE_ACCELERATOR_PEDAL = 125,
    E_FINDING_SLOT_PLEASE_BRAKE = 126,
    E_ENGINE_HOOD_OPEN_HAVPFUNCTeXTDISP = 127,
    E_PLEASE_KEEP_BRAKING = 128,
    E_MATCH_SUCCESSFUL_START_HAVP = 129
}HAVPFunctTextDisp;

typedef enum {
    E_NONE_FUNCTBTNDISP = 0,
    E_START_HAVP = 1,
    E_CONTINUE_HAVP = 2,
    E_START_SVP = 3,
    E_CONTINUE_SVP = 4,
    E_START_APA = 5,
    E_TRY = 6,
    E_SEARCH_SLOT_ALONG_WAY_FUNCTBTNDISP = 7,
    E_APA_CONTINUESEARCHSLOT = 8
}FunctBtnDisp;

typedef enum {
    E_NO_DISPLAY_UPDATEROUTEBTNDISP = 0,
    E_AVAILABLE_UPDATEROUTEBTNDISP = 1,
    E_UNAVAILABLE_UPDATEROUTEBTNDISP = 2
}UpdateRouteBtnDisp;

typedef enum {
    E_OFF_AUTOPUSHSTS = 0,
    E_ON_AUTOPUSHSTS = 1
}AutoPushSts;

typedef enum {
    E_STANDBY = 0,
    E_MAPBUILDING = 1,
    E_MAPBUILT_COMPLETE = 2,
    E_CRUISE = 3,
    E_FAILURE = 4,
    E_PAUSE = 5,
    E_PARKING = 6,
    E_COMPLETE = 7,
    E_FAULT = 8
}FunctWorkSts;

typedef enum {
    E_NO_RESPONSE = 0,
    E_RESPONSE = 1
}BtnEnaAck;

typedef enum {
    E_NO_DISPLAY_GUIDANCESTS = 0,
    E_NO_COMPLETE = 1,
    E_COMPLETE1 = 2,
    E_COMPLETE2 = 3,
    E_COMPLETE3 = 4
}GuidanceSts;

typedef enum {
    E_CAN = 0,
    E_SOMEIP = 1
}Signal_Indnc;

typedef enum {
    E_OFF_HAVPFUNCTIONSTS = 0,
    E_ON_HAVPFUNCTIONSTS = 1
}HAVPfunctionSts;

typedef enum {
    E_NONE_INTERFACEDISTYP = 0,
    E_PRE_MAPBUILT = 1,
    E_MAPBUILTING = 2,
    E_CRUISE_INTERFACEDISTYP = 3,
    E_MAPBUILT_COMPLETE_INTERFACEDISTYP = 4,
    E_HAVP_COMPLETED_INTERFACEDISTYP = 5,
    E_MAPSHOWTOSTART = 6,
    E_GUIDANCE = 7,
    E_SELECTSLOT_3D = 8,
    E_CRUISE_3D = 9,
    E_CHOOSE_EXIT = 10,
    E_CRUISE_EXIT = 11
}InterfaceDisTyp;

typedef enum {
    E_OFF_AVMSTSREQ = 0,
    E_ON_AVMSTSREQ = 1
}AVMStsReq;

typedef enum {
    E_NO_SET = 0,
    E_SET_PRKING_SLOT = 1,
    E_SET_PRKING_SLOT_AREA = 2,
    E_RANDOM = 3
}SetPrkgSlotTyp;

typedef enum {
    E_NO_REQUEST_AUTOPUSHREQ = 0,
    E_REQUEST_AUTOPUSHREQ = 1
}AutoPushReq;

typedef enum {
    E_OFF_AVMSTSRESP = 0,
    E_ON_AVMSTSRESP = 1
}AVMStsResp;

typedef enum {
    SUCCESS,
    OUT_OF_MEMORY,
    NOT_AVAILABLE,
    CONNECTION_FAILED,
    REMOTE_ERROR,
    UNKNOWN,
    INVALID_VALUE,
    SUBSCRIPTION_REFUSED
}CallStatus;

typedef enum {
    E_NO_REQUEST_HAVPFUNCTIONREQ = 0,
    E_REQUEST_HAVPFUNCTIONREQ = 1
}HAVPfunctionReq;

typedef enum {
    E_REQUEST_SIDEBSDDISPREQUEST = 0
}SideBsdDispRequest;

typedef enum {
    E_OFF_SIDEBSDDISPSTS = 0,
    E_ON_SIDEBSDDISPSTS = 1
}SideBsdDispSts;

typedef enum {
    E_OFF_SIDEBSDDISPSTATUS = 0,
    E_ON_SIDEBSDDISPSTATUS = 1
}SideBsdDispStatus;

struct SideBsdDispStsOut{
    SideBsdDispSts sideBsdDispSts;
};

struct HAVP_SVPScrnInfoStruct {
    MapUpdateReq MapUpdateReq;
    CurrMAPID CurrMAPID;
    FunctBtnDisp FunctBtnDisp;
    FunctBtnSts FunctBtnSts;
    FunctWorkSts FunctWorkSts;
    Signal_Indnc Signal_Indnc;
    InterfaceDisTyp InterfaceDisTyp;
    PopupDisp PopupDisp;
    MapBuildProcBar MapBuildProcBar;
    StartPrkBtnDisp StartPrkBtnDisp;
    UpdateRouteBtnDisp UpdateRouteBtnDisp;
    GuidanceSts GuidanceSts;
    ActualMapFlr ActualMapFlr;
    CurrLeavingPOI CurrLeavingPOI;
    ActualPrkgSlotTyp ActualPrkgSlotTyp;
    ActualPrkgSlot ActualPrkgSlot;
    ActualPrkgArea ActualPrkgArea;
    HAVPFunctTextDisp HAVPFunctTextDisp;
    SVPFunctTextDisp SVPFunctTextDisp;
    BtnEnaAck BtnEnaAck;
    HAVPfunctionSts HAVPfunctionSts;
    AutoPushSts AutoPushSts;
    SVPfunctionSts SVPfunctionSts;
};
struct HAVPLearningWorldArray {
    public:
        HAVPLearningWorldArray() {
        };
        ~HAVPLearningWorldArray() {
        }

    public:
        std::vector< uint8_t> dynamicBYTE;
};
struct HAVPVehDataArray {
    public:
        HAVPVehDataArray() {
        };
        ~HAVPVehDataArray() {
        }

    public:
        std::vector< uint8_t> dynamicBYTE;
};
struct HAVPMapFileArray {
    public:
        HAVPMapFileArray() {
        };
        ~HAVPMapFileArray() {
        }

    public:
        std::vector< uint8_t> dynamicBYTE;
};


class HAVPandAVPFunctionsListener {
  public:
    virtual ~HAVPandAVPFunctionsListener(){};
    virtual void HAVP_SVPScrnDispInfoEventListener(HAVP_SVPScrnInfoStruct &havp_SVPScrnInfoStruct){};
    virtual void AVMDispReqEventListener(AVMStsReq avmStsReq){};
    virtual void HAVPPathMapEventListener(HAVPMapFileArray &havpMapFileArray){};
    virtual void HAVPRendergInfoEventListener(HAVPVehDataArray &havpVehDataArray){};
    virtual void HAVPPathInfoEventListener(HAVPLearningWorldArray &havpLearningWorldArray){};
    virtual void SideBsdDispStsInfoEventListener(SideBsdDispStatus sideBsdDispStatus){};

};

void HAVPandAVPFunctionsInit(char *appName, char *configFile);
bool HAVPandAVPFunctionsIsReady();
CallStatus AVMDispResp(AVMStsResp avmStsResp);
CallStatus AutoReq(AutoPushReq autoPushReq);
CallStatus HAVPReq(HAVPfunctionReq havpFunctionReq);
CallStatus NearSlotIDReq(SelNearSlotID selNearSlotID);
CallStatus PrkgFlrReq(SetMapFlr setMapFlr);
CallStatus PrkgSlotReq(SetPrkgSlot setPrkgSlot);
CallStatus HAVP_SVPSwtReq(BtnEnaReq btnEnaReq);
CallStatus TarPrkgIDReq(TarMapID tarMapID);
CallStatus PrkgAreaReq(SetPrkgArea setPrkgArea);
CallStatus PrkgTypReq(SetPrkgSlotTyp setPrkgSlotTyp);
CallStatus PrkgLotMapUpdSt(MapUpdSt mapUpdSt);
CallStatus LvngPOIReq(SetLvngPOI setLvngPOI);
CallStatus SVPReq(SVPfunctionReq svpFunctionReq);
CallStatus SideBsdDisp(SideBsdDispRequest sideBsdDispRequest,SideBsdDispStsOut &out);

void HAVPandAVPFunctionsListenerRegister(HAVPandAVPFunctionsListener *listener);

void HAPFunctionsListenerRegister(HAVPandAVPFunctionsListener *listener);

void SideBsdDispStsInfoListenerRegister(HAVPandAVPFunctionsListener *listener);

void HAVPandAVPFunctionsListenerUnRegister();

void HAPFunctionsListenerUnRegister();

void SideBsdDispStsInfoListenerUnRegister();

#endif //SOMEIPTEST_HAVPANDAVP_FUNCTIONS_H