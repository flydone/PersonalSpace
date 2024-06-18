/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.1.12.v202002200719.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#ifndef V1_GREATWALL_TBOX_T_Box_Telephony_STUB_HPP_
#define V1_GREATWALL_TBOX_T_Box_Telephony_STUB_HPP_

#include <functional>
#include <sstream>




#include <v1/GREATWALL/TBOX/TBoxTelephony.hpp>

#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/Deployment.hpp>
#include <CommonAPI/InputStream.hpp>
#include <CommonAPI/OutputStream.hpp>
#include <CommonAPI/Struct.hpp>
#include <cstdint>
#include <string>
#include <unordered_set>
#include <vector>

#include <mutex>

#include <CommonAPI/Stub.hpp>

#undef COMMONAPI_INTERNAL_COMPILATION

namespace v1 {
namespace GREATWALL {
namespace TBOX {

/**
 * Receives messages from remote and handles all dispatching of deserialized calls
 * to a stub for the service TBoxTelephony. Also provides means to send broadcasts
 * and attribute-changed-notifications of observable attributes as defined by this service.
 * An application developer should not need to bother with this class.
 */
class TBoxTelephonyStubAdapter
    : public virtual CommonAPI::StubAdapter,
      public virtual TBoxTelephony {
 public:
    ///Notifies all remote listeners about a change of value of the attribute TBoxSimStatus.
    virtual void fireTBoxSimStatusAttributeChanged(const ::v1::GREATWALL::TBOX::TBoxTelephony::TBoxSimStatusStruct& TBoxSimStatus) = 0;
    ///Notifies all remote listeners about a change of value of the attribute TBoxSignalStrength.
    virtual void fireTBoxSignalStrengthAttributeChanged(const ::v1::GREATWALL::TBOX::TBoxTelephony::TBoxSignalStrengthStruct& TBoxSignalStrength) = 0;
    ///Notifies all remote listeners about a change of value of the attribute TBoxNetworkProvider.
    virtual void fireTBoxNetworkProviderAttributeChanged(const ::v1::GREATWALL::TBOX::TBoxTelephony::TBoxNetworkProviderStruct& TBoxNetworkProvider) = 0;

    /**
    * Sends a broadcast event for TBoxCallState. Should not be called directly.
    * Instead, the "fire<broadcastName>Event" methods of the stub should be used.
    */
    virtual void fireTBoxCallStateEvent(const ::v1::GREATWALL::TBOX::TBoxTelephony::TBoxTelephoneNumber &_TBoxTelephoneNumber, const ::v1::GREATWALL::TBOX::TBoxTelephony::TBoxCallType &_TBoxCallType, const ::v1::GREATWALL::TBOX::TBoxTelephony::TBoxCallState &_TBoxCallState, const ::v1::GREATWALL::TBOX::TBoxTelephony::long64 &_TBoxCallID) = 0;


    virtual void deactivateManagedInstances() = 0;

    void lockTBoxSimStatusAttribute(bool _lockAccess) {
        if (_lockAccess) {
            tBoxSimStatusMutex_.lock();
        } else {
            tBoxSimStatusMutex_.unlock();
        }
    }
    void lockTBoxSignalStrengthAttribute(bool _lockAccess) {
        if (_lockAccess) {
            tBoxSignalStrengthMutex_.lock();
        } else {
            tBoxSignalStrengthMutex_.unlock();
        }
    }
    void lockTBoxNetworkProviderAttribute(bool _lockAccess) {
        if (_lockAccess) {
            tBoxNetworkProviderMutex_.lock();
        } else {
            tBoxNetworkProviderMutex_.unlock();
        }
    }

protected:
    /**
     * Defines properties for storing the ClientIds of clients / proxies that have
     * subscribed to the selective broadcasts
     */

    std::recursive_mutex tBoxSimStatusMutex_;
    std::recursive_mutex tBoxSignalStrengthMutex_;
    std::recursive_mutex tBoxNetworkProviderMutex_;
};

/**
 * Defines the necessary callbacks to handle remote set events related to the attributes
 * defined in the IDL description for TBoxTelephony.
 * For each attribute two callbacks are defined:
 * - a verification callback that allows to verify the requested value and to prevent setting
 *   e.g. an invalid value ("onRemoteSet<AttributeName>").
 * - an action callback to do local work after the attribute value has been changed
 *   ("onRemote<AttributeName>Changed").
 *
 * This class and the one below are the ones an application developer needs to have
 * a look at if he wants to implement a service.
 */
class TBoxTelephonyStubRemoteEvent
{
public:
    virtual ~TBoxTelephonyStubRemoteEvent() { }

};

/**
 * Defines the interface that must be implemented by any class that should provide
 * the service TBoxTelephony to remote clients.
 * This class and the one above are the ones an application developer needs to have
 * a look at if he wants to implement a service.
 */
class TBoxTelephonyStub
    : public virtual CommonAPI::Stub<TBoxTelephonyStubAdapter, TBoxTelephonyStubRemoteEvent>
{
public:
    typedef std::function<void (TBoxTelephony::TBoxResponse _TBoxResponse, TBoxTelephony::long64 _TBoxCallID_Out)>TBoxCallOperationReply_t;
    typedef std::function<void (TBoxTelephony::ICCID _ICCID, TBoxTelephony::IMEI _IMEI, TBoxTelephony::IMSI _IMSI)>TBoxSIMInforReply_t;
    typedef std::function<void (TBoxTelephony::TBoxResponse _TBoxResponse, TBoxTelephony::long64 _TBoxCallID_Out)>TBoxStartCallReply_t;

    virtual ~TBoxTelephonyStub() {}
    virtual const CommonAPI::Version& getInterfaceVersion(std::shared_ptr<CommonAPI::ClientId> clientId) = 0;
    void lockInterfaceVersionAttribute(bool _lockAccess) { static_cast<void>(_lockAccess); }

    /// Provides getter access to the attribute TBoxSimStatus
    virtual const ::v1::GREATWALL::TBOX::TBoxTelephony::TBoxSimStatusStruct &getTBoxSimStatusAttribute(const std::shared_ptr<CommonAPI::ClientId> _client) = 0;
    /// sets attribute with the given value and propagates it to the adapter
    virtual void fireTBoxSimStatusAttributeChanged(::v1::GREATWALL::TBOX::TBoxTelephony::TBoxSimStatusStruct _value) {
    auto stubAdapter = CommonAPI::Stub<TBoxTelephonyStubAdapter, TBoxTelephonyStubRemoteEvent>::stubAdapter_.lock();
    if (stubAdapter)
        stubAdapter->fireTBoxSimStatusAttributeChanged(_value);
    }
    void lockTBoxSimStatusAttribute(bool _lockAccess) {
        auto stubAdapter = CommonAPI::Stub<TBoxTelephonyStubAdapter, TBoxTelephonyStubRemoteEvent>::stubAdapter_.lock();
        if (stubAdapter)
            stubAdapter->lockTBoxSimStatusAttribute(_lockAccess);
    }
    /// Provides getter access to the attribute TBoxSignalStrength
    virtual const ::v1::GREATWALL::TBOX::TBoxTelephony::TBoxSignalStrengthStruct &getTBoxSignalStrengthAttribute(const std::shared_ptr<CommonAPI::ClientId> _client) = 0;
    /// sets attribute with the given value and propagates it to the adapter
    virtual void fireTBoxSignalStrengthAttributeChanged(::v1::GREATWALL::TBOX::TBoxTelephony::TBoxSignalStrengthStruct _value) {
    auto stubAdapter = CommonAPI::Stub<TBoxTelephonyStubAdapter, TBoxTelephonyStubRemoteEvent>::stubAdapter_.lock();
    if (stubAdapter)
        stubAdapter->fireTBoxSignalStrengthAttributeChanged(_value);
    }
    void lockTBoxSignalStrengthAttribute(bool _lockAccess) {
        auto stubAdapter = CommonAPI::Stub<TBoxTelephonyStubAdapter, TBoxTelephonyStubRemoteEvent>::stubAdapter_.lock();
        if (stubAdapter)
            stubAdapter->lockTBoxSignalStrengthAttribute(_lockAccess);
    }
    /// Provides getter access to the attribute TBoxNetworkProvider
    virtual const ::v1::GREATWALL::TBOX::TBoxTelephony::TBoxNetworkProviderStruct &getTBoxNetworkProviderAttribute(const std::shared_ptr<CommonAPI::ClientId> _client) = 0;
    /// sets attribute with the given value and propagates it to the adapter
    virtual void fireTBoxNetworkProviderAttributeChanged(::v1::GREATWALL::TBOX::TBoxTelephony::TBoxNetworkProviderStruct _value) {
    auto stubAdapter = CommonAPI::Stub<TBoxTelephonyStubAdapter, TBoxTelephonyStubRemoteEvent>::stubAdapter_.lock();
    if (stubAdapter)
        stubAdapter->fireTBoxNetworkProviderAttributeChanged(_value);
    }
    void lockTBoxNetworkProviderAttribute(bool _lockAccess) {
        auto stubAdapter = CommonAPI::Stub<TBoxTelephonyStubAdapter, TBoxTelephonyStubRemoteEvent>::stubAdapter_.lock();
        if (stubAdapter)
            stubAdapter->lockTBoxNetworkProviderAttribute(_lockAccess);
    }

    /// This is the method that will be called on remote calls on the method TBoxCallOperation.
    virtual void TBoxCallOperation(const std::shared_ptr<CommonAPI::ClientId> _client, TBoxTelephony::TBoxTelephoneNumber _TBoxTelephoneNumber, TBoxTelephony::TBoxCallType _TBoxCallType, TBoxTelephony::TBoxCallOperation _TBoxCallOperation, TBoxTelephony::long64 _TBoxCallID_In, TBoxCallOperationReply_t _reply) = 0;
    /// This is the method that will be called on remote calls on the method TBoxSIMInfor.
    virtual void TBoxSIMInfor(const std::shared_ptr<CommonAPI::ClientId> _client, TBoxSIMInforReply_t _reply) = 0;
    /// This is the method that will be called on remote calls on the method TBoxStartCall.
    virtual void TBoxStartCall(const std::shared_ptr<CommonAPI::ClientId> _client, TBoxTelephony::TBoxTelephoneNumber _TBoxTelephoneNumber, TBoxTelephony::TBoxCallType _TBoxCallType, TBoxTelephony::long64 _TBoxCallID_In, TBoxStartCallReply_t _reply) = 0;
    /// Sends a broadcast event for TBoxCallState.
    virtual void fireTBoxCallStateEvent(const ::v1::GREATWALL::TBOX::TBoxTelephony::TBoxTelephoneNumber &_TBoxTelephoneNumber, const ::v1::GREATWALL::TBOX::TBoxTelephony::TBoxCallType &_TBoxCallType, const ::v1::GREATWALL::TBOX::TBoxTelephony::TBoxCallState &_TBoxCallState, const ::v1::GREATWALL::TBOX::TBoxTelephony::long64 &_TBoxCallID) {
        auto stubAdapter = CommonAPI::Stub<TBoxTelephonyStubAdapter, TBoxTelephonyStubRemoteEvent>::stubAdapter_.lock();
        if (stubAdapter)
            stubAdapter->fireTBoxCallStateEvent(_TBoxTelephoneNumber, _TBoxCallType, _TBoxCallState, _TBoxCallID);
    }

    
    using CommonAPI::Stub<TBoxTelephonyStubAdapter, TBoxTelephonyStubRemoteEvent>::initStubAdapter;
    typedef CommonAPI::Stub<TBoxTelephonyStubAdapter, TBoxTelephonyStubRemoteEvent>::StubAdapterType StubAdapterType;
    typedef CommonAPI::Stub<TBoxTelephonyStubAdapter, TBoxTelephonyStubRemoteEvent>::RemoteEventHandlerType RemoteEventHandlerType;
    typedef TBoxTelephonyStubRemoteEvent RemoteEventType;
    typedef TBoxTelephony StubInterface;
};

} // namespace TBOX
} // namespace GREATWALL
} // namespace v1


// Compatibility
namespace v1_0 = v1;

#endif // V1_GREATWALL_TBOX_T_Box_Telephony_STUB_HPP_