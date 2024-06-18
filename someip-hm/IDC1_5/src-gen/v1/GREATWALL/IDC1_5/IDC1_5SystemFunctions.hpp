/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.1.12.v202002200719.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#ifndef V1_GREATWALL_IDC1_5_IDC1_5_SYSTEM_FUNCTIONS_HPP_
#define V1_GREATWALL_IDC1_5_IDC1_5_SYSTEM_FUNCTIONS_HPP_




#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/Deployment.hpp>
#include <CommonAPI/InputStream.hpp>
#include <CommonAPI/OutputStream.hpp>
#include <CommonAPI/Struct.hpp>
#include <CommonAPI/Types.hpp>
#include <cstdint>

#undef COMMONAPI_INTERNAL_COMPILATION

namespace v1 {
namespace GREATWALL {
namespace IDC1_5 {

class IDC1_5SystemFunctions {
public:
    virtual ~IDC1_5SystemFunctions() { }

    static inline const char* getInterface();
    static inline CommonAPI::Version getInterfaceVersion();
    typedef uint64_t Collect_before_time;
    typedef uint64_t Collect_after_time;
    typedef uint64_t Sys_time_us;
    
    struct TriggerType : CommonAPI::Enumeration< uint8_t> {
        enum Literal : uint8_t {
            E_TRI_NONE = 0,
            E_TRI_DIAGNOSIS = 1,
            E_TRI_DIAGNOSIS_HARDWARE = 2,
            E_TRI_DIAGNOSIS_SOFTWARE = 3,
            E_TRI_DIAGNOSIS_NETWORK = 4,
            E_TRI_ACCIDENT = 5,
            E_TRI_REMOTE = 6,
            E_TRI_EBRAKE = 7,
            E_TRI_PBRAKE = 8,
            E_TRI_BLOCK = 9,
            E_TRI_AEB = 10,
            E_TRI_SAFESTOP = 11,
            E_TRI_SMART_DODGE = 12,
            E_TRI_ELK = 13,
            E_TRI_ESS = 14,
            E_TRI_SHARP_TURN = 15,
            E_TRI_CHANGE_LANE = 16,
            E_TRI_URGENT_ACCELERATE = 17,
            E_TRI_HMI = 18,
            E_TRI_CAMERA_BUMPY = 19,
            E_TRI_ROAD_UNDULATION = 20,
            E_TRI_FISHBONE_LINE = 21,
            E_TRI_NO_LANE_LINE = 22,
            E_TRI_SPECIAL_ROAD = 23,
            E_TRI_SPECIAL_WEATHER_SCENE = 24,
            E_TRI_LANE_LINE_COVERED = 25,
            E_TRI_ANIMAL = 26,
            E_TRI_GENERAL_OBSTACLE = 27,
            E_TRI_MINI_CAR = 28,
            E_TRI_LARGE_TRUCK = 29,
            E_TRI_RAMP = 30,
            E_TRI_ADAS_OPEN = 31,
            E_TRI_CHANGE_LANE_CANCELED = 32,
            E_TRI_ADAS_CLOSE = 33,
            E_TRI_INTERVENE = 34,
            E_TRI_TRAFFIC_JAM = 35,
            E_TRI_ME_FAILSAFE = 36,
            E_TRI_CHANGE_LANE_FAILURE = 37,
            E_CUSTOMTRIGGER = 100
        };
    
        TriggerType()
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(Literal::E_TRI_NONE)) {}
        TriggerType(Literal _literal)
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(_literal)) {}
    
        inline bool validate() const {
            switch (value_) {
                case static_cast< uint8_t>(Literal::E_TRI_NONE):
                case static_cast< uint8_t>(Literal::E_TRI_DIAGNOSIS):
                case static_cast< uint8_t>(Literal::E_TRI_DIAGNOSIS_HARDWARE):
                case static_cast< uint8_t>(Literal::E_TRI_DIAGNOSIS_SOFTWARE):
                case static_cast< uint8_t>(Literal::E_TRI_DIAGNOSIS_NETWORK):
                case static_cast< uint8_t>(Literal::E_TRI_ACCIDENT):
                case static_cast< uint8_t>(Literal::E_TRI_REMOTE):
                case static_cast< uint8_t>(Literal::E_TRI_EBRAKE):
                case static_cast< uint8_t>(Literal::E_TRI_PBRAKE):
                case static_cast< uint8_t>(Literal::E_TRI_BLOCK):
                case static_cast< uint8_t>(Literal::E_TRI_AEB):
                case static_cast< uint8_t>(Literal::E_TRI_SAFESTOP):
                case static_cast< uint8_t>(Literal::E_TRI_SMART_DODGE):
                case static_cast< uint8_t>(Literal::E_TRI_ELK):
                case static_cast< uint8_t>(Literal::E_TRI_ESS):
                case static_cast< uint8_t>(Literal::E_TRI_SHARP_TURN):
                case static_cast< uint8_t>(Literal::E_TRI_CHANGE_LANE):
                case static_cast< uint8_t>(Literal::E_TRI_URGENT_ACCELERATE):
                case static_cast< uint8_t>(Literal::E_TRI_HMI):
                case static_cast< uint8_t>(Literal::E_TRI_CAMERA_BUMPY):
                case static_cast< uint8_t>(Literal::E_TRI_ROAD_UNDULATION):
                case static_cast< uint8_t>(Literal::E_TRI_FISHBONE_LINE):
                case static_cast< uint8_t>(Literal::E_TRI_NO_LANE_LINE):
                case static_cast< uint8_t>(Literal::E_TRI_SPECIAL_ROAD):
                case static_cast< uint8_t>(Literal::E_TRI_SPECIAL_WEATHER_SCENE):
                case static_cast< uint8_t>(Literal::E_TRI_LANE_LINE_COVERED):
                case static_cast< uint8_t>(Literal::E_TRI_ANIMAL):
                case static_cast< uint8_t>(Literal::E_TRI_GENERAL_OBSTACLE):
                case static_cast< uint8_t>(Literal::E_TRI_MINI_CAR):
                case static_cast< uint8_t>(Literal::E_TRI_LARGE_TRUCK):
                case static_cast< uint8_t>(Literal::E_TRI_RAMP):
                case static_cast< uint8_t>(Literal::E_TRI_ADAS_OPEN):
                case static_cast< uint8_t>(Literal::E_TRI_CHANGE_LANE_CANCELED):
                case static_cast< uint8_t>(Literal::E_TRI_ADAS_CLOSE):
                case static_cast< uint8_t>(Literal::E_TRI_INTERVENE):
                case static_cast< uint8_t>(Literal::E_TRI_TRAFFIC_JAM):
                case static_cast< uint8_t>(Literal::E_TRI_ME_FAILSAFE):
                case static_cast< uint8_t>(Literal::E_TRI_CHANGE_LANE_FAILURE):
                case static_cast< uint8_t>(Literal::E_CUSTOMTRIGGER):
                return true;
            default:
                return false;
            }
        }
    
        inline bool operator==(const TriggerType &_other) const { return (value_ == _other.value_); }
        inline bool operator!=(const TriggerType &_other) const { return (value_ != _other.value_); }
        inline bool operator<=(const TriggerType &_other) const { return (value_ <= _other.value_); }
        inline bool operator>=(const TriggerType &_other) const { return (value_ >= _other.value_); }
        inline bool operator<(const TriggerType &_other) const { return (value_ < _other.value_); }
        inline bool operator>(const TriggerType &_other) const { return (value_ > _other.value_); }
    
        inline bool operator==(const Literal &_value) const { return (value_ == static_cast< uint8_t>(_value)); }
        inline bool operator!=(const Literal &_value) const { return (value_ != static_cast< uint8_t>(_value)); }
        inline bool operator<=(const Literal &_value) const { return (value_ <= static_cast< uint8_t>(_value)); }
        inline bool operator>=(const Literal &_value) const { return (value_ >= static_cast< uint8_t>(_value)); }
        inline bool operator<(const Literal &_value) const { return (value_ < static_cast< uint8_t>(_value)); }
        inline bool operator>(const Literal &_value) const { return (value_ > static_cast< uint8_t>(_value)); }
    };
    struct DataCollectTriggerStruct : CommonAPI::Struct< Sys_time_us, Collect_before_time, Collect_after_time, TriggerType, TriggerType> {
    
        DataCollectTriggerStruct()
        {
            std::get< 0>(values_) = Sys_time_us();
            std::get< 1>(values_) = Collect_before_time();
            std::get< 2>(values_) = Collect_after_time();
            std::get< 3>(values_) = TriggerType();
            std::get< 4>(values_) = TriggerType();
        }
        DataCollectTriggerStruct(const Sys_time_us &_Sys_time_us, const Collect_before_time &_Collect_before_time, const Collect_after_time &_Collect_after_time, const TriggerType &_Trigger_type, const TriggerType &_Trigger_subtype)
        {
            std::get< 0>(values_) = _Sys_time_us;
            std::get< 1>(values_) = _Collect_before_time;
            std::get< 2>(values_) = _Collect_after_time;
            std::get< 3>(values_) = _Trigger_type;
            std::get< 4>(values_) = _Trigger_subtype;
        }
        inline const Sys_time_us &getSys_time_us() const { return std::get< 0>(values_); }
        inline void setSys_time_us(const Sys_time_us &_value) { std::get< 0>(values_) = _value; }
        inline const Collect_before_time &getCollect_before_time() const { return std::get< 1>(values_); }
        inline void setCollect_before_time(const Collect_before_time &_value) { std::get< 1>(values_) = _value; }
        inline const Collect_after_time &getCollect_after_time() const { return std::get< 2>(values_); }
        inline void setCollect_after_time(const Collect_after_time &_value) { std::get< 2>(values_) = _value; }
        inline const TriggerType &getTrigger_type() const { return std::get< 3>(values_); }
        inline void setTrigger_type(const TriggerType &_value) { std::get< 3>(values_) = _value; }
        inline const TriggerType &getTrigger_subtype() const { return std::get< 4>(values_); }
        inline void setTrigger_subtype(const TriggerType &_value) { std::get< 4>(values_) = _value; }
        inline bool operator==(const DataCollectTriggerStruct& _other) const {
        return (getSys_time_us() == _other.getSys_time_us() && getCollect_before_time() == _other.getCollect_before_time() && getCollect_after_time() == _other.getCollect_after_time() && getTrigger_type() == _other.getTrigger_type() && getTrigger_subtype() == _other.getTrigger_subtype());
        }
        inline bool operator!=(const DataCollectTriggerStruct &_other) const {
            return !((*this) == _other);
        }
    
    };
};

const char* IDC1_5SystemFunctions::getInterface() {
    return ("GREATWALL.IDC1_5.IDC1_5SystemFunctions:v1_0");
}

CommonAPI::Version IDC1_5SystemFunctions::getInterfaceVersion() {
    return CommonAPI::Version(1, 0);
}


} // namespace IDC1_5
} // namespace GREATWALL
} // namespace v1

namespace CommonAPI {
}


// Compatibility
namespace v1_0 = v1;

#endif // V1_GREATWALL_IDC1_5_IDC1_5_SYSTEM_FUNCTIONS_HPP_