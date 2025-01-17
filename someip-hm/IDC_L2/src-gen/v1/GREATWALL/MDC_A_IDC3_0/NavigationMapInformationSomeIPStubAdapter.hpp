/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.someip 3.1.12.v202002200807.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#ifndef V1_GREATWALL_MDC_A_IDC3_0_NAVIGATION_MAP_INFORMATION_SOMEIP_STUB_ADAPTER_HPP_
#define V1_GREATWALL_MDC_A_IDC3_0_NAVIGATION_MAP_INFORMATION_SOMEIP_STUB_ADAPTER_HPP_

#include <v1/GREATWALL/MDC_A_IDC3_0/NavigationMapInformationStub.hpp>
#include <v1/GREATWALL/MDC_A_IDC3_0/NavigationMapInformationSomeIPDeployment.hpp>

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
namespace MDC_A_IDC3_0 {

template <typename _Stub = ::v1::GREATWALL::MDC_A_IDC3_0::NavigationMapInformationStub, typename... _Stubs>
class NavigationMapInformationSomeIPStubAdapterInternal
    : public virtual NavigationMapInformationStubAdapter,
      public CommonAPI::SomeIP::StubAdapterHelper< _Stub, _Stubs...>
{
public:
    typedef CommonAPI::SomeIP::StubAdapterHelper< _Stub, _Stubs...> NavigationMapInformationSomeIPStubAdapterHelper;

    ~NavigationMapInformationSomeIPStubAdapterInternal() {
        deactivateManagedInstances();
        NavigationMapInformationSomeIPStubAdapterHelper::deinit();
    }

    void fireAvlPathInfoEvent(const ::v1::GREATWALL::MDC_A_IDC3_0::NavigationMapInformation::RouteODD& RouteODD);

    void deactivateManagedInstances() {
    }

    static CommonAPI::SomeIP::GetAttributeStubDispatcher<
        ::v1::GREATWALL::MDC_A_IDC3_0::NavigationMapInformationStub,
        CommonAPI::Version
    > getNavigationMapInformationInterfaceVersionStubDispatcher;


    static CommonAPI::SomeIP::MethodStubDispatcher<
        ::v1::GREATWALL::MDC_A_IDC3_0::NavigationMapInformationStub,
        std::tuple< NavigationMapInformation::SDRoute>,
        std::tuple< CommonAPI::SomeIP::StringDeployment>
    > navPathInfoReqStubDispatcher;

    NavigationMapInformationSomeIPStubAdapterInternal(
        const CommonAPI::SomeIP::Address &_address,
        const std::shared_ptr<CommonAPI::SomeIP::ProxyConnection> &_connection,
        const std::shared_ptr<CommonAPI::StubBase> &_stub):
        CommonAPI::SomeIP::StubAdapter(_address, _connection),
        NavigationMapInformationSomeIPStubAdapterHelper(
            _address,
            _connection,
            std::dynamic_pointer_cast< NavigationMapInformationStub>(_stub))
    {

        
                NavigationMapInformationSomeIPStubAdapterHelper::addStubDispatcher( { CommonAPI::SomeIP::method_id_t(0x1) }, &navPathInfoReqStubDispatcher );

        // Provided events/fields
        {
            std::set<CommonAPI::SomeIP::eventgroup_id_t> itsEventGroups;
            itsEventGroups.insert(CommonAPI::SomeIP::eventgroup_id_t(0x2));
            CommonAPI::SomeIP::StubAdapter::registerEvent(CommonAPI::SomeIP::event_id_t(0x8002), itsEventGroups, false);
        }
    }

private:
};

template <typename _Stub, typename... _Stubs>
CommonAPI::SomeIP::GetAttributeStubDispatcher<
    ::v1::GREATWALL::MDC_A_IDC3_0::NavigationMapInformationStub,
    CommonAPI::Version
    > NavigationMapInformationSomeIPStubAdapterInternal<_Stub, _Stubs...>::getNavigationMapInformationInterfaceVersionStubDispatcher(&NavigationMapInformationStub::lockInterfaceVersionAttribute, &NavigationMapInformationStub::getInterfaceVersion, false);

template <typename _Stub, typename... _Stubs>
CommonAPI::SomeIP::MethodStubDispatcher<
    ::v1::GREATWALL::MDC_A_IDC3_0::NavigationMapInformationStub,
    std::tuple< NavigationMapInformation::SDRoute>,
    std::tuple< CommonAPI::SomeIP::StringDeployment>
> NavigationMapInformationSomeIPStubAdapterInternal<_Stub, _Stubs...>::navPathInfoReqStubDispatcher(
    &NavigationMapInformationStub::NavPathInfoReq,
    false,
    std::make_tuple(static_cast< CommonAPI::SomeIP::StringDeployment* >(nullptr)));

template <typename _Stub, typename... _Stubs>
void NavigationMapInformationSomeIPStubAdapterInternal<_Stub, _Stubs...>::fireAvlPathInfoEvent(const ::v1::GREATWALL::MDC_A_IDC3_0::NavigationMapInformation::RouteODD& _RouteODD) {
    CommonAPI::Deployable< NavigationMapInformation::RouteODD, CommonAPI::SomeIP::StringDeployment> deployed_RouteODD(_RouteODD, static_cast< CommonAPI::SomeIP::StringDeployment* >(nullptr));
    CommonAPI::SomeIP::StubEventHelper<CommonAPI::SomeIP::SerializableArguments<  CommonAPI::Deployable< ::v1::GREATWALL::MDC_A_IDC3_0::NavigationMapInformation::RouteODD, CommonAPI::SomeIP::StringDeployment > 
    >>
        ::sendEvent(
            *this,
            CommonAPI::SomeIP::event_id_t(0x8002),
            false,
             deployed_RouteODD 
    );
}

template <typename _Stub = ::v1::GREATWALL::MDC_A_IDC3_0::NavigationMapInformationStub, typename... _Stubs>
class NavigationMapInformationSomeIPStubAdapter
    : public NavigationMapInformationSomeIPStubAdapterInternal<_Stub, _Stubs...>,
      public std::enable_shared_from_this< NavigationMapInformationSomeIPStubAdapter<_Stub, _Stubs...>> {
public:
    NavigationMapInformationSomeIPStubAdapter(const CommonAPI::SomeIP::Address &_address,
                                            const std::shared_ptr<CommonAPI::SomeIP::ProxyConnection> &_connection,
                                            const std::shared_ptr<CommonAPI::StubBase> &_stub)
        : CommonAPI::SomeIP::StubAdapter(_address, _connection),
          NavigationMapInformationSomeIPStubAdapterInternal<_Stub, _Stubs...>(_address, _connection, _stub) {
    }
};

} // namespace MDC_A_IDC3_0
} // namespace GREATWALL
} // namespace v1

#endif // V1_GREATWALL_MDC_A_IDC3_0_Navigation_Map_Information_SOMEIP_STUB_ADAPTER_HPP_
