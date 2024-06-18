/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.someip 3.1.12.v202002200807.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#include <v1/GREATWALL/IDC1_5/IDC1_5SystemFunctionsSomeIPProxy.hpp>

#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/SomeIP/AddressTranslator.hpp>

#undef COMMONAPI_INTERNAL_COMPILATION

namespace v1 {
namespace GREATWALL {
namespace IDC1_5 {

std::shared_ptr<CommonAPI::SomeIP::Proxy> createIDC1_5SystemFunctionsSomeIPProxy(
    const CommonAPI::SomeIP::Address &_address,
    const std::shared_ptr<CommonAPI::SomeIP::ProxyConnection> &_connection) {
    return std::make_shared< IDC1_5SystemFunctionsSomeIPProxy>(_address, _connection);
}

void initializeIDC1_5SystemFunctionsSomeIPProxy() {
    CommonAPI::SomeIP::AddressTranslator::get()->insert(
        "local:GREATWALL.IDC1_5.IDC1_5SystemFunctions:v1_0:IDC1_5SystemFunctions01",
        0xb01, 0x1, 1, 0);
     CommonAPI::SomeIP::Factory::get()->registerProxyCreateMethod(
         IDC1_5SystemFunctions::getInterface(),
         &createIDC1_5SystemFunctionsSomeIPProxy);
}

INITIALIZER(registerIDC1_5SystemFunctionsSomeIPProxy) {
    CommonAPI::SomeIP::Factory::get()->registerInterface(initializeIDC1_5SystemFunctionsSomeIPProxy);
}

IDC1_5SystemFunctionsSomeIPProxy::IDC1_5SystemFunctionsSomeIPProxy(
    const CommonAPI::SomeIP::Address &_address,
    const std::shared_ptr<CommonAPI::SomeIP::ProxyConnection> &_connection)
        : CommonAPI::SomeIP::Proxy(_address, _connection )
,          videoUpload_(*this, 0x1, CommonAPI::SomeIP::event_id_t(0x8001), false, false, std::make_tuple(static_cast< ::v1::GREATWALL::IDC1_5::IDC1_5SystemFunctions_::DataCollectTriggerStructDeployment_t* >(nullptr)))
    {
    }


    IDC1_5SystemFunctionsSomeIPProxy::VideoUploadEvent& IDC1_5SystemFunctionsSomeIPProxy::getVideoUploadEvent() {
        return videoUpload_;
    }




    void IDC1_5SystemFunctionsSomeIPProxy::getOwnVersion(uint16_t& ownVersionMajor, uint16_t& ownVersionMinor) const {
    ownVersionMajor = 1;
    ownVersionMinor = 0;
    }

} // namespace IDC1_5
} // namespace GREATWALL
} // namespace v1