/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.someip 3.1.12.v202002200807.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#include <v1/GREATWALL/TBOX/TBoxTSPSystemFunctionsSomeIPProxy.hpp>

#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/SomeIP/AddressTranslator.hpp>

#undef COMMONAPI_INTERNAL_COMPILATION

namespace v1 {
namespace GREATWALL {
namespace TBOX {

std::shared_ptr<CommonAPI::SomeIP::Proxy> createTBoxTSPSystemFunctionsSomeIPProxy(
    const CommonAPI::SomeIP::Address &_address,
    const std::shared_ptr<CommonAPI::SomeIP::ProxyConnection> &_connection) {
    return std::make_shared< TBoxTSPSystemFunctionsSomeIPProxy>(_address, _connection);
}

void initializeTBoxTSPSystemFunctionsSomeIPProxy() {
    CommonAPI::SomeIP::AddressTranslator::get()->insert(
        "local:GREATWALL.TBOX.TBoxTSPSystemFunctions:v1_0:TBoxTSPSystemFunctions01",
        0x207, 0x1, 1, 0);
     CommonAPI::SomeIP::Factory::get()->registerProxyCreateMethod(
         TBoxTSPSystemFunctions::getInterface(),
         &createTBoxTSPSystemFunctionsSomeIPProxy);
}

INITIALIZER(registerTBoxTSPSystemFunctionsSomeIPProxy) {
    CommonAPI::SomeIP::Factory::get()->registerInterface(initializeTBoxTSPSystemFunctionsSomeIPProxy);
}

TBoxTSPSystemFunctionsSomeIPProxy::TBoxTSPSystemFunctionsSomeIPProxy(
    const CommonAPI::SomeIP::Address &_address,
    const std::shared_ptr<CommonAPI::SomeIP::ProxyConnection> &_connection)
        : CommonAPI::SomeIP::Proxy(_address, _connection )
,          stsResponse_(*this, 0x2, CommonAPI::SomeIP::event_id_t(0x8001), false, false, std::make_tuple(static_cast< ::v1::GREATWALL::TBOX::TBoxTSPSystemFunctions_::StsResponseDeployment_t* >(nullptr))),
          stsContent_(*this, 0x2, CommonAPI::SomeIP::event_id_t(0x8002), false, false, std::make_tuple(static_cast< CommonAPI::SomeIP::StringDeployment* >(nullptr))),
          registerContent_(*this, 0x3, CommonAPI::SomeIP::event_id_t(0x8004), false, false, std::make_tuple(static_cast< CommonAPI::SomeIP::StringDeployment* >(nullptr))),
          registerResponse_(*this, 0x3, CommonAPI::SomeIP::event_id_t(0x8003), false, false, std::make_tuple(static_cast< ::v1::GREATWALL::TBOX::TBoxTSPSystemFunctions_::RegisterResponseDeployment_t* >(nullptr)))
    {
    }


    TBoxTSPSystemFunctionsSomeIPProxy::StsResponseEvent& TBoxTSPSystemFunctionsSomeIPProxy::getStsResponseEvent() {
        return stsResponse_;
    }
    TBoxTSPSystemFunctionsSomeIPProxy::StsContentEvent& TBoxTSPSystemFunctionsSomeIPProxy::getStsContentEvent() {
        return stsContent_;
    }
    TBoxTSPSystemFunctionsSomeIPProxy::RegisterContentEvent& TBoxTSPSystemFunctionsSomeIPProxy::getRegisterContentEvent() {
        return registerContent_;
    }
    TBoxTSPSystemFunctionsSomeIPProxy::RegisterResponseEvent& TBoxTSPSystemFunctionsSomeIPProxy::getRegisterResponseEvent() {
        return registerResponse_;
    }

        void TBoxTSPSystemFunctionsSomeIPProxy::StsRequest(const TBoxTSPSystemFunctions::StsRequest &_StsRequest, CommonAPI::CallStatus &_internalCallStatus) {
            CommonAPI::Deployable< TBoxTSPSystemFunctions::StsRequest, ::v1::GREATWALL::TBOX::TBoxTSPSystemFunctions_::StsRequestDeployment_t> deploy_StsRequest(_StsRequest, static_cast< ::v1::GREATWALL::TBOX::TBoxTSPSystemFunctions_::StsRequestDeployment_t* >(nullptr));
            CommonAPI::SomeIP::ProxyHelper<
                CommonAPI::SomeIP::SerializableArguments<
                    CommonAPI::Deployable<
                        TBoxTSPSystemFunctions::StsRequest,
                        ::v1::GREATWALL::TBOX::TBoxTSPSystemFunctions_::StsRequestDeployment_t
                    >
                >,
                CommonAPI::SomeIP::SerializableArguments<
                >
            >::callMethod(
            *this,
            CommonAPI::SomeIP::method_id_t(0x1001),
            true,
            false,
    deploy_StsRequest,
    _internalCallStatus);
    }
        void TBoxTSPSystemFunctionsSomeIPProxy::RegisterRequest(const TBoxTSPSystemFunctions::RegisterRequest &_RegisterRequest, CommonAPI::CallStatus &_internalCallStatus) {
            CommonAPI::Deployable< TBoxTSPSystemFunctions::RegisterRequest, ::v1::GREATWALL::TBOX::TBoxTSPSystemFunctions_::RegisterRequestDeployment_t> deploy_RegisterRequest(_RegisterRequest, static_cast< ::v1::GREATWALL::TBOX::TBoxTSPSystemFunctions_::RegisterRequestDeployment_t* >(nullptr));
            CommonAPI::SomeIP::ProxyHelper<
                CommonAPI::SomeIP::SerializableArguments<
                    CommonAPI::Deployable<
                        TBoxTSPSystemFunctions::RegisterRequest,
                        ::v1::GREATWALL::TBOX::TBoxTSPSystemFunctions_::RegisterRequestDeployment_t
                    >
                >,
                CommonAPI::SomeIP::SerializableArguments<
                >
            >::callMethod(
            *this,
            CommonAPI::SomeIP::method_id_t(0x1002),
            true,
            false,
    deploy_RegisterRequest,
    _internalCallStatus);
    }



    void TBoxTSPSystemFunctionsSomeIPProxy::getOwnVersion(uint16_t& ownVersionMajor, uint16_t& ownVersionMinor) const {
    ownVersionMajor = 1;
    ownVersionMinor = 0;
    }

} // namespace TBOX
} // namespace GREATWALL
} // namespace v1
