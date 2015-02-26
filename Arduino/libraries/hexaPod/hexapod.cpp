#include "hexapod.h"

Hexapod robo;

/* 
############################################################
################# Métodos (Auxiliares) #####################
############################################################
*/
void enviaByte(byte dado, byte pino){
  // Start bit
  digitalWrite(pino, HIGH);
  delayMicroseconds(TEMPO_70US);

  // Byte - Primeiro MSB
  digitalWrite(pino, (dado >> 7));
  delayMicroseconds(TEMPO_70US);

  digitalWrite(pino, (dado >> 6)&0x01);
  delayMicroseconds(TEMPO_70US);

  digitalWrite(pino, (dado >> 5)&0x01);
  delayMicroseconds(TEMPO_70US);

  digitalWrite(pino, (dado >> 4)&0x01);
  delayMicroseconds(TEMPO_70US);

  digitalWrite(pino, (dado >> 3)&0x01);
  delayMicroseconds(TEMPO_70US);

  digitalWrite(pino, (dado >> 2)&0x01);
  delayMicroseconds(TEMPO_70US);

  digitalWrite(pino, (dado >> 1)&0x01);
  delayMicroseconds(TEMPO_70US);

  digitalWrite(pino, (dado&0x01));
  delayMicroseconds(TEMPO_70US);
  
  // Stop bit
  digitalWrite(pino, LOW);
  delayMicroseconds(TEMPO_70US);
}


static void comunicacao(){
	if (robo.transmitir){
		// Para cada uma das patas do robo
		int i = 0;
		for(i = 0; i < 6; i++){
			enviaByte(robo.patas[i].corpo, robo.pino_DOUT);
			enviaByte(robo.patas[i].coxa, robo.pino_DOUT);
			enviaByte(robo.patas[i].pinca, robo.pino_DOUT);
		}
		robo.transmitir = 0;
	}
}

void Hexapod_Config(int pinoREADY, int pinoDOUT){
 robo.pino_DOUT = pinoDOUT;
 robo.pino_READY =  pinoREADY;
 
 pinMode(robo.pino_DOUT, OUTPUT);
 pinMode(robo.pino_READY, INPUT);

 attachInterrupt(0, comunicacao, RISING);
}

/* 
############################################################
################# Métodos (Ações) ##########################
############################################################
*/

void Hexapod_Iniciar(){
  int i = 0;
  
  for(i = 0; i < 6; i++){
    robo.patas[i].corpo = 50; // Angulo dos motores do corpo
    robo.patas[i].coxa = 30;  // Angulo dos motores da coxa
    robo.patas[i].pinca = 10; // Angulo dos motores da pinca
  }
}

void Hexapod_Frente(){
  // Sobe a aranha pelo Tripod 0,2,4
  INCREMENTA(robo.patas[0].coxa, 25);
  INCREMENTA(robo.patas[2].coxa, 25);
  INCREMENTA(robo.patas[4].coxa, 25);
  
  delay(200);

  // Gira o Tripod 1,3,5 para frente
  INCREMENTA(robo.patas[1].corpo, 25);
  INCREMENTA(robo.patas[3].corpo, 25);
  INCREMENTA(robo.patas[5].corpo, 25);
  
  delay(200);

  // Desce a aranha pelo Tripod 0,2,4
  DECREMENTA(robo.patas[0].coxa, 25);
  DECREMENTA(robo.patas[2].coxa, 25);
  DECREMENTA(robo.patas[4].coxa, 25);  
  
  delay(200);
  
  // Sobe a aranha pelo Tripod 1,3,5
  INCREMENTA(robo.patas[1].coxa, 25);
  INCREMENTA(robo.patas[3].coxa, 25);
  INCREMENTA(robo.patas[5].coxa, 25);
  
  delay(200);

  // Gira o Tripod 0,2,5 para frente
  INCREMENTA(robo.patas[0].corpo, 25);
  INCREMENTA(robo.patas[2].corpo, 25);
  INCREMENTA(robo.patas[4].corpo, 25);
  
  delay(200);

  // Desce a aranha pelo Tripod 1,3,5
  DECREMENTA(robo.patas[1].coxa, 25);
  DECREMENTA(robo.patas[3].coxa, 25);
  DECREMENTA(robo.patas[5].coxa, 25);  

  delay(200);
}

void Hexapod_Tras(){
    // Sobe a aranha pelo Tripod 0,2,4
  INCREMENTA(robo.patas[0].coxa, 25);
  INCREMENTA(robo.patas[2].coxa, 25);
  INCREMENTA(robo.patas[4].coxa, 25);
  
  // Gira o Tripod 1,3,5 para tras
  DECREMENTA(robo.patas[1].corpo, 25);
  DECREMENTA(robo.patas[3].corpo, 25);
  DECREMENTA(robo.patas[5].corpo, 25);
  
  // Desce a aranha pelo Tripod 0,2,4
  DECREMENTA(robo.patas[0].coxa, 25);
  DECREMENTA(robo.patas[2].coxa, 25);
  DECREMENTA(robo.patas[4].coxa, 25);  
  
  
  // Sobe a aranha pelo Tripod 1,3,5
  INCREMENTA(robo.patas[1].coxa, 25);
  INCREMENTA(robo.patas[3].coxa, 25);
  INCREMENTA(robo.patas[5].coxa, 25);
  
  // Gira o Tripod 0,2,5 para frente
  DECREMENTA(robo.patas[0].corpo, 25);
  DECREMENTA(robo.patas[2].corpo, 25);
  DECREMENTA(robo.patas[4].corpo, 25);
  
  // Desce a aranha pelo Tripod 1,3,5
  DECREMENTA(robo.patas[1].coxa, 25);
  DECREMENTA(robo.patas[3].coxa, 25);
  DECREMENTA(robo.patas[5].coxa, 25); 
}

void Hexapod_Sobe(){
  int i = 0;
  for(i = 0; i < 6; i++){
   INCREMENTA(robo.patas[i].coxa, 20);
  }
}

void Hexapod_Desce(){
  int i = 0;
  for(i = 0; i < 6; i++){
   DECREMENTA(robo.patas[i].coxa, 20);
  }
}

void Hexapod_Horario(){
  
}

void Hexapod_AntiHorario(){

}


