/*
 * nfc.c
 *
 *  Created on: 19 Nov 2018
 *      Author: 0xFRED
 */
#include "nfc.h"
#include "nfc_app.h"
#include "secrets.h"

#define MAX_TAG_LENGTH 16
#define MAX_TAGS 5

uint8_t validTags[MAX_TAG_LENGTH * MAX_TAGS];

uint8_t fredTag[7] = FRED_TAG_ID;


void checkComms(void)
{
    uint8_t i;
    volatile uint8_t output;

#define REG 0x12

    for(i=0; i< 10; i++)
    {
        TRF79xxA_writeRegister(REG,i);
        __delay_cycles(50);

        output = TRF79xxA_readRegister(REG);
        __delay_cycles(100);
    }
}

void nfcInit(void) {

    // Set the SPI SS high
    SLAVE_SELECT_PORT_SET;
    SLAVE_SELECT_HIGH;

    // Four millisecond delay between bringing SS high and then EN high per TRF7970A Datasheet
    MCU_delayMillisecond(4);

    // Set TRF Enable Pin high
    TRF_ENABLE_SET;
    TRF_ENABLE;

    // Wait until TRF system clock started
    MCU_delayMillisecond(5);


    // Set up TRF initial settings
    TRF79xxA_initialSettings();
    TRF79xxA_setTrfPowerSetting(TRF79xxA_3V_FULL_POWER);
    NFC_init();
    IRQ_ON;

    checkComms();

    clearTags();
    storeTag(fredTag, ISO14443A_UID_DOUBLE);
    storeTag(fredTag, ISO14443A_UID_DOUBLE);
}



bool tagPermitted(uint8_t * tagId) {

    uint8_t i;
    for (i=0; i < MAX_TAGS * MAX_TAG_LENGTH; i+=MAX_TAG_LENGTH) {
        // End of list
        if (validTags[i] == 0)
            return false;

        if (memcmp(tagId, validTags+i+1, validTags[i]) == 0)
            return true;
    }

    return false;

}

// Store tag in next available slot.
// return 1 if successful
bool storeTag(uint8_t * tagId, tISO14443A_UidSize uidSize) {

    uint8_t i,j;
    for (i=0; i < MAX_TAGS * MAX_TAG_LENGTH; i+=MAX_TAG_LENGTH) {
        // Store here?
        if (validTags[i] == 0) {
            validTags[i] = uidSize;
            for (j=0; j<uidSize; j++) {
                validTags[i+j+1] = tagId[j];
            }
            validTags[i+j+1]=0;
            return true;
        }
    }

    return false;
}

void clearTags(void) {

    uint8_t i;
    for (i=0; i < MAX_TAGS * MAX_TAG_LENGTH; i++) {
        validTags[i] = 0;
    }

}
