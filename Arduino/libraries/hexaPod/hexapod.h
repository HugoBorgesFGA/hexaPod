// Autor: Hugo Borges Pinto
// Data: 18/02/2005
// Projeto: hexaPod from scratch

#include "Arduino.h"

/* 
#############################################################
################### Definições ##############################
#############################################################
*/
#define TEMPO_70US    55
#define TEMPO_560US	  551

#define ATUALIZAR_MOTORES() \
	comunicacao();

//attachInterrupt(robo.pino_READY, comunicacao, RISING);
  
#define INCREMENTA(var, valor) \
  var = ((var + valor) > 255) ? 255 : var + valor;
  
#define DECREMENTA(var, valor) \
  var = ((var - valor) < 0) ? 0 : var - valor;

/* 
#############################################################
################### Abstrações ##############################
#############################################################
*/
typedef struct sPata{
 byte corpo;  // Motor ligado ao corpo do hexaPod
 byte coxa;   // Motor ligado ao corpo e a coxa
 byte pinca;  // Motor ligado a coxa e a pinca
} Pata;

typedef struct sRobo{
  Pata patas[6];
  byte transmitir;
  byte pino_READY;
  byte pino_DOUT;
  void (*acao)(void);
} Hexapod;

/* 
############################################################
##################### Instancia ############################
############################################################
*/
extern Hexapod robo;

/* 
############################################################
################# Métodos (Ações) ##########################
############################################################
*/
void Hexapod_Iniciar();          // Põe o robo na posição inicial
void Hexapod_Frente();           // Dá um passo a frente
void Hexapod_Tras();             // Dá um passo pra trás
void Hexapod_Sobe();             // Eleva a altura do robo em relação ao chão
void Hexapod_Desce();            // Desce a altura do robo em relação ao chão
void Hexapod_Horario();          // Gira no sentido horário ao redor do eixo central
void Hexapod_AntiHorario();      // Gira no sentido horário ao redor do eixo central

/* 
############################################################
################# Métodos (Auxiliares) #####################
############################################################
*/                                  
void Hexapod_Config(int pinoREADY, int pinoDOUT);
void enviaByte(byte dado, byte pino);
static void comunicacao();      // Envia os angulos dos motores para a placa controladora


