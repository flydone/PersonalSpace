/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.1.12.v202002200719.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#ifndef V1_GREATWALL_IDC3_0_HAV_Pand_AVP_Functions_STUB_DEFAULT_HPP_
#define V1_GREATWALL_IDC3_0_HAV_Pand_AVP_Functions_STUB_DEFAULT_HPP_


#include <CommonAPI/Export.hpp>

#include <v1/GREATWALL/IDC3_0/HAVPandAVPFunctionsStub.hpp>
#include <sstream>

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

/**
 * Provides a default implementation for HAVPandAVPFunctionsStubRemoteEvent and
 * HAVPandAVPFunctionsStub. Method callbacks have an empty implementation,
 * remote set calls on attributes will always change the value of the attribute
 * to the one received.
 *
 * Override this stub if you only want to provide a subset of the functionality
 * that would be defined for this service, and/or if you do not need any non-default
 * behaviour.
 */
class COMMONAPI_EXPORT_CLASS_EXPLICIT HAVPandAVPFunctionsStubDefault
    : public virtual HAVPandAVPFunctionsStub {
public:
    COMMONAPI_EXPORT HAVPandAVPFunctionsStubDefault();

    COMMONAPI_EXPORT HAVPandAVPFunctionsStubRemoteEvent* initStubAdapter(const std::shared_ptr< HAVPandAVPFunctionsStubAdapter> &_adapter);

    COMMONAPI_EXPORT const CommonAPI::Version& getInterfaceVersion(std::shared_ptr<CommonAPI::ClientId> _client);


    COMMONAPI_EXPORT virtual void SideBsdDisp(const std::shared_ptr<CommonAPI::ClientId> _client, HAVPandAVPFunctions::SideBsdDispRequest _SideBsdDispReq, SideBsdDispReply_t _reply);
    COMMONAPI_EXPORT virtual void AVMDispResp(const std::shared_ptr<CommonAPI::ClientId> _client, HAVPandAVPFunctions::AVMStsResp _AVMStsResp);
    COMMONAPI_EXPORT virtual void HAVP_SVPSwtReq(const std::shared_ptr<CommonAPI::ClientId> _client, HAVPandAVPFunctions::BtnEnaReq _BtnEnaReq);
    COMMONAPI_EXPORT virtual void PrkgAreaReq(const std::shared_ptr<CommonAPI::ClientId> _client, HAVPandAVPFunctions::SetPrkgArea _SetPrkgArea);
    COMMONAPI_EXPORT virtual void AutoReq(const std::shared_ptr<CommonAPI::ClientId> _client, HAVPandAVPFunctions::AutoPushReq _AutoPushReq);
    COMMONAPI_EXPORT virtual void PrkgFlrReq(const std::shared_ptr<CommonAPI::ClientId> _client, HAVPandAVPFunctions::SetMapFlr _SetMapFlr);
    COMMONAPI_EXPORT virtual void SVPReq(const std::shared_ptr<CommonAPI::ClientId> _client, HAVPandAVPFunctions::SVPfunctionReq _SVPfunctionReq);
    COMMONAPI_EXPORT virtual void PrkgTypReq(const std::shared_ptr<CommonAPI::ClientId> _client, HAVPandAVPFunctions::SetPrkgSlotTyp _SetPrkgSlotTyp);
    COMMONAPI_EXPORT virtual void TarPrkgIDReq(const std::shared_ptr<CommonAPI::ClientId> _client, HAVPandAVPFunctions::TarMapID _TarMapID);
    COMMONAPI_EXPORT virtual void LvngPOIReq(const std::shared_ptr<CommonAPI::ClientId> _client, HAVPandAVPFunctions::SetLvngPOI _SetLvngPOI);
    COMMONAPI_EXPORT virtual void PrkgLotMapUpdSt(const std::shared_ptr<CommonAPI::ClientId> _client, HAVPandAVPFunctions::MapUpdSt _MapUpdSt);
    COMMONAPI_EXPORT virtual void NearSlotIDReq(const std::shared_ptr<CommonAPI::ClientId> _client, HAVPandAVPFunctions::SelNearSlotID _SelNearSlotID);
    COMMONAPI_EXPORT virtual void PrkgSlotReq(const std::shared_ptr<CommonAPI::ClientId> _client, HAVPandAVPFunctions::SetPrkgSlot _SetPrkgSlot);
    COMMONAPI_EXPORT virtual void HAVPReq(const std::shared_ptr<CommonAPI::ClientId> _client, HAVPandAVPFunctions::HAVPfunctionReq _HAVPfunctionReq);

    COMMONAPI_EXPORT virtual void fireHAVPPathMapEvent(const ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions::HAVPMapFileArray &_HAVPMapFileArray);
    COMMONAPI_EXPORT virtual void fireSideBsdDispErrStsInfoEvent(const ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions::SideBsdDispErrorSts &_SideBsdDispErrSts);
    COMMONAPI_EXPORT virtual void fireAVMDispReqEvent(const ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions::AVMStsReq &_AVMStsReq);
    COMMONAPI_EXPORT virtual void fireHAVPPathInfoEvent(const ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions::HAVPLearningWorldArray &_HAVPLearningWorldArray);
    COMMONAPI_EXPORT virtual void fireHAVPRendergInfoEvent(const ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions::HAVPVehDataArray &_HAVPVehDataArray);
    COMMONAPI_EXPORT virtual void fireSideBsdDispStsInfoEvent(const ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions::SideBsdDispStatus &_SideBsdDispSts);
    COMMONAPI_EXPORT virtual void fireHAVP_SVPScrnDispInfoEvent(const ::v1::GREATWALL::IDC3_0::HAVPandAVPFunctions::HAVP_SVPScrnInfoStruct &_HAVP_SVPScrnInfoStruct);

    
protected:
    class COMMONAPI_EXPORT_CLASS_EXPLICIT RemoteEventHandler: public virtual HAVPandAVPFunctionsStubRemoteEvent {
    public:
        COMMONAPI_EXPORT RemoteEventHandler(HAVPandAVPFunctionsStubDefault *_defaultStub);


    private:
        HAVPandAVPFunctionsStubDefault *defaultStub_;
    };
protected:
    HAVPandAVPFunctionsStubDefault::RemoteEventHandler remoteEventHandler_;

private:


    CommonAPI::Version interfaceVersion_;
};

} // namespace IDC3_0
} // namespace GREATWALL
} // namespace v1


// Compatibility
namespace v1_0 = v1;

#endif // V1_GREATWALL_IDC3_0_HAV_Pand_AVP_Functions_STUB_DEFAULT
