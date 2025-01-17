/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.someip 3.1.12.v202002200807.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#ifndef V1_GREATWALL_TBOX_SPE_LOCATION_5_G_SOMEIP_STUB_ADAPTER_HPP_
#define V1_GREATWALL_TBOX_SPE_LOCATION_5_G_SOMEIP_STUB_ADAPTER_HPP_

#include <v1/GREATWALL/TBOX/SPELocation_5GStub.hpp>
#include <v1/GREATWALL/TBOX/SPELocation_5GSomeIPDeployment.hpp>

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

template <typename _Stub = ::v1::GREATWALL::TBOX::SPELocation_5GStub, typename... _Stubs>
class SPELocation_5GSomeIPStubAdapterInternal
    : public virtual SPELocation_5GStubAdapter,
      public CommonAPI::SomeIP::StubAdapterHelper< _Stub, _Stubs...>
{
public:
    typedef CommonAPI::SomeIP::StubAdapterHelper< _Stub, _Stubs...> SPELocation_5GSomeIPStubAdapterHelper;

    ~SPELocation_5GSomeIPStubAdapterInternal() {
        deactivateManagedInstances();
        SPELocation_5GSomeIPStubAdapterHelper::deinit();
    }

    void fireNtfSPELocationAttributeChanged(const ::v1::GREATWALL::TBOX::SPELocation_5G::SPELocationStruct& value);

    void deactivateManagedInstances() {
    }

    static CommonAPI::SomeIP::GetAttributeStubDispatcher<
        ::v1::GREATWALL::TBOX::SPELocation_5GStub,
        CommonAPI::Version
    > getSPELocation_5GInterfaceVersionStubDispatcher;

    static CommonAPI::SomeIP::GetAttributeStubDispatcher<
        ::v1::GREATWALL::TBOX::SPELocation_5GStub,
        ::v1::GREATWALL::TBOX::SPELocation_5G::SPELocationStruct,
        ::v1::GREATWALL::TBOX::SPELocation_5G_::SPELocationStructDeployment_t
    > getNtfSPELocationAttributeStubDispatcher;


    SPELocation_5GSomeIPStubAdapterInternal(
        const CommonAPI::SomeIP::Address &_address,
        const std::shared_ptr<CommonAPI::SomeIP::ProxyConnection> &_connection,
        const std::shared_ptr<CommonAPI::StubBase> &_stub):
        CommonAPI::SomeIP::StubAdapter(_address, _connection),
        SPELocation_5GSomeIPStubAdapterHelper(
            _address,
            _connection,
            std::dynamic_pointer_cast< SPELocation_5GStub>(_stub))
    {

                SPELocation_5GSomeIPStubAdapterHelper::addStubDispatcher( { CommonAPI::SomeIP::method_id_t(0x0) }, &getNtfSPELocationAttributeStubDispatcher );
        
        std::shared_ptr<CommonAPI::SomeIP::ClientId> clientId = std::make_shared<CommonAPI::SomeIP::ClientId>(0xFFFF);

        // Provided events/fields
        {
            std::set<CommonAPI::SomeIP::eventgroup_id_t> itsEventGroups;
            itsEventGroups.insert(CommonAPI::SomeIP::eventgroup_id_t(CommonAPI::SomeIP::eventgroup_id_t(0x1)));
            CommonAPI::SomeIP::StubAdapter::registerEvent(CommonAPI::SomeIP::event_id_t(0x9001), itsEventGroups, true);
            fireNtfSPELocationAttributeChanged(std::dynamic_pointer_cast< ::v1::GREATWALL::TBOX::SPELocation_5GStub>(_stub)->getNtfSPELocationAttribute(clientId));
        }

    }

private:
};

template <typename _Stub, typename... _Stubs>
CommonAPI::SomeIP::GetAttributeStubDispatcher<
    ::v1::GREATWALL::TBOX::SPELocation_5GStub,
    CommonAPI::Version
    > SPELocation_5GSomeIPStubAdapterInternal<_Stub, _Stubs...>::getSPELocation_5GInterfaceVersionStubDispatcher(&SPELocation_5GStub::lockInterfaceVersionAttribute, &SPELocation_5GStub::getInterfaceVersion, false);

template <typename _Stub, typename... _Stubs>
CommonAPI::SomeIP::GetAttributeStubDispatcher<
    ::v1::GREATWALL::TBOX::SPELocation_5GStub,
    ::v1::GREATWALL::TBOX::SPELocation_5G::SPELocationStruct,
    ::v1::GREATWALL::TBOX::SPELocation_5G_::SPELocationStructDeployment_t
> SPELocation_5GSomeIPStubAdapterInternal<_Stub, _Stubs...>::getNtfSPELocationAttributeStubDispatcher(
    &SPELocation_5GStub::lockNtfSPELocationAttribute,
    &SPELocation_5GStub::getNtfSPELocationAttribute, false);

template <typename _Stub, typename... _Stubs>
void SPELocation_5GSomeIPStubAdapterInternal<_Stub, _Stubs...>::fireNtfSPELocationAttributeChanged(const ::v1::GREATWALL::TBOX::SPELocation_5G::SPELocationStruct& value) {
    CommonAPI::Deployable< ::v1::GREATWALL::TBOX::SPELocation_5G::SPELocationStruct, ::v1::GREATWALL::TBOX::SPELocation_5G_::SPELocationStructDeployment_t> deployedValue(value, static_cast< ::v1::GREATWALL::TBOX::SPELocation_5G_::SPELocationStructDeployment_t* >(nullptr));
    CommonAPI::SomeIP::StubEventHelper<
        CommonAPI::SomeIP::SerializableArguments<
            CommonAPI::Deployable<
                ::v1::GREATWALL::TBOX::SPELocation_5G::SPELocationStruct,
                ::v1::GREATWALL::TBOX::SPELocation_5G_::SPELocationStructDeployment_t
            >
            >
    >::sendEvent(
        *this,
        CommonAPI::SomeIP::event_id_t(0x9001),
        false,
        deployedValue
    );
}

template <typename _Stub = ::v1::GREATWALL::TBOX::SPELocation_5GStub, typename... _Stubs>
class SPELocation_5GSomeIPStubAdapter
    : public SPELocation_5GSomeIPStubAdapterInternal<_Stub, _Stubs...>,
      public std::enable_shared_from_this< SPELocation_5GSomeIPStubAdapter<_Stub, _Stubs...>> {
public:
    SPELocation_5GSomeIPStubAdapter(const CommonAPI::SomeIP::Address &_address,
                                            const std::shared_ptr<CommonAPI::SomeIP::ProxyConnection> &_connection,
                                            const std::shared_ptr<CommonAPI::StubBase> &_stub)
        : CommonAPI::SomeIP::StubAdapter(_address, _connection),
          SPELocation_5GSomeIPStubAdapterInternal<_Stub, _Stubs...>(_address, _connection, _stub) {
    }
};

} // namespace TBOX
} // namespace GREATWALL
} // namespace v1

#endif // V1_GREATWALL_TBOX_SPE_Location_5_G_SOMEIP_STUB_ADAPTER_HPP_
