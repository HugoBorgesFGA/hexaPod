/*
 * interrupcoes.h
 *
 *  Created on: 31/12/2014
 *      Author: Hugo
 */

#ifndef INTERRUPCOES_H_
#define INTERRUPCOES_H_

#include <io.h>
#include <stdint.h>
#include "msp430g2553.h"
#include "global.h"
#include "fsm_timerB.h"

// Interrupcao do TimerA
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void);

#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer_B (void);


#endif /* INTERRUPCOES_H_ */
