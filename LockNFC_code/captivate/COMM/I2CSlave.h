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
// I2CSlave.h
//
//! I2C slave driver module for the eUSCI_B I2C peripheral.
//
//! This is the I2C slave port driver header file.  The I2C slave port driver
//! enables interrupt-driven I2C-bus transactions via a simple API.  The
//! implementation requires one eUSCI_B instance, and the MSP430 DriverLib
//! version 2.10.00.00 or greater.
//
//! \version 1.70.00.03
//! Released on July 30, 2018
//
//*****************************************************************************
//*****************************************************************************
//! \addtogroup I2CSlave
//! @{
//*****************************************************************************

#ifndef CAPT_I2C_H_
#define CAPT_I2C_H_

#include "I2CSlave_Definitions.h"

#if (I2CSLAVE__ENABLE==true)

#if (I2CSLAVE__TIMEOUT_ENABLE==true)
#include "FunctionTimer.h"
#endif

//*****************************************************************************
//
//! def I2CSLAVE__EUSCI_VECTOR defines the interrupt vector location
//! of the selected eUSCI_B I2C peripheral.
//
//! def I2CSLAVE__EUSCI_IV defines the interrupt vector of the selected
//! eUSCI_B I2C peripheral.
//
//*****************************************************************************
#if (I2CSLAVE__EUSCI_B_PERIPHERAL == EUSCI_B0_BASE)
#define I2CSLAVE__EUSCI_VECTOR     	(USCI_B0_VECTOR)
#define I2CSLAVE__EUSCI_IV    	 	(UCB0IV)
#else
#error INVALID_EUSCI_B_SELECTION
#endif

//*****************************************************************************
//
//! def I2CSLAVE__INT_MASK defines the interrupt enable mask for the eUSCI_B
//! I2C peripheral.  The used interrupts include START, STOP, RX, and TX.
//
//*****************************************************************************
#define I2CSLAVE__INT_MASK		(0x0F)

//*****************************************************************************
//
//! def I2C__INIT_REQ_SIGNAL is a macro for setting the I2C
//! request line to active low.
//
//*****************************************************************************
#define I2C__INIT_REQ_SIGNAL		(I2CSLAVE__REQ_POUT &= ~I2CSLAVE__REQ_MASK)

//*****************************************************************************
//
//! def I2C__PULL_REQ_SIGNAL is a macro for pulling the I2C request line by
//! changing its state from Hi-Z to output low (current sink)
//
//*****************************************************************************
#define I2C__PULL_REQ_SIGNAL		(I2CSLAVE__REQ_PDIR |= I2CSLAVE__REQ_MASK)

//*****************************************************************************
//
//! def I2C__RELEASE_REQ_SIGNAL us a macro for releasing the I2C request line
//! by returing its state to Hi-Z from output low.
//
//*****************************************************************************
#define I2C__RELEASE_REQ_SIGNAL		(I2CSLAVE__REQ_PDIR &= ~I2CSLAVE__REQ_MASK)

//*****************************************************************************
//
//! typedef tI2CSlavePort defines the port definition that the user must
//! provide when instantiating this driver.  This structure is read-only from
//! the context of the driver, and may be placed in read-only memory, such as
//! the C CONST section, if desired.
//
//*****************************************************************************
typedef struct
{
	//
	//! Receive Callback.  This function will be called
	//! after each I2C write operation is completed (a write is data
	//! sent from the bus master to a slave, such as this port).
	//! If the callback returns true, the ISR exits awake.
	//
	bool (*pbReceiveCallback)(uint16_t);

	//
	//! Error Callback.  This function will be called after
	//! a failed transmission.  The passed tI2CSlaveErrors
	//! parameter indicates what caused the failure.
	//
	void (*pvErrorCallback)(uint8_t);

	//
	//! Receive Buffer Size (Bytes).  This indicates the amount of buffer
	//! space available to the driver during a receive (I2C write)
	//! transaction.
	//
	uint16_t ui16ReceiveBufferSize;

	//
	//! Receive Buffer Head Pointer.  This pointer indicates the address
	//! of the buffer space available to the I2C driver during an I2C write
	//! operation.
	//
	uint8_t *pReceiveBuffer;

	//
	//! If bSendReadLengthFirst is true, when the master
	//! reads from this device the first byte it reads out will
	//! be a length byte, indicating how many additional bytes
	//! exist to be read.
	//
	bool bSendReadLengthFirst;

} tI2CSlavePort;

//*****************************************************************************
//
//! \enum tI2CSlaveStates enumerates the possible I2C slave driver states.
//
//*****************************************************************************
enum tI2CSlaveStates {
	eI2CSlaveIsClosed = 0x00,
	eI2CSlaveIsIdle = 0x01,
	eI2CSlaveIsBeingRead = 0x02,
	eI2CSlaveIsBeingWrittenTo = 0x03
};

//*****************************************************************************
//
//! \enum tI2CSlaveErrors enumerates the possible I2C slave driver errors.
//! These error codes are passed to the error callback function.
//
//*****************************************************************************
enum tI2CSlaveErrors {
	eI2CSlaveTransmitRequestTimeout,
	eI2CSlaveTransactionTimeout,
	eI2CSlaveReceiveBufferFull,
	eI2CSlaveWasReadBeyondTransmitBuffer
};

//*****************************************************************************
//
//! This function opens the I2C slave port on the specified HW eUSCI_B
//! peripheral. This function must be called before the port is used.
//
//! \param pPort is a pointer to the I2C Slave Port configuration
//! structure.  The user must populate and provide this structure to the I2C
//! slave port driver.  The data structure must remain at the same address
//! throughout the operation of the driver.
//! \return none
//
//*****************************************************************************
extern void I2CSlave_openPort(const tI2CSlavePort *pPort);

//*****************************************************************************
//
//! This function closes the I2C slave port on the specified HW eUSCI_B
//! peripheral.
//
//!  \par Parameters
//!		none
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void I2CSlave_closePort(void);

//*****************************************************************************
//
//! This function returns the status of the I2C port when called.  The possible
//! I2C statuses are enumerated under tI2CSlaveStates.
//
//!  \par Parameters
//!		none
//! \return tI2CSlaveStates enumeration indicating the current I2C status.
//
//*****************************************************************************
extern uint8_t I2CSlave_getPortStatus(void);

//*****************************************************************************
//
//! This function sets a new transmit buffer in the I2C peripheral.  To send a
//! buffer of data to the I2C bus master, use this function to inform the
//! driver of the buffer location and size.  Then call the
//! I2CSlave_setTransmitRequestFlag function to signal the host to
//! begin transmission.
//
//! If a current read is either pending or currently in  progress,
//! this function will block until that operation has completed or timed out
//! before updating the transmit buffer pointer and length.
//
//! \param pBuffer is a pointer to the new transmit buffer
//! \param ui16Length is an integer specifying the valid data length in the
//! buffer
//!  \par Returns
//!		none
//
//*****************************************************************************
extern void I2CSlave_setTransmitBuffer(uint8_t *pBuffer, uint16_t ui16Length);

//*****************************************************************************
//
//! This function pulls the I2C request line to signal the bus master that
//! data is waiting to be read from this device.
//
//! This function will block until either the bus master begins to read out the
//! data OR the read post times out, at which point the error callback will be
//! called to handle the error.
//
//!  \par Parameters
//!		none
//! \return true if bus master began read operation; else false if the
//! request timed out.
//
//*****************************************************************************
extern void I2CSlave_setRequestFlag(void);

#endif /* I2CSLAVE__ENABLE==true */

#endif /* CAPT_I2C_H_ */
//*****************************************************************************
//! Close the doxygen group
//! @}
//*****************************************************************************
