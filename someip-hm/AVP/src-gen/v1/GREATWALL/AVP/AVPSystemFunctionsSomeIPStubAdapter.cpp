/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.someip 3.1.12.v202002200807.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#include <v1/GREATWALL/AVP/AVPSystemFunctionsSomeIPStubAdapter.hpp>
#include <v1/GREATWALL/AVP/AVPSystemFunctions.hpp>

#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/SomeIP/AddressTranslator.hpp>

#undef COMMONAPI_INTERNAL_COMPILATION

namespace v1 {
namespace GREATWALL {
namespace AVP {

std::shared_ptr<CommonAPI::SomeIP::StubAdapter> createAVPSystemFunctionsSomeIPStubAdapter(
                   const CommonAPI::SomeIP::Address &_address,
                   const std::shared_ptr<CommonAPI::SomeIP::ProxyConnection> &_connection,
                   const std::shared_ptr<CommonAPI::StubBase> &_stub) {
    return std::make_shared< AVPSystemFunctionsSomeIPStubAdapter<::v1::GREATWALL::AVP::AVPSystemFunctionsStub>>(_address, _connection, _stub);
}

void initializeAVPSystemFunctionsSomeIPStubAdapter() {
    CommonAPI::SomeIP::AddressTranslator::get()->insert(
        "local:GREATWALL.AVP.AVPSystemFunctions:v1_0:AVPSystemFunctions01",
         0x701, 0x1, 1, 0);
    CommonAPI::SomeIP::Factory::get()->registerStubAdapterCreateMethod(
        AVPSystemFunctions::getInterface(),
        &createAVPSystemFunctionsSomeIPStubAdapter);
}

INITIALIZER(registerAVPSystemFunctionsSomeIPStubAdapter) {
    CommonAPI::SomeIP::Factory::get()->registerInterface(initializeAVPSystemFunctionsSomeIPStubAdapter);
}
} // namespace AVP
} // namespace GREATWALL
} // namespace v1