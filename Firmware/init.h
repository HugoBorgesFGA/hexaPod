/*
 * temporizador.h
 *
 *  Created on: 31/12/2014
 *      Author: Hugo
 */

#ifndef INIT_H_
#define INIT_H_

#include <io.h>
#include <stdint.h>
#include "msp430g2553.h"
#include "global.h"
#include "fsm_timerB.h"

void Init();
void init_ClockPrincipal();
void init_VariaveisGlobais();
void init_TimerB();
void init_TimerA();
void init_GPIO();

#endif /* INIT_H_ */
