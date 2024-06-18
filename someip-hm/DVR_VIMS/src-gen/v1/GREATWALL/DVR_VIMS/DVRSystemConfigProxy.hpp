/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.1.12.v202002200719.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#ifndef V1_GREATWALL_DVR_VIMS_DVR_System_Config_PROXY_HPP_
#define V1_GREATWALL_DVR_VIMS_DVR_System_Config_PROXY_HPP_

#include <v1/GREATWALL/DVR_VIMS/DVRSystemConfigProxyBase.hpp>


#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif


#undef COMMONAPI_INTERNAL_COMPILATION

namespace v1 {
namespace GREATWALL {
namespace DVR_VIMS {

template <typename ... _AttributeExtensions>
class DVRSystemConfigProxy
    : virtual public DVRSystemConfig,
      virtual public DVRSystemConfigProxyBase,
      virtual public _AttributeExtensions... {
public:
    DVRSystemConfigProxy(std::shared_ptr<CommonAPI::Proxy> delegate);
    ~DVRSystemConfigProxy();

    typedef DVRSystemConfig InterfaceType;




    /**
     * Calls ResetDefaultConfig with synchronous semantics.
     *
    * All const parameters are input parameters to this method.
    * All non-const parameters will be filled with the returned values.
     * The CallStatus will be filled when the method returns and indicate either
     * "SUCCESS" or which type of error has occurred. In case of an error, ONLY the CallStatus
     * will be set.
     */
    virtual void ResetDefaultConfig(const DVRSystemConfig::ResetConfigType &_ResetConfigType, CommonAPI::CallStatus &_internalCallStatus, DVRSystemConfig::SetResult &_ResetConfigACK, const CommonAPI::CallInfo *_info = nullptr);
    /**
     * Calls ResetDefaultConfig with asynchronous semantics.
     *
     * The provided callback will be called when the reply to this call arrives or
     * an error occurs during the call. The CallStatus will indicate either "SUCCESS"
     * or which type of error has occurred. In case of any error, ONLY the CallStatus
     * will have a defined value.
     * The std::future returned by this method will be fulfilled at arrival of the reply.
     * It will provide the same value for CallStatus as will be handed to the callback.
     */
    virtual std::future<CommonAPI::CallStatus> ResetDefaultConfigAsync(const DVRSystemConfig::ResetConfigType &_ResetConfigType, ResetDefaultConfigAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr);
    /**
     * Calls DVRGetConfig with synchronous semantics.
     *
    * All const parameters are input parameters to this method.
    * All non-const parameters will be filled with the returned values.
     * The CallStatus will be filled when the method returns and indicate either
     * "SUCCESS" or which type of error has occurred. In case of an error, ONLY the CallStatus
     * will be set.
     */
    virtual void DVRGetConfig(const DVRSystemConfig::GetAllConfig &_GetAllConfig, const DVRSystemConfig::ConfigTypeList &_ConfigTypeList, CommonAPI::CallStatus &_internalCallStatus, DVRSystemConfig::ConfigListArray &_ConfigListArray, const CommonAPI::CallInfo *_info = nullptr);
    /**
     * Calls DVRGetConfig with asynchronous semantics.
     *
     * The provided callback will be called when the reply to this call arrives or
     * an error occurs during the call. The CallStatus will indicate either "SUCCESS"
     * or which type of error has occurred. In case of any error, ONLY the CallStatus
     * will have a defined value.
     * The std::future returned by this method will be fulfilled at arrival of the reply.
     * It will provide the same value for CallStatus as will be handed to the callback.
     */
    virtual std::future<CommonAPI::CallStatus> DVRGetConfigAsync(const DVRSystemConfig::GetAllConfig &_GetAllConfig, const DVRSystemConfig::ConfigTypeList &_ConfigTypeList, DVRGetConfigAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr);
    /**
     * Calls DVRSetConfig with synchronous semantics.
     *
    * All const parameters are input parameters to this method.
    * All non-const parameters will be filled with the returned values.
     * The CallStatus will be filled when the method returns and indicate either
     * "SUCCESS" or which type of error has occurred. In case of an error, ONLY the CallStatus
     * will be set.
     */
    virtual void DVRSetConfig(const DVRSystemConfig::ConfigListArray &_ConfigListArray, CommonAPI::CallStatus &_internalCallStatus, DVRSystemConfig::SetResult &_ParamConfigResult, const CommonAPI::CallInfo *_info = nullptr);
    /**
     * Calls DVRSetConfig with asynchronous semantics.
     *
     * The provided callback will be called when the reply to this call arrives or
     * an error occurs during the call. The CallStatus will indicate either "SUCCESS"
     * or which type of error has occurred. In case of any error, ONLY the CallStatus
     * will have a defined value.
     * The std::future returned by this method will be fulfilled at arrival of the reply.
     * It will provide the same value for CallStatus as will be handed to the callback.
     */
    virtual std::future<CommonAPI::CallStatus> DVRSetConfigAsync(const DVRSystemConfig::ConfigListArray &_ConfigListArray, DVRSetConfigAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr);


    /**
     * Returns the CommonAPI address of the remote partner this proxy communicates with.
     */
    virtual const CommonAPI::Address &getAddress() const;

    /**
     * Returns true if the remote partner for this proxy is currently known to be available.
     */
    virtual bool isAvailable() const;

    /**
     * Returns true if the remote partner for this proxy is available.
     */
    virtual bool isAvailableBlocking() const;

    /**
     * Returns the wrapper class that is used to (de-)register for notifications about
     * the availability of the remote partner of this proxy.
     */
    virtual CommonAPI::ProxyStatusEvent& getProxyStatusEvent();

    /**
     * Returns the wrapper class that is used to access version information of the remote
     * partner of this proxy.
     */
    virtual CommonAPI::InterfaceVersionAttribute& getInterfaceVersionAttribute();

 private:
    std::shared_ptr< DVRSystemConfigProxyBase> delegate_;
};

typedef DVRSystemConfigProxy<> DVRSystemConfigProxyDefault;


//
// DVRSystemConfigProxy Implementation
//
template <typename ... _AttributeExtensions>
DVRSystemConfigProxy<_AttributeExtensions...>::DVRSystemConfigProxy(std::shared_ptr<CommonAPI::Proxy> delegate):
        _AttributeExtensions(*(std::dynamic_pointer_cast< DVRSystemConfigProxyBase>(delegate)))...,
        delegate_(std::dynamic_pointer_cast< DVRSystemConfigProxyBase>(delegate)) {
}

template <typename ... _AttributeExtensions>
DVRSystemConfigProxy<_AttributeExtensions...>::~DVRSystemConfigProxy() {
}

template <typename ... _AttributeExtensions>
void DVRSystemConfigProxy<_AttributeExtensions...>::ResetDefaultConfig(const DVRSystemConfig::ResetConfigType &_ResetConfigType, CommonAPI::CallStatus &_internalCallStatus, DVRSystemConfig::SetResult &_ResetConfigACK, const CommonAPI::CallInfo *_info) {
    if (!_ResetConfigType.validate()) {
        _internalCallStatus = CommonAPI::CallStatus::INVALID_VALUE;
        return;
    }
    delegate_->ResetDefaultConfig(_ResetConfigType, _internalCallStatus, _ResetConfigACK, _info);
}

template <typename ... _AttributeExtensions>
std::future<CommonAPI::CallStatus> DVRSystemConfigProxy<_AttributeExtensions...>::ResetDefaultConfigAsync(const DVRSystemConfig::ResetConfigType &_ResetConfigType, ResetDefaultConfigAsyncCallback _callback, const CommonAPI::CallInfo *_info) {
    if (!_ResetConfigType.validate()) {
        DVRSystemConfig::SetResult ResetConfigACK = DVRSystemConfig::SetResult::E_SUCCESSFUL;
        _callback(CommonAPI::CallStatus::INVALID_VALUE, ResetConfigACK);
        std::promise<CommonAPI::CallStatus> promise;
        promise.set_value(CommonAPI::CallStatus::INVALID_VALUE);
        return promise.get_future();
    }
    return delegate_->ResetDefaultConfigAsync(_ResetConfigType, _callback, _info);
}
template <typename ... _AttributeExtensions>
void DVRSystemConfigProxy<_AttributeExtensions...>::DVRGetConfig(const DVRSystemConfig::GetAllConfig &_GetAllConfig, const DVRSystemConfig::ConfigTypeList &_ConfigTypeList, CommonAPI::CallStatus &_internalCallStatus, DVRSystemConfig::ConfigListArray &_ConfigListArray, const CommonAPI::CallInfo *_info) {
    if (!_GetAllConfig.validate()) {
        _internalCallStatus = CommonAPI::CallStatus::INVALID_VALUE;
        return;
    }
    delegate_->DVRGetConfig(_GetAllConfig, _ConfigTypeList, _internalCallStatus, _ConfigListArray, _info);
}

template <typename ... _AttributeExtensions>
std::future<CommonAPI::CallStatus> DVRSystemConfigProxy<_AttributeExtensions...>::DVRGetConfigAsync(const DVRSystemConfig::GetAllConfig &_GetAllConfig, const DVRSystemConfig::ConfigTypeList &_ConfigTypeList, DVRGetConfigAsyncCallback _callback, const CommonAPI::CallInfo *_info) {
    if (!_GetAllConfig.validate()) {
        DVRSystemConfig::ConfigListArray ConfigListArray = {};
        _callback(CommonAPI::CallStatus::INVALID_VALUE, ConfigListArray);
        std::promise<CommonAPI::CallStatus> promise;
        promise.set_value(CommonAPI::CallStatus::INVALID_VALUE);
        return promise.get_future();
    }
    return delegate_->DVRGetConfigAsync(_GetAllConfig, _ConfigTypeList, _callback, _info);
}
template <typename ... _AttributeExtensions>
void DVRSystemConfigProxy<_AttributeExtensions...>::DVRSetConfig(const DVRSystemConfig::ConfigListArray &_ConfigListArray, CommonAPI::CallStatus &_internalCallStatus, DVRSystemConfig::SetResult &_ParamConfigResult, const CommonAPI::CallInfo *_info) {
    delegate_->DVRSetConfig(_ConfigListArray, _internalCallStatus, _ParamConfigResult, _info);
}

template <typename ... _AttributeExtensions>
std::future<CommonAPI::CallStatus> DVRSystemConfigProxy<_AttributeExtensions...>::DVRSetConfigAsync(const DVRSystemConfig::ConfigListArray &_ConfigListArray, DVRSetConfigAsyncCallback _callback, const CommonAPI::CallInfo *_info) {
    return delegate_->DVRSetConfigAsync(_ConfigListArray, _callback, _info);
}

template <typename ... _AttributeExtensions>
const CommonAPI::Address &DVRSystemConfigProxy<_AttributeExtensions...>::getAddress() const {
    return delegate_->getAddress();
}

template <typename ... _AttributeExtensions>
bool DVRSystemConfigProxy<_AttributeExtensions...>::isAvailable() const {
    return delegate_->isAvailable();
}

template <typename ... _AttributeExtensions>
bool DVRSystemConfigProxy<_AttributeExtensions...>::isAvailableBlocking() const {
    return delegate_->isAvailableBlocking();
}

template <typename ... _AttributeExtensions>
CommonAPI::ProxyStatusEvent& DVRSystemConfigProxy<_AttributeExtensions...>::getProxyStatusEvent() {
    return delegate_->getProxyStatusEvent();
}

template <typename ... _AttributeExtensions>
CommonAPI::InterfaceVersionAttribute& DVRSystemConfigProxy<_AttributeExtensions...>::getInterfaceVersionAttribute() {
    return delegate_->getInterfaceVersionAttribute();
}


} // namespace DVR_VIMS
} // namespace GREATWALL
} // namespace v1



// Compatibility
namespace v1_0 = v1;

#endif // V1_GREATWALL_DVR_VIMS_DVR_System_Config_PROXY_HPP_