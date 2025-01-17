/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.1.12.v202002200719.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#ifndef V1_GREATWALL_IDC1_5_IDC1_5_System_Functions_PROXY_HPP_
#define V1_GREATWALL_IDC1_5_IDC1_5_System_Functions_PROXY_HPP_

#include <v1/GREATWALL/IDC1_5/IDC1_5SystemFunctionsProxyBase.hpp>


#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif


#undef COMMONAPI_INTERNAL_COMPILATION

namespace v1 {
namespace GREATWALL {
namespace IDC1_5 {

template <typename ... _AttributeExtensions>
class IDC1_5SystemFunctionsProxy
    : virtual public IDC1_5SystemFunctions,
      virtual public IDC1_5SystemFunctionsProxyBase,
      virtual public _AttributeExtensions... {
public:
    IDC1_5SystemFunctionsProxy(std::shared_ptr<CommonAPI::Proxy> delegate);
    ~IDC1_5SystemFunctionsProxy();

    typedef IDC1_5SystemFunctions InterfaceType;



    /**
     * Returns the wrapper class that provides access to the broadcast VideoUpload.
     */
    virtual VideoUploadEvent& getVideoUploadEvent() {
        return delegate_->getVideoUploadEvent();
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
    std::shared_ptr< IDC1_5SystemFunctionsProxyBase> delegate_;
};

typedef IDC1_5SystemFunctionsProxy<> IDC1_5SystemFunctionsProxyDefault;


//
// IDC1_5SystemFunctionsProxy Implementation
//
template <typename ... _AttributeExtensions>
IDC1_5SystemFunctionsProxy<_AttributeExtensions...>::IDC1_5SystemFunctionsProxy(std::shared_ptr<CommonAPI::Proxy> delegate):
        _AttributeExtensions(*(std::dynamic_pointer_cast< IDC1_5SystemFunctionsProxyBase>(delegate)))...,
        delegate_(std::dynamic_pointer_cast< IDC1_5SystemFunctionsProxyBase>(delegate)) {
}

template <typename ... _AttributeExtensions>
IDC1_5SystemFunctionsProxy<_AttributeExtensions...>::~IDC1_5SystemFunctionsProxy() {
}


template <typename ... _AttributeExtensions>
const CommonAPI::Address &IDC1_5SystemFunctionsProxy<_AttributeExtensions...>::getAddress() const {
    return delegate_->getAddress();
}

template <typename ... _AttributeExtensions>
bool IDC1_5SystemFunctionsProxy<_AttributeExtensions...>::isAvailable() const {
    return delegate_->isAvailable();
}

template <typename ... _AttributeExtensions>
bool IDC1_5SystemFunctionsProxy<_AttributeExtensions...>::isAvailableBlocking() const {
    return delegate_->isAvailableBlocking();
}

template <typename ... _AttributeExtensions>
CommonAPI::ProxyStatusEvent& IDC1_5SystemFunctionsProxy<_AttributeExtensions...>::getProxyStatusEvent() {
    return delegate_->getProxyStatusEvent();
}

template <typename ... _AttributeExtensions>
CommonAPI::InterfaceVersionAttribute& IDC1_5SystemFunctionsProxy<_AttributeExtensions...>::getInterfaceVersionAttribute() {
    return delegate_->getInterfaceVersionAttribute();
}


} // namespace IDC1_5
} // namespace GREATWALL
} // namespace v1



// Compatibility
namespace v1_0 = v1;

#endif // V1_GREATWALL_IDC1_5_IDC1_5_System_Functions_PROXY_HPP_
