/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.1.12.v202002200719.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#ifndef V1_GREATWALL_IDC3_0_HAV_Pand_AVP_Functions_PROXY_BASE_HPP_
#define V1_GREATWALL_IDC3_0_HAV_Pand_AVP_Functions_PROXY_BASE_HPP_

#include <v1/GREATWALL/IDC3_0/HAVPandAVPFunctions.hpp>



#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/Deployment.hpp>
#include <CommonAPI/InputStream.hpp>
#include <CommonAPI/OutputStream.hpp>
#include <CommonAPI/Struct.hpp>
#include <cstdint>
#include <vector>

#include <CommonAPI/Event.hpp>
#include <CommonAPI/Proxy.hpp>
#include <functional>
#include <future>

#undef COMMONAPI_INTERNAL_COMPILATION

namespace v1 {
namespace GREATWALL {
namespace IDC3_0 {

class HAVPandAVPFunctionsProxyBase
    : virtual public CommonAPI::Proxy {
public:
    typedef CommonAPI::Event<
        ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions::HAVPMapFileArray
    > HAVPPathMapEvent;
    typedef CommonAPI::Event<
        ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions::SideBsdDispErrorSts
    > SideBsdDispErrStsInfoEvent;
    typedef CommonAPI::Event<
        ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions::AVMStsReq
    > AVMDispReqEvent;
    typedef CommonAPI::Event<
        ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions::HAVPLearningWorldArray
    > HAVPPathInfoEvent;
    typedef CommonAPI::Event<
        ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions::HAVPVehDataArray
    > HAVPRendergInfoEvent;
    typedef CommonAPI::Event<
        ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions::SideBsdDispStatus
    > SideBsdDispStsInfoEvent;
    typedef CommonAPI::Event<
        ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions::HAVP_SVPScrnInfoStruct
    > HAVP_SVPScrnDispInfoEvent;

    typedef std::function<void(const CommonAPI::CallStatus&, const HAVPandAVPFunctions::SideBsdDispSts&)> SideBsdDispAsyncCallback;


    virtual HAVPPathMapEvent& getHAVPPathMapEvent() = 0;
    virtual SideBsdDispErrStsInfoEvent& getSideBsdDispErrStsInfoEvent() = 0;
    virtual AVMDispReqEvent& getAVMDispReqEvent() = 0;
    virtual HAVPPathInfoEvent& getHAVPPathInfoEvent() = 0;
    virtual HAVPRendergInfoEvent& getHAVPRendergInfoEvent() = 0;
    virtual SideBsdDispStsInfoEvent& getSideBsdDispStsInfoEvent() = 0;
    virtual HAVP_SVPScrnDispInfoEvent& getHAVP_SVPScrnDispInfoEvent() = 0;

    virtual void SideBsdDisp(const HAVPandAVPFunctions::SideBsdDispRequest &_SideBsdDispReq, CommonAPI::CallStatus &_internalCallStatus, HAVPandAVPFunctions::SideBsdDispSts &_SideBsdDispResp, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> SideBsdDispAsync(const HAVPandAVPFunctions::SideBsdDispRequest &_SideBsdDispReq, SideBsdDispAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
    /**
     * @invariant Fire And Forget
     */
    virtual void AVMDispResp(const HAVPandAVPFunctions::AVMStsResp &_AVMStsResp, CommonAPI::CallStatus &_internalCallStatus) = 0;
    /**
     * @invariant Fire And Forget
     */
    virtual void HAVP_SVPSwtReq(const HAVPandAVPFunctions::BtnEnaReq &_BtnEnaReq, CommonAPI::CallStatus &_internalCallStatus) = 0;
    /**
     * @invariant Fire And Forget
     */
    virtual void PrkgAreaReq(const HAVPandAVPFunctions::SetPrkgArea &_SetPrkgArea, CommonAPI::CallStatus &_internalCallStatus) = 0;
    /**
     * @invariant Fire And Forget
     */
    virtual void AutoReq(const HAVPandAVPFunctions::AutoPushReq &_AutoPushReq, CommonAPI::CallStatus &_internalCallStatus) = 0;
    /**
     * @invariant Fire And Forget
     */
    virtual void PrkgFlrReq(const HAVPandAVPFunctions::SetMapFlr &_SetMapFlr, CommonAPI::CallStatus &_internalCallStatus) = 0;
    /**
     * @invariant Fire And Forget
     */
    virtual void SVPReq(const HAVPandAVPFunctions::SVPfunctionReq &_SVPfunctionReq, CommonAPI::CallStatus &_internalCallStatus) = 0;
    /**
     * @invariant Fire And Forget
     */
    virtual void PrkgTypReq(const HAVPandAVPFunctions::SetPrkgSlotTyp &_SetPrkgSlotTyp, CommonAPI::CallStatus &_internalCallStatus) = 0;
    /**
     * @invariant Fire And Forget
     */
    virtual void TarPrkgIDReq(const HAVPandAVPFunctions::TarMapID &_TarMapID, CommonAPI::CallStatus &_internalCallStatus) = 0;
    /**
     * @invariant Fire And Forget
     */
    virtual void LvngPOIReq(const HAVPandAVPFunctions::SetLvngPOI &_SetLvngPOI, CommonAPI::CallStatus &_internalCallStatus) = 0;
    /**
     * @invariant Fire And Forget
     */
    virtual void PrkgLotMapUpdSt(const HAVPandAVPFunctions::MapUpdSt &_MapUpdSt, CommonAPI::CallStatus &_internalCallStatus) = 0;
    /**
     * @invariant Fire And Forget
     */
    virtual void NearSlotIDReq(const HAVPandAVPFunctions::SelNearSlotID &_SelNearSlotID, CommonAPI::CallStatus &_internalCallStatus) = 0;
    /**
     * @invariant Fire And Forget
     */
    virtual void PrkgSlotReq(const HAVPandAVPFunctions::SetPrkgSlot &_SetPrkgSlot, CommonAPI::CallStatus &_internalCallStatus) = 0;
    /**
     * @invariant Fire And Forget
     */
    virtual void HAVPReq(const HAVPandAVPFunctions::HAVPfunctionReq &_HAVPfunctionReq, CommonAPI::CallStatus &_internalCallStatus) = 0;
};

} // namespace IDC3_0
} // namespace GREATWALL
} // namespace v1


// Compatibility
namespace v1_0 = v1;

#endif // V1_GREATWALL_IDC3_0_HAV_Pand_AVP_Functions_PROXY_BASE_HPP_
