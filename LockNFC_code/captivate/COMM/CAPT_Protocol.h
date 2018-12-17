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
// CAPT_Protocol.h
//
//! Packet generator and interpretor for CapTIvate&tm; protocol.
//
//! \version 1.70.00.03
//! Released on July 30, 2018
//
//*****************************************************************************
//*****************************************************************************
//! \addtogroup CAPT_Protocol
//! @{
//*****************************************************************************

#ifndef CAPT_PROTOCOL_H_
#define CAPT_PROTOCOL_H_

#ifndef S_SPLINT_S
#include <stdio.h>
#include <stdbool.h>
#endif

//
// Include ByteQueue for queue APIs
//
#include "CAPT_ByteQueue.h"

//
// Include CAPT_TL_Type for CapTIvate&tm; types
//
#include "CAPT_Type.h"


//*****************************************************************************
//
//! CapTIvate&tm; Protocol Control Bytes
//
//! def TL_PROTOCOL_SYNC defines the CapTIvate&tm; protocol sync byte
//
//! def TL_PROTOCOL_BLANK defines a blanking byte.  This can be anything
//! other than the sync byte.
//
//! def TL_PROTOCOL_READ defines the CapTIvate&tm; protocol read flag
//
//! def TL_PROTOCOL_WRITE defines the CapTIvate&tm; protocol write flag
//
//*****************************************************************************
#define TL_PROTOCOL_SYNC					(0x55)
#define TL_PROTOCOL_BLANK					(0xAA)
#define TL_PROTOCOL_READ					(0x00)
#define TL_PROTOCOL_WRITE					(0x01)

//*****************************************************************************
//
//! CapTIvate&tm; Protocol Command Bytes
//
//! \def TL_SENSOR_PACKET_CMD defines the real-time sensor data command
//! \def TL_CYCLE_PACKET_CMD defines the real-time cycle data command
//! \def TL_GENERAL_PURPOSE_PACKET_CMD defines the gp data command
//! \def TL_STRING_PACKET_CMD defines the string data command
//! \def TL_PARAM_CMD_x defines various CapTIvate&tm; parameter commands, where x
//! is the specific command.
//
//*****************************************************************************
#define TL_SENSOR_PACKET_CMD				(0x00)
#define TL_CYCLE_PACKET_CMD					(0x01)
#define TL_TRACKPAD_PACKET_CMD				(0x02)
#define TL_GENERAL_PURPOSE_PACKET_CMD       (0x10)
#define TL_STRING_PACKET_CMD                (0x3E)

#define TL_PARAM_CMD_GENERIC_MASK			(0x80)
#define TL_PARAM_CMD_SLIDER_WHEEL_MASK		(0x90)
#define TL_PARAM_CMD_TP_MASK				(0xA0)
#define TL_PARAM_CMD_DYCAL_MASK				(0xB0)
#define TL_PARAM_CMD_CTRL_MASK				(0xC0)
#define TL_PARAM_CMD_SPECIAL_MASK			(0xD0)
#define TL_PARAM_CMD_INVALID_MASK			(0xF0)

//
// TRACKPAD PARAMETER COMMANDS
//


#define TL_PARAM_CMD_TRACKPADFILTEREN 		(0x60)
#define TL_PARAM_CMD_TRACKPADFILTERBETA		(0x61)
#define TL_PARAM_CMD_BETATOPSPEED			(0x63)
#define TL_PARAM_CMD_BETABOTTOMSPEED		(0x64)
#define TL_PARAM_CMD_LOWERBETA				(0x65)
#define TL_PARAM_CMD_TRACKPADFILTERTYPE		(0x66)
#define TL_PARAM_CMD_RESOLUTION_X			(0x67)
#define TL_PARAM_CMD_RESOLUTION_Y			(0x68)

#define TL_PARAM_CMD_LOWERTRIM_X			(0x69)
#define TL_PARAM_CMD_UPPERTRIM_X    		(0x6A)
#define TL_PARAM_CMD_LOWERTRIM_Y			(0x6B)
#define TL_PARAM_CMD_UPPERTRIM_Y			(0x6C)
#define TL_PARAM_CMD_CENTERTRIM_X	 		(0x6D)
#define TL_PARAM_CMD_CENTERTRIM_Y  		    (0x6E)
#define TL_PARAM_CMD_CIRCLERADIUS			(0x6F)

//
// TRACKPAD GESTURE COMMANDS
//
#define TL_PARAM_CMD_TAPTIME_MIN    		(0x70)
#define TL_PARAM_CMD_TAPTIME_MAX 			(0x71)
#define TL_PARAM_CMD_SWIPETIME_MAX			(0x72)
#define TL_PARAM_CMD_DBLTAPTIME_MAX 		(0x73)
#define TL_PARAM_CMD_TAPHOLDTIME_MIN		(0x74)
#define TL_PARAM_CMD_SWIPEDISTANCE_MIN  	(0x75)

#define TL_PARAM_CMD_DBLTAPENABLE			(0x76)
#define TL_PARAM_CMD_SWIPEENABLE			(0x77)
#define TL_PARAM_CMD_CIRCLEENABLE			(0x78)
#define TL_PARAM_CMD_ENDTRACKPAD			(0x7F)

//
// TL PARAMETER GENERIC COMMANDS
//
#define TL_PARAM_CMD_CONVERSIONGAIN			(0x80)
#define TL_PARAM_CMD_CONVERSIONCOUNT		(0x81)
#define TL_PARAM_CMD_PROX_THRESH			(0x82)
#define TL_PARAM_CMD_TOUCH_THRESH			(0x83)
#define TL_PARAM_CMD_PROX_DBIN				(0x84)
#define TL_PARAM_CMD_PROX_DBOUT				(0x85)
#define TL_PARAM_CMD_TOUCH_DBIN				(0x86)
#define TL_PARAM_CMD_TOUCH_DBOUT			(0x87)
#define TL_PARAM_CMD_TIMEOUT				(0x88)
#define TL_PARAM_CMD_COUNTFILTEN			(0x89)
#define TL_PARAM_CMD_COUNTFILTBETA			(0x8A)
#define TL_PARAM_CMD_LTAFILTBETA			(0x8B)
#define TL_PARAM_CMD_LTAFILTERHALT			(0x8C)
#define TL_PARAM_CMD_DRIFTRECALENABLE		(0x8D)
#define TL_PARAM_CMD_FORCERECALIBRATE		(0x8E)
#define TL_PARAM_CMD_BIAS_CURRENT			(0x8F)
#define TL_PARAM_CMD_CS_DISCHARGE			(0x95)
#define TL_PARAM_CMD_MODENABLE				(0x96)
#define TL_PARAM_CMD_FREQDIV				(0x97)
#define TL_PARAM_CMD_CPLEN					(0x98)
#define TL_PARAM_CMD_TPLEN					(0x99)
#define TL_PARAM_CMD_ERROR_THRESH			(0x9A)
#define TL_PARAM_CMD_NEG_TOUCH_THRESH		(0x9B)
#define TL_PARAM_CMD_IDLE_STATE				(0x9C)
#define TL_PARAM_CMD_INPUT_SYNC				(0x9D)
#define TL_PARAM_CMD_TIMER_SYNC				(0x9E)
#define TL_PARAM_CMD_LPMCTRL				(0x9F)
#define TL_PARAM_CMD_LTA_SENSOR_PTHALT		(0xA0)
#define TL_PARAM_CMD_LTA_ELEMENT_PTHALT		(0xA1)
#define TL_PARAM_CMD_COARSE_GAIN_RATIO		(0xA2)
#define TL_PARAM_CMD_FINE_GAIN_RATIO		(0xA3)
#define TL_PARAM_CMD_OFFSET_SUBTRACTION		(0xA4) // Deprecated for 1.00.01.00
#define TL_PARAM_CMD_OFFSET_SCALE           (0xD0) // Added for 1.00.01.00
#define TL_PARAM_CMD_OFFSET_LEVEL           (0xD1) // Added for 1.00.01.00

//
// TL PARAMETER SLIDER/WHEEL COMMANDS
//
#define TL_PARAM_CMD_SLIDER_FILTEREN		(0x90)
#define TL_PARAM_CMD_SLIDER_FILTERBETA		(0x91)
#define TL_PARAM_CMD_SLIDER_RES				(0x92)
#define TL_PARAM_CMD_SLIDER_LTRIM			(0x93)
#define TL_PARAM_CMD_SLIDER_UTRIM			(0x94)


//
// TL PARAMETER CONTROLLER COMMANDS
//
#define TL_PARAM_CMD_CTRL_ELEMENTTXEN		(0xC0)
#define TL_PARAM_CMD_CTRL_SENSORTXEN		(0xC1)
#define TL_PARAM_CMD_CTRL_REPORTRATE_ACTIVE	(0xC2)
#define TL_PARAM_CMD_CTRL_REPORTRATE_AUTO	(0xC3)
#define TL_PARAM_CMD_CTRL_WAKEINTERVAL_AUTO	(0xC4)
#define TL_PARAM_CMD_CTRL_TIMEOUT_ACTIVE	(0xC5)

//*****************************************************************************
//
//! CapTIvate&tm; Protocol Length Bytes
//
//! def TL_PCKT_SERIAL_OVRHD_LENGTH specifies the serial overhead length.
//! this includes the sync, blank, and length bytes (3).
//
//! def TL_PCKT_CHKSUM_LENGTH defines the length of the checksum in bytes.
//
//! def TL_CYCLE_STATE_OFFSET specifies the position of the state bytes
//! in the real-time cycle data packet.
//
//! def TL_CYCLE_STATE_LEN specifies the length of the state bytes in
//! the real-time cycle data packet.
//
//! def TL_CYCLE_LEN_PER_ELEMENT specifies the variable length component
//! of the cycle packet (TL_CYCLE_LEN_PER_ELEMENT required per element).
//
//! def TL_CYCLE_OVRHD_LEN defines the length of the cycle packet overhead.
//
//! def TL_SENSOR_PACKET_LENGTH defines the length of the real-time sensor
//! data packet
//
//! def TL_PARAMETER_PACKET_LENGTH defines the length of the parameter packet
//
//! def TL_PARAMETER_DATA_LENGTH defines the length of the data field in the
//! parameter packet.
//
//! def TL_GENERAL_PURPOSE_MAX_CNT defines the general purpose packet max
//! data variable count
//
//! def TL_STRING_MAX_CNT defines the string packet max byte count
//
//*****************************************************************************
#define TL_PCKT_SERIAL_OVRHD_LENGTH			(0x03)
#define TL_PCKT_CHKSUM_LENGTH				(0x02)
#define TL_CYCLE_STATE_OFFSET				(0x06)
#define TL_CYCLE_STATE_LEN					(0x03)
#define TL_CYCLE_LEN_PER_ELEMENT			(0x04)
#define TL_CYCLE_OVRHD_LEN					(0x06)
#define TL_SENSOR_PACKET_LENGTH				(0x0B)
#define TL_PARAMETER_PACKET_LENGTH			(0x0C)
#define TL_PARAMETER_DATA_LENGTH			(0x07)
#define TL_GENERAL_PURPOSE_MAX_CNT          (0x1D)
#define TL_STRING_MAX_CNT                   (0x3A)

//*****************************************************************************
//
//! CapTIvate&tm; Protocol Field Offsets
//
//! def TL_PCKT_CMD_FIELD is the packet offset of the command field.
//
//! def TL_SENSOR_PCKT_ID_FIELD is the sensor packet offset of the ID field.
//
//! def TL_CYCLE_PCKT_ID_FIELD is te cycle packet offset of the sensor
//!      ID field.
//
//! def TL_CYCLE_PCKT_CYCLE_FIELD is the cycle packet offset of the cycle
//!      ID field.
//
//! def TL_PARAM_PCKT_RW_FIELD is the parameter packet offset of the RW field.
//
//! def TL_PARAM_PCKT_ID_FIELD is the parameter packet offset of the ID field.
//
//*****************************************************************************
#define TL_PCKT_CMD_FIELD					(0x03)
#define TL_SENSOR_PCKT_ID_FIELD				(0x04)
#define TL_CYCLE_PCKT_ID_FIELD				(0x04)
#define TL_CYCLE_PCKT_CYCLE_FIELD			(0x05)
#define TL_PARAM_PCKT_RW_FIELD				(0x04)
#define TL_PARAM_PCKT_ID_FIELD				(0x05)

 //*****************************************************************************
//
//! Low level protocol packet builder for trackpad
//
//! This function assembles trackpad packet
//
//! The packet format is:
//! CMD					command byte
//! SENSOR_ID			sensor ID
//! MAX_TOUCHES			# touches supported (MAX = 1 for now)
//! GESTURE				gesture type
//! X_POS_LSB			first touch x-y
//! X_POS_MSB
//! Y_POS_LSB
//! Y_POS_MSB
//! X_POS_LSB			second touch x-y
//! X_POS_MSB
//! Y_POS_LSB
//! Y_POS_MSB
//! .........			repeat for each supported touch
//
//! \param pSensor is pointer to sensor structure
//! \param ui8SensorID is sensor's index in sensor table - see CAPT_UserConfig.c
//! \param pBuffer is pointer to buffer where packet will be placed
//! \par Returns
//!	    None
//
//*****************************************************************************
/*
 * TRACKPAD PACKET BASE LENGTH
 */

#define TL_TRACKPAD_PACKET_BASE_LENGTH		(0x09)


//*****************************************************************************
//
//! typedef tTLProtocolProcessingVariables holds "static" variables that the
//! protocol layer uses during packet framing.  These variables are used by 
//! the CAPT_processReceivedData API.
//
//*****************************************************************************
typedef struct
{
	int8_t i8currPacketIndex;
	bool bStuffedByteDetected;
} tTLProtocolProcessingVariables;

//*****************************************************************************
//
//! typedef tTLParameterAccessResult is a return type for the
//! TL_Protocol_accessParameter API.  It indicates to the application
//! whether an incoming parameter packet was valid, invald, or requires
//! the re-calibration of a sensor.
//
//*****************************************************************************
enum
{
	eInvalidSensor = 0x00,
	eInvalidCmd = 0x01,
	eValidCmd = 0x02,
	eValidCmdWithReCalibrate = 0x03
};
typedef uint8_t tTLParameterAccessResult;


//*****************************************************************************
//
//! typedef tParameterPacket is a union structure that stores a CapTIvate&tm;
//! parameter packet.  The union allows the low-level serial driver to
//! interface with a buffer, while higher-level applications can access
//! specific portions of the packet.
//
//*****************************************************************************
typedef union
{
	struct
	{
		uint8_t ui8Sync;
		uint8_t ui8Blank;
		uint8_t ui8Length;
		uint8_t ui8Command;
		uint8_t ui8Write;
		uint8_t ui8SensorID;
		uint8_t ui8Param0;
		uint8_t ui8Param1;
		uint8_t ui8Param2;
		uint8_t ui8Param3;
		uint16_t ui16Checksum;
	};
	uint8_t ui8Packet[TL_PARAMETER_PACKET_LENGTH];
} tParameterPacket;
extern tTLParameterAccessResult CAPT_accessTrackPadSensorParameter(tSensor **sensorArray, tParameterPacket *pPacket);
//
// TL Protocol API Prototypes
//

//*****************************************************************************
//
//! This API will build a packet to send one time cycle's worth of element
//! information, conforming to the CapTIvate&tm; protocol.  Information sent
//! includes element touch/prox state, current count, and current LTA.
//
//! \param sensorArray is a pointer to the global array of sensor pointers.
//! \param ui8SensorID indicates the ID of the sensor to build a packet for
//! \param ui8Cycle indicates the cycle in the sensor of interest
//! \param pBuffer is a pointer to buffer to place the packet in.
//
//! \par Returns
//!		the length of the packet that was build if a valid sensor was
//! 	found, else 0.
//
//*****************************************************************************
extern uint16_t CAPT_getCyclePacket(tSensor **sensorArray,
		uint8_t ui8SensorID, uint8_t ui8Cycle, uint8_t *pBuffer);

//*****************************************************************************
//
//! This API will build a packet to send sensor state information, 
//! conforming to the CapTIvate&tm; protocol.  Information sent
//! includes dominant button, slider position, global sensor prox/prev touch
//
//! \param sensorArray is a pointer to the global array of sensor pointers.
//! \param ui8SensorID indicates the ID of the sensor to build a packet for
//! \param pBuffer is a pointer to buffer to place the packet in.
//
//! \par Returns
//!		the length of the packet that was build if a valid sensor was
//! 	found, else 0.
//
//*****************************************************************************
extern uint16_t CAPT_getSensorPacket(tSensor **sensorArray,
		uint8_t ui8SensorID, uint8_t *pBuffer);

//*****************************************************************************
//
//! This API will build a packet to send generic unsigned integers,
//! conforming to the CapTIvate&tm; protocol.  Up to 29 entries may be sent.
//
//! \param pData is a pointer to the data to send.
//! \param ui8Cnt indicates the number of integers pointed to by pData.
//! \param pBuffer is a pointer to buffer to place the packet in.
//
//! \par Returns
//!		the length of the packet that was build if valid parameters were
//! 	found, else 0.
//
//*****************************************************************************
extern uint16_t CAPT_getGeneralPurposePacket(uint16_t *pData,
		uint8_t ui8Cnt, uint8_t *pBuffer);
	
//*****************************************************************************
//
//! This API will build a packet to send a C character string,
//! conforming to the CapTIvate&tm; protocol.  Strings up to 58 characters are
//! allowed in this protocol.
//
//! \param pSrcString is the string to transmit.
//! \param pBuffer is a pointer to buffer to place the packet in.
//
//! \par Returns
//!		the length of the packet that was build if valid parameters were
//! 	found, else 0.
//
//*****************************************************************************		
extern uint16_t CAPT_getStringPacket(const char *pSrcString, uint8_t *pBuffer);


//*****************************************************************************
//
//! This API will build a packet to send TrackPad sensor position and gesture information,
//! conforming to the CapTIvate&tm; protocol.  Information sent
//! includes X,Y position and Gesture
//
//! \param sensorArray is a pointer to the global array of sensor pointers.
//! \param ui8SensorID indicates the ID of the sensor to build a packet for
//! \param pBuffer is a pointer to buffer to place the packet in.
//
//! \par Returns
//!     the length of the packet that was build if a valid sensor was
//!     found, else 0.
//
extern uint16_t CAPT_getTrackPadPacket(tSensor* pSensor, uint8_t ui8SensorID, uint8_t *pBuffer);


//*****************************************************************************
//
//! This API will build a packet to send TrackPad sensor status information,
//! conforming to the CapTIvate&tm; protocol.
//! Information sent includes sensor status
//
//! \param sensorArray is a pointer to the global array of sensor pointers.
//! \param ui8SensorID indicates the ID of the sensor to build a packet for
//! \param pBuffer is a pointer to buffer to place the packet in.
//
//! \par Returns
//!     the length of the packet that was build if a valid sensor was
//!     found, else 0.
extern uint16_t CAPT_getTrackPadSensorStatusPacket(tSensor **sensorArray, uint8_t ui8SensorID, uint8_t *pBuffer);


//*****************************************************************************
//
//! This API calculate the checksum of a byte buffer of given length.
//
//! \param pBuffer is a pointer to buffer of bytes to calculate from.
//! \param ui16Length indicates the number of valid bytes in the buffer.
//
//! \par Returns
//!		the checksum of the buffer.
//
//*****************************************************************************
extern uint16_t CAPT_getChecksum(const uint8_t *pBuffer,
		const uint16_t ui16Length);

//*****************************************************************************
//
//! This API verifies the checksum of a byte buffer of given length.
//
//! \param pBuffer is a pointer to buffer of bytes to verify.
//! \param ui16Length indicates the number of valid bytes in the buffer.
//! \param ui16Checksum is the expected checksum to verify against.
//
//! \par Returns
//!		true of the checksum is valid, else false.
//
//*****************************************************************************
extern bool CAPT_verifyChecksum(const uint8_t *pBuffer, const uint16_t ui16Length,
		const uint16_t ui16Checksum);

//*****************************************************************************
//
//! This API parses a buffer and inserts stuffed bytes at each occurrence of the
//! sync byte in the buffer, except the first position.
//
//! \param pBuffer is a pointer to buffer of bytes to parse.
//! \param ui16Length indicates the number of valid bytes in the buffer.
//
//! \par Returns
//!		the new length of the buffer
//
//*****************************************************************************
extern uint16_t CAPT_stuffSyncBytes(uint8_t *pBuffer,
		uint16_t ui16Length);

//*****************************************************************************
//
//! Parse incoming bytes from the low level serial driver, and identify
//! valid CapTIvate&tm; packets to be processed.  Stuffed bytes are removed here.
//
//! \param pReceiveQueue is a pointer to the queue to pull incoming bytes from
//! \param pPacket is a pointer to the parameter packet to fill
//! \param pVariables is a pointer to the processing variable structure.
//
//! \par Returns
//!		true if a valid CapTIvate&tm; packet was found, else false.
//
//*****************************************************************************
extern bool CAPT_processReceivedData(tByteQueue *pReceiveQueue,
		tParameterPacket *pPacket, tTLProtocolProcessingVariables *pVariables);

//*****************************************************************************
//
//! Access a CapTIvate&tm; TL structure variable for a given capacitive touch
//! panel.
//
//! \param sensorArray is a pointer to the global array of sensor pointers.
//! \param pPacket is a pointer to the parameter packet containing the
//! parameter to access.
//
//! \par Returns
//!		a tTLParameterAccessResult enumeration indicating whether the
//! 	packet had a valid or invalid parameter, and whether a sensor
//! 	re-calibration is required.
//
//*****************************************************************************
extern tTLParameterAccessResult CAPT_accessSensorParameter(
		tSensor **sensorArray, tParameterPacket *pPacket);

//*****************************************************************************
//
//! Access a special CapTIvate&tm; TL structure variable for a given capacitive 
//! touch panel.
//
//! \param sensorArray is a pointer to the global array of sensor pointers.
//! \param pPacket is a pointer to the parameter packet containing the
//! parameter to access.
//
//! \par Returns
//!		a tTLParameterAccessResult enumeration indicating whether the
//! 	packet had a valid or invalid parameter, and whether a sensor
//! 	re-calibration is required.
//
//*****************************************************************************		
extern tTLParameterAccessResult CAPT_accessSpecialSensorParameter(
		tSensor **sensorArray, tParameterPacket *pPacket);


//
//! Access a special CapTIvate&tm; TL structure variable for a TrackPad sensor.
//
//! \param sensorArray is a pointer to the global array of sensor pointers.
//! \param pPacket is a pointer to the parameter packet containing the
//! parameter to access.
//
//! \par Returns
//!     a tTLParameterAccessResult enumeration indicating whether the
//!     packet had a valid or invalid parameter, and whether a sensor
//!     re-calibration is required.
//
extern tTLParameterAccessResult CAPT_accessTrackPadSensorParameter(
		tSensor **sensorArray, tParameterPacket *pPacket);

#endif /* CAPT_PROTOCOL_H_ */
//*****************************************************************************
//! Close the doxygen group
//! @}
//*****************************************************************************
