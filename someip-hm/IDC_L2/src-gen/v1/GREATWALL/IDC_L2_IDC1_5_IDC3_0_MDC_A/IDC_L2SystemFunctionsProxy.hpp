/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.1.12.v202002200719.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#ifndef V1_GREATWALL_IDC_L2_IDC1_5_IDC3_0_MDC_A_IDC__L2_System_Functions_PROXY_HPP_
#define V1_GREATWALL_IDC_L2_IDC1_5_IDC3_0_MDC_A_IDC__L2_System_Functions_PROXY_HPP_

#include <v1/GREATWALL/IDC_L2_IDC1_5_IDC3_0_MDC_A/IDC_L2SystemFunctionsProxyBase.hpp>


#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/AttributeExtension.hpp>
#include <CommonAPI/Factory.hpp>

#undef COMMONAPI_INTERNAL_COMPILATION

namespace v1 {
namespace GREATWALL {
namespace IDC_L2_IDC1_5_IDC3_0_MDC_A {

template <typename ... _AttributeExtensions>
class IDC_L2SystemFunctionsProxy
    : virtual public IDC_L2SystemFunctions,
      virtual public IDC_L2SystemFunctionsProxyBase,
      virtual public _AttributeExtensions... {
public:
    IDC_L2SystemFunctionsProxy(std::shared_ptr<CommonAPI::Proxy> delegate);
    ~IDC_L2SystemFunctionsProxy();

    typedef IDC_L2SystemFunctions InterfaceType;


    /**
     * Returns the wrapper class that provides access to the attribute LocationInfoData.
     */
    virtual LocationInfoDataAttribute& getLocationInfoDataAttribute() {
        return delegate_->getLocationInfoDataAttribute();
    }
    /**
     * Returns the wrapper class that provides access to the attribute OBJPptyInfoData.
     */
    virtual OBJPptyInfoDataAttribute& getOBJPptyInfoDataAttribute() {
        return delegate_->getOBJPptyInfoDataAttribute();
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
    std::shared_ptr< IDC_L2SystemFunctionsProxyBase> delegate_;
};

typedef IDC_L2SystemFunctionsProxy<> IDC_L2SystemFunctionsProxyDefault;

namespace IDC_L2SystemFunctionsExtensions {
    template <template <typename > class _ExtensionType>
    class LocationInfoDataAttributeExtension {
     public:
        typedef _ExtensionType< IDC_L2SystemFunctionsProxyBase::LocationInfoDataAttribute> extension_type;
    
        static_assert(std::is_base_of<typename CommonAPI::AttributeExtension< IDC_L2SystemFunctionsProxyBase::LocationInfoDataAttribute>, extension_type>::value,
                      "Not CommonAPI Attribute Extension!");
    
        LocationInfoDataAttributeExtension(IDC_L2SystemFunctionsProxyBase& proxy): attributeExtension_(proxy.getLocationInfoDataAttribute()) {
        }
    
        inline extension_type& getLocationInfoDataAttributeExtension() {
            return attributeExtension_;
        }
    
     private:
        extension_type attributeExtension_;
    };

    template <template <typename > class _ExtensionType>
    class OBJPptyInfoDataAttributeExtension {
     public:
        typedef _ExtensionType< IDC_L2SystemFunctionsProxyBase::OBJPptyInfoDataAttribute> extension_type;
    
        static_assert(std::is_base_of<typename CommonAPI::AttributeExtension< IDC_L2SystemFunctionsProxyBase::OBJPptyInfoDataAttribute>, extension_type>::value,
                      "Not CommonAPI Attribute Extension!");
    
        OBJPptyInfoDataAttributeExtension(IDC_L2SystemFunctionsProxyBase& proxy): attributeExtension_(proxy.getOBJPptyInfoDataAttribute()) {
        }
    
        inline extension_type& getOBJPptyInfoDataAttributeExtension() {
            return attributeExtension_;
        }
    
     private:
        extension_type attributeExtension_;
    };

} // namespace IDC_L2SystemFunctionsExtensions

//
// IDC_L2SystemFunctionsProxy Implementation
//
template <typename ... _AttributeExtensions>
IDC_L2SystemFunctionsProxy<_AttributeExtensions...>::IDC_L2SystemFunctionsProxy(std::shared_ptr<CommonAPI::Proxy> delegate):
        _AttributeExtensions(*(std::dynamic_pointer_cast< IDC_L2SystemFunctionsProxyBase>(delegate)))...,
        delegate_(std::dynamic_pointer_cast< IDC_L2SystemFunctionsProxyBase>(delegate)) {
}

template <typename ... _AttributeExtensions>
IDC_L2SystemFunctionsProxy<_AttributeExtensions...>::~IDC_L2SystemFunctionsProxy() {
}


template <typename ... _AttributeExtensions>
const CommonAPI::Address &IDC_L2SystemFunctionsProxy<_AttributeExtensions...>::getAddress() const {
    return delegate_->getAddress();
}

template <typename ... _AttributeExtensions>
bool IDC_L2SystemFunctionsProxy<_AttributeExtensions...>::isAvailable() const {
    return delegate_->isAvailable();
}

template <typename ... _AttributeExtensions>
bool IDC_L2SystemFunctionsProxy<_AttributeExtensions...>::isAvailableBlocking() const {
    return delegate_->isAvailableBlocking();
}

template <typename ... _AttributeExtensions>
CommonAPI::ProxyStatusEvent& IDC_L2SystemFunctionsProxy<_AttributeExtensions...>::getProxyStatusEvent() {
    return delegate_->getProxyStatusEvent();
}

template <typename ... _AttributeExtensions>
CommonAPI::InterfaceVersionAttribute& IDC_L2SystemFunctionsProxy<_AttributeExtensions...>::getInterfaceVersionAttribute() {
    return delegate_->getInterfaceVersionAttribute();
}


} // namespace IDC_L2_IDC1_5_IDC3_0_MDC_A
} // namespace GREATWALL
} // namespace v1

namespace CommonAPI {
template<template<typename > class _AttributeExtension>
struct DefaultAttributeProxyHelper< ::v1::GREATWALL::IDC_L2_IDC1_5_IDC3_0_MDC_A::IDC_L2SystemFunctionsProxy,
    _AttributeExtension> {
    typedef typename ::v1::GREATWALL::IDC_L2_IDC1_5_IDC3_0_MDC_A::IDC_L2SystemFunctionsProxy<
            ::v1::GREATWALL::IDC_L2_IDC1_5_IDC3_0_MDC_A::IDC_L2SystemFunctionsExtensions::LocationInfoDataAttributeExtension<_AttributeExtension>, 
            ::v1::GREATWALL::IDC_L2_IDC1_5_IDC3_0_MDC_A::IDC_L2SystemFunctionsExtensions::OBJPptyInfoDataAttributeExtension<_AttributeExtension>
    > class_t;
};
}


// Compatibility
namespace v1_0 = v1;

#endif // V1_GREATWALL_IDC_L2_IDC1_5_IDC3_0_MDC_A_IDC__L2_System_Functions_PROXY_HPP_
