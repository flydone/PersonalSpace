/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.someip 3.1.12.v202002200807.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/

#ifndef V1_GREATWALL_MDC_A_IDC1_5_IDC3_0_HAP_HAV_Pand_AVP_Functions_SOMEIP_DEPLOYMENT_HPP_
#define V1_GREATWALL_MDC_A_IDC1_5_IDC3_0_HAP_HAV_Pand_AVP_Functions_SOMEIP_DEPLOYMENT_HPP_


#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif
#include <CommonAPI/SomeIP/Deployment.hpp>
#undef COMMONAPI_INTERNAL_COMPILATION

namespace v1 {
namespace GREATWALL_MDC_A_IDC1_5_IDC3_0_HAP {
namespace HAVPandAVPFunctions_ {

// Interface-specific deployment types
typedef CommonAPI::SomeIP::ArrayDeployment<
    CommonAPI::SomeIP::IntegerDeployment<uint8_t>
> HAVPLearningWorldArrayDeployment_t;
typedef CommonAPI::SomeIP::ArrayDeployment<
    CommonAPI::SomeIP::IntegerDeployment<uint8_t>
> HAVPVehDataArrayDeployment_t;
typedef CommonAPI::SomeIP::ArrayDeployment<
    CommonAPI::SomeIP::IntegerDeployment<uint8_t>
> HAVPMapFileArrayDeployment_t;

// Type-specific deployments

// Attribute-specific deployments

// Argument-specific deployment

// Broadcast-specific deployments

} // namespace HAVPandAVPFunctions_
} // namespace GREATWALL_MDC_A_IDC1_5_IDC3_0_HAP
} // namespace v1

#endif // V1_GREATWALL_MDC_A_IDC1_5_IDC3_0_HAP_HAV_Pand_AVP_Functions_SOMEIP_DEPLOYMENT_HPP_
