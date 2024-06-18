/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.1.12.v202002200719.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#ifndef V1_GREATWALL_MDC_A_IDC1_5_IDC3_0_HAP_HAV_Pand_AVP_Functions_PROXY_HPP_
#define V1_GREATWALL_MDC_A_IDC1_5_IDC3_0_HAP_HAV_Pand_AVP_Functions_PROXY_HPP_

#include <v1/GREATWALL_MDC_A_IDC1_5_IDC3_0_HAP/HAVPandAVPFunctionsProxyBase.hpp>


#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif


#undef COMMONAPI_INTERNAL_COMPILATION

namespace v1 {
namespace GREATWALL_MDC_A_IDC1_5_IDC3_0_HAP {

template <typename ... _AttributeExtensions>
class HAVPandAVPFunctionsProxy
    : virtual public HAVPandAVPFunctions,
      virtual public HAVPandAVPFunctionsProxyBase,
      virtual public _AttributeExtensions... {
public:
    HAVPandAVPFunctionsProxy(std::shared_ptr<CommonAPI::Proxy> delegate);
    ~HAVPandAVPFunctionsProxy();

    typedef HAVPandAVPFunctions InterfaceType;



    /**
     * Returns the wrapper class that provides access to the broadcast HAVPPathInfo.
     */
    virtual HAVPPathInfoEvent& getHAVPPathInfoEvent() {
        return delegate_->getHAVPPathInfoEvent();
    }
    /**
     * Returns the wrapper class that provides access to the broadcast HAVPRendergInfo.
     */
    virtual HAVPRendergInfoEvent& getHAVPRendergInfoEvent() {
        return delegate_->getHAVPRendergInfoEvent();
    }
    /**
     * Returns the wrapper class that provides access to the broadcast HAVPPathMap.
     */
    virtual HAVPPathMapEvent& getHAVPPathMapEvent() {
        return delegate_->getHAVPPathMapEvent();
    }



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
    std::shared_ptr< HAVPandAVPFunctionsProxyBase> delegate_;
};

typedef HAVPandAVPFunctionsProxy<> HAVPandAVPFunctionsProxyDefault;


//
// HAVPandAVPFunctionsProxy Implementation
//
template <typename ... _AttributeExtensions>
HAVPandAVPFunctionsProxy<_AttributeExtensions...>::HAVPandAVPFunctionsProxy(std::shared_ptr<CommonAPI::Proxy> delegate):
        _AttributeExtensions(*(std::dynamic_pointer_cast< HAVPandAVPFunctionsProxyBase>(delegate)))...,
        delegate_(std::dynamic_pointer_cast< HAVPandAVPFunctionsProxyBase>(delegate)) {
}

template <typename ... _AttributeExtensions>
HAVPandAVPFunctionsProxy<_AttributeExtensions...>::~HAVPandAVPFunctionsProxy() {
}


template <typename ... _AttributeExtensions>
const CommonAPI::Address &HAVPandAVPFunctionsProxy<_AttributeExtensions...>::getAddress() const {
    return delegate_->getAddress();
}

template <typename ... _AttributeExtensions>
bool HAVPandAVPFunctionsProxy<_AttributeExtensions...>::isAvailable() const {
    return delegate_->isAvailable();
}

template <typename ... _AttributeExtensions>
bool HAVPandAVPFunctionsProxy<_AttributeExtensions...>::isAvailableBlocking() const {
    return delegate_->isAvailableBlocking();
}

template <typename ... _AttributeExtensions>
CommonAPI::ProxyStatusEvent& HAVPandAVPFunctionsProxy<_AttributeExtensions...>::getProxyStatusEvent() {
    return delegate_->getProxyStatusEvent();
}

template <typename ... _AttributeExtensions>
CommonAPI::InterfaceVersionAttribute& HAVPandAVPFunctionsProxy<_AttributeExtensions...>::getInterfaceVersionAttribute() {
    return delegate_->getInterfaceVersionAttribute();
}


} // namespace GREATWALL_MDC_A_IDC1_5_IDC3_0_HAP
} // namespace v1



// Compatibility
namespace v1_0 = v1;

#endif // V1_GREATWALL_MDC_A_IDC1_5_IDC3_0_HAP_HAV_Pand_AVP_Functions_PROXY_HPP_