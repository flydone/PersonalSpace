/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.1.12.v202002200719.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#ifndef V1_GREATWALL_TBOX_SPE_Location_5_G_STUB_HPP_
#define V1_GREATWALL_TBOX_SPE_Location_5_G_STUB_HPP_

#include <functional>
#include <sstream>




#include <v1/GREATWALL/TBOX/SPELocation_5G.hpp>

#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/Deployment.hpp>
#include <CommonAPI/InputStream.hpp>
#include <CommonAPI/OutputStream.hpp>
#include <CommonAPI/Struct.hpp>
#include <cstdint>

#include <mutex>

#include <CommonAPI/Stub.hpp>

#undef COMMONAPI_INTERNAL_COMPILATION

namespace v1 {
namespace GREATWALL {
namespace TBOX {

/**
 * Receives messages from remote and handles all dispatching of deserialized calls
 * to a stub for the service SPELocation_5G. Also provides means to send broadcasts
 * and attribute-changed-notifications of observable attributes as defined by this service.
 * An application developer should not need to bother with this class.
 */
class SPELocation_5GStubAdapter
    : public virtual CommonAPI::StubAdapter,
      public virtual SPELocation_5G {
 public:
    ///Notifies all remote listeners about a change of value of the attribute NtfSPELocation.
    virtual void fireNtfSPELocationAttributeChanged(const ::v1::GREATWALL::TBOX::SPELocation_5G::SPELocationStruct& NtfSPELocation) = 0;



    virtual void deactivateManagedInstances() = 0;

    void lockNtfSPELocationAttribute(bool _lockAccess) {
        if (_lockAccess) {
            ntfSPELocationMutex_.lock();
        } else {
            ntfSPELocationMutex_.unlock();
        }
    }

protected:
    /**
     * Defines properties for storing the ClientIds of clients / proxies that have
     * subscribed to the selective broadcasts
     */

    std::recursive_mutex ntfSPELocationMutex_;
};

/**
 * Defines the necessary callbacks to handle remote set events related to the attributes
 * defined in the IDL description for SPELocation_5G.
 * For each attribute two callbacks are defined:
 * - a verification callback that allows to verify the requested value and to prevent setting
 *   e.g. an invalid value ("onRemoteSet<AttributeName>").
 * - an action callback to do local work after the attribute value has been changed
 *   ("onRemote<AttributeName>Changed").
 *
 * This class and the one below are the ones an application developer needs to have
 * a look at if he wants to implement a service.
 */
class SPELocation_5GStubRemoteEvent
{
public:
    virtual ~SPELocation_5GStubRemoteEvent() { }

};

/**
 * Defines the interface that must be implemented by any class that should provide
 * the service SPELocation_5G to remote clients.
 * This class and the one above are the ones an application developer needs to have
 * a look at if he wants to implement a service.
 */
class SPELocation_5GStub
    : public virtual CommonAPI::Stub<SPELocation_5GStubAdapter, SPELocation_5GStubRemoteEvent>
{
public:

    virtual ~SPELocation_5GStub() {}
    virtual const CommonAPI::Version& getInterfaceVersion(std::shared_ptr<CommonAPI::ClientId> clientId) = 0;
    void lockInterfaceVersionAttribute(bool _lockAccess) { static_cast<void>(_lockAccess); }

    /// Provides getter access to the attribute NtfSPELocation
    virtual const ::v1::GREATWALL::TBOX::SPELocation_5G::SPELocationStruct &getNtfSPELocationAttribute(const std::shared_ptr<CommonAPI::ClientId> _client) = 0;
    /// sets attribute with the given value and propagates it to the adapter
    virtual void fireNtfSPELocationAttributeChanged(::v1::GREATWALL::TBOX::SPELocation_5G::SPELocationStruct _value) {
    auto stubAdapter = CommonAPI::Stub<SPELocation_5GStubAdapter, SPELocation_5GStubRemoteEvent>::stubAdapter_.lock();
    if (stubAdapter)
        stubAdapter->fireNtfSPELocationAttributeChanged(_value);
    }
    void lockNtfSPELocationAttribute(bool _lockAccess) {
        auto stubAdapter = CommonAPI::Stub<SPELocation_5GStubAdapter, SPELocation_5GStubRemoteEvent>::stubAdapter_.lock();
        if (stubAdapter)
            stubAdapter->lockNtfSPELocationAttribute(_lockAccess);
    }


    
    using CommonAPI::Stub<SPELocation_5GStubAdapter, SPELocation_5GStubRemoteEvent>::initStubAdapter;
    typedef CommonAPI::Stub<SPELocation_5GStubAdapter, SPELocation_5GStubRemoteEvent>::StubAdapterType StubAdapterType;
    typedef CommonAPI::Stub<SPELocation_5GStubAdapter, SPELocation_5GStubRemoteEvent>::RemoteEventHandlerType RemoteEventHandlerType;
    typedef SPELocation_5GStubRemoteEvent RemoteEventType;
    typedef SPELocation_5G StubInterface;
};

} // namespace TBOX
} // namespace GREATWALL
} // namespace v1


// Compatibility
namespace v1_0 = v1;

#endif // V1_GREATWALL_TBOX_SPE_Location_5_G_STUB_HPP_