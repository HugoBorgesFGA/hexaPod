#include "global.h"

// Variáveis globais
void (*fsm_timerB_estado_atual)(void);
uint8_t dutyCycles_meta[18];
uint8_t dutyCycles_atual[18];

uint8_t dutyCycles_g1[6];
uint8_t dutyCycles_g2[6];
uint8_t dutyCycles_g3[6];

uint8_t mascaras_g1[6];
uint8_t mascaras_g2[6];
uint8_t mascaras_g3[6];

uint8_t *mascaras;
uint8_t *dutyCycles;

uint8_t motorAtual;


void callbackG1(){

}

void callbackG2(){

}

void callbackG3(){

}

void inline callback_teste(){
	P1OUT &= ~BIT0;
	DESATIVAR_TIMERA();
}
