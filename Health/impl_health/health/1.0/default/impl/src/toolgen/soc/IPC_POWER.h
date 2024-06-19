/*************************************************************************
* Copyright (C) 2020 GWM Automotive Inc.
*
* The copyright notice above does not evidence any actual
* or intended publication of such source code.
* The code contains GWM Confidential Proprietary Information.
*************************************************************************/

/**********************************************************************************************************************
*  FILE DESCRIPTION
*  -------------------------------------------------------------------------------------------------------------------
*                 File:  IPC_POWER.h
*            Generator:  IPC Code Generator V1.3.0
*     Description file:  IPC_SOC.h.tem
*          Description:  IPC group POWER  header file
*               Author:  IPC Code Generator V1.3.0
*********************************************************************************************************************/

#ifndef _IPC_POWER_H_
#define _IPC_POWER_H_

#include "IPC_Common.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Group id */
#define IPC_GROUP_POWER_ID                                                       (2u)

/* MCU to SOC Message major id */
#define IPC_M2S_POWER_MSGMAJOR_SOCMANAGER_ID                                     (0u)
#define IPC_M2S_POWER_MSGMAJOR_SYSTEMSTATE_ID                                    (1u)
#define IPC_M2S_POWER_MSGMAJOR_POWERINFO_ID                                      (2u)
/* MCU to SOC Message sub id */
#define IPC_M2S_POWER_SOCMANAGER_MSGSUB_HANDSHAKERESPONSE_ID                     (0u)
#define IPC_M2S_POWER_SOCMANAGER_MSGSUB_MCUREQUESTQNXSERVICE_ID                  (1u)
#define IPC_M2S_POWER_SOCMANAGER_MSGSUB_VERSION_ID                               (2u)
#define IPC_M2S_POWER_SYSTEMSTATE_MSGSUB_IVI_STATE_ID                            (0u)
#define IPC_M2S_POWER_SYSTEMSTATE_MSGSUB_HUDSTATE_ID                             (1u)
#define IPC_M2S_POWER_SYSTEMSTATE_MSGSUB_CONSOLESTATE_ID                         (2u)
#define IPC_M2S_POWER_SYSTEMSTATE_MSGSUB_CLUSTERSTATE_ID                         (3u)
#define IPC_M2S_POWER_POWERINFO_MSGSUB_VOLTATEGEINFO_ID                          (0u)
#define IPC_M2S_POWER_POWERINFO_MSGSUB_TEMPERATURE_ID                            (1u)
#define IPC_M2S_POWER_POWERINFO_MSGSUB_KL15STATE_ID                              (2u)
#define IPC_M2S_POWER_POWERINFO_MSGSUB_MCUINFO_ID                                (3u)
/* MCU to SOC Message sub length */
#define IPC_M2S_POWER_SOCMANAGER_MSGSUB_HANDSHAKERESPONSE_LENGTH                 (4u)
#define IPC_M2S_POWER_SOCMANAGER_MSGSUB_MCUREQUESTQNXSERVICE_LENGTH              (1u)
#define IPC_M2S_POWER_SOCMANAGER_MSGSUB_VERSION_LENGTH                           (1u)
#define IPC_M2S_POWER_SYSTEMSTATE_MSGSUB_IVI_STATE_LENGTH                        (2u)
#define IPC_M2S_POWER_SYSTEMSTATE_MSGSUB_HUDSTATE_LENGTH                         (1u)
#define IPC_M2S_POWER_SYSTEMSTATE_MSGSUB_CONSOLESTATE_LENGTH                     (1u)
#define IPC_M2S_POWER_SYSTEMSTATE_MSGSUB_CLUSTERSTATE_LENGTH                     (1u)
#define IPC_M2S_POWER_POWERINFO_MSGSUB_VOLTATEGEINFO_LENGTH                      (5u)
#define IPC_M2S_POWER_POWERINFO_MSGSUB_TEMPERATURE_LENGTH                        (5u)
#define IPC_M2S_POWER_POWERINFO_MSGSUB_KL15STATE_LENGTH                          (1u)
#define IPC_M2S_POWER_POWERINFO_MSGSUB_MCUINFO_LENGTH                            (2u)
/* SOC to MCU Message major id */
#define IPC_S2M_POWER_MSGMAJOR_SOCMANAGER_ID                                     (0u)
#define IPC_S2M_POWER_MSGMAJOR_SYSTEMSTATE_ID                                    (1u)
/* SOC to MCU Message sub id */
#define IPC_S2M_POWER_SOCMANAGER_MSGSUB_HANDSHAKEREQUEST_ID                      (0u)
#define IPC_S2M_POWER_SOCMANAGER_MSGSUB_HEATH_ID                                 (1u)
#define IPC_S2M_POWER_SOCMANAGER_MSGSUB_RESET_ID                                 (2u)
#define IPC_S2M_POWER_SOCMANAGER_MSGSUB_QNXRESPONSEMCUREQUEST_ID                 (3u)
#define IPC_S2M_POWER_SOCMANAGER_MSGSUB_QNXINFOMCUSYSTEM_ID                      (4u)
#define IPC_S2M_POWER_SOCMANAGER_MSGSUB_QNXQUERYVERSION_ID                       (5u)
#define IPC_S2M_POWER_SYSTEMSTATE_MSGSUB_IVI_STATE_ID                            (0u)
/* SOC to MCU Message sub length */
#define IPC_S2M_POWER_SOCMANAGER_MSGSUB_HANDSHAKEREQUEST_LENGTH                  (4u)
#define IPC_S2M_POWER_SOCMANAGER_MSGSUB_HEATH_LENGTH                             (1u)
#define IPC_S2M_POWER_SOCMANAGER_MSGSUB_RESET_LENGTH                             (2u)
#define IPC_S2M_POWER_SOCMANAGER_MSGSUB_QNXRESPONSEMCUREQUEST_LENGTH             (1u)
#define IPC_S2M_POWER_SOCMANAGER_MSGSUB_QNXINFOMCUSYSTEM_LENGTH                  (1u)
#define IPC_S2M_POWER_SOCMANAGER_MSGSUB_QNXQUERYVERSION_LENGTH                   (1u)
#define IPC_S2M_POWER_SYSTEMSTATE_MSGSUB_IVI_STATE_LENGTH                        (1u)
/* Group: : POWER */
/* Message Major: SocManager */
/* Message Sub: HandshakeResponse */
typedef struct
{
    uint8_t u8Reserved[4];
}IPC_M2S_POWERSocManagerHandshakeResponse_t;

/* Pack function of sub message HandshakeResponse */
int32_t IPC_M2S_POWERSocManagerHandshakeResponse_Pack(IPC_M2S_POWERSocManagerHandshakeResponse_t *data, uint8_t *payload, uint16_t length);

/* Parse function of sub message HandshakeResponse */
int32_t IPC_M2S_POWERSocManagerHandshakeResponse_Parse(IPC_M2S_POWERSocManagerHandshakeResponse_t *data, uint8_t *payload, uint16_t length);

/* Message Sub: MCURequestQnxService */
typedef struct
{
    uint8_t MCURequestQnxService;
}IPC_M2S_POWERSocManagerMCURequestQnxService_t;

/* Pack function of sub message MCURequestQnxService */
int32_t IPC_M2S_POWERSocManagerMCURequestQnxService_Pack(IPC_M2S_POWERSocManagerMCURequestQnxService_t *data, uint8_t *payload, uint16_t length);

/* Parse function of sub message MCURequestQnxService */
int32_t IPC_M2S_POWERSocManagerMCURequestQnxService_Parse(IPC_M2S_POWERSocManagerMCURequestQnxService_t *data, uint8_t *payload, uint16_t length);

/* Message Sub: Version */
typedef struct
{
    /*
    0 : NON
    1 : A1
    2 : B0
    3 : B1*/
    uint8_t HwVersion;
}IPC_M2S_POWERSocManagerVersion_t;

/* Pack function of sub message Version */
int32_t IPC_M2S_POWERSocManagerVersion_Pack(IPC_M2S_POWERSocManagerVersion_t *data, uint8_t *payload, uint16_t length);

/* Parse function of sub message Version */
int32_t IPC_M2S_POWERSocManagerVersion_Parse(IPC_M2S_POWERSocManagerVersion_t *data, uint8_t *payload, uint16_t length);

/* Group: : POWER */
/* Message Major: SystemState */
/* Message Sub: IVI_State */
typedef struct
{
    /*0x0:IVI_OFF;0x1:IVI_Standby;0x3:IVI_Shutdown;0x4:IVI_Normal;0x5:IVI_Power_Err;0x6:IVI_PowerSave1;0x7:IVI_PowerSave2;0x8:IVI_Local
    */
    uint8_t IVI_State;
    /*0x0:None;0x1:TRUE*/
    uint8_t Force;
}IPC_M2S_POWERSystemStateIVI_State_t;

/* Pack function of sub message IVI_State */
int32_t IPC_M2S_POWERSystemStateIVI_State_Pack(IPC_M2S_POWERSystemStateIVI_State_t *data, uint8_t *payload, uint16_t length);

/* Parse function of sub message IVI_State */
int32_t IPC_M2S_POWERSystemStateIVI_State_Parse(IPC_M2S_POWERSystemStateIVI_State_t *data, uint8_t *payload, uint16_t length);

/* Message Sub: HUDState */
typedef struct
{
    /*0x0:HUD off;0x1:HUD standby;0x2:HUD on*/
    uint8_t HUD_State;
}IPC_M2S_POWERSystemStateHUDState_t;

/* Pack function of sub message HUDState */
int32_t IPC_M2S_POWERSystemStateHUDState_Pack(IPC_M2S_POWERSystemStateHUDState_t *data, uint8_t *payload, uint16_t length);

/* Parse function of sub message HUDState */
int32_t IPC_M2S_POWERSystemStateHUDState_Parse(IPC_M2S_POWERSystemStateHUDState_t *data, uint8_t *payload, uint16_t length);

/* Message Sub: ConsoleState */
typedef struct
{
    /*0x0:console off;0x1:console standby;0x2:console on*/
    uint8_t Console_State;
}IPC_M2S_POWERSystemStateConsoleState_t;

/* Pack function of sub message ConsoleState */
int32_t IPC_M2S_POWERSystemStateConsoleState_Pack(IPC_M2S_POWERSystemStateConsoleState_t *data, uint8_t *payload, uint16_t length);

/* Parse function of sub message ConsoleState */
int32_t IPC_M2S_POWERSystemStateConsoleState_Parse(IPC_M2S_POWERSystemStateConsoleState_t *data, uint8_t *payload, uint16_t length);

/* Message Sub: ClusterState */
typedef struct
{
    /*0x0:cluster off;0x1:cluster standby;0x2:cluster on*/
    uint8_t ClusterState;
}IPC_M2S_POWERSystemStateClusterState_t;

/* Pack function of sub message ClusterState */
int32_t IPC_M2S_POWERSystemStateClusterState_Pack(IPC_M2S_POWERSystemStateClusterState_t *data, uint8_t *payload, uint16_t length);

/* Parse function of sub message ClusterState */
int32_t IPC_M2S_POWERSystemStateClusterState_Parse(IPC_M2S_POWERSystemStateClusterState_t *data, uint8_t *payload, uint16_t length);

/* Group: : POWER */
/* Message Major: PowerInfo */
/* Message Sub: VoltategeInfo */
typedef struct
{
    float VoltageValue;
    /*0x0:low_sleep;
    0x1:normal;
    0x2:high_alarm;
    0x3:high_sleep;
    0x4:Low_alarm*/
    uint8_t VoltageState;
}IPC_M2S_POWERPowerInfoVoltategeInfo_t;

/* Pack function of sub message VoltategeInfo */
int32_t IPC_M2S_POWERPowerInfoVoltategeInfo_Pack(IPC_M2S_POWERPowerInfoVoltategeInfo_t *data, uint8_t *payload, uint16_t length);

/* Parse function of sub message VoltategeInfo */
int32_t IPC_M2S_POWERPowerInfoVoltategeInfo_Parse(IPC_M2S_POWERPowerInfoVoltategeInfo_t *data, uint8_t *payload, uint16_t length);

/* Message Sub: Temperature */
typedef struct
{
    float Temperature;
    /*0x00: Low Sleep
    0x01: Normal
    0x02: High protect
    0x03: High Sleep*/
    uint8_t TemperatureState;
}IPC_M2S_POWERPowerInfoTemperature_t;

/* Pack function of sub message Temperature */
int32_t IPC_M2S_POWERPowerInfoTemperature_Pack(IPC_M2S_POWERPowerInfoTemperature_t *data, uint8_t *payload, uint16_t length);

/* Parse function of sub message Temperature */
int32_t IPC_M2S_POWERPowerInfoTemperature_Parse(IPC_M2S_POWERPowerInfoTemperature_t *data, uint8_t *payload, uint16_t length);

/* Message Sub: KL15State */
typedef struct
{
    /*0x0:KL15 OFF ;
    0x1:KL15 ON*/
    uint8_t KL15State;
}IPC_M2S_POWERPowerInfoKL15State_t;

/* Pack function of sub message KL15State */
int32_t IPC_M2S_POWERPowerInfoKL15State_Pack(IPC_M2S_POWERPowerInfoKL15State_t *data, uint8_t *payload, uint16_t length);

/* Parse function of sub message KL15State */
int32_t IPC_M2S_POWERPowerInfoKL15State_Parse(IPC_M2S_POWERPowerInfoKL15State_t *data, uint8_t *payload, uint16_t length);

/* Message Sub: MCUInfo */
typedef struct
{
    /*0x0: ColdReset
    0x1: WarmReset*/
    uint8_t ResetType;
    /*0x0: ECUM_WKSOURCE_NONE                            
    0xFF: ECUM_WKSOURCE_ALL_SOURCES                     
    0x01: ECUM_WKSOURCE_POWER                           
    0x02: ECUM_WKSOURCE_RESET                           
    0x04: ECUM_WKSOURCE_INTERNAL_RESET                  
    0x08: ECUM_WKSOURCE_INTERNAL_WDG                    
    0x10: ECUM_WKSOURCE_EXTERNAL_WDG                    
    0x20: ECUM_WKSOURCE_CN_B30_for_SC_CAN_V3_2_c0d6c67b 
    0x40: ECUM_WKSOURCE_LVI                             
    0x80: ECUM_WKSOURCE_COMMON_WAKEUP          
    this is  a bit operator, one bit mean different reason    */
    uint8_t WakeupSource;
}IPC_M2S_POWERPowerInfoMCUInfo_t;

/* Pack function of sub message MCUInfo */
int32_t IPC_M2S_POWERPowerInfoMCUInfo_Pack(IPC_M2S_POWERPowerInfoMCUInfo_t *data, uint8_t *payload, uint16_t length);

/* Parse function of sub message MCUInfo */
int32_t IPC_M2S_POWERPowerInfoMCUInfo_Parse(IPC_M2S_POWERPowerInfoMCUInfo_t *data, uint8_t *payload, uint16_t length);

/* Group: : POWER */
/* Group: : POWER */
/* Message Major: SocManager */
/* Message Sub: HandshakeRequest */
typedef struct
{
    uint8_t u8Reserved[4];
}IPC_S2M_POWERSocManagerHandshakeRequest_t;

/* Pack function of sub message HandshakeRequest */
int32_t IPC_S2M_POWERSocManagerHandshakeRequest_Pack(IPC_S2M_POWERSocManagerHandshakeRequest_t *data, uint8_t *payload, uint16_t length);

/* Parse function of sub message HandshakeRequest */
int32_t IPC_S2M_POWERSocManagerHandshakeRequest_Parse(IPC_S2M_POWERSocManagerHandshakeRequest_t *data, uint8_t *payload, uint16_t length);

/* Message Sub: Heath */
typedef struct
{
    uint8_t u8Reserved;
}IPC_S2M_POWERSocManagerHeath_t;

/* Pack function of sub message Heath */
int32_t IPC_S2M_POWERSocManagerHeath_Pack(IPC_S2M_POWERSocManagerHeath_t *data, uint8_t *payload, uint16_t length);

/* Parse function of sub message Heath */
int32_t IPC_S2M_POWERSocManagerHeath_Parse(IPC_S2M_POWERSocManagerHeath_t *data, uint8_t *payload, uint16_t length);

/* Message Sub: Reset */
typedef struct
{
    uint8_t u8Parameter;
    uint8_t u8Describe;
}IPC_S2M_POWERSocManagerReset_t;

/* Pack function of sub message Reset */
int32_t IPC_S2M_POWERSocManagerReset_Pack(IPC_S2M_POWERSocManagerReset_t *data, uint8_t *payload, uint16_t length);

/* Parse function of sub message Reset */
int32_t IPC_S2M_POWERSocManagerReset_Parse(IPC_S2M_POWERSocManagerReset_t *data, uint8_t *payload, uint16_t length);

/* Message Sub: QnxResponseMCURequest */
typedef struct
{
    uint8_t QnxResponseMCURequest;
}IPC_S2M_POWERSocManagerQnxResponseMCURequest_t;

/* Pack function of sub message QnxResponseMCURequest */
int32_t IPC_S2M_POWERSocManagerQnxResponseMCURequest_Pack(IPC_S2M_POWERSocManagerQnxResponseMCURequest_t *data, uint8_t *payload, uint16_t length);

/* Parse function of sub message QnxResponseMCURequest */
int32_t IPC_S2M_POWERSocManagerQnxResponseMCURequest_Parse(IPC_S2M_POWERSocManagerQnxResponseMCURequest_t *data, uint8_t *payload, uint16_t length);

/* Message Sub: QnxInfoMCUSystem */
typedef struct
{
    /*0x0:normal��0x1:minisys*/
    uint8_t u8Parameter;
}IPC_S2M_POWERSocManagerQnxInfoMCUSystem_t;

/* Pack function of sub message QnxInfoMCUSystem */
int32_t IPC_S2M_POWERSocManagerQnxInfoMCUSystem_Pack(IPC_S2M_POWERSocManagerQnxInfoMCUSystem_t *data, uint8_t *payload, uint16_t length);

/* Parse function of sub message QnxInfoMCUSystem */
int32_t IPC_S2M_POWERSocManagerQnxInfoMCUSystem_Parse(IPC_S2M_POWERSocManagerQnxInfoMCUSystem_t *data, uint8_t *payload, uint16_t length);

/* Message Sub: QnxQueryVersion */
typedef struct
{
    uint8_t u8Reserved;
}IPC_S2M_POWERSocManagerQnxQueryVersion_t;

/* Pack function of sub message QnxQueryVersion */
int32_t IPC_S2M_POWERSocManagerQnxQueryVersion_Pack(IPC_S2M_POWERSocManagerQnxQueryVersion_t *data, uint8_t *payload, uint16_t length);

/* Parse function of sub message QnxQueryVersion */
int32_t IPC_S2M_POWERSocManagerQnxQueryVersion_Parse(IPC_S2M_POWERSocManagerQnxQueryVersion_t *data, uint8_t *payload, uint16_t length);

/* Group: : POWER */
/* Message Major: SystemState */
/* Message Sub: IVI_State */
typedef struct
{
    /*0x0:pending��0x1:done*/
    uint8_t TransferResponse;
}IPC_S2M_POWERSystemStateIVI_State_t;

/* Pack function of sub message IVI_State */
int32_t IPC_S2M_POWERSystemStateIVI_State_Pack(IPC_S2M_POWERSystemStateIVI_State_t *data, uint8_t *payload, uint16_t length);

/* Parse function of sub message IVI_State */
int32_t IPC_S2M_POWERSystemStateIVI_State_Parse(IPC_S2M_POWERSystemStateIVI_State_t *data, uint8_t *payload, uint16_t length);

/* Group: : POWER */
#ifdef __cplusplus
}
#endif

#endif
