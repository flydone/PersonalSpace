/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.1.12.v202002200719.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#ifndef V1_GREATWALL_IDC_L2_IDC1_5_IDC3_0_MDC_A_IDC__L2_SYSTEM_FUNCTIONS_HPP_
#define V1_GREATWALL_IDC_L2_IDC1_5_IDC3_0_MDC_A_IDC__L2_SYSTEM_FUNCTIONS_HPP_




#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/Deployment.hpp>
#include <CommonAPI/InputStream.hpp>
#include <CommonAPI/OutputStream.hpp>
#include <CommonAPI/Struct.hpp>
#include <CommonAPI/Types.hpp>
#include <cstdint>
#include <vector>

#undef COMMONAPI_INTERNAL_COMPILATION

namespace v1 {
namespace GREATWALL {
namespace IDC_L2_IDC1_5_IDC3_0_MDC_A {

class IDC_L2SystemFunctions {
public:
    virtual ~IDC_L2SystemFunctions() { }

    static inline const char* getInterface();
    static inline CommonAPI::Version getInterfaceVersion();
    typedef float Loc_heading_Con;
    typedef float Loc_heading;
    typedef uint64_t Loc_TimeStamp;
    typedef int32_t Loc_longitudinal_pos;
    typedef int32_t Loc_Altitude_pos;
    typedef float Loc_speed;
    typedef float Loc_head_left;
    typedef float Loc_head_right;
    
    struct Loc_Con_lane : CommonAPI::Enumeration< uint8_t> {
        enum Literal : uint8_t {
            E_INIT = 0,
            E_HIGH = 1,
            E_MEDIUM = 2,
            E_LOW = 3
        };
    
        Loc_Con_lane()
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(Literal::E_INIT)) {}
        Loc_Con_lane(Literal _literal)
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(_literal)) {}
    
        inline bool validate() const {
            switch (value_) {
                case static_cast< uint8_t>(Literal::E_INIT):
                case static_cast< uint8_t>(Literal::E_HIGH):
                case static_cast< uint8_t>(Literal::E_MEDIUM):
                case static_cast< uint8_t>(Literal::E_LOW):
                return true;
            default:
                return false;
            }
        }
    
        inline bool operator==(const Loc_Con_lane &_other) const { return (value_ == _other.value_); }
        inline bool operator!=(const Loc_Con_lane &_other) const { return (value_ != _other.value_); }
        inline bool operator<=(const Loc_Con_lane &_other) const { return (value_ <= _other.value_); }
        inline bool operator>=(const Loc_Con_lane &_other) const { return (value_ >= _other.value_); }
        inline bool operator<(const Loc_Con_lane &_other) const { return (value_ < _other.value_); }
        inline bool operator>(const Loc_Con_lane &_other) const { return (value_ > _other.value_); }
    
        inline bool operator==(const Literal &_value) const { return (value_ == static_cast< uint8_t>(_value)); }
        inline bool operator!=(const Literal &_value) const { return (value_ != static_cast< uint8_t>(_value)); }
        inline bool operator<=(const Literal &_value) const { return (value_ <= static_cast< uint8_t>(_value)); }
        inline bool operator>=(const Literal &_value) const { return (value_ >= static_cast< uint8_t>(_value)); }
        inline bool operator<(const Literal &_value) const { return (value_ < static_cast< uint8_t>(_value)); }
        inline bool operator>(const Literal &_value) const { return (value_ > static_cast< uint8_t>(_value)); }
    };
    typedef float Loc_dis_left;
    typedef float Loc_speed_Con;
    typedef float Loc_Altitude_pos_Con;
    typedef int32_t Loc_lateral_pos;
    typedef uint8_t Loc_current_lane;
    typedef float Loc_dis_right;
    struct LocationInfoStruct : CommonAPI::Struct< Loc_dis_left, Loc_dis_right, Loc_head_left, Loc_head_right, Loc_Con_lane, Loc_lateral_pos, Loc_longitudinal_pos, Loc_Altitude_pos, Loc_Altitude_pos_Con, Loc_heading, Loc_heading_Con, Loc_TimeStamp, Loc_speed, Loc_speed_Con, Loc_current_lane> {
    
        LocationInfoStruct()
        {
            std::get< 0>(values_) = Loc_dis_left();
            std::get< 1>(values_) = Loc_dis_right();
            std::get< 2>(values_) = Loc_head_left();
            std::get< 3>(values_) = Loc_head_right();
            std::get< 4>(values_) = Loc_Con_lane();
            std::get< 5>(values_) = Loc_lateral_pos();
            std::get< 6>(values_) = Loc_longitudinal_pos();
            std::get< 7>(values_) = Loc_Altitude_pos();
            std::get< 8>(values_) = Loc_Altitude_pos_Con();
            std::get< 9>(values_) = Loc_heading();
            std::get< 10>(values_) = Loc_heading_Con();
            std::get< 11>(values_) = Loc_TimeStamp();
            std::get< 12>(values_) = Loc_speed();
            std::get< 13>(values_) = Loc_speed_Con();
            std::get< 14>(values_) = Loc_current_lane();
        }
        LocationInfoStruct(const Loc_dis_left &_Loc_dis_left, const Loc_dis_right &_Loc_dis_right, const Loc_head_left &_Loc_head_left, const Loc_head_right &_Loc_head_right, const Loc_Con_lane &_Loc_Con_lane, const Loc_lateral_pos &_Loc_lateral_pos, const Loc_longitudinal_pos &_Loc_longitudinal_pos, const Loc_Altitude_pos &_Loc_Altitude_pos, const Loc_Altitude_pos_Con &_Loc_Altitude_pos_Con, const Loc_heading &_Loc_heading, const Loc_heading_Con &_Loc_heading_Con, const Loc_TimeStamp &_Loc_TimeStamp, const Loc_speed &_Loc_speed, const Loc_speed_Con &_Loc_speed_Con, const Loc_current_lane &_Loc_current_lane)
        {
            std::get< 0>(values_) = _Loc_dis_left;
            std::get< 1>(values_) = _Loc_dis_right;
            std::get< 2>(values_) = _Loc_head_left;
            std::get< 3>(values_) = _Loc_head_right;
            std::get< 4>(values_) = _Loc_Con_lane;
            std::get< 5>(values_) = _Loc_lateral_pos;
            std::get< 6>(values_) = _Loc_longitudinal_pos;
            std::get< 7>(values_) = _Loc_Altitude_pos;
            std::get< 8>(values_) = _Loc_Altitude_pos_Con;
            std::get< 9>(values_) = _Loc_heading;
            std::get< 10>(values_) = _Loc_heading_Con;
            std::get< 11>(values_) = _Loc_TimeStamp;
            std::get< 12>(values_) = _Loc_speed;
            std::get< 13>(values_) = _Loc_speed_Con;
            std::get< 14>(values_) = _Loc_current_lane;
        }
        inline const Loc_dis_left &getLoc_dis_left() const { return std::get< 0>(values_); }
        inline void setLoc_dis_left(const Loc_dis_left &_value) { std::get< 0>(values_) = _value; }
        inline const Loc_dis_right &getLoc_dis_right() const { return std::get< 1>(values_); }
        inline void setLoc_dis_right(const Loc_dis_right &_value) { std::get< 1>(values_) = _value; }
        inline const Loc_head_left &getLoc_head_left() const { return std::get< 2>(values_); }
        inline void setLoc_head_left(const Loc_head_left &_value) { std::get< 2>(values_) = _value; }
        inline const Loc_head_right &getLoc_head_right() const { return std::get< 3>(values_); }
        inline void setLoc_head_right(const Loc_head_right &_value) { std::get< 3>(values_) = _value; }
        inline const Loc_Con_lane &getLoc_Con_lane() const { return std::get< 4>(values_); }
        inline void setLoc_Con_lane(const Loc_Con_lane &_value) { std::get< 4>(values_) = _value; }
        inline const Loc_lateral_pos &getLoc_lateral_pos() const { return std::get< 5>(values_); }
        inline void setLoc_lateral_pos(const Loc_lateral_pos &_value) { std::get< 5>(values_) = _value; }
        inline const Loc_longitudinal_pos &getLoc_longitudinal_pos() const { return std::get< 6>(values_); }
        inline void setLoc_longitudinal_pos(const Loc_longitudinal_pos &_value) { std::get< 6>(values_) = _value; }
        inline const Loc_Altitude_pos &getLoc_Altitude_pos() const { return std::get< 7>(values_); }
        inline void setLoc_Altitude_pos(const Loc_Altitude_pos &_value) { std::get< 7>(values_) = _value; }
        inline const Loc_Altitude_pos_Con &getLoc_Altitude_pos_Con() const { return std::get< 8>(values_); }
        inline void setLoc_Altitude_pos_Con(const Loc_Altitude_pos_Con &_value) { std::get< 8>(values_) = _value; }
        inline const Loc_heading &getLoc_heading() const { return std::get< 9>(values_); }
        inline void setLoc_heading(const Loc_heading &_value) { std::get< 9>(values_) = _value; }
        inline const Loc_heading_Con &getLoc_heading_Con() const { return std::get< 10>(values_); }
        inline void setLoc_heading_Con(const Loc_heading_Con &_value) { std::get< 10>(values_) = _value; }
        inline const Loc_TimeStamp &getLoc_TimeStamp() const { return std::get< 11>(values_); }
        inline void setLoc_TimeStamp(const Loc_TimeStamp &_value) { std::get< 11>(values_) = _value; }
        inline const Loc_speed &getLoc_speed() const { return std::get< 12>(values_); }
        inline void setLoc_speed(const Loc_speed &_value) { std::get< 12>(values_) = _value; }
        inline const Loc_speed_Con &getLoc_speed_Con() const { return std::get< 13>(values_); }
        inline void setLoc_speed_Con(const Loc_speed_Con &_value) { std::get< 13>(values_) = _value; }
        inline const Loc_current_lane &getLoc_current_lane() const { return std::get< 14>(values_); }
        inline void setLoc_current_lane(const Loc_current_lane &_value) { std::get< 14>(values_) = _value; }
        inline bool operator==(const LocationInfoStruct& _other) const {
        return (getLoc_dis_left() == _other.getLoc_dis_left() && getLoc_dis_right() == _other.getLoc_dis_right() && getLoc_head_left() == _other.getLoc_head_left() && getLoc_head_right() == _other.getLoc_head_right() && getLoc_Con_lane() == _other.getLoc_Con_lane() && getLoc_lateral_pos() == _other.getLoc_lateral_pos() && getLoc_longitudinal_pos() == _other.getLoc_longitudinal_pos() && getLoc_Altitude_pos() == _other.getLoc_Altitude_pos() && getLoc_Altitude_pos_Con() == _other.getLoc_Altitude_pos_Con() && getLoc_heading() == _other.getLoc_heading() && getLoc_heading_Con() == _other.getLoc_heading_Con() && getLoc_TimeStamp() == _other.getLoc_TimeStamp() && getLoc_speed() == _other.getLoc_speed() && getLoc_speed_Con() == _other.getLoc_speed_Con() && getLoc_current_lane() == _other.getLoc_current_lane());
        }
        inline bool operator!=(const LocationInfoStruct &_other) const {
            return !((*this) == _other);
        }
    
    };
    typedef float OBJ_DX;
    typedef uint8_t OBJ_ID;
    typedef float OBJ_ExistProb;
    
    struct OBJ_Type : CommonAPI::Enumeration< uint8_t> {
        enum Literal : uint8_t {
            E_INVALID = 0,
            E_UNKNOWN_TYPE = 1,
            E_CAR = 2,
            E_TRUCK = 3,
            E_MOTORBIKE = 4,
            E_BICYCLE = 5,
            E_PEDESTRIAN = 6,
            E_GENERAL_OBJECT = 7,
            E_ANIMAL = 8,
            E_BUS = 9,
            E_TRAFFIC_CONE = 10,
            E_SUV = 11,
            E_TRICYCLIST = 12,
            E_TROLLEY = 13,
            E_PARKING_STOPPER = 14,
            E_WARNING_TRIANGLE = 15,
            E_PARKING_LOCK = 16,
            E_DUSTBIN = 17,
            E_BARRIER_STONE = 18,
            E_ANTICRACH_BUCKET = 19,
            E_PICKUP = 20,
            E_POLICE_CAR = 21,
            E_AMBULANCE = 22,
            E_WATER_BARRIER = 23,
            E_BOLLARD_SLEEVE = 24
        };
    
        OBJ_Type()
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(Literal::E_INVALID)) {}
        OBJ_Type(Literal _literal)
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(_literal)) {}
    
        inline bool validate() const {
            switch (value_) {
                case static_cast< uint8_t>(Literal::E_INVALID):
                case static_cast< uint8_t>(Literal::E_UNKNOWN_TYPE):
                case static_cast< uint8_t>(Literal::E_CAR):
                case static_cast< uint8_t>(Literal::E_TRUCK):
                case static_cast< uint8_t>(Literal::E_MOTORBIKE):
                case static_cast< uint8_t>(Literal::E_BICYCLE):
                case static_cast< uint8_t>(Literal::E_PEDESTRIAN):
                case static_cast< uint8_t>(Literal::E_GENERAL_OBJECT):
                case static_cast< uint8_t>(Literal::E_ANIMAL):
                case static_cast< uint8_t>(Literal::E_BUS):
                case static_cast< uint8_t>(Literal::E_TRAFFIC_CONE):
                case static_cast< uint8_t>(Literal::E_SUV):
                case static_cast< uint8_t>(Literal::E_TRICYCLIST):
                case static_cast< uint8_t>(Literal::E_TROLLEY):
                case static_cast< uint8_t>(Literal::E_PARKING_STOPPER):
                case static_cast< uint8_t>(Literal::E_WARNING_TRIANGLE):
                case static_cast< uint8_t>(Literal::E_PARKING_LOCK):
                case static_cast< uint8_t>(Literal::E_DUSTBIN):
                case static_cast< uint8_t>(Literal::E_BARRIER_STONE):
                case static_cast< uint8_t>(Literal::E_ANTICRACH_BUCKET):
                case static_cast< uint8_t>(Literal::E_PICKUP):
                case static_cast< uint8_t>(Literal::E_POLICE_CAR):
                case static_cast< uint8_t>(Literal::E_AMBULANCE):
                case static_cast< uint8_t>(Literal::E_WATER_BARRIER):
                case static_cast< uint8_t>(Literal::E_BOLLARD_SLEEVE):
                return true;
            default:
                return false;
            }
        }
    
        inline bool operator==(const OBJ_Type &_other) const { return (value_ == _other.value_); }
        inline bool operator!=(const OBJ_Type &_other) const { return (value_ != _other.value_); }
        inline bool operator<=(const OBJ_Type &_other) const { return (value_ <= _other.value_); }
        inline bool operator>=(const OBJ_Type &_other) const { return (value_ >= _other.value_); }
        inline bool operator<(const OBJ_Type &_other) const { return (value_ < _other.value_); }
        inline bool operator>(const OBJ_Type &_other) const { return (value_ > _other.value_); }
    
        inline bool operator==(const Literal &_value) const { return (value_ == static_cast< uint8_t>(_value)); }
        inline bool operator!=(const Literal &_value) const { return (value_ != static_cast< uint8_t>(_value)); }
        inline bool operator<=(const Literal &_value) const { return (value_ <= static_cast< uint8_t>(_value)); }
        inline bool operator>=(const Literal &_value) const { return (value_ >= static_cast< uint8_t>(_value)); }
        inline bool operator<(const Literal &_value) const { return (value_ < static_cast< uint8_t>(_value)); }
        inline bool operator>(const Literal &_value) const { return (value_ > static_cast< uint8_t>(_value)); }
    };
    typedef float OBJ_HeadingAngle;
    typedef int32_t OBJ_Age;
    typedef float OBJ_Hight;
    typedef float OBJ_DY;
    struct OBJInfoStruct : CommonAPI::Struct< OBJ_ID, OBJ_Type, OBJ_Hight, OBJ_HeadingAngle, OBJ_DX, OBJ_DY, OBJ_ExistProb, OBJ_Age> {
    
        OBJInfoStruct()
        {
            std::get< 0>(values_) = OBJ_ID();
            std::get< 1>(values_) = OBJ_Type();
            std::get< 2>(values_) = OBJ_Hight();
            std::get< 3>(values_) = OBJ_HeadingAngle();
            std::get< 4>(values_) = OBJ_DX();
            std::get< 5>(values_) = OBJ_DY();
            std::get< 6>(values_) = OBJ_ExistProb();
            std::get< 7>(values_) = OBJ_Age();
        }
        OBJInfoStruct(const OBJ_ID &_OBJ_ID, const OBJ_Type &_OBJ_Type, const OBJ_Hight &_OBJ_Hight, const OBJ_HeadingAngle &_OBJ_HeadingAngle, const OBJ_DX &_OBJ_DX, const OBJ_DY &_OBJ_DY, const OBJ_ExistProb &_OBJ_ExistProb, const OBJ_Age &_OBJ_Age)
        {
            std::get< 0>(values_) = _OBJ_ID;
            std::get< 1>(values_) = _OBJ_Type;
            std::get< 2>(values_) = _OBJ_Hight;
            std::get< 3>(values_) = _OBJ_HeadingAngle;
            std::get< 4>(values_) = _OBJ_DX;
            std::get< 5>(values_) = _OBJ_DY;
            std::get< 6>(values_) = _OBJ_ExistProb;
            std::get< 7>(values_) = _OBJ_Age;
        }
        inline const OBJ_ID &getOBJ_ID() const { return std::get< 0>(values_); }
        inline void setOBJ_ID(const OBJ_ID &_value) { std::get< 0>(values_) = _value; }
        inline const OBJ_Type &getOBJ_Type() const { return std::get< 1>(values_); }
        inline void setOBJ_Type(const OBJ_Type &_value) { std::get< 1>(values_) = _value; }
        inline const OBJ_Hight &getOBJ_Hight() const { return std::get< 2>(values_); }
        inline void setOBJ_Hight(const OBJ_Hight &_value) { std::get< 2>(values_) = _value; }
        inline const OBJ_HeadingAngle &getOBJ_HeadingAngle() const { return std::get< 3>(values_); }
        inline void setOBJ_HeadingAngle(const OBJ_HeadingAngle &_value) { std::get< 3>(values_) = _value; }
        inline const OBJ_DX &getOBJ_DX() const { return std::get< 4>(values_); }
        inline void setOBJ_DX(const OBJ_DX &_value) { std::get< 4>(values_) = _value; }
        inline const OBJ_DY &getOBJ_DY() const { return std::get< 5>(values_); }
        inline void setOBJ_DY(const OBJ_DY &_value) { std::get< 5>(values_) = _value; }
        inline const OBJ_ExistProb &getOBJ_ExistProb() const { return std::get< 6>(values_); }
        inline void setOBJ_ExistProb(const OBJ_ExistProb &_value) { std::get< 6>(values_) = _value; }
        inline const OBJ_Age &getOBJ_Age() const { return std::get< 7>(values_); }
        inline void setOBJ_Age(const OBJ_Age &_value) { std::get< 7>(values_) = _value; }
        inline bool operator==(const OBJInfoStruct& _other) const {
        return (getOBJ_ID() == _other.getOBJ_ID() && getOBJ_Type() == _other.getOBJ_Type() && getOBJ_Hight() == _other.getOBJ_Hight() && getOBJ_HeadingAngle() == _other.getOBJ_HeadingAngle() && getOBJ_DX() == _other.getOBJ_DX() && getOBJ_DY() == _other.getOBJ_DY() && getOBJ_ExistProb() == _other.getOBJ_ExistProb() && getOBJ_Age() == _other.getOBJ_Age());
        }
        inline bool operator!=(const OBJInfoStruct &_other) const {
            return !((*this) == _other);
        }
    
    };
    typedef std::vector< IDC_L2SystemFunctions::OBJInfoStruct> OBJInfoStructArray;
    typedef uint64_t OBJ_TimeStamp;
    
    struct ObjBarDisp_Type : CommonAPI::Enumeration< uint8_t> {
        enum Literal : uint8_t {
            E_NO_DISPLAY = 0,
            E_DISTANCE_1_ONE_BAR = 1,
            E_DISTANCE_2_TWO_BARS = 2,
            E_DISTANCE_3_THREE_BARS = 3,
            E_DISTANCE_4_FOUR_BARS = 4
        };
    
        ObjBarDisp_Type()
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(Literal::E_NO_DISPLAY)) {}
        ObjBarDisp_Type(Literal _literal)
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(_literal)) {}
    
        inline bool validate() const {
            switch (value_) {
                case static_cast< uint8_t>(Literal::E_NO_DISPLAY):
                case static_cast< uint8_t>(Literal::E_DISTANCE_1_ONE_BAR):
                case static_cast< uint8_t>(Literal::E_DISTANCE_2_TWO_BARS):
                case static_cast< uint8_t>(Literal::E_DISTANCE_3_THREE_BARS):
                case static_cast< uint8_t>(Literal::E_DISTANCE_4_FOUR_BARS):
                return true;
            default:
                return false;
            }
        }
    
        inline bool operator==(const ObjBarDisp_Type &_other) const { return (value_ == _other.value_); }
        inline bool operator!=(const ObjBarDisp_Type &_other) const { return (value_ != _other.value_); }
        inline bool operator<=(const ObjBarDisp_Type &_other) const { return (value_ <= _other.value_); }
        inline bool operator>=(const ObjBarDisp_Type &_other) const { return (value_ >= _other.value_); }
        inline bool operator<(const ObjBarDisp_Type &_other) const { return (value_ < _other.value_); }
        inline bool operator>(const ObjBarDisp_Type &_other) const { return (value_ > _other.value_); }
    
        inline bool operator==(const Literal &_value) const { return (value_ == static_cast< uint8_t>(_value)); }
        inline bool operator!=(const Literal &_value) const { return (value_ != static_cast< uint8_t>(_value)); }
        inline bool operator<=(const Literal &_value) const { return (value_ <= static_cast< uint8_t>(_value)); }
        inline bool operator>=(const Literal &_value) const { return (value_ >= static_cast< uint8_t>(_value)); }
        inline bool operator<(const Literal &_value) const { return (value_ < static_cast< uint8_t>(_value)); }
        inline bool operator>(const Literal &_value) const { return (value_ > static_cast< uint8_t>(_value)); }
    };
    struct OBJ_DispProperty_Type : CommonAPI::Struct< OBJ_ID, ObjBarDisp_Type> {
    
        OBJ_DispProperty_Type()
        {
            std::get< 0>(values_) = OBJ_ID();
            std::get< 1>(values_) = ObjBarDisp_Type();
        }
        OBJ_DispProperty_Type(const OBJ_ID &_OBJ_ID, const ObjBarDisp_Type &_ObjBarDisp)
        {
            std::get< 0>(values_) = _OBJ_ID;
            std::get< 1>(values_) = _ObjBarDisp;
        }
        inline const OBJ_ID &getOBJ_ID() const { return std::get< 0>(values_); }
        inline void setOBJ_ID(const OBJ_ID &_value) { std::get< 0>(values_) = _value; }
        inline const ObjBarDisp_Type &getObjBarDisp() const { return std::get< 1>(values_); }
        inline void setObjBarDisp(const ObjBarDisp_Type &_value) { std::get< 1>(values_) = _value; }
        inline bool operator==(const OBJ_DispProperty_Type& _other) const {
        return (getOBJ_ID() == _other.getOBJ_ID() && getObjBarDisp() == _other.getObjBarDisp());
        }
        inline bool operator!=(const OBJ_DispProperty_Type &_other) const {
            return !((*this) == _other);
        }
    
    };
    struct OBJ_DispProperty : CommonAPI::Struct< OBJ_DispProperty_Type, OBJ_DispProperty_Type, OBJ_DispProperty_Type, OBJ_DispProperty_Type, OBJ_DispProperty_Type, OBJ_DispProperty_Type, OBJ_DispProperty_Type, OBJ_DispProperty_Type, OBJ_DispProperty_Type> {
    
        OBJ_DispProperty()
        {
            std::get< 0>(values_) = OBJ_DispProperty_Type();
            std::get< 1>(values_) = OBJ_DispProperty_Type();
            std::get< 2>(values_) = OBJ_DispProperty_Type();
            std::get< 3>(values_) = OBJ_DispProperty_Type();
            std::get< 4>(values_) = OBJ_DispProperty_Type();
            std::get< 5>(values_) = OBJ_DispProperty_Type();
            std::get< 6>(values_) = OBJ_DispProperty_Type();
            std::get< 7>(values_) = OBJ_DispProperty_Type();
            std::get< 8>(values_) = OBJ_DispProperty_Type();
        }
        OBJ_DispProperty(const OBJ_DispProperty_Type &_Target_Obj, const OBJ_DispProperty_Type &_Left_Target_Obj, const OBJ_DispProperty_Type &_Right_Target_Obj, const OBJ_DispProperty_Type &_Target_Obj_2, const OBJ_DispProperty_Type &_Left_Target_Obj_2, const OBJ_DispProperty_Type &_Right_Target_Obj_2, const OBJ_DispProperty_Type &_Target_Obj_3, const OBJ_DispProperty_Type &_Left_Target_Obj_3, const OBJ_DispProperty_Type &_Right_Target_Obj_3)
        {
            std::get< 0>(values_) = _Target_Obj;
            std::get< 1>(values_) = _Left_Target_Obj;
            std::get< 2>(values_) = _Right_Target_Obj;
            std::get< 3>(values_) = _Target_Obj_2;
            std::get< 4>(values_) = _Left_Target_Obj_2;
            std::get< 5>(values_) = _Right_Target_Obj_2;
            std::get< 6>(values_) = _Target_Obj_3;
            std::get< 7>(values_) = _Left_Target_Obj_3;
            std::get< 8>(values_) = _Right_Target_Obj_3;
        }
        inline const OBJ_DispProperty_Type &getTarget_Obj() const { return std::get< 0>(values_); }
        inline void setTarget_Obj(const OBJ_DispProperty_Type &_value) { std::get< 0>(values_) = _value; }
        inline const OBJ_DispProperty_Type &getLeft_Target_Obj() const { return std::get< 1>(values_); }
        inline void setLeft_Target_Obj(const OBJ_DispProperty_Type &_value) { std::get< 1>(values_) = _value; }
        inline const OBJ_DispProperty_Type &getRight_Target_Obj() const { return std::get< 2>(values_); }
        inline void setRight_Target_Obj(const OBJ_DispProperty_Type &_value) { std::get< 2>(values_) = _value; }
        inline const OBJ_DispProperty_Type &getTarget_Obj_2() const { return std::get< 3>(values_); }
        inline void setTarget_Obj_2(const OBJ_DispProperty_Type &_value) { std::get< 3>(values_) = _value; }
        inline const OBJ_DispProperty_Type &getLeft_Target_Obj_2() const { return std::get< 4>(values_); }
        inline void setLeft_Target_Obj_2(const OBJ_DispProperty_Type &_value) { std::get< 4>(values_) = _value; }
        inline const OBJ_DispProperty_Type &getRight_Target_Obj_2() const { return std::get< 5>(values_); }
        inline void setRight_Target_Obj_2(const OBJ_DispProperty_Type &_value) { std::get< 5>(values_) = _value; }
        inline const OBJ_DispProperty_Type &getTarget_Obj_3() const { return std::get< 6>(values_); }
        inline void setTarget_Obj_3(const OBJ_DispProperty_Type &_value) { std::get< 6>(values_) = _value; }
        inline const OBJ_DispProperty_Type &getLeft_Target_Obj_3() const { return std::get< 7>(values_); }
        inline void setLeft_Target_Obj_3(const OBJ_DispProperty_Type &_value) { std::get< 7>(values_) = _value; }
        inline const OBJ_DispProperty_Type &getRight_Target_Obj_3() const { return std::get< 8>(values_); }
        inline void setRight_Target_Obj_3(const OBJ_DispProperty_Type &_value) { std::get< 8>(values_) = _value; }
        inline bool operator==(const OBJ_DispProperty& _other) const {
        return (getTarget_Obj() == _other.getTarget_Obj() && getLeft_Target_Obj() == _other.getLeft_Target_Obj() && getRight_Target_Obj() == _other.getRight_Target_Obj() && getTarget_Obj_2() == _other.getTarget_Obj_2() && getLeft_Target_Obj_2() == _other.getLeft_Target_Obj_2() && getRight_Target_Obj_2() == _other.getRight_Target_Obj_2() && getTarget_Obj_3() == _other.getTarget_Obj_3() && getLeft_Target_Obj_3() == _other.getLeft_Target_Obj_3() && getRight_Target_Obj_3() == _other.getRight_Target_Obj_3());
        }
        inline bool operator!=(const OBJ_DispProperty &_other) const {
            return !((*this) == _other);
        }
    
    };
    struct OBJPptyInfoStruct : CommonAPI::Struct< OBJ_TimeStamp, OBJInfoStructArray, OBJ_DispProperty> {
    
        OBJPptyInfoStruct()
        {
            std::get< 0>(values_) = OBJ_TimeStamp();
            std::get< 1>(values_) = OBJInfoStructArray();
            std::get< 2>(values_) = OBJ_DispProperty();
        }
        OBJPptyInfoStruct(const OBJ_TimeStamp &_OBJ_TimeStamp, const OBJInfoStructArray &_OBJInfoStructArray, const OBJ_DispProperty &_OBJ_DispProperty)
        {
            std::get< 0>(values_) = _OBJ_TimeStamp;
            std::get< 1>(values_) = _OBJInfoStructArray;
            std::get< 2>(values_) = _OBJ_DispProperty;
        }
        inline const OBJ_TimeStamp &getOBJ_TimeStamp() const { return std::get< 0>(values_); }
        inline void setOBJ_TimeStamp(const OBJ_TimeStamp &_value) { std::get< 0>(values_) = _value; }
        inline const OBJInfoStructArray &getOBJInfoStructArray() const { return std::get< 1>(values_); }
        inline void setOBJInfoStructArray(const OBJInfoStructArray &_value) { std::get< 1>(values_) = _value; }
        inline const OBJ_DispProperty &getOBJ_DispProperty() const { return std::get< 2>(values_); }
        inline void setOBJ_DispProperty(const OBJ_DispProperty &_value) { std::get< 2>(values_) = _value; }
        inline bool operator==(const OBJPptyInfoStruct& _other) const {
        return (getOBJ_TimeStamp() == _other.getOBJ_TimeStamp() && getOBJInfoStructArray() == _other.getOBJInfoStructArray() && getOBJ_DispProperty() == _other.getOBJ_DispProperty());
        }
        inline bool operator!=(const OBJPptyInfoStruct &_other) const {
            return !((*this) == _other);
        }
    
    };
};

const char* IDC_L2SystemFunctions::getInterface() {
    return ("GREATWALL.IDC_L2_IDC1_5_IDC3_0_MDC_A.IDC_L2SystemFunctions:v1_0");
}

CommonAPI::Version IDC_L2SystemFunctions::getInterfaceVersion() {
    return CommonAPI::Version(1, 0);
}


} // namespace IDC_L2_IDC1_5_IDC3_0_MDC_A
} // namespace GREATWALL
} // namespace v1

namespace CommonAPI {
}


// Compatibility
namespace v1_0 = v1;

#endif // V1_GREATWALL_IDC_L2_IDC1_5_IDC3_0_MDC_A_IDC__L2_SYSTEM_FUNCTIONS_HPP_
