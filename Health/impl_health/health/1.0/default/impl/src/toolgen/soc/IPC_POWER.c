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
 *                 File:  IPC_POWER.c
 *            Generator:  IPC Code Generator V1.3.0
 *     Description file:  IPC_SOC.c.tem
 *          Description:  IPC group POWER source file
 *               Author:  IPC Code Generator V1.3.0
 *********************************************************************************************************************/

#include "IPC_POWER.h"

/* MCU or SOC Transmit/Reveive/Pack/Parse  interface */
/* Group: POWER */
/* Message Major: SocManager */
/* Pack function of sub message HandshakeResponse */
int32_t IPC_M2S_POWERSocManagerHandshakeResponse_Pack(IPC_M2S_POWERSocManagerHandshakeResponse_t *data, uint8_t *payload, uint16_t length)
{
    int32_t ret = -1;
    uint16_t totalLength;

    if((data != NULL) && (payload != NULL) &&
        (length >= IPC_M2S_POWER_SOCMANAGER_MSGSUB_HANDSHAKERESPONSE_LENGTH))
    {
        payload[2] = IPC_GROUP_POWER_ID;
        payload[3] = IPC_M2S_POWER_MSGMAJOR_SOCMANAGER_ID;
        payload[4] = IPC_M2S_POWER_SOCMANAGER_MSGSUB_HANDSHAKERESPONSE_ID;
        {
            uint16_t arrIndex;
            for(arrIndex = 0; arrIndex < 4; arrIndex++)
            {
                payload[5 + arrIndex * 1] = IPC_GET_BYTE(data->u8Reserved[arrIndex], 0);
            }
        }
        totalLength = IPC_M2S_POWER_SOCMANAGER_MSGSUB_HANDSHAKERESPONSE_LENGTH + 5;
        payload[0] = (uint8_t)(totalLength >> 8);
        payload[1] = (uint8_t)(totalLength);
        ret = (int32_t)totalLength;
    }
    return ret;
}

/* Parse function of sub message HandshakeResponse */
int32_t IPC_M2S_POWERSocManagerHandshakeResponse_Parse(IPC_M2S_POWERSocManagerHandshakeResponse_t *data, uint8_t *payload, uint16_t length)
{
    int32_t ret = -1;
    if((payload != NULL) && (data != NULL) &&
        (IPC_M2S_POWER_SOCMANAGER_MSGSUB_HANDSHAKERESPONSE_LENGTH == length))
    {
        {
            uint16_t arrIndex;
            for(arrIndex = 0; arrIndex < 4; arrIndex++)
            {
                IPC_GET_BYTE(data->u8Reserved[arrIndex], 0) = payload[0 + arrIndex * 1];
            }
        }
        ret = 0;
    }
    return ret;
}
/* Pack function of sub message MCURequestQnxService */
int32_t IPC_M2S_POWERSocManagerMCURequestQnxService_Pack(IPC_M2S_POWERSocManagerMCURequestQnxService_t *data, uint8_t *payload, uint16_t length)
{
    int32_t ret = -1;
    uint16_t totalLength;

    if((data != NULL) && (payload != NULL) &&
        (length >= IPC_M2S_POWER_SOCMANAGER_MSGSUB_MCUREQUESTQNXSERVICE_LENGTH))
    {
        payload[2] = IPC_GROUP_POWER_ID;
        payload[3] = IPC_M2S_POWER_MSGMAJOR_SOCMANAGER_ID;
        payload[4] = IPC_M2S_POWER_SOCMANAGER_MSGSUB_MCUREQUESTQNXSERVICE_ID;
        payload[5] = IPC_GET_BYTE(data->MCURequestQnxService, 0);
        totalLength = IPC_M2S_POWER_SOCMANAGER_MSGSUB_MCUREQUESTQNXSERVICE_LENGTH + 5;
        payload[0] = (uint8_t)(totalLength >> 8);
        payload[1] = (uint8_t)(totalLength);
        ret = (int32_t)totalLength;
    }
    return ret;
}

/* Parse function of sub message MCURequestQnxService */
int32_t IPC_M2S_POWERSocManagerMCURequestQnxService_Parse(IPC_M2S_POWERSocManagerMCURequestQnxService_t *data, uint8_t *payload, uint16_t length)
{
    int32_t ret = -1;
    if((payload != NULL) && (data != NULL) &&
        (IPC_M2S_POWER_SOCMANAGER_MSGSUB_MCUREQUESTQNXSERVICE_LENGTH == length))
    {
        IPC_GET_BYTE(data->MCURequestQnxService, 0) = payload[0];
        ret = 0;
    }
    return ret;
}
/* Pack function of sub message Version */
int32_t IPC_M2S_POWERSocManagerVersion_Pack(IPC_M2S_POWERSocManagerVersion_t *data, uint8_t *payload, uint16_t length)
{
    int32_t ret = -1;
    uint16_t totalLength;

    if((data != NULL) && (payload != NULL) &&
        (length >= IPC_M2S_POWER_SOCMANAGER_MSGSUB_VERSION_LENGTH))
    {
        payload[2] = IPC_GROUP_POWER_ID;
        payload[3] = IPC_M2S_POWER_MSGMAJOR_SOCMANAGER_ID;
        payload[4] = IPC_M2S_POWER_SOCMANAGER_MSGSUB_VERSION_ID;
        payload[5] = IPC_GET_BYTE(data->HwVersion, 0);
        totalLength = IPC_M2S_POWER_SOCMANAGER_MSGSUB_VERSION_LENGTH + 5;
        payload[0] = (uint8_t)(totalLength >> 8);
        payload[1] = (uint8_t)(totalLength);
        ret = (int32_t)totalLength;
    }
    return ret;
}

/* Parse function of sub message Version */
int32_t IPC_M2S_POWERSocManagerVersion_Parse(IPC_M2S_POWERSocManagerVersion_t *data, uint8_t *payload, uint16_t length)
{
    int32_t ret = -1;
    if((payload != NULL) && (data != NULL) &&
        (IPC_M2S_POWER_SOCMANAGER_MSGSUB_VERSION_LENGTH == length))
    {
        IPC_GET_BYTE(data->HwVersion, 0) = payload[0];
        ret = 0;
    }
    return ret;
}
/* Message Major: SystemState */
/* Pack function of sub message IVI_State */
int32_t IPC_M2S_POWERSystemStateIVI_State_Pack(IPC_M2S_POWERSystemStateIVI_State_t *data, uint8_t *payload, uint16_t length)
{
    int32_t ret = -1;
    uint16_t totalLength;

    if((data != NULL) && (payload != NULL) &&
        (length >= IPC_M2S_POWER_SYSTEMSTATE_MSGSUB_IVI_STATE_LENGTH))
    {
        payload[2] = IPC_GROUP_POWER_ID;
        payload[3] = IPC_M2S_POWER_MSGMAJOR_SYSTEMSTATE_ID;
        payload[4] = IPC_M2S_POWER_SYSTEMSTATE_MSGSUB_IVI_STATE_ID;
        payload[5] = IPC_GET_BYTE(data->IVI_State, 0);
        payload[6] = IPC_GET_BYTE(data->Force, 0);
        totalLength = IPC_M2S_POWER_SYSTEMSTATE_MSGSUB_IVI_STATE_LENGTH + 5;
        payload[0] = (uint8_t)(totalLength >> 8);
        payload[1] = (uint8_t)(totalLength);
        ret = (int32_t)totalLength;
    }
    return ret;
}

/* Parse function of sub message IVI_State */
int32_t IPC_M2S_POWERSystemStateIVI_State_Parse(IPC_M2S_POWERSystemStateIVI_State_t *data, uint8_t *payload, uint16_t length)
{
    int32_t ret = -1;
    if((payload != NULL) && (data != NULL) &&
        (IPC_M2S_POWER_SYSTEMSTATE_MSGSUB_IVI_STATE_LENGTH == length))
    {
        IPC_GET_BYTE(data->IVI_State, 0) = payload[0];
        IPC_GET_BYTE(data->Force, 0) = payload[1];
        ret = 0;
    }
    return ret;
}
/* Pack function of sub message HUDState */
int32_t IPC_M2S_POWERSystemStateHUDState_Pack(IPC_M2S_POWERSystemStateHUDState_t *data, uint8_t *payload, uint16_t length)
{
    int32_t ret = -1;
    uint16_t totalLength;

    if((data != NULL) && (payload != NULL) &&
        (length >= IPC_M2S_POWER_SYSTEMSTATE_MSGSUB_HUDSTATE_LENGTH))
    {
        payload[2] = IPC_GROUP_POWER_ID;
        payload[3] = IPC_M2S_POWER_MSGMAJOR_SYSTEMSTATE_ID;
        payload[4] = IPC_M2S_POWER_SYSTEMSTATE_MSGSUB_HUDSTATE_ID;
        payload[5] = IPC_GET_BYTE(data->HUD_State, 0);
        totalLength = IPC_M2S_POWER_SYSTEMSTATE_MSGSUB_HUDSTATE_LENGTH + 5;
        payload[0] = (uint8_t)(totalLength >> 8);
        payload[1] = (uint8_t)(totalLength);
        ret = (int32_t)totalLength;
    }
    return ret;
}

/* Parse function of sub message HUDState */
int32_t IPC_M2S_POWERSystemStateHUDState_Parse(IPC_M2S_POWERSystemStateHUDState_t *data, uint8_t *payload, uint16_t length)
{
    int32_t ret = -1;
    if((payload != NULL) && (data != NULL) &&
        (IPC_M2S_POWER_SYSTEMSTATE_MSGSUB_HUDSTATE_LENGTH == length))
    {
        IPC_GET_BYTE(data->HUD_State, 0) = payload[0];
        ret = 0;
    }
    return ret;
}
/* Pack function of sub message ConsoleState */
int32_t IPC_M2S_POWERSystemStateConsoleState_Pack(IPC_M2S_POWERSystemStateConsoleState_t *data, uint8_t *payload, uint16_t length)
{
    int32_t ret = -1;
    uint16_t totalLength;

    if((data != NULL) && (payload != NULL) &&
        (length >= IPC_M2S_POWER_SYSTEMSTATE_MSGSUB_CONSOLESTATE_LENGTH))
    {
        payload[2] = IPC_GROUP_POWER_ID;
        payload[3] = IPC_M2S_POWER_MSGMAJOR_SYSTEMSTATE_ID;
        payload[4] = IPC_M2S_POWER_SYSTEMSTATE_MSGSUB_CONSOLESTATE_ID;
        payload[5] = IPC_GET_BYTE(data->Console_State, 0);
        totalLength = IPC_M2S_POWER_SYSTEMSTATE_MSGSUB_CONSOLESTATE_LENGTH + 5;
        payload[0] = (uint8_t)(totalLength >> 8);
        payload[1] = (uint8_t)(totalLength);
        ret = (int32_t)totalLength;
    }
    return ret;
}

/* Parse function of sub message ConsoleState */
int32_t IPC_M2S_POWERSystemStateConsoleState_Parse(IPC_M2S_POWERSystemStateConsoleState_t *data, uint8_t *payload, uint16_t length)
{
    int32_t ret = -1;
    if((payload != NULL) && (data != NULL) &&
        (IPC_M2S_POWER_SYSTEMSTATE_MSGSUB_CONSOLESTATE_LENGTH == length))
    {
        IPC_GET_BYTE(data->Console_State, 0) = payload[0];
        ret = 0;
    }
    return ret;
}
/* Pack function of sub message ClusterState */
int32_t IPC_M2S_POWERSystemStateClusterState_Pack(IPC_M2S_POWERSystemStateClusterState_t *data, uint8_t *payload, uint16_t length)
{
    int32_t ret = -1;
    uint16_t totalLength;

    if((data != NULL) && (payload != NULL) &&
        (length >= IPC_M2S_POWER_SYSTEMSTATE_MSGSUB_CLUSTERSTATE_LENGTH))
    {
        payload[2] = IPC_GROUP_POWER_ID;
        payload[3] = IPC_M2S_POWER_MSGMAJOR_SYSTEMSTATE_ID;
        payload[4] = IPC_M2S_POWER_SYSTEMSTATE_MSGSUB_CLUSTERSTATE_ID;
        payload[5] = IPC_GET_BYTE(data->ClusterState, 0);
        totalLength = IPC_M2S_POWER_SYSTEMSTATE_MSGSUB_CLUSTERSTATE_LENGTH + 5;
        payload[0] = (uint8_t)(totalLength >> 8);
        payload[1] = (uint8_t)(totalLength);
        ret = (int32_t)totalLength;
    }
    return ret;
}

/* Parse function of sub message ClusterState */
int32_t IPC_M2S_POWERSystemStateClusterState_Parse(IPC_M2S_POWERSystemStateClusterState_t *data, uint8_t *payload, uint16_t length)
{
    int32_t ret = -1;
    if((payload != NULL) && (data != NULL) &&
        (IPC_M2S_POWER_SYSTEMSTATE_MSGSUB_CLUSTERSTATE_LENGTH == length))
    {
        IPC_GET_BYTE(data->ClusterState, 0) = payload[0];
        ret = 0;
    }
    return ret;
}
/* Message Major: PowerInfo */
/* Pack function of sub message VoltategeInfo */
int32_t IPC_M2S_POWERPowerInfoVoltategeInfo_Pack(IPC_M2S_POWERPowerInfoVoltategeInfo_t *data, uint8_t *payload, uint16_t length)
{
    int32_t ret = -1;
    uint16_t totalLength;

    if((data != NULL) && (payload != NULL) &&
        (length >= IPC_M2S_POWER_POWERINFO_MSGSUB_VOLTATEGEINFO_LENGTH))
    {
        payload[2] = IPC_GROUP_POWER_ID;
        payload[3] = IPC_M2S_POWER_MSGMAJOR_POWERINFO_ID;
        payload[4] = IPC_M2S_POWER_POWERINFO_MSGSUB_VOLTATEGEINFO_ID;
        payload[5] = IPC_GET_BYTE(data->VoltageValue, 3);
        payload[6] = IPC_GET_BYTE(data->VoltageValue, 2);
        payload[7] = IPC_GET_BYTE(data->VoltageValue, 1);
        payload[8] = IPC_GET_BYTE(data->VoltageValue, 0);
        payload[9] = IPC_GET_BYTE(data->VoltageState, 0);
        totalLength = IPC_M2S_POWER_POWERINFO_MSGSUB_VOLTATEGEINFO_LENGTH + 5;
        payload[0] = (uint8_t)(totalLength >> 8);
        payload[1] = (uint8_t)(totalLength);
        ret = (int32_t)totalLength;
    }
    return ret;
}

/* Parse function of sub message VoltategeInfo */
int32_t IPC_M2S_POWERPowerInfoVoltategeInfo_Parse(IPC_M2S_POWERPowerInfoVoltategeInfo_t *data, uint8_t *payload, uint16_t length)
{
    int32_t ret = -1;
    if((payload != NULL) && (data != NULL) &&
        (IPC_M2S_POWER_POWERINFO_MSGSUB_VOLTATEGEINFO_LENGTH == length))
    {
        IPC_GET_BYTE(data->VoltageValue, 3) = payload[0];
        IPC_GET_BYTE(data->VoltageValue, 2) = payload[1];
        IPC_GET_BYTE(data->VoltageValue, 1) = payload[2];
        IPC_GET_BYTE(data->VoltageValue, 0) = payload[3];
        IPC_GET_BYTE(data->VoltageState, 0) = payload[4];
        ret = 0;
    }
    return ret;
}
/* Pack function of sub message Temperature */
int32_t IPC_M2S_POWERPowerInfoTemperature_Pack(IPC_M2S_POWERPowerInfoTemperature_t *data, uint8_t *payload, uint16_t length)
{
    int32_t ret = -1;
    uint16_t totalLength;

    if((data != NULL) && (payload != NULL) &&
        (length >= IPC_M2S_POWER_POWERINFO_MSGSUB_TEMPERATURE_LENGTH))
    {
        payload[2] = IPC_GROUP_POWER_ID;
        payload[3] = IPC_M2S_POWER_MSGMAJOR_POWERINFO_ID;
        payload[4] = IPC_M2S_POWER_POWERINFO_MSGSUB_TEMPERATURE_ID;
        payload[5] = IPC_GET_BYTE(data->Temperature, 3);
        payload[6] = IPC_GET_BYTE(data->Temperature, 2);
        payload[7] = IPC_GET_BYTE(data->Temperature, 1);
        payload[8] = IPC_GET_BYTE(data->Temperature, 0);
        payload[9] = IPC_GET_BYTE(data->TemperatureState, 0);
        totalLength = IPC_M2S_POWER_POWERINFO_MSGSUB_TEMPERATURE_LENGTH + 5;
        payload[0] = (uint8_t)(totalLength >> 8);
        payload[1] = (uint8_t)(totalLength);
        ret = (int32_t)totalLength;
    }
    return ret;
}

/* Parse function of sub message Temperature */
int32_t IPC_M2S_POWERPowerInfoTemperature_Parse(IPC_M2S_POWERPowerInfoTemperature_t *data, uint8_t *payload, uint16_t length)
{
    int32_t ret = -1;
    if((payload != NULL) && (data != NULL) &&
        (IPC_M2S_POWER_POWERINFO_MSGSUB_TEMPERATURE_LENGTH == length))
    {
        IPC_GET_BYTE(data->Temperature, 3) = payload[0];
        IPC_GET_BYTE(data->Temperature, 2) = payload[1];
        IPC_GET_BYTE(data->Temperature, 1) = payload[2];
        IPC_GET_BYTE(data->Temperature, 0) = payload[3];
        IPC_GET_BYTE(data->TemperatureState, 0) = payload[4];
        ret = 0;
    }
    return ret;
}
/* Pack function of sub message KL15State */
int32_t IPC_M2S_POWERPowerInfoKL15State_Pack(IPC_M2S_POWERPowerInfoKL15State_t *data, uint8_t *payload, uint16_t length)
{
    int32_t ret = -1;
    uint16_t totalLength;

    if((data != NULL) && (payload != NULL) &&
        (length >= IPC_M2S_POWER_POWERINFO_MSGSUB_KL15STATE_LENGTH))
    {
        payload[2] = IPC_GROUP_POWER_ID;
        payload[3] = IPC_M2S_POWER_MSGMAJOR_POWERINFO_ID;
        payload[4] = IPC_M2S_POWER_POWERINFO_MSGSUB_KL15STATE_ID;
        payload[5] = IPC_GET_BYTE(data->KL15State, 0);
        totalLength = IPC_M2S_POWER_POWERINFO_MSGSUB_KL15STATE_LENGTH + 5;
        payload[0] = (uint8_t)(totalLength >> 8);
        payload[1] = (uint8_t)(totalLength);
        ret = (int32_t)totalLength;
    }
    return ret;
}

/* Parse function of sub message KL15State */
int32_t IPC_M2S_POWERPowerInfoKL15State_Parse(IPC_M2S_POWERPowerInfoKL15State_t *data, uint8_t *payload, uint16_t length)
{
    int32_t ret = -1;
    if((payload != NULL) && (data != NULL) &&
        (IPC_M2S_POWER_POWERINFO_MSGSUB_KL15STATE_LENGTH == length))
    {
        IPC_GET_BYTE(data->KL15State, 0) = payload[0];
        ret = 0;
    }
    return ret;
}
/* Pack function of sub message MCUInfo */
int32_t IPC_M2S_POWERPowerInfoMCUInfo_Pack(IPC_M2S_POWERPowerInfoMCUInfo_t *data, uint8_t *payload, uint16_t length)
{
    int32_t ret = -1;
    uint16_t totalLength;

    if((data != NULL) && (payload != NULL) &&
        (length >= IPC_M2S_POWER_POWERINFO_MSGSUB_MCUINFO_LENGTH))
    {
        payload[2] = IPC_GROUP_POWER_ID;
        payload[3] = IPC_M2S_POWER_MSGMAJOR_POWERINFO_ID;
        payload[4] = IPC_M2S_POWER_POWERINFO_MSGSUB_MCUINFO_ID;
        payload[5] = IPC_GET_BYTE(data->ResetType, 0);
        payload[6] = IPC_GET_BYTE(data->WakeupSource, 0);
        totalLength = IPC_M2S_POWER_POWERINFO_MSGSUB_MCUINFO_LENGTH + 5;
        payload[0] = (uint8_t)(totalLength >> 8);
        payload[1] = (uint8_t)(totalLength);
        ret = (int32_t)totalLength;
    }
    return ret;
}

/* Parse function of sub message MCUInfo */
int32_t IPC_M2S_POWERPowerInfoMCUInfo_Parse(IPC_M2S_POWERPowerInfoMCUInfo_t *data, uint8_t *payload, uint16_t length)
{
    int32_t ret = -1;
    if((payload != NULL) && (data != NULL) &&
        (IPC_M2S_POWER_POWERINFO_MSGSUB_MCUINFO_LENGTH == length))
    {
        IPC_GET_BYTE(data->ResetType, 0) = payload[0];
        IPC_GET_BYTE(data->WakeupSource, 0) = payload[1];
        ret = 0;
    }
    return ret;
}
/* Pack function of sub message HandshakeRequest */
int32_t IPC_S2M_POWERSocManagerHandshakeRequest_Pack(IPC_S2M_POWERSocManagerHandshakeRequest_t *data, uint8_t *payload, uint16_t length)
{
    int32_t ret = -1;
    uint16_t totalLength;

    if((data != NULL) && (payload != NULL) &&
        (length >= IPC_S2M_POWER_SOCMANAGER_MSGSUB_HANDSHAKEREQUEST_LENGTH))
    {
        payload[2] = IPC_GROUP_POWER_ID;
        payload[3] = IPC_S2M_POWER_MSGMAJOR_SOCMANAGER_ID;
        payload[4] = IPC_S2M_POWER_SOCMANAGER_MSGSUB_HANDSHAKEREQUEST_ID;
        {
            uint16_t arrIndex;
            for(arrIndex = 0; arrIndex < 4; arrIndex++)
            {
                payload[5 + arrIndex * 1] = IPC_GET_BYTE(data->u8Reserved[arrIndex], 0);
            }
        }
        totalLength = IPC_S2M_POWER_SOCMANAGER_MSGSUB_HANDSHAKEREQUEST_LENGTH + 5;
        payload[0] = (uint8_t)(totalLength >> 8);
        payload[1] = (uint8_t)(totalLength);
        ret = (int32_t)totalLength;
    }
    return ret;
}
/* Parse function of sub message HandshakeRequest */
int32_t IPC_S2M_POWERSocManagerHandshakeRequest_Parse(IPC_S2M_POWERSocManagerHandshakeRequest_t *data, uint8_t *payload, uint16_t length)
{
    int32_t ret = -1;
    if((payload != NULL) && (data != NULL) &&
        (IPC_S2M_POWER_SOCMANAGER_MSGSUB_HANDSHAKEREQUEST_LENGTH == length))
    {
        {
            uint16_t arrIndex;
            for(arrIndex = 0; arrIndex < 4; arrIndex++)
            {
                IPC_GET_BYTE(data->u8Reserved[arrIndex], 0) = payload[0 + arrIndex * 1];
            }
        }
        ret = 0;
    }
    return ret;
}
/* Pack function of sub message Heath */
int32_t IPC_S2M_POWERSocManagerHeath_Pack(IPC_S2M_POWERSocManagerHeath_t *data, uint8_t *payload, uint16_t length)
{
    int32_t ret = -1;
    uint16_t totalLength;

    if((data != NULL) && (payload != NULL) &&
        (length >= IPC_S2M_POWER_SOCMANAGER_MSGSUB_HEATH_LENGTH))
    {
        payload[2] = IPC_GROUP_POWER_ID;
        payload[3] = IPC_S2M_POWER_MSGMAJOR_SOCMANAGER_ID;
        payload[4] = IPC_S2M_POWER_SOCMANAGER_MSGSUB_HEATH_ID;
        payload[5] = IPC_GET_BYTE(data->u8Reserved, 0);
        totalLength = IPC_S2M_POWER_SOCMANAGER_MSGSUB_HEATH_LENGTH + 5;
        payload[0] = (uint8_t)(totalLength >> 8);
        payload[1] = (uint8_t)(totalLength);
        ret = (int32_t)totalLength;
    }
    return ret;
}
/* Parse function of sub message Heath */
int32_t IPC_S2M_POWERSocManagerHeath_Parse(IPC_S2M_POWERSocManagerHeath_t *data, uint8_t *payload, uint16_t length)
{
    int32_t ret = -1;
    if((payload != NULL) && (data != NULL) &&
        (IPC_S2M_POWER_SOCMANAGER_MSGSUB_HEATH_LENGTH == length))
    {
        IPC_GET_BYTE(data->u8Reserved, 0) = payload[0];
        ret = 0;
    }
    return ret;
}
/* Pack function of sub message Reset */
int32_t IPC_S2M_POWERSocManagerReset_Pack(IPC_S2M_POWERSocManagerReset_t *data, uint8_t *payload, uint16_t length)
{
    int32_t ret = -1;
    uint16_t totalLength;

    if((data != NULL) && (payload != NULL) &&
        (length >= IPC_S2M_POWER_SOCMANAGER_MSGSUB_RESET_LENGTH))
    {
        payload[2] = IPC_GROUP_POWER_ID;
        payload[3] = IPC_S2M_POWER_MSGMAJOR_SOCMANAGER_ID;
        payload[4] = IPC_S2M_POWER_SOCMANAGER_MSGSUB_RESET_ID;
        payload[5] = IPC_GET_BYTE(data->u8Parameter, 0);
        payload[6] = IPC_GET_BYTE(data->u8Describe, 0);
        totalLength = IPC_S2M_POWER_SOCMANAGER_MSGSUB_RESET_LENGTH + 5;
        payload[0] = (uint8_t)(totalLength >> 8);
        payload[1] = (uint8_t)(totalLength);
        ret = (int32_t)totalLength;
    }
    return ret;
}
/* Parse function of sub message Reset */
int32_t IPC_S2M_POWERSocManagerReset_Parse(IPC_S2M_POWERSocManagerReset_t *data, uint8_t *payload, uint16_t length)
{
    int32_t ret = -1;
    if((payload != NULL) && (data != NULL) &&
        (IPC_S2M_POWER_SOCMANAGER_MSGSUB_RESET_LENGTH == length))
    {
        IPC_GET_BYTE(data->u8Parameter, 0) = payload[0];
        IPC_GET_BYTE(data->u8Describe, 0) = payload[1];
        ret = 0;
    }
    return ret;
}
/* Pack function of sub message QnxResponseMCURequest */
int32_t IPC_S2M_POWERSocManagerQnxResponseMCURequest_Pack(IPC_S2M_POWERSocManagerQnxResponseMCURequest_t *data, uint8_t *payload, uint16_t length)
{
    int32_t ret = -1;
    uint16_t totalLength;

    if((data != NULL) && (payload != NULL) &&
        (length >= IPC_S2M_POWER_SOCMANAGER_MSGSUB_QNXRESPONSEMCUREQUEST_LENGTH))
    {
        payload[2] = IPC_GROUP_POWER_ID;
        payload[3] = IPC_S2M_POWER_MSGMAJOR_SOCMANAGER_ID;
        payload[4] = IPC_S2M_POWER_SOCMANAGER_MSGSUB_QNXRESPONSEMCUREQUEST_ID;
        payload[5] = IPC_GET_BYTE(data->QnxResponseMCURequest, 0);
        totalLength = IPC_S2M_POWER_SOCMANAGER_MSGSUB_QNXRESPONSEMCUREQUEST_LENGTH + 5;
        payload[0] = (uint8_t)(totalLength >> 8);
        payload[1] = (uint8_t)(totalLength);
        ret = (int32_t)totalLength;
    }
    return ret;
}
/* Parse function of sub message QnxResponseMCURequest */
int32_t IPC_S2M_POWERSocManagerQnxResponseMCURequest_Parse(IPC_S2M_POWERSocManagerQnxResponseMCURequest_t *data, uint8_t *payload, uint16_t length)
{
    int32_t ret = -1;
    if((payload != NULL) && (data != NULL) &&
        (IPC_S2M_POWER_SOCMANAGER_MSGSUB_QNXRESPONSEMCUREQUEST_LENGTH == length))
    {
        IPC_GET_BYTE(data->QnxResponseMCURequest, 0) = payload[0];
        ret = 0;
    }
    return ret;
}
/* Pack function of sub message QnxInfoMCUSystem */
int32_t IPC_S2M_POWERSocManagerQnxInfoMCUSystem_Pack(IPC_S2M_POWERSocManagerQnxInfoMCUSystem_t *data, uint8_t *payload, uint16_t length)
{
    int32_t ret = -1;
    uint16_t totalLength;

    if((data != NULL) && (payload != NULL) &&
        (length >= IPC_S2M_POWER_SOCMANAGER_MSGSUB_QNXINFOMCUSYSTEM_LENGTH))
    {
        payload[2] = IPC_GROUP_POWER_ID;
        payload[3] = IPC_S2M_POWER_MSGMAJOR_SOCMANAGER_ID;
        payload[4] = IPC_S2M_POWER_SOCMANAGER_MSGSUB_QNXINFOMCUSYSTEM_ID;
        payload[5] = IPC_GET_BYTE(data->u8Parameter, 0);
        totalLength = IPC_S2M_POWER_SOCMANAGER_MSGSUB_QNXINFOMCUSYSTEM_LENGTH + 5;
        payload[0] = (uint8_t)(totalLength >> 8);
        payload[1] = (uint8_t)(totalLength);
        ret = (int32_t)totalLength;
    }
    return ret;
}
/* Parse function of sub message QnxInfoMCUSystem */
int32_t IPC_S2M_POWERSocManagerQnxInfoMCUSystem_Parse(IPC_S2M_POWERSocManagerQnxInfoMCUSystem_t *data, uint8_t *payload, uint16_t length)
{
    int32_t ret = -1;
    if((payload != NULL) && (data != NULL) &&
        (IPC_S2M_POWER_SOCMANAGER_MSGSUB_QNXINFOMCUSYSTEM_LENGTH == length))
    {
        IPC_GET_BYTE(data->u8Parameter, 0) = payload[0];
        ret = 0;
    }
    return ret;
}
/* Pack function of sub message QnxQueryVersion */
int32_t IPC_S2M_POWERSocManagerQnxQueryVersion_Pack(IPC_S2M_POWERSocManagerQnxQueryVersion_t *data, uint8_t *payload, uint16_t length)
{
    int32_t ret = -1;
    uint16_t totalLength;

    if((data != NULL) && (payload != NULL) &&
        (length >= IPC_S2M_POWER_SOCMANAGER_MSGSUB_QNXQUERYVERSION_LENGTH))
    {
        payload[2] = IPC_GROUP_POWER_ID;
        payload[3] = IPC_S2M_POWER_MSGMAJOR_SOCMANAGER_ID;
        payload[4] = IPC_S2M_POWER_SOCMANAGER_MSGSUB_QNXQUERYVERSION_ID;
        payload[5] = IPC_GET_BYTE(data->u8Reserved, 0);
        totalLength = IPC_S2M_POWER_SOCMANAGER_MSGSUB_QNXQUERYVERSION_LENGTH + 5;
        payload[0] = (uint8_t)(totalLength >> 8);
        payload[1] = (uint8_t)(totalLength);
        ret = (int32_t)totalLength;
    }
    return ret;
}
/* Parse function of sub message QnxQueryVersion */
int32_t IPC_S2M_POWERSocManagerQnxQueryVersion_Parse(IPC_S2M_POWERSocManagerQnxQueryVersion_t *data, uint8_t *payload, uint16_t length)
{
    int32_t ret = -1;
    if((payload != NULL) && (data != NULL) &&
        (IPC_S2M_POWER_SOCMANAGER_MSGSUB_QNXQUERYVERSION_LENGTH == length))
    {
        IPC_GET_BYTE(data->u8Reserved, 0) = payload[0];
        ret = 0;
    }
    return ret;
}
/* Message Major: SystemState */
/* Pack function of sub message IVI_State */
int32_t IPC_S2M_POWERSystemStateIVI_State_Pack(IPC_S2M_POWERSystemStateIVI_State_t *data, uint8_t *payload, uint16_t length)
{
    int32_t ret = -1;
    uint16_t totalLength;

    if((data != NULL) && (payload != NULL) &&
        (length >= IPC_S2M_POWER_SYSTEMSTATE_MSGSUB_IVI_STATE_LENGTH))
    {
        payload[2] = IPC_GROUP_POWER_ID;
        payload[3] = IPC_S2M_POWER_MSGMAJOR_SYSTEMSTATE_ID;
        payload[4] = IPC_S2M_POWER_SYSTEMSTATE_MSGSUB_IVI_STATE_ID;
        payload[5] = IPC_GET_BYTE(data->TransferResponse, 0);
        totalLength = IPC_S2M_POWER_SYSTEMSTATE_MSGSUB_IVI_STATE_LENGTH + 5;
        payload[0] = (uint8_t)(totalLength >> 8);
        payload[1] = (uint8_t)(totalLength);
        ret = (int32_t)totalLength;
    }
    return ret;
}
/* Parse function of sub message IVI_State */
int32_t IPC_S2M_POWERSystemStateIVI_State_Parse(IPC_S2M_POWERSystemStateIVI_State_t *data, uint8_t *payload, uint16_t length)
{
    int32_t ret = -1;
    if((payload != NULL) && (data != NULL) &&
        (IPC_S2M_POWER_SYSTEMSTATE_MSGSUB_IVI_STATE_LENGTH == length))
    {
        IPC_GET_BYTE(data->TransferResponse, 0) = payload[0];
        ret = 0;
    }
    return ret;
}
