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
// CAPT_Manager.c
//
// version 1.70.00.03
// Released on July 30, 2018
//
//*****************************************************************************
//*****************************************************************************
//! \addtogroup CAPT_Manager
//! @{
//*****************************************************************************

#include "CAPT_Type.h"
#include "CAPT_HAL.h"
#include "CAPT_Touch.h"
#include "CAPT_Calibration.h"
#include "CAPT_Interface.h"
#include "rom_captivate.h"
#include "rom_map_captivate.h"
#include "CAPT_UserConfig.h"

#include "CAPT_Manager.h"

//
// Link in the appropriate sensor functions based on whether
// EMC (noise immunity) is enabled.  When EMC is enabled
// via CAPT_CONDUCTED_NOISE_IMMUNITY_ENABLE,
// specific function calls are used as additional signal
// processing is performed.
//
#if defined(CAPT_CAL_ALG) && (CAPT_CAL_ALG==__CAPT_MAXOFFSET_CALIBRATION__)
#if (CAPT_CONDUCTED_NOISE_IMMUNITY_ENABLE==false)
#define CAPT_MANAGER_CALIBRATE_SENSOR(sensor) CAPT_calibrateSensorWithMaxOffset(sensor)
#else
#define CAPT_MANAGER_CALIBRATE_SENSOR(sensor) CAPT_calibrateSensorWithMaxOffsetWithEMC(sensor)
#endif  // CAPT_CONDUCTED_NOISE_IMMUNITY_ENABLE
#else // STD Calibration
#if (CAPT_CONDUCTED_NOISE_IMMUNITY_ENABLE==false)
#define CAPT_MANAGER_CALIBRATE_SENSOR(sensor) CAPT_calibrateSensor(sensor)
#else
#define CAPT_MANAGER_CALIBRATE_SENSOR(sensor) CAPT_calibrateSensorWithEMC(sensor)
#endif  // CAPT_CONDUCTED_NOISE_IMMUNITY_ENABLE
#endif  // CAPT_CAL_ALG

//
// Link the appropriate sensor update functions based on whether
// EMC (noise immunity) is enabled.  When EMC is enabled
// via CAPT_CONDUCTED_NOISE_IMMUNITY_ENABLE,
// specific function calls are used as additional signal
// processing is performed.
//
#if (CAPT_CONDUCTED_NOISE_IMMUNITY_ENABLE==false)
#define CAPT_MANAGER_UPDATE_SENSOR(sensor, lpm) CAPT_updateSensor(sensor, lpm)
#else
#define CAPT_MANAGER_UPDATE_SENSOR(sensor, lpm) CAPT_updateSensorWithEMC(sensor, lpm)
#endif  // CAPT_CONDUCTED_NOISE_IMMUNITY_ENABLE

void CAPT_initUI(tCaptivateApplication *pApp)
{
    uint8_t ui8SensorID;

    //
    // Power up the Captivate peripheral, and initialize standard operating
    // parameters via CAPT_init().
    //
    MAP_CAPT_powerOn();
    CAPT_init();

    //
    // Loop through all of the sensors in the application pointed to by
    // pApp.  For each sensor, initialize and enable the Captivate IO
    // and init the sensor.
    //
    for (ui8SensorID=0; ui8SensorID<pApp->ui8NrOfSensors; ui8SensorID++)
    {
        MAP_CAPT_initSensorIO(pApp->pSensorList[ui8SensorID]);
        MAP_CAPT_enableSensorIO(pApp->pSensorList[ui8SensorID]);
        CAPT_initSensor(pApp->pSensorList[ui8SensorID]);

#if(CAPT_TRACKPAD_ENABLE==true)
        if((pApp->pSensorList[ui8SensorID]->TypeOfSensor) == eTrackpad)
        {
            // Register default Trackpad processing callback.  User can write their own and substitute.
            CAPT_registerTrackPadSensorProcessing(pApp->pSensorList[ui8SensorID], &CAPT_processTrackPadSensor);

            // Register default Trackpad gesture processing callback.  User can write their own and substitute.
            // To disable gestures, substitute 'NULL' for function parameter name. 
            CAPT_registerTrackPadGestureProcessing(pApp->pSensorList[ui8SensorID], &CAPT_processTrackPadGesture);
        }
#endif  // CAPT_TRACKPAD_ENABLE
    }

    //
    // If a communications interface is enabled,
    // initialize it here.  CAPT_initCommInterface() assumes
    // that the required ports have already been muxed.
    //
#if (CAPT_INTERFACE!=__CAPT_NO_INTERFACE__)
    CAPT_initCommInterface(pApp);
#endif  // CAPT_INTERFACE
}

void CAPT_calibrateUI(tCaptivateApplication *pApp)
{
    uint8_t ui8SensorID;

    //
    // Loop through all of the sensors in the application pointed to by
    // pApp.  For each sensor, call the appropriate calibration routine via
    // the calibration macro.
    //
    for (ui8SensorID=0; ui8SensorID<pApp->ui8NrOfSensors; ui8SensorID++)
    {
        CAPT_MANAGER_CALIBRATE_SENSOR(pApp->pSensorList[ui8SensorID]);
    }
}

void CAPT_updateUI(tCaptivateApplication *pApp)
{
    uint8_t ui8SensorID;

    //
    // Loop through all of the sensors in the application pointed to by
    // pApp.  For each sensor, update/refresh all of its values via
    // the appropriate sensor update fxn, check for any required re-calibrations,
    // and if enabled, write the new data out of the serial interface.
    //
    for (ui8SensorID=0; ui8SensorID<(pApp->ui8NrOfSensors); ui8SensorID++)
    {
        //
        // Update the sensor via the update sensor macro,
        // which selected the appropriate sensor update fxn based on
        // whether or not EMC (noise immunity) is enabled.
        //
        CAPT_MANAGER_UPDATE_SENSOR(
                pApp->pSensorList[ui8SensorID],
                pApp->ui8AppLPM
                );

        //
        // If the UART or Bulk I2C interface is enabled, write out element
        // and sensor data here.
        //
#if ((CAPT_INTERFACE==__CAPT_UART_INTERFACE__)||\
    (CAPT_INTERFACE==__CAPT_BULKI2C_INTERFACE__))
        CAPT_writeElementData(ui8SensorID);
        CAPT_writeSensorData(ui8SensorID);

        // If trackpad enabled, check if sensor is trackpad, then
        // send trackpad specific data to the design center.
#if (CAPT_TRACKPAD_ENABLE == true)
        if((pApp->pSensorList[ui8SensorID]->TypeOfSensor) == eTrackpad)
        {
            CAPT_writeTrackPadSensorStatus(ui8SensorID);
            CAPT_writeTrackPadSensorData(ui8SensorID);
        }
#endif  // CAPT_TRACKPAD_ENABLE
#endif  // CAPT_INTERFACE

        //
        // Test the sensor to see if it has drifted out of the specified
        // operating range and needs to be re-calibrated.  If it requires
        // re-calibration,call the appropriate calibration routine via the
        // calibrate sensor macro, which selects the fxn based on whether
        // or not EMC (noise immunity) is enabled.
        //
        if ((MAP_CAPT_testForMaxCountRecalibration(pApp->pSensorList[ui8SensorID]) == true) ||\
            (MAP_CAPT_testForNegativeTouchRecalibration(pApp->pSensorList[ui8SensorID]) == true) ||\
            (MAP_CAPT_testForRecalibration(pApp->pSensorList[ui8SensorID]) == true))
        {
            CAPT_MANAGER_CALIBRATE_SENSOR(pApp->pSensorList[ui8SensorID]);
        }
    } // End of sensor for loop
}

bool CAPT_getGlobalUIProximityStatus(tCaptivateApplication *pApp)
{
    uint8_t ui8SensorID;

    for (ui8SensorID=0; ui8SensorID<pApp->ui8NrOfSensors; ui8SensorID++)
    {
        //
        // If any sensor exhibits a proximity detection, return true.
        //
        if (pApp->pSensorList[ui8SensorID]->bSensorProx == true)
        {
            return true;
        }
    }

    return false;
}

//*****************************************************************************
//
//! Close the doxygen group
//! @}
//
//*****************************************************************************

