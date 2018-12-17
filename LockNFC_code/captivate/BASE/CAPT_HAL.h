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
// CAPT_HAL.h
//
//! Low level CapTIvate configuration and peripheral hardware abstraction module.
//
//! This module contains low-level APIs for accessing the CapTIvate&tm; IP.
//! Some functions are a direct access of the CapTIvate&tm; registers while 
//! others take the definitions (see CAPT_Type.h) and place the appropriate 
//! values in the CapTIvate&tm; peripheral registers.
//
//! \version 1.70.00.03
//! Released on July 30, 2018
//
//*****************************************************************************
//*****************************************************************************
//! \addtogroup CAPT_HAL
//! @{
//*****************************************************************************

#ifndef CAPT_HAL_H_
#define CAPT_HAL_H_

#ifndef S_SPLINT_S
#include <stdint.h>
#include <stdbool.h>
#endif

#include <msp430.h>

#include "CAPT_Type.h"

//*****************************************************************************
//
// CapTIvate&tm; Timer Sources
//
//*****************************************************************************
#define CAPT_TIMER_SRC_ACLK                                              (0x00)
#define CAPT_TIMER_SRC_VLOCLK                                            (0x01)

//*****************************************************************************
//
// CapTIvate&tm; Timer Source Dividers
//
//*****************************************************************************
#define CAPT_TIMER_CLKDIV__1                                             (0x00)
#define CAPT_TIMER_CLKDIV__2                                             (0x01)
#define CAPT_TIMER_CLKDIV__4                                             (0x02)
#define CAPT_TIMER_CLKDIV__8                                             (0x03)
#define CAPT_TIMER_CLKDIV__16                                            (0x04)
#define CAPT_TIMER_CLKDIV__32                                            (0x05)
#define CAPT_TIMER_CLKDIV__64                                            (0x06)
#define CAPT_TIMER_CLKDIV__128                                           (0x07)

//*****************************************************************************
//
// CapTIvate&tm; Conversion Counter Interval Selections
//
//*****************************************************************************
#define CAPT_COUNTER__16                                                 (0x00)
#define CAPT_COUNTER__32                                                 (0x01)
#define CAPT_COUNTER__64                                                 (0x02)
#define CAPT_COUNTER__128                                                (0x03)
#define CAPT_COUNTER__256                                                (0x04)
#define CAPT_COUNTER__512                                                (0x05)
#define CAPT_COUNTER__1024                                               (0x06)
#define CAPT_COUNTER__2048                                               (0x07)
#define CAPT_COUNTER__DISABLED                                           (0x08)

//*****************************************************************************
//
// CapTIvate&tm; Conversion Clock Oscillator Frequencies
//
//*****************************************************************************
#define CAPT_OSC_FREQ_DEFAULT                                            (0x00)
#define CAPT_OSC_FREQ_16MHZ                                              (0x00)
#define CAPT_OSC_FREQ_14P7MHZ                                            (0x01)
#define CAPT_OSC_FREQ_13P1MHZ                                            (0x02)
#define CAPT_OSC_FREQ_11P2MHZ                                            (0x03)

//*****************************************************************************
//
// CapTIvate&tm; Reference Capacitor Sizes
//
//*****************************************************************************
#define CAPT_REFERENCE_CAP__SELF_1P0PF                                   (0x00)
#define CAPT_REFERENCE_CAP__SELF_1P1PF                                   (0x04)
#define CAPT_REFERENCE_CAP__SELF_1P5PF                                   (0x05)
#define CAPT_REFERENCE_CAP__SELF_5P0PF                                   (0x02)
#define CAPT_REFERENCE_CAP__SELF_5P1PF                                   (0x06)
#define CAPT_REFERENCE_CAP__SELF_5P5PF                                   (0x07)
#define CAPT_REFERENCE_CAP__MUTUAL_0P1PFM_1P0PF                          (0x00)
#define CAPT_REFERENCE_CAP__MUTUAL_0P5PFM_1P0PF                          (0x01)
#define CAPT_REFERENCE_CAP__MUTUAL_0P1PFM_5P0PF                          (0x02)
#define CAPT_REFERENCE_CAP__MUTUAL_0P5PFM_5P0PF                          (0x03)

//*****************************************************************************
//
// CapTIvate&tm; Coarse Gain Ratios
//
//*****************************************************************************
#define CAPT_COARSEGAIN_0                                                (0x00)
#define CAPT_COARSEGAIN_1                                                (0x01)
#define CAPT_COARSEGAIN_2                                                (0x02)
#define CAPT_COARSEGAIN_3                                                (0x03)
#define CAPT_COARSEGAIN_4                                                (0x04)
#define CAPT_COARSEGAIN_5                                                (0x05)
#define CAPT_COARSEGAIN_6                                                (0x06)
#define CAPT_COARSEGAIN_7                                                (0x07)
#define CAPT_COARSEGAIN_MIN                                 (CAPT_COARSEGAIN_0)
#define CAPT_COARSEGAIN_MAX                                 (CAPT_COARSEGAIN_7)

//*****************************************************************************
//
// CapTIvate&tm; Fine Gain Ratios
//
//*****************************************************************************
#define CAPT_FINEGAIN_0                                                  (0x00)
#define CAPT_FINEGAIN_1                                                  (0x01)
#define CAPT_FINEGAIN_2                                                  (0x02)
#define CAPT_FINEGAIN_3                                                  (0x03)
#define CAPT_FINEGAIN_4                                                  (0x04)
#define CAPT_FINEGAIN_5                                                  (0x05)
#define CAPT_FINEGAIN_6                                                  (0x06)
#define CAPT_FINEGAIN_7                                                  (0x07)
#define CAPT_FINEGAIN_8                                                  (0x08)
#define CAPT_FINEGAIN_9                                                  (0x09)
#define CAPT_FINEGAIN_10                                                 (0x0A)
#define CAPT_FINEGAIN_11                                                 (0x0B)
#define CAPT_FINEGAIN_12                                                 (0x0C)
#define CAPT_FINEGAIN_13                                                 (0x0D)
#define CAPT_FINEGAIN_14                                                 (0x0E)
#define CAPT_FINEGAIN_15                                                 (0x0F)
#define CAPT_FINEGAIN_16                                                 (0x10)
#define CAPT_FINEGAIN_17                                                 (0x11)
#define CAPT_FINEGAIN_18                                                 (0x12)
#define CAPT_FINEGAIN_19                                                 (0x13)
#define CAPT_FINEGAIN_MIN                                     (CAPT_FINEGAIN_0)
#define CAPT_FINEGAIN_MAX                                    (CAPT_FINEGAIN_19)

//*****************************************************************************
//
// CapTIvate&tm; Offset Tap Values
//
//*****************************************************************************
#define CAPT_OFFSETTAP_MIN                                               (0x00)
#define CAPT_OFFSETTAP_MAX                                               (0xFF)

//*****************************************************************************
//
// CapTIvate&tm; Offset Scale Values
//
//*****************************************************************************
#define CAPT_OFFSETSCALE__VERYSMALL                                    (0x0000)
#define CAPT_OFFSETSCALE__SMALL                                        (0x0100)
#define CAPT_OFFSETSCALE__LARGE                                        (0x0200)
#define CAPT_OFFSETSCALE__VERYLARGE                                    (0x0300)
#define CAPT_OFFSETSCALE_MIN                      (CAPT_OFFSETSCALE__VERYSMALL)
#define CAPT_OFFSETSCALE_MAX                      (CAPT_OFFSETSCALE__VERYLARGE)

//*****************************************************************************
//
// CapTIvate&tm; Interrupt Definitions
//
//*****************************************************************************
#define CAPT_END_OF_CONVERSION_INTERRUPT                               (0x0001)
#define CAPT_DETECTION_INTERRUPT                                       (0x0002)
#define CAPT_TIMER_INTERRUPT                                           (0x0004)
#define CAPT_CONVERSION_COUNTER_INTERRUPT                              (0x0008)
#define CAPT_MAX_COUNT_ERROR_INTERRUPT                                 (0x0100)

//*****************************************************************************
//
// CapTIvate&tm; Interrupt Vectors
//
//*****************************************************************************
#define CAPT_IV_NO_INTERRUPT                                           (0x0000)
#define CAPT_IV_END_OF_CONVERSION                                      (0x0002)
#define CAPT_IV_DETECTION                                              (0x0004)
#define CAPT_IV_TIMER                                                  (0x0006)
#define CAPT_IV_CONVERSION_COUNTER                                     (0x0008)
#define CAPT_IV_MAX_COUNT_ERROR                                        (0x000A)
 
//*****************************************************************************
//
//!  CAPT_init is not a ROM function.  This function initializes global
//!  parameters of the CapTIvate peripheral that are independent of mode and 
//!  application.  This function should always be called once to initialize
//!  the peripheral after a reset.
//!
//
//!  Initialize global settings for an application.
//!  \par Parameters
//!		none
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_init(void);


//*****************************************************************************
//
//!  Poll Reset Status Flag of the CapTIvate peripheral; 0, reset is not 
//!  complete.  This function is intended to be used after the CAPT_reset()
//!  function to determine that the peripheral is ready.
//!
//!  \par Parameters
//!		none
//!  \return Reset State
//
//*****************************************************************************
extern bool CAPT_pollResetStatus(void);

//*****************************************************************************
//
//!  Poll Conversion in progress flag (CIPF); 0, no conversion in progress. The 
//!  CIPF is not directly correlated to the conversion start: following a 
//!  conversion start there is a period during which the CIPF is 0 before
//!  transitioning to a 1 when the actual convesion takes place.
//!
//!  \par Parameters
//!		none
//!  \return CIPF state
//
//*****************************************************************************
extern bool CAPT_pollCIPF(void);

//*****************************************************************************
//
//!  Reset the CapTIvate peripheral.
//!
//!  \par Parameters
//!		none
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_reset(void);


//*****************************************************************************
//
//!  Set Stabilization control bit.  This bit is used whenever a conversion is
//!  predicated on a user controlled stabilization time.  The stabilization
//!  control must be set before the conversion is started.
//!
//!  \par Parameters
//!		none
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_setStabilization(void);

//*****************************************************************************
//
//!  Clear Stabilization control bit.  This bit is used whenever a conversion 
//!  is predicated on a user controlled stabilization time.  Although the IO 
//!  will be active, clearing the stabilization control bit will start the  
//!  actual measurement. 
//!
//!  \par Parameters
//!		none
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_releaseStabilization(void);

//*****************************************************************************
//
//!  Enable a Reference cap for a specific block.  The element definition,
//!  tElement.ui8RxBlock, is used to determine which block the reference 
//!  capacitor is applied to.  The reference capacitor size is defined in the 
//!  following table:
//!  Size   Self Value  Mutual Value
//!     0    1.0pF         0.1pF
//!     1    1.0pF         0.5pF
//!     2    5.0pF         0.1pF
//!     3    5.0pF         0.5pF
//!     4    1.1pF         0.1pF
//!     5    1.5pF         0.1pF
//!     6    5.1pF         0.1pF
//!     7    5.5pF         0.1pF
//!
//!  \param pElement = pointer to element
//!  \param capSize = size of cap
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_enableRefCap(tElement* pElement, uint8_t capSize);


//*****************************************************************************
//
//!  Disable and Remove the Reference Capacitor from the measurement circuit.
//!
//!  \par Parameters
//!		none
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_disableRefCap(void);

//*****************************************************************************
//
//!  Enable all IO associated with a sensor.  When a CapTIvate IO is enabled it
//!  is in the analog mode and the digital function is disabled.  Before
//!  enabling the IO it is recommended to set the appropriate IO state as 
//!  defined in the tSensor.bIdleState, with the CAPT_initSensorIO function.  
//!
//!  \param pSensor = pointer to sensor 
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_enableSensorIO(tSensor *pSensor);

//*****************************************************************************
//
//!  Disable all IO associated with a sensor.
//!
//!  \param pSensor = pointer to sensor
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_disableSensorIO(tSensor *pSensor);

//*****************************************************************************
//
//!  This function configures the active (Rx or Tx) and inactive
//!  (High-z or GND) states of the captivate channels, for a given sensor, as 
//!  well as initialize the IO to the inactive state.
//!
//!  \param pSensor = pointer to sensor
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_initSensorIO(tSensor *pSensor);

//*****************************************************************************
//
//!  Set all Sensor IO to Tx or Rx based upon parameter passed.
//!  Also make these active.
//!
//!  \param rxBarTx = Set to Rx if eSelf (0) or Tx if eProjected (1)
//!  \param pSensor = pointer to sensor
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_forceSensorIO(tSenseTechnology rxBarTx, tSensor *pSensor);

//*****************************************************************************
//
//!  Initialize Sensor specific settings that will remain constant for
//!  all cycles within the Sensor.
//!  Parameters Applied:
//!  tSensor.SensingMethod
//!  tSensor.DirectionOfInterest
//!  tSensor.ui16NegativeTouchThreshold
//!  tSensor.ui16ProxThreshold
//!  tSensor.bModEnable
//!  tSensor.ui8BiasControl
//!  tSensor.bCsDischarge
//!  tSensor.bLPMControl
//!  tSensor.ui8InputSyncControl
//!  tSensor.bTimerSyncControl
//!  tSensor.ui8ChargeLength
//!  tSensor.ui8TransferLength
//!  tSensor.ui16ErrorThreshold
//!  tSensor.ui8CntBeta
//!  tSensor.ui8LTABeta
//!  tSensor.bSensorHalt
//!  tSensor.bPTSensorHalt
//!  tSensor.bSensorTouch
//!  tSensor.bSensorProx
//!
//!  \param pSensor = pointer to sensor
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_applySensorParams(tSensor *pSensor);

//*****************************************************************************
//
//!  Enable Sync event.  When enabled the start of conversion is gated by the 
//!  edge of the SYNC pin.   
//!
//!  \par Parameters
//!		none
//!  \par Returns
//!		none
//
 //*****************************************************************************
extern void CAPT_enableSensorSyncEvent(void);

//*****************************************************************************
//
//!  Disable Sync event.
//!
//!  \par Parameters
//!		none
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_disableSensorSyncEvent(void);

//*****************************************************************************
//
//!  Bypass FSM.  Bypassing the FSM only the maximum count and end of
//!  conversion IFGs are updated.  
//!
//!  \par Parameters
//!		none
//!  \par Returns
//!		none.
//
//*****************************************************************************
extern void CAPT_bypassFSM(void);

//*****************************************************************************
//
//!  Engage FSM.  The Finite State Machine (FSM), performs several post
//!  measurement filters for the LTA, and measurement filter count as well as 
//!  well as detection logic.  
//!
//!  \par Parameters
//!		none
//!  \par Returns
//!		none
//!
//
//*****************************************************************************
extern void CAPT_engageFSM(void);

//*****************************************************************************
//
//!  Apply the Sensor frequency divider and for the requested frequency select.
//!  This frequency is consistent for all elements within the cycle.  
//!  freqSelect    Frequency
//!      0            16Mhz
//!      1            14.7Mhz
//!      2            13.1Mhz
//!      3            11.2Mhz
//!
//!  \param freqSelect = frequency
//!  \param pSensor = pointer to sensor
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_applySensorFreq(uint8_t freqSelect, tSensor *pSensor);

//*****************************************************************************
//
//!  Initialize cycle IO parameters.  Set to active the channels required for
//!  the cycle measurement.  The peripheral will manage the IO state
//!  transitioning the active channels between the defined active state 
//! (Rx or Tx) when actively measuring capacitance and the inactive state 
//! (GND or High-Z) when the measurement is complete.  All channels that are 
//! not active but enabled will remain in their inactive state.
//!
//!  \param pSensor = pointer to sensor
//!  \param pCycle = pointer to cycle
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_setCycleIO(tSensor *pSensor,tCycle *pCycle);

//*****************************************************************************
//
//!  Clear cycle IO parameters.  Clear active channels.
//!
//!  \param pSensor = pointer to sensor
//!  \param pCycle = pointer to cycle
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_clearCycleIO(tSensor *pSensor, tCycle *pCycle);

//*****************************************************************************
//
//!  Initialize cycle level parameters.  These parameters are consistent for
//!  all elements within the cycle.
//!
//!  \param freqOffset = offset to indicate which frequency is being measured
//!  \param pCycle = pointer to cycle
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_applyCycleComp(uint8_t freqOffset,tCycle * pCycle);

//*****************************************************************************
//
//!  Apply cycle level parameters.  These parameters are consistent for all
//!  elements within the cycle.
//!
//!  \param pCycle = pointer to cycle
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_applyCycleFSM(tCycle *pCycle);

//*****************************************************************************
//
//!  Enable ISR.  The interrupts are defined as follows:
//!               BIT0   End of Conversion interrupt enable
//!               BIT1   CapTIvate detection interrupt enable
//!               BIT2   CapTIvate Timer interrupt enable
//!               BIT3   CapTIvate Conversion Counter interrupt enable
//!               BIT8   CapTIvate maximum count error interrupt enable
//!
//!  \param interruptEnable = Interrupt(s) to enable
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_enableISR(uint16_t interruptEnable);

//*****************************************************************************
//
//!  Disable ISR.  The interrupts are defined as follows:
//!               BIT0   End of Conversion interrupt disable
//!               BIT1   CapTIvate detection interrupt disable
//!               BIT2   CapTIvate Timer interrupt disable
//!               BIT3   CapTIvate Conversion Counter interrupt disable
//!               BIT8   CapTIvate maximum count error interrupt disable
//!
//!  \param interruptDisable = Interrupt(s) to disable
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_disableISR(uint16_t interruptDisable);

//*****************************************************************************
//
//!  Set the cycle conversion bit.  If the CAPPWR bit is set 
//!  (call CAPT_powerOn), then setting the cycle conversion bit will start the 
//!  conversion process - the actual conversion (indicated by CAPT_pollCIPF 
//!  returning a '1') will take place after the stabilization time.  If the 
//!  SYNC enable is set, either via the sensor configuration and 
//!  CAPT_applySensor API or the CAPT_enableSensorSyncEvent API, then the 
//!  conversion will be gate by the SYNC event (rising/falling edge) on the 
//!  SYNC pin.
//!
//!  \par Parameters
//!		none
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_setCAPSTART(void);

//*****************************************************************************
//
//!  Clear the cycle conversion bit.  When the conversion is in progress,  
//!  calling CAPT_clearCAPSTART will stop the conversion.  
//!
//!  \par Parameters
//!		none
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_clearCAPSTART(void);

//*****************************************************************************
//
//!  Save the current status of the peripheral into the data structures of 
//!  Raw measurement information is stored in:
//!      pCycle->pElement[n]->pRawCount[indexFreq], where n is 0 to 
//!          pCycle.ui8NumberofElements
//!  If there is a maximum count error, then the bit pSensor->bMaxCountError is 
//!  set and the value in pCycle->pElement[n]->pRawCount[indexFreq] is cleared.
//!
//!  \param indexFreq = save results for selected frequency.
//!  \param pSensor = pointer to sensor.
//!  \param pCycle = pointer to cycle.
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_saveCycleRawResults(uint8_t indexFreq,tSensor *pSensor, tCycle *pCycle);

//*****************************************************************************
//
//!  Save filter results, pElements[n]->LTA and pElements[n]->filterCount, and 
//!  status bits, pElements[n]->bDetect and pElements[n]->bNegativeTouch, in 
//!  addition to what is saved in CAPT_saveCycleRawResults from the peripheral.
//!
//!  \param pSensor = pointer to sensor.
//!  \param pCycle = pointer to cycle.
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_saveCycleResults(tSensor *pSensor ,tCycle *pCycle);

//*****************************************************************************
//
//!  Select the CapTIvate&tm; counter interval. The input represents the number
//!  of conversions until a counter overflow event, CAPCNTRIFG.
//!      counterSel     Number of Conversions
//!         0                   16
//!         1                   32
//!         2                   64
//!         3                  128
//!         4                  256
//!         5                  512
//!         6                 1024
//!         7                 2048
//!
//!  \param counterSel = counter selection
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_selectCCounterInterval(uint8_t counterSel);

//*****************************************************************************
//
//!  Clear the CapTIvate&tm; counter interval.
//!
//!  \par Parameters
//!		none
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_clearCCounter(void);

//*****************************************************************************
//
//!  Start (enable) the CapTIvate&tm; counter interval.
//!
//!  \par Parameters
//!		none
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_startCCounter(void);

//*****************************************************************************
//
//!  Stop (disable) the CapTIvate&tm; counter interval.
//!
//!  \par Parameters
//!		none
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_stopCCounter(void);


//*****************************************************************************
//
//!  Select the input divider to the CapTIvate&tm; timer.
//!
//!  \param sourceDiv = time source divider
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_selectTimerSourceDivider(uint8_t sourceDiv);

//*****************************************************************************
//
//!  Select the input source to the CapTIvate&tm; timer.
//!
//!  \param source = timer source selection
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_selectTimerSource(uint8_t source);

//*****************************************************************************
//
//!  Enable measurements to be triggered from CapTIvate&tm; timer.
//!  Set CAPTCCTRL0:CAPTCONV
//!
//!  \par Parameters
//!		none
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_enableTimerTrigMeasurement(void);

//*****************************************************************************
//
//!  Disable measurements to be triggered from CapTIvate&tm; timer.
//!  Clear CAPTCCTRL0:CAPTCONV
//!
//!  \par Parameters
//!		none
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_disableTimerTrigMeasurement(void);


//*****************************************************************************
//
//!  Clear the CapTIvate&tm; timer.
//!
//!  \par Parameters
//!		none
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_clearTimer(void);

//*****************************************************************************
//
//!  Start (enable) the CapTIvate&tm; timer.
//!
//!  \par Parameters
//!		none
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_startTimer(void);

//*****************************************************************************
//
//!  Stop (disable) the CapTIvate&tm; timer.
//!
//!  \par Parameters
//!		none
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_stopTimer(void);

//*****************************************************************************
//
//!  Stop (disable) the CapTIvate&tm; timer.
//!
//!  \par Parameters
//!		none
//!  \return timer contents
//
//*****************************************************************************
extern uint16_t CAPT_readTimerRegister(void);

//*****************************************************************************
//
//!  Read value from timer compare register.
//!
//!  \par Parameters
//!		none
//!  \return Compare Register Value
//
//*****************************************************************************
extern uint16_t CAPT_readTimerCompRegister(void);

//*****************************************************************************
//
//!  Write value into timer compare register.
//!
//!  \param  compRegister = Compare Register Value
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_writeTimerCompRegister(uint16_t compRegister);

//*****************************************************************************
//
//!  Turn off the CapTIvate&tm; IP.
//!
//!  \par Parameters
//!		none
//!  \return Compare Register Value
//
//*****************************************************************************
extern void CAPT_powerOff(void);

//*****************************************************************************
//
//!  Turn on the CapTIvate&tm; IP.
//!
//!  \par Parameters
//!		none
//!  \return Compare Register Value
//
//*****************************************************************************
extern void CAPT_powerOn(void);

//*****************************************************************************
//
//!  Activate specific IO channel, CAPx.y, ui8Block-> x, ui8Pin->y.  When a
//!  conversion is started then this IO will enter either a Tx or Rx mode of
//!  operation.
//!
//!  \param ui8Block = select block
//!  \param ui8Pin = select pin
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_setChannelActive(uint8_t ui8Block, uint8_t ui8Pin);

//*****************************************************************************
//
//!  Enable a specific IO channel, CAPx.y, ui8Block-> x, ui8Pin->y.
//!
//!  \param ui8Block = select block
//!  \param ui8Pin = select pin
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_setChannelEnable(uint8_t ui8Block, uint8_t ui8Pin);

//*****************************************************************************
//
//!  Set off state for specific IO channel, CAPx.y, ui8Block-> x, ui8Pin->y.
//!  This puts the IO into the Ground state when enabled and not active.
//!
//!  \param ui8Block = select block
//!  \param ui8Pin = select pin
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_setChannelOffState(uint8_t ui8Block, uint8_t ui8Pin);

//*****************************************************************************
//
//!  Set on state for specific IO channel, CAPx.y, ui8Block-> x, ui8Pin->y.
//!  This puts the IO into the Rx mode.  The mode, mutual or self, is defined
//!  by the sensor parameter tSensor.SensingMethod and applied by API
//!  CAPT_apply_SensorParams.  The default setting for the block is self mode.
//!
//!  \param ui8Block = select block
//!  \param ui8Pin = select pin
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_setChannelOnState(uint8_t ui8Block, uint8_t ui8Pin);

//*****************************************************************************
//
//!  Activate a specific IO channel, CAPx.y, ui8Block-> x, ui8Pin->y.
//!
//!  \param ui8Block = select block
//!  \param ui8Pin = select pin
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_clearChannelActive(uint8_t ui8Block, uint8_t ui8Pin);


//*****************************************************************************
//
//!  Enable a specific IO channel, CAPx.y, ui8Block-> x, ui8Pin->y.
//!
//!  \param ui8Block = select block
//!  \param ui8Pin = select pin
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_clearChannelEnable(uint8_t ui8Block, uint8_t ui8Pin);

//*****************************************************************************
//
//!  Clear off state for specific IO channel, CAPx.y, ui8Block-> x, ui8Pin->y.
//!
//!  \param ui8Block = select block
//!  \param ui8Pin = select pin
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_clearChannelOffState(uint8_t ui8Block, uint8_t ui8Pin);

//*****************************************************************************
//
//!  Set on state for specific IO channel, CAPx.y, ui8Block-> x, ui8Pin->y.
//!
//!  \param ui8Block = select block
//!  \param ui8Pin = select pin
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_clearChannelOnState(uint8_t ui8Block, uint8_t ui8Pin);

//*****************************************************************************
//
//!  Write Coarse Gain value to Block Compensation.
//!
//!  \param ui8Block = select block
//!  \param ui8Value = value
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_writeCoarseGain(uint8_t ui8Block, uint8_t ui8Value);

//*****************************************************************************
//
//!  Read Coarse Gain value from Block Compensation.
//!
//!  \param ui8Block = select block
//!  \return 8-bit coarse gain value
//
//*****************************************************************************
extern uint8_t CAPT_readCoarseGain(uint8_t ui8Block);

//*****************************************************************************
//
//!  Write Fine Gain value to Block Compensation.
//!
//!  \param ui8Block = select block
//!  \param ui8Value = value
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_writeFineGain(uint8_t ui8Block, uint8_t ui8Value);

//*****************************************************************************
//
//!  Read Fine Gain value from Block Compensation.
//!
//!  \param ui8Block = select block
//!  \return 8-bit fine gain value
//
//*****************************************************************************
extern uint8_t CAPT_readFineGain(uint8_t ui8Block);

//*****************************************************************************
//
//!  Write Offset Tap value to Block Compensation.
//!
//!  \param ui8Block = select block
//!  \param ui16Value = offsetvalue
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_writeOffsetTap(uint8_t ui8Block, uint16_t ui16Value);

//*****************************************************************************
//
//!  Read Offset Tap value from Block Compensation.
//!
//!  \param ui8Block = select block
//!  \return 16-bit offset tap value
//
//*****************************************************************************
extern uint16_t CAPT_readOffsetTap(uint8_t ui8Block);

//*****************************************************************************
//
//!  Read Conversion value from Block.
//!
//!  \param ui8Block = select block
//!  \return 16-bit conversion value
//
//*****************************************************************************
extern uint16_t CAPT_readConversion(uint8_t ui8Block);


//*****************************************************************************
//
//!  Set CAPLPMCFG.
//!
//!  \par Parameters
//!		none
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_setCAPLPMCFG(void);

//*****************************************************************************
//
//!  Clear CAPLPMCFG.
//!
//!  \par Parameters
//!		none
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_clearCAPLPMCFG(void);

//*****************************************************************************
//
//!  Poll a CapTIvate&tm; peripheral interrupt flag.
//!
//!  \param ui16InterruptMask is a bit mask of the interrupts to test.
//!	
//!  \return interrupt flags that are set
//
//*****************************************************************************
extern uint16_t CAPT_pollIFG(uint16_t ui16InterruptMask);

//*****************************************************************************
//
//!  Clear a Captivate peripheral interrupt flag.  The bit mask is defined as:
//!  BIT0 -> End Of Conversion IFG
//!  BIT1 -> Detection IFG
//!  BIT2 -> CapTIvate Timer IFG (number of clock cycles)
//!  BIT3 -> CapTIvate Counter IFG (number of conversion cycles)
//!
//!  BIT8 -> Maximum Count Error IFG
//!
//!  \param ui16InterruptMask is a bit mask of the interrupt flags to clear.
//!		
//!  \return none.
//
//*****************************************************************************
extern void CAPT_clearIFG(uint16_t ui16InterruptMask);

//*****************************************************************************
//
//!  Retreive the CapTIvate&tm; peripheral interrupt vector register
//!
//!  \param none.
//!	
//!  \return current value of the CapTIvate&tm; IV register.
//
//*****************************************************************************
extern uint16_t CAPT_getInterruptVector(void);

//*****************************************************************************
//
//!  Enable a CapTIvate IO to be a shield.
//!
//!  \param ui8Block is the CapTIvate block that the shield resides on.
//!  \param ui8Pin is the pin on the block that the shield is connected to.
//!	
//!  \returns
//!      None.
//
//*****************************************************************************
extern void CAPT_enableShieldIO(uint8_t ui8Block, uint8_t ui8Pin);

//*****************************************************************************
//
//!  Disable a CapTIvate shield IO.
//!
//!  \param ui8Block is the CapTIvate block that the shield resides on.
//!  \param ui8Pin is the pin on the block that the shield is connected to.
//!	
//!  \returns
//!      None.
//
//*****************************************************************************
extern void CAPT_disableShieldIO(uint8_t ui8Block, uint8_t ui8Pin);

#endif /* CAPT_HAL_H_ */
//*****************************************************************************
//! Close the doxygen group
//! @}
//*****************************************************************************
