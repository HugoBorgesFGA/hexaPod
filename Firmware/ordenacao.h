#ifndef ORDENACAO_H_
#define ORDENACAO_H_

#include "global.h"
#include "msp430g2553.h"
#include <io.h>
#include <stdint.h>

// Organiza o grupo de 6 pwms em ordem crescente, gerando máscaras para a GPIO
// e agrupando valores cuja diferenca de duty cycle eh inferior ao limiar de agrupamento
void ordenar(uint8_t entrada[6], uint8_t limiar_agrupamento, uint8_t *final_dc, uint8_t *final_mascara);

#endif
