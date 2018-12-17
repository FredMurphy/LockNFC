/*
 * nfc.h
 *
 *  Created on: 19 Nov 2018
 *      Author: fred2
 */

#ifndef HARDWARE_NFC_H_
#define HARDWARE_NFC_H_

#include "stdint.h"
#include "stdbool.h"
#include "string.h"
#include "iso14443a.h"

void checkComms(void);
void nfcInit(void);
bool tagPermitted(uint8_t * tagId);
void clearTags(void);
bool storeTag(uint8_t * tagId, tISO14443A_UidSize uidSize);

#endif /* HARDWARE_NFC_H_ */
