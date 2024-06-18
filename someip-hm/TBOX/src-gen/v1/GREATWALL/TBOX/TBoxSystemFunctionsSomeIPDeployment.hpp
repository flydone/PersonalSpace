/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.someip 3.1.12.v202002200807.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/

#ifndef V1_GREATWALL_TBOX_T_Box_System_Functions_SOMEIP_DEPLOYMENT_HPP_
#define V1_GREATWALL_TBOX_T_Box_System_Functions_SOMEIP_DEPLOYMENT_HPP_


#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif
#include <CommonAPI/SomeIP/Deployment.hpp>
#undef COMMONAPI_INTERNAL_COMPILATION

namespace v1 {
namespace GREATWALL {
namespace TBOX {
namespace TBoxSystemFunctions_ {

// Interface-specific deployment types
typedef CommonAPI::SomeIP::EnumerationDeployment<uint16_t> QXRTCM_StatusCodeDeployment_t;
typedef CommonAPI::SomeIP::EnumerationDeployment<uint8_t> UpgradeRequstDeployment_t;
typedef CommonAPI::SomeIP::EnumerationDeployment<uint8_t> TBoxAPN2OperationDeployment_t;
typedef CommonAPI::SomeIP::EnumerationDeployment<uint8_t> UpgradeResultDeployment_t;
typedef CommonAPI::SomeIP::EnumerationDeployment<uint8_t> LogDownloadCommandDeployment_t;
typedef CommonAPI::SomeIP::EnumerationDeployment<uint8_t> UpgradeCompleteDeployment_t;
typedef CommonAPI::SomeIP::EnumerationDeployment<uint8_t> TBoxResetOptionDeployment_t;
typedef CommonAPI::SomeIP::EnumerationDeployment<uint8_t> TBoxResponseDeployment_t;
typedef CommonAPI::SomeIP::EnumerationDeployment<uint8_t> TBoxAPN2StatusDeployment_t;
typedef CommonAPI::SomeIP::EnumerationDeployment<uint8_t> UpgradeResponseDeployment_t;
typedef CommonAPI::SomeIP::ArrayDeployment<
    CommonAPI::SomeIP::IntegerDeployment<uint32_t>
> TBoxDTCCodeDeployment_t;
typedef CommonAPI::SomeIP::StringDeployment SNDeployment_t;
typedef CommonAPI::SomeIP::StringDeployment DoubleGPSRawDataDeployment_t;
typedef CommonAPI::SomeIP::StringDeployment COMP2Deployment_t;
typedef CommonAPI::SomeIP::StringDeployment GPSRawDataDeployment_t;
typedef CommonAPI::SomeIP::IntegerDeployment<uint8_t> UpgradeProcessDeployment_t;
typedef CommonAPI::SomeIP::StringDeployment COMP1Deployment_t;
typedef CommonAPI::SomeIP::StringDeployment FW0Deployment_t;
typedef CommonAPI::SomeIP::ArrayDeployment<
    CommonAPI::SomeIP::IntegerDeployment<uint8_t>
> ConnectionInfoDeployment_t;
typedef CommonAPI::SomeIP::StringDeployment SW1Deployment_t;
typedef CommonAPI::SomeIP::StringDeployment FW1Deployment_t;
typedef CommonAPI::SomeIP::StringDeployment GPSInfoDeployment_t;
typedef CommonAPI::SomeIP::StringDeployment SW0Deployment_t;
typedef CommonAPI::SomeIP::ArrayDeployment<
    CommonAPI::SomeIP::IntegerDeployment<uint8_t>
> TBOXCorrection_RTCM32Deployment_t;

// Type-specific deployments
COMMONAPI_EXPORT extern ::v1::GREATWALL::TBOX::TBoxSystemFunctions_::TBoxDTCCodeDeployment_t TBoxDTCCodeDeployment;

// Attribute-specific deployments

// Argument-specific deployment
COMMONAPI_EXPORT extern CommonAPI::SomeIP::StringDeployment TBoxInfrastructureData_SNDeployment;
COMMONAPI_EXPORT extern CommonAPI::SomeIP::StringDeployment TBoxInfrastructureData_FW0Deployment;
COMMONAPI_EXPORT extern CommonAPI::SomeIP::StringDeployment TBoxInfrastructureData_SW0Deployment;
COMMONAPI_EXPORT extern CommonAPI::SomeIP::StringDeployment TBoxInfrastructureData_FW1Deployment;
COMMONAPI_EXPORT extern CommonAPI::SomeIP::StringDeployment TBoxInfrastructureData_SW1Deployment;
COMMONAPI_EXPORT extern CommonAPI::SomeIP::StringDeployment TBoxInfrastructureData_COMP1Deployment;
COMMONAPI_EXPORT extern CommonAPI::SomeIP::StringDeployment TBoxInfrastructureData_COMP2Deployment;

// Broadcast-specific deployments

} // namespace TBoxSystemFunctions_
} // namespace TBOX
} // namespace GREATWALL
} // namespace v1

#endif // V1_GREATWALL_TBOX_T_Box_System_Functions_SOMEIP_DEPLOYMENT_HPP_