/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.1.12.v202002200719.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#ifndef V1_GREATWALL_TBOX_T_Box_Telephony_PROXY_BASE_HPP_
#define V1_GREATWALL_TBOX_T_Box_Telephony_PROXY_BASE_HPP_

#include <v1/GREATWALL/TBOX/TBoxTelephony.hpp>



#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/Deployment.hpp>
#include <CommonAPI/InputStream.hpp>
#include <CommonAPI/OutputStream.hpp>
#include <CommonAPI/Struct.hpp>
#include <cstdint>
#include <string>
#include <vector>

#include <CommonAPI/Attribute.hpp>
#include <CommonAPI/Event.hpp>
#include <CommonAPI/Proxy.hpp>
#include <functional>
#include <future>

#undef COMMONAPI_INTERNAL_COMPILATION

namespace v1 {
namespace GREATWALL {
namespace TBOX {

class TBoxTelephonyProxyBase
    : virtual public CommonAPI::Proxy {
public:
    typedef CommonAPI::ObservableReadonlyAttribute< ::v1::GREATWALL::TBOX::TBoxTelephony::TBoxSimStatusStruct> TBoxSimStatusAttribute;
    typedef CommonAPI::ObservableReadonlyAttribute< ::v1::GREATWALL::TBOX::TBoxTelephony::TBoxSignalStrengthStruct> TBoxSignalStrengthAttribute;
    typedef CommonAPI::ObservableReadonlyAttribute< ::v1::GREATWALL::TBOX::TBoxTelephony::TBoxNetworkProviderStruct> TBoxNetworkProviderAttribute;
    typedef CommonAPI::Event<
        ::v1::GREATWALL::TBOX::TBoxTelephony::TBoxTelephoneNumber, ::v1::GREATWALL::TBOX::TBoxTelephony::TBoxCallType, ::v1::GREATWALL::TBOX::TBoxTelephony::TBoxCallState, ::v1::GREATWALL::TBOX::TBoxTelephony::long64
    > TBoxCallStateEvent;

    typedef std::function<void(const CommonAPI::CallStatus&, const TBoxTelephony::TBoxResponse&, const TBoxTelephony::long64&)> TBoxCallOperationAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const TBoxTelephony::ICCID&, const TBoxTelephony::IMEI&, const TBoxTelephony::IMSI&)> TBoxSIMInforAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const TBoxTelephony::TBoxResponse&, const TBoxTelephony::long64&)> TBoxStartCallAsyncCallback;

    virtual TBoxSimStatusAttribute& getTBoxSimStatusAttribute() = 0;
    virtual TBoxSignalStrengthAttribute& getTBoxSignalStrengthAttribute() = 0;
    virtual TBoxNetworkProviderAttribute& getTBoxNetworkProviderAttribute() = 0;

    virtual TBoxCallStateEvent& getTBoxCallStateEvent() = 0;

    virtual void TBoxCallOperation(const TBoxTelephony::TBoxTelephoneNumber &_TBoxTelephoneNumber, const TBoxTelephony::TBoxCallType &_TBoxCallType, const TBoxTelephony::TBoxCallOperation &_TBoxCallOperation, const TBoxTelephony::long64 &_TBoxCallID_In, CommonAPI::CallStatus &_internalCallStatus, TBoxTelephony::TBoxResponse &_TBoxResponse, TBoxTelephony::long64 &_TBoxCallID_Out, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> TBoxCallOperationAsync(const TBoxTelephony::TBoxTelephoneNumber &_TBoxTelephoneNumber, const TBoxTelephony::TBoxCallType &_TBoxCallType, const TBoxTelephony::TBoxCallOperation &_TBoxCallOperation, const TBoxTelephony::long64 &_TBoxCallID_In, TBoxCallOperationAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual void TBoxSIMInfor(CommonAPI::CallStatus &_internalCallStatus, TBoxTelephony::ICCID &_ICCID, TBoxTelephony::IMEI &_IMEI, TBoxTelephony::IMSI &_IMSI, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> TBoxSIMInforAsync(TBoxSIMInforAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual void TBoxStartCall(const TBoxTelephony::TBoxTelephoneNumber &_TBoxTelephoneNumber, const TBoxTelephony::TBoxCallType &_TBoxCallType, const TBoxTelephony::long64 &_TBoxCallID_In, CommonAPI::CallStatus &_internalCallStatus, TBoxTelephony::TBoxResponse &_TBoxResponse, TBoxTelephony::long64 &_TBoxCallID_Out, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> TBoxStartCallAsync(const TBoxTelephony::TBoxTelephoneNumber &_TBoxTelephoneNumber, const TBoxTelephony::TBoxCallType &_TBoxCallType, const TBoxTelephony::long64 &_TBoxCallID_In, TBoxStartCallAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
};

} // namespace TBOX
} // namespace GREATWALL
} // namespace v1


// Compatibility
namespace v1_0 = v1;

#endif // V1_GREATWALL_TBOX_T_Box_Telephony_PROXY_BASE_HPP_