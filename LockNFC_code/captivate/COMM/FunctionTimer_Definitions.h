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
//  FunctionTimer_Definitions.h
//
//! This is the function timer module definitions file.
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

#ifndef FUNCTIONTIMER_DEF_H_
#define FUNCTIONTIMER_DEF_H_

#include "driverlib.h"

//
//! CAPT_CommConfig is used to control I2C__ENABLE.
//
#include "CAPT_CommConfig.h"

//*****************************************************************************
//
//! \def FUNCTIONTIMER__ENABLE defines whether the function timer module
//! is included in the build.
//
//*****************************************************************************
// NOTE: Rather than enabling here, the enable is controlled in
// CAPT_CommConfig.
//#define FUNCTIONTIMER__ENABLE				(true)


//*****************************************************************************
//
//! \def FUNCTIONTIMER__PERIPHERAL defines the MSP430 base address of the
//! Timer_A instance used by the serial driver.
//
//*****************************************************************************
#ifdef __MSP430_HAS_TA3__
#define FUNCTIONTIMER__PERIPHERAL	(TIMER_A3_BASE)
#elif __MSP430_HAS_TA1__
#define FUNCTIONTIMER__PERIPHERAL	(TIMER_A1_BASE)
#else
#define FUNCTIONTIMER__PERIPHERAL	(TIMER_A0_BASE)
#endif

//*****************************************************************************
//
//! \def FUNCTIONTIMER__CLOCK specifies the clock source for the function
//! timer Timer_A instance.
//
//*****************************************************************************
#define FUNCTIONTIMER__CLOCK		                             (TASSEL__ACLK)

//*****************************************************************************
//
//! \def FUNCTIONTIMER__DIVIDER specifies the clock source divider for the
//! function timer Timer_A instance.
//
//*****************************************************************************
#define FUNCTIONTIMER__DIVIDER		                                    (ID__1)

//*****************************************************************************
//
//! \def FUNCTIONTIMER__EXDIVIDER specifies the clock source extended divider
//! for the function timer Timer_A instance.
//
//*****************************************************************************
#define FUNCTIONTIMER__EXDIVIDER	                                 (TAIDEX_0)

//*****************************************************************************
//
//! \def FUNCTIONTIMER__LPM_CLEAR specifies which LPM bits are cleared if a
//! function timer callback function exits true.
//
//*****************************************************************************
#define FUNCTIONTIMER__LPM_CLEAR	                                (LPM3_bits)

#endif /* FUNCTIONTIMER_DEF_H_ */

//*****************************************************************************
//! Close the doxygen group
//! @}
//*****************************************************************************
