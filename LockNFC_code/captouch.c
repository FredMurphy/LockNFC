/*
 * CapTouch.c
 *
 *  Created on: 30 Oct 2018
 *      Author: fred
 */

#include "captouch.h"
#include "CAPT_BSP.h"
#include "main.h"
#include "mcu.h"

extern tButtonSensorParams numericKeypad_Params;

#define MAX_LENGTH 16
uint8_t entry[MAX_LENGTH] = {0};
uint8_t passcodeReversed[] = "654321\0";

uint8_t keys[] = "123456789*0#";

volatile uint16_t button;
volatile uint8_t key;


void capTouchInit() {

    MAP_CAPT_registerCallback(
        &numericKeypad,
        &numericKeypadHandler
    );

}

bool addKeyPressAndCompare(uint8_t key) {

    uint16_t i;
    // Add key press to front of entry
    for (i = MAX_LENGTH-1; i >0; i--)
        entry[i] = entry[i-1];
    entry[0] = key;

    // Compare the (reversed) codes
    for (i = 0; i < MAX_LENGTH; i++) {
        if (passcodeReversed[i] == 0)
            return true;
        if (entry[i] != passcodeReversed[i])
            return false;
    }
    return false;

}
void numericKeypadHandler(tSensor* pSensor) {


    if(numericKeypad.bSensorTouch && !numericKeypad.bSensorPrevTouch )
    {
        LED_BLUE_ON;
        button = numericKeypad_Params.ui16DominantElement;
        if (addKeyPressAndCompare(keys[button])) {
            openDoor();

        }
    }
}
