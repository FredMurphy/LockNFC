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
// CAPT_App.c
//
//! \version 1.70.00.03
//! Released on July 30, 2018
//
//*****************************************************************************

#include "captivate.h"

//*****************************************************************************
//
//! \def Define CAPT_WOP_VLO_LPM4 in order to use the very low power oscillator
//! (VLO) as the conversion timer in wake-on-proximity mode.  If this option
//! is defined, LPM4 will be selected as the power mode, disabling ACLK and
//! along with it XT1 or the REFO, whichever was sourcing ACLK previously,
//! while the system is in WOP mode.  When WOP mode is exited and active
//! mode is entered, ACLK will again be utilized to source the conversion timer
//! and the application-selected low power mode (g_uiApp.ui8AppLPM) will be
//! used until WOP mode is again entered.
//!
//! This option may be used to reduce the average current in wake-on-proximity
//! mode for designs that do not have a crystal oscillator.
//! If CAPT_WOP_VLO_LPM4 should be defined only if no CapTIvate COMM interface
//! is selected (CAPT_INTERFACE == __CAPT_NO_INTERFACE__).
//!
//! Note that if this mode is selected and the VLO is used, the tolerance
//! on the measured scan period will be poor.  For example, if 10 Hz (100ms)
//! is the selected WOP scan rate, this value may vary by as much as +/- 5 Hz
//! across temperature and voltage.  If this variance is too great for the
//! application requirements, a 32kHz crystal or the REFO should be
//! used instead.
//
//*****************************************************************************

#ifdef CAPT_WOP_VLO_LPM4
//*****************************************************************************
//! \var g_ui8SavedAppLPM
//! This variable is used as a context saving byte to recall the desired
//! app low power mode in active operation.  When in wake on proximity mode,
//! LPM4 will be used and the VLO will source the CapTIvate conversion
//! timer directly.  This variable is only included in the build when
//! CAPT_WOP_VLO_LPM4 is defined.
//
//*****************************************************************************
static uint8_t g_ui8SavedAppLPM;
#endif  // CAPT_WOP_VLO_LPM4

void CAPT_appStart(void)
{
    //
    // Initialize the user interface.
    // This function call enables the CapTIvate peripheral,
    // initializes and enables the capacitive touch IO.
    //
    CAPT_initUI(&g_uiApp);

    //
    // Load the EMC configuration, if this design has
    // noise immunity features enabled.  This function call
    // associates an EMC configuration with the EMC module.
    //
#if (CAPT_CONDUCTED_NOISE_IMMUNITY_ENABLE==true)
    CAPT_loadEMCConfig(&g_EMCConfig);
#endif  // CAPT_CONDUCTED_NOISE_IMMUNITY_ENABLE

    //
    // Calibrate the user interface.  This function establishes
    // coarse gain, fine gain, and offset tap tuning settings for
    // each element in the user interface.
    //
    CAPT_calibrateUI(&g_uiApp);

    //
    // Setup Captivate timer
    // This timer sets the g_bConvTimerFlag in the Captivate
    // library at the interval specified by CAPT_SCAN_INTERVAL.
    // This is used to trigger the app handler to update
    // the capacitive user interface.
    //
    MAP_CAPT_stopTimer();
    MAP_CAPT_clearTimer();
    MAP_CAPT_selectTimerSource(CAPT_TIMER_SRC_ACLK);
    MAP_CAPT_selectTimerSourceDivider(CAPT_TIMER_CLKDIV__1);
    MAP_CAPT_writeTimerCompRegister(CAPT_MS_TO_CYCLES(g_uiApp.ui16ActiveModeScanPeriod));
    MAP_CAPT_startTimer();
    MAP_CAPT_enableISR(CAPT_TIMER_INTERRUPT);

#ifdef CAPT_WOP_VLO_LPM4
    g_ui8SavedAppLPM  = g_uiApp.ui8AppLPM;
#endif  // CAPT_WOP_VLO_LPM4
}

bool CAPT_appHandler(void)
{
#if (CAPT_WAKEONPROX_ENABLE==true)
    static uint16_t g_ui16UISessionTimeoutCtr = 1;
#endif  // CAPT_WAKEONPROX_ENABLE
    static bool bActivity = false;

    switch (g_uiApp.state)
    {
        case eUIActive:
        case eUIActiveNoTouch:
            if (g_bConvTimerFlag == true)
            {
                //
                // Clear the conversion timer flag,
                // and update the UI
                //
                g_bConvTimerFlag = false;
                CAPT_updateUI(&g_uiApp);
                bActivity = CAPT_getGlobalUIProximityStatus(&g_uiApp);

                //
                // If autonomous mode is enabled, check to
                // see if autonomous mode should be entered.
                //
#if (CAPT_WAKEONPROX_ENABLE==true)
                if (bActivity == true)
                {
                    //
                    // If there is still a prox detection,
                    // reset the session timeout counter.
                    //
                    g_ui16UISessionTimeoutCtr = g_uiApp.ui16InactivityTimeout;
                }
                else if (--g_ui16UISessionTimeoutCtr == 0)
                {
                    //
                    // If the session has timed out,
                    // enter autonomous mode
                    //
                    g_uiApp.state = eUIWakeOnProx;
                    bActivity = false;

                    //
                    // Set the timer period for wake on touch interval
                    //
                    MAP_CAPT_disableISR(CAPT_TIMER_INTERRUPT);
                    MAP_CAPT_stopTimer();
                    MAP_CAPT_clearTimer();
#ifndef CAPT_WOP_VLO_LPM4
                    MAP_CAPT_writeTimerCompRegister(CAPT_MS_TO_CYCLES(g_uiApp.ui16WakeOnProxModeScanPeriod));
#else
                    MAP_CAPT_selectTimerSource(CAPT_TIMER_SRC_VLOCLK);
                    MAP_CAPT_writeTimerCompRegister(CAPT_MS_TO_CYCLES_VLO(g_uiApp.ui16WakeOnProxModeScanPeriod));
                    g_uiApp.ui8AppLPM = LPM4_bits;
#endif  // CAPT_WOP_VLO_LPM4
                    MAP_CAPT_startTimer();
                    g_bConvTimerFlag = false;
                    CAPT_startWakeOnProxMode(
                            &CAPT_WAKEONPROX_SENSOR,
                            0,
                            g_uiApp.ui8WakeupInterval
                            );
                }
#endif  // CAPT_WAKEONPROX_ENABLE
            }
            break;

        case eUIWakeOnProx:
#if (CAPT_WAKEONPROX_ENABLE==true)
            if (g_bDetectionFlag || g_bConvCounterFlag || g_bMaxCountErrorFlag)
            {
                //
                // If a detection, conversion counter, or max count error flag was set,
                // stop autonomous mode and reload an active session
                //
                CAPT_stopWakeOnProxMode(&CAPT_WAKEONPROX_SENSOR, 0);
                g_uiApp.state = g_bDetectionFlag ? eUIActive : eUIActiveNoTouch;
                g_bDetectionFlag = false;
                g_bConvCounterFlag = false;
                g_bMaxCountErrorFlag = false;
                g_ui16UISessionTimeoutCtr = g_uiApp.ui16InactivityTimeout;

                //
                // Set the timer period for normal scan interval
                //
                MAP_CAPT_disableISR(CAPT_TIMER_INTERRUPT);
                MAP_CAPT_stopTimer();
                MAP_CAPT_clearTimer();
#ifdef CAPT_WOP_VLO_LPM4
                MAP_CAPT_selectTimerSource(CAPT_TIMER_SRC_ACLK);
                g_uiApp.ui8AppLPM = g_ui8SavedAppLPM;
#endif  // CAPT_WOP_VLO_LPM4
                MAP_CAPT_writeTimerCompRegister(CAPT_MS_TO_CYCLES(g_uiApp.ui16ActiveModeScanPeriod));

                MAP_CAPT_startTimer();
                CAPT_clearIFG(CAPT_TIMER_INTERRUPT);
                MAP_CAPT_enableISR(CAPT_TIMER_INTERRUPT);
            }
#endif  // CAPT_WAKEONPROX_ENABLE
            break;
    }

#if ((CAPT_INTERFACE==__CAPT_UART_INTERFACE__) ||\
        (CAPT_INTERFACE==__CAPT_BULKI2C_INTERFACE__))
    //
    // If communications are enabled, check for any incoming packets.
    //
    CAPT_checkForInboundPacket();

    //
    // Check to see if the packet requested a re-calibration.
    // If wake-on-prox is enabled and the current application state
    // is wake-on-prox, disable the wake-on-prox feature during the calibration
    // and re-enable it after the calibration.
    //
    if (CAPT_checkForRecalibrationRequest() == true)
    {
#if (CAPT_WAKEONPROX_ENABLE==true)
        if (g_uiApp.state == eUIWakeOnProx)
        {
            CAPT_stopWakeOnProxMode(
                    &CAPT_WAKEONPROX_SENSOR,
                    0
                    );
            CAPT_calibrateUI(&g_uiApp);
            CAPT_startWakeOnProxMode(
                    &CAPT_WAKEONPROX_SENSOR,
                    0,
                    g_uiApp.ui8WakeupInterval
                    );
        }
        else
        {
            CAPT_calibrateUI(&g_uiApp);
        }
#else
        CAPT_calibrateUI(&g_uiApp);
#endif  // CAPT_WAKEONPROX_ENABLE
    }
#endif  // CAPT_INTERFACE

    return bActivity;
}

void CAPT_appSleep(void)
{
    //
    // If no captivate flags are set, enter the application's low power
    // mode.  Otherwise, re-enter the background loop immediately.
    //
    //__bic_SR_register(GIE);
    if (!(g_bConvTimerFlag ||g_bDetectionFlag || g_bConvCounterFlag || g_bMaxCountErrorFlag))
    {
        __bis_SR_register(g_uiApp.ui8AppLPM | GIE);
    }
    else
    {
        __bis_SR_register(GIE);
    }
}

