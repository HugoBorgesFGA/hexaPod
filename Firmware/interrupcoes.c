#include "interrupcoes.h"

// Executada sempre a cada 10us
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
	P1OUT &= ~mascaras[motorAtual];
	if ( (++motorAtual) < 6){
		DISPARAR_TIMERA(dutyCycles[motorAtual] - dutyCycles[motorAtual-1]);
	}else{
		DESATIVAR_TIMERA();
	}
}

// Executada sempre a cada 20ms
#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer_B (void)
{
	// Chama a maquina
	fsm_timerB_estado_atual();
}

// Executada quando a placa externa atualiza
// os valores do duty cycle

