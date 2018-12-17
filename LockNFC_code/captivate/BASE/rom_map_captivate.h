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
//
// rom_map_captivate.h
// Macros to facilitate calling functions in the ROM
// API table when they are available in a device.
//
//! CapTIvate Software Library Build: 1.70.00.03
//! Released on: July 30, 2018
//
//*****************************************************************************

#ifndef __ROM_MAP_CAPTIVATE_H__
#define __ROM_MAP_CAPTIVATE_H__

//*****************************************************************************
//
// Calling Macros for the CapTIvate Software Library
// There are 171 APIs in the CapTIvate library.
//
//*****************************************************************************

// ROM vs. FRAM Calling Macro for CAPT_processButtons() 
#ifdef ROM_CAPT_processButtons
#define MAP_CAPT_processButtons \
        ROM_CAPT_processButtons
#else
#define MAP_CAPT_processButtons \
        CAPT_processButtons
#endif

// ROM vs. FRAM Calling Macro for CAPT_getDominantButton() 
#ifdef ROM_CAPT_getDominantButton
#define MAP_CAPT_getDominantButton \
        ROM_CAPT_getDominantButton
#else
#define MAP_CAPT_getDominantButton \
        CAPT_getDominantButton
#endif

// ROM vs. FRAM Calling Macro for CAPT_getDominantButtonAddr() 
#ifdef ROM_CAPT_getDominantButtonAddr
#define MAP_CAPT_getDominantButtonAddr \
        ROM_CAPT_getDominantButtonAddr
#else
#define MAP_CAPT_getDominantButtonAddr \
        CAPT_getDominantButtonAddr
#endif

// ROM vs. FRAM Calling Macro for CAPT_calibrateSensor() 
#ifdef ROM_CAPT_calibrateSensor
#define MAP_CAPT_calibrateSensor \
        ROM_CAPT_calibrateSensor
#else
#define MAP_CAPT_calibrateSensor \
        CAPT_calibrateSensor
#endif

// ROM vs. FRAM Calling Macro for CAPT_calibrateSensorWithMaxOffset() 
#ifdef ROM_CAPT_calibrateSensorWithMaxOffset
#define MAP_CAPT_calibrateSensorWithMaxOffset \
        ROM_CAPT_calibrateSensorWithMaxOffset
#else
#define MAP_CAPT_calibrateSensorWithMaxOffset \
        CAPT_calibrateSensorWithMaxOffset
#endif

// ROM vs. FRAM Calling Macro for CAPT_calibrateSensorWithEMC() 
#ifdef ROM_CAPT_calibrateSensorWithEMC
#define MAP_CAPT_calibrateSensorWithEMC \
        ROM_CAPT_calibrateSensorWithEMC
#else
#define MAP_CAPT_calibrateSensorWithEMC \
        CAPT_calibrateSensorWithEMC
#endif

// ROM vs. FRAM Calling Macro for CAPT_calibrateSensorWithMaxOffsetWithEMC() 
#ifdef ROM_CAPT_calibrateSensorWithMaxOffsetWithEMC
#define MAP_CAPT_calibrateSensorWithMaxOffsetWithEMC \
        ROM_CAPT_calibrateSensorWithMaxOffsetWithEMC
#else
#define MAP_CAPT_calibrateSensorWithMaxOffsetWithEMC \
        CAPT_calibrateSensorWithMaxOffsetWithEMC
#endif

// ROM vs. FRAM Calling Macro for CAPT_calibrateGain() 
#ifdef ROM_CAPT_calibrateGain
#define MAP_CAPT_calibrateGain \
        ROM_CAPT_calibrateGain
#else
#define MAP_CAPT_calibrateGain \
        CAPT_calibrateGain
#endif

// ROM vs. FRAM Calling Macro for CAPT_calibrateOffset() 
#ifdef ROM_CAPT_calibrateOffset
#define MAP_CAPT_calibrateOffset \
        ROM_CAPT_calibrateOffset
#else
#define MAP_CAPT_calibrateOffset \
        CAPT_calibrateOffset
#endif

// ROM vs. FRAM Calling Macro for CAPT_getElementMaxCountStatus() 
#ifdef ROM_CAPT_getElementMaxCountStatus
#define MAP_CAPT_getElementMaxCountStatus \
        ROM_CAPT_getElementMaxCountStatus
#else
#define MAP_CAPT_getElementMaxCountStatus \
        CAPT_getElementMaxCountStatus
#endif

// ROM vs. FRAM Calling Macro for CAPT_calibrateForMaxOffset() 
#ifdef ROM_CAPT_calibrateForMaxOffset
#define MAP_CAPT_calibrateForMaxOffset \
        ROM_CAPT_calibrateForMaxOffset
#else
#define MAP_CAPT_calibrateForMaxOffset \
        CAPT_calibrateForMaxOffset
#endif

// ROM vs. FRAM Calling Macro for CAPT_loadEMCConfig() 
#ifdef ROM_CAPT_loadEMCConfig
#define MAP_CAPT_loadEMCConfig \
        ROM_CAPT_loadEMCConfig
#else
#define MAP_CAPT_loadEMCConfig \
        CAPT_loadEMCConfig
#endif

// ROM vs. FRAM Calling Macro for CAPT_getGlobalFilteredNoiseLevel() 
#ifdef ROM_CAPT_getGlobalFilteredNoiseLevel
#define MAP_CAPT_getGlobalFilteredNoiseLevel \
        ROM_CAPT_getGlobalFilteredNoiseLevel
#else
#define MAP_CAPT_getGlobalFilteredNoiseLevel \
        CAPT_getGlobalFilteredNoiseLevel
#endif

// ROM vs. FRAM Calling Macro for CAPT_resetGlobalFilteredNoiseLevel() 
#ifdef ROM_CAPT_resetGlobalFilteredNoiseLevel
#define MAP_CAPT_resetGlobalFilteredNoiseLevel \
        ROM_CAPT_resetGlobalFilteredNoiseLevel
#else
#define MAP_CAPT_resetGlobalFilteredNoiseLevel \
        CAPT_resetGlobalFilteredNoiseLevel
#endif

// ROM vs. FRAM Calling Macro for CAPT_updateGlobalFilteredNoiseLevel() 
#ifdef ROM_CAPT_updateGlobalFilteredNoiseLevel
#define MAP_CAPT_updateGlobalFilteredNoiseLevel \
        ROM_CAPT_updateGlobalFilteredNoiseLevel
#else
#define MAP_CAPT_updateGlobalFilteredNoiseLevel \
        CAPT_updateGlobalFilteredNoiseLevel
#endif

// ROM vs. FRAM Calling Macro for CAPT_getEMCConversionSettings() 
#ifdef ROM_CAPT_getEMCConversionSettings
#define MAP_CAPT_getEMCConversionSettings \
        ROM_CAPT_getEMCConversionSettings
#else
#define MAP_CAPT_getEMCConversionSettings \
        CAPT_getEMCConversionSettings
#endif

// ROM vs. FRAM Calling Macro for CAPT_getRelNoiseStatusThreshold() 
#ifdef ROM_CAPT_getRelNoiseStatusThreshold
#define MAP_CAPT_getRelNoiseStatusThreshold \
        ROM_CAPT_getRelNoiseStatusThreshold
#else
#define MAP_CAPT_getRelNoiseStatusThreshold \
        CAPT_getRelNoiseStatusThreshold
#endif

// ROM vs. FRAM Calling Macro for CAPT_getMaxRelThreshold() 
#ifdef ROM_CAPT_getMaxRelThreshold
#define MAP_CAPT_getMaxRelThreshold \
        ROM_CAPT_getMaxRelThreshold
#else
#define MAP_CAPT_getMaxRelThreshold \
        CAPT_getMaxRelThreshold
#endif

// ROM vs. FRAM Calling Macro for CAPT_testConversionFrequencyForNoise() 
#ifdef ROM_CAPT_testConversionFrequencyForNoise
#define MAP_CAPT_testConversionFrequencyForNoise \
        ROM_CAPT_testConversionFrequencyForNoise
#else
#define MAP_CAPT_testConversionFrequencyForNoise \
        CAPT_testConversionFrequencyForNoise
#endif

// ROM vs. FRAM Calling Macro for CAPT_correctInvalidMultiFreqCalibration() 
#ifdef ROM_CAPT_correctInvalidMultiFreqCalibration
#define MAP_CAPT_correctInvalidMultiFreqCalibration \
        ROM_CAPT_correctInvalidMultiFreqCalibration
#else
#define MAP_CAPT_correctInvalidMultiFreqCalibration \
        CAPT_correctInvalidMultiFreqCalibration
#endif

// ROM vs. FRAM Calling Macro for CAPT_replaceFrequencyWithError() 
#ifdef ROM_CAPT_replaceFrequencyWithError
#define MAP_CAPT_replaceFrequencyWithError \
        ROM_CAPT_replaceFrequencyWithError
#else
#define MAP_CAPT_replaceFrequencyWithError \
        CAPT_replaceFrequencyWithError
#endif

// ROM vs. FRAM Calling Macro for CAPT_resolveMultiFreqSet() 
#ifdef ROM_CAPT_resolveMultiFreqSet
#define MAP_CAPT_resolveMultiFreqSet \
        ROM_CAPT_resolveMultiFreqSet
#else
#define MAP_CAPT_resolveMultiFreqSet \
        CAPT_resolveMultiFreqSet
#endif

// ROM vs. FRAM Calling Macro for CAPT_computeJitterFilter() 
#ifdef ROM_CAPT_computeJitterFilter
#define MAP_CAPT_computeJitterFilter \
        ROM_CAPT_computeJitterFilter
#else
#define MAP_CAPT_computeJitterFilter \
        CAPT_computeJitterFilter
#endif

// ROM vs. FRAM Calling Macro for CAPT_computePos2ndDegPoly() 
#ifdef ROM_CAPT_computePos2ndDegPoly
#define MAP_CAPT_computePos2ndDegPoly \
        ROM_CAPT_computePos2ndDegPoly
#else
#define MAP_CAPT_computePos2ndDegPoly \
        CAPT_computePos2ndDegPoly
#endif

// ROM vs. FRAM Calling Macro for CAPT_computeRelNoiseComp() 
#ifdef ROM_CAPT_computeRelNoiseComp
#define MAP_CAPT_computeRelNoiseComp \
        ROM_CAPT_computeRelNoiseComp
#else
#define MAP_CAPT_computeRelNoiseComp \
        CAPT_computeRelNoiseComp
#endif

// ROM vs. FRAM Calling Macro for CAPT_computeWheelWrap() 
#ifdef ROM_CAPT_computeWheelWrap
#define MAP_CAPT_computeWheelWrap \
        ROM_CAPT_computeWheelWrap
#else
#define MAP_CAPT_computeWheelWrap \
        CAPT_computeWheelWrap
#endif

// ROM vs. FRAM Calling Macro for CAPT_processSlider() 
#ifdef ROM_CAPT_processSlider
#define MAP_CAPT_processSlider \
        ROM_CAPT_processSlider
#else
#define MAP_CAPT_processSlider \
        CAPT_processSlider
#endif

// ROM vs. FRAM Calling Macro for CAPT_computeArcTanApprox() 
#ifdef ROM_CAPT_computeArcTanApprox
#define MAP_CAPT_computeArcTanApprox \
        ROM_CAPT_computeArcTanApprox
#else
#define MAP_CAPT_computeArcTanApprox \
        CAPT_computeArcTanApprox
#endif

// ROM vs. FRAM Calling Macro for CAPT_computeSliderVectors() 
#ifdef ROM_CAPT_computeSliderVectors
#define MAP_CAPT_computeSliderVectors \
        ROM_CAPT_computeSliderVectors
#else
#define MAP_CAPT_computeSliderVectors \
        CAPT_computeSliderVectors
#endif

// ROM vs. FRAM Calling Macro for CAPT_getSensorPosition() 
#ifdef ROM_CAPT_getSensorPosition
#define MAP_CAPT_getSensorPosition \
        ROM_CAPT_getSensorPosition
#else
#define MAP_CAPT_getSensorPosition \
        CAPT_getSensorPosition
#endif

// ROM vs. FRAM Calling Macro for CAPT_getBeta() 
#ifdef ROM_CAPT_getBeta
#define MAP_CAPT_getBeta \
        ROM_CAPT_getBeta
#else
#define MAP_CAPT_getBeta \
        CAPT_getBeta
#endif

// ROM vs. FRAM Calling Macro for CAPT_getXY() 
#ifdef ROM_CAPT_getXY
#define MAP_CAPT_getXY \
        ROM_CAPT_getXY
#else
#define MAP_CAPT_getXY \
        CAPT_getXY
#endif

// ROM vs. FRAM Calling Macro for CAPT_trimPosition() 
#ifdef ROM_CAPT_trimPosition
#define MAP_CAPT_trimPosition \
        ROM_CAPT_trimPosition
#else
#define MAP_CAPT_trimPosition \
        CAPT_trimPosition
#endif

// ROM vs. FRAM Calling Macro for CAPT_processTrackPadSensor() 
#ifdef ROM_CAPT_processTrackPadSensor
#define MAP_CAPT_processTrackPadSensor \
        ROM_CAPT_processTrackPadSensor
#else
#define MAP_CAPT_processTrackPadSensor \
        CAPT_processTrackPadSensor
#endif

// ROM vs. FRAM Calling Macro for CAPT_processTrackPadGesture() 
#ifdef ROM_CAPT_processTrackPadGesture
#define MAP_CAPT_processTrackPadGesture \
        ROM_CAPT_processTrackPadGesture
#else
#define MAP_CAPT_processTrackPadGesture \
        CAPT_processTrackPadGesture
#endif

// ROM vs. FRAM Calling Macro for CAPT_enableRefCap() 
#ifdef ROM_CAPT_enableRefCap
#define MAP_CAPT_enableRefCap \
        ROM_CAPT_enableRefCap
#else
#define MAP_CAPT_enableRefCap \
        CAPT_enableRefCap
#endif

// ROM vs. FRAM Calling Macro for CAPT_disableRefCap() 
#ifdef ROM_CAPT_disableRefCap
#define MAP_CAPT_disableRefCap \
        ROM_CAPT_disableRefCap
#else
#define MAP_CAPT_disableRefCap \
        CAPT_disableRefCap
#endif

// ROM vs. FRAM Calling Macro for CAPT_powerOn() 
#ifdef ROM_CAPT_powerOn
#define MAP_CAPT_powerOn \
        ROM_CAPT_powerOn
#else
#define MAP_CAPT_powerOn \
        CAPT_powerOn
#endif

// ROM vs. FRAM Calling Macro for CAPT_powerOff() 
#ifdef ROM_CAPT_powerOff
#define MAP_CAPT_powerOff \
        ROM_CAPT_powerOff
#else
#define MAP_CAPT_powerOff \
        CAPT_powerOff
#endif

// ROM vs. FRAM Calling Macro for CAPT_readTimerCompRegister() 
#ifdef ROM_CAPT_readTimerCompRegister
#define MAP_CAPT_readTimerCompRegister \
        ROM_CAPT_readTimerCompRegister
#else
#define MAP_CAPT_readTimerCompRegister \
        CAPT_readTimerCompRegister
#endif

// ROM vs. FRAM Calling Macro for CAPT_writeTimerCompRegister() 
#ifdef ROM_CAPT_writeTimerCompRegister
#define MAP_CAPT_writeTimerCompRegister \
        ROM_CAPT_writeTimerCompRegister
#else
#define MAP_CAPT_writeTimerCompRegister \
        CAPT_writeTimerCompRegister
#endif

// ROM vs. FRAM Calling Macro for CAPT_readTimerRegister() 
#ifdef ROM_CAPT_readTimerRegister
#define MAP_CAPT_readTimerRegister \
        ROM_CAPT_readTimerRegister
#else
#define MAP_CAPT_readTimerRegister \
        CAPT_readTimerRegister
#endif

// ROM vs. FRAM Calling Macro for CAPT_stopTimer() 
#ifdef ROM_CAPT_stopTimer
#define MAP_CAPT_stopTimer \
        ROM_CAPT_stopTimer
#else
#define MAP_CAPT_stopTimer \
        CAPT_stopTimer
#endif

// ROM vs. FRAM Calling Macro for CAPT_startTimer() 
#ifdef ROM_CAPT_startTimer
#define MAP_CAPT_startTimer \
        ROM_CAPT_startTimer
#else
#define MAP_CAPT_startTimer \
        CAPT_startTimer
#endif

// ROM vs. FRAM Calling Macro for CAPT_enableTimerTrigMeasurement() 
#ifdef ROM_CAPT_enableTimerTrigMeasurement
#define MAP_CAPT_enableTimerTrigMeasurement \
        ROM_CAPT_enableTimerTrigMeasurement
#else
#define MAP_CAPT_enableTimerTrigMeasurement \
        CAPT_enableTimerTrigMeasurement
#endif

// ROM vs. FRAM Calling Macro for CAPT_disableTimerTrigMeasurement() 
#ifdef ROM_CAPT_disableTimerTrigMeasurement
#define MAP_CAPT_disableTimerTrigMeasurement \
        ROM_CAPT_disableTimerTrigMeasurement
#else
#define MAP_CAPT_disableTimerTrigMeasurement \
        CAPT_disableTimerTrigMeasurement
#endif

// ROM vs. FRAM Calling Macro for CAPT_clearTimer() 
#ifdef ROM_CAPT_clearTimer
#define MAP_CAPT_clearTimer \
        ROM_CAPT_clearTimer
#else
#define MAP_CAPT_clearTimer \
        CAPT_clearTimer
#endif

// ROM vs. FRAM Calling Macro for CAPT_selectTimerSource() 
#ifdef ROM_CAPT_selectTimerSource
#define MAP_CAPT_selectTimerSource \
        ROM_CAPT_selectTimerSource
#else
#define MAP_CAPT_selectTimerSource \
        CAPT_selectTimerSource
#endif

// ROM vs. FRAM Calling Macro for CAPT_selectTimerSourceDivider() 
#ifdef ROM_CAPT_selectTimerSourceDivider
#define MAP_CAPT_selectTimerSourceDivider \
        ROM_CAPT_selectTimerSourceDivider
#else
#define MAP_CAPT_selectTimerSourceDivider \
        CAPT_selectTimerSourceDivider
#endif

// ROM vs. FRAM Calling Macro for CAPT_startCCounter() 
#ifdef ROM_CAPT_startCCounter
#define MAP_CAPT_startCCounter \
        ROM_CAPT_startCCounter
#else
#define MAP_CAPT_startCCounter \
        CAPT_startCCounter
#endif

// ROM vs. FRAM Calling Macro for CAPT_stopCCounter() 
#ifdef ROM_CAPT_stopCCounter
#define MAP_CAPT_stopCCounter \
        ROM_CAPT_stopCCounter
#else
#define MAP_CAPT_stopCCounter \
        CAPT_stopCCounter
#endif

// ROM vs. FRAM Calling Macro for CAPT_clearCCounter() 
#ifdef ROM_CAPT_clearCCounter
#define MAP_CAPT_clearCCounter \
        ROM_CAPT_clearCCounter
#else
#define MAP_CAPT_clearCCounter \
        CAPT_clearCCounter
#endif

// ROM vs. FRAM Calling Macro for CAPT_selectCCounterInterval() 
#ifdef ROM_CAPT_selectCCounterInterval
#define MAP_CAPT_selectCCounterInterval \
        ROM_CAPT_selectCCounterInterval
#else
#define MAP_CAPT_selectCCounterInterval \
        CAPT_selectCCounterInterval
#endif

// ROM vs. FRAM Calling Macro for CAPT_pollResetStatus() 
#ifdef ROM_CAPT_pollResetStatus
#define MAP_CAPT_pollResetStatus \
        ROM_CAPT_pollResetStatus
#else
#define MAP_CAPT_pollResetStatus \
        CAPT_pollResetStatus
#endif

// ROM vs. FRAM Calling Macro for CAPT_setStabilization() 
#ifdef ROM_CAPT_setStabilization
#define MAP_CAPT_setStabilization \
        ROM_CAPT_setStabilization
#else
#define MAP_CAPT_setStabilization \
        CAPT_setStabilization
#endif

// ROM vs. FRAM Calling Macro for CAPT_releaseStabilization() 
#ifdef ROM_CAPT_releaseStabilization
#define MAP_CAPT_releaseStabilization \
        ROM_CAPT_releaseStabilization
#else
#define MAP_CAPT_releaseStabilization \
        CAPT_releaseStabilization
#endif

// ROM vs. FRAM Calling Macro for CAPT_reset() 
#ifdef ROM_CAPT_reset
#define MAP_CAPT_reset \
        ROM_CAPT_reset
#else
#define MAP_CAPT_reset \
        CAPT_reset
#endif

// ROM vs. FRAM Calling Macro for CAPT_pollCIPF() 
#ifdef ROM_CAPT_pollCIPF
#define MAP_CAPT_pollCIPF \
        ROM_CAPT_pollCIPF
#else
#define MAP_CAPT_pollCIPF \
        CAPT_pollCIPF
#endif

// ROM vs. FRAM Calling Macro for CAPT_init() 
#ifdef ROM_CAPT_init
#define MAP_CAPT_init \
        ROM_CAPT_init
#else
#define MAP_CAPT_init \
        CAPT_init
#endif

// ROM vs. FRAM Calling Macro for CAPT_bypassFSM() 
#ifdef ROM_CAPT_bypassFSM
#define MAP_CAPT_bypassFSM \
        ROM_CAPT_bypassFSM
#else
#define MAP_CAPT_bypassFSM \
        CAPT_bypassFSM
#endif

// ROM vs. FRAM Calling Macro for CAPT_engageFSM() 
#ifdef ROM_CAPT_engageFSM
#define MAP_CAPT_engageFSM \
        ROM_CAPT_engageFSM
#else
#define MAP_CAPT_engageFSM \
        CAPT_engageFSM
#endif

// ROM vs. FRAM Calling Macro for CAPT_writeCoarseGain() 
#ifdef ROM_CAPT_writeCoarseGain
#define MAP_CAPT_writeCoarseGain \
        ROM_CAPT_writeCoarseGain
#else
#define MAP_CAPT_writeCoarseGain \
        CAPT_writeCoarseGain
#endif

// ROM vs. FRAM Calling Macro for CAPT_readCoarseGain() 
#ifdef ROM_CAPT_readCoarseGain
#define MAP_CAPT_readCoarseGain \
        ROM_CAPT_readCoarseGain
#else
#define MAP_CAPT_readCoarseGain \
        CAPT_readCoarseGain
#endif

// ROM vs. FRAM Calling Macro for CAPT_writeFineGain() 
#ifdef ROM_CAPT_writeFineGain
#define MAP_CAPT_writeFineGain \
        ROM_CAPT_writeFineGain
#else
#define MAP_CAPT_writeFineGain \
        CAPT_writeFineGain
#endif

// ROM vs. FRAM Calling Macro for CAPT_readFineGain() 
#ifdef ROM_CAPT_readFineGain
#define MAP_CAPT_readFineGain \
        ROM_CAPT_readFineGain
#else
#define MAP_CAPT_readFineGain \
        CAPT_readFineGain
#endif

// ROM vs. FRAM Calling Macro for CAPT_writeOffsetTap() 
#ifdef ROM_CAPT_writeOffsetTap
#define MAP_CAPT_writeOffsetTap \
        ROM_CAPT_writeOffsetTap
#else
#define MAP_CAPT_writeOffsetTap \
        CAPT_writeOffsetTap
#endif

// ROM vs. FRAM Calling Macro for CAPT_readOffsetTap() 
#ifdef ROM_CAPT_readOffsetTap
#define MAP_CAPT_readOffsetTap \
        ROM_CAPT_readOffsetTap
#else
#define MAP_CAPT_readOffsetTap \
        CAPT_readOffsetTap
#endif

// ROM vs. FRAM Calling Macro for CAPT_readConversion() 
#ifdef ROM_CAPT_readConversion
#define MAP_CAPT_readConversion \
        ROM_CAPT_readConversion
#else
#define MAP_CAPT_readConversion \
        CAPT_readConversion
#endif

// ROM vs. FRAM Calling Macro for CAPT_setCAPLPMCFG() 
#ifdef ROM_CAPT_setCAPLPMCFG
#define MAP_CAPT_setCAPLPMCFG \
        ROM_CAPT_setCAPLPMCFG
#else
#define MAP_CAPT_setCAPLPMCFG \
        CAPT_setCAPLPMCFG
#endif

// ROM vs. FRAM Calling Macro for CAPT_clearCAPLPMCFG() 
#ifdef ROM_CAPT_clearCAPLPMCFG
#define MAP_CAPT_clearCAPLPMCFG \
        ROM_CAPT_clearCAPLPMCFG
#else
#define MAP_CAPT_clearCAPLPMCFG \
        CAPT_clearCAPLPMCFG
#endif

// ROM vs. FRAM Calling Macro for CAPT_setChannelEnable() 
#ifdef ROM_CAPT_setChannelEnable
#define MAP_CAPT_setChannelEnable \
        ROM_CAPT_setChannelEnable
#else
#define MAP_CAPT_setChannelEnable \
        CAPT_setChannelEnable
#endif

// ROM vs. FRAM Calling Macro for CAPT_clearChannelEnable() 
#ifdef ROM_CAPT_clearChannelEnable
#define MAP_CAPT_clearChannelEnable \
        ROM_CAPT_clearChannelEnable
#else
#define MAP_CAPT_clearChannelEnable \
        CAPT_clearChannelEnable
#endif

// ROM vs. FRAM Calling Macro for CAPT_setChannelActive() 
#ifdef ROM_CAPT_setChannelActive
#define MAP_CAPT_setChannelActive \
        ROM_CAPT_setChannelActive
#else
#define MAP_CAPT_setChannelActive \
        CAPT_setChannelActive
#endif

// ROM vs. FRAM Calling Macro for CAPT_clearChannelActive() 
#ifdef ROM_CAPT_clearChannelActive
#define MAP_CAPT_clearChannelActive \
        ROM_CAPT_clearChannelActive
#else
#define MAP_CAPT_clearChannelActive \
        CAPT_clearChannelActive
#endif

// ROM vs. FRAM Calling Macro for CAPT_setChannelOffState() 
#ifdef ROM_CAPT_setChannelOffState
#define MAP_CAPT_setChannelOffState \
        ROM_CAPT_setChannelOffState
#else
#define MAP_CAPT_setChannelOffState \
        CAPT_setChannelOffState
#endif

// ROM vs. FRAM Calling Macro for CAPT_clearChannelOffState() 
#ifdef ROM_CAPT_clearChannelOffState
#define MAP_CAPT_clearChannelOffState \
        ROM_CAPT_clearChannelOffState
#else
#define MAP_CAPT_clearChannelOffState \
        CAPT_clearChannelOffState
#endif

// ROM vs. FRAM Calling Macro for CAPT_setChannelOnState() 
#ifdef ROM_CAPT_setChannelOnState
#define MAP_CAPT_setChannelOnState \
        ROM_CAPT_setChannelOnState
#else
#define MAP_CAPT_setChannelOnState \
        CAPT_setChannelOnState
#endif

// ROM vs. FRAM Calling Macro for CAPT_clearChannelOnState() 
#ifdef ROM_CAPT_clearChannelOnState
#define MAP_CAPT_clearChannelOnState \
        ROM_CAPT_clearChannelOnState
#else
#define MAP_CAPT_clearChannelOnState \
        CAPT_clearChannelOnState
#endif

// ROM vs. FRAM Calling Macro for CAPT_enableSensorIO() 
#ifdef ROM_CAPT_enableSensorIO
#define MAP_CAPT_enableSensorIO \
        ROM_CAPT_enableSensorIO
#else
#define MAP_CAPT_enableSensorIO \
        CAPT_enableSensorIO
#endif

// ROM vs. FRAM Calling Macro for CAPT_disableSensorIO() 
#ifdef ROM_CAPT_disableSensorIO
#define MAP_CAPT_disableSensorIO \
        ROM_CAPT_disableSensorIO
#else
#define MAP_CAPT_disableSensorIO \
        CAPT_disableSensorIO
#endif

// ROM vs. FRAM Calling Macro for CAPT_initSensorIO() 
#ifdef ROM_CAPT_initSensorIO
#define MAP_CAPT_initSensorIO \
        ROM_CAPT_initSensorIO
#else
#define MAP_CAPT_initSensorIO \
        CAPT_initSensorIO
#endif

// ROM vs. FRAM Calling Macro for CAPT_forceSensorIO() 
#ifdef ROM_CAPT_forceSensorIO
#define MAP_CAPT_forceSensorIO \
        ROM_CAPT_forceSensorIO
#else
#define MAP_CAPT_forceSensorIO \
        CAPT_forceSensorIO
#endif

// ROM vs. FRAM Calling Macro for CAPT_applySensorParams() 
#ifdef ROM_CAPT_applySensorParams
#define MAP_CAPT_applySensorParams \
        ROM_CAPT_applySensorParams
#else
#define MAP_CAPT_applySensorParams \
        CAPT_applySensorParams
#endif

// ROM vs. FRAM Calling Macro for CAPT_disableSensorSyncEvent() 
#ifdef ROM_CAPT_disableSensorSyncEvent
#define MAP_CAPT_disableSensorSyncEvent \
        ROM_CAPT_disableSensorSyncEvent
#else
#define MAP_CAPT_disableSensorSyncEvent \
        CAPT_disableSensorSyncEvent
#endif

// ROM vs. FRAM Calling Macro for CAPT_enableSensorSyncEvent() 
#ifdef ROM_CAPT_enableSensorSyncEvent
#define MAP_CAPT_enableSensorSyncEvent \
        ROM_CAPT_enableSensorSyncEvent
#else
#define MAP_CAPT_enableSensorSyncEvent \
        CAPT_enableSensorSyncEvent
#endif

// ROM vs. FRAM Calling Macro for CAPT_applySensorFreq() 
#ifdef ROM_CAPT_applySensorFreq
#define MAP_CAPT_applySensorFreq \
        ROM_CAPT_applySensorFreq
#else
#define MAP_CAPT_applySensorFreq \
        CAPT_applySensorFreq
#endif

// ROM vs. FRAM Calling Macro for CAPT_setCycleIO() 
#ifdef ROM_CAPT_setCycleIO
#define MAP_CAPT_setCycleIO \
        ROM_CAPT_setCycleIO
#else
#define MAP_CAPT_setCycleIO \
        CAPT_setCycleIO
#endif

// ROM vs. FRAM Calling Macro for CAPT_clearCycleIO() 
#ifdef ROM_CAPT_clearCycleIO
#define MAP_CAPT_clearCycleIO \
        ROM_CAPT_clearCycleIO
#else
#define MAP_CAPT_clearCycleIO \
        CAPT_clearCycleIO
#endif

// ROM vs. FRAM Calling Macro for CAPT_applyCycleComp() 
#ifdef ROM_CAPT_applyCycleComp
#define MAP_CAPT_applyCycleComp \
        ROM_CAPT_applyCycleComp
#else
#define MAP_CAPT_applyCycleComp \
        CAPT_applyCycleComp
#endif

// ROM vs. FRAM Calling Macro for CAPT_applyCycleFSM() 
#ifdef ROM_CAPT_applyCycleFSM
#define MAP_CAPT_applyCycleFSM \
        ROM_CAPT_applyCycleFSM
#else
#define MAP_CAPT_applyCycleFSM \
        CAPT_applyCycleFSM
#endif

// ROM vs. FRAM Calling Macro for CAPT_enableISR() 
#ifdef ROM_CAPT_enableISR
#define MAP_CAPT_enableISR \
        ROM_CAPT_enableISR
#else
#define MAP_CAPT_enableISR \
        CAPT_enableISR
#endif

// ROM vs. FRAM Calling Macro for CAPT_disableISR() 
#ifdef ROM_CAPT_disableISR
#define MAP_CAPT_disableISR \
        ROM_CAPT_disableISR
#else
#define MAP_CAPT_disableISR \
        CAPT_disableISR
#endif

// ROM vs. FRAM Calling Macro for CAPT_setCAPSTART() 
#ifdef ROM_CAPT_setCAPSTART
#define MAP_CAPT_setCAPSTART \
        ROM_CAPT_setCAPSTART
#else
#define MAP_CAPT_setCAPSTART \
        CAPT_setCAPSTART
#endif

// ROM vs. FRAM Calling Macro for CAPT_clearCAPSTART() 
#ifdef ROM_CAPT_clearCAPSTART
#define MAP_CAPT_clearCAPSTART \
        ROM_CAPT_clearCAPSTART
#else
#define MAP_CAPT_clearCAPSTART \
        CAPT_clearCAPSTART
#endif

// ROM vs. FRAM Calling Macro for CAPT_saveCycleResults() 
#ifdef ROM_CAPT_saveCycleResults
#define MAP_CAPT_saveCycleResults \
        ROM_CAPT_saveCycleResults
#else
#define MAP_CAPT_saveCycleResults \
        CAPT_saveCycleResults
#endif

// ROM vs. FRAM Calling Macro for CAPT_saveCycleRawResults() 
#ifdef ROM_CAPT_saveCycleRawResults
#define MAP_CAPT_saveCycleRawResults \
        ROM_CAPT_saveCycleRawResults
#else
#define MAP_CAPT_saveCycleRawResults \
        CAPT_saveCycleRawResults
#endif

// ROM vs. FRAM Calling Macro for CAPT_pollIFG() 
#ifdef ROM_CAPT_pollIFG
#define MAP_CAPT_pollIFG \
        ROM_CAPT_pollIFG
#else
#define MAP_CAPT_pollIFG \
        CAPT_pollIFG
#endif

// ROM vs. FRAM Calling Macro for CAPT_clearIFG() 
#ifdef ROM_CAPT_clearIFG
#define MAP_CAPT_clearIFG \
        ROM_CAPT_clearIFG
#else
#define MAP_CAPT_clearIFG \
        CAPT_clearIFG
#endif

// ROM vs. FRAM Calling Macro for CAPT_getInterruptVector() 
#ifdef ROM_CAPT_getInterruptVector
#define MAP_CAPT_getInterruptVector \
        ROM_CAPT_getInterruptVector
#else
#define MAP_CAPT_getInterruptVector \
        CAPT_getInterruptVector
#endif

// ROM vs. FRAM Calling Macro for CAPT_enableShieldIO() 
#ifdef ROM_CAPT_enableShieldIO
#define MAP_CAPT_enableShieldIO \
        ROM_CAPT_enableShieldIO
#else
#define MAP_CAPT_enableShieldIO \
        CAPT_enableShieldIO
#endif

// ROM vs. FRAM Calling Macro for CAPT_disableShieldIO() 
#ifdef ROM_CAPT_disableShieldIO
#define MAP_CAPT_disableShieldIO \
        ROM_CAPT_disableShieldIO
#else
#define MAP_CAPT_disableShieldIO \
        CAPT_disableShieldIO
#endif

// ROM vs. FRAM Calling Macro for CAPT_initSensor() 
#ifdef ROM_CAPT_initSensor
#define MAP_CAPT_initSensor \
        ROM_CAPT_initSensor
#else
#define MAP_CAPT_initSensor \
        CAPT_initSensor
#endif

// ROM vs. FRAM Calling Macro for CAPT_updateSensor() 
#ifdef ROM_CAPT_updateSensor
#define MAP_CAPT_updateSensor \
        ROM_CAPT_updateSensor
#else
#define MAP_CAPT_updateSensor \
        CAPT_updateSensor
#endif

// ROM vs. FRAM Calling Macro for CAPT_updateSensorRawCount() 
#ifdef ROM_CAPT_updateSensorRawCount
#define MAP_CAPT_updateSensorRawCount \
        ROM_CAPT_updateSensorRawCount
#else
#define MAP_CAPT_updateSensorRawCount \
        CAPT_updateSensorRawCount
#endif

// ROM vs. FRAM Calling Macro for CAPT_startWakeOnProxMode() 
#ifdef ROM_CAPT_startWakeOnProxMode
#define MAP_CAPT_startWakeOnProxMode \
        ROM_CAPT_startWakeOnProxMode
#else
#define MAP_CAPT_startWakeOnProxMode \
        CAPT_startWakeOnProxMode
#endif

// ROM vs. FRAM Calling Macro for CAPT_stopWakeOnProxMode() 
#ifdef ROM_CAPT_stopWakeOnProxMode
#define MAP_CAPT_stopWakeOnProxMode \
        ROM_CAPT_stopWakeOnProxMode
#else
#define MAP_CAPT_stopWakeOnProxMode \
        CAPT_stopWakeOnProxMode
#endif

// ROM vs. FRAM Calling Macro for CAPT_processFSMCycle() 
#ifdef ROM_CAPT_processFSMCycle
#define MAP_CAPT_processFSMCycle \
        ROM_CAPT_processFSMCycle
#else
#define MAP_CAPT_processFSMCycle \
        CAPT_processFSMCycle
#endif

// ROM vs. FRAM Calling Macro for CAPT_preProcessSlider() 
#ifdef ROM_CAPT_preProcessSlider
#define MAP_CAPT_preProcessSlider \
        ROM_CAPT_preProcessSlider
#else
#define MAP_CAPT_preProcessSlider \
        CAPT_preProcessSlider
#endif

// ROM vs. FRAM Calling Macro for CAPT_processSensor() 
#ifdef ROM_CAPT_processSensor
#define MAP_CAPT_processSensor \
        ROM_CAPT_processSensor
#else
#define MAP_CAPT_processSensor \
        CAPT_processSensor
#endif

// ROM vs. FRAM Calling Macro for CAPT_testForRecalibration() 
#ifdef ROM_CAPT_testForRecalibration
#define MAP_CAPT_testForRecalibration \
        ROM_CAPT_testForRecalibration
#else
#define MAP_CAPT_testForRecalibration \
        CAPT_testForRecalibration
#endif

// ROM vs. FRAM Calling Macro for CAPT_testForMaxCountRecalibration() 
#ifdef ROM_CAPT_testForMaxCountRecalibration
#define MAP_CAPT_testForMaxCountRecalibration \
        ROM_CAPT_testForMaxCountRecalibration
#else
#define MAP_CAPT_testForMaxCountRecalibration \
        CAPT_testForMaxCountRecalibration
#endif

// ROM vs. FRAM Calling Macro for CAPT_testForNegativeTouchRecalibration() 
#ifdef ROM_CAPT_testForNegativeTouchRecalibration
#define MAP_CAPT_testForNegativeTouchRecalibration \
        ROM_CAPT_testForNegativeTouchRecalibration
#else
#define MAP_CAPT_testForNegativeTouchRecalibration \
        CAPT_testForNegativeTouchRecalibration
#endif

// ROM vs. FRAM Calling Macro for CAPT_flagAllElementsForReseed() 
#ifdef ROM_CAPT_flagAllElementsForReseed
#define MAP_CAPT_flagAllElementsForReseed \
        ROM_CAPT_flagAllElementsForReseed
#else
#define MAP_CAPT_flagAllElementsForReseed \
        CAPT_flagAllElementsForReseed
#endif

// ROM vs. FRAM Calling Macro for CAPT_updateSensorTimeout() 
#ifdef ROM_CAPT_updateSensorTimeout
#define MAP_CAPT_updateSensorTimeout \
        ROM_CAPT_updateSensorTimeout
#else
#define MAP_CAPT_updateSensorTimeout \
        CAPT_updateSensorTimeout
#endif

// ROM vs. FRAM Calling Macro for CAPT_updateSensorNoise() 
#ifdef ROM_CAPT_updateSensorNoise
#define MAP_CAPT_updateSensorNoise \
        ROM_CAPT_updateSensorNoise
#else
#define MAP_CAPT_updateSensorNoise \
        CAPT_updateSensorNoise
#endif

// ROM vs. FRAM Calling Macro for CAPT_convertAbsToRel() 
#ifdef ROM_CAPT_convertAbsToRel
#define MAP_CAPT_convertAbsToRel \
        ROM_CAPT_convertAbsToRel
#else
#define MAP_CAPT_convertAbsToRel \
        CAPT_convertAbsToRel
#endif

// ROM vs. FRAM Calling Macro for CAPT_convertRelToAbs() 
#ifdef ROM_CAPT_convertRelToAbs
#define MAP_CAPT_convertRelToAbs \
        ROM_CAPT_convertRelToAbs
#else
#define MAP_CAPT_convertRelToAbs \
        CAPT_convertRelToAbs
#endif

// ROM vs. FRAM Calling Macro for CAPT_getElementStateBitField() 
#ifdef ROM_CAPT_getElementStateBitField
#define MAP_CAPT_getElementStateBitField \
        ROM_CAPT_getElementStateBitField
#else
#define MAP_CAPT_getElementStateBitField \
        CAPT_getElementStateBitField
#endif

// ROM vs. FRAM Calling Macro for CAPT_updateFilterCounts() 
#ifdef ROM_CAPT_updateFilterCounts
#define MAP_CAPT_updateFilterCounts \
        ROM_CAPT_updateFilterCounts
#else
#define MAP_CAPT_updateFilterCounts \
        CAPT_updateFilterCounts
#endif

// ROM vs. FRAM Calling Macro for CAPT_updateFSMTouch() 
#ifdef ROM_CAPT_updateFSMTouch
#define MAP_CAPT_updateFSMTouch \
        ROM_CAPT_updateFSMTouch
#else
#define MAP_CAPT_updateFSMTouch \
        CAPT_updateFSMTouch
#endif

// ROM vs. FRAM Calling Macro for CAPT_updateFSMProx() 
#ifdef ROM_CAPT_updateFSMProx
#define MAP_CAPT_updateFSMProx \
        ROM_CAPT_updateFSMProx
#else
#define MAP_CAPT_updateFSMProx \
        CAPT_updateFSMProx
#endif

// ROM vs. FRAM Calling Macro for CAPT_updateProx() 
#ifdef ROM_CAPT_updateProx
#define MAP_CAPT_updateProx \
        ROM_CAPT_updateProx
#else
#define MAP_CAPT_updateProx \
        CAPT_updateProx
#endif

// ROM vs. FRAM Calling Macro for CAPT_updateTouch() 
#ifdef ROM_CAPT_updateTouch
#define MAP_CAPT_updateTouch \
        ROM_CAPT_updateTouch
#else
#define MAP_CAPT_updateTouch \
        CAPT_updateTouch
#endif

// ROM vs. FRAM Calling Macro for CAPT_updateLTA() 
#ifdef ROM_CAPT_updateLTA
#define MAP_CAPT_updateLTA \
        ROM_CAPT_updateLTA
#else
#define MAP_CAPT_updateLTA \
        CAPT_updateLTA
#endif

// ROM vs. FRAM Calling Macro for CAPT_clearSensorProxTouch() 
#ifdef ROM_CAPT_clearSensorProxTouch
#define MAP_CAPT_clearSensorProxTouch \
        ROM_CAPT_clearSensorProxTouch
#else
#define MAP_CAPT_clearSensorProxTouch \
        CAPT_clearSensorProxTouch
#endif

// ROM vs. FRAM Calling Macro for CAPT_updateSensorProxTouch() 
#ifdef ROM_CAPT_updateSensorProxTouch
#define MAP_CAPT_updateSensorProxTouch \
        ROM_CAPT_updateSensorProxTouch
#else
#define MAP_CAPT_updateSensorProxTouch \
        CAPT_updateSensorProxTouch
#endif

// ROM vs. FRAM Calling Macro for CAPT_updateFilterCount() 
#ifdef ROM_CAPT_updateFilterCount
#define MAP_CAPT_updateFilterCount \
        ROM_CAPT_updateFilterCount
#else
#define MAP_CAPT_updateFilterCount \
        CAPT_updateFilterCount
#endif

// ROM vs. FRAM Calling Macro for CAPT_computeIIRFilter() 
#ifdef ROM_CAPT_computeIIRFilter
#define MAP_CAPT_computeIIRFilter \
        ROM_CAPT_computeIIRFilter
#else
#define MAP_CAPT_computeIIRFilter \
        CAPT_computeIIRFilter
#endif

// ROM vs. FRAM Calling Macro for CAPT_computeIIRFilterFast() 
#ifdef ROM_CAPT_computeIIRFilterFast
#define MAP_CAPT_computeIIRFilterFast \
        ROM_CAPT_computeIIRFilterFast
#else
#define MAP_CAPT_computeIIRFilterFast \
        CAPT_computeIIRFilterFast
#endif

// ROM vs. FRAM Calling Macro for CAPT_registerCallback() 
#ifdef ROM_CAPT_registerCallback
#define MAP_CAPT_registerCallback \
        ROM_CAPT_registerCallback
#else
#define MAP_CAPT_registerCallback \
        CAPT_registerCallback
#endif

// ROM vs. FRAM Calling Macro for CAPT_reseedFilter() 
#ifdef ROM_CAPT_reseedFilter
#define MAP_CAPT_reseedFilter \
        ROM_CAPT_reseedFilter
#else
#define MAP_CAPT_reseedFilter \
        CAPT_reseedFilter
#endif

// ROM vs. FRAM Calling Macro for CAPT_reseedFilterAll() 
#ifdef ROM_CAPT_reseedFilterAll
#define MAP_CAPT_reseedFilterAll \
        ROM_CAPT_reseedFilterAll
#else
#define MAP_CAPT_reseedFilterAll \
        CAPT_reseedFilterAll
#endif

// ROM vs. FRAM Calling Macro for CAPT_blockOnFlag() 
#ifdef ROM_CAPT_blockOnFlag
#define MAP_CAPT_blockOnFlag \
        ROM_CAPT_blockOnFlag
#else
#define MAP_CAPT_blockOnFlag \
        CAPT_blockOnFlag
#endif

// ROM vs. FRAM Calling Macro for CAPT_loadCycle() 
#ifdef ROM_CAPT_loadCycle
#define MAP_CAPT_loadCycle \
        ROM_CAPT_loadCycle
#else
#define MAP_CAPT_loadCycle \
        CAPT_loadCycle
#endif

// ROM vs. FRAM Calling Macro for CAPT_unloadCycle() 
#ifdef ROM_CAPT_unloadCycle
#define MAP_CAPT_unloadCycle \
        ROM_CAPT_unloadCycle
#else
#define MAP_CAPT_unloadCycle \
        CAPT_unloadCycle
#endif

// ROM vs. FRAM Calling Macro for CAPT_startConversion() 
#ifdef ROM_CAPT_startConversion
#define MAP_CAPT_startConversion \
        ROM_CAPT_startConversion
#else
#define MAP_CAPT_startConversion \
        CAPT_startConversion
#endif

// ROM vs. FRAM Calling Macro for CAPT_cleanupAfterConversion() 
#ifdef ROM_CAPT_cleanupAfterConversion
#define MAP_CAPT_cleanupAfterConversion \
        ROM_CAPT_cleanupAfterConversion
#else
#define MAP_CAPT_cleanupAfterConversion \
        CAPT_cleanupAfterConversion
#endif

// ROM vs. FRAM Calling Macro for CAPT_startConversionAndWaitUntilDone() 
#ifdef ROM_CAPT_startConversionAndWaitUntilDone
#define MAP_CAPT_startConversionAndWaitUntilDone \
        ROM_CAPT_startConversionAndWaitUntilDone
#else
#define MAP_CAPT_startConversionAndWaitUntilDone \
        CAPT_startConversionAndWaitUntilDone
#endif

// ROM vs. FRAM Calling Macro for CAPT_updateSensorWithEMC() 
#ifdef ROM_CAPT_updateSensorWithEMC
#define MAP_CAPT_updateSensorWithEMC \
        ROM_CAPT_updateSensorWithEMC
#else
#define MAP_CAPT_updateSensorWithEMC \
        CAPT_updateSensorWithEMC
#endif

// ROM vs. FRAM Calling Macro for CAPT_processCycleWithEMC() 
#ifdef ROM_CAPT_processCycleWithEMC
#define MAP_CAPT_processCycleWithEMC \
        ROM_CAPT_processCycleWithEMC
#else
#define MAP_CAPT_processCycleWithEMC \
        CAPT_processCycleWithEMC
#endif

// ROM vs. FRAM Calling Macro for CAPT_updateElementFilteredValuesWithEMC() 
#ifdef ROM_CAPT_updateElementFilteredValuesWithEMC
#define MAP_CAPT_updateElementFilteredValuesWithEMC \
        ROM_CAPT_updateElementFilteredValuesWithEMC
#else
#define MAP_CAPT_updateElementFilteredValuesWithEMC \
        CAPT_updateElementFilteredValuesWithEMC
#endif

// ROM vs. FRAM Calling Macro for CAPT_updateSelfElementProxTouchWithEMC() 
#ifdef ROM_CAPT_updateSelfElementProxTouchWithEMC
#define MAP_CAPT_updateSelfElementProxTouchWithEMC \
        ROM_CAPT_updateSelfElementProxTouchWithEMC
#else
#define MAP_CAPT_updateSelfElementProxTouchWithEMC \
        CAPT_updateSelfElementProxTouchWithEMC
#endif

// ROM vs. FRAM Calling Macro for CAPT_updateProjElementProxTouchWithEMC() 
#ifdef ROM_CAPT_updateProjElementProxTouchWithEMC
#define MAP_CAPT_updateProjElementProxTouchWithEMC \
        ROM_CAPT_updateProjElementProxTouchWithEMC
#else
#define MAP_CAPT_updateProjElementProxTouchWithEMC \
        CAPT_updateProjElementProxTouchWithEMC
#endif

// ROM vs. FRAM Calling Macro for CAPT_registerTrackPadSensorProcessing() 
#ifdef ROM_CAPT_registerTrackPadSensorProcessing
#define MAP_CAPT_registerTrackPadSensorProcessing \
        ROM_CAPT_registerTrackPadSensorProcessing
#else
#define MAP_CAPT_registerTrackPadSensorProcessing \
        CAPT_registerTrackPadSensorProcessing
#endif

// ROM vs. FRAM Calling Macro for CAPT_registerTrackPadGestureProcessing() 
#ifdef ROM_CAPT_registerTrackPadGestureProcessing
#define MAP_CAPT_registerTrackPadGestureProcessing \
        ROM_CAPT_registerTrackPadGestureProcessing
#else
#define MAP_CAPT_registerTrackPadGestureProcessing \
        CAPT_registerTrackPadGestureProcessing
#endif

// ROM vs. FRAM Calling Macro for CAPT_initByteQueue() 
#ifdef ROM_CAPT_initByteQueue
#define MAP_CAPT_initByteQueue \
        ROM_CAPT_initByteQueue
#else
#define MAP_CAPT_initByteQueue \
        CAPT_initByteQueue
#endif

// ROM vs. FRAM Calling Macro for CAPT_pushOntoByteQueue() 
#ifdef ROM_CAPT_pushOntoByteQueue
#define MAP_CAPT_pushOntoByteQueue \
        ROM_CAPT_pushOntoByteQueue
#else
#define MAP_CAPT_pushOntoByteQueue \
        CAPT_pushOntoByteQueue
#endif

// ROM vs. FRAM Calling Macro for CAPT_pullFromByteQueue() 
#ifdef ROM_CAPT_pullFromByteQueue
#define MAP_CAPT_pullFromByteQueue \
        ROM_CAPT_pullFromByteQueue
#else
#define MAP_CAPT_pullFromByteQueue \
        CAPT_pullFromByteQueue
#endif

// ROM vs. FRAM Calling Macro for CAPT_getByteQueueSize() 
#ifdef ROM_CAPT_getByteQueueSize
#define MAP_CAPT_getByteQueueSize \
        ROM_CAPT_getByteQueueSize
#else
#define MAP_CAPT_getByteQueueSize \
        CAPT_getByteQueueSize
#endif

// ROM vs. FRAM Calling Macro for CAPT_isByteQueueFull() 
#ifdef ROM_CAPT_isByteQueueFull
#define MAP_CAPT_isByteQueueFull \
        ROM_CAPT_isByteQueueFull
#else
#define MAP_CAPT_isByteQueueFull \
        CAPT_isByteQueueFull
#endif

// ROM vs. FRAM Calling Macro for CAPT_isByteQueueEmpty() 
#ifdef ROM_CAPT_isByteQueueEmpty
#define MAP_CAPT_isByteQueueEmpty \
        ROM_CAPT_isByteQueueEmpty
#else
#define MAP_CAPT_isByteQueueEmpty \
        CAPT_isByteQueueEmpty
#endif

// ROM vs. FRAM Calling Macro for CAPT_initPingPongBuffer() 
#ifdef ROM_CAPT_initPingPongBuffer
#define MAP_CAPT_initPingPongBuffer \
        ROM_CAPT_initPingPongBuffer
#else
#define MAP_CAPT_initPingPongBuffer \
        CAPT_initPingPongBuffer
#endif

// ROM vs. FRAM Calling Macro for CAPT_togglePingPongBuffer() 
#ifdef ROM_CAPT_togglePingPongBuffer
#define MAP_CAPT_togglePingPongBuffer \
        ROM_CAPT_togglePingPongBuffer
#else
#define MAP_CAPT_togglePingPongBuffer \
        CAPT_togglePingPongBuffer
#endif

// ROM vs. FRAM Calling Macro for CAPT_getGeneralPurposePacket() 
#ifdef ROM_CAPT_getGeneralPurposePacket
#define MAP_CAPT_getGeneralPurposePacket \
        ROM_CAPT_getGeneralPurposePacket
#else
#define MAP_CAPT_getGeneralPurposePacket \
        CAPT_getGeneralPurposePacket
#endif

// ROM vs. FRAM Calling Macro for CAPT_getStringPacket() 
#ifdef ROM_CAPT_getStringPacket
#define MAP_CAPT_getStringPacket \
        ROM_CAPT_getStringPacket
#else
#define MAP_CAPT_getStringPacket \
        CAPT_getStringPacket
#endif

// ROM vs. FRAM Calling Macro for CAPT_getTrackPadPacket() 
#ifdef ROM_CAPT_getTrackPadPacket
#define MAP_CAPT_getTrackPadPacket \
        ROM_CAPT_getTrackPadPacket
#else
#define MAP_CAPT_getTrackPadPacket \
        CAPT_getTrackPadPacket
#endif

// ROM vs. FRAM Calling Macro for CAPT_accessSpecialSensorParameter() 
#ifdef ROM_CAPT_accessSpecialSensorParameter
#define MAP_CAPT_accessSpecialSensorParameter \
        ROM_CAPT_accessSpecialSensorParameter
#else
#define MAP_CAPT_accessSpecialSensorParameter \
        CAPT_accessSpecialSensorParameter
#endif

// ROM vs. FRAM Calling Macro for CAPT_getCyclePacket() 
#ifdef ROM_CAPT_getCyclePacket
#define MAP_CAPT_getCyclePacket \
        ROM_CAPT_getCyclePacket
#else
#define MAP_CAPT_getCyclePacket \
        CAPT_getCyclePacket
#endif

// ROM vs. FRAM Calling Macro for CAPT_getSensorPacket() 
#ifdef ROM_CAPT_getSensorPacket
#define MAP_CAPT_getSensorPacket \
        ROM_CAPT_getSensorPacket
#else
#define MAP_CAPT_getSensorPacket \
        CAPT_getSensorPacket
#endif

// ROM vs. FRAM Calling Macro for CAPT_getChecksum() 
#ifdef ROM_CAPT_getChecksum
#define MAP_CAPT_getChecksum \
        ROM_CAPT_getChecksum
#else
#define MAP_CAPT_getChecksum \
        CAPT_getChecksum
#endif

// ROM vs. FRAM Calling Macro for CAPT_verifyChecksum() 
#ifdef ROM_CAPT_verifyChecksum
#define MAP_CAPT_verifyChecksum \
        ROM_CAPT_verifyChecksum
#else
#define MAP_CAPT_verifyChecksum \
        CAPT_verifyChecksum
#endif

// ROM vs. FRAM Calling Macro for CAPT_stuffSyncBytes() 
#ifdef ROM_CAPT_stuffSyncBytes
#define MAP_CAPT_stuffSyncBytes \
        ROM_CAPT_stuffSyncBytes
#else
#define MAP_CAPT_stuffSyncBytes \
        CAPT_stuffSyncBytes
#endif

// ROM vs. FRAM Calling Macro for CAPT_processReceivedData() 
#ifdef ROM_CAPT_processReceivedData
#define MAP_CAPT_processReceivedData \
        ROM_CAPT_processReceivedData
#else
#define MAP_CAPT_processReceivedData \
        CAPT_processReceivedData
#endif

// ROM vs. FRAM Calling Macro for CAPT_accessSensorParameter() 
#ifdef ROM_CAPT_accessSensorParameter
#define MAP_CAPT_accessSensorParameter \
        ROM_CAPT_accessSensorParameter
#else
#define MAP_CAPT_accessSensorParameter \
        CAPT_accessSensorParameter
#endif

// ROM vs. FRAM Calling Macro for CAPT_accessTrackPadSensorParameter() 
#ifdef ROM_CAPT_accessTrackPadSensorParameter
#define MAP_CAPT_accessTrackPadSensorParameter \
        ROM_CAPT_accessTrackPadSensorParameter
#else
#define MAP_CAPT_accessTrackPadSensorParameter \
        CAPT_accessTrackPadSensorParameter
#endif

// ROM vs. FRAM Calling Macro for CAPT_getTrackPadSensorStatusPacket() 
#ifdef ROM_CAPT_getTrackPadSensorStatusPacket
#define MAP_CAPT_getTrackPadSensorStatusPacket \
        ROM_CAPT_getTrackPadSensorStatusPacket
#else
#define MAP_CAPT_getTrackPadSensorStatusPacket \
        CAPT_getTrackPadSensorStatusPacket
#endif

// ROM vs. FRAM Calling Macro for CAPT_initUI() 
#ifdef ROM_CAPT_initUI
#define MAP_CAPT_initUI \
        ROM_CAPT_initUI
#else
#define MAP_CAPT_initUI \
        CAPT_initUI
#endif

// ROM vs. FRAM Calling Macro for CAPT_calibrateUI() 
#ifdef ROM_CAPT_calibrateUI
#define MAP_CAPT_calibrateUI \
        ROM_CAPT_calibrateUI
#else
#define MAP_CAPT_calibrateUI \
        CAPT_calibrateUI
#endif

// ROM vs. FRAM Calling Macro for CAPT_updateUI() 
#ifdef ROM_CAPT_updateUI
#define MAP_CAPT_updateUI \
        ROM_CAPT_updateUI
#else
#define MAP_CAPT_updateUI \
        CAPT_updateUI
#endif

// ROM vs. FRAM Calling Macro for CAPT_getGlobalUIProximityStatus() 
#ifdef ROM_CAPT_getGlobalUIProximityStatus
#define MAP_CAPT_getGlobalUIProximityStatus \
        ROM_CAPT_getGlobalUIProximityStatus
#else
#define MAP_CAPT_getGlobalUIProximityStatus \
        CAPT_getGlobalUIProximityStatus
#endif

// ROM vs. FRAM Calling Macro for CAPT_ISR() 
#ifdef ROM_CAPT_ISR
#define MAP_CAPT_ISR \
        ROM_CAPT_ISR
#else
#define MAP_CAPT_ISR \
        CAPT_ISR
#endif

#endif // __ROM_MAP_CAPTIVATE_H__
