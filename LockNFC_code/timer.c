/*
 * timer.c
 *
 * Manages timeout timer for reseting back to active state
 */
#include "timer.h"
#include "main.h"

volatile uint8_t count;

void initTimeout(void) {

    // Timer1_A3 setup - interrupts at 1 second but off
    TA1CCTL0 = CCIE;
    TA1CCR0 = 32768;
    TA1CTL = MC_0;
}

void startTimeout(uint8_t seconds) {

    count = seconds;
    TA1CTL = TASSEL_1 | MC_1; // ACLK, up mode
}

#pragma vector = TIMER1_A0_VECTOR
__interrupt void Timer1_A0_ISR(void)
{
    if (--count == 0) {
        TA1CTL = MC_0; // Stop timer
        stateActive();
    }
}
