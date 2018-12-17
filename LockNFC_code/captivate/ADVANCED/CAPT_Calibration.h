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
// CAPT_Calibration.h
//
//! This module contains sensor calibration routines.
//
//! \version 1.70.00.03
//! Released on July 30, 2018
//
//*****************************************************************************
//*****************************************************************************
//! \addtogroup CAPT_CALIBRATION
//! @{
//*****************************************************************************
#ifndef __CAPT_CALIBRATION__
#define __CAPT_CALIBRATION__

#include "CAPT_HAL.h"

//*****************************************************************************
//
// CAPT_CAL_ALG may be defined as one of the following options:
//
//! def __CAPT_STD_CALIBRATION__ selects the conversion gain/count calibration.
//! def __CAPT_MAXOFFSET_CALIBRATION__ selects the max offset calibration.
//
//*****************************************************************************
#define __CAPT_STD_CALIBRATION__                                            (0)
#define __CAPT_MAXOFFSET_CALIBRATION__                                      (1)


//*****************************************************************************
//
//! The calibrate sensor function calibrates all elements in the sensor based
//! on the sensor's input conversion gain and conversion count parameters.
//!
//! This routine calibrates at one frequency only, and is intented to be used
//! in applications where noise immunity (EMC) features are disabled.
//!
//! After this function has completed running, the following outputs are set:
//!   - The coarse gain, fine gain, and offset tap for each element are saved
//!     in the element structure's pTuning array for frequency 0 only.
//!   - The bCalibrationError parameter in the sensor structure is set if
//!     a valid calibration could not be obtained.  If this bit is set, it
//!     means that the external capacitor being measured could not be scaled
//!     to meet the desired conversion gain and conversion count inputs that
//!     were requested.
//!
//! \param pSensor is a pointer to the sensor to adjust
//!
//! \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_calibrateSensor(tSensor *pSensor);


//*****************************************************************************
//
//! The calibrate sensor with max offset function calibrates all elements in
//! the sensor based on the sensor's input conversion count parameter only.
//! This calibration routine achieves the maximim sensitivity for a given
//! conversion count by applying as much offset subtraction as possible.
//!
//! This routine calibrates at one frequency only, and is intented to be used
//! in applications where noise immunity (EMC) features are disabled.
//!
//! After this function has completed running, the following outputs are set:
//!   - The coarse gain, fine gain, and offset tap for each element are saved
//!     in the element structure's pTuning array for frequency 0 only.
//!   - The bCalibrationError parameter in the sensor structure is set if
//!     a valid calibration could not be obtained.  If this bit is set, it
//!     means that the external capacitor being measured could not be scaled
//!     to meet the desired conversion count inputs that were requested.
//!
//! \param pSensor is a pointer to the sensor to adjust
//!
//! \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_calibrateSensorWithMaxOffset(tSensor *pSensor);


//*****************************************************************************
//
//! The calibrate sensor function runs all of the necessary calibration
//! routines to achieve the desired sensitivity for a sensor with EMC
//! (noise immunity) enabled.  This involves calibrating gain and offset
//! at 4 conversion frequencies based on the sensor's input conversion gain 
//! and conversion count parameters, and ensuring that all calibration values 
//! are valid.
//!
//! After this function has completed running, the following outputs are set:
//!   - The coarse gain, fine gain, and offset tap for each element are saved
//!     in the element structure's pTuning array for frequency 0-3 (4 total)
//!   - The bCalibrationError parameter in the sensor structure is set if
//!     a valid calibration could not be obtained.  If this bit is set, it
//!     means that the external capacitor being measured could not be scaled
//!     to meet the desired conversion gain and conversion count inputs that
//!     were requested.  This bit is also set if noise was detected on all 4
//!     conversion frequencies, in which case calibration is not possible.
//!   - The bSensorNoiseState parameter in the sensor structure is set if
//!     noise was present for at one or more conversion frequencies.
//!
//! \param pSensor is a pointer to the sensor to adjust
//!
//! \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_calibrateSensorWithEMC(tSensor *pSensor);


//*****************************************************************************
//
//! The calibrate sensor function runs all of the necessary calibration
//! routines to achieve the desired sensitivity for a sensor with EMC
//! (noise immunity) enabled.  This function calibrates all elements in
//! the sensor based on the sensor's input conversion count parameter only.
//! This calibration routine achieves the maximim sensitivity for a given
//! conversion count by applying as much offset subtraction as possible.
//! This involves calibrating gain and offset at 4 conversion frequencies, 
//! and ensuring that all calibration values are valid.
//!
//! After this function has completed running, the following outputs are set:
//!   - The coarse gain, fine gain, and offset tap for each element are saved
//!     in the element structure's pTuning array for frequency 0-3 (4 total)
//!   - The bCalibrationError parameter in the sensor structure is set if
//!     a valid calibration could not be obtained.  If this bit is set, it
//!     means that the external capacitor being measured could not be scaled
//!     to meet the desired conversion count inputs that were requested.
//!     This bit is also set if noise was detected on all 4
//!     conversion frequencies, in which case calibration is not possible.
//!   - The bSensorNoiseState parameter in the sensor structure is set if
//!     noise was present for at one or more conversion frequencies.
//!
//! \param pSensor is a pointer to the sensor to adjust
//!
//! \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_calibrateSensorWithMaxOffsetWithEMC(tSensor *pSensor);


//*****************************************************************************
//
//! The calibrate gain parameter function identifies the correct gain ratio
//! to achieve the specified conversion gain.
//
//! Note that this calibration will clear out any offset applied by a call to
//! CAPT_calibrateOffset().  Call this calibration function first.
//
//!
//! \param pSensor is a pointer to the sensor to calibrate
//
//! \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_calibrateGain(tSensor *pSensor, 
	volatile bool *pbEndOfConversionFlag, uint8_t ui8Frequency);


//*****************************************************************************
//
//! The calibrate offset parameter function identifies the correct offset tap
//! to achieve the specified conversion count.
//!
//! \param pSensor is a pointer to the sensor to calibrate
//
//! \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_calibrateOffset(tSensor *pSensor, 
	volatile bool *pbEndOfConversionFlag, uint8_t ui8Frequency);


//*****************************************************************************
//
//! The CAPT_calibrateForMaxOffset function identifies the correct offset tap
//! and gain ratios for each element in a sensor when calibrating at the
//! specified frequency.  The target result is a conversion result as close as
//! possible to the sensor's conversion count parameter, with the max amount
//! of offset subtraction applied.  The conversion gain parameter is not used
//! with this calibration option.
//!
//! \param pSensor is a pointer to the sensor to calibrate
//
//! \par Returns
//!		none
//
//*****************************************************************************	
void CAPT_calibrateForMaxOffset(tSensor *pSensor, 
    uint16_t ui16MaxOffsetStartPoint, volatile bool *pbEndOfConversionFlag, 
	uint8_t ui8Freq);


#endif
//*****************************************************************************
//! Close the doxygen group
//! @}
//*****************************************************************************
