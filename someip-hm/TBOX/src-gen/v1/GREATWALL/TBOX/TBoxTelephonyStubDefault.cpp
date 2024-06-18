/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.1.12.v202002200719.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#include <v1/GREATWALL/TBOX/TBoxTelephonyStubDefault.hpp>
#include <assert.h>

namespace v1 {
namespace GREATWALL {
namespace TBOX {

TBoxTelephonyStubDefault::TBoxTelephonyStubDefault():
        remoteEventHandler_(this),
        interfaceVersion_(TBoxTelephony::getInterfaceVersion()) {
}

const CommonAPI::Version& TBoxTelephonyStubDefault::getInterfaceVersion(std::shared_ptr<CommonAPI::ClientId> _client) {
    (void)_client;
    return interfaceVersion_;
}

TBoxTelephonyStubRemoteEvent* TBoxTelephonyStubDefault::initStubAdapter(const std::shared_ptr< TBoxTelephonyStubAdapter> &_adapter) {
    CommonAPI::Stub<TBoxTelephonyStubAdapter, TBoxTelephonyStubRemoteEvent>::stubAdapter_ = _adapter;
    return &remoteEventHandler_;
}

 const ::v1::GREATWALL::TBOX::TBoxTelephony::TBoxSimStatusStruct& TBoxTelephonyStubDefault::getTBoxSimStatusAttribute() {
     return tBoxSimStatusAttributeValue_;
 }

 const ::v1::GREATWALL::TBOX::TBoxTelephony::TBoxSimStatusStruct& TBoxTelephonyStubDefault::getTBoxSimStatusAttribute(const std::shared_ptr<CommonAPI::ClientId> _client) {
     (void)_client;
     return getTBoxSimStatusAttribute();
 }

 void TBoxTelephonyStubDefault::setTBoxSimStatusAttribute(::v1::GREATWALL::TBOX::TBoxTelephony::TBoxSimStatusStruct _value) {
     std::shared_ptr<TBoxTelephonyStubAdapter> stubAdapter = CommonAPI::Stub<TBoxTelephonyStubAdapter,
     TBoxTelephonyStubRemoteEvent>::stubAdapter_.lock();
     if(stubAdapter) {
         stubAdapter->lockTBoxSimStatusAttribute(true);
         const bool valueChanged = (tBoxSimStatusAttributeValue_ != _value);
         if (valueChanged) {
             tBoxSimStatusAttributeValue_ = std::move(_value);
             fireTBoxSimStatusAttributeChanged(tBoxSimStatusAttributeValue_);
         }
         stubAdapter->lockTBoxSimStatusAttribute(false);
     } else {
         const bool valueChanged = trySetTBoxSimStatusAttribute(std::move(_value));
         if (valueChanged) {
             fireTBoxSimStatusAttributeChanged(tBoxSimStatusAttributeValue_);
         }
     }
}

 bool TBoxTelephonyStubDefault::trySetTBoxSimStatusAttribute(::v1::GREATWALL::TBOX::TBoxTelephony::TBoxSimStatusStruct _value) {
     if (!validateTBoxSimStatusAttributeRequestedValue(_value))
         return false;

     bool valueChanged;
     std::shared_ptr<TBoxTelephonyStubAdapter> stubAdapter = CommonAPI::Stub<TBoxTelephonyStubAdapter, TBoxTelephonyStubRemoteEvent>::stubAdapter_.lock();
     if(stubAdapter) {
         stubAdapter->lockTBoxSimStatusAttribute(true);
         valueChanged = (tBoxSimStatusAttributeValue_ != _value);
         tBoxSimStatusAttributeValue_ = std::move(_value);
         stubAdapter->lockTBoxSimStatusAttribute(false);
     } else {
         valueChanged = (tBoxSimStatusAttributeValue_ != _value);
         tBoxSimStatusAttributeValue_ = std::move(_value);
     }

     return valueChanged;
 }

 bool TBoxTelephonyStubDefault::validateTBoxSimStatusAttributeRequestedValue(const ::v1::GREATWALL::TBOX::TBoxTelephony::TBoxSimStatusStruct &_value) {
     (void)_value;
     return true;
 }


 const ::v1::GREATWALL::TBOX::TBoxTelephony::TBoxSignalStrengthStruct& TBoxTelephonyStubDefault::getTBoxSignalStrengthAttribute() {
     return tBoxSignalStrengthAttributeValue_;
 }

 const ::v1::GREATWALL::TBOX::TBoxTelephony::TBoxSignalStrengthStruct& TBoxTelephonyStubDefault::getTBoxSignalStrengthAttribute(const std::shared_ptr<CommonAPI::ClientId> _client) {
     (void)_client;
     return getTBoxSignalStrengthAttribute();
 }

 void TBoxTelephonyStubDefault::setTBoxSignalStrengthAttribute(::v1::GREATWALL::TBOX::TBoxTelephony::TBoxSignalStrengthStruct _value) {
     std::shared_ptr<TBoxTelephonyStubAdapter> stubAdapter = CommonAPI::Stub<TBoxTelephonyStubAdapter,
     TBoxTelephonyStubRemoteEvent>::stubAdapter_.lock();
     if(stubAdapter) {
         stubAdapter->lockTBoxSignalStrengthAttribute(true);
         const bool valueChanged = (tBoxSignalStrengthAttributeValue_ != _value);
         if (valueChanged) {
             tBoxSignalStrengthAttributeValue_ = std::move(_value);
             fireTBoxSignalStrengthAttributeChanged(tBoxSignalStrengthAttributeValue_);
         }
         stubAdapter->lockTBoxSignalStrengthAttribute(false);
     } else {
         const bool valueChanged = trySetTBoxSignalStrengthAttribute(std::move(_value));
         if (valueChanged) {
             fireTBoxSignalStrengthAttributeChanged(tBoxSignalStrengthAttributeValue_);
         }
     }
}

 bool TBoxTelephonyStubDefault::trySetTBoxSignalStrengthAttribute(::v1::GREATWALL::TBOX::TBoxTelephony::TBoxSignalStrengthStruct _value) {
     if (!validateTBoxSignalStrengthAttributeRequestedValue(_value))
         return false;

     bool valueChanged;
     std::shared_ptr<TBoxTelephonyStubAdapter> stubAdapter = CommonAPI::Stub<TBoxTelephonyStubAdapter, TBoxTelephonyStubRemoteEvent>::stubAdapter_.lock();
     if(stubAdapter) {
         stubAdapter->lockTBoxSignalStrengthAttribute(true);
         valueChanged = (tBoxSignalStrengthAttributeValue_ != _value);
         tBoxSignalStrengthAttributeValue_ = std::move(_value);
         stubAdapter->lockTBoxSignalStrengthAttribute(false);
     } else {
         valueChanged = (tBoxSignalStrengthAttributeValue_ != _value);
         tBoxSignalStrengthAttributeValue_ = std::move(_value);
     }

     return valueChanged;
 }

 bool TBoxTelephonyStubDefault::validateTBoxSignalStrengthAttributeRequestedValue(const ::v1::GREATWALL::TBOX::TBoxTelephony::TBoxSignalStrengthStruct &_value) {
     (void)_value;
     return true;
 }


 const ::v1::GREATWALL::TBOX::TBoxTelephony::TBoxNetworkProviderStruct& TBoxTelephonyStubDefault::getTBoxNetworkProviderAttribute() {
     return tBoxNetworkProviderAttributeValue_;
 }

 const ::v1::GREATWALL::TBOX::TBoxTelephony::TBoxNetworkProviderStruct& TBoxTelephonyStubDefault::getTBoxNetworkProviderAttribute(const std::shared_ptr<CommonAPI::ClientId> _client) {
     (void)_client;
     return getTBoxNetworkProviderAttribute();
 }

 void TBoxTelephonyStubDefault::setTBoxNetworkProviderAttribute(::v1::GREATWALL::TBOX::TBoxTelephony::TBoxNetworkProviderStruct _value) {
     std::shared_ptr<TBoxTelephonyStubAdapter> stubAdapter = CommonAPI::Stub<TBoxTelephonyStubAdapter,
     TBoxTelephonyStubRemoteEvent>::stubAdapter_.lock();
     if(stubAdapter) {
         stubAdapter->lockTBoxNetworkProviderAttribute(true);
         const bool valueChanged = (tBoxNetworkProviderAttributeValue_ != _value);
         if (valueChanged) {
             tBoxNetworkProviderAttributeValue_ = std::move(_value);
             fireTBoxNetworkProviderAttributeChanged(tBoxNetworkProviderAttributeValue_);
         }
         stubAdapter->lockTBoxNetworkProviderAttribute(false);
     } else {
         const bool valueChanged = trySetTBoxNetworkProviderAttribute(std::move(_value));
         if (valueChanged) {
             fireTBoxNetworkProviderAttributeChanged(tBoxNetworkProviderAttributeValue_);
         }
     }
}

 bool TBoxTelephonyStubDefault::trySetTBoxNetworkProviderAttribute(::v1::GREATWALL::TBOX::TBoxTelephony::TBoxNetworkProviderStruct _value) {
     if (!validateTBoxNetworkProviderAttributeRequestedValue(_value))
         return false;

     bool valueChanged;
     std::shared_ptr<TBoxTelephonyStubAdapter> stubAdapter = CommonAPI::Stub<TBoxTelephonyStubAdapter, TBoxTelephonyStubRemoteEvent>::stubAdapter_.lock();
     if(stubAdapter) {
         stubAdapter->lockTBoxNetworkProviderAttribute(true);
         valueChanged = (tBoxNetworkProviderAttributeValue_ != _value);
         tBoxNetworkProviderAttributeValue_ = std::move(_value);
         stubAdapter->lockTBoxNetworkProviderAttribute(false);
     } else {
         valueChanged = (tBoxNetworkProviderAttributeValue_ != _value);
         tBoxNetworkProviderAttributeValue_ = std::move(_value);
     }

     return valueChanged;
 }

 bool TBoxTelephonyStubDefault::validateTBoxNetworkProviderAttributeRequestedValue(const ::v1::GREATWALL::TBOX::TBoxTelephony::TBoxNetworkProviderStruct &_value) {
     (void)_value;
     return true;
 }



void TBoxTelephonyStubDefault::TBoxCallOperation(const std::shared_ptr<CommonAPI::ClientId> _client, TBoxTelephony::TBoxTelephoneNumber _TBoxTelephoneNumber, TBoxTelephony::TBoxCallType _TBoxCallType, TBoxTelephony::TBoxCallOperation _TBoxCallOperation, TBoxTelephony::long64 _TBoxCallID_In, TBoxCallOperationReply_t _reply) {
    (void)_client;
    (void)_TBoxTelephoneNumber;
    (void)_TBoxCallType;
    (void)_TBoxCallOperation;
    (void)_TBoxCallID_In;
    TBoxTelephony::TBoxResponse TBoxResponse = TBoxTelephony::TBoxResponse::E_ACTIONFAILED;
    TBoxTelephony::long64 TBoxCallID_Out = 0;
    if (!TBoxResponse.validate()) {
        return;
    }
    _reply(TBoxResponse, TBoxCallID_Out);
}

void TBoxTelephonyStubDefault::TBoxSIMInfor(const std::shared_ptr<CommonAPI::ClientId> _client, TBoxSIMInforReply_t _reply) {
    (void)_client;
    TBoxTelephony::ICCID ICCID = "";
    TBoxTelephony::IMEI IMEI = "";
    TBoxTelephony::IMSI IMSI = "";
    _reply(ICCID, IMEI, IMSI);
}

void TBoxTelephonyStubDefault::TBoxStartCall(const std::shared_ptr<CommonAPI::ClientId> _client, TBoxTelephony::TBoxTelephoneNumber _TBoxTelephoneNumber, TBoxTelephony::TBoxCallType _TBoxCallType, TBoxTelephony::long64 _TBoxCallID_In, TBoxStartCallReply_t _reply) {
    (void)_client;
    (void)_TBoxTelephoneNumber;
    (void)_TBoxCallType;
    (void)_TBoxCallID_In;
    TBoxTelephony::TBoxResponse TBoxResponse = TBoxTelephony::TBoxResponse::E_ACTIONFAILED;
    TBoxTelephony::long64 TBoxCallID_Out = 0;
    if (!TBoxResponse.validate()) {
        return;
    }
    _reply(TBoxResponse, TBoxCallID_Out);
}


void TBoxTelephonyStubDefault::fireTBoxCallStateEvent(const ::v1::GREATWALL::TBOX::TBoxTelephony::TBoxTelephoneNumber &_TBoxTelephoneNumber, const ::v1::GREATWALL::TBOX::TBoxTelephony::TBoxCallType &_TBoxCallType, const ::v1::GREATWALL::TBOX::TBoxTelephony::TBoxCallState &_TBoxCallState, const ::v1::GREATWALL::TBOX::TBoxTelephony::long64 &_TBoxCallID) {
    if (!_TBoxCallType.validate()) {
        return;
    }
    if (!_TBoxCallState.validate()) {
        return;
    }
    TBoxTelephonyStub::fireTBoxCallStateEvent(_TBoxTelephoneNumber, _TBoxCallType, _TBoxCallState, _TBoxCallID);
}


TBoxTelephonyStubDefault::RemoteEventHandler::RemoteEventHandler(TBoxTelephonyStubDefault *_defaultStub)
    : 
      defaultStub_(_defaultStub) {
}

} // namespace TBOX
} // namespace GREATWALL
} // namespace v1
