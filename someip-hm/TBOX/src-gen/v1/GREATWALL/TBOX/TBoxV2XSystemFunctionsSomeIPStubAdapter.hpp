/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.someip 3.1.12.v202002200807.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#ifndef V1_GREATWALL_TBOX_T_BOX_V2_X_SYSTEM_FUNCTIONS_SOMEIP_STUB_ADAPTER_HPP_
#define V1_GREATWALL_TBOX_T_BOX_V2_X_SYSTEM_FUNCTIONS_SOMEIP_STUB_ADAPTER_HPP_

#include <v1/GREATWALL/TBOX/TBoxV2XSystemFunctionsStub.hpp>
#include <v1/GREATWALL/TBOX/TBoxV2XSystemFunctionsSomeIPDeployment.hpp>

#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/SomeIP/AddressTranslator.hpp>
#include <CommonAPI/SomeIP/StubAdapterHelper.hpp>
#include <CommonAPI/SomeIP/StubAdapter.hpp>
#include <CommonAPI/SomeIP/Factory.hpp>
#include <CommonAPI/SomeIP/Types.hpp>
#include <CommonAPI/SomeIP/Constants.hpp>

#undef COMMONAPI_INTERNAL_COMPILATION

namespace v1 {
namespace GREATWALL {
namespace TBOX {

template <typename _Stub = ::v1::GREATWALL::TBOX::TBoxV2XSystemFunctionsStub, typename... _Stubs>
class TBoxV2XSystemFunctionsSomeIPStubAdapterInternal
    : public virtual TBoxV2XSystemFunctionsStubAdapter,
      public CommonAPI::SomeIP::StubAdapterHelper< _Stub, _Stubs...>
{
public:
    typedef CommonAPI::SomeIP::StubAdapterHelper< _Stub, _Stubs...> TBoxV2XSystemFunctionsSomeIPStubAdapterHelper;

    ~TBoxV2XSystemFunctionsSomeIPStubAdapterInternal() {
        deactivateManagedInstances();
        TBoxV2XSystemFunctionsSomeIPStubAdapterHelper::deinit();
    }

    void fireV2XFunctionStatusAttributeChanged(const ::v1::GREATWALL::TBOX::TBoxV2XSystemFunctions::V2XStatus& value);

    void deactivateManagedInstances() {
    }

    static CommonAPI::SomeIP::GetAttributeStubDispatcher<
        ::v1::GREATWALL::TBOX::TBoxV2XSystemFunctionsStub,
        CommonAPI::Version
    > getTBoxV2XSystemFunctionsInterfaceVersionStubDispatcher;

    static CommonAPI::SomeIP::GetAttributeStubDispatcher<
        ::v1::GREATWALL::TBOX::TBoxV2XSystemFunctionsStub,
        ::v1::GREATWALL::TBOX::TBoxV2XSystemFunctions::V2XStatus,
        ::v1::GREATWALL::TBOX::TBoxV2XSystemFunctions_::V2XStatusDeployment_t
    > getV2XFunctionStatusAttributeStubDispatcher;

    
    static CommonAPI::SomeIP::MethodWithReplyStubDispatcher<
        ::v1::GREATWALL::TBOX::TBoxV2XSystemFunctionsStub,
        std::tuple< TBoxV2XSystemFunctions::V2XLOCKRequest>,
        std::tuple< TBoxV2XSystemFunctions::V2XLOCKRespone>,
        std::tuple< ::v1::GREATWALL::TBOX::TBoxV2XSystemFunctions_::V2XLOCKRequestDeployment_t>,
        std::tuple< ::v1::GREATWALL::TBOX::TBoxV2XSystemFunctions_::V2XLOCKResponeDeployment_t>
    > v2XLockSwitchStubDispatcher;

    TBoxV2XSystemFunctionsSomeIPStubAdapterInternal(
        const CommonAPI::SomeIP::Address &_address,
        const std::shared_ptr<CommonAPI::SomeIP::ProxyConnection> &_connection,
        const std::shared_ptr<CommonAPI::StubBase> &_stub):
        CommonAPI::SomeIP::StubAdapter(_address, _connection),
        TBoxV2XSystemFunctionsSomeIPStubAdapterHelper(
            _address,
            _connection,
            std::dynamic_pointer_cast< TBoxV2XSystemFunctionsStub>(_stub))
    {

                TBoxV2XSystemFunctionsSomeIPStubAdapterHelper::addStubDispatcher( { CommonAPI::SomeIP::method_id_t(0x1001) }, &getV2XFunctionStatusAttributeStubDispatcher );
        
                TBoxV2XSystemFunctionsSomeIPStubAdapterHelper::addStubDispatcher( { CommonAPI::SomeIP::method_id_t(0x1) }, &v2XLockSwitchStubDispatcher );
        std::shared_ptr<CommonAPI::SomeIP::ClientId> clientId = std::make_shared<CommonAPI::SomeIP::ClientId>(0xFFFF);

        // Provided events/fields
        {
            std::set<CommonAPI::SomeIP::eventgroup_id_t> itsEventGroups;
            itsEventGroups.insert(CommonAPI::SomeIP::eventgroup_id_t(CommonAPI::SomeIP::eventgroup_id_t(0x1)));
            CommonAPI::SomeIP::StubAdapter::registerEvent(CommonAPI::SomeIP::event_id_t(0x9001), itsEventGroups, true);
            fireV2XFunctionStatusAttributeChanged(std::dynamic_pointer_cast< ::v1::GREATWALL::TBOX::TBoxV2XSystemFunctionsStub>(_stub)->getV2XFunctionStatusAttribute(clientId));
        }

    }

private:
};

template <typename _Stub, typename... _Stubs>
CommonAPI::SomeIP::GetAttributeStubDispatcher<
    ::v1::GREATWALL::TBOX::TBoxV2XSystemFunctionsStub,
    CommonAPI::Version
    > TBoxV2XSystemFunctionsSomeIPStubAdapterInternal<_Stub, _Stubs...>::getTBoxV2XSystemFunctionsInterfaceVersionStubDispatcher(&TBoxV2XSystemFunctionsStub::lockInterfaceVersionAttribute, &TBoxV2XSystemFunctionsStub::getInterfaceVersion, false);

template <typename _Stub, typename... _Stubs>
CommonAPI::SomeIP::GetAttributeStubDispatcher<
    ::v1::GREATWALL::TBOX::TBoxV2XSystemFunctionsStub,
    ::v1::GREATWALL::TBOX::TBoxV2XSystemFunctions::V2XStatus,
    ::v1::GREATWALL::TBOX::TBoxV2XSystemFunctions_::V2XStatusDeployment_t
> TBoxV2XSystemFunctionsSomeIPStubAdapterInternal<_Stub, _Stubs...>::getV2XFunctionStatusAttributeStubDispatcher(
    &TBoxV2XSystemFunctionsStub::lockV2XFunctionStatusAttribute,
    &TBoxV2XSystemFunctionsStub::getV2XFunctionStatusAttribute, false);

template <typename _Stub, typename... _Stubs>
CommonAPI::SomeIP::MethodWithReplyStubDispatcher<
    ::v1::GREATWALL::TBOX::TBoxV2XSystemFunctionsStub,
    std::tuple< TBoxV2XSystemFunctions::V2XLOCKRequest>,
    std::tuple< TBoxV2XSystemFunctions::V2XLOCKRespone>,
    std::tuple< ::v1::GREATWALL::TBOX::TBoxV2XSystemFunctions_::V2XLOCKRequestDeployment_t>,
    std::tuple< ::v1::GREATWALL::TBOX::TBoxV2XSystemFunctions_::V2XLOCKResponeDeployment_t>
> TBoxV2XSystemFunctionsSomeIPStubAdapterInternal<_Stub, _Stubs...>::v2XLockSwitchStubDispatcher(
    &TBoxV2XSystemFunctionsStub::V2XLockSwitch,
    false,
    std::make_tuple(static_cast< ::v1::GREATWALL::TBOX::TBoxV2XSystemFunctions_::V2XLOCKRequestDeployment_t* >(nullptr)),
    std::make_tuple(static_cast< ::v1::GREATWALL::TBOX::TBoxV2XSystemFunctions_::V2XLOCKResponeDeployment_t* >(nullptr)));

template <typename _Stub, typename... _Stubs>
void TBoxV2XSystemFunctionsSomeIPStubAdapterInternal<_Stub, _Stubs...>::fireV2XFunctionStatusAttributeChanged(const ::v1::GREATWALL::TBOX::TBoxV2XSystemFunctions::V2XStatus& value) {
    CommonAPI::Deployable< ::v1::GREATWALL::TBOX::TBoxV2XSystemFunctions::V2XStatus, ::v1::GREATWALL::TBOX::TBoxV2XSystemFunctions_::V2XStatusDeployment_t> deployedValue(value, static_cast< ::v1::GREATWALL::TBOX::TBoxV2XSystemFunctions_::V2XStatusDeployment_t* >(nullptr));
    CommonAPI::SomeIP::StubEventHelper<
        CommonAPI::SomeIP::SerializableArguments<
            CommonAPI::Deployable<
                ::v1::GREATWALL::TBOX::TBoxV2XSystemFunctions::V2XStatus,
                ::v1::GREATWALL::TBOX::TBoxV2XSystemFunctions_::V2XStatusDeployment_t
            >
            >
    >::sendEvent(
        *this,
        CommonAPI::SomeIP::event_id_t(0x9001),
        false,
        deployedValue
    );
}

template <typename _Stub = ::v1::GREATWALL::TBOX::TBoxV2XSystemFunctionsStub, typename... _Stubs>
class TBoxV2XSystemFunctionsSomeIPStubAdapter
    : public TBoxV2XSystemFunctionsSomeIPStubAdapterInternal<_Stub, _Stubs...>,
      public std::enable_shared_from_this< TBoxV2XSystemFunctionsSomeIPStubAdapter<_Stub, _Stubs...>> {
public:
    TBoxV2XSystemFunctionsSomeIPStubAdapter(const CommonAPI::SomeIP::Address &_address,
                                            const std::shared_ptr<CommonAPI::SomeIP::ProxyConnection> &_connection,
                                            const std::shared_ptr<CommonAPI::StubBase> &_stub)
        : CommonAPI::SomeIP::StubAdapter(_address, _connection),
          TBoxV2XSystemFunctionsSomeIPStubAdapterInternal<_Stub, _Stubs...>(_address, _connection, _stub) {
    }
};

} // namespace TBOX
} // namespace GREATWALL
} // namespace v1

#endif // V1_GREATWALL_TBOX_T_Box_V2_X_System_Functions_SOMEIP_STUB_ADAPTER_HPP_