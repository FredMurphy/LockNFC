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
// I2CSlave_Definitions.h
//
//! This is the I2C slave definitions file.  This file sets the configuration
//! parameters for the I2C slave port.
//
//! \version 1.70.00.03
//! Released on July 30, 2018
//
//*****************************************************************************
//*****************************************************************************
//! \addtogroup I2CSlave
//! @{
//*****************************************************************************

#ifndef I2CSLAVE_DEFINITIONS_H_
#define I2CSLAVE_DEFINITIONS_H_

#include "rom_driverlib.h"
#include "rom_map_driverlib.h"
#include "driverlib.h"

//
//! CAPT_CommConfig is used to control I2C__ENABLE.
//
#include "CAPT_CommConfig.h"

//*****************************************************************************
//
//! \def I2CSLAVE__ENABLE controls whether the I2C slave port is included
//! during build.  To use the I2C slave port, set this definition to true.
//
//*****************************************************************************
// NOTE: Rather than enabling I2C Slave here, the enable is controlled in
// CAPT_CommConfig.
//#define I2CSLAVE__ENABLE				                                 (true)

//*****************************************************************************
//
//! \def I2CSLAVE__EUSCI_B_PERIPHERAL defines the MSP430 base address of the
//! eUSCI_B instance being used with this I2C slave port.
//
//! \def I2CSLAVE__ADDRESS defines the I2C bus address associated with this
//! device.
//
//*****************************************************************************
#define I2CSLAVE__EUSCI_B_PERIPHERAL	                        (EUSCI_B0_BASE)
#define I2CSLAVE__ADDRESS				                                 (0x0A)

//*****************************************************************************
//
//! \def I2CSLAVE__LPMx_bits defines the low power mode to enter
//! when pending on a resource.
//
//*****************************************************************************
#define I2CSLAVE__LPMx_bits				                            (LPM3_bits)

//*****************************************************************************
//
//! \def I2CSLAVE__INVALID_BYTE is sent when a master continues to read out
//! data past the valid length of the transmit buffer.
//
//*****************************************************************************
#define I2CSLAVE__INVALID_BYTE			                                 (0xFF)

//*****************************************************************************
//
//! \def I2CSLAVE__TIMEOUT_ENABLE controls whether the I2C timeout
//! feature is included.
//
//! \def I2CSLAVE__REQ_TIMEOUT_CYCLES defines how long to wait when requesting
//! the bus master to perform a read operation. The default value is 2ms.
//
//! \def I2CSLAVE__TXFR_TIMEOUT_CYCLES defines how ling to wait for a transfer
//! to complete before terminating it (due to a possible bus disconnect).
//! The default value is 8ms.
//
//*****************************************************************************
#define I2CSLAVE__TIMEOUT_ENABLE		                                 (true)
#define I2CSLAVE__REQ_TIMEOUT_CYCLES	                                   (66)
#define I2CSLAVE__TXFR_TIMEOUT_CYCLES	                                  (264)

//*****************************************************************************
//
//! The I2C request line is the mechanism by which the I2C slave (this device)
//! may alert the I2C bus master that data is waiting to be read.
//! the I2C request line is open-drain and active low, and requires a pull-up
//! resistor.
//
//! \def I2CSLAVE__REQ_POUT defines the I2C request line port output reg.
//
//! \def I2CSLAVE__REQ_PDIR defines the I2C request line port direction reg.
//
//! \def I2CSLAVE__REQ_MASK defines the I2C request line pin mask.
//
//*****************************************************************************
// NOTE: Rather than selecting the I2C IRQ IO here, the enable is controlled in
// CAPT_CommConfig.
//#define I2CSLAVE__REQ_POUT				                            (P1OUT)
//#define I2CSLAVE__REQ_PDIR				                            (P1DIR)
//#define I2CSLAVE__REQ_MASK				                             (BIT1)

//*****************************************************************************
//! Close the doxygen group
//! @}
//*****************************************************************************

#endif /* I2CSLAVE_DEFINITIONS_H_ */
