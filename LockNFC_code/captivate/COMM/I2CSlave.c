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
// I2CSlave.c
//
// \version 1.70.00.03
// Released on July 30, 2018
//
//*****************************************************************************
//*****************************************************************************
//! \addtogroup I2CSlave
//! @{
//*****************************************************************************

#include "I2CSlave.h"

#if (I2CSLAVE__ENABLE==true)

#if (I2CSLAVE__TIMEOUT_ENABLE==true)
#include "FunctionTimer.h"
#endif /* I2CSLAVE__TIMEOUT_ENABLE==true */

//*****************************************************************************
//
//! var g_pI2CSlavePort stores a pointer to the I2C slave port configuration
//! structure that was passed to the I2CSlave_openPort function.  The I2C
//! slave driver does not modify this structure.
//
//*****************************************************************************
const tI2CSlavePort *g_pI2CSlavePort;

//*****************************************************************************
//
//! var g_I2CSlaveConfiguration stores the MSP430 DriverLib EUSCI_B_I2C
//! configuration parameters for the EUSCI_B_I2C_initSlave() function call.
//
//*****************************************************************************
const EUSCI_B_I2C_initSlaveParam g_I2CSlaveConfiguration =
{
	.slaveAddress = I2CSLAVE__ADDRESS,
	.slaveAddressOffset = EUSCI_B_I2C_OWN_ADDRESS_OFFSET0,
	.slaveOwnAddressEnable = EUSCI_B_I2C_OWN_ADDRESS_ENABLE
};

//*****************************************************************************
//
//! var g_pI2CTransmitBuffer stores a pointer to the current transmit buffer.
//
//*****************************************************************************
const uint8_t *g_pI2CTransmitBuffer;

//*****************************************************************************
//
//! var g_ui16I2CLength stores the valid data length of the data pointed
//! to by g_pI2CTransmitBuffer.
//
//*****************************************************************************
uint16_t g_ui16I2CLength;

//*****************************************************************************
//
//! var g_ui16I2CIndex stores the current transmit or receive buffer index.
//
//*****************************************************************************
volatile uint16_t g_ui16I2CIndex;

//*****************************************************************************
//
//! var g_I2CSlaveStatus stores the current status of the I2C slave port.
//! possible options are enumerated in tI2CSlaveStates.
//
//*****************************************************************************
volatile uint8_t g_I2CSlaveStatus = eI2CSlaveIsClosed;

//*****************************************************************************
//
//! var g_bI2CSlaveRequestPending indicates whether or not a read
//! operation is currently pending on the I2C bus master.
//
//*****************************************************************************
volatile bool g_bI2CSlaveRequestPending;

//*****************************************************************************
//
//! This function is for private use only.  This is called by the I2C Slave
//! ISR when a receive (I2C write to this slave) operation is completed,
//! which is indicated either by a stop condition or a repeated start
//! condition.  This function handles receiving the last byte of data (if
//! present) and calling the receive callback in the user's application,
//! if one is registered.
//
//!  \par Parameters
//!		none
//! \return true if the ISR should exit active (per the callback), else false.
//
//*****************************************************************************
static bool I2CSlave_handleEndOfReceive(void);

#if (I2CSLAVE__TIMEOUT_ENABLE==true)

static bool I2CSlave_requestTimeoutHandler(void)
{
	//
	// If this function is called, the slave request to the master
	// has timed out.  This function cancels the request here
	// and notifies the application via the error callback.
	//
	g_bI2CSlaveRequestPending = false;
	if (g_pI2CSlavePort->pvErrorCallback != 0)
	{
		g_pI2CSlavePort->pvErrorCallback(eI2CSlaveTransmitRequestTimeout);
	}
	return true;
}

static bool I2CSlave_transactionTimeoutHandler(void)
{
	//
	// If this function is called, an I2C transaction with the master
	// has timed out.  This function resets the I2C port,
	// and notifies the application via the error callback.
	//
	I2CSlave_openPort(g_pI2CSlavePort);
	if (g_pI2CSlavePort->pvErrorCallback != 0)
	{
		g_pI2CSlavePort->pvErrorCallback(eI2CSlaveTransactionTimeout);
	}
	return true;
}

//*****************************************************************************
//
//! var g_I2CSlaveFunctionTimer contains the function timer configuration
//! for the two I2C timeout events-  a slave request timeout (Fxn A)
//! and an I2C transaction timeout (Fxn B)
//
//*****************************************************************************
const tFunctionTimer g_I2CSlaveFunctionTimer =
{
	.pbFunction_A = &I2CSlave_requestTimeoutHandler,
	.pbFunction_B = &I2CSlave_transactionTimeoutHandler,
	.ui16FunctionDelay_A = I2CSLAVE__REQ_TIMEOUT_CYCLES,
	.ui16FunctionDelay_B = I2CSLAVE__TXFR_TIMEOUT_CYCLES
};

#endif /* I2CSLAVE__TIMEOUT_ENABLE==true */

void I2CSlave_openPort(const tI2CSlavePort *pPort)
{
	I2CSlave_closePort();
	g_pI2CSlavePort = pPort;
	g_bI2CSlaveRequestPending = false;

#if (I2CSLAVE__TIMEOUT_ENABLE==true)
	Timer_startDelayedFunctionTimer(&g_I2CSlaveFunctionTimer);
#endif /* I2CSLAVE__TIMEOUT_ENABLE==true */

	MAP_EUSCI_B_I2C_initSlave(
			I2CSLAVE__EUSCI_B_PERIPHERAL,
			(EUSCI_B_I2C_initSlaveParam*)&g_I2CSlaveConfiguration
		);
	MAP_EUSCI_B_I2C_enable(I2CSLAVE__EUSCI_B_PERIPHERAL);
	MAP_EUSCI_B_I2C_clearInterrupt(I2CSLAVE__EUSCI_B_PERIPHERAL,I2CSLAVE__INT_MASK);
	MAP_EUSCI_B_I2C_enableInterrupt(I2CSLAVE__EUSCI_B_PERIPHERAL, I2CSLAVE__INT_MASK);

	I2C__INIT_REQ_SIGNAL;

	g_I2CSlaveStatus = eI2CSlaveIsIdle;
}


void I2CSlave_closePort(void)
{
	MAP_EUSCI_B_I2C_disable(I2CSLAVE__EUSCI_B_PERIPHERAL);
	g_I2CSlaveStatus = eI2CSlaveIsClosed;
#if (I2CSLAVE__TIMEOUT_ENABLE==true)
	Timer_stopDelayedFunctionTimer();
#endif /* I2CSLAVE__TIMEOUT_ENABLE==true */
}

uint8_t I2CSlave_getPortStatus(void)
{
	return g_I2CSlaveStatus;
}

void I2CSlave_setTransmitBuffer(uint8_t *pBuffer, uint16_t ui16Length)
{
	//
	// Before setting the transmit buffer, safely wait for
	// current read operations to finish
	//
#if (I2CSLAVE__LPMx_bits>0)
	while (1)
	{
		__bic_SR_register(GIE);
		if ((g_I2CSlaveStatus == eI2CSlaveIsBeingRead)
					|| (g_bI2CSlaveRequestPending==true))
		{
			__bis_SR_register(I2CSLAVE__LPMx_bits | GIE);
		}
		else
		{
			__bis_SR_register(GIE);
			break;
		}
	};
#else
	{
		while((g_I2CSlaveStatus == eI2CSlaveIsBeingRead)|| (g_bI2CSlaveRequestPending==true));
	}
#endif

	//
	// Update the transmit buffer and length.
	//
	g_ui16I2CLength = ui16Length;
	g_pI2CTransmitBuffer = pBuffer;
}

void I2CSlave_setRequestFlag(void)
{
	g_bI2CSlaveRequestPending = true;
	I2C__PULL_REQ_SIGNAL;

	//
	// If the slave timeout feature is enabled,
	// schedule a request flag timeout function
	//
#if (I2CSLAVE__TIMEOUT_ENABLE==true)
	Timer_scheduleDelayedFunction(eTimerDelayedFunction_A);
#endif /* I2CSLAVE__TIMEOUT_ENABLE==true */

	//
	// Before exiting the fxn,
	// safely wait for read operation
	// to begin before exiting
	//
#if (I2CSLAVE__LPMx_bits>0)
	while(1)
	{
		__bic_SR_register(GIE);
		if (g_bI2CSlaveRequestPending==true)
		{
			__bis_SR_register(I2CSLAVE__LPMx_bits | GIE);
		}
		else
		{
			__bis_SR_register(GIE);
			break;
		}
	}
#else
	while(g_bI2CSlaveRequestPending==true);
#endif

	//
	// If the slave timeout feature is enabled,
	// cancel the request flag timeout function
	// as transmission has begun.
	//
#if (I2CSLAVE__TIMEOUT_ENABLE==true)
			Timer_cancelDelayedFunction(eTimerDelayedFunction_A);
#endif /* I2CSLAVE__TIMEOUT_ENABLE==true */
	I2C__RELEASE_REQ_SIGNAL;
}

static bool I2CSlave_handleEndOfReceive(void)
{
	uint8_t ui8Data;

	//
	// Check for final received data byte in case start/stop interrupt is being serviced
	// before last rx interrupt due to MSP430 I2C interrupt priority
	//
	if(MAP_EUSCI_B_I2C_getInterruptStatus(I2CSLAVE__EUSCI_B_PERIPHERAL, EUSCI_B_I2C_RECEIVE_INTERRUPT0))
	{
		ui8Data = MAP_EUSCI_B_I2C_slaveGetData(I2CSLAVE__EUSCI_B_PERIPHERAL);
		if (g_ui16I2CIndex < g_pI2CSlavePort->ui16ReceiveBufferSize)
		{
			g_pI2CSlavePort->pReceiveBuffer[g_ui16I2CIndex++] = ui8Data;
		}
		MAP_EUSCI_B_I2C_clearInterrupt(I2CSLAVE__EUSCI_B_PERIPHERAL, EUSCI_B_I2C_RECEIVE_INTERRUPT0);
	}

	//
	// Call receive callback if it exists
	//
	if (g_pI2CSlavePort->pbReceiveCallback != 0)
	{
		return g_pI2CSlavePort->pbReceiveCallback(g_ui16I2CIndex);
	}
	else
	{
		return false;
	}
}

#pragma vector=I2CSLAVE__EUSCI_VECTOR
__interrupt void I2CSlave_ISR(void)
{
	uint8_t ui8Data;

	switch (__even_in_range(I2CSLAVE__EUSCI_IV, USCI_I2C_UCTXIFG0))
	{
		case USCI_I2C_UCSTTIFG:
			//
			// Check for the repeated start case.  If this is a repeated start
			// and the previous operation was a write to this device,
			// handle the written (received) data.  If this is a first-time stard,
			// the previous I2C state is eI2CSlaveIsIdle.
			//
			if (g_I2CSlaveStatus == eI2CSlaveIsBeingWrittenTo)
			{
				if (I2CSlave_handleEndOfReceive() == true)
				{
					__bic_SR_register_on_exit(I2CSLAVE__LPMx_bits);
				}
			}

			//
			// Reset the I2C Index to zero to begin the new transaction.
			// Then check the I2C mode (read/write) to determine
			// the transaction mode.
			//
			g_ui16I2CIndex = 0;
			if (MAP_EUSCI_B_I2C_getMode(I2CSLAVE__EUSCI_B_PERIPHERAL)
					== EUSCI_B_I2C_TRANSMIT_MODE)
			{
				//
				// If this is a read operation (read from this device),
				// cancel the slave request flag and trigger and active
				// exit to alert the application that the flag has changed.
				//
				g_I2CSlaveStatus = eI2CSlaveIsBeingRead;
				g_bI2CSlaveRequestPending = false;
				__bic_SR_register_on_exit(I2CSLAVE__LPMx_bits);

				//
				// If the driver is set up to send the number of bytes to be read
				// before the rest of the buffer, load the number as the first data byte.
				// Otherwise, load the first byte of the transmit buffer into the peripheral.
				//
				if (g_pI2CSlavePort->bSendReadLengthFirst == true)
				{
					ui8Data = g_ui16I2CLength;
				}
				else
				{
					ui8Data = g_pI2CTransmitBuffer[g_ui16I2CIndex++];
				}
				MAP_EUSCI_B_I2C_slavePutData(
						I2CSLAVE__EUSCI_B_PERIPHERAL,
						ui8Data
					);
			}
			else
			{
				//
				// If this is a write operation (write from master to this device),
				// update the status accordingly and continue (no additional action is necessary).
				//
				g_I2CSlaveStatus = eI2CSlaveIsBeingWrittenTo;
			}

			//
			// If the slave timeout feature is enabled, schedule a
			// transaction timeout.
			//
#if (I2CSLAVE__TIMEOUT_ENABLE==true)
			Timer_scheduleDelayedFunction(eTimerDelayedFunction_B);
#endif /* I2CSLAVE__TIMEOUT_ENABLE==true */
			break;

		case USCI_I2C_UCSTPIFG:
			//
			// If the timeout feature is enabled, cancel
			// the transaction timeout as the operation
			// has finished successfully.
			//
#if (I2CSLAVE__TIMEOUT_ENABLE==true)
			Timer_cancelDelayedFunction(eTimerDelayedFunction_B);
#endif /* I2CSLAVE__TIMEOUT_ENABLE==true */


			if (g_I2CSlaveStatus == eI2CSlaveIsBeingWrittenTo)
			{
				//
				// If the operation that is ending was a write to this
				// device, handle the written (received) data, and exit
				// active if the callback function requested it.
				//
				if (I2CSlave_handleEndOfReceive() == true)
				{
					__bic_SR_register_on_exit(I2CSLAVE__LPMx_bits);
				}
			}
			else if (g_I2CSlaveStatus == eI2CSlaveIsBeingRead)
			{
				//
				// If the opreation that is ending was a read from this device,
				// exit active in case a transmit (read) buffer pointer update
				// was pending upon this read.
				//
				__bic_SR_register_on_exit(I2CSLAVE__LPMx_bits);
			}

			//
			// Set new status to idle, as the I2C transaction has stopped.
			//
			g_I2CSlaveStatus = eI2CSlaveIsIdle;
			break;

		case USCI_I2C_UCRXIFG0:
			//
			// Grab the received (written) byte from the I2C peripheral.
			// If there is receive buffer space left, store the received
			// byte in the receive buffer.  Otherwise, discard it and call
			// the error callback fxn if one is registered.
			//
			ui8Data = ROM_EUSCI_B_I2C_slaveGetData(I2CSLAVE__EUSCI_B_PERIPHERAL);
			if (g_ui16I2CIndex < g_pI2CSlavePort->ui16ReceiveBufferSize)
			{
				g_pI2CSlavePort->pReceiveBuffer[g_ui16I2CIndex++] = ui8Data;
			}
			else
			{
				if (g_pI2CSlavePort->pvErrorCallback != 0)
				{
					g_pI2CSlavePort->pvErrorCallback(eI2CSlaveReceiveBufferFull);
				}
			}
			break;

		case USCI_I2C_UCTXIFG0:
			//
			// If the transmit index is less than the length, there is still
			// valid data in the buffer.  Load the next byte.
			// Else, there is no valid data left in the buffer, so transmit
			// the invalid byte.
			//
			if (g_ui16I2CIndex<g_ui16I2CLength)
			{
				ui8Data = g_pI2CTransmitBuffer[g_ui16I2CIndex++];
			}
			else
			{
				ui8Data = I2CSLAVE__INVALID_BYTE;
				if (g_pI2CSlavePort->pvErrorCallback != 0)
				{
					g_pI2CSlavePort->pvErrorCallback(eI2CSlaveWasReadBeyondTransmitBuffer);
				}
			}
			MAP_EUSCI_B_I2C_slavePutData(I2CSLAVE__EUSCI_B_PERIPHERAL, ui8Data);
			break;
	}
}

#endif /* I2CSLAVE__ENABLE==true */

//*****************************************************************************
//! Close the doxygen group
//! @}
//*****************************************************************************
