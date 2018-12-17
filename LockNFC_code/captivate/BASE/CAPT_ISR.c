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
// CAPT_ISR.c
//
//! CapTIvate&tm; peripheral interrupt service routine.
//
//! The ISR serves to set status flags that may be used by the application.
//! The CapTIvate&tm; ISR always exits in CPU active mode.
//
//! \version 1.70.00.03
//! Released on July 30, 2018
//
//*****************************************************************************
//*****************************************************************************
//! \addtogroup CAPT_ISR
//! @{
//*****************************************************************************

#include <msp430.h>
#include <stdbool.h>
#include "CAPT_HAL.h"

//*****************************************************************************
//
//! \var g_bEndOfConversionFlag is a global flag used to indicate to the
//! CAPT_Touch layer when a conversion has completed.  This flag must be set
//! by the application's CapTIvate&tm; ISR to communicate to the touch layer
//! when a conversion has completed.
//
//! \var g_bDetectionFlag
//! This bool is set by the CapTIvate&tm; ISR when a detection interrupt occurs.
//
//! \var g_bConvTimerFlag
//! This bool is set by the CapTIvate&tm; timer when it is time to update (refresh)
//! the user interface.
//
//! \var g_bConvCounterFlag
//! This bool is set by the CapTIvate&tm; ISR when a conversion counter interrupt
//! occurs.
//
//! \var g_bMaxCountErrorFlag
//! This bool is set by the CapTIvate&tm; ISR when a maximum count error interrupt
//! occurs.
//
//*****************************************************************************
volatile bool g_bEndOfConversionFlag;
volatile bool g_bDetectionFlag;
volatile bool g_bConvTimerFlag;
volatile bool g_bConvCounterFlag;
volatile bool g_bMaxCountErrorFlag;

//*****************************************************************************
//
//! CAPT_ISR is the Captivate peripheral interrupt service routine.
//
//*****************************************************************************
#pragma vector=CAPTIVATE_VECTOR
__interrupt void CAPT_ISR(void)
{
	switch(__even_in_range(CAPT_getInterruptVector(), CAPT_IV_MAX_COUNT_ERROR))
	{
		// End of Conversion Interrupt
		case CAPT_IV_END_OF_CONVERSION:
			g_bEndOfConversionFlag = true;
			break;

		// Detection Interrupt
		case CAPT_IV_DETECTION:
			g_bDetectionFlag = true;
			break;

		// Timer Interrupt
		case CAPT_IV_TIMER:
			g_bConvTimerFlag = true;
			break;

		// Conversion Counter Interrupt
		case CAPT_IV_CONVERSION_COUNTER:
			g_bConvCounterFlag = true;
			break;

		// Max Count Error Interrupt
		case CAPT_IV_MAX_COUNT_ERROR:
			g_bMaxCountErrorFlag = true;
			break;
	}
	__bic_SR_register_on_exit(LPM3_bits);
}
//*****************************************************************************
//! Close the doxygen group
//! @}
//*****************************************************************************
