/*
 * CapTouch.c
 *
 *  Created on: 30 Oct 2018
 *      Author: 0xFRED
 */

#include "captouch.h"
#include "CAPT_BSP.h"
#include "main.h"
#include "mcu.h"
#include "secrets.h"

extern tButtonSensorParams numericKeypad_Params;

#define MAX_LENGTH 16
#define MAX_CODES 3

uint8_t entry[MAX_LENGTH] = {0};

// initialize codes
uint8_t codes[MAX_CODES][MAX_LENGTH] = {ADAM_PASSCODE_REVERSED, DANIEL_PASSCODE_REVERSED};

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

    uint8_t c;
    for (c = 0; c < MAX_CODES; c++) {

        // End of the list
        if (codes[c][0] == 0)
            return false;

        // Compare the (reversed) codes
        for (i = 0; i < MAX_LENGTH; i++) {
            if (codes[c][i] == 0)
                return true;
            if (codes[c][i] != entry[i])
                break;
        }
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
