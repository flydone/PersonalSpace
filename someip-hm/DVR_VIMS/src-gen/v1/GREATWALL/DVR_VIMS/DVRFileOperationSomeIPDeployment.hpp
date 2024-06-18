/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.someip 3.1.12.v202002200807.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/

#ifndef V1_GREATWALL_DVR_VIMS_DVR_File_Operation_SOMEIP_DEPLOYMENT_HPP_
#define V1_GREATWALL_DVR_VIMS_DVR_File_Operation_SOMEIP_DEPLOYMENT_HPP_


#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif
#include <CommonAPI/SomeIP/Deployment.hpp>
#undef COMMONAPI_INTERNAL_COMPILATION

namespace v1 {
namespace GREATWALL {
namespace DVR_VIMS {
namespace DVRFileOperation_ {

// Interface-specific deployment types
typedef CommonAPI::SomeIP::EnumerationDeployment<uint8_t> ExportFileACKDeployment_t;
typedef CommonAPI::SomeIP::EnumerationDeployment<uint8_t> GetAllInfoDeployment_t;
typedef CommonAPI::SomeIP::EnumerationDeployment<uint8_t> FileTypeDeployment_t;
typedef CommonAPI::SomeIP::EnumerationDeployment<uint8_t> AccessTypeDeployment_t;
typedef CommonAPI::SomeIP::EnumerationDeployment<uint8_t> TFCardStatusDeployment_t;
typedef CommonAPI::SomeIP::EnumerationDeployment<uint8_t> TFCardOptionDeployment_t;
typedef CommonAPI::SomeIP::EnumerationDeployment<uint8_t> EMMCStatusDeployment_t;
typedef CommonAPI::SomeIP::EnumerationDeployment<uint8_t> SetResultDeployment_t;
typedef CommonAPI::SomeIP::EnumerationDeployment<uint8_t> RecordStatusDeployment_t;
typedef CommonAPI::SomeIP::EnumerationDeployment<uint8_t> SDCardOptionDeployment_t;
typedef CommonAPI::SomeIP::EnumerationDeployment<uint8_t> EventTypeDeployment_t;
typedef CommonAPI::SomeIP::EnumerationDeployment<uint8_t> ExportModeDeployment_t;
typedef CommonAPI::SomeIP::EnumerationDeployment<uint8_t> TFAllFileCapacity_EnumDeployment_t;
typedef CommonAPI::SomeIP::EnumerationDeployment<uint8_t> ParamFileType_EnumDeployment_t;
typedef CommonAPI::SomeIP::IntegerDeployment<uint32_t> SelectAllFileCapacityDeployment_t;
typedef CommonAPI::SomeIP::ArrayDeployment<
    CommonAPI::SomeIP::StructDeployment<
        CommonAPI::SomeIP::StringDeployment,
        CommonAPI::SomeIP::StringDeployment,
        ::v1::GREATWALL::DVR_VIMS::DVRFileOperation_::FileTypeDeployment_t,
        ::v1::GREATWALL::DVR_VIMS::DVRFileOperation_::AccessTypeDeployment_t
    >
> FileListStructArrayDeployment_t;
typedef CommonAPI::SomeIP::StructDeployment<
    CommonAPI::SomeIP::StringDeployment,
    CommonAPI::SomeIP::StringDeployment,
    ::v1::GREATWALL::DVR_VIMS::DVRFileOperation_::FileTypeDeployment_t,
    ::v1::GREATWALL::DVR_VIMS::DVRFileOperation_::AccessTypeDeployment_t
> FileListStructDeployment_t;
typedef CommonAPI::SomeIP::StringDeployment FilePathDeployment_t;
typedef CommonAPI::SomeIP::StringDeployment ThumbnailPathDeployment_t;
typedef CommonAPI::SomeIP::ArrayDeployment<
    CommonAPI::SomeIP::StructDeployment<
        ::v1::GREATWALL::DVR_VIMS::DVRFileOperation_::TFCardOptionDeployment_t,
        ::v1::GREATWALL::DVR_VIMS::DVRFileOperation_::TFCardStatusDeployment_t,
        CommonAPI::SomeIP::StructDeployment<
            CommonAPI::SomeIP::IntegerDeployment<uint32_t>,
            CommonAPI::SomeIP::IntegerDeployment<uint32_t>
        >
    >
> TFCardInfoListDeployment_t;
typedef CommonAPI::SomeIP::StructDeployment<
    ::v1::GREATWALL::DVR_VIMS::DVRFileOperation_::TFCardOptionDeployment_t,
    ::v1::GREATWALL::DVR_VIMS::DVRFileOperation_::TFCardStatusDeployment_t,
    CommonAPI::SomeIP::StructDeployment<
        CommonAPI::SomeIP::IntegerDeployment<uint32_t>,
        CommonAPI::SomeIP::IntegerDeployment<uint32_t>
    >
> TFCardInfoStructDeployment_t;
typedef CommonAPI::SomeIP::StructDeployment<
    CommonAPI::SomeIP::IntegerDeployment<uint32_t>,
    CommonAPI::SomeIP::IntegerDeployment<uint32_t>
> TFCardCapacityDeployment_t;
typedef CommonAPI::SomeIP::IntegerDeployment<uint32_t> RemainingCapacityDeployment_t;
typedef CommonAPI::SomeIP::IntegerDeployment<uint32_t> TotalCapacityDeployment_t;
typedef CommonAPI::SomeIP::IntegerDeployment<uint32_t> FileCapacityDeployment_t;
typedef CommonAPI::SomeIP::ArrayDeployment<
    CommonAPI::SomeIP::StructDeployment<
        CommonAPI::SomeIP::StringDeployment,
        CommonAPI::SomeIP::StringDeployment,
        ::v1::GREATWALL::DVR_VIMS::DVRFileOperation_::FileTypeDeployment_t,
        ::v1::GREATWALL::DVR_VIMS::DVRFileOperation_::AccessTypeDeployment_t,
        CommonAPI::SomeIP::StringDeployment,
        CommonAPI::SomeIP::IntegerDeployment<uint8_t>
    >
> FileListIncludeDate_ArrayDeployment_t;
typedef CommonAPI::SomeIP::StructDeployment<
    CommonAPI::SomeIP::StringDeployment,
    CommonAPI::SomeIP::StringDeployment,
    ::v1::GREATWALL::DVR_VIMS::DVRFileOperation_::FileTypeDeployment_t,
    ::v1::GREATWALL::DVR_VIMS::DVRFileOperation_::AccessTypeDeployment_t,
    CommonAPI::SomeIP::StringDeployment,
    CommonAPI::SomeIP::IntegerDeployment<uint8_t>
> FileListIncludeDate_StructDeployment_t;
typedef CommonAPI::SomeIP::IntegerDeployment<uint8_t> FileNumberDeployment_t;
typedef CommonAPI::SomeIP::StringDeployment EventTimeDeployment_t;
typedef CommonAPI::SomeIP::ArrayDeployment<
    CommonAPI::SomeIP::StringDeployment
> FileListPathDeployment_t;
typedef CommonAPI::SomeIP::StringDeployment FileNameDeployment_t;
typedef CommonAPI::SomeIP::ArrayDeployment<
    ::v1::GREATWALL::DVR_VIMS::DVRFileOperation_::TFCardOptionDeployment_t
> TFCardOptionListDeployment_t;
typedef CommonAPI::SomeIP::ArrayDeployment<
    CommonAPI::SomeIP::StructDeployment<
        ::v1::GREATWALL::DVR_VIMS::DVRFileOperation_::ParamFileType_EnumDeployment_t,
        CommonAPI::SomeIP::IntegerDeployment<int32_t>,
        CommonAPI::SomeIP::IntegerDeployment<int32_t>
    >
> FileCapacityList_ArrayDeployment_t;
typedef CommonAPI::SomeIP::StructDeployment<
    ::v1::GREATWALL::DVR_VIMS::DVRFileOperation_::ParamFileType_EnumDeployment_t,
    CommonAPI::SomeIP::IntegerDeployment<int32_t>,
    CommonAPI::SomeIP::IntegerDeployment<int32_t>
> ParamFileCapacityStructDeployment_t;
typedef CommonAPI::SomeIP::IntegerDeployment<int32_t> UsedCapacity_IntegerDeployment_t;
typedef CommonAPI::SomeIP::IntegerDeployment<int32_t> TotalCapacity_IntegerDeployment_t;
typedef CommonAPI::SomeIP::ArrayDeployment<
    ::v1::GREATWALL::DVR_VIMS::DVRFileOperation_::ParamFileType_EnumDeployment_t
> TFCardFileTypeList_ArrayDeployment_t;
typedef CommonAPI::SomeIP::StructDeployment<
    CommonAPI::SomeIP::IntegerDeployment<uint32_t>,
    CommonAPI::SomeIP::IntegerDeployment<uint32_t>
> EMMCCapacityStructDeployment_t;

// Type-specific deployments
COMMONAPI_EXPORT extern ::v1::GREATWALL::DVR_VIMS::DVRFileOperation_::FileListStructArrayDeployment_t FileListStructArrayDeployment;
COMMONAPI_EXPORT extern ::v1::GREATWALL::DVR_VIMS::DVRFileOperation_::FileListStructDeployment_t FileListStructDeployment;
COMMONAPI_EXPORT extern ::v1::GREATWALL::DVR_VIMS::DVRFileOperation_::FileListIncludeDate_ArrayDeployment_t FileListIncludeDate_ArrayDeployment;
COMMONAPI_EXPORT extern ::v1::GREATWALL::DVR_VIMS::DVRFileOperation_::FileListIncludeDate_StructDeployment_t FileListIncludeDate_StructDeployment;

// Attribute-specific deployments

// Argument-specific deployment

// Broadcast-specific deployments

} // namespace DVRFileOperation_
} // namespace DVR_VIMS
} // namespace GREATWALL
} // namespace v1

#endif // V1_GREATWALL_DVR_VIMS_DVR_File_Operation_SOMEIP_DEPLOYMENT_HPP_