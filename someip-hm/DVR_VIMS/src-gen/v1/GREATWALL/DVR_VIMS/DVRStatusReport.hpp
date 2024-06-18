/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.1.12.v202002200719.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#ifndef V1_GREATWALL_DVR_VIMS_DVR_STATUS_REPORT_HPP_
#define V1_GREATWALL_DVR_VIMS_DVR_STATUS_REPORT_HPP_




#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/Deployment.hpp>
#include <CommonAPI/InputStream.hpp>
#include <CommonAPI/OutputStream.hpp>
#include <CommonAPI/Struct.hpp>
#include <CommonAPI/Types.hpp>
#include <cstdint>
#include <string>
#include <vector>

#undef COMMONAPI_INTERNAL_COMPILATION

namespace v1 {
namespace GREATWALL {
namespace DVR_VIMS {

class DVRStatusReport {
public:
    virtual ~DVRStatusReport() { }

    static inline const char* getInterface();
    static inline CommonAPI::Version getInterfaceVersion();
    
    struct TFCardStatus : CommonAPI::Enumeration< uint8_t> {
        enum Literal : uint8_t {
            E_DVR_NOT_FOUND = 0,
            E_DVR_FAULT = 1,
            E_DVR_MEMEORY_FULL = 2,
            E_DVR_OK = 3,
            E_WRITESLOWLY = 4,
            E_DVR_EMERGENCY_SPACE_FULL = 5,
            E_DVR_CAPACITY_NOT_SUPPORTED = 6
        };
    
        TFCardStatus()
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(Literal::E_DVR_NOT_FOUND)) {}
        TFCardStatus(Literal _literal)
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(_literal)) {}
    
        inline bool validate() const {
            switch (value_) {
                case static_cast< uint8_t>(Literal::E_DVR_NOT_FOUND):
                case static_cast< uint8_t>(Literal::E_DVR_FAULT):
                case static_cast< uint8_t>(Literal::E_DVR_MEMEORY_FULL):
                case static_cast< uint8_t>(Literal::E_DVR_OK):
                case static_cast< uint8_t>(Literal::E_WRITESLOWLY):
                case static_cast< uint8_t>(Literal::E_DVR_EMERGENCY_SPACE_FULL):
                case static_cast< uint8_t>(Literal::E_DVR_CAPACITY_NOT_SUPPORTED):
                return true;
            default:
                return false;
            }
        }
    
        inline bool operator==(const TFCardStatus &_other) const { return (value_ == _other.value_); }
        inline bool operator!=(const TFCardStatus &_other) const { return (value_ != _other.value_); }
        inline bool operator<=(const TFCardStatus &_other) const { return (value_ <= _other.value_); }
        inline bool operator>=(const TFCardStatus &_other) const { return (value_ >= _other.value_); }
        inline bool operator<(const TFCardStatus &_other) const { return (value_ < _other.value_); }
        inline bool operator>(const TFCardStatus &_other) const { return (value_ > _other.value_); }
    
        inline bool operator==(const Literal &_value) const { return (value_ == static_cast< uint8_t>(_value)); }
        inline bool operator!=(const Literal &_value) const { return (value_ != static_cast< uint8_t>(_value)); }
        inline bool operator<=(const Literal &_value) const { return (value_ <= static_cast< uint8_t>(_value)); }
        inline bool operator>=(const Literal &_value) const { return (value_ >= static_cast< uint8_t>(_value)); }
        inline bool operator<(const Literal &_value) const { return (value_ < static_cast< uint8_t>(_value)); }
        inline bool operator>(const Literal &_value) const { return (value_ > static_cast< uint8_t>(_value)); }
    };
    
    struct EventOperationType : CommonAPI::Enumeration< uint8_t> {
        enum Literal : uint8_t {
            E_EVENTSTART = 0,
            E_EVENTSTOP = 1,
            E_EVENTFAILED = 2
        };
    
        EventOperationType()
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(Literal::E_EVENTSTART)) {}
        EventOperationType(Literal _literal)
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(_literal)) {}
    
        inline bool validate() const {
            switch (value_) {
                case static_cast< uint8_t>(Literal::E_EVENTSTART):
                case static_cast< uint8_t>(Literal::E_EVENTSTOP):
                case static_cast< uint8_t>(Literal::E_EVENTFAILED):
                return true;
            default:
                return false;
            }
        }
    
        inline bool operator==(const EventOperationType &_other) const { return (value_ == _other.value_); }
        inline bool operator!=(const EventOperationType &_other) const { return (value_ != _other.value_); }
        inline bool operator<=(const EventOperationType &_other) const { return (value_ <= _other.value_); }
        inline bool operator>=(const EventOperationType &_other) const { return (value_ >= _other.value_); }
        inline bool operator<(const EventOperationType &_other) const { return (value_ < _other.value_); }
        inline bool operator>(const EventOperationType &_other) const { return (value_ > _other.value_); }
    
        inline bool operator==(const Literal &_value) const { return (value_ == static_cast< uint8_t>(_value)); }
        inline bool operator!=(const Literal &_value) const { return (value_ != static_cast< uint8_t>(_value)); }
        inline bool operator<=(const Literal &_value) const { return (value_ <= static_cast< uint8_t>(_value)); }
        inline bool operator>=(const Literal &_value) const { return (value_ >= static_cast< uint8_t>(_value)); }
        inline bool operator<(const Literal &_value) const { return (value_ < static_cast< uint8_t>(_value)); }
        inline bool operator>(const Literal &_value) const { return (value_ > static_cast< uint8_t>(_value)); }
    };
    
    struct DVRSystemStatus : CommonAPI::Enumeration< uint8_t> {
        enum Literal : uint8_t {
            E_DVR_OK = 0,
            E_DVR_FAULT = 1
        };
    
        DVRSystemStatus()
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(Literal::E_DVR_OK)) {}
        DVRSystemStatus(Literal _literal)
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(_literal)) {}
    
        inline bool validate() const {
            switch (value_) {
                case static_cast< uint8_t>(Literal::E_DVR_OK):
                case static_cast< uint8_t>(Literal::E_DVR_FAULT):
                return true;
            default:
                return false;
            }
        }
    
        inline bool operator==(const DVRSystemStatus &_other) const { return (value_ == _other.value_); }
        inline bool operator!=(const DVRSystemStatus &_other) const { return (value_ != _other.value_); }
        inline bool operator<=(const DVRSystemStatus &_other) const { return (value_ <= _other.value_); }
        inline bool operator>=(const DVRSystemStatus &_other) const { return (value_ >= _other.value_); }
        inline bool operator<(const DVRSystemStatus &_other) const { return (value_ < _other.value_); }
        inline bool operator>(const DVRSystemStatus &_other) const { return (value_ > _other.value_); }
    
        inline bool operator==(const Literal &_value) const { return (value_ == static_cast< uint8_t>(_value)); }
        inline bool operator!=(const Literal &_value) const { return (value_ != static_cast< uint8_t>(_value)); }
        inline bool operator<=(const Literal &_value) const { return (value_ <= static_cast< uint8_t>(_value)); }
        inline bool operator>=(const Literal &_value) const { return (value_ >= static_cast< uint8_t>(_value)); }
        inline bool operator<(const Literal &_value) const { return (value_ < static_cast< uint8_t>(_value)); }
        inline bool operator>(const Literal &_value) const { return (value_ > static_cast< uint8_t>(_value)); }
    };
    typedef uint8_t TimelapseVideoInterval;
    typedef std::string FilePath;
    typedef uint8_t CurrentTransProgress;
    struct ExportFileInfoStruct : CommonAPI::Struct< CurrentTransProgress, FilePath> {
    
        ExportFileInfoStruct()
        {
            std::get< 0>(values_) = CurrentTransProgress();
            std::get< 1>(values_) = FilePath();
        }
        ExportFileInfoStruct(const CurrentTransProgress &_CurrentTransProgress, const FilePath &_FilePath)
        {
            std::get< 0>(values_) = _CurrentTransProgress;
            std::get< 1>(values_) = _FilePath;
        }
        inline const CurrentTransProgress &getCurrentTransProgress() const { return std::get< 0>(values_); }
        inline void setCurrentTransProgress(const CurrentTransProgress &_value) { std::get< 0>(values_) = _value; }
        inline const FilePath &getFilePath() const { return std::get< 1>(values_); }
        inline void setFilePath(const FilePath &_value) { std::get< 1>(values_) = _value; }
        inline bool operator==(const ExportFileInfoStruct& _other) const {
        return (getCurrentTransProgress() == _other.getCurrentTransProgress() && getFilePath() == _other.getFilePath());
        }
        inline bool operator!=(const ExportFileInfoStruct &_other) const {
            return !((*this) == _other);
        }
    
    };
    
    struct TFCardOption : CommonAPI::Enumeration< uint8_t> {
        enum Literal : uint8_t {
            E_TFCARD1 = 0,
            E_TFCARD2 = 1
        };
    
        TFCardOption()
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(Literal::E_TFCARD1)) {}
        TFCardOption(Literal _literal)
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(_literal)) {}
    
        inline bool validate() const {
            switch (value_) {
                case static_cast< uint8_t>(Literal::E_TFCARD1):
                case static_cast< uint8_t>(Literal::E_TFCARD2):
                return true;
            default:
                return false;
            }
        }
    
        inline bool operator==(const TFCardOption &_other) const { return (value_ == _other.value_); }
        inline bool operator!=(const TFCardOption &_other) const { return (value_ != _other.value_); }
        inline bool operator<=(const TFCardOption &_other) const { return (value_ <= _other.value_); }
        inline bool operator>=(const TFCardOption &_other) const { return (value_ >= _other.value_); }
        inline bool operator<(const TFCardOption &_other) const { return (value_ < _other.value_); }
        inline bool operator>(const TFCardOption &_other) const { return (value_ > _other.value_); }
    
        inline bool operator==(const Literal &_value) const { return (value_ == static_cast< uint8_t>(_value)); }
        inline bool operator!=(const Literal &_value) const { return (value_ != static_cast< uint8_t>(_value)); }
        inline bool operator<=(const Literal &_value) const { return (value_ <= static_cast< uint8_t>(_value)); }
        inline bool operator>=(const Literal &_value) const { return (value_ >= static_cast< uint8_t>(_value)); }
        inline bool operator<(const Literal &_value) const { return (value_ < static_cast< uint8_t>(_value)); }
        inline bool operator>(const Literal &_value) const { return (value_ > static_cast< uint8_t>(_value)); }
    };
    typedef uint8_t PreRecordingTime;
    typedef uint8_t CaptureNumber;
    typedef uint32_t TotalExportCapacity;
    
    struct EMMCStatus : CommonAPI::Enumeration< uint8_t> {
        enum Literal : uint8_t {
            E_EMMCNORMAL = 0,
            E_EMMCFAULT = 1
        };
    
        EMMCStatus()
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(Literal::E_EMMCNORMAL)) {}
        EMMCStatus(Literal _literal)
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(_literal)) {}
    
        inline bool validate() const {
            switch (value_) {
                case static_cast< uint8_t>(Literal::E_EMMCNORMAL):
                case static_cast< uint8_t>(Literal::E_EMMCFAULT):
                return true;
            default:
                return false;
            }
        }
    
        inline bool operator==(const EMMCStatus &_other) const { return (value_ == _other.value_); }
        inline bool operator!=(const EMMCStatus &_other) const { return (value_ != _other.value_); }
        inline bool operator<=(const EMMCStatus &_other) const { return (value_ <= _other.value_); }
        inline bool operator>=(const EMMCStatus &_other) const { return (value_ >= _other.value_); }
        inline bool operator<(const EMMCStatus &_other) const { return (value_ < _other.value_); }
        inline bool operator>(const EMMCStatus &_other) const { return (value_ > _other.value_); }
    
        inline bool operator==(const Literal &_value) const { return (value_ == static_cast< uint8_t>(_value)); }
        inline bool operator!=(const Literal &_value) const { return (value_ != static_cast< uint8_t>(_value)); }
        inline bool operator<=(const Literal &_value) const { return (value_ <= static_cast< uint8_t>(_value)); }
        inline bool operator>=(const Literal &_value) const { return (value_ >= static_cast< uint8_t>(_value)); }
        inline bool operator<(const Literal &_value) const { return (value_ < static_cast< uint8_t>(_value)); }
        inline bool operator>(const Literal &_value) const { return (value_ > static_cast< uint8_t>(_value)); }
    };
    typedef std::string ThumbnailPath;
    typedef uint8_t TotalTransProgress;
    typedef uint32_t FileSize;
    typedef uint8_t TotalRecordingTime;
    
    struct AccessType : CommonAPI::Enumeration< uint8_t> {
        enum Literal : uint8_t {
            E_FORESIGHT = 0,
            E_WITHINSIGNT_OMC = 1,
            E_STREAMINGMEDIA_OR_BACKSIGNT_RESERVED = 2,
            E_360SURROUNDVIEW = 3,
            E_MULTICHANNEL = 4,
            E_WITHINSIGNT_DMC = 5
        };
    
        AccessType()
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(Literal::E_FORESIGHT)) {}
        AccessType(Literal _literal)
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(_literal)) {}
    
        inline bool validate() const {
            switch (value_) {
                case static_cast< uint8_t>(Literal::E_FORESIGHT):
                case static_cast< uint8_t>(Literal::E_WITHINSIGNT_OMC):
                case static_cast< uint8_t>(Literal::E_STREAMINGMEDIA_OR_BACKSIGNT_RESERVED):
                case static_cast< uint8_t>(Literal::E_360SURROUNDVIEW):
                case static_cast< uint8_t>(Literal::E_MULTICHANNEL):
                case static_cast< uint8_t>(Literal::E_WITHINSIGNT_DMC):
                return true;
            default:
                return false;
            }
        }
    
        inline bool operator==(const AccessType &_other) const { return (value_ == _other.value_); }
        inline bool operator!=(const AccessType &_other) const { return (value_ != _other.value_); }
        inline bool operator<=(const AccessType &_other) const { return (value_ <= _other.value_); }
        inline bool operator>=(const AccessType &_other) const { return (value_ >= _other.value_); }
        inline bool operator<(const AccessType &_other) const { return (value_ < _other.value_); }
        inline bool operator>(const AccessType &_other) const { return (value_ > _other.value_); }
    
        inline bool operator==(const Literal &_value) const { return (value_ == static_cast< uint8_t>(_value)); }
        inline bool operator!=(const Literal &_value) const { return (value_ != static_cast< uint8_t>(_value)); }
        inline bool operator<=(const Literal &_value) const { return (value_ <= static_cast< uint8_t>(_value)); }
        inline bool operator>=(const Literal &_value) const { return (value_ >= static_cast< uint8_t>(_value)); }
        inline bool operator<(const Literal &_value) const { return (value_ < static_cast< uint8_t>(_value)); }
        inline bool operator>(const Literal &_value) const { return (value_ > static_cast< uint8_t>(_value)); }
    };
    
    struct DVRSensorStatus : CommonAPI::Enumeration< uint8_t> {
        enum Literal : uint8_t {
            E_SENSOR_OK = 0,
            E_SENSOR_FAULT = 1,
            E_SENSOR_INIT = 2
        };
    
        DVRSensorStatus()
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(Literal::E_SENSOR_OK)) {}
        DVRSensorStatus(Literal _literal)
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(_literal)) {}
    
        inline bool validate() const {
            switch (value_) {
                case static_cast< uint8_t>(Literal::E_SENSOR_OK):
                case static_cast< uint8_t>(Literal::E_SENSOR_FAULT):
                case static_cast< uint8_t>(Literal::E_SENSOR_INIT):
                return true;
            default:
                return false;
            }
        }
    
        inline bool operator==(const DVRSensorStatus &_other) const { return (value_ == _other.value_); }
        inline bool operator!=(const DVRSensorStatus &_other) const { return (value_ != _other.value_); }
        inline bool operator<=(const DVRSensorStatus &_other) const { return (value_ <= _other.value_); }
        inline bool operator>=(const DVRSensorStatus &_other) const { return (value_ >= _other.value_); }
        inline bool operator<(const DVRSensorStatus &_other) const { return (value_ < _other.value_); }
        inline bool operator>(const DVRSensorStatus &_other) const { return (value_ > _other.value_); }
    
        inline bool operator==(const Literal &_value) const { return (value_ == static_cast< uint8_t>(_value)); }
        inline bool operator!=(const Literal &_value) const { return (value_ != static_cast< uint8_t>(_value)); }
        inline bool operator<=(const Literal &_value) const { return (value_ <= static_cast< uint8_t>(_value)); }
        inline bool operator>=(const Literal &_value) const { return (value_ >= static_cast< uint8_t>(_value)); }
        inline bool operator<(const Literal &_value) const { return (value_ < static_cast< uint8_t>(_value)); }
        inline bool operator>(const Literal &_value) const { return (value_ > static_cast< uint8_t>(_value)); }
    };
    struct DVRSensorStatusStruct : CommonAPI::Struct< AccessType, DVRSensorStatus> {
    
        DVRSensorStatusStruct()
        {
            std::get< 0>(values_) = AccessType();
            std::get< 1>(values_) = DVRSensorStatus();
        }
        DVRSensorStatusStruct(const AccessType &_AccessType, const DVRSensorStatus &_DVRSensorStatus)
        {
            std::get< 0>(values_) = _AccessType;
            std::get< 1>(values_) = _DVRSensorStatus;
        }
        inline const AccessType &getAccessType() const { return std::get< 0>(values_); }
        inline void setAccessType(const AccessType &_value) { std::get< 0>(values_) = _value; }
        inline const DVRSensorStatus &getDVRSensorStatus() const { return std::get< 1>(values_); }
        inline void setDVRSensorStatus(const DVRSensorStatus &_value) { std::get< 1>(values_) = _value; }
        inline bool operator==(const DVRSensorStatusStruct& _other) const {
        return (getAccessType() == _other.getAccessType() && getDVRSensorStatus() == _other.getDVRSensorStatus());
        }
        inline bool operator!=(const DVRSensorStatusStruct &_other) const {
            return !((*this) == _other);
        }
    
    };
    typedef uint8_t DVRTimelapseVideoPlayFrameNumber;
    
    struct EventType : CommonAPI::Enumeration< uint8_t> {
        enum Literal : uint8_t {
            E_MANUALCAPTURE_BYBUTTON = 0,
            E_MANUALCAPTURE_BYHUT = 1,
            E_MANUALRECORDING_BYBUTTON = 2,
            E_MANUALRECORDING_BYHUT = 3,
            E_TIMELAPSEVIDEO = 4,
            E_PARKINGMONITORVIDEO = 5,
            E_VEHICLECOLLISIONVIDEO = 6,
            E_AIRBAGEJECTIONVIDEO = 7,
            E_AEBVIDEO = 8,
            E_BURGLARALARMVIDEO = 9,
            E_CONTINUOUSCAPTURE = 10,
            E_SHORTVIDEORECORDING_BYBUTTON = 11,
            E_SHORTVIDEORECORDING_BYHUT = 12,
            E_APSVIDEO = 13,
            E_ACC_AEBVIDEO = 14,
            E_WHISTLEVIDEO = 15,
            E_RADARRINGINGVIDEO = 16,
            E_MEBVIDEO = 17,
            E_HANDLEFTVIDEO = 18,
            E_CARINGMODE = 19,
            E_EXPORTFILE = 20,
            E_GUARDIANMODE = 21,
            E_DELETEFILE = 22,
            E_MANUALCAPTURE_BYFINDCAR = 23,
            E_SENTINELMODE_HIGH = 24,
            E_SENTINELMODE_LOW = 25
        };
    
        EventType()
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(Literal::E_MANUALCAPTURE_BYBUTTON)) {}
        EventType(Literal _literal)
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(_literal)) {}
    
        inline bool validate() const {
            switch (value_) {
                case static_cast< uint8_t>(Literal::E_MANUALCAPTURE_BYBUTTON):
                case static_cast< uint8_t>(Literal::E_MANUALCAPTURE_BYHUT):
                case static_cast< uint8_t>(Literal::E_MANUALRECORDING_BYBUTTON):
                case static_cast< uint8_t>(Literal::E_MANUALRECORDING_BYHUT):
                case static_cast< uint8_t>(Literal::E_TIMELAPSEVIDEO):
                case static_cast< uint8_t>(Literal::E_PARKINGMONITORVIDEO):
                case static_cast< uint8_t>(Literal::E_VEHICLECOLLISIONVIDEO):
                case static_cast< uint8_t>(Literal::E_AIRBAGEJECTIONVIDEO):
                case static_cast< uint8_t>(Literal::E_AEBVIDEO):
                case static_cast< uint8_t>(Literal::E_BURGLARALARMVIDEO):
                case static_cast< uint8_t>(Literal::E_CONTINUOUSCAPTURE):
                case static_cast< uint8_t>(Literal::E_SHORTVIDEORECORDING_BYBUTTON):
                case static_cast< uint8_t>(Literal::E_SHORTVIDEORECORDING_BYHUT):
                case static_cast< uint8_t>(Literal::E_APSVIDEO):
                case static_cast< uint8_t>(Literal::E_ACC_AEBVIDEO):
                case static_cast< uint8_t>(Literal::E_WHISTLEVIDEO):
                case static_cast< uint8_t>(Literal::E_RADARRINGINGVIDEO):
                case static_cast< uint8_t>(Literal::E_MEBVIDEO):
                case static_cast< uint8_t>(Literal::E_HANDLEFTVIDEO):
                case static_cast< uint8_t>(Literal::E_CARINGMODE):
                case static_cast< uint8_t>(Literal::E_EXPORTFILE):
                case static_cast< uint8_t>(Literal::E_GUARDIANMODE):
                case static_cast< uint8_t>(Literal::E_DELETEFILE):
                case static_cast< uint8_t>(Literal::E_MANUALCAPTURE_BYFINDCAR):
                case static_cast< uint8_t>(Literal::E_SENTINELMODE_HIGH):
                case static_cast< uint8_t>(Literal::E_SENTINELMODE_LOW):
                return true;
            default:
                return false;
            }
        }
    
        inline bool operator==(const EventType &_other) const { return (value_ == _other.value_); }
        inline bool operator!=(const EventType &_other) const { return (value_ != _other.value_); }
        inline bool operator<=(const EventType &_other) const { return (value_ <= _other.value_); }
        inline bool operator>=(const EventType &_other) const { return (value_ >= _other.value_); }
        inline bool operator<(const EventType &_other) const { return (value_ < _other.value_); }
        inline bool operator>(const EventType &_other) const { return (value_ > _other.value_); }
    
        inline bool operator==(const Literal &_value) const { return (value_ == static_cast< uint8_t>(_value)); }
        inline bool operator!=(const Literal &_value) const { return (value_ != static_cast< uint8_t>(_value)); }
        inline bool operator<=(const Literal &_value) const { return (value_ <= static_cast< uint8_t>(_value)); }
        inline bool operator>=(const Literal &_value) const { return (value_ >= static_cast< uint8_t>(_value)); }
        inline bool operator<(const Literal &_value) const { return (value_ < static_cast< uint8_t>(_value)); }
        inline bool operator>(const Literal &_value) const { return (value_ > static_cast< uint8_t>(_value)); }
    };
    
    struct ManualOperation : CommonAPI::Enumeration< uint8_t> {
        enum Literal : uint8_t {
            E_MANUALCAPTURE = 0,
            E_MANUALRECORDING = 1,
            E_STOPTIMELAPSEVIDEOTAPE = 2,
            E_STOPCARINGMODE = 3,
            E_STOPEXPORTFILE = 4,
            E_OMCMANUALCAPTURE = 5,
            E_STOPASYNCDELETEFILE = 6,
            E_FINDCARCAPTURE = 7
        };
    
        ManualOperation()
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(Literal::E_MANUALCAPTURE)) {}
        ManualOperation(Literal _literal)
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(_literal)) {}
    
        inline bool validate() const {
            switch (value_) {
                case static_cast< uint8_t>(Literal::E_MANUALCAPTURE):
                case static_cast< uint8_t>(Literal::E_MANUALRECORDING):
                case static_cast< uint8_t>(Literal::E_STOPTIMELAPSEVIDEOTAPE):
                case static_cast< uint8_t>(Literal::E_STOPCARINGMODE):
                case static_cast< uint8_t>(Literal::E_STOPEXPORTFILE):
                case static_cast< uint8_t>(Literal::E_OMCMANUALCAPTURE):
                case static_cast< uint8_t>(Literal::E_STOPASYNCDELETEFILE):
                case static_cast< uint8_t>(Literal::E_FINDCARCAPTURE):
                return true;
            default:
                return false;
            }
        }
    
        inline bool operator==(const ManualOperation &_other) const { return (value_ == _other.value_); }
        inline bool operator!=(const ManualOperation &_other) const { return (value_ != _other.value_); }
        inline bool operator<=(const ManualOperation &_other) const { return (value_ <= _other.value_); }
        inline bool operator>=(const ManualOperation &_other) const { return (value_ >= _other.value_); }
        inline bool operator<(const ManualOperation &_other) const { return (value_ < _other.value_); }
        inline bool operator>(const ManualOperation &_other) const { return (value_ > _other.value_); }
    
        inline bool operator==(const Literal &_value) const { return (value_ == static_cast< uint8_t>(_value)); }
        inline bool operator!=(const Literal &_value) const { return (value_ != static_cast< uint8_t>(_value)); }
        inline bool operator<=(const Literal &_value) const { return (value_ <= static_cast< uint8_t>(_value)); }
        inline bool operator>=(const Literal &_value) const { return (value_ >= static_cast< uint8_t>(_value)); }
        inline bool operator<(const Literal &_value) const { return (value_ < static_cast< uint8_t>(_value)); }
        inline bool operator>(const Literal &_value) const { return (value_ > static_cast< uint8_t>(_value)); }
    };
    typedef uint16_t TimelapseVideoTotalFrameNumber;
    typedef uint8_t TotalCareTime;
    typedef uint32_t FreeExportCapacity;
    typedef uint32_t FileID;
    typedef uint8_t CaptureInterval;
    typedef std::string EventTime;
    
    struct SetResult : CommonAPI::Enumeration< uint8_t> {
        enum Literal : uint8_t {
            E_SUCCESSFUL = 0,
            E_FAILED = 1
        };
    
        SetResult()
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(Literal::E_SUCCESSFUL)) {}
        SetResult(Literal _literal)
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(_literal)) {}
    
        inline bool validate() const {
            switch (value_) {
                case static_cast< uint8_t>(Literal::E_SUCCESSFUL):
                case static_cast< uint8_t>(Literal::E_FAILED):
                return true;
            default:
                return false;
            }
        }
    
        inline bool operator==(const SetResult &_other) const { return (value_ == _other.value_); }
        inline bool operator!=(const SetResult &_other) const { return (value_ != _other.value_); }
        inline bool operator<=(const SetResult &_other) const { return (value_ <= _other.value_); }
        inline bool operator>=(const SetResult &_other) const { return (value_ >= _other.value_); }
        inline bool operator<(const SetResult &_other) const { return (value_ < _other.value_); }
        inline bool operator>(const SetResult &_other) const { return (value_ > _other.value_); }
    
        inline bool operator==(const Literal &_value) const { return (value_ == static_cast< uint8_t>(_value)); }
        inline bool operator!=(const Literal &_value) const { return (value_ != static_cast< uint8_t>(_value)); }
        inline bool operator<=(const Literal &_value) const { return (value_ <= static_cast< uint8_t>(_value)); }
        inline bool operator>=(const Literal &_value) const { return (value_ >= static_cast< uint8_t>(_value)); }
        inline bool operator<(const Literal &_value) const { return (value_ < static_cast< uint8_t>(_value)); }
        inline bool operator>(const Literal &_value) const { return (value_ > static_cast< uint8_t>(_value)); }
    };
    typedef std::vector< uint8_t> FileContentArray;
    
    struct OMCCaptureFaileCode : CommonAPI::Enumeration< uint8_t> {
        enum Literal : uint8_t {
            E_SUCCESS = 0,
            E_UNKNOW = 1,
            E_EVENTTYPEERROR = 2,
            E_ACCESSTYPEERROR = 3,
            E_BUSY = 4,
            E_CAPACITYNOTENOUGH = 5
        };
    
        OMCCaptureFaileCode()
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(Literal::E_SUCCESS)) {}
        OMCCaptureFaileCode(Literal _literal)
            : CommonAPI::Enumeration< uint8_t>(static_cast< uint8_t>(_literal)) {}
    
        inline bool validate() const {
            switch (value_) {
                case static_cast< uint8_t>(Literal::E_SUCCESS):
                case static_cast< uint8_t>(Literal::E_UNKNOW):
                case static_cast< uint8_t>(Literal::E_EVENTTYPEERROR):
                case static_cast< uint8_t>(Literal::E_ACCESSTYPEERROR):
                case static_cast< uint8_t>(Literal::E_BUSY):
                case static_cast< uint8_t>(Literal::E_CAPACITYNOTENOUGH):
                return true;
            default:
                return false;
            }
        }
    
        inline bool operator==(const OMCCaptureFaileCode &_other) const { return (value_ == _other.value_); }
        inline bool operator!=(const OMCCaptureFaileCode &_other) const { return (value_ != _other.value_); }
        inline bool operator<=(const OMCCaptureFaileCode &_other) const { return (value_ <= _other.value_); }
        inline bool operator>=(const OMCCaptureFaileCode &_other) const { return (value_ >= _other.value_); }
        inline bool operator<(const OMCCaptureFaileCode &_other) const { return (value_ < _other.value_); }
        inline bool operator>(const OMCCaptureFaileCode &_other) const { return (value_ > _other.value_); }
    
        inline bool operator==(const Literal &_value) const { return (value_ == static_cast< uint8_t>(_value)); }
        inline bool operator!=(const Literal &_value) const { return (value_ != static_cast< uint8_t>(_value)); }
        inline bool operator<=(const Literal &_value) const { return (value_ <= static_cast< uint8_t>(_value)); }
        inline bool operator>=(const Literal &_value) const { return (value_ >= static_cast< uint8_t>(_value)); }
        inline bool operator<(const Literal &_value) const { return (value_ < static_cast< uint8_t>(_value)); }
        inline bool operator>(const Literal &_value) const { return (value_ > static_cast< uint8_t>(_value)); }
    };
    typedef uint32_t ThemePictureID;
    typedef uint32_t RemainingCapacity;
    typedef uint32_t TotalCapacity;
    struct EMMCCapacityStruct : CommonAPI::Struct< TotalCapacity, RemainingCapacity> {
    
        EMMCCapacityStruct()
        {
            std::get< 0>(values_) = TotalCapacity();
            std::get< 1>(values_) = RemainingCapacity();
        }
        EMMCCapacityStruct(const TotalCapacity &_TotalCapacity, const RemainingCapacity &_RemainingCapacity)
        {
            std::get< 0>(values_) = _TotalCapacity;
            std::get< 1>(values_) = _RemainingCapacity;
        }
        inline const TotalCapacity &getTotalCapacity() const { return std::get< 0>(values_); }
        inline void setTotalCapacity(const TotalCapacity &_value) { std::get< 0>(values_) = _value; }
        inline const RemainingCapacity &getRemainingCapacity() const { return std::get< 1>(values_); }
        inline void setRemainingCapacity(const RemainingCapacity &_value) { std::get< 1>(values_) = _value; }
        inline bool operator==(const EMMCCapacityStruct& _other) const {
        return (getTotalCapacity() == _other.getTotalCapacity() && getRemainingCapacity() == _other.getRemainingCapacity());
        }
        inline bool operator!=(const EMMCCapacityStruct &_other) const {
            return !((*this) == _other);
        }
    
    };
    struct TFCardCapacity : CommonAPI::Struct< TotalCapacity, RemainingCapacity> {
    
        TFCardCapacity()
        {
            std::get< 0>(values_) = TotalCapacity();
            std::get< 1>(values_) = RemainingCapacity();
        }
        TFCardCapacity(const TotalCapacity &_TotalCapacity, const RemainingCapacity &_RemainingCapacity)
        {
            std::get< 0>(values_) = _TotalCapacity;
            std::get< 1>(values_) = _RemainingCapacity;
        }
        inline const TotalCapacity &getTotalCapacity() const { return std::get< 0>(values_); }
        inline void setTotalCapacity(const TotalCapacity &_value) { std::get< 0>(values_) = _value; }
        inline const RemainingCapacity &getRemainingCapacity() const { return std::get< 1>(values_); }
        inline void setRemainingCapacity(const RemainingCapacity &_value) { std::get< 1>(values_) = _value; }
        inline bool operator==(const TFCardCapacity& _other) const {
        return (getTotalCapacity() == _other.getTotalCapacity() && getRemainingCapacity() == _other.getRemainingCapacity());
        }
        inline bool operator!=(const TFCardCapacity &_other) const {
            return !((*this) == _other);
        }
    
    };
};

const char* DVRStatusReport::getInterface() {
    return ("GREATWALL.DVR_VIMS.DVRStatusReport:v1_0");
}

CommonAPI::Version DVRStatusReport::getInterfaceVersion() {
    return CommonAPI::Version(1, 0);
}


} // namespace DVR_VIMS
} // namespace GREATWALL
} // namespace v1

namespace CommonAPI {
}


// Compatibility
namespace v1_0 = v1;

#endif // V1_GREATWALL_DVR_VIMS_DVR_STATUS_REPORT_HPP_
