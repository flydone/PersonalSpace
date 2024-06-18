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

#ifndef DVR_VIMS_DVRFILEOPERATION_H
#define DVR_VIMS_DVRFILEOPERATION_H

#include "public_def.h"
#include <string>

typedef __uint8_t FileNumber;
typedef __uint32_t SelectAllFileCapacity;
typedef __uint32_t FileCapacity;
typedef __int32_t UsedCapacity_Integer;
typedef __int32_t TotalCapacity_Integer;
using namespace std;

typedef enum {
    E_NORMALVIDEO = 0,
    E_EVENTVIDEO = 1,
    E_USERDATA = 2,
    E_EXPORTDATA = 3,
    E_SENTINELMODE = 4,
    E_GUARDIANMODE_F = 5
}FileType_DT;

typedef enum {
    E_SDCARD1 = 0,
    E_SDCARD2 = 1
}SDCardOption_DT;

typedef enum {
    E_FILTERMODE = 0,
    E_COVERMODE = 1,
    E_COPYMODE = 2
}ExportMode_DT;

typedef enum {
    E_EXPORTSUCCESS = 0,
    E_FILEMISSING = 1,
    E_CAPACITYWARNING = 2,
    E_ISDELETING = 3,
    E_OTHERREASON = 4
}ExportFileACK_DT;

typedef enum {
    E_GET_ALL_INFO = 0,
    E_GET_ARRAY_INFO = 1
}GetAllInfo_DT;

typedef enum {
    E_INACTIVE = 0,
    E_ACTIVE = 1
}RecordStatus_DT;

typedef enum {
    E_GET_ALL_FILE_TYPE_CAPACITY = 0,
    E_GET_ARRAY_CAPACITY = 1
}TFAllFileCapacityEnum_DT;

typedef enum {
    E_CUSTOMDATE = 0,
    E_EXPORTDATA_P = 1,
    E_SENTINELDATA = 2,
    E_GUARDDATA = 3
}ParamFileTypeEnum_DT;

struct ParamFileCapacityStruct_DT {
    public:
        ParamFileCapacityStruct_DT() {
        };

        ~ParamFileCapacityStruct_DT() {
        }

    public:
        ParamFileTypeEnum_DT paramFileTypeEnumDt;
        UsedCapacity_Integer usedCapacity;
        TotalCapacity_Integer totalCapacity;
};

struct FileListIncludeDateStruct_DT {
    public:
        FileListIncludeDateStruct_DT(){
        }
        ~FileListIncludeDateStruct_DT(){
        }

    public:
    std::string filePath = "";
    std::string thumbnailPath = "";
    FileType_DT fileTypeDt;
    AccessType_DT accessTypeDt;
    std::string eventTime = "";
	FileNumber fileNumber;
};

struct TFCardFileTypeListArrayInput {
    public:
        TFCardFileTypeListArrayInput() {
        };

        ~TFCardFileTypeListArrayInput() {
        }

    public:
    vector<ParamFileTypeEnum_DT> dynamicInArray;
};

struct FileCapacityListArrayOut {
    public:
        FileCapacityListArrayOut() {
        };

        ~FileCapacityListArrayOut() {
        }

    public:
    vector<ParamFileCapacityStruct_DT> dynamicOutArray;
};

struct FileListIncludeDateArrayOut {
    public:
        FileListIncludeDateArrayOut() {
        };

        ~FileListIncludeDateArrayOut() {
        }

    public:
    vector<FileListIncludeDateStruct_DT> dynamicOutArray;
};

struct FileListPath_DT {
    public:
        FileListPath_DT() {
        };

        ~FileListPath_DT() {
        }

    public:
        vector<string> filePath;
};

struct FileListStruct_DT{
    public:
        FileListStruct_DT(){
        }
        ~FileListStruct_DT(){
        }

    public:
    std::string filePath = "";
    std::string thumbnailPath = "";
    FileType_DT fileTypeDt;
    AccessType_DT accessTypeDt;
};

struct FileListStructArrayOut{
    public:
        FileListStructArrayOut(){
        }
        ~FileListStructArrayOut(){
        }

    public:
        std::vector<FileListStruct_DT> dynamicArray;
};

struct TFCardInfoStruct_DT{
    TFCardOption_DT tfCardOptionDt;
    TFCardStatus_DT tfCardStatusDt;
    TFCardCapacity_DT tfCardCapacityDt;
};

struct EMMCCapacityStructOut{
    public:
        EMMCCapacityStructOut(){
        }
        ~EMMCCapacityStructOut(){
        }

    public:
    std::vector<EMMCCapacityStruct_DT> dynamicList;
};

struct TFCardInfoListOut{
    public:
        TFCardInfoListOut(){
        }
        ~TFCardInfoListOut(){
        }

    public:
        std::vector<TFCardInfoStruct_DT> dynamicList;
};

struct SetResultVideoBrowseOut{
    SetResult_DT videoBrowseACKDt;
};

struct SetResultOMCVideoBrowseACKOut{
    SetResult_DT oMCVideoBrowseACKDt;
};

struct SetResultTFCardFormatACKOut{
    SetResult_DT tFCardFormatACKDt;
};

struct SetResultFileDeleteACKOut{
    SetResult_DT fileDeleteACKDt;
};

struct ExportFileACKOut{
    ExportFileACK_DT exportFileACKDt;
};

struct AccessTypeOut{
    AccessType_DT accessTypeDT;
};

struct FileTypeOut{
    FileType_DT fileTypeDt;
};

struct TFCardOptionList_DT{
    TFCardOption_DT tfCardOptionDt;
};

struct TFCardOptionList{
    public:
        TFCardOptionList(){
        }
        ~TFCardOptionList(){
        }

    public:
        std::vector<TFCardOptionList_DT> dynamicList;
};

void DVRFileOperationInit(char *appName, char *configFile);
bool DVRFileOperationIsReady();

CallStatus_DT StartVideoBrowseFunc(AccessType_DT VideoBrowseChannel, SetResultVideoBrowseOut &out);
CallStatus_DT StopVideoBrowseFunc(AccessType_DT VideoBrowseChannel, SetResultVideoBrowseOut &out);
//CallStatus_DT StartOMCVideoBrowseFunc(AccessType_DT OMCVideoBrowseChannel, SetResultOMCVideoBrowseACKOut &out);
//CallStatus_DT StopOMCVideoBrowseFunc(AccessType_DT OMCVideoBrowseChannel, SetResultOMCVideoBrowseACKOut &out);
CallStatus_DT FileListRequestFunc(FileType_DT FileType, AccessType_DT AccessType, FileNumber FileNumber, const char *FileName, FileListStructArrayOut &out);
CallStatus_DT SDCardFormatFunc(SDCardOption_DT SDCardOption, SetResultTFCardFormatACKOut &out);
CallStatus_DT FileDeleteRequestFunc(FileListPath_DT fileListPathDt, SetResultFileDeleteACKOut &out);
CallStatus_DT AllFileDeleteRequestFunc(AccessType_DT AccessType, FileType_DT FileType, SetResultFileDeleteACKOut &out);
CallStatus_DT AsyncAllFileDeleteRequestFuc(AccessType_DT accessTypeDt, FileType_DT fileTypeDt, SetResultFileDeleteACKOut &out);
CallStatus_DT FileExportRequestFunc(ExportMode_DT ExportMode, FileListPath_DT fileListPathDt, ExportFileACKOut &out);
CallStatus_DT SelectAllFileCapacityRequestFunc(AccessType_DT AccessType_In, FileType_DT FileType_In, AccessTypeOut &accessTypeOut, FileTypeOut &fileTypeOut, int &selectAllFileCapacity);
CallStatus_DT AllFileExportRequestFunc(ExportMode_DT ExportMode, AccessType_DT AccessType, FileType_DT FileType, ExportFileACKOut &out);
CallStatus_DT TFCardInfoQueryFunc(GetAllInfo_DT GetAllInfo, TFCardOptionList &TFCardOptionList, TFCardInfoListOut &out);
CallStatus_DT EMMCInfoQueryFunc(GetAllInfo_DT GetAllInfo, EMMCStatus_DT EMMCStatus, EMMCCapacityStructOut &out);

CallStatus_DT SelectFileCapacityRequestFuc(FileListPath_DT fileListPathDt , SetResult_DT &setResultDt , FileCapacity &fileCapacity);
CallStatus_DT RecordEventStatusRequestFuc(AccessType_DT accessTypeDt , RecordStatus_DT &recordStatusDt , EventType_DT &eventTypeDt);
CallStatus_DT DVRFileCapacityInfoReqFunc(TFAllFileCapacityEnum_DT tfAllFileCapacity , TFCardFileTypeListArrayInput &list , FileCapacityListArrayOut &out);
CallStatus_DT FileListIncludeDateReqFunc(FileType_DT FileType, AccessType_DT AccessType, FileNumber FileNumber, const char *FileName, FileListIncludeDateArrayOut &out);

#endif //DVR_VIMS_DVRFILEOPERATION_H
