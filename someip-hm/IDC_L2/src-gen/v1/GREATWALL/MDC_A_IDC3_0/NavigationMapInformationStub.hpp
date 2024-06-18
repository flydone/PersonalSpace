/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.1.12.v202002200719.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#ifndef V1_GREATWALL_MDC_A_IDC3_0_Navigation_Map_Information_STUB_HPP_
#define V1_GREATWALL_MDC_A_IDC3_0_Navigation_Map_Information_STUB_HPP_

#include <functional>
#include <sstream>




#include <v1/GREATWALL/MDC_A_IDC3_0/NavigationMapInformation.hpp>

#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <string>
#include <unordered_set>
#include <vector>


#include <CommonAPI/Stub.hpp>

#undef COMMONAPI_INTERNAL_COMPILATION

namespace v1 {
namespace GREATWALL {
namespace MDC_A_IDC3_0 {

/**
 * Receives messages from remote and handles all dispatching of deserialized calls
 * to a stub for the service NavigationMapInformation. Also provides means to send broadcasts
 * and attribute-changed-notifications of observable attributes as defined by this service.
 * An application developer should not need to bother with this class.
 */
class NavigationMapInformationStubAdapter
    : public virtual CommonAPI::StubAdapter,
      public virtual NavigationMapInformation {
 public:

    /**
    * Sends a broadcast event for AvlPathInfo. Should not be called directly.
    * Instead, the "fire<broadcastName>Event" methods of the stub should be used.
    */
    virtual void fireAvlPathInfoEvent(const ::v1::GREATWALL::MDC_A_IDC3_0::NavigationMapInformation::RouteODD &_RouteODD) = 0;


    virtual void deactivateManagedInstances() = 0;


protected:
    /**
     * Defines properties for storing the ClientIds of clients / proxies that have
     * subscribed to the selective broadcasts
     */

};

/**
 * Defines the necessary callbacks to handle remote set events related to the attributes
 * defined in the IDL description for NavigationMapInformation.
 * For each attribute two callbacks are defined:
 * - a verification callback that allows to verify the requested value and to prevent setting
 *   e.g. an invalid value ("onRemoteSet<AttributeName>").
 * - an action callback to do local work after the attribute value has been changed
 *   ("onRemote<AttributeName>Changed").
 *
 * This class and the one below are the ones an application developer needs to have
 * a look at if he wants to implement a service.
 */
class NavigationMapInformationStubRemoteEvent
{
public:
    virtual ~NavigationMapInformationStubRemoteEvent() { }

};

/**
 * Defines the interface that must be implemented by any class that should provide
 * the service NavigationMapInformation to remote clients.
 * This class and the one above are the ones an application developer needs to have
 * a look at if he wants to implement a service.
 */
class NavigationMapInformationStub
    : public virtual CommonAPI::Stub<NavigationMapInformationStubAdapter, NavigationMapInformationStubRemoteEvent>
{
public:

    virtual ~NavigationMapInformationStub() {}
    virtual const CommonAPI::Version& getInterfaceVersion(std::shared_ptr<CommonAPI::ClientId> clientId) = 0;
    void lockInterfaceVersionAttribute(bool _lockAccess) { static_cast<void>(_lockAccess); }


    /// This is the method that will be called on remote calls on the method NavPathInfoReq.
    virtual void NavPathInfoReq(const std::shared_ptr<CommonAPI::ClientId> _client, NavigationMapInformation::SDRoute _SDRoute) = 0;
    /// Sends a broadcast event for AvlPathInfo.
    virtual void fireAvlPathInfoEvent(const ::v1::GREATWALL::MDC_A_IDC3_0::NavigationMapInformation::RouteODD &_RouteODD) {
        auto stubAdapter = CommonAPI::Stub<NavigationMapInformationStubAdapter, NavigationMapInformationStubRemoteEvent>::stubAdapter_.lock();
        if (stubAdapter)
            stubAdapter->fireAvlPathInfoEvent(_RouteODD);
    }

    
    using CommonAPI::Stub<NavigationMapInformationStubAdapter, NavigationMapInformationStubRemoteEvent>::initStubAdapter;
    typedef CommonAPI::Stub<NavigationMapInformationStubAdapter, NavigationMapInformationStubRemoteEvent>::StubAdapterType StubAdapterType;
    typedef CommonAPI::Stub<NavigationMapInformationStubAdapter, NavigationMapInformationStubRemoteEvent>::RemoteEventHandlerType RemoteEventHandlerType;
    typedef NavigationMapInformationStubRemoteEvent RemoteEventType;
    typedef NavigationMapInformation StubInterface;
};

} // namespace MDC_A_IDC3_0
} // namespace GREATWALL
} // namespace v1


// Compatibility
namespace v1_0 = v1;

#endif // V1_GREATWALL_MDC_A_IDC3_0_Navigation_Map_Information_STUB_HPP_