/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.someip 3.1.12.v202002200807.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#ifndef V1_GREATWALL_MDC_A_IDC1_5_IDC3_0_HAP_HAV_PAND_AVP_FUNCTIONS_SOMEIP_STUB_ADAPTER_HPP_
#define V1_GREATWALL_MDC_A_IDC1_5_IDC3_0_HAP_HAV_PAND_AVP_FUNCTIONS_SOMEIP_STUB_ADAPTER_HPP_

#include <v1/GREATWALL_MDC_A_IDC1_5_IDC3_0_HAP/HAVPandAVPFunctionsStub.hpp>
#include <v1/GREATWALL_MDC_A_IDC1_5_IDC3_0_HAP/HAVPandAVPFunctionsSomeIPDeployment.hpp>

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
namespace GREATWALL_MDC_A_IDC1_5_IDC3_0_HAP {

template <typename _Stub = ::v1::GREATWALL_MDC_A_IDC1_5_IDC3_0_HAP::HAVPandAVPFunctionsStub, typename... _Stubs>
class HAVPandAVPFunctionsSomeIPStubAdapterInternal
    : public virtual HAVPandAVPFunctionsStubAdapter,
      public CommonAPI::SomeIP::StubAdapterHelper< _Stub, _Stubs...>
{
public:
    typedef CommonAPI::SomeIP::StubAdapterHelper< _Stub, _Stubs...> HAVPandAVPFunctionsSomeIPStubAdapterHelper;

    ~HAVPandAVPFunctionsSomeIPStubAdapterInternal() {
        deactivateManagedInstances();
        HAVPandAVPFunctionsSomeIPStubAdapterHelper::deinit();
    }

    void fireHAVPPathInfoEvent(const ::v1::GREATWALL_MDC_A_IDC1_5_IDC3_0_HAP::HAVPandAVPFunctions::HAVPLearningWorldArray& HAVPLearningWorldArray);

    void fireHAVPRendergInfoEvent(const ::v1::GREATWALL_MDC_A_IDC1_5_IDC3_0_HAP::HAVPandAVPFunctions::HAVPVehDataArray& HAVPVehDataArray);

    void fireHAVPPathMapEvent(const ::v1::GREATWALL_MDC_A_IDC1_5_IDC3_0_HAP::HAVPandAVPFunctions::HAVPMapFileArray& HAVPMapFileArray);

    void deactivateManagedInstances() {
    }

    static CommonAPI::SomeIP::GetAttributeStubDispatcher<
        ::v1::GREATWALL_MDC_A_IDC1_5_IDC3_0_HAP::HAVPandAVPFunctionsStub,
        CommonAPI::Version
    > getHAVPandAVPFunctionsInterfaceVersionStubDispatcher;



    HAVPandAVPFunctionsSomeIPStubAdapterInternal(
        const CommonAPI::SomeIP::Address &_address,
        const std::shared_ptr<CommonAPI::SomeIP::ProxyConnection> &_connection,
        const std::shared_ptr<CommonAPI::StubBase> &_stub):
        CommonAPI::SomeIP::StubAdapter(_address, _connection),
        HAVPandAVPFunctionsSomeIPStubAdapterHelper(
            _address,
            _connection,
            std::dynamic_pointer_cast< HAVPandAVPFunctionsStub>(_stub))
    {

        



        // Provided events/fields
        {
            std::set<CommonAPI::SomeIP::eventgroup_id_t> itsEventGroups;
            itsEventGroups.insert(CommonAPI::SomeIP::eventgroup_id_t(0x1));
            CommonAPI::SomeIP::StubAdapter::registerEvent(CommonAPI::SomeIP::event_id_t(0x8001), itsEventGroups, false);
        }
        {
            std::set<CommonAPI::SomeIP::eventgroup_id_t> itsEventGroups;
            itsEventGroups.insert(CommonAPI::SomeIP::eventgroup_id_t(0x1));
            CommonAPI::SomeIP::StubAdapter::registerEvent(CommonAPI::SomeIP::event_id_t(0x8002), itsEventGroups, false);
        }
        {
            std::set<CommonAPI::SomeIP::eventgroup_id_t> itsEventGroups;
            itsEventGroups.insert(CommonAPI::SomeIP::eventgroup_id_t(0x1));
            CommonAPI::SomeIP::StubAdapter::registerEvent(CommonAPI::SomeIP::event_id_t(0x8003), itsEventGroups, false);
        }
    }

private:
};

template <typename _Stub, typename... _Stubs>
CommonAPI::SomeIP::GetAttributeStubDispatcher<
    ::v1::GREATWALL_MDC_A_IDC1_5_IDC3_0_HAP::HAVPandAVPFunctionsStub,
    CommonAPI::Version
    > HAVPandAVPFunctionsSomeIPStubAdapterInternal<_Stub, _Stubs...>::getHAVPandAVPFunctionsInterfaceVersionStubDispatcher(&HAVPandAVPFunctionsStub::lockInterfaceVersionAttribute, &HAVPandAVPFunctionsStub::getInterfaceVersion, false);

template <typename _Stub, typename... _Stubs>
void HAVPandAVPFunctionsSomeIPStubAdapterInternal<_Stub, _Stubs...>::fireHAVPPathInfoEvent(const ::v1::GREATWALL_MDC_A_IDC1_5_IDC3_0_HAP::HAVPandAVPFunctions::HAVPLearningWorldArray& _HAVPLearningWorldArray) {
    CommonAPI::Deployable< HAVPandAVPFunctions::HAVPLearningWorldArray, ::v1::GREATWALL_MDC_A_IDC1_5_IDC3_0_HAP::HAVPandAVPFunctions_::HAVPLearningWorldArrayDeployment_t> deployed_HAVPLearningWorldArray(_HAVPLearningWorldArray, static_cast< ::v1::GREATWALL_MDC_A_IDC1_5_IDC3_0_HAP::HAVPandAVPFunctions_::HAVPLearningWorldArrayDeployment_t* >(nullptr));
    CommonAPI::SomeIP::StubEventHelper<CommonAPI::SomeIP::SerializableArguments<  CommonAPI::Deployable< ::v1::GREATWALL_MDC_A_IDC1_5_IDC3_0_HAP::HAVPandAVPFunctions::HAVPLearningWorldArray, ::v1::GREATWALL_MDC_A_IDC1_5_IDC3_0_HAP::HAVPandAVPFunctions_::HAVPLearningWorldArrayDeployment_t > 
    >>
        ::sendEvent(
            *this,
            CommonAPI::SomeIP::event_id_t(0x8001),
            false,
             deployed_HAVPLearningWorldArray 
    );
}

template <typename _Stub, typename... _Stubs>
void HAVPandAVPFunctionsSomeIPStubAdapterInternal<_Stub, _Stubs...>::fireHAVPRendergInfoEvent(const ::v1::GREATWALL_MDC_A_IDC1_5_IDC3_0_HAP::HAVPandAVPFunctions::HAVPVehDataArray& _HAVPVehDataArray) {
    CommonAPI::Deployable< HAVPandAVPFunctions::HAVPVehDataArray, ::v1::GREATWALL_MDC_A_IDC1_5_IDC3_0_HAP::HAVPandAVPFunctions_::HAVPVehDataArrayDeployment_t> deployed_HAVPVehDataArray(_HAVPVehDataArray, static_cast< ::v1::GREATWALL_MDC_A_IDC1_5_IDC3_0_HAP::HAVPandAVPFunctions_::HAVPVehDataArrayDeployment_t* >(nullptr));
    CommonAPI::SomeIP::StubEventHelper<CommonAPI::SomeIP::SerializableArguments<  CommonAPI::Deployable< ::v1::GREATWALL_MDC_A_IDC1_5_IDC3_0_HAP::HAVPandAVPFunctions::HAVPVehDataArray, ::v1::GREATWALL_MDC_A_IDC1_5_IDC3_0_HAP::HAVPandAVPFunctions_::HAVPVehDataArrayDeployment_t > 
    >>
        ::sendEvent(
            *this,
            CommonAPI::SomeIP::event_id_t(0x8002),
            false,
             deployed_HAVPVehDataArray 
    );
}

template <typename _Stub, typename... _Stubs>
void HAVPandAVPFunctionsSomeIPStubAdapterInternal<_Stub, _Stubs...>::fireHAVPPathMapEvent(const ::v1::GREATWALL_MDC_A_IDC1_5_IDC3_0_HAP::HAVPandAVPFunctions::HAVPMapFileArray& _HAVPMapFileArray) {
    CommonAPI::Deployable< HAVPandAVPFunctions::HAVPMapFileArray, ::v1::GREATWALL_MDC_A_IDC1_5_IDC3_0_HAP::HAVPandAVPFunctions_::HAVPMapFileArrayDeployment_t> deployed_HAVPMapFileArray(_HAVPMapFileArray, static_cast< ::v1::GREATWALL_MDC_A_IDC1_5_IDC3_0_HAP::HAVPandAVPFunctions_::HAVPMapFileArrayDeployment_t* >(nullptr));
    CommonAPI::SomeIP::StubEventHelper<CommonAPI::SomeIP::SerializableArguments<  CommonAPI::Deployable< ::v1::GREATWALL_MDC_A_IDC1_5_IDC3_0_HAP::HAVPandAVPFunctions::HAVPMapFileArray, ::v1::GREATWALL_MDC_A_IDC1_5_IDC3_0_HAP::HAVPandAVPFunctions_::HAVPMapFileArrayDeployment_t > 
    >>
        ::sendEvent(
            *this,
            CommonAPI::SomeIP::event_id_t(0x8003),
            false,
             deployed_HAVPMapFileArray 
    );
}

template <typename _Stub = ::v1::GREATWALL_MDC_A_IDC1_5_IDC3_0_HAP::HAVPandAVPFunctionsStub, typename... _Stubs>
class HAVPandAVPFunctionsSomeIPStubAdapter
    : public HAVPandAVPFunctionsSomeIPStubAdapterInternal<_Stub, _Stubs...>,
      public std::enable_shared_from_this< HAVPandAVPFunctionsSomeIPStubAdapter<_Stub, _Stubs...>> {
public:
    HAVPandAVPFunctionsSomeIPStubAdapter(const CommonAPI::SomeIP::Address &_address,
                                            const std::shared_ptr<CommonAPI::SomeIP::ProxyConnection> &_connection,
                                            const std::shared_ptr<CommonAPI::StubBase> &_stub)
        : CommonAPI::SomeIP::StubAdapter(_address, _connection),
          HAVPandAVPFunctionsSomeIPStubAdapterInternal<_Stub, _Stubs...>(_address, _connection, _stub) {
    }
};

} // namespace GREATWALL_MDC_A_IDC1_5_IDC3_0_HAP
} // namespace v1

#endif // V1_GREATWALL_MDC_A_IDC1_5_IDC3_0_HAP_HAV_Pand_AVP_Functions_SOMEIP_STUB_ADAPTER_HPP_
