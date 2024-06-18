/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.someip 3.1.12.v202002200807.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#ifndef V1_GREATWALL_DVR_VIMS_DVR_STATUS_REPORT_SOMEIP_PROXY_HPP_
#define V1_GREATWALL_DVR_VIMS_DVR_STATUS_REPORT_SOMEIP_PROXY_HPP_

#include <v1/GREATWALL/DVR_VIMS/DVRStatusReportProxyBase.hpp>
#include <v1/GREATWALL/DVR_VIMS/DVRStatusReportSomeIPDeployment.hpp>

#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/SomeIP/Factory.hpp>
#include <CommonAPI/SomeIP/Proxy.hpp>
#include <CommonAPI/SomeIP/Types.hpp>
#include <CommonAPI/SomeIP/Attribute.hpp>
#include <CommonAPI/SomeIP/Event.hpp>

#undef COMMONAPI_INTERNAL_COMPILATION

#include <string>

# if defined(_MSC_VER)
#  if _MSC_VER >= 1300
/*
 * Diamond inheritance is used for the CommonAPI::Proxy base class.
 * The Microsoft compiler put warning (C4250) using a desired c++ feature: "Delegating to a sister class"
 * A powerful technique that arises from using virtual inheritance is to delegate a method from a class in another class
 * by using a common abstract base class. This is also called cross delegation.
 */
#    pragma warning( disable : 4250 )
#  endif
# endif

namespace v1 {
namespace GREATWALL {
namespace DVR_VIMS {

class DVRStatusReportSomeIPProxy
    : virtual public DVRStatusReportProxyBase,
    virtual public CommonAPI::SomeIP::Proxy {
public:
    DVRStatusReportSomeIPProxy(
        const CommonAPI::SomeIP::Address &_address,
        const std::shared_ptr<CommonAPI::SomeIP::ProxyConnection> &_connection);

    virtual ~DVRStatusReportSomeIPProxy() { }

    virtual DVRSensorStatusReportAttribute& getDVRSensorStatusReportAttribute();
    virtual DVRSystemStatusReportAttribute& getDVRSystemStatusReportAttribute();

    virtual DVREMMCStatusReportEvent& getDVREMMCStatusReportEvent();
    virtual OMCThemePictureReportEvent& getOMCThemePictureReportEvent();
    virtual AsyncDeleteOperationProgressEvent& getAsyncDeleteOperationProgressEvent();
    virtual EventOperationReportEvent& getEventOperationReportEvent();
    virtual DVRTFStatusReportEvent& getDVRTFStatusReportEvent();
    virtual DVREventReportEvent& getDVREventReportEvent();
    virtual ExportOperationProgressReportEvent& getExportOperationProgressReportEvent();

    virtual void DVRContinuousCapture(const DVRStatusReport::AccessType &_AccessType, const DVRStatusReport::CaptureNumber &_CaptureNumber, const DVRStatusReport::CaptureInterval &_CaptureInterval, CommonAPI::CallStatus &_internalCallStatus, DVRStatusReport::SetResult &_ContinuousCaptureACK, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> DVRContinuousCaptureAsync(const DVRStatusReport::AccessType &_AccessType, const DVRStatusReport::CaptureNumber &_CaptureNumber, const DVRStatusReport::CaptureInterval &_CaptureInterval, DVRContinuousCaptureAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    virtual void DVRStatusReportACK(const DVRStatusReport::SetResult &_StatusReportACK, CommonAPI::CallStatus &_internalCallStatus);
    virtual void DVRTimelapseVideoTape(const DVRStatusReport::TimelapseVideoInterval &_TimelapseVideoInterval, const DVRStatusReport::TimelapseVideoTotalFrameNumber &_TimelapseVideoTotalFrameNumber, const DVRStatusReport::DVRTimelapseVideoPlayFrameNumber &_DVRTimelapseVideoPlayFrameNumber, const DVRStatusReport::AccessType &_AccessType, CommonAPI::CallStatus &_internalCallStatus, DVRStatusReport::SetResult &_TimelapseVideoTapeACK, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> DVRTimelapseVideoTapeAsync(const DVRStatusReport::TimelapseVideoInterval &_TimelapseVideoInterval, const DVRStatusReport::TimelapseVideoTotalFrameNumber &_TimelapseVideoTotalFrameNumber, const DVRStatusReport::DVRTimelapseVideoPlayFrameNumber &_DVRTimelapseVideoPlayFrameNumber, const DVRStatusReport::AccessType &_AccessType, DVRTimelapseVideoTapeAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    virtual void DVRManualOperation(const DVRStatusReport::ManualOperation &_ManualOperation, const DVRStatusReport::AccessType &_AccessType, CommonAPI::CallStatus &_internalCallStatus, DVRStatusReport::SetResult &_ManualOperationACK, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> DVRManualOperationAsync(const DVRStatusReport::ManualOperation &_ManualOperation, const DVRStatusReport::AccessType &_AccessType, DVRManualOperationAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    virtual void StopShortVideoRecording(const DVRStatusReport::AccessType &_VideoRecordingChannel, CommonAPI::CallStatus &_internalCallStatus, DVRStatusReport::SetResult &_VideoRecordingACK, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> StopShortVideoRecordingAsync(const DVRStatusReport::AccessType &_VideoRecordingChannel, StopShortVideoRecordingAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    virtual void PictureTransferRequest(const DVRStatusReport::EventTime &_EventTime, const DVRStatusReport::EventType &_EventType, const DVRStatusReport::AccessType &_AccessType, const DVRStatusReport::FileID &_FileID, const DVRStatusReport::FileSize &_FileSize, const DVRStatusReport::FileContentArray &_FileContentArray, CommonAPI::CallStatus &_internalCallStatus, DVRStatusReport::OMCCaptureFaileCode &_OMCCaptureFaileCode, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> PictureTransferRequestAsync(const DVRStatusReport::EventTime &_EventTime, const DVRStatusReport::EventType &_EventType, const DVRStatusReport::AccessType &_AccessType, const DVRStatusReport::FileID &_FileID, const DVRStatusReport::FileSize &_FileSize, const DVRStatusReport::FileContentArray &_FileContentArray, PictureTransferRequestAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    virtual void CaringMode(const DVRStatusReport::AccessType &_AccessType, const DVRStatusReport::TotalCareTime &_TotalCareTime, CommonAPI::CallStatus &_internalCallStatus, DVRStatusReport::SetResult &_CaringModeACK, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> CaringModeAsync(const DVRStatusReport::AccessType &_AccessType, const DVRStatusReport::TotalCareTime &_TotalCareTime, CaringModeAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    virtual void OMCThemePictureResult(const DVRStatusReport::AccessType &_AccessType, const DVRStatusReport::ThemePictureID &_ThemePictureID, const DVRStatusReport::FileSize &_FileSize, const DVRStatusReport::FileContentArray &_FileContentArray, CommonAPI::CallStatus &_internalCallStatus, DVRStatusReport::OMCCaptureFaileCode &_OMCCaptureFaileCode, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> OMCThemePictureResultAsync(const DVRStatusReport::AccessType &_AccessType, const DVRStatusReport::ThemePictureID &_ThemePictureID, const DVRStatusReport::FileSize &_FileSize, const DVRStatusReport::FileContentArray &_FileContentArray, OMCThemePictureResultAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    virtual void OMCCaptureRequest(const DVRStatusReport::EventTime &_EventTime, const DVRStatusReport::EventType &_EventType, const DVRStatusReport::AccessType &_AccessType, const DVRStatusReport::FileID &_FileID, const DVRStatusReport::FileSize &_FileSize, CommonAPI::CallStatus &_internalCallStatus, DVRStatusReport::OMCCaptureFaileCode &_OMCCaptureFaileCode, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> OMCCaptureRequestAsync(const DVRStatusReport::EventTime &_EventTime, const DVRStatusReport::EventType &_EventType, const DVRStatusReport::AccessType &_AccessType, const DVRStatusReport::FileID &_FileID, const DVRStatusReport::FileSize &_FileSize, OMCCaptureRequestAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    virtual void StartShortVideoRecording(const DVRStatusReport::AccessType &_VideoRecordingChannel, const DVRStatusReport::PreRecordingTime &_PreRecordingTime, const DVRStatusReport::TotalRecordingTime &_TotalRecordingTime, CommonAPI::CallStatus &_internalCallStatus, DVRStatusReport::SetResult &_VideoRecordingACK, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> StartShortVideoRecordingAsync(const DVRStatusReport::AccessType &_VideoRecordingChannel, const DVRStatusReport::PreRecordingTime &_PreRecordingTime, const DVRStatusReport::TotalRecordingTime &_TotalRecordingTime, StartShortVideoRecordingAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    virtual void TFCardExportCapacityQuery(const DVRStatusReport::TFCardOption &_TFCardOption, CommonAPI::CallStatus &_internalCallStatus, DVRStatusReport::TotalExportCapacity &_TotalExportCapacity, DVRStatusReport::FreeExportCapacity &_FreeExportCapacity, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> TFCardExportCapacityQueryAsync(const DVRStatusReport::TFCardOption &_TFCardOption, TFCardExportCapacityQueryAsyncCallback _callback, const CommonAPI::CallInfo *_info);


    virtual void getOwnVersion(uint16_t &_major, uint16_t &_minor) const;

private:

    CommonAPI::SomeIP::ObservableAttribute<CommonAPI::SomeIP::ReadonlyAttribute<DVRSensorStatusReportAttribute, ::v1::GREATWALL::DVR_VIMS::DVRStatusReport_::DVRSensorStatusStructDeployment_t>> dVRSensorStatusReport_;
    class SomeIPdVRSystemStatusReport_Attribute : public CommonAPI::SomeIP::ObservableAttribute<CommonAPI::SomeIP::ReadonlyAttribute<DVRSystemStatusReportAttribute, ::v1::GREATWALL::DVR_VIMS::DVRStatusReport_::DVRSystemStatusDeployment_t>> {
    public:
        template <typename... _A>
            SomeIPdVRSystemStatusReport_Attribute(DVRStatusReportSomeIPProxy &_proxy,
                _A ... arguments) : CommonAPI::SomeIP::ObservableAttribute<CommonAPI::SomeIP::ReadonlyAttribute<DVRSystemStatusReportAttribute, ::v1::GREATWALL::DVR_VIMS::DVRStatusReport_::DVRSystemStatusDeployment_t>>(
                                        _proxy, arguments...) {}
    };

    SomeIPdVRSystemStatusReport_Attribute dVRSystemStatusReport_;


     CommonAPI::SomeIP::Event<DVREMMCStatusReportEvent, CommonAPI::Deployable< ::v1::GREATWALL::DVR_VIMS::DVRStatusReport::EMMCStatus, ::v1::GREATWALL::DVR_VIMS::DVRStatusReport_::EMMCStatusDeployment_t >, CommonAPI::Deployable< ::v1::GREATWALL::DVR_VIMS::DVRStatusReport::EMMCCapacityStruct, ::v1::GREATWALL::DVR_VIMS::DVRStatusReport_::EMMCCapacityStructDeployment_t >> dVREMMCStatusReport_;
     CommonAPI::SomeIP::Event<OMCThemePictureReportEvent, CommonAPI::Deployable< ::v1::GREATWALL::DVR_VIMS::DVRStatusReport::AccessType, ::v1::GREATWALL::DVR_VIMS::DVRStatusReport_::AccessTypeDeployment_t >, CommonAPI::Deployable< ::v1::GREATWALL::DVR_VIMS::DVRStatusReport::ThemePictureID, CommonAPI::SomeIP::IntegerDeployment<uint32_t> >> oMCThemePictureReport_;
     CommonAPI::SomeIP::Event<AsyncDeleteOperationProgressEvent, CommonAPI::Deployable< ::v1::GREATWALL::DVR_VIMS::DVRStatusReport::TotalTransProgress, CommonAPI::SomeIP::IntegerDeployment<uint8_t> >> asyncDeleteOperationProgress_;
     CommonAPI::SomeIP::Event<EventOperationReportEvent, CommonAPI::Deployable< ::v1::GREATWALL::DVR_VIMS::DVRStatusReport::EventOperationType, ::v1::GREATWALL::DVR_VIMS::DVRStatusReport_::EventOperationTypeDeployment_t >, CommonAPI::Deployable< ::v1::GREATWALL::DVR_VIMS::DVRStatusReport::EventType, ::v1::GREATWALL::DVR_VIMS::DVRStatusReport_::EventTypeDeployment_t >, CommonAPI::Deployable< ::v1::GREATWALL::DVR_VIMS::DVRStatusReport::AccessType, ::v1::GREATWALL::DVR_VIMS::DVRStatusReport_::AccessTypeDeployment_t >> eventOperationReport_;
     CommonAPI::SomeIP::Event<DVRTFStatusReportEvent, CommonAPI::Deployable< ::v1::GREATWALL::DVR_VIMS::DVRStatusReport::TFCardOption, ::v1::GREATWALL::DVR_VIMS::DVRStatusReport_::TFCardOptionDeployment_t >, CommonAPI::Deployable< ::v1::GREATWALL::DVR_VIMS::DVRStatusReport::TFCardStatus, ::v1::GREATWALL::DVR_VIMS::DVRStatusReport_::TFCardStatusDeployment_t >, CommonAPI::Deployable< ::v1::GREATWALL::DVR_VIMS::DVRStatusReport::TFCardCapacity, ::v1::GREATWALL::DVR_VIMS::DVRStatusReport_::TFCardCapacityDeployment_t >> dVRTFStatusReport_;
     CommonAPI::SomeIP::Event<DVREventReportEvent, CommonAPI::Deployable< ::v1::GREATWALL::DVR_VIMS::DVRStatusReport::EventTime, CommonAPI::SomeIP::StringDeployment >, CommonAPI::Deployable< ::v1::GREATWALL::DVR_VIMS::DVRStatusReport::EventType, ::v1::GREATWALL::DVR_VIMS::DVRStatusReport_::EventTypeDeployment_t >, CommonAPI::Deployable< ::v1::GREATWALL::DVR_VIMS::DVRStatusReport::AccessType, ::v1::GREATWALL::DVR_VIMS::DVRStatusReport_::AccessTypeDeployment_t >, CommonAPI::Deployable< ::v1::GREATWALL::DVR_VIMS::DVRStatusReport::FilePath, CommonAPI::SomeIP::StringDeployment >, CommonAPI::Deployable< ::v1::GREATWALL::DVR_VIMS::DVRStatusReport::ThumbnailPath, CommonAPI::SomeIP::StringDeployment >> dVREventReport_;
     CommonAPI::SomeIP::Event<ExportOperationProgressReportEvent, CommonAPI::Deployable< ::v1::GREATWALL::DVR_VIMS::DVRStatusReport::ExportFileInfoStruct, ::v1::GREATWALL::DVR_VIMS::DVRStatusReport_::ExportFileInfoStructDeployment_t >, CommonAPI::Deployable< ::v1::GREATWALL::DVR_VIMS::DVRStatusReport::TotalTransProgress, CommonAPI::SomeIP::IntegerDeployment<uint8_t> >> exportOperationProgressReport_;

};

} // namespace DVR_VIMS
} // namespace GREATWALL
} // namespace v1

#endif // V1_GREATWALL_DVR_VIMS_DVR_Status_Report_SOMEIP_PROXY_HPP_