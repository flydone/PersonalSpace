/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.1.12.v202002200719.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#ifndef V1_GREATWALL_TBOX_T_Box_TSP_Com_PROXY_HPP_
#define V1_GREATWALL_TBOX_T_Box_TSP_Com_PROXY_HPP_

#include <v1/GREATWALL/TBOX/TBoxTSPComProxyBase.hpp>


#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/AttributeExtension.hpp>
#include <CommonAPI/Factory.hpp>

#undef COMMONAPI_INTERNAL_COMPILATION

namespace v1 {
namespace GREATWALL {
namespace TBOX {

template <typename ... _AttributeExtensions>
class TBoxTSPComProxy
    : virtual public TBoxTSPCom,
      virtual public TBoxTSPComProxyBase,
      virtual public _AttributeExtensions... {
public:
    TBoxTSPComProxy(std::shared_ptr<CommonAPI::Proxy> delegate);
    ~TBoxTSPComProxy();

    typedef TBoxTSPCom InterfaceType;


    /**
     * Returns the wrapper class that provides access to the attribute TBoxTSPLoginState.
     */
    virtual TBoxTSPLoginStateAttribute& getTBoxTSPLoginStateAttribute() {
        return delegate_->getTBoxTSPLoginStateAttribute();
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
    std::shared_ptr< TBoxTSPComProxyBase> delegate_;
};

typedef TBoxTSPComProxy<> TBoxTSPComProxyDefault;

namespace TBoxTSPComExtensions {
    template <template <typename > class _ExtensionType>
    class TBoxTSPLoginStateAttributeExtension {
     public:
        typedef _ExtensionType< TBoxTSPComProxyBase::TBoxTSPLoginStateAttribute> extension_type;
    
        static_assert(std::is_base_of<typename CommonAPI::AttributeExtension< TBoxTSPComProxyBase::TBoxTSPLoginStateAttribute>, extension_type>::value,
                      "Not CommonAPI Attribute Extension!");
    
        TBoxTSPLoginStateAttributeExtension(TBoxTSPComProxyBase& proxy): attributeExtension_(proxy.getTBoxTSPLoginStateAttribute()) {
        }
    
        inline extension_type& getTBoxTSPLoginStateAttributeExtension() {
            return attributeExtension_;
        }
    
     private:
        extension_type attributeExtension_;
    };

} // namespace TBoxTSPComExtensions

//
// TBoxTSPComProxy Implementation
//
template <typename ... _AttributeExtensions>
TBoxTSPComProxy<_AttributeExtensions...>::TBoxTSPComProxy(std::shared_ptr<CommonAPI::Proxy> delegate):
        _AttributeExtensions(*(std::dynamic_pointer_cast< TBoxTSPComProxyBase>(delegate)))...,
        delegate_(std::dynamic_pointer_cast< TBoxTSPComProxyBase>(delegate)) {
}

template <typename ... _AttributeExtensions>
TBoxTSPComProxy<_AttributeExtensions...>::~TBoxTSPComProxy() {
}


template <typename ... _AttributeExtensions>
const CommonAPI::Address &TBoxTSPComProxy<_AttributeExtensions...>::getAddress() const {
    return delegate_->getAddress();
}

template <typename ... _AttributeExtensions>
bool TBoxTSPComProxy<_AttributeExtensions...>::isAvailable() const {
    return delegate_->isAvailable();
}

template <typename ... _AttributeExtensions>
bool TBoxTSPComProxy<_AttributeExtensions...>::isAvailableBlocking() const {
    return delegate_->isAvailableBlocking();
}

template <typename ... _AttributeExtensions>
CommonAPI::ProxyStatusEvent& TBoxTSPComProxy<_AttributeExtensions...>::getProxyStatusEvent() {
    return delegate_->getProxyStatusEvent();
}

template <typename ... _AttributeExtensions>
CommonAPI::InterfaceVersionAttribute& TBoxTSPComProxy<_AttributeExtensions...>::getInterfaceVersionAttribute() {
    return delegate_->getInterfaceVersionAttribute();
}


} // namespace TBOX
} // namespace GREATWALL
} // namespace v1

namespace CommonAPI {
template<template<typename > class _AttributeExtension>
struct DefaultAttributeProxyHelper< ::v1::GREATWALL::TBOX::TBoxTSPComProxy,
    _AttributeExtension> {
    typedef typename ::v1::GREATWALL::TBOX::TBoxTSPComProxy<
            ::v1::GREATWALL::TBOX::TBoxTSPComExtensions::TBoxTSPLoginStateAttributeExtension<_AttributeExtension>
    > class_t;
};
}


// Compatibility
namespace v1_0 = v1;

#endif // V1_GREATWALL_TBOX_T_Box_TSP_Com_PROXY_HPP_
