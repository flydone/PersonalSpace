/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.1.12.v202002200719.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#ifndef V1_GREATWALL_TBOX_T_BOX_RESERVATION_FUNCTIONS_HPP_
#define V1_GREATWALL_TBOX_T_BOX_RESERVATION_FUNCTIONS_HPP_




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
namespace TBOX {

class TBoxReservationFunctions {
public:
    virtual ~TBoxReservationFunctions() { }

    static inline const char* getInterface();
    static inline CommonAPI::Version getInterfaceVersion();
    
    struct ChargMode : CommonAPI::Enumeration< uint8_t> {
        enum Literal : uint8_t {
            E_IMMEDIATELY = 0,
            E_RESERVATION = 1
        };
    
        ChargMode()
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(Literal::E_IMMEDIATELY)) {}
        ChargMode(Literal _literal)
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(_literal)) {}
    
        inline bool validate() const {
            switch (value_) {
                case static_cast< uint8_t>(Literal::E_IMMEDIATELY):
                case static_cast< uint8_t>(Literal::E_RESERVATION):
                return true;
            default:
                return false;
            }
        }
    
        inline bool operator==(const ChargMode &_other) const { return (value_ == _other.value_); }
        inline bool operator!=(const ChargMode &_other) const { return (value_ != _other.value_); }
        inline bool operator<=(const ChargMode &_other) const { return (value_ <= _other.value_); }
        inline bool operator>=(const ChargMode &_other) const { return (value_ >= _other.value_); }
        inline bool operator<(const ChargMode &_other) const { return (value_ < _other.value_); }
        inline bool operator>(const ChargMode &_other) const { return (value_ > _other.value_); }
    
        inline bool operator==(const Literal &_value) const { return (value_ == static_cast< uint8_t>(_value)); }
        inline bool operator!=(const Literal &_value) const { return (value_ != static_cast< uint8_t>(_value)); }
        inline bool operator<=(const Literal &_value) const { return (value_ <= static_cast< uint8_t>(_value)); }
        inline bool operator>=(const Literal &_value) const { return (value_ >= static_cast< uint8_t>(_value)); }
        inline bool operator<(const Literal &_value) const { return (value_ < static_cast< uint8_t>(_value)); }
        inline bool operator>(const Literal &_value) const { return (value_ > static_cast< uint8_t>(_value)); }
    };
    
    struct ReservationOperation : CommonAPI::Enumeration< uint8_t> {
        enum Literal : uint8_t {
            E_CANCEL = 0,
            E_SET = 1,
            E_CHANGE = 2
        };
    
        ReservationOperation()
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(Literal::E_CANCEL)) {}
        ReservationOperation(Literal _literal)
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(_literal)) {}
    
        inline bool validate() const {
            switch (value_) {
                case static_cast< uint8_t>(Literal::E_CANCEL):
                case static_cast< uint8_t>(Literal::E_SET):
                case static_cast< uint8_t>(Literal::E_CHANGE):
                return true;
            default:
                return false;
            }
        }
    
        inline bool operator==(const ReservationOperation &_other) const { return (value_ == _other.value_); }
        inline bool operator!=(const ReservationOperation &_other) const { return (value_ != _other.value_); }
        inline bool operator<=(const ReservationOperation &_other) const { return (value_ <= _other.value_); }
        inline bool operator>=(const ReservationOperation &_other) const { return (value_ >= _other.value_); }
        inline bool operator<(const ReservationOperation &_other) const { return (value_ < _other.value_); }
        inline bool operator>(const ReservationOperation &_other) const { return (value_ > _other.value_); }
    
        inline bool operator==(const Literal &_value) const { return (value_ == static_cast< uint8_t>(_value)); }
        inline bool operator!=(const Literal &_value) const { return (value_ != static_cast< uint8_t>(_value)); }
        inline bool operator<=(const Literal &_value) const { return (value_ <= static_cast< uint8_t>(_value)); }
        inline bool operator>=(const Literal &_value) const { return (value_ >= static_cast< uint8_t>(_value)); }
        inline bool operator<(const Literal &_value) const { return (value_ < static_cast< uint8_t>(_value)); }
        inline bool operator>(const Literal &_value) const { return (value_ > static_cast< uint8_t>(_value)); }
    };
    typedef std::vector< uint8_t> TimeArray;
    struct LocalFOTAResParStruct : CommonAPI::Struct< ReservationOperation, TimeArray> {
    
        LocalFOTAResParStruct()
        {
            std::get< 0>(values_) = ReservationOperation();
            std::get< 1>(values_) = TimeArray();
        }
        LocalFOTAResParStruct(const ReservationOperation &_ReservationOperation, const TimeArray &_UpdateTime)
        {
            std::get< 0>(values_) = _ReservationOperation;
            std::get< 1>(values_) = _UpdateTime;
        }
        inline const ReservationOperation &getReservationOperation() const { return std::get< 0>(values_); }
        inline void setReservationOperation(const ReservationOperation &_value) { std::get< 0>(values_) = _value; }
        inline const TimeArray &getUpdateTime() const { return std::get< 1>(values_); }
        inline void setUpdateTime(const TimeArray &_value) { std::get< 1>(values_) = _value; }
        inline bool operator==(const LocalFOTAResParStruct& _other) const {
        return (getReservationOperation() == _other.getReservationOperation() && getUpdateTime() == _other.getUpdateTime());
        }
        inline bool operator!=(const LocalFOTAResParStruct &_other) const {
            return !((*this) == _other);
        }
    
    };
    
    struct ReservationACK : CommonAPI::Enumeration< uint8_t> {
        enum Literal : uint8_t {
            E_ACTIONFAILED = 0,
            E_ACTIONSUCCEED = 1,
            E_ACTIONNOTALLOWED = 2
        };
    
        ReservationACK()
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(Literal::E_ACTIONFAILED)) {}
        ReservationACK(Literal _literal)
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(_literal)) {}
    
        inline bool validate() const {
            switch (value_) {
                case static_cast< uint8_t>(Literal::E_ACTIONFAILED):
                case static_cast< uint8_t>(Literal::E_ACTIONSUCCEED):
                case static_cast< uint8_t>(Literal::E_ACTIONNOTALLOWED):
                return true;
            default:
                return false;
            }
        }
    
        inline bool operator==(const ReservationACK &_other) const { return (value_ == _other.value_); }
        inline bool operator!=(const ReservationACK &_other) const { return (value_ != _other.value_); }
        inline bool operator<=(const ReservationACK &_other) const { return (value_ <= _other.value_); }
        inline bool operator>=(const ReservationACK &_other) const { return (value_ >= _other.value_); }
        inline bool operator<(const ReservationACK &_other) const { return (value_ < _other.value_); }
        inline bool operator>(const ReservationACK &_other) const { return (value_ > _other.value_); }
    
        inline bool operator==(const Literal &_value) const { return (value_ == static_cast< uint8_t>(_value)); }
        inline bool operator!=(const Literal &_value) const { return (value_ != static_cast< uint8_t>(_value)); }
        inline bool operator<=(const Literal &_value) const { return (value_ <= static_cast< uint8_t>(_value)); }
        inline bool operator>=(const Literal &_value) const { return (value_ >= static_cast< uint8_t>(_value)); }
        inline bool operator<(const Literal &_value) const { return (value_ < static_cast< uint8_t>(_value)); }
        inline bool operator>(const Literal &_value) const { return (value_ > static_cast< uint8_t>(_value)); }
    };
    
    struct Repeat : CommonAPI::Enumeration< uint8_t> {
        enum Literal : uint8_t {
            E_ONLYONCE = 0,
            E_EVERYDAY = 1
        };
    
        Repeat()
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(Literal::E_ONLYONCE)) {}
        Repeat(Literal _literal)
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(_literal)) {}
    
        inline bool validate() const {
            switch (value_) {
                case static_cast< uint8_t>(Literal::E_ONLYONCE):
                case static_cast< uint8_t>(Literal::E_EVERYDAY):
                return true;
            default:
                return false;
            }
        }
    
        inline bool operator==(const Repeat &_other) const { return (value_ == _other.value_); }
        inline bool operator!=(const Repeat &_other) const { return (value_ != _other.value_); }
        inline bool operator<=(const Repeat &_other) const { return (value_ <= _other.value_); }
        inline bool operator>=(const Repeat &_other) const { return (value_ >= _other.value_); }
        inline bool operator<(const Repeat &_other) const { return (value_ < _other.value_); }
        inline bool operator>(const Repeat &_other) const { return (value_ > _other.value_); }
    
        inline bool operator==(const Literal &_value) const { return (value_ == static_cast< uint8_t>(_value)); }
        inline bool operator!=(const Literal &_value) const { return (value_ != static_cast< uint8_t>(_value)); }
        inline bool operator<=(const Literal &_value) const { return (value_ <= static_cast< uint8_t>(_value)); }
        inline bool operator>=(const Literal &_value) const { return (value_ >= static_cast< uint8_t>(_value)); }
        inline bool operator<(const Literal &_value) const { return (value_ < static_cast< uint8_t>(_value)); }
        inline bool operator>(const Literal &_value) const { return (value_ > static_cast< uint8_t>(_value)); }
    };
    struct LocalChargeResParStruct : CommonAPI::Struct< ChargMode, TimeArray, Repeat, TimeArray> {
    
        LocalChargeResParStruct()
        {
            std::get< 0>(values_) = ChargMode();
            std::get< 1>(values_) = TimeArray();
            std::get< 2>(values_) = Repeat();
            std::get< 3>(values_) = TimeArray();
        }
        LocalChargeResParStruct(const ChargMode &_ChargMode, const TimeArray &_StartTime, const Repeat &_Repeat, const TimeArray &_EndTime)
        {
            std::get< 0>(values_) = _ChargMode;
            std::get< 1>(values_) = _StartTime;
            std::get< 2>(values_) = _Repeat;
            std::get< 3>(values_) = _EndTime;
        }
        inline const ChargMode &getChargMode() const { return std::get< 0>(values_); }
        inline void setChargMode(const ChargMode &_value) { std::get< 0>(values_) = _value; }
        inline const TimeArray &getStartTime() const { return std::get< 1>(values_); }
        inline void setStartTime(const TimeArray &_value) { std::get< 1>(values_) = _value; }
        inline const Repeat &getRepeat() const { return std::get< 2>(values_); }
        inline void setRepeat(const Repeat &_value) { std::get< 2>(values_) = _value; }
        inline const TimeArray &getEndTime() const { return std::get< 3>(values_); }
        inline void setEndTime(const TimeArray &_value) { std::get< 3>(values_) = _value; }
        inline bool operator==(const LocalChargeResParStruct& _other) const {
        return (getChargMode() == _other.getChargMode() && getStartTime() == _other.getStartTime() && getRepeat() == _other.getRepeat() && getEndTime() == _other.getEndTime());
        }
        inline bool operator!=(const LocalChargeResParStruct &_other) const {
            return !((*this) == _other);
        }
    
    };
};

const char* TBoxReservationFunctions::getInterface() {
    return ("GREATWALL.TBOX.TBoxReservationFunctions:v1_0");
}

CommonAPI::Version TBoxReservationFunctions::getInterfaceVersion() {
    return CommonAPI::Version(1, 0);
}


} // namespace TBOX
} // namespace GREATWALL
} // namespace v1

namespace CommonAPI {
}


// Compatibility
namespace v1_0 = v1;

#endif // V1_GREATWALL_TBOX_T_BOX_RESERVATION_FUNCTIONS_HPP_