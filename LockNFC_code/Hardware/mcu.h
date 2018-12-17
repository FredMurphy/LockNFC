/*
 * File Name: mcu.h
 *
 * Description: Header file for all functions for mcu.h
 *
 * Copyright (C) 2016 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/

#ifndef MCU_H_
#define MCU_H_

//===============================================================

#include "MSP430.h" 		// Processor specific header
#include "types.h"
#include "VLO_Library.h"

//=====MCU constants=============================================
#if defined(__CUSTOMFR2633__) // Custom LockNFC board
#define TRF_ENABLE_SET  P1DIR |= BIT3       // P1.4 is switched in output direction
#define TRF_ENABLE      P1OUT |= BIT3       // EN pin on the TRF7970A
#define TRF_DISABLE     P1OUT &= ~BIT3

// IRQ on P2.2
#define IRQ_PIN_SET     P2DIR &= ~IRQ_PIN
#define IRQ_PIN         BIT2
#define IRQ_PORT        P2IN
#define IRQ_ON          P2IE |= IRQ_PIN
//#define IRQ_OFF         P1IE &= ~IRQ_PIN
#define IRQ_EDGE_SET    P2IES &= ~IRQ_PIN       // Rising edge interrupt
#define IRQ_CLR         P2IFG = 0x00
#define IRQ_REQ_REG     P2IFG
#define IRQ_VECTOR      PORT2_VECTOR

/*
#define LED_PORT_SET    P1DIR |= BIT1
#define LED_ALL_OFF     P1OUT &= ~BIT1

#define LED_14443A_ON   P1OUT &= ~BIT1 // Active low
#define LED_14443A_OFF  P1OUT |= BIT1
#define LED_14443B_ON   ;
#define LED_14443B_OFF  ;
#define LED_15693_ON    ;
#define LED_15693_OFF   ;
*/
#define LED1_POUT                                                       (P1OUT)
#define LED1_PDIR                                                       (P1DIR)
#define LED1_PIN                                                         (BIT0)
#define LED1_ON                                        (LED1_POUT &= ~LED1_PIN)
#define LED1_OFF                                        (LED1_POUT |= LED1_PIN)
#define LED1_TOGGLE                                     (LED1_POUT ^= LED1_PIN)

#define LED2_POUT                                                       (P1OUT)
#define LED2_PDIR                                                       (P1DIR)
#define LED2_PIN                                                         (BIT1)
#define LED2_ON                                        (LED2_POUT &= ~LED2_PIN)
#define LED2_OFF                                        (LED2_POUT |= LED2_PIN)
#define LED2_TOGGLE                                     (LED2_POUT ^= LED2_PIN)

#define LED3_POUT                                                       (P1OUT)
#define LED3_PDIR                                                       (P1DIR)
#define LED3_PIN                                                         (BIT2)
#define LED3_ON                                        (LED3_POUT &= ~LED3_PIN)
#define LED3_OFF                                        (LED3_POUT |= LED3_PIN)
#define LED3_TOGGLE                                     (LED3_POUT ^= LED3_PIN)

// LEDs are active low
#define LED_RED            (LED1_POUT = LED1_POUT & 0xF8 | LED2_PIN | LED3_PIN)
#define LED_RED_OFF                                     (LED1_POUT |= LED1_PIN)
#define LED_RED_ON                                     (LED1_POUT &= ~LED1_PIN)
#define LED_GREEN          (LED1_POUT = LED1_POUT & 0xF8 | LED1_PIN | LED3_PIN)
#define LED_GREEN_OFF                                   (LED1_POUT |= LED2_PIN)
#define LED_GREEN_ON                                   (LED1_POUT &= ~LED2_PIN)
#define LED_BLUE           (LED1_POUT = LED1_POUT & 0xF8 | LED1_PIN | LED2_PIN)
#define LED_BLUE_OFF                                    (LED1_POUT |= LED3_PIN)
#define LED_BLUE_ON                                    (LED1_POUT &= ~LED3_PIN)
#define LED_OFF                 (LED1_POUT |= (LED1_PIN | LED2_PIN | LED3_PIN))

//SS 3.0
#define SLAVE_SELECT_PORT_SET   P3DIR |= BIT0
#define SLAVE_SELECT_HIGH       P3OUT |= BIT0
#define SLAVE_SELECT_LOW        P3OUT &= ~BIT0

// UCB0 SPI on 1.1-3
// UCA0 SPI on 1.4-6 (+7 for STE)
#define SPI_PIN_FUNCTION    P1SEL0 |= BIT4 + BIT5 + BIT6
/*
#define SPI_DIR             P1DIR
#define SPI_OUT             P1OUT
#define SPI_CTL0            UCB0CTL0
#define SPI_CTL1            UCB0CTL1
#define SPI_BR0             UCB0BR0
#define SPI_BR1             UCB0BR1
*/
#define SPI_RX_BUF          UCA0RXBUF
#define SPI_TX_BUF          UCA0TXBUF
#define SPI_RX_READY        UCA0IFG & UCRXIFG
#define SPI_TX_READY        UCA0IFG & UCTXIFG
#define SPI_BUSY            UCA0STATW & UCBUSY
//-----Counter-timer constants-----------------------------------

#define COUNTER_VALUE   TA0CCR0                             //counter register
#define START_COUNTER   TA0CTL |=  MC0; TA0CCTL0 |= CCIE            //start counter in up mode
#define STOP_COUNTER    TA0CTL &= ~(MC0 + MC1)   //stops the counter ; TA0CCTL0 &= ~CCIE
#define RESET_COUNTER   TA0CTL |= TACLR                             //Resets and stops counter.

#elif defined(__MSP430FR2633__)
#define TRF_ENABLE_SET  P1DIR |= BIT3       // P1.4 is switched in output direction
#define TRF_ENABLE      P1OUT |= BIT3       // EN pin on the TRF7970A
#define TRF_DISABLE     P1OUT &= ~BIT3

// IRQ on P1.0
#define IRQ_PIN_SET     P1DIR &= ~IRQ_PIN
#define IRQ_PIN         BIT0
#define IRQ_PORT        P1IN
#define IRQ_ON          P1IE |= IRQ_PIN
//#define IRQ_OFF         P1IE &= ~IRQ_PIN
#define IRQ_EDGE_SET    P1IES &= ~IRQ_PIN       // Rising edge interrupt
#define IRQ_CLR         P1IFG = 0x00
#define IRQ_REQ_REG     P1IFG
#define IRQ_VECTOR      PORT1_VECTOR

#define LED_PORT_SET    P1DIR |= BIT7
#define LED_ALL_OFF     P1OUT &= ~BIT7

#define LED_14443A_ON   P1OUT |= BIT7
#define LED_14443A_OFF  P1OUT &= ~BIT7
#define LED_14443B_ON   ;
#define LED_14443B_OFF  ;
#define LED_15693_ON    ;
#define LED_15693_OFF   ;

#define DEBUG_SET       P1DIR |= BIT6
#define DEBUG_ON        P1OUT |= BIT6
#define DEBUG_OFF       P1OUT &= ~BIT6

//SS 1.5
#define SLAVE_SELECT_PORT_SET   P1DIR |= BIT2
#define SLAVE_SELECT_HIGH       P1OUT |= BIT2
#define SLAVE_SELECT_LOW        P1OUT &= ~BIT2

// UCB0 SPI on 1.1-3
// UCA0 SPI on 1.4-6 (+7 for STE)
#define SPI_PIN_FUNCTION    P1SEL0 |= BIT4 + BIT5 + BIT6
/*
#define SPI_DIR             P1DIR
#define SPI_OUT             P1OUT
#define SPI_CTL0            UCB0CTL0
#define SPI_CTL1            UCB0CTL1
#define SPI_BR0             UCB0BR0
#define SPI_BR1             UCB0BR1
*/
#define SPI_RX_BUF          UCA0RXBUF
#define SPI_TX_BUF          UCA0TXBUF
#define SPI_RX_READY        UCA0IFG & UCRXIFG
#define SPI_TX_READY        UCA0IFG & UCTXIFG
#define SPI_BUSY            UCA0STATW & UCBUSY
//-----Counter-timer constants-----------------------------------

#define COUNTER_VALUE   TA0CCR0                             //counter register
#define START_COUNTER   TA0CTL |=  MC0; TA0CCTL0 |= CCIE            //start counter in up mode
#define STOP_COUNTER    TA0CTL &= ~(MC0 + MC1)   //stops the counter ; TA0CCTL0 &= ~CCIE
#define RESET_COUNTER   TA0CTL |= TACLR                             //Resets and stops counter.

#endif

/*
#if defined(__MSP430G2553__)
#define USE_VLO
#define TRF_ENABLE_SET	P2DIR |= BIT2		// P2.2 is switched in output direction
#define	TRF_ENABLE		P2OUT |= BIT2		// EN pin on the TRF7970A
#define TRF_DISABLE		P2OUT &= ~BIT2

// IRQ on P2.0 or P2.7 depending on BP Version
#define IRQ_PIN_SET		P2DIR &= ~IRQ_PIN
#define IRQ_PIN			(BIT0 | BIT7)
#define IRQ_PORT		P2IN
#define IRQ_ON			P2IE |= IRQ_PIN
#define IRQ_OFF			P2IE &= ~IRQ_PIN
#define IRQ_EDGE_SET	P2IES &= ~IRQ_PIN		// Rising edge interrupt
#define IRQ_CLR			P2IFG = 0x00
#define IRQ_REQ_REG		P2IFG
#define IRQ_VECTOR      PORT2_VECTOR

#define LED_PORT_SET	P2DIR |= 0x38
#define LED_ALL_OFF		P2OUT &= ~0x38

#define LED_14443A_ON	P2OUT |= BIT4
#define LED_14443A_OFF	P2OUT &= ~BIT4
#define LED_14443B_ON	P2OUT |= BIT3
#define LED_14443B_OFF	P2OUT &= ~BIT3
#define LED_15693_ON	P2OUT |= BIT5
#define LED_15693_OFF	P2OUT &= ~BIT5

#define DEBUG_SET       P1DIR |= BIT0
#define DEBUG_ON        P1OUT |= BIT0
#define DEBUG_OFF       P1OUT &= ~BIT0

#define SLAVE_SELECT_PORT_SET	P2DIR |= BIT1
#define SLAVE_SELECT_HIGH		P2OUT |= BIT1
#define SLAVE_SELECT_LOW		P2OUT &= ~BIT1

//-----Counter-timer constants-----------------------------------

#define COUNTER_VALUE	TA0CCR0					//counter register
#define START_COUNTER	TA0CTL |=  MC0			//start counter in up mode
#define STOP_COUNTER	TA0CTL &= ~(MC0 + MC1)	//stops the counter
#define RESET_COUNTER   TA0CTL |= TACLR	    	//Resets and stops counter.

// SPI on 1.1-3
#define SPI_PIN_FUNCTION    P1SEL |= BIT5 + BIT6 + BIT7; P1SEL2 |= BIT5 + BIT6 + BIT7

//#define SPI_CTL0            UCB0CTL0
//#define SPI_CTL1            UCB0CTL1
//#define SPI_BR0             UCB0BR0
//#define SPI_BR1             UCB0BR1
//#define SPI_RX_BUF          UCB0RXBUF
//#define SPI_TX_BUF          UCB0TXBUF

#define SPI_TX_READY        IFG2 & UCB0TXIFG
//#define SPI_RX_READY        IFG2 & UCB0RXIFG
#define SPI_BUSY            UCB0STAT & UCBUSY

//===============================================================
#endif
*/

#define DELAY_1ms		8000	// Used for McuDelayMillisecond

//===============================================================

void MCU_setCounter(uint16_t ui16mSecTimeout);
void MCU_delayMillisecond(uint32_t n_ms);
void MCU_initClock(void);
void MCU_initPorts(void);
void MCU_calculateVLOFreq(void);

//===============================================================

#endif
