/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.1.12.v202002200719.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#ifndef V1_GREATWALL_DVR_VIMS_DVR_System_Config_PROXY_BASE_HPP_
#define V1_GREATWALL_DVR_VIMS_DVR_System_Config_PROXY_BASE_HPP_

#include <v1/GREATWALL/DVR_VIMS/DVRSystemConfig.hpp>



#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/InputStream.hpp>
#include <CommonAPI/OutputStream.hpp>
#include <cstdint>
#include <vector>

#include <CommonAPI/Proxy.hpp>
#include <functional>
#include <future>

#undef COMMONAPI_INTERNAL_COMPILATION

namespace v1 {
namespace GREATWALL {
namespace DVR_VIMS {

class DVRSystemConfigProxyBase
    : virtual public CommonAPI::Proxy {
public:

    typedef std::function<void(const CommonAPI::CallStatus&, const DVRSystemConfig::SetResult&)> ResetDefaultConfigAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const DVRSystemConfig::ConfigListArray&)> DVRGetConfigAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const DVRSystemConfig::SetResult&)> DVRSetConfigAsyncCallback;



    virtual void ResetDefaultConfig(const DVRSystemConfig::ResetConfigType &_ResetConfigType, CommonAPI::CallStatus &_internalCallStatus, DVRSystemConfig::SetResult &_ResetConfigACK, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> ResetDefaultConfigAsync(const DVRSystemConfig::ResetConfigType &_ResetConfigType, ResetDefaultConfigAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual void DVRGetConfig(const DVRSystemConfig::GetAllConfig &_GetAllConfig, const DVRSystemConfig::ConfigTypeList &_ConfigTypeList, CommonAPI::CallStatus &_internalCallStatus, DVRSystemConfig::ConfigListArray &_ConfigListArray, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> DVRGetConfigAsync(const DVRSystemConfig::GetAllConfig &_GetAllConfig, const DVRSystemConfig::ConfigTypeList &_ConfigTypeList, DVRGetConfigAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual void DVRSetConfig(const DVRSystemConfig::ConfigListArray &_ConfigListArray, CommonAPI::CallStatus &_internalCallStatus, DVRSystemConfig::SetResult &_ParamConfigResult, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> DVRSetConfigAsync(const DVRSystemConfig::ConfigListArray &_ConfigListArray, DVRSetConfigAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
};

} // namespace DVR_VIMS
} // namespace GREATWALL
} // namespace v1


// Compatibility
namespace v1_0 = v1;

#endif // V1_GREATWALL_DVR_VIMS_DVR_System_Config_PROXY_BASE_HPP_