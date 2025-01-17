/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.1.12.v202002200719.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#ifndef V1_GREATWALL_TBOX_T_Box_V2_X_System_Functions_STUB_HPP_
#define V1_GREATWALL_TBOX_T_Box_V2_X_System_Functions_STUB_HPP_

#include <functional>
#include <sstream>




#include <v1/GREATWALL/TBOX/TBoxV2XSystemFunctions.hpp>

#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/InputStream.hpp>
#include <CommonAPI/OutputStream.hpp>
#include <cstdint>
#include <vector>

#include <mutex>

#include <CommonAPI/Stub.hpp>

#undef COMMONAPI_INTERNAL_COMPILATION

namespace v1 {
namespace GREATWALL {
namespace TBOX {

/**
 * Receives messages from remote and handles all dispatching of deserialized calls
 * to a stub for the service TBoxV2XSystemFunctions. Also provides means to send broadcasts
 * and attribute-changed-notifications of observable attributes as defined by this service.
 * An application developer should not need to bother with this class.
 */
class TBoxV2XSystemFunctionsStubAdapter
    : public virtual CommonAPI::StubAdapter,
      public virtual TBoxV2XSystemFunctions {
 public:
    ///Notifies all remote listeners about a change of value of the attribute V2XFunctionStatus.
    virtual void fireV2XFunctionStatusAttributeChanged(const ::v1::GREATWALL::TBOX::TBoxV2XSystemFunctions::V2XStatus& V2XFunctionStatus) = 0;



    virtual void deactivateManagedInstances() = 0;

    void lockV2XFunctionStatusAttribute(bool _lockAccess) {
        if (_lockAccess) {
            v2XFunctionStatusMutex_.lock();
        } else {
            v2XFunctionStatusMutex_.unlock();
        }
    }

protected:
    /**
     * Defines properties for storing the ClientIds of clients / proxies that have
     * subscribed to the selective broadcasts
     */

    std::recursive_mutex v2XFunctionStatusMutex_;
};

/**
 * Defines the necessary callbacks to handle remote set events related to the attributes
 * defined in the IDL description for TBoxV2XSystemFunctions.
 * For each attribute two callbacks are defined:
 * - a verification callback that allows to verify the requested value and to prevent setting
 *   e.g. an invalid value ("onRemoteSet<AttributeName>").
 * - an action callback to do local work after the attribute value has been changed
 *   ("onRemote<AttributeName>Changed").
 *
 * This class and the one below are the ones an application developer needs to have
 * a look at if he wants to implement a service.
 */
class TBoxV2XSystemFunctionsStubRemoteEvent
{
public:
    virtual ~TBoxV2XSystemFunctionsStubRemoteEvent() { }

};

/**
 * Defines the interface that must be implemented by any class that should provide
 * the service TBoxV2XSystemFunctions to remote clients.
 * This class and the one above are the ones an application developer needs to have
 * a look at if he wants to implement a service.
 */
class TBoxV2XSystemFunctionsStub
    : public virtual CommonAPI::Stub<TBoxV2XSystemFunctionsStubAdapter, TBoxV2XSystemFunctionsStubRemoteEvent>
{
public:
    typedef std::function<void (TBoxV2XSystemFunctions::V2XLOCKRespone _V2XLOCKRespone)>V2XLockSwitchReply_t;

    virtual ~TBoxV2XSystemFunctionsStub() {}
    virtual const CommonAPI::Version& getInterfaceVersion(std::shared_ptr<CommonAPI::ClientId> clientId) = 0;
    void lockInterfaceVersionAttribute(bool _lockAccess) { static_cast<void>(_lockAccess); }

    /// Provides getter access to the attribute V2XFunctionStatus
    virtual const ::v1::GREATWALL::TBOX::TBoxV2XSystemFunctions::V2XStatus &getV2XFunctionStatusAttribute(const std::shared_ptr<CommonAPI::ClientId> _client) = 0;
    /// sets attribute with the given value and propagates it to the adapter
    virtual void fireV2XFunctionStatusAttributeChanged(::v1::GREATWALL::TBOX::TBoxV2XSystemFunctions::V2XStatus _value) {
    auto stubAdapter = CommonAPI::Stub<TBoxV2XSystemFunctionsStubAdapter, TBoxV2XSystemFunctionsStubRemoteEvent>::stubAdapter_.lock();
    if (stubAdapter)
        stubAdapter->fireV2XFunctionStatusAttributeChanged(_value);
    }
    void lockV2XFunctionStatusAttribute(bool _lockAccess) {
        auto stubAdapter = CommonAPI::Stub<TBoxV2XSystemFunctionsStubAdapter, TBoxV2XSystemFunctionsStubRemoteEvent>::stubAdapter_.lock();
        if (stubAdapter)
            stubAdapter->lockV2XFunctionStatusAttribute(_lockAccess);
    }

    /// This is the method that will be called on remote calls on the method V2XLockSwitch.
    virtual void V2XLockSwitch(const std::shared_ptr<CommonAPI::ClientId> _client, TBoxV2XSystemFunctions::V2XLOCKRequest _V2XLOCKRequest, V2XLockSwitchReply_t _reply) = 0;

    
    using CommonAPI::Stub<TBoxV2XSystemFunctionsStubAdapter, TBoxV2XSystemFunctionsStubRemoteEvent>::initStubAdapter;
    typedef CommonAPI::Stub<TBoxV2XSystemFunctionsStubAdapter, TBoxV2XSystemFunctionsStubRemoteEvent>::StubAdapterType StubAdapterType;
    typedef CommonAPI::Stub<TBoxV2XSystemFunctionsStubAdapter, TBoxV2XSystemFunctionsStubRemoteEvent>::RemoteEventHandlerType RemoteEventHandlerType;
    typedef TBoxV2XSystemFunctionsStubRemoteEvent RemoteEventType;
    typedef TBoxV2XSystemFunctions StubInterface;
};

} // namespace TBOX
} // namespace GREATWALL
} // namespace v1


// Compatibility
namespace v1_0 = v1;

#endif // V1_GREATWALL_TBOX_T_Box_V2_X_System_Functions_STUB_HPP_
