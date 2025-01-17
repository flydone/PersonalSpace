/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.someip 3.1.12.v202002200807.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#include <v1/GREATWALL/MDC_A_IDC3_0/NavigationMapInformationSomeIPStubAdapter.hpp>
#include <v1/GREATWALL/MDC_A_IDC3_0/NavigationMapInformation.hpp>

#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/SomeIP/AddressTranslator.hpp>

#undef COMMONAPI_INTERNAL_COMPILATION

namespace v1 {
namespace GREATWALL {
namespace MDC_A_IDC3_0 {

std::shared_ptr<CommonAPI::SomeIP::StubAdapter> createNavigationMapInformationSomeIPStubAdapter(
                   const CommonAPI::SomeIP::Address &_address,
                   const std::shared_ptr<CommonAPI::SomeIP::ProxyConnection> &_connection,
                   const std::shared_ptr<CommonAPI::StubBase> &_stub) {
    return std::make_shared< NavigationMapInformationSomeIPStubAdapter<::v1::GREATWALL::MDC_A_IDC3_0::NavigationMapInformationStub>>(_address, _connection, _stub);
}

void initializeNavigationMapInformationSomeIPStubAdapter() {
    CommonAPI::SomeIP::AddressTranslator::get()->insert(
        "local:GREATWALL.MDC_A_IDC3_0.NavigationMapInformation:v1_0:NavigationMapInformation01",
         0x802, 0x1, 1, 0);
    CommonAPI::SomeIP::Factory::get()->registerStubAdapterCreateMethod(
        NavigationMapInformation::getInterface(),
        &createNavigationMapInformationSomeIPStubAdapter);
}

INITIALIZER(registerNavigationMapInformationSomeIPStubAdapter) {
    CommonAPI::SomeIP::Factory::get()->registerInterface(initializeNavigationMapInformationSomeIPStubAdapter);
}
} // namespace MDC_A_IDC3_0
} // namespace GREATWALL
} // namespace v1
