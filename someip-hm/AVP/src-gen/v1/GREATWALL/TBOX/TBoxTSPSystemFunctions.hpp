/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.1.12.v202002200719.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#ifndef V1_GREATWALL_TBOX_T_BOX_TSP_SYSTEM_FUNCTIONS_HPP_
#define V1_GREATWALL_TBOX_T_BOX_TSP_SYSTEM_FUNCTIONS_HPP_




#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/InputStream.hpp>
#include <CommonAPI/OutputStream.hpp>
#include <CommonAPI/Types.hpp>
#include <cstdint>
#include <string>

#undef COMMONAPI_INTERNAL_COMPILATION

namespace v1 {
namespace GREATWALL {
namespace TBOX {

class TBoxTSPSystemFunctions {
public:
    virtual ~TBoxTSPSystemFunctions() { }

    static inline const char* getInterface();
    static inline CommonAPI::Version getInterfaceVersion();
    
    struct StsResponse : CommonAPI::Enumeration< uint8_t> {
        enum Literal : uint8_t {
            E_RESERVED = 0,
            E_SUCCESS = 1,
            E_FAILED_NETWORK = 2,
            E_FAILED_TSPSERVICE = 3,
            E_FAILED_CIOUDSERVICE = 4
        };
    
        StsResponse()
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(Literal::E_RESERVED)) {}
        StsResponse(Literal _literal)
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(_literal)) {}
    
        inline bool validate() const {
            switch (value_) {
                case static_cast< uint8_t>(Literal::E_RESERVED):
                case static_cast< uint8_t>(Literal::E_SUCCESS):
                case static_cast< uint8_t>(Literal::E_FAILED_NETWORK):
                case static_cast< uint8_t>(Literal::E_FAILED_TSPSERVICE):
                case static_cast< uint8_t>(Literal::E_FAILED_CIOUDSERVICE):
                return true;
            default:
                return false;
            }
        }
    
        inline bool operator==(const StsResponse &_other) const { return (value_ == _other.value_); }
        inline bool operator!=(const StsResponse &_other) const { return (value_ != _other.value_); }
        inline bool operator<=(const StsResponse &_other) const { return (value_ <= _other.value_); }
        inline bool operator>=(const StsResponse &_other) const { return (value_ >= _other.value_); }
        inline bool operator<(const StsResponse &_other) const { return (value_ < _other.value_); }
        inline bool operator>(const StsResponse &_other) const { return (value_ > _other.value_); }
    
        inline bool operator==(const Literal &_value) const { return (value_ == static_cast< uint8_t>(_value)); }
        inline bool operator!=(const Literal &_value) const { return (value_ != static_cast< uint8_t>(_value)); }
        inline bool operator<=(const Literal &_value) const { return (value_ <= static_cast< uint8_t>(_value)); }
        inline bool operator>=(const Literal &_value) const { return (value_ >= static_cast< uint8_t>(_value)); }
        inline bool operator<(const Literal &_value) const { return (value_ < static_cast< uint8_t>(_value)); }
        inline bool operator>(const Literal &_value) const { return (value_ > static_cast< uint8_t>(_value)); }
    };
    typedef std::string StsContent;
    
    struct RegisterResponse : CommonAPI::Enumeration< uint8_t> {
        enum Literal : uint8_t {
            E_RESERVED = 0,
            E_SUCCESS = 1,
            E_FAILED_TSPSERVICE = 2
        };
    
        RegisterResponse()
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(Literal::E_RESERVED)) {}
        RegisterResponse(Literal _literal)
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(_literal)) {}
    
        inline bool validate() const {
            switch (value_) {
                case static_cast< uint8_t>(Literal::E_RESERVED):
                case static_cast< uint8_t>(Literal::E_SUCCESS):
                case static_cast< uint8_t>(Literal::E_FAILED_TSPSERVICE):
                return true;
            default:
                return false;
            }
        }
    
        inline bool operator==(const RegisterResponse &_other) const { return (value_ == _other.value_); }
        inline bool operator!=(const RegisterResponse &_other) const { return (value_ != _other.value_); }
        inline bool operator<=(const RegisterResponse &_other) const { return (value_ <= _other.value_); }
        inline bool operator>=(const RegisterResponse &_other) const { return (value_ >= _other.value_); }
        inline bool operator<(const RegisterResponse &_other) const { return (value_ < _other.value_); }
        inline bool operator>(const RegisterResponse &_other) const { return (value_ > _other.value_); }
    
        inline bool operator==(const Literal &_value) const { return (value_ == static_cast< uint8_t>(_value)); }
        inline bool operator!=(const Literal &_value) const { return (value_ != static_cast< uint8_t>(_value)); }
        inline bool operator<=(const Literal &_value) const { return (value_ <= static_cast< uint8_t>(_value)); }
        inline bool operator>=(const Literal &_value) const { return (value_ >= static_cast< uint8_t>(_value)); }
        inline bool operator<(const Literal &_value) const { return (value_ < static_cast< uint8_t>(_value)); }
        inline bool operator>(const Literal &_value) const { return (value_ > static_cast< uint8_t>(_value)); }
    };
    typedef std::string RegisterContent;
    
    struct StsRequest : CommonAPI::Enumeration< uint8_t> {
        enum Literal : uint8_t {
            E_STSFROMBAIDU = 0,
            E_STSFROMMOMENTA = 1,
            E_SRCFROMBAIDU = 2,
            E_SRCFROMMOMENTA = 3
        };
    
        StsRequest()
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(Literal::E_STSFROMBAIDU)) {}
        StsRequest(Literal _literal)
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(_literal)) {}
    
        inline bool validate() const {
            switch (value_) {
                case static_cast< uint8_t>(Literal::E_STSFROMBAIDU):
                case static_cast< uint8_t>(Literal::E_STSFROMMOMENTA):
                case static_cast< uint8_t>(Literal::E_SRCFROMBAIDU):
                case static_cast< uint8_t>(Literal::E_SRCFROMMOMENTA):
                return true;
            default:
                return false;
            }
        }
    
        inline bool operator==(const StsRequest &_other) const { return (value_ == _other.value_); }
        inline bool operator!=(const StsRequest &_other) const { return (value_ != _other.value_); }
        inline bool operator<=(const StsRequest &_other) const { return (value_ <= _other.value_); }
        inline bool operator>=(const StsRequest &_other) const { return (value_ >= _other.value_); }
        inline bool operator<(const StsRequest &_other) const { return (value_ < _other.value_); }
        inline bool operator>(const StsRequest &_other) const { return (value_ > _other.value_); }
    
        inline bool operator==(const Literal &_value) const { return (value_ == static_cast< uint8_t>(_value)); }
        inline bool operator!=(const Literal &_value) const { return (value_ != static_cast< uint8_t>(_value)); }
        inline bool operator<=(const Literal &_value) const { return (value_ <= static_cast< uint8_t>(_value)); }
        inline bool operator>=(const Literal &_value) const { return (value_ >= static_cast< uint8_t>(_value)); }
        inline bool operator<(const Literal &_value) const { return (value_ < static_cast< uint8_t>(_value)); }
        inline bool operator>(const Literal &_value) const { return (value_ > static_cast< uint8_t>(_value)); }
    };
    
    struct RegisterRequest : CommonAPI::Enumeration< uint8_t> {
        enum Literal : uint8_t {
            E_RESERVED = 0,
            E_REQUEST = 1
        };
    
        RegisterRequest()
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(Literal::E_RESERVED)) {}
        RegisterRequest(Literal _literal)
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(_literal)) {}
    
        inline bool validate() const {
            switch (value_) {
                case static_cast< uint8_t>(Literal::E_RESERVED):
                case static_cast< uint8_t>(Literal::E_REQUEST):
                return true;
            default:
                return false;
            }
        }
    
        inline bool operator==(const RegisterRequest &_other) const { return (value_ == _other.value_); }
        inline bool operator!=(const RegisterRequest &_other) const { return (value_ != _other.value_); }
        inline bool operator<=(const RegisterRequest &_other) const { return (value_ <= _other.value_); }
        inline bool operator>=(const RegisterRequest &_other) const { return (value_ >= _other.value_); }
        inline bool operator<(const RegisterRequest &_other) const { return (value_ < _other.value_); }
        inline bool operator>(const RegisterRequest &_other) const { return (value_ > _other.value_); }
    
        inline bool operator==(const Literal &_value) const { return (value_ == static_cast< uint8_t>(_value)); }
        inline bool operator!=(const Literal &_value) const { return (value_ != static_cast< uint8_t>(_value)); }
        inline bool operator<=(const Literal &_value) const { return (value_ <= static_cast< uint8_t>(_value)); }
        inline bool operator>=(const Literal &_value) const { return (value_ >= static_cast< uint8_t>(_value)); }
        inline bool operator<(const Literal &_value) const { return (value_ < static_cast< uint8_t>(_value)); }
        inline bool operator>(const Literal &_value) const { return (value_ > static_cast< uint8_t>(_value)); }
    };
};

const char* TBoxTSPSystemFunctions::getInterface() {
    return ("GREATWALL.TBOX.TBoxTSPSystemFunctions:v1_0");
}

CommonAPI::Version TBoxTSPSystemFunctions::getInterfaceVersion() {
    return CommonAPI::Version(1, 0);
}


} // namespace TBOX
} // namespace GREATWALL
} // namespace v1

namespace CommonAPI {
}


// Compatibility
namespace v1_0 = v1;

#endif // V1_GREATWALL_TBOX_T_BOX_TSP_SYSTEM_FUNCTIONS_HPP_