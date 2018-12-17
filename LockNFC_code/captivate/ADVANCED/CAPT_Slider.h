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
// CAPT_Slider.h
//
//! High level slider and wheel processing module.
//
//! Slider processing APIs apply to sliders and wheels.  Sliders
//! and wheels share sensor structures (tSlider).  A wheel is identical to a
//! slider, except its filtering algorithm allows wrap-around on the endpoints.
//
//! \version 1.70.00.03
//! Released on July 30, 2018
//
//*****************************************************************************
//*****************************************************************************
//
//! \addtogroup CAPT_Slider
//! @{
//
//*****************************************************************************

#ifndef CAPT_Sliders_H_
#define CAPT_Sliders_H_

#include "CAPT_Touch.h"

//*****************************************************************************
//
//! Trigonometric Arctan approximation
//!
//! Perform an arctan(YComp/XComp) approximation using a linear approximation
//! with basic error correction, to give max error of +- 1 degree.  A full
//! 0 to 360 degree output range is achieved.
//!
//! \param i32XComp, i32YComp are the X and Y vectors
//!
//!  \par Returns
//!		approximated arctan(Y/X) value (0 to 360 degrees mapped from 0 to 65535)
//
//*****************************************************************************
extern uint16_t CAPT_computeArcTanApprox(int32_t i32XComp, int32_t i32YComp);


//*****************************************************************************
//
//! Calculate Slider Position
//!
//! Slider position is calculated using a vector sum method.
//!
//! \param pSlider is a pointer to the Slider Sensor to process
//!
//!  \par Returns
//!		Slider position
//
//*****************************************************************************
extern uint16_t CAPT_computeSliderVectors(tSensor *pSlider);


//*****************************************************************************
//
//! Test for a wrap on slider / wheel
//!
//! With the slider/wheel functionality working in a 0-360 degree vector plane,
//! a value must always be checked if it has not wrapped, and thus must be kept
//! between 0 and 360.
//!
//! \param i16Position is the slider/wheel position to check for wrapping
//! \param ui16MaxPosition is the wrapping value (relating to 360degrees)
//!
//!  \par Returns
//!		the adjusted position to fit in 0 to slider/wheel resolution
//
//*****************************************************************************
extern uint16_t CAPT_computeWheelWrap(int16_t i16Position, uint16_t ui16MaxPosition);


//*****************************************************************************
//
//! Perform processing for a Slider
//!
//! Here processing is performed on a slider sensor implementation.
//! This includes calculating the slider output position and filtering of this
//! position.
//!
//! \param pSlider is a pointer to the Slider Sensor to process
//!
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void CAPT_processSlider(tSensor *pSlider);


//*****************************************************************************
//
//! Get the position value for a slider or wheel sensor.
//
//! This function provides easy access to the slider or wheel position value.
//
//! \param pSensor is a pointer to the sensor to query
//! \par Returns
//!	    The current slider position if touched, else 0xFFFF.
//
//*****************************************************************************
extern uint16_t CAPT_getSensorPosition(tSensor *pSensor);

#endif /* CAPT_Sliders_H_ */
//*****************************************************************************
//
//! Close the doxygen group
//! @}
//
//*****************************************************************************
