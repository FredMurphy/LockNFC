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
// CAPT_Type.h
//
//! CapTIvate&tm; Capacitive Touch Library type definitions.
//
//! \version 1.70.00.03
//! Released on July 30, 2018
//
//*****************************************************************************
//*****************************************************************************
//! \addtogroup CAPT_TYPE
//! @{
//*****************************************************************************
#ifndef __CAPT_TYPE__
#define __CAPT_TYPE__

#ifndef S_SPLINT_S
#include <stdint.h>
#include <stdbool.h>
#endif

#ifndef NULL
#define NULL	(0)
#endif

//*****************************************************************************
//
//! typedef tSensorType
//
//! Specifies the different Capacitive Sensor Implementations available
//! Note: This is defined as a 4 bit field in the structures, limiting the
//! maximum number of sensor types to 16.
//
//*****************************************************************************
enum
{
    //
	//! Single Button or Button Group Sensor
	//! Composed of at least 1 but no more than 256 elements
	//
	eButtonGroup = 0x00,
	
	//
	//! Slider Sensor (1D Sensor) 
	//! Composed of at least 3 but no more than 12 elements
	//
    eSlider = 0x01,
	
	//
	//! Wheel Sensor (1D Sensor) 
	//! Composed of at least 3 but no more than 12 elements
	//! Identical to slider, but with the endpoints connected
	//
    eWheel = 0x02,
	
	//
	//! Track Pad (2D Sensor)
	//! Only supported on specific devices
	//
    eTrackpad = 0x03,
	
	//
	//! Proximity Sensor
	//! Composed of exactly 1 element.
	//! Projected capacitance implementation has special considerations.
	//
    eProx = 0x04
};
typedef uint8_t tSensorType;

//*****************************************************************************
//
//! typedef tSenseTechnology
//!
//! Specifies the different sensing methods available to an element,
//! namely Self or Projected capacitance.
//!
//! NOTE: This fits in a single bit field in the element structure!
//
//*****************************************************************************
enum
{
	//
	//! Self capacitive sensing 
	//! Single-ended electrodes to earth ground, 1 device pin per element
	//
	eSelf = 0x00,
	
	//
	//! Projected capacitive sensing
	//! Measurement between two electrodes, one transmitter and one receiver
	//
	eProjected = 0x01
};
typedef uint8_t tSenseTechnology;

//*****************************************************************************
//
//! typedef tDirectionOfInterest
//!
//! Specifies the direction of interest for a sensor group.  The direction
//! refers to the count value of successive conversions, either increasing (up)
//! or decreasing (down).
//!
//! NOTE: This fits in a single bit field in the element structure!
//
//*****************************************************************************
enum
{
	//
	//! Decreasing Counts
	//
	eDOIDown = 0x00,

	//
	//! Increasing Counts
	//
	eDOIUp = 0x01
};
typedef uint8_t tDirectionOfInterest;

//*****************************************************************************
//
//! typedef tPositionAlgorithm
//
//! Specifies the two different algorithms available for the slider position
//! algorithm.
//
//*****************************************************************************
enum
{
	//
	//! Selection of the vector algorithm
	//
	eVectors = 0x00,
	
	//
	//! Selection of alternative algorithm (not implemented to date)
	//
	eOtherPositionAlg
};
typedef uint8_t tPositionAlgorithm;

//*****************************************************************************
//
//! typedef tFilterOption
//
//! Specifies the two filtered values in an element.
//
//*****************************************************************************
enum
{
	//
	//! Select the filtered count value
	//
	eCount = 0x00,

	//
	//! Select the filtered LTA (long term average) value
	//
	eLTA = 0x01
};
typedef uint8_t tFilterOption;

//*****************************************************************************
//
//! typedef tRawConversionStyle
//
//! Specifies the conversion style to use when performing a raw conversion.
//
//*****************************************************************************
enum
{
	//
	//! One sample is perfomed at the base (default) conversion frequency.
	//
	eStandard = 0x00,

	//
	//! The element is sampled at multiple conversion frequencies,
	//! and the composite raw count is populated via an averaging filter
	//
	eMultiFrequency = 0x01,

	//
	//! The element is sampled at multiple conversion frequencies,
	//! and the largest outlier is removed from the dataset
	//! and the composite raw count is populated via an averaging filter
	//! after the outlier is removed
	//
	eMultiFrequencyWithOutlierRemoval = 0x02,
	
	//
	//! This option is being DEPRECATED for library version 1.10.03.00.
	//! From this version forward, eStandard, eMultiFrequency and
	//! eMultiFrequencyWithOutlierRemoval have error correction built-in
	//! and there is no longer an option to not have error correction.
	//! This means that all max count error conversion that result in a
	//! conversion result of zero will have their conversion result value
	//! set equal to the max count error threshold, rather than to zero.
	//! This improves algorithm performance, and allows for efficient
	//! true max count error detection based on the composite result
	//! value.  Passing eMultiFrequencyWithOutlierRemovalAndErrCorrection
	//! will give the same results as passing eMultiFrequencyWithOutlierRemoval.
	//
	eMultiFrequencyWithOutlierRemovalAndErrCorrection = 0x03,
	
	//
	//! Indicates the number of available conversion styles
	//
	eNrOfConversionStyles
};
typedef uint8_t tRawConversionStyle;

//*****************************************************************************
//
//! typedef tOversamplingStyle
//
//! Specifies the number of oversamples to perform when noise immunity (EMC)
//! mode is enabled.
//
//*****************************************************************************
enum
{
	//
	//! Oversampling is disabled
	//
	eNoOversampling = 0x00,

	//
	//! 2x oversampling is enabled
	//
	e2xOversampling = 0x01,

	//
	//! 4x oversampling is enabled
	//
	e4xOversampling = 0x02,

	//
	//! 8x oversampling is enabled
	//
	e8xOversampling = 0x03,
	
	//
	//! 16x oversampling is enabled
	//
	e16xOversampling = 0x04,
	
	//
	//! 32x oversampling is enabled
	//
	e32xOversampling = 0x05,

	//
	//! The number of different oversampling styles
	//
	eNrOfOversamplingStyles
};
typedef uint8_t tOversamplingStyle;

//*****************************************************************************
//
//! typedef tElementStatusType
//
//! Specifies the different element status flags
//
//*****************************************************************************
enum
{
	//
	//! Touch status flag
	//
	eTouchStatus = 0x00,
	
	//
	//! Prox status flag
	//
	eProxStatus,
	
	//
	//! Negative touch status flag
	//
	eNegativeTouchStatus,

	//
	//! Detect status flag
	//
	eDetectStatus,
	
	//
	//! BIST status flag
	//
	eBISTStatus,
	
	//
	//! Noise status flag
	//
	eNoiseStatus
};
typedef uint8_t tElementStatusType;

//*****************************************************************************
//
//@typedef tXYFilterType
//!
//! Specifies the two different filter beta options available.
//!
//! eStatic - The beta is kept to a fixed value (constant filtering)
//!
//! eDynmaic - The beta is dynamically changed relative to the speed of movement
//! of the XY point
//
//*****************************************************************************
typedef enum
{
	eStatic,
	eDynamic
}
tXYFilterType;

//*****************************************************************************
//
//! \typedef tXYAlgorithm
//!
//! Specifies the two different XY position algorithms implemented.
//!
//! eSingle - Only computes one point, based on a large weighted sum across the
//! whole trackpad (better for large/flat finger inputs)
//!
//! eMulti - Computes multiple position outputs (large/flat inputs could be seen
//! as multiple small inputs)
//
//*****************************************************************************
typedef enum
{
	eSingle,
	eMulti
}
tXYAlgorithm;

//*****************************************************************************
//
//! typedef IQ16_t
//
//! IQ16_t is a fixed-point integer/fractional data type.
//! Common type used mainly for filtered values.  The upper
//! 16bits will be the natural (integer) values, and the lower
//! 16bits will be the decimal section.
//
//*****************************************************************************
typedef union
{
	struct
    {
        //
		//! Lower 16; Decimal Bits
		//
		uint16_t ui16Decimal;
		
		//
		//! Upper 16; Integer Bits
		//
        uint16_t ui16Natural;
    };
	
	//
	//! Full 32 bits
	//
    uint32_t ui32Full;
} IQ16_t;

//*****************************************************************************
//
//! typedef IQ31_t
//
//! IQ31_t is a fixed-point fractional data type that supports the following
//! range and accuracy: MIN=-1; MAX=0.999999999; RES=0.0000000005
//
//*****************************************************************************
typedef int32_t IQ31_t;

//*****************************************************************************
//
//! def _IQ31
//
//! Convert a value into IQ31 format.
//
//*****************************************************************************
#define _IQ31(x)                     (((IQ31_t)((x) * ((IQ31_t)1 << 30))) << 1)

//*****************************************************************************
//
//! typedef tDeBounceSettings
//
//! The de-bounce structure holds de-bounce up/down information, and can be 
//! used for storing de-bounce thresholds or counts.
//
//*****************************************************************************
typedef struct
{
    //
	//! De-bounce into a Touch/Prox State
	//! May hold the threshold or the current de-bounce count
	//
	uint8_t DbIn : 4;
	
    //
	//! De-bounce out of a Touch/Prox State
	//! May hold the threshold or the current de-bounce count
	//
    uint8_t DbOut : 4;
}
tDeBounceSettings;

//*****************************************************************************
//
//! typedef tCaptivateElementTuning
//
//! Every element in the system has at a corresponding element tuning 
//! structure associated with it for each frequency it is measured at.
//! This structure holds the CapTIvate&tm; block tuning configuration for the
//! specific element at a specific conversion frequency.
//
//*****************************************************************************
typedef struct
{
    //
    //! Offset Correction Tap (16 Bit Selection)
    //
    uint16_t ui16OffsetTap;
	
	//
    //! Coarse Gain Ratio (3 Bit Selection)
    //
    uint8_t ui8CoarseGainRatio;

    //
    //! Fine Gain Ratio (5 Bit Selection)
    //
    uint8_t ui8FineGainRatio;
} tCaptivateElementTuning;

//*****************************************************************************
//
//! typedef tElement
//
//! The element structure is used to define the lowest level properties
//! of an element.  All element specific properties are stored in the struct
//! for each element.
//
//*****************************************************************************
typedef struct
{
	//
	//! Holds the current count for this element as a filtered value.
	//! If multi-frequency scanning is enabled, this value represents the
	//! composite of all measurements.
	//
    IQ16_t  filterCount;
	
	//
	//! Holds the long term average for this element as a filtered value.
	//! If multi-frequency scanning is enabled, this value represents the
	//! composite of all measurements.
	//
    IQ16_t  LTA;
	
	//
	//! This pointer links to the array of tuning structures.
	//! Each frequency that this element is scanned at requires a tuning
	//! structure.  The tuning structure contains gain and offset configurations
	//! as defined by the automatic runtime calibration algorithm.
	//
    tCaptivateElementTuning* pTuning;

	//
	//! This is a pointer to an array of raw count values.
	//! each frequency that this element is scanned at requires a place
	//! to store the raw conversion result at that frequency.
	//
    uint16_t* pRawCount;
	
	//
	//! Touch threshold for this element.
	//! Units are specified as 1/128 of the element's LTA.
	//
    uint8_t ui8TouchThreshold;
	
	//
	//! De-Bounce structure that stores the current de-bounce count (in and out)
	//! for this element's proximity status flag.
	//
    tDeBounceSettings ProxDbCounter;
	
	//
	//! De-Bounce structure that stores the current de-bounce count (in and out)
	//! for this element's touch status flag.
	//
    tDeBounceSettings TouchDbCounter;
	
	//
	//! Specifies the Rx pin on the given block that this
	//! element is connected to.
	//
	uint8_t ui8RxPin : 4;
	
	//
	//! Specifies the CapTIvate&tm; block on which the Rx pin resides.
	//
    uint8_t ui8RxBlock : 4;
	
	//
	//! Specifies the Tx pin on the given block that this
	//! element is connected to.  Applies to projected (mutual) cap only.
	//
    uint8_t ui8TxPin : 4;
	
	//
	//! Specifies the CapTIvate&tm; block on which the Rx pin resides.
	//!  Applies to projected (mutual) cap only.
	//
    uint8_t ui8TxBlock : 4;

	//
	//! The noise detected flag indicates that noise was found on the channel.
	//
    bool bNoiseDetected : 1;

	//
	//! The Built-In Self Test (BIST) feature will flag elements here that fail
	//! a built in self test.  This bit may also be used to flag a max count error
	//! at an element level during run time (When a BIST is not running)
	//
    bool bBISTFail :1;
	
	//
	//! Indicates a prox threshold crossing detection in the finite state machine.
	//! This bit is only valid when the FSM is enabled and the detection
	//! results are valid.
	//
    bool bDetect : 1;
	
	//
	//! Proximity status flag.  Indicates when the element is in a prox state.
	//! If the prox de-bounce thresholds are set to 0, then bProx = bDetect.
	//
    bool bProx : 1;
	
	//
	//! Indicates a negative touch threshold crossing detection in the finite state 
	//! machine. This bit is only valid when the FSM is enabled and the detection
	//! results are valid.
	//
    bool bNegativeTouch : 1;
	
	//
	//! Touch status flag.  Indicates when the element is in a touched state.
	//
    bool bTouch : 1;
	
	//
	//! Halt LTA updating immediately on this element specifically
	//
    bool bElementHalt : 1;
	
	//
	//! Trigger a filter reseed on this element specifically
	//
    bool bReseed : 1;
	
	//*************************************************************************
	// NOTE: AT THIS POINT, THE LIBRARY DEVIATES FROM THE ELEMENT STRUCTURE
	// USED FOR THE ROM BUILD.  ALL ITEMS BELOW THIS POINT IN THE ELEMENT
	// STRUCTURE DID NOT EXIST FOR THE ROM BUILD, AND ARE NOT REFERENCED
	// BY ROM FXNS.
	//*************************************************************************

    //
    //! The previous composite raw count for this element.
    //
    uint16_t ui16PrevCompositeRawCount;

    //
    //! The current composite raw count for this element.
    //
    uint16_t ui16CompositeRawCount;

	//
    //! The noise spread observed during a multi-frequency conversion.
    //
    uint16_t ui16NoiseCount;

}
tElement;

//*****************************************************************************
//
//! typedef tCycle
//!
//! The cycle structure contains the information regarding the elements which
//! belong to that specific cycle.  The total active elements in the cycle are
//! stored, and a pointer to each of these elements.
//
//*****************************************************************************
typedef struct
{
    //
	//! Pointer to an array of element pointers that belong to this cycle.
	//! Elements should be ordered in the cycle in accordance with slider/wheel
	//! order, if applicable. One element pointer array must be created for
	//! each cycle.
	//
	tElement** pElements;
	
	//
	//! Number of elements in this cycle.  This must be equal to the size of
	//! the pointer array pointed to by pElements.
	//	
	uint8_t ui8NrOfElements;
}
tCycle;

//*****************************************************************************
//
//! typedef tGenericSensorParams
//!
//! Place holder for pointer to sensor specific parameters.
//! Sensor-specific structures are tied in to the sensor stucture by casting
//! the sensor parameter structure to a generic sensor parameters structure.
//
//*****************************************************************************
typedef struct
{
    //
	//! Generic Value
	//
	uint16_t ui16Value;
	
	//
	//! Generic Parameter
	//
    uint16_t ui16Parameter;
}
tGenericSensorParams;

//*****************************************************************************
//
//! typedef tSensor
//!
//! The generic sensor structure holds the basic properties for a sensor
//
//*****************************************************************************
typedef struct
{
	//
	//! Pointer to a callback function.  If !=NULL, this function
	//! will be called after this sensor is measured.
	//
    void (* pvCallback)();
	
	//
	//! Pointer to an array of cycle pointers.
	//! The cycle pointer array length must be equal to
	//! the value in ui8NrOfCycles.
	//
    const tCycle** pCycle;
	
	//
	//! Pointer to the sensor-specific parameter structure.
	//
    tGenericSensorParams* pSensorParams;
	
	//
	//! Defines the sensor conversion count.  This is the desired
	//! count value for all elements in this sensor.  This establishes
	//! the resolution of the measurement, and is an input to the automatic
	//! calibration algorithm.
	//! Valid values are < 8192.
	//
    uint16_t ui16ConversionGain;
	
	//
	//! Defines the sensor conversion gain.  This value must be less than the  
	//! conversion count above.  Lowering the value increases the amount 
	//! of offset applied to the measurement for each element in this sensor.
	//! This is an input to the automatic calibration algorithm.
	//! Valid values are < 8192.
	//
    uint16_t ui16ConversionCount;
	
	//
	//! Defines the error threshold for the sensor in absolute counts.
	//! A measurement that exceeds this threshold will show a max count error.
	//
    uint16_t ui16ErrorThreshold;
	
	//
	//! Defines the proximity threshold for the sensor relative to each element's
	//! LTA.  This is the detection threshold used by the finite state machine.
	//
    uint16_t ui16ProxThreshold;
	
	//
	//! Defines the negative (reverse) touch threshold for the sensor relative
	//! to each element's LTA.  This threshold allows detection of a touch removal if
	//! a system powers up or re-calibrates while being touched.
	//
    uint16_t ui16NegativeTouchThreshold;
		
	//
	//! Defines the timeout threshold for the sensor, in samples.  If any element
	//! in this sensor is in a touch/prox state for this many samples, the touch/prox
	//! state is cleared and the LTA/Count filters are reset.
	//
    uint16_t ui16TimeoutThreshold;
	
	//
	//! Timeout counter for the sensor.
	//
    uint16_t ui16Timeout;
	
	//
	//! Defines the proximity de-bounce in and out thresholds for the sensor.
	//! Valid values are 0 (off) to 15 samples.
	//
    tDeBounceSettings ProxDbThreshold;
	
	//
	//! Defines the touch de-bounce in and out thresholds for the sensor.
	//! Valid values are 0 (off) to 15 samples.
	//
    tDeBounceSettings TouchDbThreshold;	
	
	//
	//! Defines the number of cycles that are implemented in this sensor.
	//! The maximum number of cycles supported is 32.
	//
    uint8_t ui8NrOfCycles : 5;
	
	//
	//! Defines the conversion clock frequency divider.
	//! There are 8 possible clock dividers from 0 to 7 (Divide by 1
	//! to divide by 128).
	//
    uint8_t ui8FreqDiv : 3;
	
	//
	//! Defines the charge phase length.  There are 16 possible
	//! lengths, with 0 representing 1 conversion clock cycle and 
	//! 15 representing 16 conversion clock cycles.
	//
    uint8_t ui8ChargeLength : 4;
	
	//
	//! Defines the transfer phase length.  There are 16 possible
	//! lengths, with 0 representing 1 conversion clock cycle and 
	//! 15 representing 16 conversion clock cycles.
	//
    uint8_t ui8TransferLength : 4;
	
    //
	//! Defines the type of sensor being defined here (Button Group, Slider,
	//! Wheel, Proximity).  Up to 16 sensor types are supported.
	//
	tSensorType TypeOfSensor : 4;
		
    //
	//! Enables or disables count filtering of elements in this sensor.
	//
    bool bCountFilterEnable : 1;
		
	//
	//! Defines the count filter beta coefficient for this sensor.
	//
    uint8_t ui8CntBeta : 3;
	
	//
	//! Defines the LTA filter beta coefficient for this sensor.
	//
    uint8_t ui8LTABeta : 3;
	
	//
	//! Defines the bias control setting (only applicable in mutual 
	//! capacitance mode). There are four possible bias current levels, 
	//! 0-3, with 0 being lowest power and 3 being highest power.
	//
    uint8_t ui8BiasControl : 2;

    //
    //! Defines the dead time between charge and transfer phases.
    //! There are 5 possible times that can be selected.
    //
	
	//
	//! Defines whether measurements for cycles in this sensor pend
	//! on a input sync event. 0=disabled, 1=rising edge triggered,
	//! 2=falling edge triggered.
	//
    uint8_t ui8InputSyncControl : 2;	
	
	//
	//! Defines the capacitive sensing method to use with this sensor (self
	//! capacitance or projected (mutual) capacitance).
	//
    tSenseTechnology SensingMethod : 1;

    //
    //!  Direction of Interest: Increasing counts or decreasing counts
    //
    tDirectionOfInterest DirectionOfInterest : 1;
	
	//
	//! Indicates that the sensor is currently updating.
	//
    bool bSensorUpdating : 1;
	
	//
	//! Defines the sample capacitor discharge level. 0 indicates 0V,
	//! 1 indicates 0.5V.
	//
    bool bCsDischarge : 1;
		
	//
	//! Defines whether conversion clock modulation is enabled to
	//! reduce radiated emissions.
	//
    bool bModEnable : 1;
	
	//
	//! Defines whether the CapTIvate&tm; analog domain is powered down
	//! after each cycle completes measurement. (CAPCTRL01:CAPLPMCFG)
	//
    bool bLpmControl : 1;
	
	//
	//! Defines whether measurements for cycles in this sensor pend
	//! on a timer event.
	//
    bool bTimerSyncControl : 1;
	
	//
	//! Defines whether the sensor will re-calibrate if an element's LTA
	//! drifts outside of 1/8th of the conversion count specification.
	//
    bool bReCalibrateEnable : 1;
	
	//
	//! Defines whether the pins of the elements in this sensor
	//! are grounded or set to high impedance when not being measured.
	//! 0=High-Z, 1=GND.
	//
    bool bIdleState : 1;	

	//
	//! Immediately halt the LTA of all elements in this sensor.
	//
    bool bSensorHalt : 1;
	
	//
	//! Defines whether to halt the LTA for all elements in this 
	//! sensor if any enter a proximity or touch state.
	//
    bool bPTSensorHalt : 1;
	
	//
	//! Defines whether to halt the LTA of a specific element in this 
	//! sensor if that element enters a proximity or touch state.
	//
    bool bPTElementHalt : 1;
	
	//
	//! Indicates whether any element in the sensor experienced
	//! a detection via the FSM.
	//
    bool bSensorDetect : 1;	
	
	//
	//! Indicates that at least one element in the sensor is
	//! in a proximity state.
	//
    bool bSensorProx : 1;
	
	//
	//! Indicates that at least one element in the sensor is
	//! in a touch state.
	//
    bool bSensorTouch : 1;
	
	//
	//! Indicates whether the previous sample was in a touch state.
	//! This aids in identifying a new touch versus a stale touch.
	//	
    bool bSensorPrevTouch : 1;
	
	//
	//! Indicates whether any element in the sensor experienced
	//! a negative touch (via the FSM).
	//
    bool bSensorNegativeTouch : 1;	
	
	//
	//! Indicates whether any element in this sensor experienced
	//! a max count error (crossing of the ui16ErrorThreshold).
	//		
    bool bMaxCountError : 1;
	
	//
	//! Indicates whether any element in this sensor experienced
	//! an error during runtime calibration.
	//		
    bool bCalibrationError : 1;
	
	//
	//! Indicates whether a counter overflow occured.
	//
    bool bCounterOVF : 1;
	
	//
	//! Indicates whether the sensor is experiencing noise.
	//
    bool bSensorNoiseState : 1;

} tSensor;


//*****************************************************************************
//
//! typedef tButtonSensorParams
//!
//! Button group sensor specific parameters.
//! One instance must be created and tied to every button group sensor.
//
//*****************************************************************************
typedef struct
{

	//
	//! Pointer to an array of sensor pointers that should be activated
	//! as Tx electrodes during the proximity measurement (if in projected 
	//! capacitance mode).
	//
    tSensor** pSensor;
	
	//
	//! Indicates how many sensors are activated as Tx electrodes
	//! during the proximity measurement (if in projected capacitance mode).
	//
	uint8_t ui8NumberOfSensors;

    //
	//! Indicates the dominant element being touched in the button group,
	//! based upon filtered count delta from the LTA.
	//
	uint16_t ui16DominantElement;
	
	//
	//! Indicates the previous dominant element when a new dominant element
	//! is identified.
	//
    uint16_t ui16PrevDominantElement;
}
tButtonSensorParams;

//*****************************************************************************
//
//! typedef tSliderSensorParams
//!
//! Slider/Wheel sensor specific parameters.
//! One instance must be created and tied to every slider or wheel sensor.
//
//*****************************************************************************
typedef struct
{	
	//
	//! Current slider/wheel position stored as a filtered value
	//
	IQ16_t SliderPosition;
	
	//
	//! Specifies the slider/wheel resolution in points
	//
	uint16_t ui16Resolution;
	
	//
	//! Lower slider trim/stretch point (not applicable to wheels)
	//
	uint16_t SliderLower;
	
	//
	//! Upper slider trim/stretch point (not applicable to wheels)
	//	
	uint16_t SliderUpper;
	
	//
	//! Specifies the beta coefficient of the slider/wheel position filter.
	//
	uint8_t SliderBeta;
	
	//
	//! Total elements in slider/wheel sensor (pre-populated)
	//
	uint8_t ui8TotalElements;
	
	//
	//! Position algorithm type (16 possible options)
	//
	tPositionAlgorithm SliderAlgorithm : 4;
	
	//
	//! Slider/wheel position filter enable
	//
	bool SliderFilterEnable : 1;
	
	//
	//! Flag the slider/wheel position filter for an immediate reseed
	//
	bool Reseed : 1;
}
tSliderSensorParams;


/*
 * Trackpad sensor parameters
 */
//*****************************************************************************
//
//! typedef tTrackPadSensorParams
//
//! This structure contains the configuration parameters for the trackpad.
//
//*****************************************************************************
typedef struct
{

//
//! Trackpad Position (Filtered)
//
IQ16_t 		Position_X;
IQ16_t 		Position_Y;

//
//! Pointer to the trackpad sensor processing function.  If !=NULL, this function
//! will be called after this sensor is measured.
//
void (* pvProcessSensor)();

//
//! Pointer to the trackpad sensor gesture processing function.  If !=NULL, this function
//! will be called after this sensor has been processed.
//
void (* pvProcessGesture)();

//
//! pMatrix is a pointer to the element matrix containing address' for each element
//
tElement** pMatrix;

//
//! Pointers to SumX and SumY used for trackpad calculations
uint16_t* pSumX;
uint16_t* pSumY;

//
//! Raw Position
//
uint16_t	ui16Raw_X;
uint16_t	ui16Raw_Y;

//
//! Prev Raw Position (needed for mav filter..can still remove)
//
uint16_t	ui16PrevRaw_X;
uint16_t	ui16PrevRaw_Y;

//
//! Dynamic Beta parameter ui16TopSpeed
//! The speed at which the sensor beta is used
//! CMD 0x63
//
uint16_t	ui16TopSpeed;

//
//! Dynamic Beta parameter ui16BottomSpeed
//! The speed at which the ui8LowerBeta kicks in
//! CMD 0x64
//
uint16_t	ui16BottomSpeed;

//
//! Trackpad Resolution (across x-axis)
//! CMD 0x67
//
uint16_t    ui16Resolution_X;

//
//! Trackpad Resolution (across y-axis)
//! CMD 0x68
//
uint16_t    ui16Resolution_Y;

//
//! Trackpad upper trim (x-axis)
//! CMD 0x6A
//
uint16_t    ui16UpperTrim_X;

//
//! Trackpad lower trim (x-axis)
//! CMD 0x69
//
uint16_t    ui16LowerTrim_X;

//
//! Trackpad upper trim (y-axis)
//! CMD 0x6C
//
uint16_t    ui16UpperTrim_Y;

//
//! Trackpad lower trim (y-axis)
//! CMD 0x6B
//
uint16_t    ui16LowerTrim_Y;

//! TAP SAMPLE THRESHOLD MINIMUM
//! This is minimum time allowed for a valid tap
//! If #samples => MINIMUM then begin gesture
//! If #samples < MINUMUM then ignore
//! CMD 0x70
//
uint16_t    ui16TapTime_Min;


//! TAP SAMPLE THRESHOLD - MAXIMUM
//! This is the maximum time allowed for a tap
//! If #samples < MAX then valid Tap
//! If #sample => MAX then not a TAP
//! CMD = 0x71
//
uint16_t    ui16TapTime_Max;


//! SWIPE SAMPLE THRESHOLD MAXIMUM
//! This is maximum time allowed for a swipe
//! If #samples < MAX then valid swipe
//! If #samples => MAX then not valid swipe
//! CMD 0x72
//
uint16_t    ui16SwipeTime_Max;


//! DOUBLE TAP DELAY THRESHOLD MAX
//! This is the maximum time allowed from the end of the first tap until the start of second tap
//! If #samples < MAX then valid double tap
//! If #samples => MAX then not valid double tap
//! CMD 0x73
//
uint16_t    ui16DoubleTapTime_Max;


//! TAP-HOLD THRESHOLD MIN
//! This is the minimum time allowed for a continuous touch to be a tap-hold
//! If #samples < MIN then not valid tap-hold
//! If #samples => MIN then valid tap-hold
//! CMD 0x74
//
uint16_t    ui16TapHoldTime_Min;


//! TAP_DISTANCE_THRESHOLD = valid 1 Finger press transitions into swipe if motion exceeds this threshold
//! This is the minimum distance (difference between touch position and release position) for a valid swipe
//! If delta < MIN then valid swipe
//! If delta > MAX then not a valid swipe
//! CMD 0x75
//
uint16_t    ui16SwipeDistance_Min;

//
//! Dynamic Beta parameters
//! Lower beta value
//! CMD 0x65
//
uint8_t     ui8LowerBeta;

//
//! Current Gesture
//! Updated during runtime by application
//
uint8_t     ui8Gesture;

//
//! Trackpad size
//! Size is generated by design center
//
uint8_t     ui8TotalColumns;
uint8_t     ui8TotalRows;

//
//! Trackpad XY Filter Beta
//! CMD 0x61
//
uint8_t     ui8TrackPadSensorBeta;

//
//! Trackpad Filter enable
//! CMD 0x60
//
bool        bTrackPadFilterEnable : 1;

//
//! Select TrackPad Beta type (static or dynamic)
//! CMD 0x66
//
bool        bTrackPadFilterType : 1;

//
//! Current touch flag
//
bool        bPresentTouch;

//
//! Enable Gestures
//! Controlled during runtime by application
//
bool        bGestureEnable;

//
//! Reseed Trackpad Filter
//
bool        bReseed;

}tTrackPadSensorParams;

//*****************************************************************************
//
//! typedef tWheelSensorParams
//!
//! Wheel sensor specific parameters.
//! One instance must be created and tied to every wheel sensor.
//! Note that the wheel sensor parameters are identical to the slider sensor's.
//
//*****************************************************************************
typedef tSliderSensorParams tWheelSensorParams;

//*****************************************************************************
//
//! typedef tProxSensorParams
//!
//! Proximity sensor specific parameters.
//! One instance must be created and tied to every proximity sensor.
//
//*****************************************************************************
typedef struct
{
	//
	//! Pointer to an array of sensor pointers that should be activated
	//! as Tx electrodes during the proximity measurement (if in projected 
	//! capacitance mode).
	//
    tSensor** pSensor;
	
	//
	//! Indicates how many sensors are activated as Tx electrodes
	//! during the proximity measurement (if in projected capacitance mode).
	//
	uint8_t ui8NumberOfSensors;
}
tProxSensorParams;

//*****************************************************************************
//
//! typedef tEMCConfig
//
//! This structure contains the configuration parameters for the EMC layer.
//
//*****************************************************************************
typedef struct
{
	//
	//! This is the 'A' coefficient to use when computing the threshold
	//! compensation in self-capacitance mode.
	//
	IQ31_t coeffA;

	//
	//! This is the 'B' coefficient to use when computing the threshold
	//! compensation in self-capacitance mode.
	//
	IQ31_t coeffB;

	//
	//! ui16CalibrationNoiseLimit specifies the maximum peak-to-peak
	//! noise tolerated on a given frequency during the calibration process
	//! after which that frequency will be considered affected by noise and
	//! its calibration values will be considered invalid.
	//
	uint16_t ui16CalibrationNoiseLimit;

	//
	//! ui8CalibrationTestSampleSize specifies size of the sample set
	//! used to determine if noise was present on a given frequency
	//! during calibration.
	//
	uint16_t ui8CalibrationTestSampleSize;

	//
	//! ui8NoiseThreshold specifies the level of noise after which
	//! the noise status bits get set.  The units are specified in
	//! terms of % of the long term average, with 0=0% and 128=100%.
	//
	uint8_t ui8NoiseThreshold;
	
	//
	//! ui8MaxRelThreshAdj specifies the maximum relative threshold adjustment.
	//
	uint8_t ui8MaxRelThreshAdj;
	
	//
	//! ui8NoiseLevelFilterThresh defines a level at which the noise level becomes a
	//! filtered value.
	//
	uint8_t ui8NoiseLevelFilterEntryThresh;
	
	//
	//! ui8NoiseLevelFilterThresh defines a level at which the noise level filter
	//! is disabled.
	//
	uint8_t ui8NoiseLevelFilterExitThresh;

	//
	//! ui8NoiseLevelFilterUp specifies the strength of the filter
	//! applied to new noise values when the new value is larger than the
	//! current value.
	//
	uint8_t ui8NoiseLevelFilterUp : 4;

	//
	//! ui8NoiseLevelFilterDown specifies the strength of the filter
	//! applied to new noise values when the new value is less than the
	//! current value.
	//
	uint8_t ui8NoiseLevelFilterDown : 4;
	
	//
	//! selfModeOversamplingStyle specifies the oversampling style to use
	//! for self conversions when noise immunity is enabled
	//
	tOversamplingStyle selfModeOversamplingStyle : 4;
	
	//
	//! projModeOversamplingStyle specifies the oversampling style to use
	//! for projected (mutual) conversions when noise immunity is enabled
	//
	tOversamplingStyle projModeOversamplingStyle : 4;

	//
	//! bSelfModeFrequencyHoppingEnable enables frequency hopping in
	//! self capacitance mode.
	//
	tRawConversionStyle selfModeConversionStyle : 3;

	//
	//! bProjModeFrequencyHoppingEnable enables frequency hopping in
	//! projected (mutual) capacitance mode.
	//
	tRawConversionStyle projModeConversionStyle : 3;

	//
	//! bJitterFilterEnable controls whether the jitter filter is enabled.
	//
	bool bJitterFilterEnable : 1;

	//
	//! bEnableDynamicThresholdAdjustment
	//! This switch turns on or off the dynamic threshold adjustment.
	//
	bool bEnableDynamicThresholdAdjustment : 1;

} tEMCConfig;

//*****************************************************************************
//
//! typedef tAppState
//
//! The app state enumeration is used by the CapTIvate&tm; application structure
//! to manage the current state of the application (active or autonomous).
//
//*****************************************************************************
enum 
{ 
	//
	//! eUIActive indicates that the UI is the active state
	//
	eUIActive,
	
	//
	//! eUIWakeOnProx indicates that the UI is the autonomous state
	//
	eUIWakeOnProx
};
typedef uint8_t tAppState;

//*****************************************************************************
//
//! typedef tCaptivateApplication
//
//! The application type stores global information about a
//! CapTIvate&tm; application.  This structure is used for passing information to
//! the CapTIvate&tm; manager functions.
//
//*****************************************************************************
typedef struct
{
	//
	//! pSensorList is a pointer to an array of pointers to each sensor,
	//! ordered alphabetically.
	//
	tSensor** pSensorList;
	
	//
	//! ui16ActiveModeScanPeriod specifies the amount of time
	//! in milliseconds between each UI refresh when in active mode.
	//
	uint16_t ui16ActiveModeScanPeriod;
	
	//
	//! ui16WakeOnProxModeScanPeriod specifies the amount of time
	//! in milliseconds between each refresh when in wake-on-prox mode.
	//
	uint16_t ui16WakeOnProxModeScanPeriod;
	
	//
	//! ui16InactivityTimeout specifies the number of samples in a row
	//! with no proximity detections after which to enter wake on prox mode,
	//! if already in active mode.
	//
	uint16_t ui16InactivityTimeout;
	
	//
	//! ui8WakeupInterval applies to wake on proximity mode only.
	//! This field should be populated with CAPT_COUNTER__x values.
	//! It defines after how may autonomous conversions a conversion
	//! counter interrupt is set.  This mechanism can be used to 
	//! periodically wake the UI even if a touch is not detected, 
	//! for the purpose of making sure all other sensors are tracking 
	//! correctly and to maintain their long term averages.
	//
	uint8_t ui8WakeupInterval;
	
	//
	//! ui8NrOfSensors defines the number of sensors in the application
	//
	uint8_t ui8NrOfSensors;

	//
	//! ui8MeasurementLPM defines the low power mode to use in the app.
	//
	uint8_t ui8AppLPM;
	
	//
	//! tAppState controls the state (active or autonomous) of the UI.
	//
	tAppState state;
	
	//
	//! bElementDataTxEnable controls whether element data is allowed to be
	//! sent when CAPT_writeElementData is called.
	//
	bool bElementDataTxEnable : 1;

	//
	//! bSensorDataTxEnable controls whether sensor data is allowed to be
	//! sent when CAPT_writeSensorData is called.
	//
	bool bSensorDataTxEnable : 1;
}
tCaptivateApplication;

#endif
//*****************************************************************************
//! Close the doxygen group
//! @}
//*****************************************************************************
