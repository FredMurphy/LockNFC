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
// UART.c
//
// \version 1.70.00.03
// Released on July 30, 2018
//
//*****************************************************************************
//*****************************************************************************
//! \addtogroup UART
//! @{
//*****************************************************************************

#include "UART.h"

#if (UART__ENABLE==true)

//*****************************************************************************
//
//! var g_pUARTPort stores a pointer to the UART port configuration
//! structure that was passed to the UART_openPort function.  The UART
//! driver does not modify this structure.
//
//*****************************************************************************
const tUARTPort *g_pUARTPort;

//*****************************************************************************
//
//! var g_pUARTTransmitPtr stores a pointer to the current byte to transmit.
//
//*****************************************************************************
volatile const uint8_t *g_pUARTTransmitPtr;

//*****************************************************************************
//
//! var g_ui16UARTTransmitBytesLeft stores how many bytes remain to be sent
//! in the current transmission.
//
//*****************************************************************************
volatile uint16_t g_ui16UARTTransmitBytesLeft;

//*****************************************************************************
//
//! var g_UARTStatus stores the current status of the UART port driver.
//
//*****************************************************************************
volatile uint8_t g_UARTStatus;

void UART_openPort(const tUARTPort *pPort)
{
	UART_closePort();
	g_pUARTPort = pPort;

	MAP_EUSCI_A_UART_init(
			UART__EUSCI_A_PERIPHERAL,
			(EUSCI_A_UART_initParam*)&(g_pUARTPort->peripheralParameters)
		);
	MAP_EUSCI_A_UART_enable(UART__EUSCI_A_PERIPHERAL);
	MAP_EUSCI_A_UART_clearInterrupt(
			UART__EUSCI_A_PERIPHERAL,
			EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG
		);
	MAP_EUSCI_A_UART_enableInterrupt(
			UART__EUSCI_A_PERIPHERAL,
			EUSCI_A_UART_RECEIVE_INTERRUPT
		);

	g_UARTStatus = eUARTIsIdle;
}

void UART_closePort(void)
{
	g_UARTStatus = eUARTIsClosed;
	MAP_EUSCI_A_UART_disable(UART__EUSCI_A_PERIPHERAL);
}

uint8_t UART_getPortStatus(void)
{
	return g_UARTStatus;
}

void UART_transmitBuffer(const uint8_t *pBuffer, uint16_t ui16Length)
{
	if (g_UARTStatus == eUARTIsClosed)
	{
		return;
	}
	
	//
	// Before transmitting, safely wait for
	// current operations to finish
	//
#if (UART__LPMx_bits>0)
	while (1)
	{
		__bic_SR_register(GIE);
		if (g_UARTStatus != eUARTIsIdle)
		{
			__bis_SR_register(UART__LPMx_bits | GIE);
		}
		else
		{
			__bis_SR_register(GIE);
			break;
		}
	};
#else
	while(g_UARTStatus != eUARTIsIdle);
#endif

	g_pUARTTransmitPtr = pBuffer;
	g_ui16UARTTransmitBytesLeft = ui16Length;
	g_UARTStatus = eUARTIsTransmitting;
	MAP_EUSCI_A_UART_enableInterrupt(
			UART__EUSCI_A_PERIPHERAL,
			EUSCI_A_UART_TRANSMIT_INTERRUPT
		);
}

extern void UART_transmitByteImmediately(uint8_t ui8Data)
{
	while(!(MAP_EUSCI_A_UART_getInterruptStatus(
					UART__EUSCI_A_PERIPHERAL, 
					EUSCI_A_UART_TRANSMIT_INTERRUPT_FLAG
				)
			));
	MAP_EUSCI_A_UART_transmitData(UART__EUSCI_A_PERIPHERAL, ui8Data);
};

//*****************************************************************************
//
//! UART Interrupt Service Routine
//
//*****************************************************************************

#pragma vector=UART__EUSCI_VECTOR
__interrupt void UART_ISR(void)
{
	uint8_t ui8Errors = 0;
	uint8_t ui8Data;

	switch (__even_in_range(UART__EUSCI_IV, USCI_UART_UCTXIFG))
	{
		case USCI_UART_UCRXIFG:
			ui8Errors = MAP_EUSCI_A_UART_queryStatusFlags(
					UART__EUSCI_A_PERIPHERAL,
					UART__ERROR_MASK
				);
			ui8Data = MAP_EUSCI_A_UART_receiveData(UART__EUSCI_A_PERIPHERAL);
			ui8Errors |= MAP_EUSCI_A_UART_queryStatusFlags(
					UART__EUSCI_A_PERIPHERAL,
					EUSCI_A_UART_OVERRUN_ERROR
				);
			if (g_pUARTPort->pbReceiveCallback != 0)
			{
				if(g_pUARTPort->pbReceiveCallback(ui8Data) == true)
				{
					__bic_SR_register_on_exit(UART__LPMx_bits);
				}
			}
			if (ui8Errors > 0)
			{
				if (g_pUARTPort->pbErrorCallback != 0)
				{
					if(g_pUARTPort->pbErrorCallback(ui8Errors) == true)
					{
						__bic_SR_register_on_exit(UART__LPMx_bits);
					}
				}
			}
			break;

		case USCI_UART_UCTXIFG:
			MAP_EUSCI_A_UART_transmitData(
					UART__EUSCI_A_PERIPHERAL,
					*(g_pUARTTransmitPtr++)
				);
			g_ui16UARTTransmitBytesLeft--;

			if (g_ui16UARTTransmitBytesLeft == 0)
			{
				MAP_EUSCI_A_UART_disableInterrupt(
						UART__EUSCI_A_PERIPHERAL,
						EUSCI_A_UART_TRANSMIT_INTERRUPT
					);
				g_UARTStatus = eUARTIsIdle;
				__bic_SR_register_on_exit(UART__LPMx_bits);
			}
			break;
	}
}

#endif /* UART__ENABLE==true */
//*****************************************************************************
//! Close the doxygen group
//! @}
//*****************************************************************************
