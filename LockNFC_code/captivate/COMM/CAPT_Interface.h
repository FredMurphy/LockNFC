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
// CAPT_Interface.h
//
//! This is the high-level communications interface module.
//
//! These functions provide the interfaces between the application level,
//! protocol layer, and the low-level serial interface.
//
//! \version 1.70.00.03
//! Released on July 30, 2018
//
//*****************************************************************************
//*****************************************************************************
//! \addtogroup CAPT_Interface
//! @{
//*****************************************************************************

#ifndef CAPT_INTERFACE_H_
#define CAPT_INTERFACE_H_

//*****************************************************************************
// Include string library for memcpy
//
#ifndef S_SPLINT_S
#include <string.h>
#endif
//*****************************************************************************

#include "CAPT_CommConfig.h"
#include "CAPT_UserConfig.h"

//*****************************************************************************
//
//! Initialize TL communications as a whole. This API will start the low-level
//! serial driver.
//!
//! \param pApp is a pointer to the application to link to
//! \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_initCommInterface(tCaptivateApplication *pApp);

//*****************************************************************************
//
//! Transmit all element data for a given sensor.
//!
//! \param ui8SensorID indicates which sensor's data to transmit.
//
//! \par Returns
//!		true if data transmitting, else false.
//
//*****************************************************************************
extern bool CAPT_writeElementData(uint8_t ui8SensorID);

//*****************************************************************************
//
//! Transmit all sensor-specific data for a given sensor.
//!
//! \param ui8SensorID indicates which sensor's data to transmit.
//
//! \par Returns
//!		true if data transmitting, else false.
//
//*****************************************************************************
extern bool CAPT_writeSensorData(uint8_t ui8SensorID);

//*****************************************************************************
//
//! Transmit generic, unsigned integer formatted data for logging or plotting.
//!
//! \param pData is a pointer to the data to send.
//! \param ui8Cnt is the number of entries pointed to by pData; the max is 29.
//
//! \par Returns
//!		true if data transmitting, else false.
//
//*****************************************************************************
extern bool CAPT_writeGeneralPurposeData(uint16_t *pData, uint8_t ui8Cnt);

//*****************************************************************************
//
//! Transmit a C string.
//!
//! \param pSrcString is a pointer to the first character of the string to
//!        send.  The string must be null terminated.
//
//! \par Returns
//!		true if data transmitting, else false.
//
//*****************************************************************************
extern bool CAPT_writeString(const char *pSrcString);

//*****************************************************************************
//
//! Transmit TrackPad specific X,Y position and Gesture data.
//!
//! \param ui8SensorID indicates which sensor's data to transmit.
//
//! \par Returns
//!     true if data transmitting, else false.
//
//*****************************************************************************
extern bool CAPT_writeTrackPadSensorData(uint8_t ui8SensorID);


//*****************************************************************************
//
//! Transmit TrackPad sensor status.
//!
//! \param ui8SensorID indicates which sensor's data to transmit.
//
//! \par Returns
//!     true if data transmitting, else false.
//
//*****************************************************************************
extern bool CAPT_writeTrackPadSensorStatus(uint8_t ui8SensorID);

//*****************************************************************************
//
//! Call into the protocol layer to determine if any parameter packets have
//! been received.  THis API should be called periodically in the background
//! by the application layer.
//!
//!  \par Parameters
//!		none
//
//! \par Returns
//!		true if packet received, else false.
//
//*****************************************************************************
extern bool CAPT_checkForInboundPacket(void);

//*****************************************************************************
//
//! Check if a sensor re-calibration was requested by the host.
//!
//!  \par Parameters
//!		none
//
//! \par Returns
//!		true if re-cal required, else false
//
//*****************************************************************************
extern bool CAPT_checkForRecalibrationRequest(void);

#endif /* CAPT_INTERFACE_H_ */
//*****************************************************************************
//! Close the doxygen group
//! @}
//*****************************************************************************
