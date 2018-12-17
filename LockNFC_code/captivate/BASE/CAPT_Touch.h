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
// CAPT_Touch.h
//
//! Low-level sensor update module.
//
//! This module APIs for sensor initialization, measurement, filtering, 
//! auto calibration, threshold detection, and debounce for proximity and touch.
//! A fast IIR filter API and a performance IIR filter API
//! are made available to higher level processing functions as well.
//
//! \version 1.70.00.03
//! Released on July 30, 2018
//
//*****************************************************************************
//*****************************************************************************
//! \addtogroup CAPT_TOUCH
//! @{
//*****************************************************************************
#ifndef __CAPT_TOUCH__
#define __CAPT_TOUCH__

#include "CAPT_HAL.h"

//*****************************************************************************
//
//! Use CAPT_blockOnFlag to safely stall the running program in the
//! specified LPM mode until a boolean flag is set to true and the CPU
//! is awakened.
//
//! \param pFlag is a pointer to the boolean flag to pend on
//! \param ui8LPM indicates the low power mode to use while waiting
//
//! \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_blockOnFlag(volatile bool *pFlag, uint8_t ui8LPM);


//*****************************************************************************
//
//! Use CAPT_loadCycle before CAPT_startConversion() or
//! CAPT_startConversionAndWaitUntilDone() to load a cycle for measurement.
//! This function sets up the IO for the cycle, applies the gain and offset,
//! for each element in the cycle, and configures the FSM if requested.
//
//! \param pSensor is a pointer to the parent sensor
//! \param ui8Cycle is the cycle to load in the sensor
//! \param ui8Freq is the oscillator frequency index to load values from
//! \param bFSM specifies whether to load and enable the FSM.
//
//! \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_loadCycle(tSensor *pSensor, uint8_t ui8Cycle,
		uint8_t ui8Freq, bool bFSM);


//*****************************************************************************
//
//! Use CAPT_unloadCycle after CAPT_startConversion() or
//! CAPT_startConversionAndWaitUntilDone() to unload a cycle after measurement.
//! This function clears up the IO for the cycle, saves the raw results, and
//! saves the filtered count / LTA if the FSM parameter is true.
//
//! \param pSensor is a pointer to the parent sensor
//! \param ui8Cycle is the cycle to load in the sensor
//! \param ui8Index is the raw count index to save the results to
//! \param bFSM specifies whether to save filtered count and LTA data from
//! the FSM.
//
//! \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_unloadCycle(tSensor *pSensor, uint8_t ui8Cycle,
		uint8_t ui8Index, bool bFSM);


//*****************************************************************************
//
//! Use CAPT_startConversion to immediately kickoff a conversion
//! that has been set up.  This function returns immediately and does not
//! wait for the conversion to complete.
//
//! \param none
//
//! \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_startConversion(volatile bool *pbEndOfConversionFlag);


//*****************************************************************************
//
//! Use CAPT_cleanupAfterConversion to cleanup the peripheral after
//! CAPT_startConversion has been called and the conversion has completed.
//
//! \param none
//
//! \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_cleanupAfterConversion(void);


//*****************************************************************************
//
//! Use CAPT_startConversionAndWaitUntilDone to kickoff a conversion that has
//! been setup and wait in the specified low power mode until the conversion
//! has completed, at which time the peripheral will be cleaned up.
//
//! \param ui8LPM is the low power mode to enter during the conversion
//
//! \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_startConversionAndWaitUntilDone(
	volatile bool *pbEndOfConversionFlag, uint8_t ui8LPM);


//*****************************************************************************
//
//! Initialize Sensor
//!
//! Clear all status flags in the sensor and elements.
//!
//! \param pSensor is a pointer to a generic sensor type
//!
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_initSensor(tSensor *pSensor);


//*****************************************************************************
//
//! Refresh all data for the specified sensor
//!
//! This function samples the sensor and processes the data, upating
//! all of the sensor and element values with the current data.  Upon
//! completion of the update, the sensor callback function will be called, if
//! it exists.
//!
//! \param pSensor is a pointer to the sensor to update
//! \param ui8LPM is the low power mode to enter during conversions
//!
//! \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_updateSensor(tSensor *pSensor,  uint8_t ui8LPM);


//*****************************************************************************
//
//! Update raw count values for a sensor.
//!
//! This function samples the sensor, but only updates the raw count values
//! for each element- no processing is performed on the data, and the sensor
//! callback function is NOT called upon completion of the update.
//!
//! \param pSensor is a pointer to the sensor to update
//! \param conversion specifies the conversion style to use. Valid options include:
//!   - eStandard
//!   - eMultiFrequency
//!   - eMultiFrequencyWithOutlierRemoval
//! \param oversampling specifies the oversampling to use. Valid options include:
//!   - eNoOversampling (default)
//!   - e2xOversampling
//!   - e4xOversampling
//!   - e8xOversampling
//!   - e16xOversampling
//!   - e32xOversampling
//! \param ui8LPM is the low power mode to enter during conversions.
//!
//! \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_updateSensorRawCount(tSensor* pSensor,
		tRawConversionStyle conversion, tOversamplingStyle oversampling,
		uint8_t ui8LPM);


//*****************************************************************************
//
//! Use CAPT_startWakeOnProxMode to configure the peripheral for
//! wake-on-proximity mode.  The cycle/sensor selected will be measured
//! autonomously with no CPU unteraction.  The following flags will
//! indicate to the application that action needs to be taken:
//!   - g_bDetectionFlag (A proximity threshold was crossed for an element)
//!   - g_bConvCounterFlag (The conversion counter timed out)
//!   - g_bMaxCountErrorFlag (A max count error occured and should be handled)
//! Once an event occurs, the application should call CAPT_stopWakeOnProxMode()
//! to disable wake on touch mode, then handle the event accordingly.
//!
//
//! \param pSensor is a pointer to the sensor to use
//! \param ui8Cycle indicates the cycle of the sensor to load and use for
//! for wakeup
//! \param ui16WakeupInterval specifies the wakeup interval to use.  Valid
//! options include:
//!   - CAPT_COUNTER__16
//!   - CAPT_COUNTER__32
//!   - CAPT_COUNTER__64
//!   - CAPT_COUNTER__128
//!   - CAPT_COUNTER__256
//!   - CAPT_COUNTER__512
//!   - CAPT_COUNTER__1024
//!   - CAPT_COUNTER__2048
//!   - CAPT_COUNTER__DISABLED
//
//! \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_startWakeOnProxMode(tSensor* pSensor, uint8_t ui8Cycle,
		uint16_t ui16WakeupInterval);

		
//*****************************************************************************
//
//! Call CAPT_stopWakeOnProxMode() after calling CAPT_startWakeOnProxMode()
//! to disable wake-on-proximity mode.
//! This function saves the count/LTA data for the loaded cycle, 
//! then unloads the cycle from the peripheral.
//
//! \param pSensor is a pointer to the sensor that is being measured.
//! \param ui8Cycle indicates the cycle of the sensor being measured.
//
//! \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_stopWakeOnProxMode(tSensor* pSensor, uint8_t ui8Cycle);


//*****************************************************************************
//
//! Perform processing for a cycle
//!
//! Here standard processing is performed on the elements of the cycle.
//! This includes the basics of capacitive sensing such as the long-term
//! average, output status bits (prox/touch) and basic filtering.
//!
//! \param pSensor is a pointer to the sensor of the cycle to process
//!
//! \param pCycle is a pointer to the cycle to process
//!
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_processFSMCycle(tSensor *pSensor, tCycle *pCycle);


//*****************************************************************************
//
//! Perform generic sensor processing
//!
//! Here different status bits are updated to summarise the status of the sensor
//!
//! \param pSensor is a pointer to the Sensor Implementation to update
//!
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_processSensor(tSensor *pSensor);


//*****************************************************************************
//
//! Sensor Recalibration Management Function - LTA Drift Check
//!
//! The LTA of each element of the sensor is monitored here, and if any of them
//! drift out of range of the intended calibration values, the function
//! returns true, flagging the application layer that the sensor should be
//! re-calibrated as it has drifted out of range.
//! Currently the drift is fixed at 1/8th of the conversion count.
//!
//! \param pSensor is a pointer to the sensor to test.
//!
//! \par Returns
//!		true if a re-calibration is required, else false.
//
//*****************************************************************************
extern bool CAPT_testForRecalibration(tSensor *pSensor);

//*****************************************************************************
//
//! Sensor Recalibration Management Function - Max Count Bounds Check
//!
//! The max count parameter of the sensor is tested here, and if it is set
//! and the runtime re-calibration parameter is set, this function returns
//! true and clears the max count error for the sensor.
//!
//! \param pSensor is a pointer to the sensor to test.
//!
//! \par Returns
//!		true if a re-calibration is required, else false.
//
//*****************************************************************************
extern bool CAPT_testForMaxCountRecalibration(tSensor *pSensor);

//*****************************************************************************
//
//! Sensor Recalibration Management Function - Negative Touch Check
//!
//! The negative touch parameter of the sensor is tested here, and if it is set
//! and the runtime re-calibration parameter is set, this function returns
//! true.
//!
//! \param pSensor is a pointer to the sensor to test.
//!
//! \par Returns
//!		true if a re-calibration is required, else false.
//
//*****************************************************************************
extern bool CAPT_testForNegativeTouchRecalibration(tSensor *pSensor);

//*****************************************************************************
//
//! Flag All Elements for Reseed
//!
//! Use CAPT_flagAllElementsForReseed() to set the reseed bit for all
//! elements within a sensor.
//!
//! \param pSensor is a pointer to the sensor to process
//!
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_flagAllElementsForReseed(tSensor* pSensor);


//*****************************************************************************
//
//! Sensor Timeout algorithm
//!
//! Update the sensor timeout counter, then test if the timeout threshold has
//! been reached.  In that case reseed all the sensor LTAs and clear status bits
//!
//! \param pSensor is a pointer to the Sensor Implementation to update
//!
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_updateSensorTimeout(tSensor *pSensor);


//*****************************************************************************
//
//! Sensor Noise Algorithm
//!
//! Update the noise status flag of the sensor based on the status
//! of it's elements.
//!
//! \param pSensor is a pointer to the sensor to update.
//!
//! \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_updateSensorNoise(tSensor *pSensor);


//*****************************************************************************
//
//! This function converts a absolute parameter to a relative parameter. This
//! can be thought of as a percentage operation, but a value of 128 is
//! equivalent to 100%.  The maximum supported output is 255, or just under
//! 200%.
//
//! \param ui16Ref is the reference value.
//! \param ui16Abs is the value to convert with respect to the reference.
//
//! \par Returns
//!		the relative value.
//
//*****************************************************************************
extern uint8_t CAPT_convertAbsToRel(uint16_t ui16Ref, uint16_t ui16Abs);


//*****************************************************************************
//
//! This function converts a relative parameter to an absolute parameter. This
//! can be thought of as reverse a percentage operation, but a value of 128 is
//! equivalent to 100%.  The relative value passed must be between 0 and 128.
//
//! \param ui16Ref is the reference value.
//! \param ui8Rel is the value to convert. with respect to the reference.
//
//! \par Returns
//!		the absolute value.
//
//*****************************************************************************
extern uint16_t CAPT_convertRelToAbs(uint16_t ui16Ref, uint8_t ui8Rel);


//*****************************************************************************
//
//! Get a bit field of the requested state of all elements in the sensor.
//
//! This function may be called by the application to obtain a bit field
//! containing the requested state of each element within the sensor.  The bit
//! field supports up to 64 elements.  Elements are mapped to bit positions
//! starting with the first element of the first cycle to the last element
//! of the last cycle.  For example,  a sensor with two cycles and two
//! elements in each cycle would have the following mapping:
//!	    Return value bit 0 (0x01): Cycle 0 Element 0
//!	    Return value bit 1 (0x02): Cycle 0 Element 1
//!	    Return value bit 2 (0x04): Cycle 1 Element 0
//!	    Return value bit 3 (0x08): Cycle 1 Element 1
//
//! \param pSensor is a pointer to the sensor from which to generate the mask
//! \param status is the element status flag of which to create a field.
//!        Valid options are:
//!          - eTouchStatus
//!          - eProxStatus
//!          - eNegativeTouchStatus
//!          - eDetectStatus
//!          - eBISTStatus
//!          - eNoiseStatus       
//! \par Returns
//!	    A 64-bit field of touch statuses, where '0' is no touch 
//!     and '1' is touch
//
//*****************************************************************************
extern uint64_t CAPT_getElementStateBitField(tSensor *pSensor, 
        tElementStatusType status);
		
		
//*****************************************************************************
//
//! Register a user's callback function with each sensor
//!
//! This provides a method for the user to be notified of a sensor "event"
//! such as touch, prox, etc.
//!
//! The default callback is TL_GenericCallback() if user fails to register
//! their own.
//!
//! \param pSensor = pointer to the Sensor
//!
//! \param user_callback = pointer to user's callback function
//!
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_registerCallback(tSensor *pSensor,
		void (* user_callback)(tSensor *pSensor));


//*****************************************************************************
//
//! The default callback for sensor processing is CAPT_processTrackPadSensor()
//! User can override by registering their own callback
//! their own.
//!
//! \param pSensor = pointer to the Trackpad sensor processing
//!
//! \param user_callback = pointer to user's callback function
//!
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_registerTrackPadSensorProcessing(tSensor *pSensor, void (* user_function)(tSensor*));


//*****************************************************************************
//
//! The default callback for gesture processing is CAPT_processTrackPadGesture()
//! User can override by registering their own callback
//!
//! \param pFunction = pointer to the Gesture processing function
//!
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_registerTrackPadGestureProcessing(tSensor *pSensor, void (* user_function)(tSensor*));


//*****************************************************************************
//
//! Clear all Prox, Touch and NegativeTouch status bits relating to a specific
//! sensor. Here different status bits are cleared in the sensor, and in
//! its elements.
//!
//! \param pSensor is a pointer to the Sensor Implementation to update
//!
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_clearSensorProxTouch(tSensor *pSensor);


//*****************************************************************************
//
//! IIR Filter function
//!
//! A common filter used for capacitive sensing.  This filter implements a beta
//! that is a value/255 and processing more than the IIRFilterFast() function.
//! This is usually implemented on properties such as slider/wheel outputs.
//!
//! \param pRaw is a pointer to the new value to enter the filter
//!
//! \param pFiltered is a pointer to the stored filter value
//!
//! \param ui8Beta is a fraction of 255 that determines the IIR filter Beta
//!
//!  \par Returns
//!		none
//
//*****************************************************************************
extern IQ16_t CAPT_computeIIRFilter(IQ16_t *pRaw, IQ16_t *pFiltered,
		uint8_t ui8Beta);


//*****************************************************************************
//
//! IIR Filter (fast) function
//!
//! A common filter used for capacitive sensing.  This filter is faster to
//! process (since the beta is a bitwise shift, and is usually implemented on
//! properties that are large in quantity, such as LTA's and Count values.
//!
//! \param pRaw is a pointer to the new value to enter the filter
//!
//! \param pFiltered is a pointer to the stored filter value
//!
//! \param ui8Beta is a shifter value which determines the IIR filter Beta
//!
//!  \par Returns
//!		none
//
//*****************************************************************************
extern IQ16_t CAPT_computeIIRFilterFast(IQ16_t *pRaw, IQ16_t *pFiltered,
		uint8_t ui8Beta);


//*****************************************************************************
//
//! Reseed a filtered data array for a sensor
//!
//! Perform a reseed on all of the filtered values for a specific sensor.
//! This could be any filtered data such as Counts or Long-term averages.
//!
//! \param pSensor is a pointer to the sensor to reseed
//!
//! \param WhatToFilter indicates which value is filtered
//!
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_reseedFilterAll(tSensor *pSensor, tFilterOption WhatToFilter);


//*****************************************************************************
//
//! Reseed a filtered data value for a single data array entry
//!
//! Perform a reseed on one of the filtered values. This could be any filtered
//! data such as Counts or Long-term averages.
//!
//! \param pFilter is a pointer to the data that must be reseeded
//!
//! \param ui16ReseedValue is the reseed value
//!
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_reseedFilter(IQ16_t *pFilter, uint16_t ui16ReseedValue);


//*****************************************************************************
//
//! Update Prox Status
//!
//! Depending on the senseMethod implemented, calculate the delta as a positive
//! value when changing in the standard direction for the specific method.
//! Counts increase for projected, and decrease for self capacitive.  Then check
//! if this exceeds the selected threshold value.
//!
//! \param pSensor is the sensor pointer
//!
//! \param pElement is a pointer to the element to process
//!
//! \par Returns
//!		Boolean to indicate if a debounce is busy or if a prox is active
//
//*****************************************************************************
extern bool CAPT_updateProx(tSensor *pSensor, tElement *pElement);


//*****************************************************************************
//
//! Update Touch Status
//!
//! Using the touch threshold, an actual threshold point is calculated for the
//! specific element, and the count value is compared to that threshold.
//! Clearly Projected must be above this threshold, and self capacitive below
//!
//! \param pSensor is the sensor pointer
//!
//! \param pElement is a pointer to the element to process touch on
//!
//! \par Returns
//!		Boolean to indicate if a debounce is busy or if a touch is active
//
//*****************************************************************************
extern bool CAPT_updateTouch(tSensor *pSensor, tElement *pElement);


//*****************************************************************************
//
//! Update LTA filter for specific element based upon four freq measurements
//!
//! Update the LTA using the latest obtained Count value for the new cycle of
//! sensed data.
//!
//! \param pSensor is the sensor pointer
//!
//! \param pElement is a pointer to the element which LTA must be updated
//!
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_updateLTA(tSensor *pSensor, tElement *pElement);


//*****************************************************************************
//
//! Update the count value used for processing
//!
//! The raw count value is obtained from the HAL element structures, and if
//! required, is processed (such as filtering) and populated in the capacitive
//! touch library array 'Count[]'.
//!
//! \param pSensor is the sensor pointer (for sensor configuration)
//!
//! \param pElement is the cycle pointer
//!
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_updateFilterCount(tSensor *pSensor, tElement *pElement);


//*****************************************************************************
//!
//!  Update the filter count value based upon the 4 frequency
//!  measurements.
//! 
//!  \param  pCycle = pointer to cycle
//!
//!  \param  ui8Beta =
//!
//! \par Returns
//!		Compare Register Value
//!
//*****************************************************************************
extern void CAPT_updateFilterCounts(tCycle *pCycle, uint8_t ui8Beta);


//*****************************************************************************
//
//! Update Prox Status
//!
//! Update the prox and debounce status.
//!
//! \param pSensor = pointer to sensor
//!
//! \param pElement = pointer to the element to process
//!
//! \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_updateFSMProx(tSensor *pSensor, tElement *pElement);


//*****************************************************************************
//
//! Update Touch Status
//!
//! Using the touch threshold, an actual threshold point is calculated for the
//! specific element, and the count value is compared to that threshold.
//! Clearly Projected must be above this threshold, and self capacitive below
//!
//! \param pSensor is the sensor pointer
//!
//! \param pElement is a pointer to the element to process touch on
//!
//! \par Returns
//!		Boolean to indicate if a debounce is busy or if a touch is active
//
//*****************************************************************************
extern void CAPT_updateFSMTouch(tSensor *pSensor, tElement *pElement);


//*****************************************************************************
//
//! Sensor Global Prox and Touch status update
//!
//! The global sensor proximity and touch status is updated here.  The touch or
//! prox status is set if any of the elements in the sensor have prox or touch
//! states active.
//!
//! \param pSensor is a pointer to the Sensor Implementation to update
//!
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_updateSensorProxTouch(tSensor *pSensor);

		
//*****************************************************************************
//
//
//
// THE FOLLOWING FUNCTIONS ARE SPECIFIC TO SENSORS WITH NOISE IMMUNUITY
// (EMC) ENABLED.
//
//
//
//*****************************************************************************


//*****************************************************************************
//
//! Update all aspects of a sensor with additional EMC processing applied.
//!
//! \param pSensor is a pointer to the sensor to update
//! \param ui8LPM is the low power mode to use during conversions
//!
//! \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_updateSensorWithEMC(tSensor *pSensor, uint8_t ui8LPM);


//*****************************************************************************
//
//! Perform processing for a cycle with additional EMC processing applied.
//!
//! Here standard processing is performed on the elements of the cycle.
//! This includes the basics of capacitive sensing such as the long-term
//! average, output status bits (prox/touch) and basic filtering.
//!
//! \param pSensor is a pointer to the sensor of the cycle to process
//! \param pCycle is a pointer to the cycle to process
//!
//! \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_processCycleWithEMC(tSensor *pSensor, const tCycle *pCycle);


//*****************************************************************************
//
//! Use CAPT_updateElementFilteredValuesWithEMC() to update filtered
//! values in the element based on the raw sampled data.  Updated values
//! include the filtered count and the filtered noise value.
//!
//! \param pSensor is the parent sensor to pElement.
//! \param pElement is the element to process.
//!
//! \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_updateElementFilteredValuesWithEMC(tSensor *pSensor,
		tElement *pElement);


//*****************************************************************************
//
//! Use CAPT_updateSelfElementProxTouchWithEMC() to update the prox/touch
//! status of an element after the filtered count, LTA and noise values
//! have all been updated.  This function is for self-capacitance sensors.
//!
//! \param pSensor is the parent sensor to pElement.
//! \param pElement is the element to process.
//!
//! \par Returns
//!		the true if a prox or touch detection is pending/active.
//
//*****************************************************************************
extern bool CAPT_updateSelfElementProxTouchWithEMC(tSensor *pSensor,
		tElement *pElement);

		
//*****************************************************************************
//
//! Use CAPT_updateProjElementProxTouchWithEMC() to update the prox/touch
//! status of an element after the filtered count, LTA and noise values
//! have all been updated.  This function is for projected-capacitance sensors.
//!
//! \param pSensor is the parent sensor to pElement.
//! \param pElement is the element to process.
//!
//! \par Returns
//!		the true if a prox or touch detection is pending/active.
//
//*****************************************************************************
extern bool CAPT_updateProjElementProxTouchWithEMC(tSensor *pSensor,
		tElement *pElement);

#endif
//*****************************************************************************
//! Close the doxygen group
//! @}
//*****************************************************************************
