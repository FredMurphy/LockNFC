/*
 * main.h
 *
 *  Created on: 17 Dec 2018
 *      Author: fred2
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "captouch.h"
#include <msp430.h>                      // Generic MSP430 Device Include
#include "driverlib.h"                   // MSPWare Driver Library
#include "captivate.h"                   // CapTIvate Touch Software Library
#include "CAPT_App.h"                    // CapTIvate Application Code
#include "CAPT_BSP.h"                    // CapTIvate EVM Board Support Package
#include "nfc.h"
#include "nfc_app.h"

void stateActive(void);
void openDoor(void);
void showFail(void);


#endif /* MAIN_H_ */
