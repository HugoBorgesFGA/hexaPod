#include "fsm_timerB.h"

// Estados da maquina
void fsm_timerB_alto1(){
	DESATIVAR_TIMERA();

	// Ativa latch 1 e desliga outros 2
	MUX_LATCH1();

	// Nesse estado, todos os pinos do PWM estão em alto
	// durante 1ms
	P1OUT |= maskServosP1OUT;

	// Define o timer para disparar novamente em 1ms
	TIMERB_1SEGUNDO();

	// Desabilita interrupção do DIN
	P1IE &= ~PINO_DIN;

	// Desativa o pino de Ready;
	P1OUT &= ~PINO_READY;

	// Próximo estado
	fsm_timerB_estado_atual = fsm_timerB_PWM_G1;
}

void fsm_timerB_PWM_G1(){
	motorAtual = 0;
	dutyCycles = dutyCycles_g1;
	mascaras = mascaras_g1;

	DISPARAR_TIMERA(dutyCycles[0]);

	fsm_timerB_estado_atual = fsm_timerB_alto2;
}

void fsm_timerB_alto2(){
	// Ativa latch 1 e desliga outros 2
	MUX_LATCH2();

	// Nesse estado, todos os pinos do PWM estão em alto
	// durante 1ms
	P1OUT |= maskServosP1OUT;

	// Próximo estado
	fsm_timerB_estado_atual = fsm_timerB_PWM_G2;
}

void fsm_timerB_PWM_G2(){
	motorAtual = 0;
	dutyCycles = dutyCycles_g2;
	mascaras = mascaras_g2;

	DISPARAR_TIMERA(dutyCycles[0]);

	fsm_timerB_estado_atual = fsm_timerB_alto3;
}

void fsm_timerB_alto3(){
	// Ativa latch 1 e desliga outros 2
	MUX_LATCH3();

	// Nesse estado, todos os pinos do PWM estão em alto
	// durante 1ms
	P1OUT |= maskServosP1OUT;

	// Próximo estado
	fsm_timerB_estado_atual = fsm_timerB_PWM_G3;
}

void fsm_timerB_PWM_G3(){
	motorAtual = 0;
	dutyCycles = dutyCycles_g3;
	mascaras = mascaras_g3;

	DISPARAR_TIMERA(dutyCycles[0]);

	fsm_timerB_estado_atual = fsm_timerB_PWM_UPDATE;
}

void fsm_timerB_PWM_UPDATE(){
	// Desliga enables dos latches
	P2OUT &= ~(latch1_pino_enable | latch2_pino_enable | latch3_pino_enable);

	fsm_timerB_estado_atual = fsm_timerB_idle;

}

void fsm_timerB_idle(){
	// Sinaliza recepção dos dados
	P1OUT |= PINO_READY;


	//Já foi 6ms dos 20ms, logo, deve-se esperar 14ms
	TA1CCR0 = 25700;
	TA1CTL = TASSEL_2 + ID_3 + MC_1 + TACLR;
	TA1CCTL0 = CCIE;

	// Desliga os pwms
	P1OUT &= ~maskServosP1OUT;

	fsm_timerB_estado_atual = fsm_timerB_alto1;
}
