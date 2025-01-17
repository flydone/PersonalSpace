/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.someip 3.1.12.v202002200807.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#ifndef V1_GREATWALL_IDC3_0_HAV_PAND_AVP_FUNCTIONS_SOMEIP_STUB_ADAPTER_HPP_
#define V1_GREATWALL_IDC3_0_HAV_PAND_AVP_FUNCTIONS_SOMEIP_STUB_ADAPTER_HPP_

#include <v1/GREATWALL/IDC3_0/HAVPandAVPFunctionsStub.hpp>
#include <v1/GREATWALL/IDC3_0/HAVPandAVPFunctionsSomeIPDeployment.hpp>

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
namespace IDC3_0 {

template <typename _Stub = ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctionsStub, typename... _Stubs>
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

    void fireHAVPPathMapEvent(const ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions::HAVPMapFileArray& HAVPMapFileArray);

    void fireSideBsdDispErrStsInfoEvent(const ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions::SideBsdDispErrorSts& SideBsdDispErrSts);

    void fireAVMDispReqEvent(const ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions::AVMStsReq& AVMStsReq);

    void fireHAVPPathInfoEvent(const ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions::HAVPLearningWorldArray& HAVPLearningWorldArray);

    void fireHAVPRendergInfoEvent(const ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions::HAVPVehDataArray& HAVPVehDataArray);

    void fireSideBsdDispStsInfoEvent(const ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions::SideBsdDispStatus& SideBsdDispSts);

    void fireHAVP_SVPScrnDispInfoEvent(const ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions::HAVP_SVPScrnInfoStruct& HAVP_SVPScrnInfoStruct);

    void deactivateManagedInstances() {
    }

    static CommonAPI::SomeIP::GetAttributeStubDispatcher<
        ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctionsStub,
        CommonAPI::Version
    > getHAVPandAVPFunctionsInterfaceVersionStubDispatcher;


    
    static CommonAPI::SomeIP::MethodWithReplyStubDispatcher<
        ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctionsStub,
        std::tuple< HAVPandAVPFunctions::SideBsdDispRequest>,
        std::tuple< HAVPandAVPFunctions::SideBsdDispSts>,
        std::tuple< ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions_::SideBsdDispRequestDeployment_t>,
        std::tuple< ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions_::SideBsdDispStsDeployment_t>
    > sideBsdDispStubDispatcher;
    static CommonAPI::SomeIP::MethodStubDispatcher<
        ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctionsStub,
        std::tuple< HAVPandAVPFunctions::AVMStsResp>,
        std::tuple< ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions_::AVMStsRespDeployment_t>
    > aVMDispRespStubDispatcher;
    static CommonAPI::SomeIP::MethodStubDispatcher<
        ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctionsStub,
        std::tuple< HAVPandAVPFunctions::BtnEnaReq>,
        std::tuple< ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions_::BtnEnaReqDeployment_t>
    > hAVP_SVPSwtReqStubDispatcher;
    static CommonAPI::SomeIP::MethodStubDispatcher<
        ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctionsStub,
        std::tuple< HAVPandAVPFunctions::SetPrkgArea>,
        std::tuple< CommonAPI::SomeIP::IntegerDeployment<uint8_t>>
    > prkgAreaReqStubDispatcher;
    static CommonAPI::SomeIP::MethodStubDispatcher<
        ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctionsStub,
        std::tuple< HAVPandAVPFunctions::AutoPushReq>,
        std::tuple< ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions_::AutoPushReqDeployment_t>
    > autoReqStubDispatcher;
    static CommonAPI::SomeIP::MethodStubDispatcher<
        ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctionsStub,
        std::tuple< HAVPandAVPFunctions::SetMapFlr>,
        std::tuple< CommonAPI::SomeIP::IntegerDeployment<int8_t>>
    > prkgFlrReqStubDispatcher;
    static CommonAPI::SomeIP::MethodStubDispatcher<
        ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctionsStub,
        std::tuple< HAVPandAVPFunctions::SVPfunctionReq>,
        std::tuple< ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions_::SVPfunctionReqDeployment_t>
    > sVPReqStubDispatcher;
    static CommonAPI::SomeIP::MethodStubDispatcher<
        ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctionsStub,
        std::tuple< HAVPandAVPFunctions::SetPrkgSlotTyp>,
        std::tuple< ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions_::SetPrkgSlotTypDeployment_t>
    > prkgTypReqStubDispatcher;
    static CommonAPI::SomeIP::MethodStubDispatcher<
        ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctionsStub,
        std::tuple< HAVPandAVPFunctions::TarMapID>,
        std::tuple< CommonAPI::SomeIP::IntegerDeployment<uint16_t>>
    > tarPrkgIDReqStubDispatcher;
    static CommonAPI::SomeIP::MethodStubDispatcher<
        ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctionsStub,
        std::tuple< HAVPandAVPFunctions::SetLvngPOI>,
        std::tuple< CommonAPI::SomeIP::IntegerDeployment<uint8_t>>
    > lvngPOIReqStubDispatcher;
    static CommonAPI::SomeIP::MethodStubDispatcher<
        ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctionsStub,
        std::tuple< HAVPandAVPFunctions::MapUpdSt>,
        std::tuple< ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions_::MapUpdStDeployment_t>
    > prkgLotMapUpdStStubDispatcher;
    static CommonAPI::SomeIP::MethodStubDispatcher<
        ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctionsStub,
        std::tuple< HAVPandAVPFunctions::SelNearSlotID>,
        std::tuple< CommonAPI::SomeIP::IntegerDeployment<uint8_t>>
    > nearSlotIDReqStubDispatcher;
    static CommonAPI::SomeIP::MethodStubDispatcher<
        ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctionsStub,
        std::tuple< HAVPandAVPFunctions::SetPrkgSlot>,
        std::tuple< CommonAPI::SomeIP::IntegerDeployment<uint16_t>>
    > prkgSlotReqStubDispatcher;
    static CommonAPI::SomeIP::MethodStubDispatcher<
        ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctionsStub,
        std::tuple< HAVPandAVPFunctions::HAVPfunctionReq>,
        std::tuple< ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions_::HAVPfunctionReqDeployment_t>
    > hAVPReqStubDispatcher;

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

        
                HAVPandAVPFunctionsSomeIPStubAdapterHelper::addStubDispatcher( { CommonAPI::SomeIP::method_id_t(0x14) }, &sideBsdDispStubDispatcher );
                HAVPandAVPFunctionsSomeIPStubAdapterHelper::addStubDispatcher( { CommonAPI::SomeIP::method_id_t(0x13) }, &aVMDispRespStubDispatcher );
                HAVPandAVPFunctionsSomeIPStubAdapterHelper::addStubDispatcher( { CommonAPI::SomeIP::method_id_t(0x2) }, &hAVP_SVPSwtReqStubDispatcher );
                HAVPandAVPFunctionsSomeIPStubAdapterHelper::addStubDispatcher( { CommonAPI::SomeIP::method_id_t(0x6) }, &prkgAreaReqStubDispatcher );
                HAVPandAVPFunctionsSomeIPStubAdapterHelper::addStubDispatcher( { CommonAPI::SomeIP::method_id_t(0x11) }, &autoReqStubDispatcher );
                HAVPandAVPFunctionsSomeIPStubAdapterHelper::addStubDispatcher( { CommonAPI::SomeIP::method_id_t(0x4) }, &prkgFlrReqStubDispatcher );
                HAVPandAVPFunctionsSomeIPStubAdapterHelper::addStubDispatcher( { CommonAPI::SomeIP::method_id_t(0x12) }, &sVPReqStubDispatcher );
                HAVPandAVPFunctionsSomeIPStubAdapterHelper::addStubDispatcher( { CommonAPI::SomeIP::method_id_t(0x3) }, &prkgTypReqStubDispatcher );
                HAVPandAVPFunctionsSomeIPStubAdapterHelper::addStubDispatcher( { CommonAPI::SomeIP::method_id_t(0x8) }, &tarPrkgIDReqStubDispatcher );
                HAVPandAVPFunctionsSomeIPStubAdapterHelper::addStubDispatcher( { CommonAPI::SomeIP::method_id_t(0x7) }, &lvngPOIReqStubDispatcher );
                HAVPandAVPFunctionsSomeIPStubAdapterHelper::addStubDispatcher( { CommonAPI::SomeIP::method_id_t(0x1) }, &prkgLotMapUpdStStubDispatcher );
                HAVPandAVPFunctionsSomeIPStubAdapterHelper::addStubDispatcher( { CommonAPI::SomeIP::method_id_t(0x9) }, &nearSlotIDReqStubDispatcher );
                HAVPandAVPFunctionsSomeIPStubAdapterHelper::addStubDispatcher( { CommonAPI::SomeIP::method_id_t(0x5) }, &prkgSlotReqStubDispatcher );
                HAVPandAVPFunctionsSomeIPStubAdapterHelper::addStubDispatcher( { CommonAPI::SomeIP::method_id_t(0x10) }, &hAVPReqStubDispatcher );







        // Provided events/fields
        {
            std::set<CommonAPI::SomeIP::eventgroup_id_t> itsEventGroups;
            itsEventGroups.insert(CommonAPI::SomeIP::eventgroup_id_t(0x1));
            CommonAPI::SomeIP::StubAdapter::registerEvent(CommonAPI::SomeIP::event_id_t(0x8003), itsEventGroups, false);
        }
        {
            std::set<CommonAPI::SomeIP::eventgroup_id_t> itsEventGroups;
            itsEventGroups.insert(CommonAPI::SomeIP::eventgroup_id_t(0x4));
            CommonAPI::SomeIP::StubAdapter::registerEvent(CommonAPI::SomeIP::event_id_t(0x8006), itsEventGroups, false);
        }
        {
            std::set<CommonAPI::SomeIP::eventgroup_id_t> itsEventGroups;
            itsEventGroups.insert(CommonAPI::SomeIP::eventgroup_id_t(0x3));
            CommonAPI::SomeIP::StubAdapter::registerEvent(CommonAPI::SomeIP::event_id_t(0x8005), itsEventGroups, false);
        }
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
            itsEventGroups.insert(CommonAPI::SomeIP::eventgroup_id_t(0x4));
            CommonAPI::SomeIP::StubAdapter::registerEvent(CommonAPI::SomeIP::event_id_t(0x8007), itsEventGroups, false);
        }
        {
            std::set<CommonAPI::SomeIP::eventgroup_id_t> itsEventGroups;
            itsEventGroups.insert(CommonAPI::SomeIP::eventgroup_id_t(0x2));
            CommonAPI::SomeIP::StubAdapter::registerEvent(CommonAPI::SomeIP::event_id_t(0x8004), itsEventGroups, false);
        }
    }

private:
};

template <typename _Stub, typename... _Stubs>
CommonAPI::SomeIP::GetAttributeStubDispatcher<
    ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctionsStub,
    CommonAPI::Version
    > HAVPandAVPFunctionsSomeIPStubAdapterInternal<_Stub, _Stubs...>::getHAVPandAVPFunctionsInterfaceVersionStubDispatcher(&HAVPandAVPFunctionsStub::lockInterfaceVersionAttribute, &HAVPandAVPFunctionsStub::getInterfaceVersion, false);

template <typename _Stub, typename... _Stubs>
CommonAPI::SomeIP::MethodWithReplyStubDispatcher<
    ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctionsStub,
    std::tuple< HAVPandAVPFunctions::SideBsdDispRequest>,
    std::tuple< HAVPandAVPFunctions::SideBsdDispSts>,
    std::tuple< ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions_::SideBsdDispRequestDeployment_t>,
    std::tuple< ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions_::SideBsdDispStsDeployment_t>
> HAVPandAVPFunctionsSomeIPStubAdapterInternal<_Stub, _Stubs...>::sideBsdDispStubDispatcher(
    &HAVPandAVPFunctionsStub::SideBsdDisp,
    false,
    std::make_tuple(static_cast< ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions_::SideBsdDispRequestDeployment_t* >(nullptr)),
    std::make_tuple(static_cast< ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions_::SideBsdDispStsDeployment_t* >(nullptr)));

template <typename _Stub, typename... _Stubs>
CommonAPI::SomeIP::MethodStubDispatcher<
    ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctionsStub,
    std::tuple< HAVPandAVPFunctions::AVMStsResp>,
    std::tuple< ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions_::AVMStsRespDeployment_t>
> HAVPandAVPFunctionsSomeIPStubAdapterInternal<_Stub, _Stubs...>::aVMDispRespStubDispatcher(
    &HAVPandAVPFunctionsStub::AVMDispResp,
    false,
    std::make_tuple(static_cast< ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions_::AVMStsRespDeployment_t* >(nullptr)));

template <typename _Stub, typename... _Stubs>
CommonAPI::SomeIP::MethodStubDispatcher<
    ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctionsStub,
    std::tuple< HAVPandAVPFunctions::BtnEnaReq>,
    std::tuple< ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions_::BtnEnaReqDeployment_t>
> HAVPandAVPFunctionsSomeIPStubAdapterInternal<_Stub, _Stubs...>::hAVP_SVPSwtReqStubDispatcher(
    &HAVPandAVPFunctionsStub::HAVP_SVPSwtReq,
    false,
    std::make_tuple(static_cast< ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions_::BtnEnaReqDeployment_t* >(nullptr)));

template <typename _Stub, typename... _Stubs>
CommonAPI::SomeIP::MethodStubDispatcher<
    ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctionsStub,
    std::tuple< HAVPandAVPFunctions::SetPrkgArea>,
    std::tuple< CommonAPI::SomeIP::IntegerDeployment<uint8_t>>
> HAVPandAVPFunctionsSomeIPStubAdapterInternal<_Stub, _Stubs...>::prkgAreaReqStubDispatcher(
    &HAVPandAVPFunctionsStub::PrkgAreaReq,
    false,
    std::make_tuple(static_cast< CommonAPI::SomeIP::IntegerDeployment<uint8_t>* >(nullptr)));

template <typename _Stub, typename... _Stubs>
CommonAPI::SomeIP::MethodStubDispatcher<
    ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctionsStub,
    std::tuple< HAVPandAVPFunctions::AutoPushReq>,
    std::tuple< ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions_::AutoPushReqDeployment_t>
> HAVPandAVPFunctionsSomeIPStubAdapterInternal<_Stub, _Stubs...>::autoReqStubDispatcher(
    &HAVPandAVPFunctionsStub::AutoReq,
    false,
    std::make_tuple(static_cast< ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions_::AutoPushReqDeployment_t* >(nullptr)));

template <typename _Stub, typename... _Stubs>
CommonAPI::SomeIP::MethodStubDispatcher<
    ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctionsStub,
    std::tuple< HAVPandAVPFunctions::SetMapFlr>,
    std::tuple< CommonAPI::SomeIP::IntegerDeployment<int8_t>>
> HAVPandAVPFunctionsSomeIPStubAdapterInternal<_Stub, _Stubs...>::prkgFlrReqStubDispatcher(
    &HAVPandAVPFunctionsStub::PrkgFlrReq,
    false,
    std::make_tuple(static_cast< CommonAPI::SomeIP::IntegerDeployment<int8_t>* >(nullptr)));

template <typename _Stub, typename... _Stubs>
CommonAPI::SomeIP::MethodStubDispatcher<
    ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctionsStub,
    std::tuple< HAVPandAVPFunctions::SVPfunctionReq>,
    std::tuple< ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions_::SVPfunctionReqDeployment_t>
> HAVPandAVPFunctionsSomeIPStubAdapterInternal<_Stub, _Stubs...>::sVPReqStubDispatcher(
    &HAVPandAVPFunctionsStub::SVPReq,
    false,
    std::make_tuple(static_cast< ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions_::SVPfunctionReqDeployment_t* >(nullptr)));

template <typename _Stub, typename... _Stubs>
CommonAPI::SomeIP::MethodStubDispatcher<
    ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctionsStub,
    std::tuple< HAVPandAVPFunctions::SetPrkgSlotTyp>,
    std::tuple< ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions_::SetPrkgSlotTypDeployment_t>
> HAVPandAVPFunctionsSomeIPStubAdapterInternal<_Stub, _Stubs...>::prkgTypReqStubDispatcher(
    &HAVPandAVPFunctionsStub::PrkgTypReq,
    false,
    std::make_tuple(static_cast< ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions_::SetPrkgSlotTypDeployment_t* >(nullptr)));

template <typename _Stub, typename... _Stubs>
CommonAPI::SomeIP::MethodStubDispatcher<
    ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctionsStub,
    std::tuple< HAVPandAVPFunctions::TarMapID>,
    std::tuple< CommonAPI::SomeIP::IntegerDeployment<uint16_t>>
> HAVPandAVPFunctionsSomeIPStubAdapterInternal<_Stub, _Stubs...>::tarPrkgIDReqStubDispatcher(
    &HAVPandAVPFunctionsStub::TarPrkgIDReq,
    false,
    std::make_tuple(static_cast< CommonAPI::SomeIP::IntegerDeployment<uint16_t>* >(nullptr)));

template <typename _Stub, typename... _Stubs>
CommonAPI::SomeIP::MethodStubDispatcher<
    ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctionsStub,
    std::tuple< HAVPandAVPFunctions::SetLvngPOI>,
    std::tuple< CommonAPI::SomeIP::IntegerDeployment<uint8_t>>
> HAVPandAVPFunctionsSomeIPStubAdapterInternal<_Stub, _Stubs...>::lvngPOIReqStubDispatcher(
    &HAVPandAVPFunctionsStub::LvngPOIReq,
    false,
    std::make_tuple(static_cast< CommonAPI::SomeIP::IntegerDeployment<uint8_t>* >(nullptr)));

template <typename _Stub, typename... _Stubs>
CommonAPI::SomeIP::MethodStubDispatcher<
    ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctionsStub,
    std::tuple< HAVPandAVPFunctions::MapUpdSt>,
    std::tuple< ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions_::MapUpdStDeployment_t>
> HAVPandAVPFunctionsSomeIPStubAdapterInternal<_Stub, _Stubs...>::prkgLotMapUpdStStubDispatcher(
    &HAVPandAVPFunctionsStub::PrkgLotMapUpdSt,
    false,
    std::make_tuple(static_cast< ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions_::MapUpdStDeployment_t* >(nullptr)));

template <typename _Stub, typename... _Stubs>
CommonAPI::SomeIP::MethodStubDispatcher<
    ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctionsStub,
    std::tuple< HAVPandAVPFunctions::SelNearSlotID>,
    std::tuple< CommonAPI::SomeIP::IntegerDeployment<uint8_t>>
> HAVPandAVPFunctionsSomeIPStubAdapterInternal<_Stub, _Stubs...>::nearSlotIDReqStubDispatcher(
    &HAVPandAVPFunctionsStub::NearSlotIDReq,
    false,
    std::make_tuple(static_cast< CommonAPI::SomeIP::IntegerDeployment<uint8_t>* >(nullptr)));

template <typename _Stub, typename... _Stubs>
CommonAPI::SomeIP::MethodStubDispatcher<
    ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctionsStub,
    std::tuple< HAVPandAVPFunctions::SetPrkgSlot>,
    std::tuple< CommonAPI::SomeIP::IntegerDeployment<uint16_t>>
> HAVPandAVPFunctionsSomeIPStubAdapterInternal<_Stub, _Stubs...>::prkgSlotReqStubDispatcher(
    &HAVPandAVPFunctionsStub::PrkgSlotReq,
    false,
    std::make_tuple(static_cast< CommonAPI::SomeIP::IntegerDeployment<uint16_t>* >(nullptr)));

template <typename _Stub, typename... _Stubs>
CommonAPI::SomeIP::MethodStubDispatcher<
    ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctionsStub,
    std::tuple< HAVPandAVPFunctions::HAVPfunctionReq>,
    std::tuple< ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions_::HAVPfunctionReqDeployment_t>
> HAVPandAVPFunctionsSomeIPStubAdapterInternal<_Stub, _Stubs...>::hAVPReqStubDispatcher(
    &HAVPandAVPFunctionsStub::HAVPReq,
    false,
    std::make_tuple(static_cast< ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions_::HAVPfunctionReqDeployment_t* >(nullptr)));

template <typename _Stub, typename... _Stubs>
void HAVPandAVPFunctionsSomeIPStubAdapterInternal<_Stub, _Stubs...>::fireHAVPPathMapEvent(const ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions::HAVPMapFileArray& _HAVPMapFileArray) {
    CommonAPI::Deployable< HAVPandAVPFunctions::HAVPMapFileArray, ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions_::HAVPMapFileArrayDeployment_t> deployed_HAVPMapFileArray(_HAVPMapFileArray, static_cast< ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions_::HAVPMapFileArrayDeployment_t* >(nullptr));
    CommonAPI::SomeIP::StubEventHelper<CommonAPI::SomeIP::SerializableArguments<  CommonAPI::Deployable< ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions::HAVPMapFileArray, ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions_::HAVPMapFileArrayDeployment_t > 
    >>
        ::sendEvent(
            *this,
            CommonAPI::SomeIP::event_id_t(0x8003),
            false,
             deployed_HAVPMapFileArray 
    );
}

template <typename _Stub, typename... _Stubs>
void HAVPandAVPFunctionsSomeIPStubAdapterInternal<_Stub, _Stubs...>::fireSideBsdDispErrStsInfoEvent(const ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions::SideBsdDispErrorSts& _SideBsdDispErrSts) {
    CommonAPI::Deployable< HAVPandAVPFunctions::SideBsdDispErrorSts, ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions_::SideBsdDispErrorStsDeployment_t> deployed_SideBsdDispErrSts(_SideBsdDispErrSts, static_cast< ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions_::SideBsdDispErrorStsDeployment_t* >(nullptr));
    CommonAPI::SomeIP::StubEventHelper<CommonAPI::SomeIP::SerializableArguments<  CommonAPI::Deployable< ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions::SideBsdDispErrorSts, ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions_::SideBsdDispErrorStsDeployment_t > 
    >>
        ::sendEvent(
            *this,
            CommonAPI::SomeIP::event_id_t(0x8006),
            false,
             deployed_SideBsdDispErrSts 
    );
}

template <typename _Stub, typename... _Stubs>
void HAVPandAVPFunctionsSomeIPStubAdapterInternal<_Stub, _Stubs...>::fireAVMDispReqEvent(const ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions::AVMStsReq& _AVMStsReq) {
    CommonAPI::Deployable< HAVPandAVPFunctions::AVMStsReq, ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions_::AVMStsReqDeployment_t> deployed_AVMStsReq(_AVMStsReq, static_cast< ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions_::AVMStsReqDeployment_t* >(nullptr));
    CommonAPI::SomeIP::StubEventHelper<CommonAPI::SomeIP::SerializableArguments<  CommonAPI::Deployable< ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions::AVMStsReq, ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions_::AVMStsReqDeployment_t > 
    >>
        ::sendEvent(
            *this,
            CommonAPI::SomeIP::event_id_t(0x8005),
            false,
             deployed_AVMStsReq 
    );
}

template <typename _Stub, typename... _Stubs>
void HAVPandAVPFunctionsSomeIPStubAdapterInternal<_Stub, _Stubs...>::fireHAVPPathInfoEvent(const ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions::HAVPLearningWorldArray& _HAVPLearningWorldArray) {
    CommonAPI::Deployable< HAVPandAVPFunctions::HAVPLearningWorldArray, ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions_::HAVPLearningWorldArrayDeployment_t> deployed_HAVPLearningWorldArray(_HAVPLearningWorldArray, static_cast< ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions_::HAVPLearningWorldArrayDeployment_t* >(nullptr));
    CommonAPI::SomeIP::StubEventHelper<CommonAPI::SomeIP::SerializableArguments<  CommonAPI::Deployable< ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions::HAVPLearningWorldArray, ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions_::HAVPLearningWorldArrayDeployment_t > 
    >>
        ::sendEvent(
            *this,
            CommonAPI::SomeIP::event_id_t(0x8001),
            false,
             deployed_HAVPLearningWorldArray 
    );
}

template <typename _Stub, typename... _Stubs>
void HAVPandAVPFunctionsSomeIPStubAdapterInternal<_Stub, _Stubs...>::fireHAVPRendergInfoEvent(const ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions::HAVPVehDataArray& _HAVPVehDataArray) {
    CommonAPI::Deployable< HAVPandAVPFunctions::HAVPVehDataArray, ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions_::HAVPVehDataArrayDeployment_t> deployed_HAVPVehDataArray(_HAVPVehDataArray, static_cast< ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions_::HAVPVehDataArrayDeployment_t* >(nullptr));
    CommonAPI::SomeIP::StubEventHelper<CommonAPI::SomeIP::SerializableArguments<  CommonAPI::Deployable< ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions::HAVPVehDataArray, ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions_::HAVPVehDataArrayDeployment_t > 
    >>
        ::sendEvent(
            *this,
            CommonAPI::SomeIP::event_id_t(0x8002),
            false,
             deployed_HAVPVehDataArray 
    );
}

template <typename _Stub, typename... _Stubs>
void HAVPandAVPFunctionsSomeIPStubAdapterInternal<_Stub, _Stubs...>::fireSideBsdDispStsInfoEvent(const ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions::SideBsdDispStatus& _SideBsdDispSts) {
    CommonAPI::Deployable< HAVPandAVPFunctions::SideBsdDispStatus, ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions_::SideBsdDispStatusDeployment_t> deployed_SideBsdDispSts(_SideBsdDispSts, static_cast< ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions_::SideBsdDispStatusDeployment_t* >(nullptr));
    CommonAPI::SomeIP::StubEventHelper<CommonAPI::SomeIP::SerializableArguments<  CommonAPI::Deployable< ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions::SideBsdDispStatus, ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions_::SideBsdDispStatusDeployment_t > 
    >>
        ::sendEvent(
            *this,
            CommonAPI::SomeIP::event_id_t(0x8007),
            false,
             deployed_SideBsdDispSts 
    );
}

template <typename _Stub, typename... _Stubs>
void HAVPandAVPFunctionsSomeIPStubAdapterInternal<_Stub, _Stubs...>::fireHAVP_SVPScrnDispInfoEvent(const ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions::HAVP_SVPScrnInfoStruct& _HAVP_SVPScrnInfoStruct) {
    CommonAPI::Deployable< HAVPandAVPFunctions::HAVP_SVPScrnInfoStruct, ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions_::HAVP_SVPScrnInfoStructDeployment_t> deployed_HAVP_SVPScrnInfoStruct(_HAVP_SVPScrnInfoStruct, static_cast< ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions_::HAVP_SVPScrnInfoStructDeployment_t* >(nullptr));
    CommonAPI::SomeIP::StubEventHelper<CommonAPI::SomeIP::SerializableArguments<  CommonAPI::Deployable< ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions::HAVP_SVPScrnInfoStruct, ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions_::HAVP_SVPScrnInfoStructDeployment_t > 
    >>
        ::sendEvent(
            *this,
            CommonAPI::SomeIP::event_id_t(0x8004),
            false,
             deployed_HAVP_SVPScrnInfoStruct 
    );
}

template <typename _Stub = ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctionsStub, typename... _Stubs>
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

} // namespace IDC3_0
} // namespace GREATWALL
} // namespace v1

#endif // V1_GREATWALL_IDC3_0_HAV_Pand_AVP_Functions_SOMEIP_STUB_ADAPTER_HPP_
