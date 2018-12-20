/*
 * timer.h
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <msp430.h>
#include "stdint.h"

void initTimeout(void);
void startTimeout(uint8_t seconds);


#endif /* TIMER_H_ */
