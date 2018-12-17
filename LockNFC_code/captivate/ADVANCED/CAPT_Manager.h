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
// CAPT_Manager.h
//
//! High level sensor management module for init, calibration, and updating.
//
//! The Captivate Manager provides a feature set for
//! running a Captivate application.  Functions are provided for initializing
//! an application, calibrating an application, or updating (measuring,
//! processing, and communicating) and application.
//!
//! The manager layer requires a CAPT_UserConfig file to be included in
//! the build.
//
//! \version 1.70.00.03
//! Released on July 30, 2018
//
//*****************************************************************************
//*****************************************************************************
//! \addtogroup CAPT_Manager
//! @{
//*****************************************************************************

#ifndef CAPT_MANAGER_H_
#define CAPT_MANAGER_H_

//*****************************************************************************
//
//! Initialize a CapTIvate&tm; application (UI).
//
//! This function powers on the CapTIvate&tm; peripheral, initializes it,
//! and sets up the CapTIvate&tm; IO for each sensor.
//! If a communications interface is enabled, it is initialized here as well.
//
//! \param pApp is a pointer to the CapTIvate&tm; application to init.
//!
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_initUI(tCaptivateApplication *pApp);

//*****************************************************************************
//
//! Calibrate a CapTIvate&tm; application (UI).
//
//! This function calls the touch library calibration function on every sensor
//! in the application.
//
//! \param pApp is a pointer to the CapTIvate&tm; application to calibrate.
//!
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_calibrateUI(tCaptivateApplication *pApp);

//*****************************************************************************
//
//! Update a CapTIvate&tm; application (UI).
//
//! This function updates every sensor in the application.  This involves
//! measuring the sensor, processing it, and if communications are enabled,
//! transmitting the output data.
//
//! \param pApp is a pointer to the CapTIvate&tm; application to update.
//!
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_updateUI(tCaptivateApplication *pApp);

//*****************************************************************************
//
//! Return true if any sensor in the UI configuration has a proximity
//! detection.
//!
//! \param pApp is a pointer to the CapTIvate&tm; application to test.
//!
//!  \par Returns
//!		true of prox on any sensor is found, else false.
//
//*****************************************************************************
extern bool CAPT_getGlobalUIProximityStatus(tCaptivateApplication *pApp);


#endif /* CAPT_MANAGER_H_ */
//*****************************************************************************
//
//! Close the doxygen group
//! @}
//
//*****************************************************************************
