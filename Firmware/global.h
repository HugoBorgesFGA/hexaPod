#ifndef GLOBAL_H_
#define GLOBAL_H_

#include "msp430g2553.h"
#include <io.h>
#include <stdint.h>

/*
 * ##################################################################################################
 * ####################################### INCLUDES #################################################
 * ##################################################################################################
 */

/*
 * ##################################################################################################
 * ###################################### CONSTANTES ################################################
 * ##################################################################################################
 */

// Frequencia em que o MCU funciona em nanosegundos
#define FREQUENCIA_BASE			700

// Multiplo da frequencia base que gera um periodo de quase 10us
// 10000/FREQUENCIA_BASE
#define MULTIPLO_10US			14

#define maskServosP1OUT			0x3F

#define latch1_pino_enable		BIT3
#define latch2_pino_enable		BIT4
#define latch3_pino_enable		BIT5

#define INCREMENTO_SERVO		1
#define PINO_READY				BIT6
#define PINO_DIN				BIT7

#define ESPERAR_70US()			__delay_cycles(800);

#define DESATIVAR_TIMERA()			TA0CCTL0 &= ~CCIE;\
									TA0CTL = MC_0 | TACLR;

#define ATIVAR_TIMERA()				TA0CTL = TASSEL_2 + ID_0 + MC_1 + TACLR; \
									TA0CCTL0 = CCIE;

#define DISPARAR_TIMERA(X)		TA0CCR0 = ((X)<<4)*10; \
								TA0CTL = TASSEL_2 + ID_0 + MC_1 + TACLR; \
								TA0CCTL0 = CCIE;

#define TIMERB_1SEGUNDO() 		TA1CCR0 = 16000; \
								TA1CTL = TASSEL_2 + ID_0 + MC_1 + TACLR; \
								TA1CCTL0 = CCIE;

#define MUX_LATCHES_OFF() \
	P2OUT &= ~(latch1_pino_enable | latch2_pino_enable | latch3_pino_enable);

#define MUX_LATCH1() \
	P2OUT |= latch1_pino_enable; \
	P2OUT &= ~(latch2_pino_enable | latch3_pino_enable);

#define MUX_LATCH2() \
	P2OUT |= latch2_pino_enable; \
	P2OUT &= ~(latch1_pino_enable | latch3_pino_enable);

#define MUX_LATCH3() \
	P2OUT |= latch3_pino_enable; \
	P2OUT &= ~(latch2_pino_enable | latch1_pino_enable);



/*
 * ##################################################################################################
 * ###################################### VARIAVEIS #################################################
 * ##################################################################################################
 */

extern uint8_t dutyCycles_meta[18];
extern uint8_t dutyCycles_atual[18];

extern uint8_t dutyCycles_g1[6];
extern uint8_t dutyCycles_g2[6];
extern uint8_t dutyCycles_g3[6];

extern uint8_t mascaras_g1[6];
extern uint8_t mascaras_g2[6];
extern uint8_t mascaras_g3[6];

extern uint8_t *mascaras;
extern uint8_t *dutyCycles;

extern uint8_t motorAtual;

extern void (*fsm_timerB_estado_atual)(void);


/*
 * ##################################################################################################
 * ###################################### Funções  ##################################################
 * ##################################################################################################
 */
void callbackG1();
void callbackG2();
void callbackG3();

void inline callback_teste();

#endif /* GLOBAL_H_ */
