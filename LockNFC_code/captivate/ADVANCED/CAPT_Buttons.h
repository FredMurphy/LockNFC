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
// CAPT_Buttons.h
//
//! High level button group processing module.
//
//! \version 1.70.00.03
//! Released on July 30, 2018
//
//*****************************************************************************
//*****************************************************************************
//! \addtogroup CAPT_Buttons
//! @{
//*****************************************************************************

#ifndef CAPT_Buttons_H_
#define CAPT_Buttons_H_

#include "CAPT_Touch.h"

//*****************************************************************************
//
//! This API performs processing for a button group.
//
//! This sensor-level API identifies the button within a button group that has
//! the largest delta.  The output of this API is an integer indicating the
//! button that is being pressed the most (based upon a delta comparison).
//! This output is stored in the ui16DominantElement parameter of the
//! tButtonGroup sensor being pointed to.
//
//! The mapping between integer output and element is based upon the order of
//! the elements and cycles within the sensor.
//
//! \param pButtonGroup is a pointer to the button group to process
//! \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_processButtons(tSensor *pButtonGroup);

//*****************************************************************************
//
//! Get the ID of the dominant element.
//
//! This function provides easy access to the sensor's dominant element ID.
//
//! \param pSensor is a pointer to the sensor to query
//! \par Returns
//!	    The dominant element, regardless of whether a touch is present.
//
//*****************************************************************************
extern uint8_t CAPT_getDominantButton(tSensor *pButtonGroup);

//*****************************************************************************
//
//! Get the address of the dominant element.
//
//! This function provides easy access to the sensor's dominant element by
//! means of it's address.
//
//! \param pSensor is a pointer to the sensor to query
//! \par Returns
//!	    The address of the dominant element
//!     regardless of whether a touch is present.
//
//*****************************************************************************
extern tElement* CAPT_getDominantButtonAddr(tSensor *pButtonGroup);

#endif /* CAPT_Buttons_H_ */
//*****************************************************************************
//! Close the doxygen group
//! @}
//*****************************************************************************
