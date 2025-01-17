/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.1.12.v202002200719.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#ifndef V1_GREATWALL_TBOX_T_BOX_TSP_COM_HPP_
#define V1_GREATWALL_TBOX_T_BOX_TSP_COM_HPP_




#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/InputStream.hpp>
#include <CommonAPI/OutputStream.hpp>
#include <CommonAPI/Types.hpp>
#include <cstdint>

#undef COMMONAPI_INTERNAL_COMPILATION

namespace v1 {
namespace GREATWALL {
namespace TBOX {

class TBoxTSPCom {
public:
    virtual ~TBoxTSPCom() { }

    static inline const char* getInterface();
    static inline CommonAPI::Version getInterfaceVersion();
    
    struct TBoxTSPLoginState : CommonAPI::Enumeration< uint8_t> {
        enum Literal : uint8_t {
            E_CONNECTING = 0,
            E_CONNECTED = 1,
            E_DISCONNECTED = 2,
            E_NETWORK_UNREACHABLE = 3,
            E_LOGGINGFAIL = 4
        };
    
        TBoxTSPLoginState()
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(Literal::E_CONNECTING)) {}
        TBoxTSPLoginState(Literal _literal)
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(_literal)) {}
    
        inline bool validate() const {
            switch (value_) {
                case static_cast< uint8_t>(Literal::E_CONNECTING):
                case static_cast< uint8_t>(Literal::E_CONNECTED):
                case static_cast< uint8_t>(Literal::E_DISCONNECTED):
                case static_cast< uint8_t>(Literal::E_NETWORK_UNREACHABLE):
                case static_cast< uint8_t>(Literal::E_LOGGINGFAIL):
                return true;
            default:
                return false;
            }
        }
    
        inline bool operator==(const TBoxTSPLoginState &_other) const { return (value_ == _other.value_); }
        inline bool operator!=(const TBoxTSPLoginState &_other) const { return (value_ != _other.value_); }
        inline bool operator<=(const TBoxTSPLoginState &_other) const { return (value_ <= _other.value_); }
        inline bool operator>=(const TBoxTSPLoginState &_other) const { return (value_ >= _other.value_); }
        inline bool operator<(const TBoxTSPLoginState &_other) const { return (value_ < _other.value_); }
        inline bool operator>(const TBoxTSPLoginState &_other) const { return (value_ > _other.value_); }
    
        inline bool operator==(const Literal &_value) const { return (value_ == static_cast< uint8_t>(_value)); }
        inline bool operator!=(const Literal &_value) const { return (value_ != static_cast< uint8_t>(_value)); }
        inline bool operator<=(const Literal &_value) const { return (value_ <= static_cast< uint8_t>(_value)); }
        inline bool operator>=(const Literal &_value) const { return (value_ >= static_cast< uint8_t>(_value)); }
        inline bool operator<(const Literal &_value) const { return (value_ < static_cast< uint8_t>(_value)); }
        inline bool operator>(const Literal &_value) const { return (value_ > static_cast< uint8_t>(_value)); }
    };
};

const char* TBoxTSPCom::getInterface() {
    return ("GREATWALL.TBOX.TBoxTSPCom:v1_0");
}

CommonAPI::Version TBoxTSPCom::getInterfaceVersion() {
    return CommonAPI::Version(1, 0);
}


} // namespace TBOX
} // namespace GREATWALL
} // namespace v1

namespace CommonAPI {
}


// Compatibility
namespace v1_0 = v1;

#endif // V1_GREATWALL_TBOX_T_BOX_TSP_COM_HPP_
