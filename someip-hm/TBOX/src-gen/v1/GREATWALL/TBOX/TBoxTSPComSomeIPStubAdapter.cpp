/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.someip 3.1.12.v202002200807.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#include <v1/GREATWALL/TBOX/TBoxTSPComSomeIPStubAdapter.hpp>
#include <v1/GREATWALL/TBOX/TBoxTSPCom.hpp>

#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/SomeIP/AddressTranslator.hpp>

#undef COMMONAPI_INTERNAL_COMPILATION

namespace v1 {
namespace GREATWALL {
namespace TBOX {

std::shared_ptr<CommonAPI::SomeIP::StubAdapter> createTBoxTSPComSomeIPStubAdapter(
                   const CommonAPI::SomeIP::Address &_address,
                   const std::shared_ptr<CommonAPI::SomeIP::ProxyConnection> &_connection,
                   const std::shared_ptr<CommonAPI::StubBase> &_stub) {
    return std::make_shared< TBoxTSPComSomeIPStubAdapter<::v1::GREATWALL::TBOX::TBoxTSPComStub>>(_address, _connection, _stub);
}

void initializeTBoxTSPComSomeIPStubAdapter() {
    CommonAPI::SomeIP::AddressTranslator::get()->insert(
        "local:GREATWALL.TBOX.TBoxTSPCom:v1_0:TBoxTSPCom01",
         0x202, 0x1, 1, 0);
    CommonAPI::SomeIP::Factory::get()->registerStubAdapterCreateMethod(
        TBoxTSPCom::getInterface(),
        &createTBoxTSPComSomeIPStubAdapter);
}

INITIALIZER(registerTBoxTSPComSomeIPStubAdapter) {
    CommonAPI::SomeIP::Factory::get()->registerInterface(initializeTBoxTSPComSomeIPStubAdapter);
}
} // namespace TBOX
} // namespace GREATWALL
} // namespace v1
