/* --COPYRIGHT--,BSD
 * Copyright (c) 2017, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
//*****************************************************************************
// CAPT_Interface.c
//
// \version 1.70.00.03
// Released on July 30, 2018
//
//*****************************************************************************
//*****************************************************************************
//! \addtogroup CAPT_Interface
//! @{
//*****************************************************************************

#include "CAPT_CommConfig.h"
#include "CAPT_ByteQueue.h"
#include "CAPT_PingPongBuffer.h"
#include "CAPT_Protocol.h"
#include "rom_captivate.h"
#include "rom_map_captivate.h"
#include "UART.h"
#include "I2CSlave.h"
#include "CAPT_Interface.h"

//
// If an interface is selected, include the interface layer
//
#if (CAPT_INTERFACE!=__CAPT_NO_INTERFACE__)

//
// If the serial interface is a bulk interface (for communication with the
// Captivate Design Center), include a byte queue and a ping pong buffer.
//
#if ((CAPT_INTERFACE==__CAPT_BULKI2C_INTERFACE__) || (CAPT_INTERFACE==__CAPT_UART_INTERFACE__))

//*****************************************************************************
//
//! static g_ui8TransmitBuffer_ping is the transmit "ping" buffer, used in
//! conjunction with g_ui8TransmitBuffer_pong by g_PingPongBuffer.
//
//*****************************************************************************
static uint8_t g_ui8TransmitBuffer_ping[CAPT_TRANSMIT_BUFFER_SIZE];

//*****************************************************************************
//
//! \static g_ui8TransmitBuffer_pong is the transmit "pong" buffer, used in
//! conjunction with g_ui8TransmitBuffer_ping by g_PingPongBuffer.
//
//*****************************************************************************
static uint8_t g_ui8TransmitBuffer_pong[CAPT_TRANSMIT_BUFFER_SIZE];

//*****************************************************************************
//
//! \static g_ui8TransmitBuffer_pong is the receive buffer, used by g_ReceiveQueue
//! for incoming serial buffering.
//
//*****************************************************************************
static uint8_t g_ui8QueueBuffer[CAPT_QUEUE_BUFFER_SIZE];

//*****************************************************************************
//
//! \static g_PingPongBuffer is the transmit ping-pong buffer.
//
//*****************************************************************************
static tPingPongBuffer g_PingPongBuffer;

//*****************************************************************************
//
//! \static g_ReceiveQueue is the receive byte queue.
//
//*****************************************************************************
static tByteQueue g_ReceiveQueue;

//*****************************************************************************
//
//! \static tTLProtocolProcessingVariables contains the global variables used by
//! the TL_Protocol layer during incoming data processing.
//
//*****************************************************************************
static tTLProtocolProcessingVariables g_protocolProcessingVars;

//*****************************************************************************
//
//! \static g_parameterPacket is a structure for holding a parameter packet both
//! during framing when received, and during processing and transmit.
//
//*****************************************************************************
static tParameterPacket g_parameterPacket;

#endif /* ((CAPT_INTERFACE==__CAPT_BULKI2C_INTERFACE__) || (CAPT_INTERFACE==__CAPT_UART_INTERFACE__)) */

//*****************************************************************************
//
//! \static g_bReCalibrationRequired indicates whether a re-calibration is
//! pending to the application layer.
//
//*****************************************************************************
static bool g_bReCalibrationRequired;

//*****************************************************************************
//
//! \static *g_pApp holds a pointer to the application
//! global variable structure.  This allows transmission APIs to check whether
//! element or sensor data transmit is enabled or disabled.
//
//*****************************************************************************
static tCaptivateApplication *g_pApp;

//*****************************************************************************
//
//! Interpret Controller Parameter Command. This API checks to see if a
//! parameter packet has a CMD that matches a supported controller CMD.  If it
//! does, then the parameter is read or written.
//
//! \param pPacket specifies the packet containing command to be processed.
//! \return tTLParameterAccessResult type specifying whether any system
//! actions are required after the parameter specified is updated.
//
//*****************************************************************************
static tTLParameterAccessResult CAPT_accessControllerParameter(
		tParameterPacket *pPacket);

#if 	(CAPT_INTERFACE==__CAPT_UART_INTERFACE__)

static bool CAPT_UARTReceiveHandler(uint8_t ui8Data)
{
	MAP_CAPT_pushOntoByteQueue(
			&g_ReceiveQueue,
			ui8Data
		);
	return true;
}

static const tUARTPort g_UARTPort =
{
	.pbReceiveCallback = CAPT_UARTReceiveHandler,
	.pbErrorCallback = 0,
	.peripheralParameters.selectClockSource = EUSCI_A_UART_CLOCKSOURCE_SMCLK,
	.peripheralParameters.clockPrescalar = UART__PRESCALER,
	.peripheralParameters.firstModReg = UART__FIRST_STAGE_MOD,
	.peripheralParameters.secondModReg = UART__SECOND_STAGE_MOD,
	.peripheralParameters.parity = EUSCI_A_UART_NO_PARITY,
	.peripheralParameters.msborLsbFirst = EUSCI_A_UART_LSB_FIRST,
	.peripheralParameters.numberofStopBits = EUSCI_A_UART_ONE_STOP_BIT,
	.peripheralParameters.uartMode = EUSCI_A_UART_MODE,
	.peripheralParameters.overSampling = UART__SAMPLING_MODE
};

#elif 	(CAPT_INTERFACE==__CAPT_BULKI2C_INTERFACE__)

static uint8_t g_ui8I2CReceiveBuffer[CAPT_I2C_RECEIVE_BUFFER_SIZE];

static bool CAPT_I2CBulkReceiveHandler(uint16_t ui16Cnt)
{
	uint16_t ui16Index;

	for (ui16Index=0; ui16Index<ui16Cnt; ui16Index++)
	{
		(void)MAP_CAPT_pushOntoByteQueue(
				&g_ReceiveQueue,
				g_ui8I2CReceiveBuffer[ui16Index]
			);
	}
	return true;
}

static const tI2CSlavePort g_I2CSlavePort =
{
	.pbReceiveCallback = CAPT_I2CBulkReceiveHandler,
	.pvErrorCallback = 0,
	.pReceiveBuffer = g_ui8I2CReceiveBuffer,
	.ui16ReceiveBufferSize = CAPT_I2C_RECEIVE_BUFFER_SIZE,
	.bSendReadLengthFirst = true
};

#elif 	(CAPT_INTERFACE==__CAPT_REGISTERI2C_INTERFACE__)
static uint8_t g_ui8I2CDataBuffer[CAPT_I2C_REGISTER_RW_BUFFER_SIZE];
static bool CAPT_I2CRegisterReceiveHandler(uint16_t ui16Cnt)
{
	tTLParameterAccessResult actionAfterParamterAccess;
	
	if (ui16Cnt < 2)
	{
		return false;
	}

	//
	// If the master is requesting a sensor packet, enter here
	//
	if (g_ui8I2CDataBuffer[TL_PCKT_CMD_FIELD] == TL_SENSOR_PACKET_CMD)
	{
		(void)MAP_CAPT_getSensorPacket(
				g_pApp->pSensorList,
				g_ui8I2CDataBuffer[TL_SENSOR_PCKT_ID_FIELD],
				g_ui8I2CDataBuffer
			);
	}

	//
	// Else, if the master is requesting a cycle packet, enter here
	//
	else if (g_ui8I2CDataBuffer[TL_PCKT_CMD_FIELD] == TL_CYCLE_PACKET_CMD)
	{
		(void)MAP_CAPT_getCyclePacket(
				g_pApp->pSensorList,
				g_ui8I2CDataBuffer[TL_CYCLE_PCKT_ID_FIELD],
				g_ui8I2CDataBuffer[TL_CYCLE_PCKT_CYCLE_FIELD],
				g_ui8I2CDataBuffer
			);
	}

	//
	// Else, assume the master is requesting a parameter packet and enter here
	//
	else
	{
		if (g_ui8I2CDataBuffer[TL_PCKT_CMD_FIELD] < TL_PARAM_CMD_CTRL_MASK)
		{
			actionAfterParamterAccess = MAP_CAPT_accessSensorParameter(
					g_pApp->pSensorList,
					(tParameterPacket*)g_ui8I2CDataBuffer
				);
		}
		else
		{
			actionAfterParamterAccess = CAPT_accessControllerParameter((tParameterPacket*)g_ui8I2CDataBuffer);
		}

		if (actionAfterParamterAccess == eValidCmdWithReCalibrate)
		{
			g_bReCalibrationRequired = true;
		}
	}

	//
	// Return false to exit with the CPU in its previous state.
	// Since the response packet generation was handled immediately here,
	// there is no need to exit active.
	//
	return false;
}

static const tI2CSlavePort g_I2CSlavePort =
{
	.pbReceiveCallback = CAPT_I2CRegisterReceiveHandler,
	.pvErrorCallback = 0,
	.pReceiveBuffer = (g_ui8I2CDataBuffer + TL_PCKT_SERIAL_OVRHD_LENGTH),
	.ui16ReceiveBufferSize = (TL_PARAMETER_DATA_LENGTH + TL_PCKT_CHKSUM_LENGTH),
	.bSendReadLengthFirst = false
};

#endif

void CAPT_initCommInterface(tCaptivateApplication *pApp)
{
	g_pApp = pApp;

#if ((CAPT_INTERFACE==__CAPT_BULKI2C_INTERFACE__) || (CAPT_INTERFACE==__CAPT_UART_INTERFACE__))

	(void)MAP_CAPT_initByteQueue(
			&g_ReceiveQueue,
			g_ui8QueueBuffer,
			CAPT_QUEUE_BUFFER_SIZE
		);

	(void)MAP_CAPT_initPingPongBuffer(
			&g_PingPongBuffer,
			g_ui8TransmitBuffer_ping,
			g_ui8TransmitBuffer_pong
		);

	g_protocolProcessingVars.bStuffedByteDetected = false;
	g_protocolProcessingVars.i8currPacketIndex = -1;



	g_parameterPacket.ui8Sync = TL_PROTOCOL_SYNC;
	g_parameterPacket.ui8Blank = TL_PROTOCOL_BLANK;
	g_parameterPacket.ui8Length = TL_PARAMETER_PACKET_LENGTH - TL_PCKT_SERIAL_OVRHD_LENGTH;
	g_bReCalibrationRequired = false;
#endif
#if 	(CAPT_INTERFACE==__CAPT_UART_INTERFACE__)
	UART_openPort(&g_UARTPort);
#elif	(CAPT_INTERFACE==__CAPT_BULKI2C_INTERFACE__)
	I2CSlave_openPort(&g_I2CSlavePort);
#elif 	(CAPT_INTERFACE==__CAPT_REGISTERI2C_INTERFACE__)
	I2CSlave_openPort(&g_I2CSlavePort);
	I2CSlave_setTransmitBuffer(
			(g_ui8I2CDataBuffer + TL_PCKT_SERIAL_OVRHD_LENGTH),
			(CAPT_I2C_REGISTER_RW_BUFFER_SIZE - TL_PCKT_SERIAL_OVRHD_LENGTH)
		);
#endif /* CAPT_INTERFACE SELECTION */

}

bool CAPT_writeElementData(uint8_t ui8SensorID)
{
#if ((CAPT_INTERFACE==__CAPT_BULKI2C_INTERFACE__) || (CAPT_INTERFACE==__CAPT_UART_INTERFACE__))
	uint8_t ui8Cycle;
	uint16_t ui16Length;

	//
	// Ensure that element transmission is enabled, and sensor ID is valid
	//
	if ((g_pApp->bElementDataTxEnable == false)
		|| (g_pApp->pSensorList[ui8SensorID] == 0))
	{
		return false;
	}

	//
	// Transmit element data one cycle at a time.
	//
	for (ui8Cycle = 0;
			ui8Cycle < g_pApp->pSensorList[ui8SensorID]->ui8NrOfCycles;
			ui8Cycle++)
	{
		ui16Length = MAP_CAPT_getCyclePacket(g_pApp->pSensorList,
				ui8SensorID, ui8Cycle, g_PingPongBuffer.pEditBuffer);
		if (ui16Length==0)
		{
			return false;
		}

#if 	(CAPT_INTERFACE==__CAPT_UART_INTERFACE__)
		ui16Length = MAP_CAPT_stuffSyncBytes(g_PingPongBuffer.pEditBuffer,
				ui16Length);
		(void)MAP_CAPT_togglePingPongBuffer(&g_PingPongBuffer);
		UART_transmitBuffer(g_PingPongBuffer.pTransmitBuffer, ui16Length);
#elif	(CAPT_INTERFACE==__CAPT_BULKI2C_INTERFACE__)
		(void)MAP_CAPT_togglePingPongBuffer(&g_PingPongBuffer);
		I2CSlave_setTransmitBuffer(
				(g_PingPongBuffer.pTransmitBuffer+TL_PCKT_SERIAL_OVRHD_LENGTH),
				(ui16Length-TL_PCKT_SERIAL_OVRHD_LENGTH)
			);
		I2CSlave_setRequestFlag();
#endif /* CAPT_INTERFACE SELECTION */
	}

	return true;
#else
	return false;
#endif
}

bool CAPT_writeSensorData(uint8_t ui8SensorID)
{
#if ((CAPT_INTERFACE==__CAPT_BULKI2C_INTERFACE__) || (CAPT_INTERFACE==__CAPT_UART_INTERFACE__))

	uint16_t ui16Length;

	if ((g_pApp->bSensorDataTxEnable == false)
			|| (g_pApp->pSensorList[ui8SensorID] == 0))
	{
		return false;
	}
	ui16Length = MAP_CAPT_getSensorPacket(g_pApp->pSensorList,
			ui8SensorID, g_PingPongBuffer.pEditBuffer);
	if (ui16Length==0)
	{
		return false;
	}

#if 	(CAPT_INTERFACE==__CAPT_UART_INTERFACE__)
		ui16Length = MAP_CAPT_stuffSyncBytes(g_PingPongBuffer.pEditBuffer,
				ui16Length);
		(void)MAP_CAPT_togglePingPongBuffer(&g_PingPongBuffer);
		UART_transmitBuffer(g_PingPongBuffer.pTransmitBuffer, ui16Length);
#elif	(CAPT_INTERFACE==__CAPT_BULKI2C_INTERFACE__)
		(void)MAP_CAPT_togglePingPongBuffer(&g_PingPongBuffer);
		I2CSlave_setTransmitBuffer(
				(g_PingPongBuffer.pTransmitBuffer+TL_PCKT_SERIAL_OVRHD_LENGTH),
				(ui16Length-TL_PCKT_SERIAL_OVRHD_LENGTH)
			);
		I2CSlave_setRequestFlag();
#endif /* CAPT_INTERFACE SELECTION */

	return true;
#else
	return false;
#endif
}

bool CAPT_writeGeneralPurposeData(uint16_t *pData, uint8_t ui8Cnt)
{
#if ((CAPT_INTERFACE==__CAPT_BULKI2C_INTERFACE__) || (CAPT_INTERFACE==__CAPT_UART_INTERFACE__))

	uint16_t ui16Length;

	ui16Length = CAPT_getGeneralPurposePacket(pData,
			ui8Cnt, g_PingPongBuffer.pEditBuffer);
	if (ui16Length==0)
	{
		return false;
	}

#if 	(CAPT_INTERFACE==__CAPT_UART_INTERFACE__)
		ui16Length = MAP_CAPT_stuffSyncBytes(g_PingPongBuffer.pEditBuffer,
				ui16Length);
		(void)MAP_CAPT_togglePingPongBuffer(&g_PingPongBuffer);
		UART_transmitBuffer(g_PingPongBuffer.pTransmitBuffer, ui16Length);
#elif	(CAPT_INTERFACE==__CAPT_BULKI2C_INTERFACE__)
		(void)MAP_CAPT_togglePingPongBuffer(&g_PingPongBuffer);
		I2CSlave_setTransmitBuffer(
				(g_PingPongBuffer.pTransmitBuffer+TL_PCKT_SERIAL_OVRHD_LENGTH),
				(ui16Length-TL_PCKT_SERIAL_OVRHD_LENGTH)
			);
		I2CSlave_setRequestFlag();
#endif /* CAPT_INTERFACE SELECTION */

	return true;
#else
	return false;
#endif
}

bool CAPT_writeString(const char *pSrcString)
{
#if ((CAPT_INTERFACE==__CAPT_BULKI2C_INTERFACE__) || (CAPT_INTERFACE==__CAPT_UART_INTERFACE__))

	uint16_t ui16Length;

	ui16Length = CAPT_getStringPacket(pSrcString, g_PingPongBuffer.pEditBuffer);
	if (ui16Length==0)
	{
		return false;
	}

#if 	(CAPT_INTERFACE==__CAPT_UART_INTERFACE__)
		ui16Length = MAP_CAPT_stuffSyncBytes(g_PingPongBuffer.pEditBuffer,
				ui16Length);
		(void)MAP_CAPT_togglePingPongBuffer(&g_PingPongBuffer);
		UART_transmitBuffer(g_PingPongBuffer.pTransmitBuffer, ui16Length);
#elif	(CAPT_INTERFACE==__CAPT_BULKI2C_INTERFACE__)
		(void)MAP_CAPT_togglePingPongBuffer(&g_PingPongBuffer);
		I2CSlave_setTransmitBuffer(
				(g_PingPongBuffer.pTransmitBuffer+TL_PCKT_SERIAL_OVRHD_LENGTH),
				(ui16Length-TL_PCKT_SERIAL_OVRHD_LENGTH)
			);
		I2CSlave_setRequestFlag();
#endif /* CAPT_INTERFACE SELECTION */

	return true;
#else
	return false;
#endif
}

bool CAPT_writeTrackPadSensorData(uint8_t ui8SensorID)
{
#if ((CAPT_INTERFACE==__CAPT_BULKI2C_INTERFACE__) || (CAPT_INTERFACE==__CAPT_UART_INTERFACE__))

	uint16_t ui16Length;

	if ((g_pApp->bSensorDataTxEnable == false) || (ui8SensorID == 0xFF))
	{
		return false;
	}
	ui16Length = CAPT_getTrackPadPacket(g_pApp->pSensorList[ui8SensorID],
			ui8SensorID, g_PingPongBuffer.pEditBuffer);
	if (ui16Length==0)
	{		return false;
	}

	 /* CAPT_INTERFACE SELECTION */
#if 	(CAPT_INTERFACE==__CAPT_UART_INTERFACE__)
		ui16Length = MAP_CAPT_stuffSyncBytes(g_PingPongBuffer.pEditBuffer,
				ui16Length);
		(void)MAP_CAPT_togglePingPongBuffer(&g_PingPongBuffer);
		UART_transmitBuffer(g_PingPongBuffer.pTransmitBuffer, ui16Length);
#elif	(CAPT_INTERFACE==__CAPT_BULKI2C_INTERFACE__)
		(void)MAP_CAPT_togglePingPongBuffer(&g_PingPongBuffer);
		I2CSlave_setTransmitBuffer(
				(g_PingPongBuffer.pTransmitBuffer+TL_PCKT_SERIAL_OVRHD_LENGTH),
				(ui16Length-TL_PCKT_SERIAL_OVRHD_LENGTH)
			);
		I2CSlave_setRequestFlag();
#endif

	return true;
#else
	return false;
#endif
}

bool CAPT_writeTrackPadSensorStatus(uint8_t ui8SensorID)
{
#if ((CAPT_INTERFACE==__CAPT_BULKI2C_INTERFACE__) || (CAPT_INTERFACE==__CAPT_UART_INTERFACE__))

    uint16_t ui16Length;

    if ((g_pApp->bSensorDataTxEnable == false) || (ui8SensorID == 0xFF))
    {
        return false;
    }
    ui16Length = CAPT_getTrackPadSensorStatusPacket(g_pApp->pSensorList,
            ui8SensorID, g_PingPongBuffer.pEditBuffer);
    if (ui16Length==0)
    {       return false;
    }

     /* CAPT_INTERFACE SELECTION */
#if     (CAPT_INTERFACE==__CAPT_UART_INTERFACE__)
        ui16Length = MAP_CAPT_stuffSyncBytes(g_PingPongBuffer.pEditBuffer,
                ui16Length);
        (void)MAP_CAPT_togglePingPongBuffer(&g_PingPongBuffer);
        UART_transmitBuffer(g_PingPongBuffer.pTransmitBuffer, ui16Length);
#elif   (CAPT_INTERFACE==__CAPT_BULKI2C_INTERFACE__)
        (void)MAP_CAPT_togglePingPongBuffer(&g_PingPongBuffer);
        I2CSlave_setTransmitBuffer(
                (g_PingPongBuffer.pTransmitBuffer+TL_PCKT_SERIAL_OVRHD_LENGTH),
                (ui16Length-TL_PCKT_SERIAL_OVRHD_LENGTH)
            );
        I2CSlave_setRequestFlag();
#endif

	return true;
#else
	return false;
#endif
}

bool CAPT_checkForInboundPacket(void)
{
#if ((CAPT_INTERFACE==__CAPT_BULKI2C_INTERFACE__) || (CAPT_INTERFACE==__CAPT_UART_INTERFACE__))

	bool bGotPacket = false;
	uint16_t ui16TransmitLength;
	tTLParameterAccessResult actionAfterParamterAccess;

	actionAfterParamterAccess = eInvalidCmd;

	bGotPacket = MAP_CAPT_processReceivedData(&g_ReceiveQueue,
			&g_parameterPacket, &g_protocolProcessingVars);

	if (bGotPacket)
	{
		bGotPacket = false;

		//
		// Access the parameter
		//
		if (g_parameterPacket.ui8Command == TL_PARAM_CMD_OFFSET_SUBTRACTION)
		{
			//
			// Do nothing; this means a deprecated command was sent.
			//
			__no_operation();
		}
#if (CAPT_TRACKPAD_ENABLE==true)

		else if((g_parameterPacket.ui8Command < TL_PARAM_CMD_GENERIC_MASK))
				{
					actionAfterParamterAccess = CAPT_accessTrackPadSensorParameter(
							g_pApp->pSensorList,
							&g_parameterPacket
						);
		}
#endif
		else if (g_parameterPacket.ui8Command < TL_PARAM_CMD_CTRL_MASK)
		{
			actionAfterParamterAccess = MAP_CAPT_accessSensorParameter(
					g_pApp->pSensorList,
					&g_parameterPacket
				);
		}
		else if (g_parameterPacket.ui8Command < TL_PARAM_CMD_SPECIAL_MASK)
		{
			actionAfterParamterAccess = CAPT_accessControllerParameter(&g_parameterPacket);
		}
		else
		{
			actionAfterParamterAccess = CAPT_accessSpecialSensorParameter(
					g_pApp->pSensorList,
					&g_parameterPacket
				);
		}

		switch (actionAfterParamterAccess)
		{
			case eInvalidCmd:
				__no_operation();
				break;
			case eValidCmd:
				__no_operation();
				break;
			case eValidCmdWithReCalibrate:
				g_bReCalibrationRequired = true;
				__no_operation();
				break;
			default:
				break;
		}

		//
		// Respond back to host
		//
		g_parameterPacket.ui16Checksum = CAPT_getChecksum(
				&g_parameterPacket.ui8Packet[TL_PCKT_SERIAL_OVRHD_LENGTH],
				TL_PARAMETER_DATA_LENGTH);
		memcpy(
				(void*)g_PingPongBuffer.pEditBuffer, 
				(void*)g_parameterPacket.ui8Packet, 
				TL_PARAMETER_PACKET_LENGTH
			);
#if 	(CAPT_INTERFACE==__CAPT_UART_INTERFACE__)
		ui16TransmitLength = MAP_CAPT_stuffSyncBytes(g_PingPongBuffer.pEditBuffer,
				TL_PARAMETER_PACKET_LENGTH);
		(void)MAP_CAPT_togglePingPongBuffer(&g_PingPongBuffer);
		UART_transmitBuffer(g_PingPongBuffer.pTransmitBuffer, ui16TransmitLength);
#elif	(CAPT_INTERFACE==__CAPT_BULKI2C_INTERFACE__)
		(void)MAP_CAPT_togglePingPongBuffer(&g_PingPongBuffer);
		ui16TransmitLength = TL_PARAMETER_PACKET_LENGTH-TL_PCKT_SERIAL_OVRHD_LENGTH;
		I2CSlave_setTransmitBuffer(
				(g_PingPongBuffer.pTransmitBuffer+TL_PCKT_SERIAL_OVRHD_LENGTH),
				ui16TransmitLength
			);
		I2CSlave_setRequestFlag();
#endif /* CAPT_INTERFACE SELECTION */
	}

	return bGotPacket;

#else
	return false;
#endif
}

tTLParameterAccessResult CAPT_accessControllerParameter(
		tParameterPacket *pPacket)
{
	tTLParameterAccessResult returnInfo = eValidCmd;

	switch (pPacket->ui8Command)
	{
		// Element Packet Transmit Enable
		case TL_PARAM_CMD_CTRL_ELEMENTTXEN:
			if (pPacket->ui8Write == TL_PROTOCOL_WRITE)
			{
				g_pApp->bElementDataTxEnable = (bool)pPacket->ui8Param2;
			}
			else
			{
				pPacket->ui8Param2 = (uint8_t)g_pApp->bElementDataTxEnable;
			}
			break;

		// Sensor Packet Transmit Enable
		case TL_PARAM_CMD_CTRL_SENSORTXEN:
			if (pPacket->ui8Write == TL_PROTOCOL_WRITE)
			{
				g_pApp->bSensorDataTxEnable = (bool)pPacket->ui8Param2;
			}
			else
			{
				pPacket->ui8Param2 = (uint8_t)g_pApp->bSensorDataTxEnable;
			}
			break;

		// Active Report Rate
		case TL_PARAM_CMD_CTRL_REPORTRATE_ACTIVE:
			if (pPacket->ui8Write == TL_PROTOCOL_WRITE)
			{
				g_pApp->ui16ActiveModeScanPeriod = pPacket->ui8Param2 | (pPacket->ui8Param3 << 8);
				if (g_pApp->state == eUIActive)
				{
					MAP_CAPT_stopTimer();
					MAP_CAPT_clearTimer();
					MAP_CAPT_writeTimerCompRegister(CAPT_MS_TO_CYCLES(g_pApp->ui16ActiveModeScanPeriod));
					MAP_CAPT_startTimer();
				}
			}
			else
			{
				pPacket->ui8Param2 = (uint8_t)(g_pApp->ui16ActiveModeScanPeriod);
				pPacket->ui8Param3 = (uint8_t)(g_pApp->ui16ActiveModeScanPeriod >> 8);
			}
			break;

		// Autonomous Report Rate
		case TL_PARAM_CMD_CTRL_REPORTRATE_AUTO:
			if (pPacket->ui8Write == TL_PROTOCOL_WRITE)
			{
				g_pApp->ui16WakeOnProxModeScanPeriod = pPacket->ui8Param2 | (pPacket->ui8Param3 << 8);
				if (g_pApp->state == eUIWakeOnProx)
				{
					MAP_CAPT_stopTimer();
					MAP_CAPT_clearTimer();
					MAP_CAPT_writeTimerCompRegister(CAPT_MS_TO_CYCLES(g_pApp->ui16WakeOnProxModeScanPeriod));
					MAP_CAPT_startTimer();
				}
			}
			else
			{
				pPacket->ui8Param2 = (uint8_t)(g_pApp->ui16WakeOnProxModeScanPeriod);
				pPacket->ui8Param3 = (uint8_t)(g_pApp->ui16WakeOnProxModeScanPeriod >> 8);
			}
			break;
			
		// Wakeup Interval
		case TL_PARAM_CMD_CTRL_WAKEINTERVAL_AUTO:
			if (pPacket->ui8Write == TL_PROTOCOL_WRITE)
			{
				g_pApp->ui8WakeupInterval = pPacket->ui8Param2;
			}
			else
			{
				pPacket->ui8Param2 = (g_pApp->ui8WakeupInterval);
			}
			break;
			
		// Timeout Period (in samples)
		case TL_PARAM_CMD_CTRL_TIMEOUT_ACTIVE:
			if (pPacket->ui8Write == TL_PROTOCOL_WRITE)
			{
				g_pApp->ui16InactivityTimeout = pPacket->ui8Param2 | (pPacket->ui8Param3 << 8);
			}
			else
			{
				pPacket->ui8Param2 = (uint8_t)(g_pApp->ui16InactivityTimeout);
				pPacket->ui8Param3 = (uint8_t)(g_pApp->ui16InactivityTimeout >> 8);
			}
			break;

		// Valid controller command not found, return invalid command!
		default:
			returnInfo = eInvalidCmd;
			break;
	}

	return returnInfo;
}

bool CAPT_checkForRecalibrationRequest(void)
{
	if (g_bReCalibrationRequired)
	{
		g_bReCalibrationRequired = false;
		return true;
	}
	else
	{
		return false;
	}
}

#endif /*  CAPT_INTERFACE != __CAPT_NO_INTERFACE__ */

//*****************************************************************************
//! Close the doxygen group
//! @}
//*****************************************************************************
