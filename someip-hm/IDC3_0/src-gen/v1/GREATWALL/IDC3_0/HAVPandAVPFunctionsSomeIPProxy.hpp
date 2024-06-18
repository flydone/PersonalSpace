/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.someip 3.1.12.v202002200807.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#ifndef V1_GREATWALL_IDC3_0_HAV_PAND_AVP_FUNCTIONS_SOMEIP_PROXY_HPP_
#define V1_GREATWALL_IDC3_0_HAV_PAND_AVP_FUNCTIONS_SOMEIP_PROXY_HPP_

#include <v1/GREATWALL/IDC3_0/HAVPandAVPFunctionsProxyBase.hpp>
#include <v1/GREATWALL/IDC3_0/HAVPandAVPFunctionsSomeIPDeployment.hpp>

#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/SomeIP/Factory.hpp>
#include <CommonAPI/SomeIP/Proxy.hpp>
#include <CommonAPI/SomeIP/Types.hpp>
#include <CommonAPI/SomeIP/Event.hpp>

#undef COMMONAPI_INTERNAL_COMPILATION

#include <string>

# if defined(_MSC_VER)
#  if _MSC_VER >= 1300
/*
 * Diamond inheritance is used for the CommonAPI::Proxy base class.
 * The Microsoft compiler put warning (C4250) using a desired c++ feature: "Delegating to a sister class"
 * A powerful technique that arises from using virtual inheritance is to delegate a method from a class in another class
 * by using a common abstract base class. This is also called cross delegation.
 */
#    pragma warning( disable : 4250 )
#  endif
# endif

namespace v1 {
namespace GREATWALL {
namespace IDC3_0 {

class HAVPandAVPFunctionsSomeIPProxy
    : virtual public HAVPandAVPFunctionsProxyBase,
    virtual public CommonAPI::SomeIP::Proxy {
public:
    HAVPandAVPFunctionsSomeIPProxy(
        const CommonAPI::SomeIP::Address &_address,
        const std::shared_ptr<CommonAPI::SomeIP::ProxyConnection> &_connection);

    virtual ~HAVPandAVPFunctionsSomeIPProxy() { }


    virtual HAVPPathMapEvent& getHAVPPathMapEvent();
    virtual SideBsdDispErrStsInfoEvent& getSideBsdDispErrStsInfoEvent();
    virtual AVMDispReqEvent& getAVMDispReqEvent();
    virtual HAVPPathInfoEvent& getHAVPPathInfoEvent();
    virtual HAVPRendergInfoEvent& getHAVPRendergInfoEvent();
    virtual SideBsdDispStsInfoEvent& getSideBsdDispStsInfoEvent();
    virtual HAVP_SVPScrnDispInfoEvent& getHAVP_SVPScrnDispInfoEvent();

    virtual void SideBsdDisp(const HAVPandAVPFunctions::SideBsdDispRequest &_SideBsdDispReq, CommonAPI::CallStatus &_internalCallStatus, HAVPandAVPFunctions::SideBsdDispSts &_SideBsdDispResp, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> SideBsdDispAsync(const HAVPandAVPFunctions::SideBsdDispRequest &_SideBsdDispReq, SideBsdDispAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    virtual void AVMDispResp(const HAVPandAVPFunctions::AVMStsResp &_AVMStsResp, CommonAPI::CallStatus &_internalCallStatus);
    virtual void HAVP_SVPSwtReq(const HAVPandAVPFunctions::BtnEnaReq &_BtnEnaReq, CommonAPI::CallStatus &_internalCallStatus);
    virtual void PrkgAreaReq(const HAVPandAVPFunctions::SetPrkgArea &_SetPrkgArea, CommonAPI::CallStatus &_internalCallStatus);
    virtual void AutoReq(const HAVPandAVPFunctions::AutoPushReq &_AutoPushReq, CommonAPI::CallStatus &_internalCallStatus);
    virtual void PrkgFlrReq(const HAVPandAVPFunctions::SetMapFlr &_SetMapFlr, CommonAPI::CallStatus &_internalCallStatus);
    virtual void SVPReq(const HAVPandAVPFunctions::SVPfunctionReq &_SVPfunctionReq, CommonAPI::CallStatus &_internalCallStatus);
    virtual void PrkgTypReq(const HAVPandAVPFunctions::SetPrkgSlotTyp &_SetPrkgSlotTyp, CommonAPI::CallStatus &_internalCallStatus);
    virtual void TarPrkgIDReq(const HAVPandAVPFunctions::TarMapID &_TarMapID, CommonAPI::CallStatus &_internalCallStatus);
    virtual void LvngPOIReq(const HAVPandAVPFunctions::SetLvngPOI &_SetLvngPOI, CommonAPI::CallStatus &_internalCallStatus);
    virtual void PrkgLotMapUpdSt(const HAVPandAVPFunctions::MapUpdSt &_MapUpdSt, CommonAPI::CallStatus &_internalCallStatus);
    virtual void NearSlotIDReq(const HAVPandAVPFunctions::SelNearSlotID &_SelNearSlotID, CommonAPI::CallStatus &_internalCallStatus);
    virtual void PrkgSlotReq(const HAVPandAVPFunctions::SetPrkgSlot &_SetPrkgSlot, CommonAPI::CallStatus &_internalCallStatus);
    virtual void HAVPReq(const HAVPandAVPFunctions::HAVPfunctionReq &_HAVPfunctionReq, CommonAPI::CallStatus &_internalCallStatus);


    virtual void getOwnVersion(uint16_t &_major, uint16_t &_minor) const;

private:


     CommonAPI::SomeIP::Event<HAVPPathMapEvent, CommonAPI::Deployable< ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions::HAVPMapFileArray, ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions_::HAVPMapFileArrayDeployment_t >> hAVPPathMap_;
     CommonAPI::SomeIP::Event<SideBsdDispErrStsInfoEvent, CommonAPI::Deployable< ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions::SideBsdDispErrorSts, ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions_::SideBsdDispErrorStsDeployment_t >> sideBsdDispErrStsInfo_;
     CommonAPI::SomeIP::Event<AVMDispReqEvent, CommonAPI::Deployable< ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions::AVMStsReq, ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions_::AVMStsReqDeployment_t >> aVMDispReq_;
     CommonAPI::SomeIP::Event<HAVPPathInfoEvent, CommonAPI::Deployable< ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions::HAVPLearningWorldArray, ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions_::HAVPLearningWorldArrayDeployment_t >> hAVPPathInfo_;
     CommonAPI::SomeIP::Event<HAVPRendergInfoEvent, CommonAPI::Deployable< ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions::HAVPVehDataArray, ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions_::HAVPVehDataArrayDeployment_t >> hAVPRendergInfo_;
     CommonAPI::SomeIP::Event<SideBsdDispStsInfoEvent, CommonAPI::Deployable< ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions::SideBsdDispStatus, ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions_::SideBsdDispStatusDeployment_t >> sideBsdDispStsInfo_;
     CommonAPI::SomeIP::Event<HAVP_SVPScrnDispInfoEvent, CommonAPI::Deployable< ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions::HAVP_SVPScrnInfoStruct, ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions_::HAVP_SVPScrnInfoStructDeployment_t >> hAVP_SVPScrnDispInfo_;

};

} // namespace IDC3_0
} // namespace GREATWALL
} // namespace v1

#endif // V1_GREATWALL_IDC3_0_HAV_Pand_AVP_Functions_SOMEIP_PROXY_HPP_