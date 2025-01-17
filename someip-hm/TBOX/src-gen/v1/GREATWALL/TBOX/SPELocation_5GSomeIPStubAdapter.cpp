/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.someip 3.1.12.v202002200807.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#include <v1/GREATWALL/TBOX/SPELocation_5GSomeIPStubAdapter.hpp>
#include <v1/GREATWALL/TBOX/SPELocation_5G.hpp>

#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/SomeIP/AddressTranslator.hpp>

#undef COMMONAPI_INTERNAL_COMPILATION

namespace v1 {
namespace GREATWALL {
namespace TBOX {

std::shared_ptr<CommonAPI::SomeIP::StubAdapter> createSPELocation_5GSomeIPStubAdapter(
                   const CommonAPI::SomeIP::Address &_address,
                   const std::shared_ptr<CommonAPI::SomeIP::ProxyConnection> &_connection,
                   const std::shared_ptr<CommonAPI::StubBase> &_stub) {
    return std::make_shared< SPELocation_5GSomeIPStubAdapter<::v1::GREATWALL::TBOX::SPELocation_5GStub>>(_address, _connection, _stub);
}

void initializeSPELocation_5GSomeIPStubAdapter() {
    CommonAPI::SomeIP::AddressTranslator::get()->insert(
        "local:GREATWALL.TBOX.SPELocation_5G:v1_0:SPELocation_5G01",
         0x20c, 0x1, 1, 0);
    CommonAPI::SomeIP::Factory::get()->registerStubAdapterCreateMethod(
        SPELocation_5G::getInterface(),
        &createSPELocation_5GSomeIPStubAdapter);
}

INITIALIZER(registerSPELocation_5GSomeIPStubAdapter) {
    CommonAPI::SomeIP::Factory::get()->registerInterface(initializeSPELocation_5GSomeIPStubAdapter);
}
} // namespace TBOX
} // namespace GREATWALL
} // namespace v1
