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
// CAPT_App.h
//
//! The application layer handles UI sample timing and whether the application
//! is in active mode or wake-on-proximity mode.
//
//! \version 1.70.00.03
//! Released on July 30, 2018
//
//*****************************************************************************

#ifndef CAPT_APP_H_
#define CAPT_APP_H_

//*****************************************************************************
//
// CAPT_appStart() initilizes and calibrates the user interface application
// specified in CAPT_UserConfig.  It also starts the captivate timer.
//
// \param none
// \return none
//
//*****************************************************************************
extern void CAPT_appStart(void);

//*****************************************************************************
//
// CAPT_appHandler() performs several functions:
//  (1) It manages the mode of the UI (Active versus Wake-on-Proximity)
//  (2) It controls when sensors are measured
//  (2) It handles timer requests via the flags set by the captivate ISR
//  (3) It checks for incoming packets, if the communications stack is enabled
//
// \param none
// \return none
//
//*****************************************************************************
extern bool CAPT_appHandler(void);

//*****************************************************************************
//
// CAPT_appSleep() puts the MCU into the low power mode specified in the 
// global applicaiton structure, if and ONLY if no pending captivate flags
// exist.
//
// The flags that are checked are: detection, timer, and conversion counter.
//
// \param none
// \return none
//
//*****************************************************************************
extern void CAPT_appSleep(void);

#endif /* CAPT_APP_H_ */
