/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.1.12.v202002200719.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#include <v1/GREATWALL/DVR_VIMS/DVRSystemConfigStubDefault.hpp>
#include <assert.h>

namespace v1 {
namespace GREATWALL {
namespace DVR_VIMS {

DVRSystemConfigStubDefault::DVRSystemConfigStubDefault():
        remoteEventHandler_(this),
        interfaceVersion_(DVRSystemConfig::getInterfaceVersion()) {
}

const CommonAPI::Version& DVRSystemConfigStubDefault::getInterfaceVersion(std::shared_ptr<CommonAPI::ClientId> _client) {
    (void)_client;
    return interfaceVersion_;
}

DVRSystemConfigStubRemoteEvent* DVRSystemConfigStubDefault::initStubAdapter(const std::shared_ptr< DVRSystemConfigStubAdapter> &_adapter) {
    CommonAPI::Stub<DVRSystemConfigStubAdapter, DVRSystemConfigStubRemoteEvent>::stubAdapter_ = _adapter;
    return &remoteEventHandler_;
}


void DVRSystemConfigStubDefault::ResetDefaultConfig(const std::shared_ptr<CommonAPI::ClientId> _client, DVRSystemConfig::ResetConfigType _ResetConfigType, ResetDefaultConfigReply_t _reply) {
    (void)_client;
    (void)_ResetConfigType;
    DVRSystemConfig::SetResult ResetConfigACK = DVRSystemConfig::SetResult::E_SUCCESSFUL;
    if (!ResetConfigACK.validate()) {
        return;
    }
    _reply(ResetConfigACK);
}

void DVRSystemConfigStubDefault::DVRGetConfig(const std::shared_ptr<CommonAPI::ClientId> _client, DVRSystemConfig::GetAllConfig _GetAllConfig, DVRSystemConfig::ConfigTypeList _ConfigTypeList, DVRGetConfigReply_t _reply) {
    (void)_client;
    (void)_GetAllConfig;
    (void)_ConfigTypeList;
    DVRSystemConfig::ConfigListArray ConfigListArray = {};
    _reply(ConfigListArray);
}

void DVRSystemConfigStubDefault::DVRSetConfig(const std::shared_ptr<CommonAPI::ClientId> _client, DVRSystemConfig::ConfigListArray _ConfigListArray, DVRSetConfigReply_t _reply) {
    (void)_client;
    (void)_ConfigListArray;
    DVRSystemConfig::SetResult ParamConfigResult = DVRSystemConfig::SetResult::E_SUCCESSFUL;
    if (!ParamConfigResult.validate()) {
        return;
    }
    _reply(ParamConfigResult);
}




DVRSystemConfigStubDefault::RemoteEventHandler::RemoteEventHandler(DVRSystemConfigStubDefault *_defaultStub)
    : 
      defaultStub_(_defaultStub) {
}

} // namespace DVR_VIMS
} // namespace GREATWALL
} // namespace v1
