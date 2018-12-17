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
// FunctionTimer.c
//
// \version 1.70.00.03
// Released on July 30, 2018
//
//*****************************************************************************
//*****************************************************************************
//! \addtogroup FunctionTimer
//! @{
//*****************************************************************************

#include "FunctionTimer.h"

#if (FUNCTIONTIMER__ENABLE==true)

//*****************************************************************************
//
//! const g_pFunctionTimer stores a pointer to the current tFunctionTimer
//! instance associated with this module.  The memory pointed to by this
//! variable must not be modified between when
//! Timer_startDelayedFunctionTimer() is called and
//! Timer_stopDelayedFunctionTimer() is called.
//
//*****************************************************************************
const tFunctionTimer *g_pFunctionTimer;

//*****************************************************************************
//
//! \def HWREG16 provides a macro to access 16-bit hardware registers.
//
//*****************************************************************************
#define HWREG16(x)	(*((volatile uint16_t *)((uint16_t)x)))

void Timer_startDelayedFunctionTimer(const tFunctionTimer *pFunctionTimer)
{
	Timer_stopDelayedFunctionTimer();
	g_pFunctionTimer = pFunctionTimer;
	HWREG16(FUNCTIONTIMER__PERIPHERAL + OFS_TAxCCTL0) &= ~(CCIFG);
	HWREG16(FUNCTIONTIMER__PERIPHERAL + OFS_TAxCCTL1) &= ~(CCIFG);
	HWREG16(FUNCTIONTIMER__PERIPHERAL + OFS_TAxEX0) = FUNCTIONTIMER__EXDIVIDER;
	HWREG16(FUNCTIONTIMER__PERIPHERAL + OFS_TAxCTL) =
		(FUNCTIONTIMER__CLOCK | FUNCTIONTIMER__DIVIDER | MC__CONTINUOUS | TACLR);
}

void Timer_stopDelayedFunctionTimer(void)
{
	HWREG16(FUNCTIONTIMER__PERIPHERAL + OFS_TAxCTL) = 0;
}

void Timer_scheduleDelayedFunction(uint8_t ui8Function)
{
	HWREG16(FUNCTIONTIMER__PERIPHERAL + OFS_TAxCTL) &= ~(MC__CONTINUOUS);

	switch (ui8Function)
	{
		case eTimerDelayedFunction_A:
			HWREG16(FUNCTIONTIMER__PERIPHERAL + OFS_TAxCCR0) =
					HWREG16(FUNCTIONTIMER__PERIPHERAL + OFS_TAxR) + g_pFunctionTimer->ui16FunctionDelay_A;
			HWREG16(FUNCTIONTIMER__PERIPHERAL + OFS_TAxCCTL0) = CCIE;
			break;

		case eTimerDelayedFunction_B:
			HWREG16(FUNCTIONTIMER__PERIPHERAL + OFS_TAxCCR1) =
					HWREG16(FUNCTIONTIMER__PERIPHERAL + OFS_TAxR) + g_pFunctionTimer->ui16FunctionDelay_B;
			HWREG16(FUNCTIONTIMER__PERIPHERAL + OFS_TAxCCTL1) = CCIE;
			break;

		default:
			break;
	}
	HWREG16(FUNCTIONTIMER__PERIPHERAL + OFS_TAxCTL) |= MC__CONTINUOUS;
}

void Timer_cancelDelayedFunction(uint8_t ui8Function)
{
	switch (ui8Function)
	{
		case eTimerDelayedFunction_A:
			HWREG16(FUNCTIONTIMER__PERIPHERAL + OFS_TAxCCTL0) = 0;
			break;

		case eTimerDelayedFunction_B:
			HWREG16(FUNCTIONTIMER__PERIPHERAL + OFS_TAxCCTL1) = 0;
			break;

		default:
			break;
	}
}

#pragma vector=TIMER__CCR0_VECTOR
__interrupt void FunctionTimer_A_ISR(void)
{
	HWREG16(FUNCTIONTIMER__PERIPHERAL + OFS_TAxCCTL0) = 0;
	if (g_pFunctionTimer->pbFunction_A != 0)
	{
		if (g_pFunctionTimer->pbFunction_A() == true)
		{
			__bic_SR_register_on_exit(FUNCTIONTIMER__LPM_CLEAR);
		}
	}
}

#pragma vector=TIMER__CCR1_VECTOR
__interrupt void FunctionTimer_B_ISR(void)
{
	HWREG16(FUNCTIONTIMER__PERIPHERAL + OFS_TAxCCTL1) = 0;
	if (g_pFunctionTimer->pbFunction_B != 0)
	{
		if (g_pFunctionTimer->pbFunction_B() == true)
		{
			__bic_SR_register_on_exit(FUNCTIONTIMER__LPM_CLEAR);
		}
	}
}

#endif /* FUNCTIONTIMER__ENABLE */

//*****************************************************************************
//! Close the doxygen group
//! @}
//*****************************************************************************
