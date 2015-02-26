#include <hexapod.h>
#include <PS2X_lib.h>

#define PINO_DOUT      5
#define PINO_READY     2
#define PINO_DEBUG     4

#define SERIAL_BAUD_RATE 57600
#define DEBUG_MODE  1
#define debug(x) \
  if (DEBUG_MODE) Serial.println(x);

PS2X ps2x; // create PS2 Controller Class

int error = 0; 

void setup(){
  // Usa a serial como debug
  if (DEBUG_MODE)  Serial.begin(SERIAL_BAUD_RATE);
  
  //GamePad(clock, command, attention, data, pressão, controle ANALOGICO)
  error = ps2x.config_gamepad(13,11,10,12, false, true);
 
  // Verifica se foi identificado e está pronto para uso
  if (DEBUG_MODE){
    switch(error){
      case 0:
          debug("[DEBUG] - Controle encontrado e configurado com sucesso!");
        break;
      case 1:
          debug("[ERRO] - Controle não encontrado, verifique os fios!");
        break; 
      case 2:
          debug("[ERRO] - Controle encontrado mas não aceita comandos!");
        break; 
      case 3:
          debug("[ERRO] - Controle não está aceitando o modo pressão!");
        break; 
      default:
          debug("[ERRO] - Erro desconhecido!");
        break; 
    }
  }
  
  // Configuração do hexaPod
  Hexapod_Config(2,5);
  Hexapod_Iniciar();
 
}

void loop(){ 
  // Se houver algum erro, sai do loop
  if(error) return; 
  
  // Leitura do controle
  ps2x.read_gamepad();

 // Verifica qual está sendo pressionado
 
 // START
 if(ps2x.Button(PSB_START)){
   debug("[DEBUG] - START Pressionado!");
 }
 
 // SELECT
 else if(ps2x.Button(PSB_SELECT)){
    debug("[DEBUG] - SELECT Pressionado!");
 }
 
 // R1
 else if(ps2x.Button(PSB_R1)){
    debug("[DEBUG] - R1 Pressionado!");
 }
 
 // R2
 else if(ps2x.Button(PSB_R2)){
    debug("[DEBUG] - R2 Pressionado!");
 }
 
 // L1
 else if(ps2x.Button(PSB_L1)){
    debug("[DEBUG] - L1 Pressionado!");
 }
 
 // L2
 else if(ps2x.Button(PSB_L2)){
    debug("[DEBUG] - L2 Pressionado!");
 }
 
 // BOLA
 else if(ps2x.Button(PSB_CIRCLE)){
    debug("[DEBUG] - BOLA Pressionado!");
    
    robo.acao = Hexapod_Iniciar;
    robo.transmitir = 1;
 }
 
 // QUADRADO
 else if(ps2x.Button(PSB_SQUARE)){
    debug("[DEBUG] - QUADRADO Pressionado!");
    
    //robo.acao = Hexapod_Frente;
    //robo.transmitir = 1;
 }
 
 // XIS
 else if(ps2x.Button(PSB_CROSS)){
    debug("[DEBUG] - XIS Pressionado!");
    
    // Envia um byte pro MSP430
    enviaByte(0x23, PINO_DOUT);
    enviaByte(0x0F, PINO_DOUT);
 }
 
 // TRIANGULO
 else if(ps2x.Button(PSB_TRIANGLE)){
    debug("[DEBUG] - TRIANGULO Pressionado!");
 }
 
 // CIMA (BOTAO)
 else if(ps2x.Button(PSB_PAD_UP)){
    debug("[DEBUG] - CIMA Pressionado!");
 }
 
 // BAIXO (BOTAO)
 else if(ps2x.Button(PSB_PAD_DOWN)){
    debug("[DEBUG] - BAIXO Pressionado!");
 }
 
 // DIREITA (BOTAO)
 else if(ps2x.Button(PSB_PAD_RIGHT)){
    debug("[DEBUG] - DIREITA Pressionado!");
 }
 
 // ESQUERDA (BOTAO)
 else if(ps2x.Button(PSB_PAD_LEFT)){
    debug("[DEBUG] - ESQUERDA Pressionado!");
 }
 
 // CIMA (ANALOGICO ESQUERDO)
 else if(ps2x.Analog(PSS_LY) < 80){
     debug("[DEBUG] - CIMA (ANALOGICO ESQUERDO) -> Robo vai para frente...");
     
     // Vai pra Frente
     Hexapod_Frente();
 }
 
 // BAIXO (ANALOGICO ESQUERDO)
 else if(ps2x.Analog(PSS_LY) > 200){
      debug("[DEBUG] - BAIXO (ANALOGICO ESQUERDO)!");
 }
 
 // DIREITA (ANALOGICO ESQUERDO)
 else if(ps2x.Analog(PSS_LX) > 200){
      debug("[DEBUG] - DIREITA (ANALOGICO ESQUERDO)!");
 }
 
 // ESQUERDA (ANALOGICO ESQUERDO)
 else if(ps2x.Analog(PSS_LX) < 80){
      debug("[DEBUG] - ESQUERDA (ANALOGICO ESQUERDO)!");
 }
 
  // CIMA (ANALOGICO DIREITO)
 else if(ps2x.Analog(PSS_RY) < 80){
      debug("[DEBUG] - CIMA (ANALOGICO DIREITO)!");
 }
 
 // BAIXO (ANALOGICO DIREITO)
 else if(ps2x.Analog(PSS_RY) > 200){
       debug("[DEBUG] - BAIXO (ANALOGICO DIREITO)!");
 }
 
 // DIREITA (ANALOGICO DIREITO)
 else if(ps2x.Analog(PSS_RX) > 200){
       debug("[DEBUG] - DIREITA (ANALOGICO DIREITO)!");
 }
 
 // ESQUERDA (ANALOGICO DIREITO)
 else if(ps2x.Analog(PSS_RX) < 80){
       debug("[DEBUG] - ESQUERDA (ANALOGICO DIREITO)!");
 }
 
 delay(50);
     
}


//void enviaByte(byte dado, byte pino){
//  // Start bit
//  digitalWrite(pino, HIGH);
//  delayMicroseconds(TEMPO_70US);
//  
//  // Byte - Primeiro MSB
//  digitalWrite(pino, (dado >> 7));
//  delayMicroseconds(TEMPO_70US);  
//  
//  digitalWrite(pino, (dado >> 6)&0x01);
//  delayMicroseconds(TEMPO_70US);  
//  
//  digitalWrite(pino, (dado >> 5)&0x01);
//  delayMicroseconds(TEMPO_70US);  
//  
//  digitalWrite(pino, (dado >> 4)&0x01);
//  delayMicroseconds(TEMPO_70US);  
//  
//  digitalWrite(pino, (dado >> 3)&0x01);
//  delayMicroseconds(TEMPO_70US);
//
//  digitalWrite(pino, (dado >> 2)&0x01);
//  delayMicroseconds(TEMPO_70US);
//
//  digitalWrite(pino, (dado >> 1)&0x01);
//  delayMicroseconds(TEMPO_70US);
//
//  digitalWrite(pino, (dado&0x01));
//  delayMicroseconds(TEMPO_70US);    
//  
//  // Stop bit
//  digitalWrite(pino, LOW);
//  delayMicroseconds(TEMPO_70US);
//}
//  
//void comunicacao2(){
// // Para cada uma das patas do robo
// int i = 0;
// for(i = 0; i < 6; i++){
//    enviaByte(robo.patas[i].corpo, PINO_DOUT);
//    enviaByte(robo.patas[i].coxa, PINO_DOUT);
//    enviaByte(robo.patas[i].pinca, PINO_DOUT);   
// } 
//}




