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
// Development main.c for MSP430FR2633, MSP430FR2533, MSP430FR2632, and
// MSP430FR2532.
//
// This starter application initializes the CapTIvate touch library
// for the touch panel specified by CAPT_UserConfig.c/.h via a call to
// CAPT_appStart(), which initializes and calibrates all sensors in the
// application, and starts the CapTIvate interval timer.
//
// Then, the capacitive touch interface is driven by calling the CapTIvate
// application handler, CAPT_appHandler().  The application handler manages
// whether the user interface (UI) is running in full active scan mode, or
// in a low-power wake-on-proximity mode.
//
// The CapTIvate application handler will return true if proximity was
// detected on any of the sensors in the application, which is used here
// to control the state of LED2. LED1 is set while the background loop enters
// the handler, and is cleared when the background loop leaves the handler.
//
// \version 1.60.00.03
// Released on November 22, 2017
//
//*****************************************************************************

#include "main.h"

tISO14443A_UidSize uidSize;
uint8_t *uid;

enum
{
    Active,
    Opening,
    AddTag,
    AddCode
};
typedef uint8_t tState;

tState state = Active;
uint8_t nfcStatus;
uint16_t pause;
uint8_t nfcDuty;
#define NFC_DUTY_RATIO 8

void main(void)
{
	//
	// Initialize the MCU
	// BSP_configureMCU() sets up the device IO and clocking
	// The global interrupt enable is set to allow peripherals
	// to wake the MCU.
	//
	WDTCTL = WDTPW | WDTHOLD;
	BSP_configureMCU();
	__bis_SR_register(GIE);

	LED_RED;
    LED_GREEN;
    LED_BLUE;
    LED_OFF;

	capTouchInit();
	nfcInit();
	nfcDuty = NFC_DUTY_RATIO;

	//
	// Start the CapTIvate application
	//
	CAPT_appStart();

	//
	// Background Loop
	//
	while(1)
	{
        LED_BLUE_OFF;

	    switch(state) {

            case Active:
            case AddTag:
                // Check CapTouch
                CAPT_appHandler();
                // Only scan NFC every N times for captouch performance
                if (--nfcDuty)
                    break;
                nfcDuty = NFC_DUTY_RATIO;

                nfcStatus = NFC_Find14443A();
                if (nfcStatus == STATUS_SUCCESS) {
                    uidSize = ISO14443A_getUidSize();
                    uid = ISO14443A_getUid();

                    if (state == Active) {
                        if (tagPermitted(uid)) {
                            openDoor();
                        } else {
                            showFail();
                        }
                    } else {
                        storeTag(uid, uidSize);
                    }
                }
                break;
            case Opening:
                // For now, reset back immediately. Will have timer.
                stateActive();
                break;
	    }

		// End of background loop iteration
		// Go to sleep if there is nothing left to do
		CAPT_appSleep();
		
	} // End background loop
} // End main()

void openDoor(void) {
    state = Opening;
    LED_GREEN;

    // Actually open the door!


}

void stateActive(void) {
    state = Active;
    LED_OFF;
}

void showFail(void) {
    LED_RED;
}
