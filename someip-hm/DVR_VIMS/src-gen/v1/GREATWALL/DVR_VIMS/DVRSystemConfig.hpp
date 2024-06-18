/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.1.12.v202002200719.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#ifndef V1_GREATWALL_DVR_VIMS_DVR_SYSTEM_CONFIG_HPP_
#define V1_GREATWALL_DVR_VIMS_DVR_SYSTEM_CONFIG_HPP_




#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/Deployment.hpp>
#include <CommonAPI/InputStream.hpp>
#include <CommonAPI/OutputStream.hpp>
#include <CommonAPI/Struct.hpp>
#include <CommonAPI/Types.hpp>
#include <cstdint>
#include <string>
#include <vector>

#undef COMMONAPI_INTERNAL_COMPILATION

namespace v1 {
namespace GREATWALL {
namespace DVR_VIMS {

class DVRSystemConfig {
public:
    virtual ~DVRSystemConfig() { }

    static inline const char* getInterface();
    static inline CommonAPI::Version getInterfaceVersion();
    
    struct GetAllConfig : CommonAPI::Enumeration< uint8_t> {
        enum Literal : uint8_t {
            E_GET_ALL_CONFIG = 0,
            E_GET_ARRAY_CONFIG = 1
        };
    
        GetAllConfig()
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(Literal::E_GET_ALL_CONFIG)) {}
        GetAllConfig(Literal _literal)
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(_literal)) {}
    
        inline bool validate() const {
            switch (value_) {
                case static_cast< uint8_t>(Literal::E_GET_ALL_CONFIG):
                case static_cast< uint8_t>(Literal::E_GET_ARRAY_CONFIG):
                return true;
            default:
                return false;
            }
        }
    
        inline bool operator==(const GetAllConfig &_other) const { return (value_ == _other.value_); }
        inline bool operator!=(const GetAllConfig &_other) const { return (value_ != _other.value_); }
        inline bool operator<=(const GetAllConfig &_other) const { return (value_ <= _other.value_); }
        inline bool operator>=(const GetAllConfig &_other) const { return (value_ >= _other.value_); }
        inline bool operator<(const GetAllConfig &_other) const { return (value_ < _other.value_); }
        inline bool operator>(const GetAllConfig &_other) const { return (value_ > _other.value_); }
    
        inline bool operator==(const Literal &_value) const { return (value_ == static_cast< uint8_t>(_value)); }
        inline bool operator!=(const Literal &_value) const { return (value_ != static_cast< uint8_t>(_value)); }
        inline bool operator<=(const Literal &_value) const { return (value_ <= static_cast< uint8_t>(_value)); }
        inline bool operator>=(const Literal &_value) const { return (value_ >= static_cast< uint8_t>(_value)); }
        inline bool operator<(const Literal &_value) const { return (value_ < static_cast< uint8_t>(_value)); }
        inline bool operator>(const Literal &_value) const { return (value_ > static_cast< uint8_t>(_value)); }
    };
    
    struct SetResult : CommonAPI::Enumeration< uint8_t> {
        enum Literal : uint8_t {
            E_SUCCESSFUL = 0,
            E_FAILED = 1
        };
    
        SetResult()
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(Literal::E_SUCCESSFUL)) {}
        SetResult(Literal _literal)
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(_literal)) {}
    
        inline bool validate() const {
            switch (value_) {
                case static_cast< uint8_t>(Literal::E_SUCCESSFUL):
                case static_cast< uint8_t>(Literal::E_FAILED):
                return true;
            default:
                return false;
            }
        }
    
        inline bool operator==(const SetResult &_other) const { return (value_ == _other.value_); }
        inline bool operator!=(const SetResult &_other) const { return (value_ != _other.value_); }
        inline bool operator<=(const SetResult &_other) const { return (value_ <= _other.value_); }
        inline bool operator>=(const SetResult &_other) const { return (value_ >= _other.value_); }
        inline bool operator<(const SetResult &_other) const { return (value_ < _other.value_); }
        inline bool operator>(const SetResult &_other) const { return (value_ > _other.value_); }
    
        inline bool operator==(const Literal &_value) const { return (value_ == static_cast< uint8_t>(_value)); }
        inline bool operator!=(const Literal &_value) const { return (value_ != static_cast< uint8_t>(_value)); }
        inline bool operator<=(const Literal &_value) const { return (value_ <= static_cast< uint8_t>(_value)); }
        inline bool operator>=(const Literal &_value) const { return (value_ >= static_cast< uint8_t>(_value)); }
        inline bool operator<(const Literal &_value) const { return (value_ < static_cast< uint8_t>(_value)); }
        inline bool operator>(const Literal &_value) const { return (value_ > static_cast< uint8_t>(_value)); }
    };
    
    struct ParamConfigType : CommonAPI::Enumeration< uint8_t> {
        enum Literal : uint8_t {
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
        };
    
        ParamConfigType()
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(Literal::E_SETWIDEDYNAMICMODE)) {}
        ParamConfigType(Literal _literal)
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(_literal)) {}
    
        inline bool validate() const {
            switch (value_) {
                case static_cast< uint8_t>(Literal::E_SETWIDEDYNAMICMODE):
                case static_cast< uint8_t>(Literal::E_SETSEGMENTRECORDINGTIME):
                case static_cast< uint8_t>(Literal::E_SETPOWEROFFDELAY):
                case static_cast< uint8_t>(Literal::E_SETEVENTVIDEOCYCLECOVERAGE):
                case static_cast< uint8_t>(Literal::E_SETTAPERECORDING):
                case static_cast< uint8_t>(Literal::E_SETCYCLEVIDEOTAPEMODE):
                case static_cast< uint8_t>(Literal::E_SETINTERIORCAMERA):
                case static_cast< uint8_t>(Literal::E_SET360SURROUNDVIEW):
                case static_cast< uint8_t>(Literal::E_SETPARKMONITOR):
                case static_cast< uint8_t>(Literal::E_SETOSDINFO):
                return true;
            default:
                return false;
            }
        }
    
        inline bool operator==(const ParamConfigType &_other) const { return (value_ == _other.value_); }
        inline bool operator!=(const ParamConfigType &_other) const { return (value_ != _other.value_); }
        inline bool operator<=(const ParamConfigType &_other) const { return (value_ <= _other.value_); }
        inline bool operator>=(const ParamConfigType &_other) const { return (value_ >= _other.value_); }
        inline bool operator<(const ParamConfigType &_other) const { return (value_ < _other.value_); }
        inline bool operator>(const ParamConfigType &_other) const { return (value_ > _other.value_); }
    
        inline bool operator==(const Literal &_value) const { return (value_ == static_cast< uint8_t>(_value)); }
        inline bool operator!=(const Literal &_value) const { return (value_ != static_cast< uint8_t>(_value)); }
        inline bool operator<=(const Literal &_value) const { return (value_ <= static_cast< uint8_t>(_value)); }
        inline bool operator>=(const Literal &_value) const { return (value_ >= static_cast< uint8_t>(_value)); }
        inline bool operator<(const Literal &_value) const { return (value_ < static_cast< uint8_t>(_value)); }
        inline bool operator>(const Literal &_value) const { return (value_ > static_cast< uint8_t>(_value)); }
    };
    typedef std::vector< DVRSystemConfig::ParamConfigType> ConfigTypeList;
    
    struct ResetConfigType : CommonAPI::Enumeration< uint8_t> {
        enum Literal : uint8_t {
            E_RESUMEFACTORY = 0,
            E_PATCHUPGRADE = 1
        };
    
        ResetConfigType()
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(Literal::E_RESUMEFACTORY)) {}
        ResetConfigType(Literal _literal)
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(_literal)) {}
    
        inline bool validate() const {
            switch (value_) {
                case static_cast< uint8_t>(Literal::E_RESUMEFACTORY):
                case static_cast< uint8_t>(Literal::E_PATCHUPGRADE):
                return true;
            default:
                return false;
            }
        }
    
        inline bool operator==(const ResetConfigType &_other) const { return (value_ == _other.value_); }
        inline bool operator!=(const ResetConfigType &_other) const { return (value_ != _other.value_); }
        inline bool operator<=(const ResetConfigType &_other) const { return (value_ <= _other.value_); }
        inline bool operator>=(const ResetConfigType &_other) const { return (value_ >= _other.value_); }
        inline bool operator<(const ResetConfigType &_other) const { return (value_ < _other.value_); }
        inline bool operator>(const ResetConfigType &_other) const { return (value_ > _other.value_); }
    
        inline bool operator==(const Literal &_value) const { return (value_ == static_cast< uint8_t>(_value)); }
        inline bool operator!=(const Literal &_value) const { return (value_ != static_cast< uint8_t>(_value)); }
        inline bool operator<=(const Literal &_value) const { return (value_ <= static_cast< uint8_t>(_value)); }
        inline bool operator>=(const Literal &_value) const { return (value_ >= static_cast< uint8_t>(_value)); }
        inline bool operator<(const Literal &_value) const { return (value_ < static_cast< uint8_t>(_value)); }
        inline bool operator>(const Literal &_value) const { return (value_ > static_cast< uint8_t>(_value)); }
    };
    
    struct ConfigParamValueType : CommonAPI::Enumeration< uint8_t> {
        enum Literal : uint8_t {
            E_UINT8 = 0,
            E_UINT16 = 1,
            E_UINT32 = 2,
            E_UINT64 = 3,
            E_UTF8 = 4,
            E_ENUM = 5,
            E_BOOL = 6
        };
    
        ConfigParamValueType()
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(Literal::E_UINT8)) {}
        ConfigParamValueType(Literal _literal)
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(_literal)) {}
    
        inline bool validate() const {
            switch (value_) {
                case static_cast< uint8_t>(Literal::E_UINT8):
                case static_cast< uint8_t>(Literal::E_UINT16):
                case static_cast< uint8_t>(Literal::E_UINT32):
                case static_cast< uint8_t>(Literal::E_UINT64):
                case static_cast< uint8_t>(Literal::E_UTF8):
                case static_cast< uint8_t>(Literal::E_ENUM):
                case static_cast< uint8_t>(Literal::E_BOOL):
                return true;
            default:
                return false;
            }
        }
    
        inline bool operator==(const ConfigParamValueType &_other) const { return (value_ == _other.value_); }
        inline bool operator!=(const ConfigParamValueType &_other) const { return (value_ != _other.value_); }
        inline bool operator<=(const ConfigParamValueType &_other) const { return (value_ <= _other.value_); }
        inline bool operator>=(const ConfigParamValueType &_other) const { return (value_ >= _other.value_); }
        inline bool operator<(const ConfigParamValueType &_other) const { return (value_ < _other.value_); }
        inline bool operator>(const ConfigParamValueType &_other) const { return (value_ > _other.value_); }
    
        inline bool operator==(const Literal &_value) const { return (value_ == static_cast< uint8_t>(_value)); }
        inline bool operator!=(const Literal &_value) const { return (value_ != static_cast< uint8_t>(_value)); }
        inline bool operator<=(const Literal &_value) const { return (value_ <= static_cast< uint8_t>(_value)); }
        inline bool operator>=(const Literal &_value) const { return (value_ >= static_cast< uint8_t>(_value)); }
        inline bool operator<(const Literal &_value) const { return (value_ < static_cast< uint8_t>(_value)); }
        inline bool operator>(const Literal &_value) const { return (value_ > static_cast< uint8_t>(_value)); }
    };
    typedef std::string ConfigInfo;
    
    struct ParamConfigOperation : CommonAPI::Enumeration< uint8_t> {
        enum Literal : uint8_t {
            E_ON = 0,
            E_OFF = 1,
            E_0S = 2,
            E_10S = 3,
            E_60SOR1MINUTE = 4,
            E_3MINUTE = 5,
            E_5MINUTE = 6
        };
    
        ParamConfigOperation()
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(Literal::E_ON)) {}
        ParamConfigOperation(Literal _literal)
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(_literal)) {}
    
        inline bool validate() const {
            switch (value_) {
                case static_cast< uint8_t>(Literal::E_ON):
                case static_cast< uint8_t>(Literal::E_OFF):
                case static_cast< uint8_t>(Literal::E_0S):
                case static_cast< uint8_t>(Literal::E_10S):
                case static_cast< uint8_t>(Literal::E_60SOR1MINUTE):
                case static_cast< uint8_t>(Literal::E_3MINUTE):
                case static_cast< uint8_t>(Literal::E_5MINUTE):
                return true;
            default:
                return false;
            }
        }
    
        inline bool operator==(const ParamConfigOperation &_other) const { return (value_ == _other.value_); }
        inline bool operator!=(const ParamConfigOperation &_other) const { return (value_ != _other.value_); }
        inline bool operator<=(const ParamConfigOperation &_other) const { return (value_ <= _other.value_); }
        inline bool operator>=(const ParamConfigOperation &_other) const { return (value_ >= _other.value_); }
        inline bool operator<(const ParamConfigOperation &_other) const { return (value_ < _other.value_); }
        inline bool operator>(const ParamConfigOperation &_other) const { return (value_ > _other.value_); }
    
        inline bool operator==(const Literal &_value) const { return (value_ == static_cast< uint8_t>(_value)); }
        inline bool operator!=(const Literal &_value) const { return (value_ != static_cast< uint8_t>(_value)); }
        inline bool operator<=(const Literal &_value) const { return (value_ <= static_cast< uint8_t>(_value)); }
        inline bool operator>=(const Literal &_value) const { return (value_ >= static_cast< uint8_t>(_value)); }
        inline bool operator<(const Literal &_value) const { return (value_ < static_cast< uint8_t>(_value)); }
        inline bool operator>(const Literal &_value) const { return (value_ > static_cast< uint8_t>(_value)); }
    };
    struct ParamCofigStruct : CommonAPI::Struct< ConfigParamValueType, ParamConfigType, ParamConfigOperation, ConfigInfo> {
    
        ParamCofigStruct()
        {
            std::get< 0>(values_) = ConfigParamValueType();
            std::get< 1>(values_) = ParamConfigType();
            std::get< 2>(values_) = ParamConfigOperation();
            std::get< 3>(values_) = ConfigInfo();
        }
        ParamCofigStruct(const ConfigParamValueType &_ConfigParamValueType, const ParamConfigType &_ParamConfigType, const ParamConfigOperation &_ParamConfigOperation, const ConfigInfo &_ConfigInfo)
        {
            std::get< 0>(values_) = _ConfigParamValueType;
            std::get< 1>(values_) = _ParamConfigType;
            std::get< 2>(values_) = _ParamConfigOperation;
            std::get< 3>(values_) = _ConfigInfo;
        }
        inline const ConfigParamValueType &getConfigParamValueType() const { return std::get< 0>(values_); }
        inline void setConfigParamValueType(const ConfigParamValueType &_value) { std::get< 0>(values_) = _value; }
        inline const ParamConfigType &getParamConfigType() const { return std::get< 1>(values_); }
        inline void setParamConfigType(const ParamConfigType &_value) { std::get< 1>(values_) = _value; }
        inline const ParamConfigOperation &getParamConfigOperation() const { return std::get< 2>(values_); }
        inline void setParamConfigOperation(const ParamConfigOperation &_value) { std::get< 2>(values_) = _value; }
        inline const ConfigInfo &getConfigInfo() const { return std::get< 3>(values_); }
        inline void setConfigInfo(const ConfigInfo &_value) { std::get< 3>(values_) = _value; }
        inline bool operator==(const ParamCofigStruct& _other) const {
        return (getConfigParamValueType() == _other.getConfigParamValueType() && getParamConfigType() == _other.getParamConfigType() && getParamConfigOperation() == _other.getParamConfigOperation() && getConfigInfo() == _other.getConfigInfo());
        }
        inline bool operator!=(const ParamCofigStruct &_other) const {
            return !((*this) == _other);
        }
    
    };
    typedef std::vector< DVRSystemConfig::ParamCofigStruct> ConfigListArray;
};

const char* DVRSystemConfig::getInterface() {
    return ("GREATWALL.DVR_VIMS.DVRSystemConfig:v1_0");
}

CommonAPI::Version DVRSystemConfig::getInterfaceVersion() {
    return CommonAPI::Version(1, 0);
}


} // namespace DVR_VIMS
} // namespace GREATWALL
} // namespace v1

namespace CommonAPI {
}


// Compatibility
namespace v1_0 = v1;

#endif // V1_GREATWALL_DVR_VIMS_DVR_SYSTEM_CONFIG_HPP_
