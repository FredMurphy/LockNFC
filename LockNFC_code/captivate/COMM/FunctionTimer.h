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
//  FunctionTimer.h
//
//! Timer based communication time-out management.
//
//! The function timer provides a mechanism to call a function in the
//! foreground (from an ISR) after a specified delay, specified in timer
//! cycles.  One Timer_A instance is required.  Up to two delayed functions
//! may be registered at the same time (Function A and Function B) with
//! each having a different delay.  A Timer_A instance with at least a CCR0
//! and CCR1 unit is required.
//
//! \version 1.70.00.03
//! Released on July 30, 2018
//
//*****************************************************************************
//*****************************************************************************
//! \addtogroup FunctionTimer
//! @{
//*****************************************************************************

#ifndef FUNCTIONTIMER_H_
#define FUNCTIONTIMER_H_

#include "FunctionTimer_Definitions.h"

#if (FUNCTIONTIMER__ENABLE==true)

//*****************************************************************************
//
//! \enum tFunctionTimerSelection enumerates the available function delays.
//
//*****************************************************************************
enum tFunctionTimerSelection {
	eTimerDelayedFunction_A,
	eTimerDelayedFunction_B
};

//*****************************************************************************
//
//! typedef tFunctionTimer defines the configuration structure for a function
//! timer.  One instance of this structure must be created by the user and
//! passed to the Timer_startDelayedFunctionTimer function.  This structure
//! identifies the pointers and delays for function A and function B.
//
//*****************************************************************************
typedef struct
{
	//
	//! ui16FunctionDelay_A stores the delay (in timer clock cycles) that
	//! is applied to function A.
	//
	uint16_t ui16FunctionDelay_A;

	//
	//! pbFunction_A stores the pointer to function A, which will be called
	//! ui16FunctionDelay_A seconds after Timer_scheduleDelayedFunction() is
	//! called with eTimerDelayedFunction_A specified.
	//
	bool (*pbFunction_A)(void);

	//
	//! ui16FunctionDelay_B stores the delay (in timer clock cycles) that
	//! is applied to function B.
	//
	uint16_t ui16FunctionDelay_B;

	//
	//! pbFunction_B stores the pointer to function B, which will be called
	//! ui16FunctionDelay_B seconds after Timer_scheduleDelayedFunction() is
	//! called with eTimerDelayedFunction_B specified.
	//
	bool (*pbFunction_B)(void);

} tFunctionTimer;

//*****************************************************************************
//
//! \def TIMER__CCR0_VECTOR defines the interrupt vector location
//! of the selected Timer_A peripheral for CCR0 / Function A.
//
//! \def TIMER__CCR1_VECTOR defines the interrupt vector location
//! of the selected Timer_A peripheral for CCR1 / Function B.
//
//*****************************************************************************
#if (FUNCTIONTIMER__PERIPHERAL==TIMER_A0_BASE)
#define TIMER__CCR0_VECTOR     	(TIMER0_A0_VECTOR)
#define TIMER__CCR1_VECTOR     	(TIMER0_A1_VECTOR)
#elif (FUNCTIONTIMER__PERIPHERAL==TIMER_A1_BASE)
#define TIMER__CCR0_VECTOR     	(TIMER1_A0_VECTOR)
#define TIMER__CCR1_VECTOR     	(TIMER1_A1_VECTOR)
#elif (FUNCTIONTIMER__PERIPHERAL==TIMER_A2_BASE)
#define TIMER__CCR0_VECTOR     	(TIMER2_A0_VECTOR)
#define TIMER__CCR1_VECTOR     	(TIMER2_A1_VECTOR)
#elif (FUNCTIONTIMER__PERIPHERAL==TIMER_A3_BASE)
#define TIMER__CCR0_VECTOR     	(TIMER3_A0_VECTOR)
#define TIMER__CCR1_VECTOR     	(TIMER3_A1_VECTOR)
#else
#error INVALID_TIMERA_SELECTION
#endif

//*****************************************************************************
//
//! This function registers the tFunctionTimer configuration structure with the
//! module, so that the module knows the delays and function pointers.  It then
//! starts the Timer_A instance counting in continuous mode.
//
//! \param pFunctionTimer is a pointer to the function timer configuration
//! structure to use.
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void Timer_startDelayedFunctionTimer(const tFunctionTimer *pFunctionTimer);

//*****************************************************************************
//
//! This function stops the Timer_A.
//
//!  \par Parameters
//!		none
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void Timer_stopDelayedFunctionTimer(void);

//*****************************************************************************
//
//! This function starts the delay for the passed function (A or B), which
//! will then be called after the expiration of the delay.
//
//! \param ui8Function specifies the function to schedule (A or B).
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void Timer_scheduleDelayedFunction(uint8_t ui8Function);

//*****************************************************************************
//
//! This function cancels a scheduled function if the delay has not already
//! expired.  If the delay has expired, this function has no effect.
//
//! \param ui8Function specifies the function to cancel (A or B).
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void Timer_cancelDelayedFunction(uint8_t ui8Function);

#endif /* FUNCTIONTIMER__ENABLE */

#endif /* FUNCTIONTIMER_DEF_H_ */

//*****************************************************************************
//! Close the doxygen group
//! @}
//*****************************************************************************
