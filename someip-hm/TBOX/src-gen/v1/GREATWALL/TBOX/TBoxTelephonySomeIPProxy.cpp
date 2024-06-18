/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.someip 3.1.12.v202002200807.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#include <v1/GREATWALL/TBOX/TBoxTelephonySomeIPProxy.hpp>

#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/SomeIP/AddressTranslator.hpp>

#undef COMMONAPI_INTERNAL_COMPILATION

namespace v1 {
namespace GREATWALL {
namespace TBOX {

std::shared_ptr<CommonAPI::SomeIP::Proxy> createTBoxTelephonySomeIPProxy(
    const CommonAPI::SomeIP::Address &_address,
    const std::shared_ptr<CommonAPI::SomeIP::ProxyConnection> &_connection) {
    return std::make_shared< TBoxTelephonySomeIPProxy>(_address, _connection);
}

void initializeTBoxTelephonySomeIPProxy() {
    CommonAPI::SomeIP::AddressTranslator::get()->insert(
        "local:GREATWALL.TBOX.TBoxTelephony:v1_0:TBoxTelephony01",
        0x201, 0x1, 1, 0);
     CommonAPI::SomeIP::Factory::get()->registerProxyCreateMethod(
         TBoxTelephony::getInterface(),
         &createTBoxTelephonySomeIPProxy);
}

INITIALIZER(registerTBoxTelephonySomeIPProxy) {
    CommonAPI::SomeIP::Factory::get()->registerInterface(initializeTBoxTelephonySomeIPProxy);
}

TBoxTelephonySomeIPProxy::TBoxTelephonySomeIPProxy(
    const CommonAPI::SomeIP::Address &_address,
    const std::shared_ptr<CommonAPI::SomeIP::ProxyConnection> &_connection)
        : CommonAPI::SomeIP::Proxy(_address, _connection )
,          tBoxSimStatus_(*this, CommonAPI::SomeIP::eventgroup_id_t(0x1), CommonAPI::SomeIP::event_id_t(0x9001), CommonAPI::SomeIP::method_id_t(0x1001), false, false, static_cast< ::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxSimStatusStructDeployment_t* >(nullptr)),
          tBoxSignalStrength_(*this, CommonAPI::SomeIP::eventgroup_id_t(0x1), CommonAPI::SomeIP::event_id_t(0x9003), CommonAPI::SomeIP::method_id_t(0x1003), false, false, static_cast< ::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxSignalStrengthStructDeployment_t* >(nullptr)),
          tBoxNetworkProvider_(*this, CommonAPI::SomeIP::eventgroup_id_t(0x1), CommonAPI::SomeIP::event_id_t(0x9002), CommonAPI::SomeIP::method_id_t(0x1002), false, false, &::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxNetworkProviderStructDeployment)
,          tBoxCallState_(*this, 0x1, CommonAPI::SomeIP::event_id_t(0x8001), false, false, std::make_tuple(&::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxTelephoneNumberDeployment, static_cast< ::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxCallTypeDeployment_t* >(nullptr), static_cast< ::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxCallStateDeployment_t* >(nullptr), static_cast< CommonAPI::SomeIP::IntegerDeployment<int64_t>* >(nullptr)))
    {
    }

    TBoxTelephonySomeIPProxy::TBoxSimStatusAttribute& TBoxTelephonySomeIPProxy::getTBoxSimStatusAttribute() {
        return tBoxSimStatus_;
    }
    TBoxTelephonySomeIPProxy::TBoxSignalStrengthAttribute& TBoxTelephonySomeIPProxy::getTBoxSignalStrengthAttribute() {
        return tBoxSignalStrength_;
    }
    TBoxTelephonySomeIPProxy::TBoxNetworkProviderAttribute& TBoxTelephonySomeIPProxy::getTBoxNetworkProviderAttribute() {
        return tBoxNetworkProvider_;
    }

    TBoxTelephonySomeIPProxy::TBoxCallStateEvent& TBoxTelephonySomeIPProxy::getTBoxCallStateEvent() {
        return tBoxCallState_;
    }

        void TBoxTelephonySomeIPProxy::TBoxCallOperation(const TBoxTelephony::TBoxTelephoneNumber &_TBoxTelephoneNumber, const TBoxTelephony::TBoxCallType &_TBoxCallType, const TBoxTelephony::TBoxCallOperation &_TBoxCallOperation, const TBoxTelephony::long64 &_TBoxCallID_In, CommonAPI::CallStatus &_internalCallStatus, TBoxTelephony::TBoxResponse &_TBoxResponse, TBoxTelephony::long64 &_TBoxCallID_Out, const CommonAPI::CallInfo *_info) {
            CommonAPI::Deployable< TBoxTelephony::TBoxTelephoneNumber, ::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxTelephoneNumberDeployment_t> deploy_TBoxTelephoneNumber(_TBoxTelephoneNumber, &::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxTelephoneNumberDeployment);
            CommonAPI::Deployable< TBoxTelephony::TBoxCallType, ::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxCallTypeDeployment_t> deploy_TBoxCallType(_TBoxCallType, static_cast< ::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxCallTypeDeployment_t* >(nullptr));
            CommonAPI::Deployable< TBoxTelephony::TBoxCallOperation, ::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxCallOperationDeployment_t> deploy_TBoxCallOperation(_TBoxCallOperation, static_cast< ::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxCallOperationDeployment_t* >(nullptr));
            CommonAPI::Deployable< TBoxTelephony::long64, CommonAPI::SomeIP::IntegerDeployment<int64_t>> deploy_TBoxCallID_In(_TBoxCallID_In, static_cast< CommonAPI::SomeIP::IntegerDeployment<int64_t>* >(nullptr));
            CommonAPI::Deployable< TBoxTelephony::TBoxResponse, ::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxResponseDeployment_t> deploy_TBoxResponse(static_cast< ::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxResponseDeployment_t* >(nullptr));
            CommonAPI::Deployable< TBoxTelephony::long64, CommonAPI::SomeIP::IntegerDeployment<int64_t>> deploy_TBoxCallID_Out(static_cast< CommonAPI::SomeIP::IntegerDeployment<int64_t>* >(nullptr));
            CommonAPI::SomeIP::ProxyHelper<
                CommonAPI::SomeIP::SerializableArguments<
                    CommonAPI::Deployable<
                        TBoxTelephony::TBoxTelephoneNumber,
                        ::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxTelephoneNumberDeployment_t
                    >,
                    CommonAPI::Deployable<
                        TBoxTelephony::TBoxCallType,
                        ::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxCallTypeDeployment_t
                    >,
                    CommonAPI::Deployable<
                        TBoxTelephony::TBoxCallOperation,
                        ::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxCallOperationDeployment_t
                    >,
                    CommonAPI::Deployable<
                        TBoxTelephony::long64,
                        CommonAPI::SomeIP::IntegerDeployment<int64_t>
                    >
                >,
                CommonAPI::SomeIP::SerializableArguments<
                    CommonAPI::Deployable<
                        TBoxTelephony::TBoxResponse,
                        ::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxResponseDeployment_t
                    >,
                    CommonAPI::Deployable<
                        TBoxTelephony::long64,
                        CommonAPI::SomeIP::IntegerDeployment<int64_t>
                    >
                >
            >::callMethodWithReply(
            *this,
            CommonAPI::SomeIP::method_id_t(0x2),
            false,
            false,
    (_info ? _info : &CommonAPI::SomeIP::defaultCallInfo),
    deploy_TBoxTelephoneNumber, deploy_TBoxCallType, deploy_TBoxCallOperation, deploy_TBoxCallID_In,
    _internalCallStatus,
    deploy_TBoxResponse, deploy_TBoxCallID_Out);
    _TBoxResponse = deploy_TBoxResponse.getValue();
    _TBoxCallID_Out = deploy_TBoxCallID_Out.getValue();
    }
    std::future<CommonAPI::CallStatus> TBoxTelephonySomeIPProxy::TBoxCallOperationAsync(const TBoxTelephony::TBoxTelephoneNumber &_TBoxTelephoneNumber, const TBoxTelephony::TBoxCallType &_TBoxCallType, const TBoxTelephony::TBoxCallOperation &_TBoxCallOperation, const TBoxTelephony::long64 &_TBoxCallID_In, TBoxCallOperationAsyncCallback _callback, const CommonAPI::CallInfo *_info) {
        CommonAPI::Deployable< TBoxTelephony::TBoxTelephoneNumber, ::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxTelephoneNumberDeployment_t> deploy_TBoxTelephoneNumber(_TBoxTelephoneNumber, &::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxTelephoneNumberDeployment);
        CommonAPI::Deployable< TBoxTelephony::TBoxCallType, ::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxCallTypeDeployment_t> deploy_TBoxCallType(_TBoxCallType, static_cast< ::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxCallTypeDeployment_t* >(nullptr));
        CommonAPI::Deployable< TBoxTelephony::TBoxCallOperation, ::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxCallOperationDeployment_t> deploy_TBoxCallOperation(_TBoxCallOperation, static_cast< ::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxCallOperationDeployment_t* >(nullptr));
        CommonAPI::Deployable< TBoxTelephony::long64, CommonAPI::SomeIP::IntegerDeployment<int64_t>> deploy_TBoxCallID_In(_TBoxCallID_In, static_cast< CommonAPI::SomeIP::IntegerDeployment<int64_t>* >(nullptr));
        CommonAPI::Deployable< TBoxTelephony::TBoxResponse, ::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxResponseDeployment_t> deploy_TBoxResponse(static_cast< ::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxResponseDeployment_t* >(nullptr));
        CommonAPI::Deployable< TBoxTelephony::long64, CommonAPI::SomeIP::IntegerDeployment<int64_t>> deploy_TBoxCallID_Out(static_cast< CommonAPI::SomeIP::IntegerDeployment<int64_t>* >(nullptr));
        return CommonAPI::SomeIP::ProxyHelper<
            CommonAPI::SomeIP::SerializableArguments<
                CommonAPI::Deployable<
                    TBoxTelephony::TBoxTelephoneNumber,
                    ::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxTelephoneNumberDeployment_t
                >,
                CommonAPI::Deployable<
                    TBoxTelephony::TBoxCallType,
                    ::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxCallTypeDeployment_t
                >,
                CommonAPI::Deployable<
                    TBoxTelephony::TBoxCallOperation,
                    ::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxCallOperationDeployment_t
                >,
                CommonAPI::Deployable<
                    TBoxTelephony::long64,
                    CommonAPI::SomeIP::IntegerDeployment<int64_t>
                >
            >,
            CommonAPI::SomeIP::SerializableArguments<
                CommonAPI::Deployable<
                    TBoxTelephony::TBoxResponse,
                    ::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxResponseDeployment_t
                >,
                CommonAPI::Deployable<
                    TBoxTelephony::long64,
                    CommonAPI::SomeIP::IntegerDeployment<int64_t>
                >
            >
        >::callMethodAsync(
            *this,
            CommonAPI::SomeIP::method_id_t(0x2),
            false,
            false,
            (_info ? _info : &CommonAPI::SomeIP::defaultCallInfo),
            deploy_TBoxTelephoneNumber, deploy_TBoxCallType, deploy_TBoxCallOperation, deploy_TBoxCallID_In,
            [_callback] (CommonAPI::CallStatus _internalCallStatus, CommonAPI::Deployable< TBoxTelephony::TBoxResponse, ::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxResponseDeployment_t > _TBoxResponse, CommonAPI::Deployable< TBoxTelephony::long64, CommonAPI::SomeIP::IntegerDeployment<int64_t> > _TBoxCallID_Out) {
                if (_callback)
                    _callback(_internalCallStatus, _TBoxResponse.getValue(), _TBoxCallID_Out.getValue());
            },
            std::make_tuple(deploy_TBoxResponse, deploy_TBoxCallID_Out));
    }
        void TBoxTelephonySomeIPProxy::TBoxSIMInfor(CommonAPI::CallStatus &_internalCallStatus, TBoxTelephony::ICCID &_ICCID, TBoxTelephony::IMEI &_IMEI, TBoxTelephony::IMSI &_IMSI, const CommonAPI::CallInfo *_info) {
            CommonAPI::Deployable< TBoxTelephony::ICCID, CommonAPI::SomeIP::StringDeployment> deploy_ICCID(&::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxSIMInfor_ICCIDDeployment);
            CommonAPI::Deployable< TBoxTelephony::IMEI, CommonAPI::SomeIP::StringDeployment> deploy_IMEI(&::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxSIMInfor_IMEIDeployment);
            CommonAPI::Deployable< TBoxTelephony::IMSI, CommonAPI::SomeIP::StringDeployment> deploy_IMSI(&::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxSIMInfor_IMSIDeployment);
            CommonAPI::SomeIP::ProxyHelper<
                CommonAPI::SomeIP::SerializableArguments<
                >,
                CommonAPI::SomeIP::SerializableArguments<
                    CommonAPI::Deployable<
                        TBoxTelephony::ICCID,
                        CommonAPI::SomeIP::StringDeployment
                    >,
                    CommonAPI::Deployable<
                        TBoxTelephony::IMEI,
                        CommonAPI::SomeIP::StringDeployment
                    >,
                    CommonAPI::Deployable<
                        TBoxTelephony::IMSI,
                        CommonAPI::SomeIP::StringDeployment
                    >
                >
            >::callMethodWithReply(
            *this,
            CommonAPI::SomeIP::method_id_t(0x3),
            false,
            false,
    (_info ? _info : &CommonAPI::SomeIP::defaultCallInfo),
    _internalCallStatus,
    deploy_ICCID, deploy_IMEI, deploy_IMSI);
    _ICCID = deploy_ICCID.getValue();
    _IMEI = deploy_IMEI.getValue();
    _IMSI = deploy_IMSI.getValue();
    }
    std::future<CommonAPI::CallStatus> TBoxTelephonySomeIPProxy::TBoxSIMInforAsync(TBoxSIMInforAsyncCallback _callback, const CommonAPI::CallInfo *_info) {
        CommonAPI::Deployable< TBoxTelephony::ICCID, CommonAPI::SomeIP::StringDeployment> deploy_ICCID(&::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxSIMInfor_ICCIDDeployment);
        CommonAPI::Deployable< TBoxTelephony::IMEI, CommonAPI::SomeIP::StringDeployment> deploy_IMEI(&::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxSIMInfor_IMEIDeployment);
        CommonAPI::Deployable< TBoxTelephony::IMSI, CommonAPI::SomeIP::StringDeployment> deploy_IMSI(&::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxSIMInfor_IMSIDeployment);
        return CommonAPI::SomeIP::ProxyHelper<
            CommonAPI::SomeIP::SerializableArguments<
            >,
            CommonAPI::SomeIP::SerializableArguments<
                CommonAPI::Deployable<
                    TBoxTelephony::ICCID,
                    CommonAPI::SomeIP::StringDeployment
                >,
                CommonAPI::Deployable<
                    TBoxTelephony::IMEI,
                    CommonAPI::SomeIP::StringDeployment
                >,
                CommonAPI::Deployable<
                    TBoxTelephony::IMSI,
                    CommonAPI::SomeIP::StringDeployment
                >
            >
        >::callMethodAsync(
            *this,
            CommonAPI::SomeIP::method_id_t(0x3),
            false,
            false,
            (_info ? _info : &CommonAPI::SomeIP::defaultCallInfo),
            [_callback] (CommonAPI::CallStatus _internalCallStatus, CommonAPI::Deployable< TBoxTelephony::ICCID, CommonAPI::SomeIP::StringDeployment > _ICCID, CommonAPI::Deployable< TBoxTelephony::IMEI, CommonAPI::SomeIP::StringDeployment > _IMEI, CommonAPI::Deployable< TBoxTelephony::IMSI, CommonAPI::SomeIP::StringDeployment > _IMSI) {
                if (_callback)
                    _callback(_internalCallStatus, _ICCID.getValue(), _IMEI.getValue(), _IMSI.getValue());
            },
            std::make_tuple(deploy_ICCID, deploy_IMEI, deploy_IMSI));
    }
        void TBoxTelephonySomeIPProxy::TBoxStartCall(const TBoxTelephony::TBoxTelephoneNumber &_TBoxTelephoneNumber, const TBoxTelephony::TBoxCallType &_TBoxCallType, const TBoxTelephony::long64 &_TBoxCallID_In, CommonAPI::CallStatus &_internalCallStatus, TBoxTelephony::TBoxResponse &_TBoxResponse, TBoxTelephony::long64 &_TBoxCallID_Out, const CommonAPI::CallInfo *_info) {
            CommonAPI::Deployable< TBoxTelephony::TBoxTelephoneNumber, ::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxTelephoneNumberDeployment_t> deploy_TBoxTelephoneNumber(_TBoxTelephoneNumber, &::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxTelephoneNumberDeployment);
            CommonAPI::Deployable< TBoxTelephony::TBoxCallType, ::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxCallTypeDeployment_t> deploy_TBoxCallType(_TBoxCallType, static_cast< ::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxCallTypeDeployment_t* >(nullptr));
            CommonAPI::Deployable< TBoxTelephony::long64, CommonAPI::SomeIP::IntegerDeployment<int64_t>> deploy_TBoxCallID_In(_TBoxCallID_In, static_cast< CommonAPI::SomeIP::IntegerDeployment<int64_t>* >(nullptr));
            CommonAPI::Deployable< TBoxTelephony::TBoxResponse, ::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxResponseDeployment_t> deploy_TBoxResponse(static_cast< ::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxResponseDeployment_t* >(nullptr));
            CommonAPI::Deployable< TBoxTelephony::long64, CommonAPI::SomeIP::IntegerDeployment<int64_t>> deploy_TBoxCallID_Out(static_cast< CommonAPI::SomeIP::IntegerDeployment<int64_t>* >(nullptr));
            CommonAPI::SomeIP::ProxyHelper<
                CommonAPI::SomeIP::SerializableArguments<
                    CommonAPI::Deployable<
                        TBoxTelephony::TBoxTelephoneNumber,
                        ::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxTelephoneNumberDeployment_t
                    >,
                    CommonAPI::Deployable<
                        TBoxTelephony::TBoxCallType,
                        ::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxCallTypeDeployment_t
                    >,
                    CommonAPI::Deployable<
                        TBoxTelephony::long64,
                        CommonAPI::SomeIP::IntegerDeployment<int64_t>
                    >
                >,
                CommonAPI::SomeIP::SerializableArguments<
                    CommonAPI::Deployable<
                        TBoxTelephony::TBoxResponse,
                        ::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxResponseDeployment_t
                    >,
                    CommonAPI::Deployable<
                        TBoxTelephony::long64,
                        CommonAPI::SomeIP::IntegerDeployment<int64_t>
                    >
                >
            >::callMethodWithReply(
            *this,
            CommonAPI::SomeIP::method_id_t(0x1),
            false,
            false,
    (_info ? _info : &CommonAPI::SomeIP::defaultCallInfo),
    deploy_TBoxTelephoneNumber, deploy_TBoxCallType, deploy_TBoxCallID_In,
    _internalCallStatus,
    deploy_TBoxResponse, deploy_TBoxCallID_Out);
    _TBoxResponse = deploy_TBoxResponse.getValue();
    _TBoxCallID_Out = deploy_TBoxCallID_Out.getValue();
    }
    std::future<CommonAPI::CallStatus> TBoxTelephonySomeIPProxy::TBoxStartCallAsync(const TBoxTelephony::TBoxTelephoneNumber &_TBoxTelephoneNumber, const TBoxTelephony::TBoxCallType &_TBoxCallType, const TBoxTelephony::long64 &_TBoxCallID_In, TBoxStartCallAsyncCallback _callback, const CommonAPI::CallInfo *_info) {
        CommonAPI::Deployable< TBoxTelephony::TBoxTelephoneNumber, ::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxTelephoneNumberDeployment_t> deploy_TBoxTelephoneNumber(_TBoxTelephoneNumber, &::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxTelephoneNumberDeployment);
        CommonAPI::Deployable< TBoxTelephony::TBoxCallType, ::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxCallTypeDeployment_t> deploy_TBoxCallType(_TBoxCallType, static_cast< ::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxCallTypeDeployment_t* >(nullptr));
        CommonAPI::Deployable< TBoxTelephony::long64, CommonAPI::SomeIP::IntegerDeployment<int64_t>> deploy_TBoxCallID_In(_TBoxCallID_In, static_cast< CommonAPI::SomeIP::IntegerDeployment<int64_t>* >(nullptr));
        CommonAPI::Deployable< TBoxTelephony::TBoxResponse, ::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxResponseDeployment_t> deploy_TBoxResponse(static_cast< ::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxResponseDeployment_t* >(nullptr));
        CommonAPI::Deployable< TBoxTelephony::long64, CommonAPI::SomeIP::IntegerDeployment<int64_t>> deploy_TBoxCallID_Out(static_cast< CommonAPI::SomeIP::IntegerDeployment<int64_t>* >(nullptr));
        return CommonAPI::SomeIP::ProxyHelper<
            CommonAPI::SomeIP::SerializableArguments<
                CommonAPI::Deployable<
                    TBoxTelephony::TBoxTelephoneNumber,
                    ::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxTelephoneNumberDeployment_t
                >,
                CommonAPI::Deployable<
                    TBoxTelephony::TBoxCallType,
                    ::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxCallTypeDeployment_t
                >,
                CommonAPI::Deployable<
                    TBoxTelephony::long64,
                    CommonAPI::SomeIP::IntegerDeployment<int64_t>
                >
            >,
            CommonAPI::SomeIP::SerializableArguments<
                CommonAPI::Deployable<
                    TBoxTelephony::TBoxResponse,
                    ::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxResponseDeployment_t
                >,
                CommonAPI::Deployable<
                    TBoxTelephony::long64,
                    CommonAPI::SomeIP::IntegerDeployment<int64_t>
                >
            >
        >::callMethodAsync(
            *this,
            CommonAPI::SomeIP::method_id_t(0x1),
            false,
            false,
            (_info ? _info : &CommonAPI::SomeIP::defaultCallInfo),
            deploy_TBoxTelephoneNumber, deploy_TBoxCallType, deploy_TBoxCallID_In,
            [_callback] (CommonAPI::CallStatus _internalCallStatus, CommonAPI::Deployable< TBoxTelephony::TBoxResponse, ::v1::GREATWALL::TBOX::TBoxTelephony_::TBoxResponseDeployment_t > _TBoxResponse, CommonAPI::Deployable< TBoxTelephony::long64, CommonAPI::SomeIP::IntegerDeployment<int64_t> > _TBoxCallID_Out) {
                if (_callback)
                    _callback(_internalCallStatus, _TBoxResponse.getValue(), _TBoxCallID_Out.getValue());
            },
            std::make_tuple(deploy_TBoxResponse, deploy_TBoxCallID_Out));
    }



    void TBoxTelephonySomeIPProxy::getOwnVersion(uint16_t& ownVersionMajor, uint16_t& ownVersionMinor) const {
    ownVersionMajor = 1;
    ownVersionMinor = 0;
    }

} // namespace TBOX
} // namespace GREATWALL
} // namespace v1
