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
// CAPT_Trackpad.h
//
//! This file contains higher-level sensor processing APIs for trackpad sensor
//
//! \version 1.70.00.03
//! Released on July 30, 2018
//
//*****************************************************************************
//*****************************************************************************
//! \addtogroup CAPT_Trackpad
//! @{
//*****************************************************************************
#ifndef CAPT_TRACKPAD__
#define CAPT_TRACKPAD__

#include "CAPT_Touch.h"

//*****************************************************************************
//
//! Perform Trackpad processing
//!
//! Does all TrackPad related processing: Position, Track, Filter
//! User can override with custom processing.
//! Refer to touch:CAPT_registerTrackPadSensorProcessing() in touch.c
//!
//! \param pSensor is a pointer to the TrackPad Sensor to process
//!
//! \return None.
//
//*****************************************************************************
extern void CAPT_processTrackPadSensor(tSensor*);


//*****************************************************************************
//
//! Process the track/gesture pad gestures
//
//! This function applies gesture algorithms to the results of trackpad processing.
//! User can override with custom gesture processing.
//! Refer to touch:CAPT_registerTrackPadGestureProcessing() in touch.c
//
//! \param pSensor is a pointer to the sensor to query
//! \par Returns
//!	    None
//
//*****************************************************************************
extern void CAPT_processTrackPadGesture(tSensor *pTrackpad);


//*****************************************************************************
//
//! Send trackpad position and gesture
//
//! This function sends trackpad position and gesture data using trackpad protocol to the GUI.
//
//! \param None - Trackpad sensor ID is determined during Trackpad Interface Initialization
//! \par Returns
//!	    None
//
//*****************************************************************************
extern bool CAPT_writeTrackPadData(uint8_t ui8SensorID);


//*****************************************************************************
//! Close the doxygen group
//! @}
//*****************************************************************************

#endif
