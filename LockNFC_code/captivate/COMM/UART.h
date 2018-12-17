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
// UART.h
//
//! UART driver module for the eUSCI_A UART peripheral.
//
//! This is the UART port driver header file.  This driver enables interrupt
//! driven, full-duplex UART communication via a simple API.  The UART port
//! driver requires one eUSCI_A instance, and is built on top of the
//! MSP430 DriverLib version 2.10.00.00 or greater.
//
//! \version 1.70.00.03
//! Released on July 30, 2018
//
//*****************************************************************************
//*****************************************************************************
//! \addtogroup UART
//! @{
//*****************************************************************************

#ifndef UARTDRIVER_H_
#define UARTDRIVER_H_

#include "UART_Definitions.h"

#if (UART__ENABLE==true)

//*****************************************************************************
//
//! def UART__EUSCI_VECTOR defines the interrupt vector location
//! of the selected eUSCI_A UART peripheral.
//
//! def UART__EUSCI_IV defines the interrupt vector of the selected
//! eUSCI_A UART peripheral.
//
//*****************************************************************************
#if (UART__EUSCI_A_PERIPHERAL == EUSCI_A0_BASE)
#define UART__EUSCI_VECTOR     	(USCI_A0_VECTOR)
#define UART__EUSCI_IV    	 	(UCA0IV)
#elif (UART__EUSCI_A_PERIPHERAL == EUSCI_A1_BASE)
#define UART__EUSCI_VECTOR     	(USCI_A1_VECTOR)
#define UART__EUSCI_IV     		(UCA1IV)
#else
#error INVALID_EUSCI_A_SELECTION
#endif

//*****************************************************************************
//
//! def UART__ERROR_MASK defines the error bits from the eUSCI_A peripheral
//! that cause an error callback to occur.  The errors communicated are
//! UCOE and UCFE for overrun errors and framing errors, respectivly.
//
//*****************************************************************************
#define UART__ERROR_MASK		(0x60)

//*****************************************************************************
//
//! \typedef tUARTPort defines the port definition that the user must
//! provide when instantiating this driver.  This structure is read-only from
//! the context of the driver, and may be placed in read-only memory, such as
//! the C CONST section, if desired.
//
//*****************************************************************************
typedef struct
{
	//
	//! Receive Callback.  This function will be called
	//! after each UART byte is received.  This fxn is called
	//! from the foreground (ISR), and as such it should be kept
	//! as short as possible.
	//
	bool (*pbReceiveCallback)(uint8_t);

	//
	//! Error Callback.  This function will be called after
	//! a UART error is detected.  The passed tUARTErrors
	//! parameter indicates what caused the error.
	//
	bool (*pbErrorCallback)(uint8_t);

	//
	//! eUSCI_A initialization parameters.  This structure
	//! is defined in the MSP430 peripheral driver library.
	//
	EUSCI_A_UART_initParam peripheralParameters;

} tUARTPort;

//*****************************************************************************
//
//! \enum tUARTStates enumerates the possible UART driver states.
//
//*****************************************************************************
enum tUARTStates {
	eUARTIsClosed,
	eUARTIsIdle,
	eUARTIsTransmitting
};

//*****************************************************************************
//
//! \enum tUARTErrors enumerates the possible UART driver errors.
//! These error codes are passed to the error callback function.
//
//*****************************************************************************
enum tUARTErrors {
	eUARTFramingError = 0x40,
	eUARTOverrunError = 0x20
};

//*****************************************************************************
//
//! This API opens the UART port on the specified HW eUSCI_A peripheral.
//! This API must be called before the port is used.
//
//! \param pPort is a pointer to the UART Port configuration
//! structure.  The user must populate and provide this structure to the
//! port driver.  The data structure must remain at the same address
//! throughout the operation of the driver.
//! \return none
//
//*****************************************************************************
extern void UART_openPort(const tUARTPort *pPort);

//*****************************************************************************
//
//! This API closes the UART port on the specified HW eUSCI_A peripheral.
//
//!  \par Parameters
//!		none
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void UART_closePort(void);

//*****************************************************************************
//
//! This API returns the status of the UART port when called.  The possible
//! statuses are enumerated under tUARTStates.
//
//!  \par Parameters
//!		none
//! \return tUARTStates enumeration indicating the current status.
//
//*****************************************************************************
extern uint8_t UART_getPortStatus(void);

//*****************************************************************************
//
//! This API begins transmission of the buffer pointed to as soon as the
//! UART hardware resources are available.  If a previous transmission is
//! still in progress, this function will block until it is complete.
//! The blocking may take place in a low power mode if desired by
//! configuring UART__LPMx_bits in the UART_Definitions.h header file.
//
//! \param pBuffer is a pointer to the buffer to transmit
//! \param ui16Length indicates the valid byte length of the buffer to transmit
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void UART_transmitBuffer(const uint8_t *pBuffer, uint16_t ui16Length);

//*****************************************************************************
//
//! This function transmits a single byte of data as soon as the UART
//! peripheral is available.  It blocks until this time.  This function is
//! useful for terminal emulators where keystrokes should be echoed.
//
//! \param ui8Data is the single byte of data to send
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void UART_transmitByteImmediately(uint8_t ui8Data);

#endif /* UART__ENABLE==true */

#endif /* UARTDRIVER_H_ */
//*****************************************************************************
//! Close the doxygen group
//! @}
//*****************************************************************************
