/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.1.12.v202002200719.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#ifndef V1_GREATWALL_DVR_VIMS_DVR_Status_Report_PROXY_BASE_HPP_
#define V1_GREATWALL_DVR_VIMS_DVR_Status_Report_PROXY_BASE_HPP_

#include <v1/GREATWALL/DVR_VIMS/DVRStatusReport.hpp>



#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/Deployment.hpp>
#include <CommonAPI/InputStream.hpp>
#include <CommonAPI/OutputStream.hpp>
#include <CommonAPI/Struct.hpp>
#include <cstdint>
#include <string>
#include <vector>

#include <CommonAPI/Attribute.hpp>
#include <CommonAPI/Event.hpp>
#include <CommonAPI/Proxy.hpp>
#include <functional>
#include <future>

#undef COMMONAPI_INTERNAL_COMPILATION

namespace v1 {
namespace GREATWALL {
namespace DVR_VIMS {

class DVRStatusReportProxyBase
    : virtual public CommonAPI::Proxy {
public:
    typedef CommonAPI::ObservableReadonlyAttribute< ::v1::GREATWALL::DVR_VIMS::DVRStatusReport::DVRSensorStatusStruct> DVRSensorStatusReportAttribute;
    typedef CommonAPI::ObservableReadonlyAttribute< ::v1::GREATWALL::DVR_VIMS::DVRStatusReport::DVRSystemStatus> DVRSystemStatusReportAttribute;
    typedef CommonAPI::Event<
        ::v1::GREATWALL::DVR_VIMS::DVRStatusReport::EMMCStatus, ::v1::GREATWALL::DVR_VIMS::DVRStatusReport::EMMCCapacityStruct
    > DVREMMCStatusReportEvent;
    typedef CommonAPI::Event<
        ::v1::GREATWALL::DVR_VIMS::DVRStatusReport::AccessType, ::v1::GREATWALL::DVR_VIMS::DVRStatusReport::ThemePictureID
    > OMCThemePictureReportEvent;
    typedef CommonAPI::Event<
        ::v1::GREATWALL::DVR_VIMS::DVRStatusReport::TotalTransProgress
    > AsyncDeleteOperationProgressEvent;
    typedef CommonAPI::Event<
        ::v1::GREATWALL::DVR_VIMS::DVRStatusReport::EventOperationType, ::v1::GREATWALL::DVR_VIMS::DVRStatusReport::EventType, ::v1::GREATWALL::DVR_VIMS::DVRStatusReport::AccessType
    > EventOperationReportEvent;
    typedef CommonAPI::Event<
        ::v1::GREATWALL::DVR_VIMS::DVRStatusReport::TFCardOption, ::v1::GREATWALL::DVR_VIMS::DVRStatusReport::TFCardStatus, ::v1::GREATWALL::DVR_VIMS::DVRStatusReport::TFCardCapacity
    > DVRTFStatusReportEvent;
    typedef CommonAPI::Event<
        ::v1::GREATWALL::DVR_VIMS::DVRStatusReport::EventTime, ::v1::GREATWALL::DVR_VIMS::DVRStatusReport::EventType, ::v1::GREATWALL::DVR_VIMS::DVRStatusReport::AccessType, ::v1::GREATWALL::DVR_VIMS::DVRStatusReport::FilePath, ::v1::GREATWALL::DVR_VIMS::DVRStatusReport::ThumbnailPath
    > DVREventReportEvent;
    typedef CommonAPI::Event<
        ::v1::GREATWALL::DVR_VIMS::DVRStatusReport::ExportFileInfoStruct, ::v1::GREATWALL::DVR_VIMS::DVRStatusReport::TotalTransProgress
    > ExportOperationProgressReportEvent;

    typedef std::function<void(const CommonAPI::CallStatus&, const DVRStatusReport::SetResult&)> DVRContinuousCaptureAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const DVRStatusReport::SetResult&)> DVRTimelapseVideoTapeAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const DVRStatusReport::SetResult&)> DVRManualOperationAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const DVRStatusReport::SetResult&)> StopShortVideoRecordingAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const DVRStatusReport::OMCCaptureFaileCode&)> PictureTransferRequestAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const DVRStatusReport::SetResult&)> CaringModeAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const DVRStatusReport::OMCCaptureFaileCode&)> OMCThemePictureResultAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const DVRStatusReport::OMCCaptureFaileCode&)> OMCCaptureRequestAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const DVRStatusReport::SetResult&)> StartShortVideoRecordingAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const DVRStatusReport::TotalExportCapacity&, const DVRStatusReport::FreeExportCapacity&)> TFCardExportCapacityQueryAsyncCallback;

    virtual DVRSensorStatusReportAttribute& getDVRSensorStatusReportAttribute() = 0;
    virtual DVRSystemStatusReportAttribute& getDVRSystemStatusReportAttribute() = 0;

    virtual DVREMMCStatusReportEvent& getDVREMMCStatusReportEvent() = 0;
    virtual OMCThemePictureReportEvent& getOMCThemePictureReportEvent() = 0;
    virtual AsyncDeleteOperationProgressEvent& getAsyncDeleteOperationProgressEvent() = 0;
    virtual EventOperationReportEvent& getEventOperationReportEvent() = 0;
    virtual DVRTFStatusReportEvent& getDVRTFStatusReportEvent() = 0;
    virtual DVREventReportEvent& getDVREventReportEvent() = 0;
    virtual ExportOperationProgressReportEvent& getExportOperationProgressReportEvent() = 0;

    virtual void DVRContinuousCapture(const DVRStatusReport::AccessType &_AccessType, const DVRStatusReport::CaptureNumber &_CaptureNumber, const DVRStatusReport::CaptureInterval &_CaptureInterval, CommonAPI::CallStatus &_internalCallStatus, DVRStatusReport::SetResult &_ContinuousCaptureACK, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> DVRContinuousCaptureAsync(const DVRStatusReport::AccessType &_AccessType, const DVRStatusReport::CaptureNumber &_CaptureNumber, const DVRStatusReport::CaptureInterval &_CaptureInterval, DVRContinuousCaptureAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
    /**
     * @invariant Fire And Forget
     */
    virtual void DVRStatusReportACK(const DVRStatusReport::SetResult &_StatusReportACK, CommonAPI::CallStatus &_internalCallStatus) = 0;
    virtual void DVRTimelapseVideoTape(const DVRStatusReport::TimelapseVideoInterval &_TimelapseVideoInterval, const DVRStatusReport::TimelapseVideoTotalFrameNumber &_TimelapseVideoTotalFrameNumber, const DVRStatusReport::DVRTimelapseVideoPlayFrameNumber &_DVRTimelapseVideoPlayFrameNumber, const DVRStatusReport::AccessType &_AccessType, CommonAPI::CallStatus &_internalCallStatus, DVRStatusReport::SetResult &_TimelapseVideoTapeACK, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> DVRTimelapseVideoTapeAsync(const DVRStatusReport::TimelapseVideoInterval &_TimelapseVideoInterval, const DVRStatusReport::TimelapseVideoTotalFrameNumber &_TimelapseVideoTotalFrameNumber, const DVRStatusReport::DVRTimelapseVideoPlayFrameNumber &_DVRTimelapseVideoPlayFrameNumber, const DVRStatusReport::AccessType &_AccessType, DVRTimelapseVideoTapeAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual void DVRManualOperation(const DVRStatusReport::ManualOperation &_ManualOperation, const DVRStatusReport::AccessType &_AccessType, CommonAPI::CallStatus &_internalCallStatus, DVRStatusReport::SetResult &_ManualOperationACK, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> DVRManualOperationAsync(const DVRStatusReport::ManualOperation &_ManualOperation, const DVRStatusReport::AccessType &_AccessType, DVRManualOperationAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual void StopShortVideoRecording(const DVRStatusReport::AccessType &_VideoRecordingChannel, CommonAPI::CallStatus &_internalCallStatus, DVRStatusReport::SetResult &_VideoRecordingACK, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> StopShortVideoRecordingAsync(const DVRStatusReport::AccessType &_VideoRecordingChannel, StopShortVideoRecordingAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual void PictureTransferRequest(const DVRStatusReport::EventTime &_EventTime, const DVRStatusReport::EventType &_EventType, const DVRStatusReport::AccessType &_AccessType, const DVRStatusReport::FileID &_FileID, const DVRStatusReport::FileSize &_FileSize, const DVRStatusReport::FileContentArray &_FileContentArray, CommonAPI::CallStatus &_internalCallStatus, DVRStatusReport::OMCCaptureFaileCode &_OMCCaptureFaileCode, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> PictureTransferRequestAsync(const DVRStatusReport::EventTime &_EventTime, const DVRStatusReport::EventType &_EventType, const DVRStatusReport::AccessType &_AccessType, const DVRStatusReport::FileID &_FileID, const DVRStatusReport::FileSize &_FileSize, const DVRStatusReport::FileContentArray &_FileContentArray, PictureTransferRequestAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual void CaringMode(const DVRStatusReport::AccessType &_AccessType, const DVRStatusReport::TotalCareTime &_TotalCareTime, CommonAPI::CallStatus &_internalCallStatus, DVRStatusReport::SetResult &_CaringModeACK, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> CaringModeAsync(const DVRStatusReport::AccessType &_AccessType, const DVRStatusReport::TotalCareTime &_TotalCareTime, CaringModeAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual void OMCThemePictureResult(const DVRStatusReport::AccessType &_AccessType, const DVRStatusReport::ThemePictureID &_ThemePictureID, const DVRStatusReport::FileSize &_FileSize, const DVRStatusReport::FileContentArray &_FileContentArray, CommonAPI::CallStatus &_internalCallStatus, DVRStatusReport::OMCCaptureFaileCode &_OMCCaptureFaileCode, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> OMCThemePictureResultAsync(const DVRStatusReport::AccessType &_AccessType, const DVRStatusReport::ThemePictureID &_ThemePictureID, const DVRStatusReport::FileSize &_FileSize, const DVRStatusReport::FileContentArray &_FileContentArray, OMCThemePictureResultAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual void OMCCaptureRequest(const DVRStatusReport::EventTime &_EventTime, const DVRStatusReport::EventType &_EventType, const DVRStatusReport::AccessType &_AccessType, const DVRStatusReport::FileID &_FileID, const DVRStatusReport::FileSize &_FileSize, CommonAPI::CallStatus &_internalCallStatus, DVRStatusReport::OMCCaptureFaileCode &_OMCCaptureFaileCode, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> OMCCaptureRequestAsync(const DVRStatusReport::EventTime &_EventTime, const DVRStatusReport::EventType &_EventType, const DVRStatusReport::AccessType &_AccessType, const DVRStatusReport::FileID &_FileID, const DVRStatusReport::FileSize &_FileSize, OMCCaptureRequestAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual void StartShortVideoRecording(const DVRStatusReport::AccessType &_VideoRecordingChannel, const DVRStatusReport::PreRecordingTime &_PreRecordingTime, const DVRStatusReport::TotalRecordingTime &_TotalRecordingTime, CommonAPI::CallStatus &_internalCallStatus, DVRStatusReport::SetResult &_VideoRecordingACK, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> StartShortVideoRecordingAsync(const DVRStatusReport::AccessType &_VideoRecordingChannel, const DVRStatusReport::PreRecordingTime &_PreRecordingTime, const DVRStatusReport::TotalRecordingTime &_TotalRecordingTime, StartShortVideoRecordingAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual void TFCardExportCapacityQuery(const DVRStatusReport::TFCardOption &_TFCardOption, CommonAPI::CallStatus &_internalCallStatus, DVRStatusReport::TotalExportCapacity &_TotalExportCapacity, DVRStatusReport::FreeExportCapacity &_FreeExportCapacity, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> TFCardExportCapacityQueryAsync(const DVRStatusReport::TFCardOption &_TFCardOption, TFCardExportCapacityQueryAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
};

} // namespace DVR_VIMS
} // namespace GREATWALL
} // namespace v1


// Compatibility
namespace v1_0 = v1;

#endif // V1_GREATWALL_DVR_VIMS_DVR_Status_Report_PROXY_BASE_HPP_
