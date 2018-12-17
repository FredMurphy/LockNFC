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
// CAPT_BSP.c
//
// *** CLOCK CONFIGURATION ***
// MCLK is 8 MHz, sourced from the DCO
// SMCLK is 2 MHz, sourced from MCLK
// ACLK is 32kHz, sourced from XT1 or REFO, with XT1 having priority
// FLLREF is 32kHz, sourced from XT1 or REFO, with XT1 having priority
//
// *** SERIAL INTERFACES ***
// This board support package supports the MSP430FR2633 device.
// UCA0 is muxed in UART mode to P1.4 and P1.5
// UCB0 is muxed in I2C mode to P1.2 and P1.3
// P1.1 is set up as an open drain input
//
// \version 1.70.00.03
// Released on July 30, 2018
//
//*****************************************************************************

#include <msp430.h>
#include <stdint.h>

#include "CAPT_BSP.h"

//*****************************************************************************
//
//! This function is configures the MCU Digital IO and CS for operation.
//
//*****************************************************************************
void BSP_configureMCU(void)
{
	uint8_t ui8LFOsc = CS_XT1CLK_SELECT;

    // P1.0: RED LED
    // P1.1: GREEN LED
    // P1.2: BLUE LED
    // P1.3: TRF_EN
    // P1.4: UCA0 SPI MOSI
    // P1.5: UCA0 SPI MISO
    // P1.6: UCAO SPI CLK
    // P1.7:
    P1OUT  = (GPIO_PIN0 | GPIO_PIN1 | GPIO_PIN2);
    P1DIR  = (GPIO_PIN0 | GPIO_PIN1 | GPIO_PIN2 | GPIO_PIN3);
    P1SEL0 = (GPIO_PIN4 | GPIO_PIN5 | GPIO_PIN6);
    P1SEL1 = (0);


	// P2.0: XOUT
	// P2.1: XIN
	// P2.2: SYNC (SET OUTPUT LOW UNLESS USED)
	// P2.3: OUTPUT LOW
	// P2.4: OUTPUT LOW
	// P2.5: OUTPUT LOW
	// P2.6: OUTPUT LOW
	// P2.7: OUTPUT LOW
	P2OUT  =  (0);
	P2DIR  =  (GPIO_PIN2 | GPIO_PIN3 | GPIO_PIN4 | GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7);
	P2SEL0 =  (GPIO_PIN0 | GPIO_PIN1);
	P2SEL1 =  (0);

	// P3.0: OUTPUT LOW
	// P3.1: OUTPUT LOW
	// P3.2: OUTPUT LOW
	P3OUT  =  (0);
	P3DIR  =  (GPIO_PIN0 | GPIO_PIN1 | GPIO_PIN2);
	P3SEL0 =  (0);
	P3SEL1 =  (0);

	//
	// Clear port lock
	//
	PM5CTL0 &= ~LOCKLPM5;
	
	// Configure FRAM wait state (set to 1 to support 16MHz MCLK)
	FRAMCtl_configureWaitStateControl(FRAMCTL_ACCESS_TIME_CYCLES_1);

	//
	// Attempt to start the low frequency crystal oscillator
	//
	CS_setExternalClockSource(XT1_OSC_FREQ);
	if (CS_turnOnXT1LFWithTimeout(CS_XT1_DRIVE_0, XT1_OSC_TIMEOUT) == STATUS_FAIL)
	{
		//
		// If a crystal is not present or is failing, switch the LF
		// clock definition to the internal 32kHz reference oscillator.
		//
		ui8LFOsc = CS_REFOCLK_SELECT;
	}

	//
	// Initialize Clock Signals
	//
	CS_initClockSignal(CS_FLLREF, ui8LFOsc, CS_CLOCK_DIVIDER_1);
	CS_initClockSignal(CS_ACLK, ui8LFOsc, CS_CLOCK_DIVIDER_1);
	CS_initClockSignal(CS_MCLK, CS_DCOCLKDIV_SELECT, CS_CLOCK_DIVIDER_1);
	CS_initClockSignal(CS_SMCLK, CS_DCOCLKDIV_SELECT, CS_CLOCK_DIVIDER_8);

	//
	// Tune the DCO parameters
	//
	CS_initFLL((MCLK_FREQ/1000), FLL_RATIO);
	CS_clearAllOscFlagsWithTimeout(1000);
}

//*****************************************************************************
//
//! This function disables the watchdog timer during boot, ensuring a WDT
//! reset does not occur during boot before main() is entered.
//
//*****************************************************************************
int _system_pre_init(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    return 1;
}
