#include <io.h>
#include <stdint.h>
#include <signal.h>
#include "msp430g2553.h"

#include "global.h"
#include "init.h"
#include "interrupcoes.h"
#include "fsm_timerB.h"

#define DEBUG() \
	P2OUT |= BIT0; \
	P2OUT &= ~BIT0;

/*
 * Autor: Hugo Borges Pinto
 * Data: 01/01/2015
 * Descrição: controlador PWM para robô HexaPod
 *
 * Comentário: Esse código é orientado a interrupções
 * portanto, para uma melhor compreensão do seu funcionamento
 * analise a máquina de estados e os disparos de interrupção
 */

int main(void) {
	// Desliga WatchDog
	WDTCTL = WDTPW | WDTHOLD;

	// Efetua configuração inicial
	Init();

	_BIS_SR(GIE);

	uint8_t receivedByte = 0x00;
	uint8_t countReceived = 0x00;

	// Loop Infinito
	while(1){

		// Verifica se tem algum dado vindo da placa controladora, se houver, recebe
		if (P1IN & PINO_DIN){
			DEBUG();
			receivedByte = 0x00;

			// Start BIT
			__delay_cycles(420); // Até o meio
			ESPERAR_70US();

			// MSB - BIT7
			DEBUG();
			receivedByte |= (P1IN & PINO_DIN);
			ESPERAR_70US();

			// BIT6
			DEBUG();
			receivedByte |= (P1IN & PINO_DIN) >> 1;
			ESPERAR_70US();

			// BIT5
			DEBUG();
			receivedByte |= (P1IN & PINO_DIN) >> 2;
			ESPERAR_70US();

			// BIT4
			DEBUG();
			receivedByte |= (P1IN & PINO_DIN) >> 3;
			ESPERAR_70US();

			// BIT3
			DEBUG();
			receivedByte |= (P1IN & PINO_DIN) >> 4;
			ESPERAR_70US();

			// BIT2
			DEBUG();
			receivedByte |= (P1IN & PINO_DIN) >> 5;
			ESPERAR_70US();

			// BIT1
			DEBUG();
			receivedByte |= (P1IN & PINO_DIN) >> 6;
			ESPERAR_70US();

			// BIT0
			DEBUG();
			receivedByte |= (P1IN & PINO_DIN) >> 7;
			ESPERAR_70US();

			// Stop BIT (...)
			DEBUG();
			// Aproveita para processar
			dutyCycles_atual[countReceived] = receivedByte;
			countReceived = (countReceived < 17) ? countReceived + 1 : 0;

		}

	};
}
