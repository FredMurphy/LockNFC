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
// CAPT_EMC.h
//
//! EMC plug-ins for enhanced noise immunity.
//
//! The EMC software module of the Captivate touch library provides a set of
//! utilities that aid in designing for electromagnetic compatibility (EMC).
//! These functions work together with the Captivate peripheral to provide
//! a high level of immunity to conducted/radiated RF disturbances, EFT, and
//! ESD transients.
//
//! \version 1.70.00.03
//! Released on July 30, 2018
//
//*****************************************************************************
//*****************************************************************************
//! \addtogroup CAPT_EMC
//! @{
//*****************************************************************************

#ifndef CAPT_EMC_H_
#define CAPT_EMC_H_

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

/*ROM_DEFINE_START*/

//*****************************************************************************
//
//! \def CAPT_EMC_STDFREQ_CNT defines the number of distinct conversion
//! frequencies to scan at for a standard conversion.
//
//*****************************************************************************
#define CAPT_EMC_STDFREQ_CNT                                             (0x01)

//*****************************************************************************
//
//! \def CAPT_EMC_MULTIFREQ_CNT defines the number of distinct conversion
//! frequencies to scan at when frequency hopping is enabled.
//
//*****************************************************************************
#define CAPT_EMC_MULTIFREQ_CNT                                           (0x04)

//*****************************************************************************
//
//! \def CAPT_EMC_SAMPLE_ERROR_CODE defines the value returned from a
//! conversion if the maximum count error was reached.
//
//*****************************************************************************
#define CAPT_EMC_SAMPLE_ERROR_CODE                                    (0x00000)

/*ROM_DEFINE_STOP*/

//*****************************************************************************
//
//! Use this function to load an EMC configuration.  This must be done prior
//! to using the EMC layer.  When a new EMC configuration is loaded, the
//! the internal global noise level and highest noise element variables are
//! both reset.  If a null pointer is passed, the function will not adjust
//! any variables and will exit leaving the existing configuration.
//
//! The EMC configuration is a tEMCConfig structure that defines how the 
//! EMC layer processes data.  The structure is defined in CAPT_Type.h.
//
//! \param pRawSet is a pointer to the source data memory
//
//! \par Returns
//!		true if a valid pointer was passed, else false.
//
//*****************************************************************************
extern bool CAPT_loadEMCConfig(const tEMCConfig *pConfig);


//*****************************************************************************
//
//! Use CAPT_getGlobalFilteredNoiseValue() to retrieve the global filtered
//! noise value.  This value stores an aggregate noise level for all
//! self-capacitance elements when bDynamicThresholdAdjustmentIsGlobal is true.
//
//! \param none
//
//! \par Returns
//!		the global filtered noise value, expressed as a % of the LTA of any
//!     given sensor, with 0=0% and 128=100%
//
//*****************************************************************************
extern uint16_t CAPT_getGlobalFilteredNoiseLevel(void);


//*****************************************************************************
//
//! Use CAPT_resetGlobalFilteredNoiseLevel() to seed the global filtered noise
//! value to zero, effectively resetting it.
//
//! \param none
//
//! \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_resetGlobalFilteredNoiseLevel(void);


//*****************************************************************************
//
//! Use CAPT_updateGlobalFilteredNoiseLevel() to update the global filtered
//! noise level based on a channel's noise level.
//!
//! If the new noise level is above the current global value, the "up" 
//! direction filter beta will be applied; otherwise, the "down" direction 
//! filter beta will be applied.
//!
//! Additionally, if the new noise level is "up" going and the new value is
//! below the noise level filter entry threshold, no filtering will be applied.
//! Likewise, if the new noise level is "down" going and the new value
//! is below the noise level filter exit threshold, the filter will not be
//! applied.  This is to speed response to quick, drastic changes in values.
//!
//! To maintain a valid global level when only one element is being interacted
//! with, whenever a new high point is established the address of that data
//! point (effectively the corresponding sensing element) will be stored.
//! Then, only that data point is allowed to decrease the global value
//! unless the global value is reset manually.
//
//! \param pElement is the address of the element
//! \param ui16RelNoiseLevel is the new relative noise level
//
//! \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_updateGlobalFilteredNoiseLevel(tElement *pElement,
		uint16_t ui16RelNoiseLevel);
		

//*****************************************************************************
//
//! Get the raw conversion style and oversampling style that are specified for
//! an EMC conversion in self or projected mode.
//
//! \param method is the sensing method to query
//! \param pConversion is a pointer to the location to store the raw
//! conversion style
//! \param pOversampling is a pointer to the location to store the
//! oversampling style.
//
//! \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_getEMCConversionSettings(tSenseTechnology method, 
        tRawConversionStyle *pConversion, tOversamplingStyle *pOversampling);


//*****************************************************************************
//
//! Get the relative noise threshold parameter
//
//! \param none
//
//! \par Returns
//!		the relative noise threshold
//
//*****************************************************************************
extern uint8_t CAPT_getRelNoiseStatusThreshold(void);


//*****************************************************************************
//
//! Get the maximum relative threshold parameter, as specified in the EMC 
//! configuration structure that is currently loaded.  This may be used
//! for bounds checks on adjusted thresholds by external functions.
//
//! \param none
//
//! \par Returns
//!		the maximum relative threshold allowed
//
//*****************************************************************************
extern uint8_t CAPT_getMaxRelThreshold(void);


//*****************************************************************************
//
//! This function will test a frequency for noise and return true if noise
//! is detected.  All elements in the sensor will be scanned at the requested
//! frequency to determine if noise is present.  The number of samples measured
//! as well as the noise threshold used to determine the presence of noise may
//! be adjusted in the EMC configuration structure via the 
//! ui8CalibrationTestSampleSize and ui16CalibrationNoiseLimit parameters,
//! respectively.
//
//! \param pSensor is a pointer to the sensor to test
//! \param ui8Freq is the frequency to test
//!
//! \par Returns
//!		true if noise was detected, else false
//
//*****************************************************************************
extern bool CAPT_testConversionFrequencyForNoise(tSensor *pSensor,
		uint8_t ui8Freq);
		

//*****************************************************************************
//
//! This function will correct invalid calibration parameters for a given
//! sensor based on the noise mask that is passed.  BIT0 through BIT3 in
//! the passed ui8NoiseMask indicate that noise is present on FREQ0 to FREQ3,
//! respectively.  If a frequency is marked as noisy, its calibration values
//! are automatically considered to be invalid and are replaced with the next
//! closest valid values.  If no valid values are available to correct a 
//! frequency, the invalid values are left alone and the function returns true
//! to indicate that no corrections were made.  This would happen if noise was
//! present on all frequencies.
//!
//! \param pSensor is a pointer to the sensor to correct
//! \param ui8NoiseMask is a bit mask of frequencies that have noise.
//!
//! \par Returns
//!		true if the calibration values were not modified because all had noise,
//!     else false.
//
//*****************************************************************************
extern bool CAPT_correctInvalidMultiFreqCalibration(tSensor *pSensor,
		uint8_t ui8NoiseMask);


//*****************************************************************************
//
//! This function inspects the new set of sample results at different
//! conversion frequencies and if an error code is found (max count error),
//! that frequency is replaced with the passed replacement value.
//! Only one frequency will be corrected.
//
//! \param pNewSet is a pointer to the new raw data set.  Four words are
//! expected at this location.
//! \param ui16Replacement is the value to replace any error codes with.
//! \par Returns
//!		none
//
//*****************************************************************************		
extern void CAPT_replaceFrequencyWithError(uint16_t *pNewSet, 
		uint16_t ui16Replacement);
		
		
//*****************************************************************************
//
//! This function resolves a set of conversions done in series at different
//! conversion frequencies into a single conversion result.
//
//! \param pNewSet is a pointer to the new raw data set.  Four words are
//! expected at this location.
//! \param pResult is a pointer indicating the memory location to store the
//! output of the algorithm
//! \param pNoiseLevel is a pointer indicating the memory location to store the
//! level of noise in the raw set.  The noise level is calculated as max-min.
//! \param bRemoveOutlier tells the function to remove the outlier
//! from the sample set.
//! \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_resolveMultiFreqSet(const uint16_t *pNewSet,
		uint16_t *pResult, uint16_t *pNoiseLevel, bool bRemoveOutlier);


//*****************************************************************************
//
//! This function applies a basic single-level jitter filter to a sample.
//
//! \param ui16Prev is the current natural count value.
//! \param ui16Curr is the new raw count value to filter in.
//! \par Returns
//!		The new, filtered value.
//
//*****************************************************************************
extern uint16_t CAPT_computeJitterFilter(uint16_t ui16Prev,
		uint16_t ui16Curr);


//*****************************************************************************
//
//! CAPT_computePos2ndDegPoly()
//! This function computes the output Y for the input X to a 2nd-order
//! polynomial function, described as Y = A*(X^2) + B*X.  The coefficients
//! A and B are IQ31 format and are effectively limited to -1 <= x < 1.
//! The function input value X may be full scale (0 <= x <= 65535).
//
//! \param ui16X is the X input to the polynomial calculator.  This number
//! must be in unsigned integer with no fractional component (Q0).
//! \param iq31A is the A coefficient (the coefficient of ui16X^2).  This
//! parameter MUST be in 32-bit IQ31 format, which limits the range of values
//! to this bound: MIN=-1; MAX=0.999999999; RES=0.0000000005
//! \param iq31B is the B coefficient (the coefficient of ui16X).  This
//! parameter MUST be in 32-bit IQ31 format, which limits the range of values
//! to this bound: MIN=-1; MAX=0.999999999; RES=0.0000000005
//
//! \par Returns
//!		y, the accumulation of AX^2 and BX.
//
//*****************************************************************************
static inline uint16_t CAPT_computePos2ndDegPoly(uint16_t ui16X, IQ31_t iq31A,
		IQ31_t iq31B);


//*****************************************************************************
//
//! This function computes the amount of threshold compensation to apply
//! to an element.  The noise level passed will be used as the input
//! to determine the amount of threshold compensation to apply.  If the global
//! noise setting (bDynamicThresholdAdjustmentIsGlobal) is true, and the
//! global noise value is higher than the passed noise level, the global
//! noise reference will be used to compute the threshold compensation.
//
//! \param ui8NoiseLevel specifies the relative noise level to adjust for,
//! based on a 1/128 scale.
//
//! \par Returns
//!		The amount to adjust the threshold by.
//
//*****************************************************************************
extern uint8_t CAPT_computeRelNoiseComp(void);


#endif /* CAPT_EMC_H_ */

//*****************************************************************************
//
//! Close the doxygen group
//! @}
//
//*****************************************************************************
