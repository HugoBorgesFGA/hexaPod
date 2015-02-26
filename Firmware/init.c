#include "init.h"


void init_VariaveisGlobais(){
	// Estado inicial
	motorAtual = 0;
	fsm_timerB_estado_atual = fsm_timerB_alto1;

	// Zera variáveis
	uint8_t i;
	for(i = 0; i < 6; i++){
		dutyCycles_g1[i] = 0;
		dutyCycles_g2[i] = 0;
		dutyCycles_g3[i] = 0;

		mascaras_g1[i] = 0;
		mascaras_g2[i] = 0;
		mascaras_g3[i] = 0;
	}

	for(i = 0; i < 18; i++){
		dutyCycles_atual[i] = 0;
	}


	// ######################################################################################################
	// ######################################### PATA 1 #####################################################
	// ######################################################################################################

	// Motor 0
	// Tipo: Body
	// PATA1_0 (Esquemático) -> P1.5
	dutyCycles_meta[0] = 10 - 3;

	// Motor 1
	// Tipo: Femur
	// PATA1_1 (Esquemático) -> P1.4
	dutyCycles_meta[1] = 20 - 3;

	// Motor 2
	// Tipo: Tibia
	// PATA1_2 (Esquemático) -> P1.3
	dutyCycles_meta[2] = 30 - 3;

	// ######################################################################################################
	// ######################################### PATA 2 #####################################################
	// ######################################################################################################

	// Motor 3
	// Tipo: Body
	// PATA2_0 (Esquemático) -> P1.2
	dutyCycles_meta[3] = 40 - 3;

	// Motor 4
	// Tipo: Femur
	// PATA2_1 (Esquemático) -> P1.1
	dutyCycles_meta[4] = 45 - 3;

	// Motor 5
	// Tipo: Tibia
	// PATA2_2 (Esquemático) -> P1.0
	dutyCycles_meta[5] = 85 - 3;

	// ######################################################################################################
	// ######################################### PATA 3 #####################################################
	// ######################################################################################################

	// Motor 6
	// Tipo: Body
	// PATA3_0 (Esquemático) -> P1.5
	dutyCycles_meta[6] = 55 - 3;

	// Motor 7
	// Tipo: Femur
	// PATA3_1 (Esquemático) -> P1.4
	dutyCycles_meta[7] = 60 - 3;

	// Motor 8
	// Tipo: Tibia
	// PATA3_2 (Esquemático) -> P1.3
	dutyCycles_meta[8] = 65 - 3;

	// ######################################################################################################
	// ######################################### PATA 4 #####################################################
	// ######################################################################################################

	// Motor 9
	// Tipo: Body
	// PATA4_0 (Esquemático) -> P1.2
	dutyCycles_meta[9] = 70 - 3;

	// Motor 10
	// Tipo: Femur
	// PATA4_1 (Esquemático) -> P1.1
	dutyCycles_meta[10] = 75 - 3;

	// Motor 11
	// Tipo: Tibia
	// PATA4_2 (Esquemático) -> P1.0
	dutyCycles_meta[11] = 80 - 3;

	// ######################################################################################################
	// ######################################### PATA 5 #####################################################
	// ######################################################################################################

	// Motor 12
	// Tipo: Body
	// PATA5_0 (Esquemático) -> P1.5
	dutyCycles_meta[12] = 85 - 3;

	// Motor 13
	// Tipo: Femur
	// PATA5_1 (Esquemático) -> P1.4
	dutyCycles_meta[13] = 90 - 3;

	// Motor 14
	// Tipo: Tibia
	// PATA5_2 (Esquemático) -> P1.3
	dutyCycles_meta[14] = 92 - 3;

	// ######################################################################################################
	// ######################################### PATA 6 #####################################################
	// ######################################################################################################

	// Motor 15
	// Tipo: Body
	// PATA6_0 (Esquemático) -> P1.2
	dutyCycles_meta[15] = 93 - 3;

	// Motor 16
	// Tipo: Femur
	// PATA6_1 (Esquemático) -> P1.1
	dutyCycles_meta[16] = 95 - 3;

	// Motor 17
	// Tipo: Tibia
	// PATA6_2 (Esquemático) -> P1.0
	dutyCycles_meta[17] = 100 - 3;

	for(i = 0; i < 18; i++){
		dutyCycles_atual[i] = dutyCycles_meta[i];
	}

	mascaras_g1[0] = 0x01; // P1.0
	mascaras_g1[1] = 0x02; // P1.1
	mascaras_g1[2] = 0x04; // P1.2
	mascaras_g1[3] = 0x08; // P1.3
	mascaras_g1[4] = 0x10; // P1.4
	mascaras_g1[5] = 0x20; // P1.5

	for(i = 0; i < 6; i++){
		dutyCycles_g1[i] = dutyCycles_meta[i];
		dutyCycles_g2[i] = dutyCycles_meta[i+6];
		dutyCycles_g3[i] = dutyCycles_meta[i+12];

		mascaras_g2[i] = mascaras_g1[i];
		mascaras_g3[i] = mascaras_g1[i];
	}
}


void init_ClockPrincipal(){
	DCOCTL = 0;
	BCSCTL1 = CALBC1_16MHZ;
	DCOCTL = CALDCO_16MHZ;
}

void init_TimerB(){
	// Configura o TimerB do MSP430 para disparar uma interrupção
	// a cada 1ms para executar os estágios da maquina de estado

	// Define o tanto que ele vai contar
	// pelo menor espaco de tempo distinguivel pelo micro (periodo da frequencia de operacao) = 1/16Mhz
	TA1CCR0 = 16000;

	// TASSEL_2: Define o Timer para usar o clock principal (16Mhz)
	// ID_0: Divide o clock source por 1 (16Mhz)
	// MC_1: Conta ate o valor especificado e dispara a interrupção
	TA1CTL |= TASSEL_2 + ID_0 + MC_1 + TACLR;


	// Habilita a Interrupção
	TA1CCTL0 = CCIE;
}

void init_TimerA(){
	// Configura para disparar de 10 em 10 us
	TA0CCR0 = 160;
	TA0CTL |= TASSEL_2 + ID_0 + MC_1 + TACLR;
	TA0CCTL0 = CCIE;
}

void init_GPIO(){
	// Define todos os pinos como saida, exceto o PINO_DIN (P1.7)
	P2DIR = 0xFF;
	P1DIR = 0x7F;

	// Poe os pinos dos servos em baixo por default
	P1OUT &= ~maskServosP1OUT;
	MUX_LATCHES_OFF();

	// Configura o PINO_DIN
	//P1IFG &= ~PINO_DIN;			// Limpa flag indicadora de interrupt
	//P1IES &= ~PINO_DIN;			// Borda de subida
	//P1IE |= PINO_DIN;			// Habilita interrupcao nesse pino
}

void Init(){
	// Inicia variaveis globais
	init_VariaveisGlobais();

	// Configura o clock principal pra 16Mhz
	init_ClockPrincipal();

	// Configura o Timer_B
	init_TimerB();

	init_TimerA();

	// Configuração das GPIOS
	init_GPIO();
}
