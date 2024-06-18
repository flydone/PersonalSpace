/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.1.12.v202002200719.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#ifndef V1_GREATWALL_MDC_A_IDC3_0_Navigation_Map_Information_PROXY_BASE_HPP_
#define V1_GREATWALL_MDC_A_IDC3_0_Navigation_Map_Information_PROXY_BASE_HPP_

#include <v1/GREATWALL/MDC_A_IDC3_0/NavigationMapInformation.hpp>



#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <string>
#include <vector>

#include <CommonAPI/Event.hpp>
#include <CommonAPI/Proxy.hpp>
#include <functional>
#include <future>

#undef COMMONAPI_INTERNAL_COMPILATION

namespace v1 {
namespace GREATWALL {
namespace MDC_A_IDC3_0 {

class NavigationMapInformationProxyBase
    : virtual public CommonAPI::Proxy {
public:
    typedef CommonAPI::Event<
        ::v1::GREATWALL::MDC_A_IDC3_0::NavigationMapInformation::RouteODD
    > AvlPathInfoEvent;



    virtual AvlPathInfoEvent& getAvlPathInfoEvent() = 0;

    /**
     * @invariant Fire And Forget
     */
    virtual void NavPathInfoReq(const NavigationMapInformation::SDRoute &_SDRoute, CommonAPI::CallStatus &_internalCallStatus) = 0;
};

} // namespace MDC_A_IDC3_0
} // namespace GREATWALL
} // namespace v1


// Compatibility
namespace v1_0 = v1;

#endif // V1_GREATWALL_MDC_A_IDC3_0_Navigation_Map_Information_PROXY_BASE_HPP_