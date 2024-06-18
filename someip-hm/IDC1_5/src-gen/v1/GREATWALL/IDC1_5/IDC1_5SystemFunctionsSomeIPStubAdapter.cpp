/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.someip 3.1.12.v202002200807.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#include <v1/GREATWALL/IDC1_5/IDC1_5SystemFunctionsSomeIPStubAdapter.hpp>
#include <v1/GREATWALL/IDC1_5/IDC1_5SystemFunctions.hpp>

#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/SomeIP/AddressTranslator.hpp>

#undef COMMONAPI_INTERNAL_COMPILATION

namespace v1 {
namespace GREATWALL {
namespace IDC1_5 {

std::shared_ptr<CommonAPI::SomeIP::StubAdapter> createIDC1_5SystemFunctionsSomeIPStubAdapter(
                   const CommonAPI::SomeIP::Address &_address,
                   const std::shared_ptr<CommonAPI::SomeIP::ProxyConnection> &_connection,
                   const std::shared_ptr<CommonAPI::StubBase> &_stub) {
    return std::make_shared< IDC1_5SystemFunctionsSomeIPStubAdapter<::v1::GREATWALL::IDC1_5::IDC1_5SystemFunctionsStub>>(_address, _connection, _stub);
}

void initializeIDC1_5SystemFunctionsSomeIPStubAdapter() {
    CommonAPI::SomeIP::AddressTranslator::get()->insert(
        "local:GREATWALL.IDC1_5.IDC1_5SystemFunctions:v1_0:IDC1_5SystemFunctions01",
         0xb01, 0x1, 1, 0);
    CommonAPI::SomeIP::Factory::get()->registerStubAdapterCreateMethod(
        IDC1_5SystemFunctions::getInterface(),
        &createIDC1_5SystemFunctionsSomeIPStubAdapter);
}

INITIALIZER(registerIDC1_5SystemFunctionsSomeIPStubAdapter) {
    CommonAPI::SomeIP::Factory::get()->registerInterface(initializeIDC1_5SystemFunctionsSomeIPStubAdapter);
}
} // namespace IDC1_5
} // namespace GREATWALL
} // namespace v1
