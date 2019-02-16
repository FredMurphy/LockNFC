/*
 * LockNFC
 *
 * A combination of:
 *   NFC reader tuned for implanted tags
 *   Capacitive touch keypad
 *
 *  Created on: 2019
 *      Author: 0xFRED
 *
 */

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

    initTimeout();

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
                // For now, do nothing until timer expires
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
    DOOR_SINGLE_ON;
    startTimeout(3);


}

void stateActive(void) {
    state = Active;
    LED_OFF;
    DOOR_OFF;
}

void showFail(void) {
    LED_RED;
}
