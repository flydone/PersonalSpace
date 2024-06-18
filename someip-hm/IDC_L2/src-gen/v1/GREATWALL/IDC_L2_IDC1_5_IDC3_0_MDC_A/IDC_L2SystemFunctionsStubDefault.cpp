/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.1.12.v202002200719.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#include <v1/GREATWALL/IDC_L2_IDC1_5_IDC3_0_MDC_A/IDC_L2SystemFunctionsStubDefault.hpp>
#include <assert.h>

namespace v1 {
namespace GREATWALL {
namespace IDC_L2_IDC1_5_IDC3_0_MDC_A {

IDC_L2SystemFunctionsStubDefault::IDC_L2SystemFunctionsStubDefault():
        remoteEventHandler_(this),
        interfaceVersion_(IDC_L2SystemFunctions::getInterfaceVersion()) {
}

const CommonAPI::Version& IDC_L2SystemFunctionsStubDefault::getInterfaceVersion(std::shared_ptr<CommonAPI::ClientId> _client) {
    (void)_client;
    return interfaceVersion_;
}

IDC_L2SystemFunctionsStubRemoteEvent* IDC_L2SystemFunctionsStubDefault::initStubAdapter(const std::shared_ptr< IDC_L2SystemFunctionsStubAdapter> &_adapter) {
    CommonAPI::Stub<IDC_L2SystemFunctionsStubAdapter, IDC_L2SystemFunctionsStubRemoteEvent>::stubAdapter_ = _adapter;
    return &remoteEventHandler_;
}

 const ::v1::GREATWALL::IDC_L2_IDC1_5_IDC3_0_MDC_A::IDC_L2SystemFunctions::LocationInfoStruct& IDC_L2SystemFunctionsStubDefault::getLocationInfoDataAttribute() {
     return locationInfoDataAttributeValue_;
 }

 const ::v1::GREATWALL::IDC_L2_IDC1_5_IDC3_0_MDC_A::IDC_L2SystemFunctions::LocationInfoStruct& IDC_L2SystemFunctionsStubDefault::getLocationInfoDataAttribute(const std::shared_ptr<CommonAPI::ClientId> _client) {
     (void)_client;
     return getLocationInfoDataAttribute();
 }

 void IDC_L2SystemFunctionsStubDefault::setLocationInfoDataAttribute(::v1::GREATWALL::IDC_L2_IDC1_5_IDC3_0_MDC_A::IDC_L2SystemFunctions::LocationInfoStruct _value) {
     std::shared_ptr<IDC_L2SystemFunctionsStubAdapter> stubAdapter = CommonAPI::Stub<IDC_L2SystemFunctionsStubAdapter,
     IDC_L2SystemFunctionsStubRemoteEvent>::stubAdapter_.lock();
     if(stubAdapter) {
         stubAdapter->lockLocationInfoDataAttribute(true);
         const bool valueChanged = (locationInfoDataAttributeValue_ != _value);
         if (valueChanged) {
             locationInfoDataAttributeValue_ = std::move(_value);
             fireLocationInfoDataAttributeChanged(locationInfoDataAttributeValue_);
         }
         stubAdapter->lockLocationInfoDataAttribute(false);
     } else {
         const bool valueChanged = trySetLocationInfoDataAttribute(std::move(_value));
         if (valueChanged) {
             fireLocationInfoDataAttributeChanged(locationInfoDataAttributeValue_);
         }
     }
}

 bool IDC_L2SystemFunctionsStubDefault::trySetLocationInfoDataAttribute(::v1::GREATWALL::IDC_L2_IDC1_5_IDC3_0_MDC_A::IDC_L2SystemFunctions::LocationInfoStruct _value) {
     if (!validateLocationInfoDataAttributeRequestedValue(_value))
         return false;

     bool valueChanged;
     std::shared_ptr<IDC_L2SystemFunctionsStubAdapter> stubAdapter = CommonAPI::Stub<IDC_L2SystemFunctionsStubAdapter, IDC_L2SystemFunctionsStubRemoteEvent>::stubAdapter_.lock();
     if(stubAdapter) {
         stubAdapter->lockLocationInfoDataAttribute(true);
         valueChanged = (locationInfoDataAttributeValue_ != _value);
         locationInfoDataAttributeValue_ = std::move(_value);
         stubAdapter->lockLocationInfoDataAttribute(false);
     } else {
         valueChanged = (locationInfoDataAttributeValue_ != _value);
         locationInfoDataAttributeValue_ = std::move(_value);
     }

     return valueChanged;
 }

 bool IDC_L2SystemFunctionsStubDefault::validateLocationInfoDataAttributeRequestedValue(const ::v1::GREATWALL::IDC_L2_IDC1_5_IDC3_0_MDC_A::IDC_L2SystemFunctions::LocationInfoStruct &_value) {
     (void)_value;
     return true;
 }


 const ::v1::GREATWALL::IDC_L2_IDC1_5_IDC3_0_MDC_A::IDC_L2SystemFunctions::OBJPptyInfoStruct& IDC_L2SystemFunctionsStubDefault::getOBJPptyInfoDataAttribute() {
     return oBJPptyInfoDataAttributeValue_;
 }

 const ::v1::GREATWALL::IDC_L2_IDC1_5_IDC3_0_MDC_A::IDC_L2SystemFunctions::OBJPptyInfoStruct& IDC_L2SystemFunctionsStubDefault::getOBJPptyInfoDataAttribute(const std::shared_ptr<CommonAPI::ClientId> _client) {
     (void)_client;
     return getOBJPptyInfoDataAttribute();
 }

 void IDC_L2SystemFunctionsStubDefault::setOBJPptyInfoDataAttribute(::v1::GREATWALL::IDC_L2_IDC1_5_IDC3_0_MDC_A::IDC_L2SystemFunctions::OBJPptyInfoStruct _value) {
     std::shared_ptr<IDC_L2SystemFunctionsStubAdapter> stubAdapter = CommonAPI::Stub<IDC_L2SystemFunctionsStubAdapter,
     IDC_L2SystemFunctionsStubRemoteEvent>::stubAdapter_.lock();
     if(stubAdapter) {
         stubAdapter->lockOBJPptyInfoDataAttribute(true);
         const bool valueChanged = (oBJPptyInfoDataAttributeValue_ != _value);
         if (valueChanged) {
             oBJPptyInfoDataAttributeValue_ = std::move(_value);
             fireOBJPptyInfoDataAttributeChanged(oBJPptyInfoDataAttributeValue_);
         }
         stubAdapter->lockOBJPptyInfoDataAttribute(false);
     } else {
         const bool valueChanged = trySetOBJPptyInfoDataAttribute(std::move(_value));
         if (valueChanged) {
             fireOBJPptyInfoDataAttributeChanged(oBJPptyInfoDataAttributeValue_);
         }
     }
}

 bool IDC_L2SystemFunctionsStubDefault::trySetOBJPptyInfoDataAttribute(::v1::GREATWALL::IDC_L2_IDC1_5_IDC3_0_MDC_A::IDC_L2SystemFunctions::OBJPptyInfoStruct _value) {
     if (!validateOBJPptyInfoDataAttributeRequestedValue(_value))
         return false;

     bool valueChanged;
     std::shared_ptr<IDC_L2SystemFunctionsStubAdapter> stubAdapter = CommonAPI::Stub<IDC_L2SystemFunctionsStubAdapter, IDC_L2SystemFunctionsStubRemoteEvent>::stubAdapter_.lock();
     if(stubAdapter) {
         stubAdapter->lockOBJPptyInfoDataAttribute(true);
         valueChanged = (oBJPptyInfoDataAttributeValue_ != _value);
         oBJPptyInfoDataAttributeValue_ = std::move(_value);
         stubAdapter->lockOBJPptyInfoDataAttribute(false);
     } else {
         valueChanged = (oBJPptyInfoDataAttributeValue_ != _value);
         oBJPptyInfoDataAttributeValue_ = std::move(_value);
     }

     return valueChanged;
 }

 bool IDC_L2SystemFunctionsStubDefault::validateOBJPptyInfoDataAttributeRequestedValue(const ::v1::GREATWALL::IDC_L2_IDC1_5_IDC3_0_MDC_A::IDC_L2SystemFunctions::OBJPptyInfoStruct &_value) {
     (void)_value;
     return true;
 }






IDC_L2SystemFunctionsStubDefault::RemoteEventHandler::RemoteEventHandler(IDC_L2SystemFunctionsStubDefault *_defaultStub)
    : 
      defaultStub_(_defaultStub) {
}

} // namespace IDC_L2_IDC1_5_IDC3_0_MDC_A
} // namespace GREATWALL
} // namespace v1