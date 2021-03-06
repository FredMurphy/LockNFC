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


// Generated by Captivate Design Center v1_70_00_03 on Sun Nov 11 19:21:29 GMT 2018


//*****************************************************************************
// CAPT_UserConfig.c
//
// \version 1.70.00.03
// Released on July 30, 2018
//
//*****************************************************************************

//*****************************************************************************
//
// NOTE: This is an automatically generated source code file!  The Captivate
// Design Center generates the User Configuration file automatically based
// upon the sensor layout that was created.
//
// Changes to this file will be OVERWRITTEN if a you select
// "Update Existing Project" under "Generate Source Code" in the Design Center.
//
// To avoid interference with the code generation process, keep ALL application
// code external to this file.
//
//*****************************************************************************

#include "CAPT_UserConfig.h"

//*****************************************************************************
//
//! Captivate Element Definitions
//! All elements in this application are defined below.
//! Each element has 3 components:
//!  1) a raw count array (One index per freq. scanned) (uint16_t)
//!  2) a tuning array (One index per freq. scanned) (tCaptivateElementTuning)
//!  3) a element structure (tElement)
//
//*****************************************************************************
// Sensor: numericKeypad, Element: E00
uint16_t numericKeypad_E00_RawCnts[CAPT_MUTUAL_FREQ_CNT];
tCaptivateElementTuning numericKeypad_E00_Tuning[CAPT_MUTUAL_FREQ_CNT];
tElement numericKeypad_E00 =
{
    .ui8TxPin = 0,
    .ui8TxBlock = 2,
    .ui8RxPin = 1,
    .ui8RxBlock = 0,
    .ui8TouchThreshold = 15,
    .pRawCount = numericKeypad_E00_RawCnts,
    .pTuning = numericKeypad_E00_Tuning,
};

// Sensor: numericKeypad, Element: E01
uint16_t numericKeypad_E01_RawCnts[CAPT_MUTUAL_FREQ_CNT];
tCaptivateElementTuning numericKeypad_E01_Tuning[CAPT_MUTUAL_FREQ_CNT];
tElement numericKeypad_E01 =
{
    .ui8TxPin = 0,
    .ui8TxBlock = 2,
    .ui8RxPin = 2,
    .ui8RxBlock = 0,
    .ui8TouchThreshold = 10,
    .pRawCount = numericKeypad_E01_RawCnts,
    .pTuning = numericKeypad_E01_Tuning,
};

// Sensor: numericKeypad, Element: E02
uint16_t numericKeypad_E02_RawCnts[CAPT_MUTUAL_FREQ_CNT];
tCaptivateElementTuning numericKeypad_E02_Tuning[CAPT_MUTUAL_FREQ_CNT];
tElement numericKeypad_E02 =
{
    .ui8TxPin = 0,
    .ui8TxBlock = 2,
    .ui8RxPin = 3,
    .ui8RxBlock = 0,
    .ui8TouchThreshold = 10,
    .pRawCount = numericKeypad_E02_RawCnts,
    .pTuning = numericKeypad_E02_Tuning,
};

// Sensor: numericKeypad, Element: E03
uint16_t numericKeypad_E03_RawCnts[CAPT_MUTUAL_FREQ_CNT];
tCaptivateElementTuning numericKeypad_E03_Tuning[CAPT_MUTUAL_FREQ_CNT];
tElement numericKeypad_E03 =
{
    .ui8TxPin = 1,
    .ui8TxBlock = 2,
    .ui8RxPin = 1,
    .ui8RxBlock = 0,
    .ui8TouchThreshold = 10,
    .pRawCount = numericKeypad_E03_RawCnts,
    .pTuning = numericKeypad_E03_Tuning,
};

// Sensor: numericKeypad, Element: E04
uint16_t numericKeypad_E04_RawCnts[CAPT_MUTUAL_FREQ_CNT];
tCaptivateElementTuning numericKeypad_E04_Tuning[CAPT_MUTUAL_FREQ_CNT];
tElement numericKeypad_E04 =
{
    .ui8TxPin = 1,
    .ui8TxBlock = 2,
    .ui8RxPin = 2,
    .ui8RxBlock = 0,
    .ui8TouchThreshold = 10,
    .pRawCount = numericKeypad_E04_RawCnts,
    .pTuning = numericKeypad_E04_Tuning,
};

// Sensor: numericKeypad, Element: E05
uint16_t numericKeypad_E05_RawCnts[CAPT_MUTUAL_FREQ_CNT];
tCaptivateElementTuning numericKeypad_E05_Tuning[CAPT_MUTUAL_FREQ_CNT];
tElement numericKeypad_E05 =
{
    .ui8TxPin = 1,
    .ui8TxBlock = 2,
    .ui8RxPin = 3,
    .ui8RxBlock = 0,
    .ui8TouchThreshold = 10,
    .pRawCount = numericKeypad_E05_RawCnts,
    .pTuning = numericKeypad_E05_Tuning,
};

// Sensor: numericKeypad, Element: E06
uint16_t numericKeypad_E06_RawCnts[CAPT_MUTUAL_FREQ_CNT];
tCaptivateElementTuning numericKeypad_E06_Tuning[CAPT_MUTUAL_FREQ_CNT];
tElement numericKeypad_E06 =
{
    .ui8TxPin = 2,
    .ui8TxBlock = 2,
    .ui8RxPin = 1,
    .ui8RxBlock = 0,
    .ui8TouchThreshold = 10,
    .pRawCount = numericKeypad_E06_RawCnts,
    .pTuning = numericKeypad_E06_Tuning,
};

// Sensor: numericKeypad, Element: E07
uint16_t numericKeypad_E07_RawCnts[CAPT_MUTUAL_FREQ_CNT];
tCaptivateElementTuning numericKeypad_E07_Tuning[CAPT_MUTUAL_FREQ_CNT];
tElement numericKeypad_E07 =
{
    .ui8TxPin = 2,
    .ui8TxBlock = 2,
    .ui8RxPin = 2,
    .ui8RxBlock = 0,
    .ui8TouchThreshold = 10,
    .pRawCount = numericKeypad_E07_RawCnts,
    .pTuning = numericKeypad_E07_Tuning,
};

// Sensor: numericKeypad, Element: E08
uint16_t numericKeypad_E08_RawCnts[CAPT_MUTUAL_FREQ_CNT];
tCaptivateElementTuning numericKeypad_E08_Tuning[CAPT_MUTUAL_FREQ_CNT];
tElement numericKeypad_E08 =
{
    .ui8TxPin = 2,
    .ui8TxBlock = 2,
    .ui8RxPin = 3,
    .ui8RxBlock = 0,
    .ui8TouchThreshold = 10,
    .pRawCount = numericKeypad_E08_RawCnts,
    .pTuning = numericKeypad_E08_Tuning,
};

// Sensor: numericKeypad, Element: E09
uint16_t numericKeypad_E09_RawCnts[CAPT_MUTUAL_FREQ_CNT];
tCaptivateElementTuning numericKeypad_E09_Tuning[CAPT_MUTUAL_FREQ_CNT];
tElement numericKeypad_E09 =
{
    .ui8TxPin = 3,
    .ui8TxBlock = 2,
    .ui8RxPin = 1,
    .ui8RxBlock = 0,
    .ui8TouchThreshold = 10,
    .pRawCount = numericKeypad_E09_RawCnts,
    .pTuning = numericKeypad_E09_Tuning,
};

// Sensor: numericKeypad, Element: E10
uint16_t numericKeypad_E10_RawCnts[CAPT_MUTUAL_FREQ_CNT];
tCaptivateElementTuning numericKeypad_E10_Tuning[CAPT_MUTUAL_FREQ_CNT];
tElement numericKeypad_E10 =
{
    .ui8TxPin = 3,
    .ui8TxBlock = 2,
    .ui8RxPin = 2,
    .ui8RxBlock = 0,
    .ui8TouchThreshold = 10,
    .pRawCount = numericKeypad_E10_RawCnts,
    .pTuning = numericKeypad_E10_Tuning,
};

// Sensor: numericKeypad, Element: E11
uint16_t numericKeypad_E11_RawCnts[CAPT_MUTUAL_FREQ_CNT];
tCaptivateElementTuning numericKeypad_E11_Tuning[CAPT_MUTUAL_FREQ_CNT];
tElement numericKeypad_E11 =
{
    .ui8TxPin = 3,
    .ui8TxBlock = 2,
    .ui8RxPin = 3,
    .ui8RxBlock = 0,
    .ui8TouchThreshold = 10,
    .pRawCount = numericKeypad_E11_RawCnts,
    .pTuning = numericKeypad_E11_Tuning,
};

// Sensor: proximityAndGuard, Element: E00
uint16_t proximityAndGuard_E00_RawCnts[CAPT_SELF_FREQ_CNT];
tCaptivateElementTuning proximityAndGuard_E00_Tuning[CAPT_SELF_FREQ_CNT];
tElement proximityAndGuard_E00 =
{
    .ui8RxPin = 0,
    .ui8RxBlock = 3,
    .ui8TouchThreshold = 5,
    .pRawCount = proximityAndGuard_E00_RawCnts,
    .pTuning = proximityAndGuard_E00_Tuning,
};


//*****************************************************************************
//
//! Captivate Time Cycle Definitions
//! All time cycles in this application are defined below.  Time cycles are
//! groups of elements that are measured together in parallel in one time slot.
//! Each cycle has 2 components:
//!  1) an element pointer array to the member elements (tElement*)
//!  2) a cycle structure (tCycle)
//
//*****************************************************************************
// Time Cycle: numericKeypad_C00
tElement* numericKeypad_C00_Elements[1] =
{
    &numericKeypad_E00,
};
tCycle numericKeypad_C00 =
{
    .ui8NrOfElements = 1,
    .pElements = numericKeypad_C00_Elements,
};

// Time Cycle: numericKeypad_C01
tElement* numericKeypad_C01_Elements[1] =
{
    &numericKeypad_E01,
};
tCycle numericKeypad_C01 =
{
    .ui8NrOfElements = 1,
    .pElements = numericKeypad_C01_Elements,
};

// Time Cycle: numericKeypad_C02
tElement* numericKeypad_C02_Elements[1] =
{
    &numericKeypad_E02,
};
tCycle numericKeypad_C02 =
{
    .ui8NrOfElements = 1,
    .pElements = numericKeypad_C02_Elements,
};

// Time Cycle: numericKeypad_C03
tElement* numericKeypad_C03_Elements[1] =
{
    &numericKeypad_E03,
};
tCycle numericKeypad_C03 =
{
    .ui8NrOfElements = 1,
    .pElements = numericKeypad_C03_Elements,
};

// Time Cycle: numericKeypad_C04
tElement* numericKeypad_C04_Elements[1] =
{
    &numericKeypad_E04,
};
tCycle numericKeypad_C04 =
{
    .ui8NrOfElements = 1,
    .pElements = numericKeypad_C04_Elements,
};

// Time Cycle: numericKeypad_C05
tElement* numericKeypad_C05_Elements[1] =
{
    &numericKeypad_E05,
};
tCycle numericKeypad_C05 =
{
    .ui8NrOfElements = 1,
    .pElements = numericKeypad_C05_Elements,
};

// Time Cycle: numericKeypad_C06
tElement* numericKeypad_C06_Elements[1] =
{
    &numericKeypad_E06,
};
tCycle numericKeypad_C06 =
{
    .ui8NrOfElements = 1,
    .pElements = numericKeypad_C06_Elements,
};

// Time Cycle: numericKeypad_C07
tElement* numericKeypad_C07_Elements[1] =
{
    &numericKeypad_E07,
};
tCycle numericKeypad_C07 =
{
    .ui8NrOfElements = 1,
    .pElements = numericKeypad_C07_Elements,
};

// Time Cycle: numericKeypad_C08
tElement* numericKeypad_C08_Elements[1] =
{
    &numericKeypad_E08,
};
tCycle numericKeypad_C08 =
{
    .ui8NrOfElements = 1,
    .pElements = numericKeypad_C08_Elements,
};

// Time Cycle: numericKeypad_C09
tElement* numericKeypad_C09_Elements[1] =
{
    &numericKeypad_E09,
};
tCycle numericKeypad_C09 =
{
    .ui8NrOfElements = 1,
    .pElements = numericKeypad_C09_Elements,
};

// Time Cycle: numericKeypad_C10
tElement* numericKeypad_C10_Elements[1] =
{
    &numericKeypad_E10,
};
tCycle numericKeypad_C10 =
{
    .ui8NrOfElements = 1,
    .pElements = numericKeypad_C10_Elements,
};

// Time Cycle: numericKeypad_C11
tElement* numericKeypad_C11_Elements[1] =
{
    &numericKeypad_E11,
};
tCycle numericKeypad_C11 =
{
    .ui8NrOfElements = 1,
    .pElements = numericKeypad_C11_Elements,
};

// Time Cycle: proximityAndGuard_C00
tElement* proximityAndGuard_C00_Elements[1] =
{
    &proximityAndGuard_E00,
};
tCycle proximityAndGuard_C00 =
{
    .ui8NrOfElements = 1,
    .pElements = proximityAndGuard_C00_Elements,
};


//*****************************************************************************
//
//! Captivate Sensor Definitions
//! All sensors in this application are defined below.  Sensors are
//! groups of time cycles that utilize raw measurement data to create an
//! abstract sensor type, such as a button, slider, wheel, or prox sensor.
//! Each sensor has 3 components:
//!  1) a cycle pointer array to the member time cycles (tCycle*)
//!  2) a sensor-specific parameter structure (tGenericSensorParams)
//!  3) a sensor structure (tSensor)
//
//*****************************************************************************
//Sensor: numericKeypad
const tCycle* numericKeypad_Cycles[12] =
{
    &numericKeypad_C00,
    &numericKeypad_C01,
    &numericKeypad_C02,
    &numericKeypad_C03,
    &numericKeypad_C04,
    &numericKeypad_C05,
    &numericKeypad_C06,
    &numericKeypad_C07,
    &numericKeypad_C08,
    &numericKeypad_C09,
    &numericKeypad_C10,
    &numericKeypad_C11,
};

tButtonSensorParams numericKeypad_Params;
tSensor numericKeypad =
{
    // Basic Properties
    .TypeOfSensor = eButtonGroup,
    .SensingMethod = eProjected,
    .DirectionOfInterest = eDOIUp,
    .pvCallback = NULL,
    .ui8NrOfCycles = 12,
    .pCycle = numericKeypad_Cycles,
    .pSensorParams = (tGenericSensorParams*)&numericKeypad_Params,
    // Conversion Control Parameters
    .ui16ConversionCount = 150,
    .ui16ConversionGain = 100,
    .ui8FreqDiv = 1,
    .ui8ChargeLength = 0,
    .ui8TransferLength = 0,
    .bModEnable = false,
    .ui8BiasControl = 3,
    .bCsDischarge = true,
    .bLpmControl = false,
    .ui8InputSyncControl = 0,
    .bTimerSyncControl = false,
    .bIdleState = true,
    // Tuning  Parameters
    .ui16ProxThreshold = 7,
    .ui16NegativeTouchThreshold = 20,
    .ui16ErrorThreshold = 8191,
    .ui16TimeoutThreshold = 65535,
    .ProxDbThreshold.DbIn = 1,
    .ProxDbThreshold.DbOut = 0,
    .TouchDbThreshold.DbIn = 1,
    .TouchDbThreshold.DbOut = 0,
    .bCountFilterEnable = true,
    .ui8CntBeta = 1,
    .bSensorHalt = false,
    .bPTSensorHalt = true,
    .bPTElementHalt = true,
    .ui8LTABeta = 7,
    .bReCalibrateEnable = true,
};

//Sensor: proximityAndGuard
const tCycle* proximityAndGuard_Cycles[1] =
{
    &proximityAndGuard_C00,
};

tProxSensorParams proximityAndGuard_Params =
{
    .pSensor = NULL,
    .ui8NumberOfSensors = 0,
};

tSensor proximityAndGuard =
{
    // Basic Properties
    .TypeOfSensor = eProx,
    .SensingMethod = eSelf,
    .DirectionOfInterest = eDOIDown,
    .pvCallback = NULL,
    .ui8NrOfCycles = 1,
    .pCycle = proximityAndGuard_Cycles,
    .pSensorParams = (tGenericSensorParams*)&proximityAndGuard_Params,
    // Conversion Control Parameters
    .ui16ConversionCount = 800,
    .ui16ConversionGain = 100,
    .ui8FreqDiv = 3,
    .ui8ChargeLength = 0,
    .ui8TransferLength = 0,
    .bModEnable = false,
    .ui8BiasControl = 3,
    .bCsDischarge = true,
    .bLpmControl = false,
    .ui8InputSyncControl = 0,
    .bTimerSyncControl = false,
    .bIdleState = true,
    // Tuning  Parameters
    .ui16ProxThreshold = 10,
    .ui16NegativeTouchThreshold = 20,
    .ui16ErrorThreshold = 8191,
    .ui16TimeoutThreshold = 65535,
    .ProxDbThreshold.DbIn = 1,
    .ProxDbThreshold.DbOut = 0,
    .TouchDbThreshold.DbIn = 1,
    .TouchDbThreshold.DbOut = 0,
    .bCountFilterEnable = true,
    .ui8CntBeta = 1,
    .bSensorHalt = false,
    .bPTSensorHalt = true,
    .bPTElementHalt = true,
    .ui8LTABeta = 7,
    .bReCalibrateEnable = true,
};


#if (CAPT_CONDUCTED_NOISE_IMMUNITY_ENABLE==true)
//*****************************************************************************
//
//! \var g_EMCConfig
//! This structure stores the EMC configuration for this application.
//
//*****************************************************************************
const tEMCConfig g_EMCConfig =
{
	// Conversion Style
	.selfModeConversionStyle = eMultiFrequency,
	.projModeConversionStyle = eMultiFrequencyWithOutlierRemoval,
	
	// Oversampling Style
	.selfModeOversamplingStyle = eNoOversampling,
	.projModeOversamplingStyle = eNoOversampling,
	
	// Jitter Filter Enable
	.bJitterFilterEnable = true,
	
	// Noise Thresholds and Calibration Noise Limits
	.ui8NoiseThreshold = 20,
	.ui16CalibrationNoiseLimit = 10,
	.ui8CalibrationTestSampleSize = 8,
		
	// Dynamic Threshold Adjustment Parameters
	.bEnableDynamicThresholdAdjustment = true,
	.ui8MaxRelThreshAdj = 76,
	.ui8NoiseLevelFilterEntryThresh = 40,
	.ui8NoiseLevelFilterExitThresh = 0,
	.ui8NoiseLevelFilterDown = 6,
	.ui8NoiseLevelFilterUp = 1,
	.coeffA = _IQ31(0.0065),
	.coeffB = _IQ31(0.050)
};
#endif

//*****************************************************************************
//
//! \var g_pCaptivateSensorArray
//! This array allows for indexed access to any
//! sensor in the configuration.
//
//*****************************************************************************
tSensor* g_pCaptivateSensorArray[CAPT_SENSOR_COUNT] =
{
    &numericKeypad,
    &proximityAndGuard,
};


//*****************************************************************************
//
//! \var g_uiApp
//! This structure stores the global settings for this application.
//
//*****************************************************************************
tCaptivateApplication g_uiApp =
{
    .state = eUIActive,
	.pSensorList = &g_pCaptivateSensorArray[0],
    .ui8NrOfSensors = CAPT_SENSOR_COUNT,
    .ui8AppLPM = CAPT_LOW_POWER_MODE,
    .bElementDataTxEnable = true,
    .bSensorDataTxEnable = true,
    .ui16ActiveModeScanPeriod = 33,
    .ui16WakeOnProxModeScanPeriod = 100,
    .ui16InactivityTimeout = 32,
    .ui8WakeupInterval = 5,
};
