/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.1.12.v202002200719.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#ifndef V1_GREATWALL_DVR_VIMS_DVR_File_Operation_PROXY_BASE_HPP_
#define V1_GREATWALL_DVR_VIMS_DVR_File_Operation_PROXY_BASE_HPP_

#include <v1/GREATWALL/DVR_VIMS/DVRFileOperation.hpp>



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

#include <CommonAPI/Proxy.hpp>
#include <functional>
#include <future>

#undef COMMONAPI_INTERNAL_COMPILATION

namespace v1 {
namespace GREATWALL {
namespace DVR_VIMS {

class DVRFileOperationProxyBase
    : virtual public CommonAPI::Proxy {
public:

    typedef std::function<void(const CommonAPI::CallStatus&, const DVRFileOperation::SetResult&)> AllFileDeleteRequestAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const DVRFileOperation::FileListStructArray&)> FileListRequestAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const DVRFileOperation::ExportFileACK&)> AllFileExportRequestAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const DVRFileOperation::ExportFileACK&)> FileExportRequestAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const DVRFileOperation::SetResult&)> AsyncAllFileDeleteRequestAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const DVRFileOperation::FileCapacityList_Array&)> DVRFileCapacityInfoReqAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const DVRFileOperation::SetResult&)> SDCardFormatAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const DVRFileOperation::SetResult&)> StartVideoBrowseAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const DVRFileOperation::FileListIncludeDate_Array&)> FileListIncludeDateReqAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const DVRFileOperation::SetResult&)> FileDeleteRequestAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const DVRFileOperation::TFCardInfoList&)> TFCardInfoQueryAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const DVRFileOperation::SetResult&, const DVRFileOperation::FileCapacity&)> SelectFileCapacityRequestAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const DVRFileOperation::EMMCStatus&, const DVRFileOperation::EMMCCapacityStruct&)> EMMCInfoQueryAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const DVRFileOperation::SetResult&)> StopVideoBrowseAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const DVRFileOperation::AccessType&, const DVRFileOperation::FileType&, const DVRFileOperation::SelectAllFileCapacity&)> SelectAllFileCapacityRequestAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const DVRFileOperation::RecordStatus&, const DVRFileOperation::EventType&)> RecordEventStatusRequestAsyncCallback;



    virtual void AllFileDeleteRequest(const DVRFileOperation::AccessType &_AccessType, const DVRFileOperation::FileType &_FileType, CommonAPI::CallStatus &_internalCallStatus, DVRFileOperation::SetResult &_FileDeleteACK, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> AllFileDeleteRequestAsync(const DVRFileOperation::AccessType &_AccessType, const DVRFileOperation::FileType &_FileType, AllFileDeleteRequestAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual void FileListRequest(const DVRFileOperation::FileType &_FileType, const DVRFileOperation::AccessType &_AccessType, const DVRFileOperation::FileNumber &_FileNumber, const DVRFileOperation::FileName &_FileName, CommonAPI::CallStatus &_internalCallStatus, DVRFileOperation::FileListStructArray &_FileListStructArray, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> FileListRequestAsync(const DVRFileOperation::FileType &_FileType, const DVRFileOperation::AccessType &_AccessType, const DVRFileOperation::FileNumber &_FileNumber, const DVRFileOperation::FileName &_FileName, FileListRequestAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual void AllFileExportRequest(const DVRFileOperation::ExportMode &_ExportMode, const DVRFileOperation::AccessType &_AccessType, const DVRFileOperation::FileType &_FileType, CommonAPI::CallStatus &_internalCallStatus, DVRFileOperation::ExportFileACK &_ExportFileACK, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> AllFileExportRequestAsync(const DVRFileOperation::ExportMode &_ExportMode, const DVRFileOperation::AccessType &_AccessType, const DVRFileOperation::FileType &_FileType, AllFileExportRequestAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual void FileExportRequest(const DVRFileOperation::ExportMode &_ExportMode, const DVRFileOperation::FileListPath &_FileListPath, CommonAPI::CallStatus &_internalCallStatus, DVRFileOperation::ExportFileACK &_ExportFileACK, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> FileExportRequestAsync(const DVRFileOperation::ExportMode &_ExportMode, const DVRFileOperation::FileListPath &_FileListPath, FileExportRequestAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual void AsyncAllFileDeleteRequest(const DVRFileOperation::AccessType &_AccessType, const DVRFileOperation::FileType &_FileType, CommonAPI::CallStatus &_internalCallStatus, DVRFileOperation::SetResult &_FileDeleteACK, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> AsyncAllFileDeleteRequestAsync(const DVRFileOperation::AccessType &_AccessType, const DVRFileOperation::FileType &_FileType, AsyncAllFileDeleteRequestAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual void DVRFileCapacityInfoReq(const DVRFileOperation::TFAllFileCapacity_Enum &_TFAllFileCapacity, const DVRFileOperation::TFCardFileTypeList_Array &_TFCardFileTypeList, CommonAPI::CallStatus &_internalCallStatus, DVRFileOperation::FileCapacityList_Array &_FileCapacityList, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> DVRFileCapacityInfoReqAsync(const DVRFileOperation::TFAllFileCapacity_Enum &_TFAllFileCapacity, const DVRFileOperation::TFCardFileTypeList_Array &_TFCardFileTypeList, DVRFileCapacityInfoReqAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual void SDCardFormat(const DVRFileOperation::SDCardOption &_SDCardOption, CommonAPI::CallStatus &_internalCallStatus, DVRFileOperation::SetResult &_TFCardFormatACK, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> SDCardFormatAsync(const DVRFileOperation::SDCardOption &_SDCardOption, SDCardFormatAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual void StartVideoBrowse(const DVRFileOperation::AccessType &_VideoBrowseChannel, CommonAPI::CallStatus &_internalCallStatus, DVRFileOperation::SetResult &_VideoBrowseACK, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> StartVideoBrowseAsync(const DVRFileOperation::AccessType &_VideoBrowseChannel, StartVideoBrowseAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual void FileListIncludeDateReq(const DVRFileOperation::FileType &_FileType, const DVRFileOperation::AccessType &_AccessType, const DVRFileOperation::FileNumber &_FileNumber, const DVRFileOperation::FileName &_FileName, CommonAPI::CallStatus &_internalCallStatus, DVRFileOperation::FileListIncludeDate_Array &_FileListIncludeDate, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> FileListIncludeDateReqAsync(const DVRFileOperation::FileType &_FileType, const DVRFileOperation::AccessType &_AccessType, const DVRFileOperation::FileNumber &_FileNumber, const DVRFileOperation::FileName &_FileName, FileListIncludeDateReqAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual void FileDeleteRequest(const DVRFileOperation::FileListPath &_FileListPath, CommonAPI::CallStatus &_internalCallStatus, DVRFileOperation::SetResult &_FileDeleteACK, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> FileDeleteRequestAsync(const DVRFileOperation::FileListPath &_FileListPath, FileDeleteRequestAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual void TFCardInfoQuery(const DVRFileOperation::GetAllInfo &_GetAllInfo, const DVRFileOperation::TFCardOptionList &_TFCardOptionList, CommonAPI::CallStatus &_internalCallStatus, DVRFileOperation::TFCardInfoList &_TFCardInfoList, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> TFCardInfoQueryAsync(const DVRFileOperation::GetAllInfo &_GetAllInfo, const DVRFileOperation::TFCardOptionList &_TFCardOptionList, TFCardInfoQueryAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual void SelectFileCapacityRequest(const DVRFileOperation::FileListPath &_FileListPath, CommonAPI::CallStatus &_internalCallStatus, DVRFileOperation::SetResult &_SetResult, DVRFileOperation::FileCapacity &_FileCapacity, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> SelectFileCapacityRequestAsync(const DVRFileOperation::FileListPath &_FileListPath, SelectFileCapacityRequestAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual void EMMCInfoQuery(const DVRFileOperation::GetAllInfo &_GetAllInfo, CommonAPI::CallStatus &_internalCallStatus, DVRFileOperation::EMMCStatus &_EMMCStatus, DVRFileOperation::EMMCCapacityStruct &_EMMCCapacityStruct, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> EMMCInfoQueryAsync(const DVRFileOperation::GetAllInfo &_GetAllInfo, EMMCInfoQueryAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual void StopVideoBrowse(const DVRFileOperation::AccessType &_VideoBrowseChannel, CommonAPI::CallStatus &_internalCallStatus, DVRFileOperation::SetResult &_VideoBrowseACK, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> StopVideoBrowseAsync(const DVRFileOperation::AccessType &_VideoBrowseChannel, StopVideoBrowseAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual void SelectAllFileCapacityRequest(const DVRFileOperation::AccessType &_AccessType_In, const DVRFileOperation::FileType &_FileType_In, CommonAPI::CallStatus &_internalCallStatus, DVRFileOperation::AccessType &_AccessType_Out, DVRFileOperation::FileType &_FileType_Out, DVRFileOperation::SelectAllFileCapacity &_SelectAllFileCapacity, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> SelectAllFileCapacityRequestAsync(const DVRFileOperation::AccessType &_AccessType_In, const DVRFileOperation::FileType &_FileType_In, SelectAllFileCapacityRequestAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual void RecordEventStatusRequest(const DVRFileOperation::AccessType &_AccessType, CommonAPI::CallStatus &_internalCallStatus, DVRFileOperation::RecordStatus &_RecordStatus, DVRFileOperation::EventType &_EventType, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> RecordEventStatusRequestAsync(const DVRFileOperation::AccessType &_AccessType, RecordEventStatusRequestAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
};

} // namespace DVR_VIMS
} // namespace GREATWALL
} // namespace v1


// Compatibility
namespace v1_0 = v1;

#endif // V1_GREATWALL_DVR_VIMS_DVR_File_Operation_PROXY_BASE_HPP_