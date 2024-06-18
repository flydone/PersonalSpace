/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.1.12.v202002200719.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#ifndef V1_GREATWALL_TBOX_T_Box_System_Functions_STUB_HPP_
#define V1_GREATWALL_TBOX_T_Box_System_Functions_STUB_HPP_

#include <functional>
#include <sstream>




#include <v1/GREATWALL/TBOX/TBoxSystemFunctions.hpp>

#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <string>

#include <mutex>

#include <CommonAPI/Stub.hpp>

#undef COMMONAPI_INTERNAL_COMPILATION

namespace v1 {
namespace GREATWALL {
namespace TBOX {

/**
 * Receives messages from remote and handles all dispatching of deserialized calls
 * to a stub for the service TBoxSystemFunctions. Also provides means to send broadcasts
 * and attribute-changed-notifications of observable attributes as defined by this service.
 * An application developer should not need to bother with this class.
 */
class TBoxSystemFunctionsStubAdapter
    : public virtual CommonAPI::StubAdapter,
      public virtual TBoxSystemFunctions {
 public:
    ///Notifies all remote listeners about a change of value of the attribute GPSData.
    virtual void fireGPSDataAttributeChanged(const ::v1::GREATWALL::TBOX::TBoxSystemFunctions::GPSRawData& GPSData) = 0;



    virtual void deactivateManagedInstances() = 0;

    void lockGPSDataAttribute(bool _lockAccess) {
        if (_lockAccess) {
            gPSDataMutex_.lock();
        } else {
            gPSDataMutex_.unlock();
        }
    }

protected:
    /**
     * Defines properties for storing the ClientIds of clients / proxies that have
     * subscribed to the selective broadcasts
     */

    std::recursive_mutex gPSDataMutex_;
};

/**
 * Defines the necessary callbacks to handle remote set events related to the attributes
 * defined in the IDL description for TBoxSystemFunctions.
 * For each attribute two callbacks are defined:
 * - a verification callback that allows to verify the requested value and to prevent setting
 *   e.g. an invalid value ("onRemoteSet<AttributeName>").
 * - an action callback to do local work after the attribute value has been changed
 *   ("onRemote<AttributeName>Changed").
 *
 * This class and the one below are the ones an application developer needs to have
 * a look at if he wants to implement a service.
 */
class TBoxSystemFunctionsStubRemoteEvent
{
public:
    virtual ~TBoxSystemFunctionsStubRemoteEvent() { }

};

/**
 * Defines the interface that must be implemented by any class that should provide
 * the service TBoxSystemFunctions to remote clients.
 * This class and the one above are the ones an application developer needs to have
 * a look at if he wants to implement a service.
 */
class TBoxSystemFunctionsStub
    : public virtual CommonAPI::Stub<TBoxSystemFunctionsStubAdapter, TBoxSystemFunctionsStubRemoteEvent>
{
public:

    virtual ~TBoxSystemFunctionsStub() {}
    virtual const CommonAPI::Version& getInterfaceVersion(std::shared_ptr<CommonAPI::ClientId> clientId) = 0;
    void lockInterfaceVersionAttribute(bool _lockAccess) { static_cast<void>(_lockAccess); }

    /// Provides getter access to the attribute GPSData
    virtual const ::v1::GREATWALL::TBOX::TBoxSystemFunctions::GPSRawData &getGPSDataAttribute(const std::shared_ptr<CommonAPI::ClientId> _client) = 0;
    /// sets attribute with the given value and propagates it to the adapter
    virtual void fireGPSDataAttributeChanged(::v1::GREATWALL::TBOX::TBoxSystemFunctions::GPSRawData _value) {
    auto stubAdapter = CommonAPI::Stub<TBoxSystemFunctionsStubAdapter, TBoxSystemFunctionsStubRemoteEvent>::stubAdapter_.lock();
    if (stubAdapter)
        stubAdapter->fireGPSDataAttributeChanged(_value);
    }
    void lockGPSDataAttribute(bool _lockAccess) {
        auto stubAdapter = CommonAPI::Stub<TBoxSystemFunctionsStubAdapter, TBoxSystemFunctionsStubRemoteEvent>::stubAdapter_.lock();
        if (stubAdapter)
            stubAdapter->lockGPSDataAttribute(_lockAccess);
    }


    
    using CommonAPI::Stub<TBoxSystemFunctionsStubAdapter, TBoxSystemFunctionsStubRemoteEvent>::initStubAdapter;
    typedef CommonAPI::Stub<TBoxSystemFunctionsStubAdapter, TBoxSystemFunctionsStubRemoteEvent>::StubAdapterType StubAdapterType;
    typedef CommonAPI::Stub<TBoxSystemFunctionsStubAdapter, TBoxSystemFunctionsStubRemoteEvent>::RemoteEventHandlerType RemoteEventHandlerType;
    typedef TBoxSystemFunctionsStubRemoteEvent RemoteEventType;
    typedef TBoxSystemFunctions StubInterface;
};

} // namespace TBOX
} // namespace GREATWALL
} // namespace v1


// Compatibility
namespace v1_0 = v1;

#endif // V1_GREATWALL_TBOX_T_Box_System_Functions_STUB_HPP_