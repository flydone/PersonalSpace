/*************************************************************************
 * Copyright (C) 2022 GWM Automotive Inc.
 *
 * The copyright notice above does not evidence any actual
 * or intended publication of such source code.
 * The code contains GWM Confidential Proprietary Information.
 *************************************************************************/
//
// Created by LZX on 2022/4/3.
//

#include "public_util.h"
#include "DVRFileOperation.h"

void DVRFileOperationInit(char *appName, char *configFile) {
    LOGI("DVRFileOperationInit, appName=%s, configFile=%s", appName, configFile);
    if (configFile) {
        setenv("VSOMEIP_CONFIGURATION", configFile, 1);
    }
    if (gRuntime == NULL) {
        gRuntime = CommonAPI::Runtime::get();
    }
    gDVRFileOperationProxy = gRuntime->buildProxy<DVRFileOperationProxy>(
            "local", "DVRFileOperation01", appName);
    std::string versionInfo = gRuntime->get_version();
    std::string version = versionInfo.substr(versionInfo.rfind(" ") + 1);

    LOGI("DVRFileOperationInit: appName = %s version = %s", appName, version.c_str());
    __system_property_set("vendor.gwm.someip.version", version.c_str());
}

bool DVRFileOperationIsReady() {
    bool ret = gDVRFileOperationProxy->isAvailable();
    LOGD("DVRFileOperationIsReady: %d",ret);
    return ret;
}

void fillFileListStructArray(DVRFileOperation::FileListStructArray &array,FileListStructArrayOut &out) {
    int len = array.size();
    LOGI("fillFileListStructArray: enter, len:%d", len);

    for (int i=0; i<len; i++) {

        FileListStruct_DT file;
        file.filePath = array[i].getFilePath();
        file.thumbnailPath = array[i].getThumbnailPath();
        file.fileTypeDt = static_cast<FileType_DT>(array[i].getFileType().value_);
        file.accessTypeDt = static_cast<AccessType_DT>(array[i].getAccessType().value_);
        out.dynamicArray.push_back(std::move(file));

        LOGD("fillFileListStructArray: filePath = %s, thumbnailPath = %s, FileType = %d, AccessType = %d, len = %d",
             out.dynamicArray[i].filePath.c_str() ,out.dynamicArray[i].thumbnailPath.c_str() ,out.dynamicArray[i].fileTypeDt ,out.dynamicArray[i].accessTypeDt ,len);
    }
}

void fillFileListIncludeDateArray(DVRFileOperation::FileListIncludeDate_Array &array,FileListIncludeDateArrayOut &out) {
    int len = array.size();
    LOGI("fillFileListIncludeDateArray: enter, len:%d", len);

    for (int i=0; i<len; i++) {

        FileListIncludeDateStruct_DT file;
        file.filePath = array[i].getFilePath();
        file.thumbnailPath = array[i].getThumbnailPath();
        file.fileTypeDt = static_cast<FileType_DT>(array[i].getFileType().value_);
        file.accessTypeDt = static_cast<AccessType_DT>(array[i].getAccessType().value_);
		file.eventTime = array[i].getEventTime();
		file.fileNumber = array[i].getFileNumber();
        out.dynamicOutArray.push_back(std::move(file));

        LOGD("fillFileListIncludeDateArray: filePath = %s, thumbnailPath = %s, fileType = %d, AccessType = %d, eventTime = %s, fileNumber = %d, len = %d",
             out.dynamicOutArray[i].filePath.c_str() ,out.dynamicOutArray[i].thumbnailPath.c_str() ,out.dynamicOutArray[i].fileTypeDt ,out.dynamicOutArray[i].accessTypeDt ,out.dynamicOutArray[i].eventTime.c_str() ,out.dynamicOutArray[i].fileNumber ,len);
    }
}

void fillDVRFileCapacityInfoArray(DVRFileOperation::FileCapacityList_Array &array,FileCapacityListArrayOut &out) {
    int len = array.size();
    LOGI("fillDVRFileCapacityInfoArray: enter, len:%d", len);

    for (int i=0; i<len; i++) {

        ParamFileCapacityStruct_DT file;
        file.paramFileTypeEnumDt = static_cast<ParamFileTypeEnum_DT>(array[i].getParamFileType().value_);
        file.usedCapacity = array[i].getUsedCapacity();
        file.totalCapacity = array[i].getTotalCapacity();
        out.dynamicOutArray.push_back(std::move(file));

        LOGD("fillDVRFileCapacityInfoArray: paramFileTypeEnumDt = %d, usedCapacity = %d, totalCapacity = %d, len = %d",
             out.dynamicOutArray[i].paramFileTypeEnumDt ,out.dynamicOutArray[i].usedCapacity ,out.dynamicOutArray[i].totalCapacity ,len);
    }
}

void fillTFCardInfoList(DVRFileOperation::TFCardInfoList &list,TFCardInfoListOut &out) {
    int len = list.size();
    LOGI("fillTFCardInfoList: enter, len=%d", len);

    for (int i=0;i<len;i++) {
        TFCardInfoStruct_DT carInfoItem;
        carInfoItem.tfCardOptionDt = static_cast<TFCardOption_DT>(list[i].getTFCardOption().value_);
        carInfoItem.tfCardStatusDt = static_cast<TFCardStatus_DT>(list[i].getTFCardStatus().value_);
        carInfoItem.tfCardCapacityDt.remainingCapacity = list[i].getTFCardCapacity().getRemainingCapacity();
        carInfoItem.tfCardCapacityDt.totalCapacity = list[i].getTFCardCapacity().getTotalCapacity();
        out.dynamicList.push_back(std::move(carInfoItem));

        LOGD("fillTFCardInfoList: tfCardOptionDt = %d, tfCardStatusDt = %d, tfCardCapacityDt.remainingCapacity = %d, tfCardCapacityDt.totalCapacity = %d, len = %d",
             out.dynamicList[i].tfCardOptionDt,
             out.dynamicList[i].tfCardStatusDt,
             out.dynamicList[i].tfCardCapacityDt.remainingCapacity,
             out.dynamicList[i].tfCardCapacityDt.totalCapacity,
             len);
    }
}

void fillEMMCCapacityStruct(DVRFileOperation::EMMCCapacityStruct &capacityStruct,EMMCCapacityStructOut &out) {
    EMMCCapacityStruct_DT emmc;
    emmc.totalCapacity = capacityStruct.getTotalCapacity();
    emmc.remainingCapacity = capacityStruct.getRemainingCapacity();
    out.dynamicList.push_back(std::move(emmc));

    LOGD("fillEMMCCapacityStruct: totalCapacity = %d, remainingCapacity = %d",
            out.dynamicList[0].totalCapacity ,out.dynamicList[0].remainingCapacity);
}

CallStatus_DT StartVideoBrowseFunc(AccessType_DT VideoBrowseChannel, SetResultVideoBrowseOut &out){
    CommonAPI::CallStatus callStatus;

    DVRFileOperation::AccessType type;
    type.value_ = VideoBrowseChannel;

    DVRFileOperation::SetResult result;

    gDVRFileOperationProxy->StartVideoBrowse(type ,callStatus ,result);

    out.videoBrowseACKDt = static_cast<SetResult_DT>(result.value_);

    LOGD("StartVideoBrowseFunc: out = %d, callStatus = %d",out.videoBrowseACKDt, static_cast<CallStatus_DT>(callStatus));
    return static_cast<CallStatus_DT>(callStatus);
}

CallStatus_DT StopVideoBrowseFunc(AccessType_DT VideoBrowseChannel, SetResultVideoBrowseOut &out){
    CommonAPI::CallStatus callStatus;

    DVRFileOperation::AccessType type;
    type.value_ = VideoBrowseChannel;

    DVRFileOperation::SetResult result;

    gDVRFileOperationProxy->StopVideoBrowse(type ,callStatus ,result);

    out.videoBrowseACKDt = static_cast<SetResult_DT>(result.value_);

    LOGD("StopVideoBrowseFunc: out = %d, callStatus = %d",out.videoBrowseACKDt, static_cast<CallStatus_DT>(callStatus));
    return static_cast<CallStatus_DT>(callStatus);
}

//CallStatus_DT StartOMCVideoBrowseFunc(AccessType_DT OMCVideoBrowseChannel, SetResultOMCVideoBrowseACKOut &out){
//    CommonAPI::CallStatus callStatus;
//
//    DVRFileOperation::AccessType type;
//    type.value_ = OMCVideoBrowseChannel;
//
//    DVRFileOperation::SetResult result;
//
//    gDVRFileOperationProxy->StartOMCVideoBrowse(type ,callStatus ,result);
//
//    out.oMCVideoBrowseACKDt = static_cast<SetResult_DT>(result.value_);
//
//    LOGD("StartOMCVideoBrowseFunc: out = %d, callStatus = %d",out.oMCVideoBrowseACKDt, static_cast<CallStatus_DT>(callStatus));
//    return static_cast<CallStatus_DT>(callStatus);
//}

//CallStatus_DT StopOMCVideoBrowseFunc(AccessType_DT OMCVideoBrowseChannel, SetResultOMCVideoBrowseACKOut &out){
//    CommonAPI::CallStatus callStatus;
//
//    DVRFileOperation::AccessType type;
//    type.value_ = OMCVideoBrowseChannel;
//
//    DVRFileOperation::SetResult result;
//
//    gDVRFileOperationProxy->StopOMCVideoBrowse(type ,callStatus ,result);
//
//    out.oMCVideoBrowseACKDt = static_cast<SetResult_DT>(result.value_);
//
//    LOGD("StopOMCVideoBrowseFunc: out = %d, callStatus = %d",out.oMCVideoBrowseACKDt, static_cast<CallStatus_DT>(callStatus));
//    return static_cast<CallStatus_DT>(callStatus);
//}

CallStatus_DT FileListRequestFunc(FileType_DT FileType, AccessType_DT AccessType, FileNumber FileNumber, const char *FileName, FileListStructArrayOut &out){
    CommonAPI::CallStatus callStatus;

    DVRFileOperation::FileType fileType;
    fileType.value_ = FileType;

    DVRFileOperation::AccessType accessType;
    accessType.value_ = AccessType;

    DVRFileOperation::FileListStructArray array;
    std::string fileName(FileName);

    gDVRFileOperationProxy->FileListRequest(fileType ,accessType ,FileNumber ,fileName ,callStatus ,array);

    int len = array.size();
    if(len == 0){
        LOGI("FileListRequestFunc: out.len == 0 callStatus = %d, FileType = %d , AccessType = %d , FileNumber = %d ,fileName = %s ",static_cast<CallStatus_DT>(callStatus),fileType.value_,accessType.value_,FileNumber,fileName.c_str());
        return static_cast<CallStatus_DT>(callStatus);
    }
    fillFileListStructArray(array,out);
    LOGD("FileListRequestFunc: callStatus = %d, FileType = %d , AccessType = %d , FileNumber = %d ,fileName = %s , out.len = %lu",
        static_cast<CallStatus_DT>(callStatus),fileType.value_,accessType.value_,FileNumber,fileName.c_str(),out.dynamicArray.size());
    return static_cast<CallStatus_DT>(callStatus);
}

CallStatus_DT FileListIncludeDateReqFunc(FileType_DT FileType, AccessType_DT AccessType, FileNumber FileNumber, const char *FileName, FileListIncludeDateArrayOut &out){
    CommonAPI::CallStatus callStatus;

    DVRFileOperation::FileType fileType;
    fileType.value_ = FileType;

    DVRFileOperation::AccessType accessType;
    accessType.value_ = AccessType;

    DVRFileOperation::FileListIncludeDate_Array array;
    std::string fileName(FileName);

    gDVRFileOperationProxy->FileListIncludeDateReq(fileType ,accessType ,FileNumber ,fileName ,callStatus ,array);

    int len = array.size();
    if(len == 0){
        LOGI("FileListIncludeDateReqFunc: out.len == 0 callStatus = %d, FileType = %d , AccessType = %d , FileNumber = %d ,fileName = %s ",static_cast<CallStatus_DT>(callStatus),fileType.value_,accessType.value_,FileNumber,fileName.c_str());
        return static_cast<CallStatus_DT>(callStatus);
    }
    fillFileListIncludeDateArray(array,out);
    LOGD("FileListIncludeDateReqFunc: callStatus = %d, FileType = %d , AccessType = %d , FileNumber = %d ,fileName = %s , out.len = %lu",
        static_cast<CallStatus_DT>(callStatus),fileType.value_,accessType.value_,FileNumber,fileName.c_str(),out.dynamicOutArray.size());
    return static_cast<CallStatus_DT>(callStatus);
}

CallStatus_DT DVRFileCapacityInfoReqFunc(TFAllFileCapacityEnum_DT tfAllFileCapacity,TFCardFileTypeListArrayInput &list,FileCapacityListArrayOut &out){
    CommonAPI::CallStatus callStatus;

    DVRFileOperation::TFAllFileCapacity_Enum capacity;
    capacity.value_ = tfAllFileCapacity;
    
    DVRFileOperation::TFCardFileTypeList_Array tfCardFileTypeList(list.dynamicInArray.size());

    for (int i = 0; i < list.dynamicInArray.size(); ++i) {
        tfCardFileTypeList[i].value_ = list.dynamicInArray[i];
    }

    DVRFileOperation::FileCapacityList_Array array;
    gDVRFileOperationProxy->DVRFileCapacityInfoReq(capacity, tfCardFileTypeList, callStatus, array);

    int len = array.size();
    if(len == 0){
        LOGI("DVRFileCapacityInfoReqFunc: out.len == 0 callStatus = %d",static_cast<CallStatus_DT>(callStatus));
        return static_cast<CallStatus_DT>(callStatus);
    }
    fillDVRFileCapacityInfoArray(array,out);
    LOGD("DVRFileCapacityInfoReqFunc: callStatus = %d, out.len = %lu",static_cast<CallStatus_DT>(callStatus), out.dynamicOutArray.size());
    return static_cast<CallStatus_DT>(callStatus);
}

CallStatus_DT SDCardFormatFunc(SDCardOption_DT SDCardOption, SetResultTFCardFormatACKOut &out){
    CommonAPI::CallStatus callStatus;

    DVRFileOperation::SDCardOption option;
    option.value_ = SDCardOption;

    DVRFileOperation::SetResult result;

    CommonAPI::CallInfo callInfo;
    callInfo.timeout_ = 10*1000;

    gDVRFileOperationProxy->SDCardFormat(option ,callStatus , result , &callInfo);

    out.tFCardFormatACKDt = static_cast<SetResult_DT>(result.value_);

    LOGD("SDCardFormatFunc: out = %d, callStatus = %d",out.tFCardFormatACKDt, static_cast<CallStatus_DT>(callStatus));
    return static_cast<CallStatus_DT>(callStatus);
}

CallStatus_DT FileDeleteRequestFunc(FileListPath_DT fileListPathDt, SetResultFileDeleteACKOut &out){
    CommonAPI::CallStatus callStatus;

    DVRFileOperation::FileListPath path;
    // LOGD("FileDeleteRequestFunc: fileListPathDt.len = %d",fileListPathDt.len);

    for (int i = 0; i < fileListPathDt.filePath.size(); ++i) {
        LOGD("FileDeleteRequestFunc: filePath = %s",fileListPathDt.filePath[i].c_str());
        path.push_back(fileListPathDt.filePath[i]);
    }

    DVRFileOperation::SetResult result;

    gDVRFileOperationProxy->FileDeleteRequest(path ,callStatus , result);

    out.fileDeleteACKDt = static_cast<SetResult_DT>(result.value_);

    LOGD("FileDeleteRequestFunc: out = %d, callStatus = %d",out.fileDeleteACKDt, static_cast<CallStatus_DT>(callStatus));
    return static_cast<CallStatus_DT>(callStatus);
}

CallStatus_DT AllFileDeleteRequestFunc(AccessType_DT AccessType, FileType_DT FileType, SetResultFileDeleteACKOut &out){
    CommonAPI::CallStatus callStatus;

    DVRFileOperation::AccessType accessType;
    accessType.value_ = AccessType;

    DVRFileOperation::FileType fileType;
    fileType.value_ = FileType;

    DVRFileOperation::SetResult result;

    gDVRFileOperationProxy->AllFileDeleteRequest(accessType ,fileType ,callStatus ,result);

    out.fileDeleteACKDt = static_cast<SetResult_DT>(result.value_);

    LOGD("AllFileDeleteRequestFunc: out = %d, callStatus = %d",out.fileDeleteACKDt, static_cast<CallStatus_DT>(callStatus));
    return static_cast<CallStatus_DT>(callStatus);
}

CallStatus_DT AsyncAllFileDeleteRequestFuc(AccessType_DT accessTypeDt, FileType_DT fileTypeDt, SetResultFileDeleteACKOut &out){
    CommonAPI::CallStatus callStatus;

    DVRFileOperation::AccessType accessType;
    accessType.value_ = accessTypeDt;

    DVRFileOperation::FileType fileType;
    fileType.value_ = fileTypeDt;

    DVRFileOperation::SetResult result;

    gDVRFileOperationProxy->AsyncAllFileDeleteRequest(accessType ,fileType ,callStatus ,result);

    out.fileDeleteACKDt = static_cast<SetResult_DT>(result.value_);

    LOGD("AsyncAllFileDeleteRequestFuc: out = %d, callStatus = %d",out.fileDeleteACKDt, static_cast<CallStatus_DT>(callStatus));
    return static_cast<CallStatus_DT>(callStatus);
}

CallStatus_DT FileExportRequestFunc(ExportMode_DT ExportMode, FileListPath_DT fileListPathDt, ExportFileACKOut &out){
    CommonAPI::CallStatus callStatus;

    DVRFileOperation::ExportMode mode;
    mode.value_ = ExportMode;

    DVRFileOperation::FileListPath path;
    // LOGD("FileExportRequestFunc: fileListPathDt.len = %d ",fileListPathDt.len);

    for (int i = 0; i < fileListPathDt.filePath.size(); ++i) {
        LOGD("FileExportRequestFunc: filePath = %s ",fileListPathDt.filePath[i].c_str());
        path.push_back(fileListPathDt.filePath[i]);
    }

    DVRFileOperation::ExportFileACK file;
    gDVRFileOperationProxy->FileExportRequest(mode ,path ,callStatus ,file);

    out.exportFileACKDt = static_cast<ExportFileACK_DT>(file.value_);

    LOGD("FileExportRequestFunc: out = %d, callStatus = %d",out.exportFileACKDt, static_cast<CallStatus_DT>(callStatus));
    return static_cast<CallStatus_DT>(callStatus);
}
CallStatus_DT SelectAllFileCapacityRequestFunc(AccessType_DT AccessType_In, FileType_DT FileType_In, AccessTypeOut &accessTypeOut, FileTypeOut &fileTypeOut, int &selectAllFileCapacity){

    CommonAPI::CallStatus callStatus;

    DVRFileOperation::AccessType accessType_in;
    accessType_in.value_ = AccessType_In;

    DVRFileOperation::FileType fileType_in;
    fileType_in.value_ = FileType_In;

    DVRFileOperation::AccessType accessType_out;

    DVRFileOperation::FileType fileType_out;

    DVRFileOperation::SelectAllFileCapacity fileCapacity;

    gDVRFileOperationProxy->SelectAllFileCapacityRequest(accessType_in ,fileType_in ,callStatus ,accessType_out ,fileType_out ,fileCapacity);

    accessTypeOut.accessTypeDT = static_cast<AccessType_DT>(accessType_out.value_);

    fileTypeOut.fileTypeDt = static_cast<FileType_DT>(fileType_out.value_);

    selectAllFileCapacity = fileCapacity;

    LOGD("SelectAllFileCapacityRequestFunc: AccessType_Out = %d, FileType_Out = %d, SelectAllFileCapacity = %d, callStatus = %d",accessTypeOut.accessTypeDT, accessTypeOut.accessTypeDT, selectAllFileCapacity,static_cast<CallStatus_DT>(callStatus));

    return static_cast<CallStatus_DT>(callStatus);
}

CallStatus_DT AllFileExportRequestFunc(ExportMode_DT ExportMode, AccessType_DT AccessType, FileType_DT FileType, ExportFileACKOut &out){
    CommonAPI::CallStatus callStatus;

    DVRFileOperation::ExportMode mode;
    mode.value_ = ExportMode;

    DVRFileOperation::AccessType accessType;
    accessType.value_ = AccessType;

    DVRFileOperation::FileType fileType;
    fileType.value_ = FileType;

    DVRFileOperation::ExportFileACK exportFileACK;

    gDVRFileOperationProxy->AllFileExportRequest(mode ,accessType ,fileType ,callStatus ,exportFileACK);

    out.exportFileACKDt = static_cast<ExportFileACK_DT>(exportFileACK.value_);

    LOGD("AllFileExportRequestFunc: out = %d, callStatus = %d",out.exportFileACKDt, static_cast<CallStatus_DT>(callStatus));

    return static_cast<CallStatus_DT>(callStatus);
}

CallStatus_DT TFCardInfoQueryFunc(GetAllInfo_DT GetAllInfo, TFCardOptionList &TFCardOptionList, TFCardInfoListOut &out){
    CommonAPI::CallStatus callStatus;

    DVRFileOperation::GetAllInfo info;
    info.value_ = GetAllInfo;

    DVRFileOperation::TFCardOptionList optionList;
    for (int i = 0; i < TFCardOptionList.dynamicList.size(); ++i) {
        DVRFileOperation::TFCardOption option;
        option.value_ = TFCardOptionList.dynamicList[i].tfCardOptionDt;
        optionList.push_back(option);
        LOGD("tfCardOptionDt = %d ",TFCardOptionList.dynamicList[i].tfCardOptionDt);
    }

    DVRFileOperation::TFCardInfoList list;

    gDVRFileOperationProxy->TFCardInfoQuery(info ,optionList ,callStatus ,list);

    int len = list.size();
    if(len == 0){
        LOGI("TFCardInfoQueryFunc: out.len == 0 callStatus = %d",static_cast<CallStatus_DT>(callStatus));
        return static_cast<CallStatus_DT>(callStatus);
    }
    fillTFCardInfoList(list,out);
    LOGD("TFCardInfoQueryFunc: callStatus = %d, out.len = %lu",static_cast<CallStatus_DT>(callStatus), out.dynamicList.size());
    return static_cast<CallStatus_DT>(callStatus);
}

CallStatus_DT EMMCInfoQueryFunc(GetAllInfo_DT GetAllInfo, EMMCStatus_DT EMMCStatus, EMMCCapacityStructOut &out) {
    CommonAPI::CallStatus callStatus;

    DVRFileOperation::GetAllInfo info;
    info.value_ = GetAllInfo;

    DVRFileOperation::EMMCStatus status;

    DVRFileOperation::EMMCCapacityStruct capacityStruct;

    gDVRFileOperationProxy->EMMCInfoQuery(info, callStatus, status, capacityStruct);

    EMMCStatus = static_cast<EMMCStatus_DT>(status.value_);

    LOGD("EMMCInfoQueryFunc: getTotalCapacity = %d ,  getRemainingCapacity = %d EMMCStatus = %d",capacityStruct.getTotalCapacity() ,capacityStruct.getRemainingCapacity() ,EMMCStatus);
    fillEMMCCapacityStruct(capacityStruct, out);
    LOGD("EMMCInfoQueryFunc: callStatus = %d, out.len = %lu", static_cast<CallStatus_DT>(callStatus), out.dynamicList.size());
    return static_cast<CallStatus_DT>(callStatus);
}

CallStatus_DT SelectFileCapacityRequestFuc(FileListPath_DT fileListPathDt , SetResult_DT &setResultDt , FileCapacity &fileCapacity){
    CommonAPI::CallStatus callStatus;

    DVRFileOperation::FileListPath path;
    // LOGD("SelectFileCapacityRequestFuc: fileListPathDt.len = %d ",fileListPathDt.len);

    for (int i = 0; i < fileListPathDt.filePath.size(); ++i) {
        LOGD("SelectFileCapacityRequestFuc: filePath = %s ",fileListPathDt.filePath[i].c_str());
        path.push_back(fileListPathDt.filePath[i]);
    }

    DVRFileOperation::SetResult result;

    DVRFileOperation::FileCapacity capacity;

    gDVRFileOperationProxy->SelectFileCapacityRequest(path , callStatus , result , capacity);

    setResultDt = static_cast<SetResult_DT>(result.value_);

    fileCapacity = capacity;

    LOGD("SelectFileCapacityRequestFuc: callStatus = %d, setResultDt = %d , fileCapacity = %d ", static_cast<CallStatus_DT>(callStatus), setResultDt , fileCapacity);

    return static_cast<CallStatus_DT>(callStatus);
}

CallStatus_DT RecordEventStatusRequestFuc(AccessType_DT accessTypeDt , RecordStatus_DT &recordStatusDt , EventType_DT &eventTypeDt){
    CommonAPI::CallStatus callStatus;

    DVRFileOperation::AccessType accessType;
    accessType.value_ = accessTypeDt;

    DVRFileOperation::RecordStatus status;

    DVRFileOperation::EventType type;

    gDVRFileOperationProxy->RecordEventStatusRequest(accessType , callStatus , status , type);

    recordStatusDt = static_cast<RecordStatus_DT>(status.value_);

    eventTypeDt = static_cast<EventType_DT>(type.value_);

    LOGD("RecordEventStatusRequestFuc: callStatus = %d, accessTypeDt = %d , recordStatusDt = %d , eventTypeDt = %d ", static_cast<CallStatus_DT>(callStatus), accessTypeDt , recordStatusDt , eventTypeDt);

    return static_cast<CallStatus_DT>(callStatus);
}