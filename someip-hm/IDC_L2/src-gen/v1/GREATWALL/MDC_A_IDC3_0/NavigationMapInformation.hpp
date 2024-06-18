/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.1.12.v202002200719.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#ifndef V1_GREATWALL_MDC_A_IDC3_0_NAVIGATION_MAP_INFORMATION_HPP_
#define V1_GREATWALL_MDC_A_IDC3_0_NAVIGATION_MAP_INFORMATION_HPP_




#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/Types.hpp>
#include <string>

#undef COMMONAPI_INTERNAL_COMPILATION

namespace v1 {
namespace GREATWALL {
namespace MDC_A_IDC3_0 {

class NavigationMapInformation {
public:
    virtual ~NavigationMapInformation() { }

    static inline const char* getInterface();
    static inline CommonAPI::Version getInterfaceVersion();
    typedef std::string RouteODD;
    typedef std::string SDRoute;
};

const char* NavigationMapInformation::getInterface() {
    return ("GREATWALL.MDC_A_IDC3_0.NavigationMapInformation:v1_0");
}

CommonAPI::Version NavigationMapInformation::getInterfaceVersion() {
    return CommonAPI::Version(1, 0);
}


} // namespace MDC_A_IDC3_0
} // namespace GREATWALL
} // namespace v1

namespace CommonAPI {
}


// Compatibility
namespace v1_0 = v1;

#endif // V1_GREATWALL_MDC_A_IDC3_0_NAVIGATION_MAP_INFORMATION_HPP_
