#include "ordenacao.h"

void ordenar(uint8_t entrada[6], uint8_t limiar_agrupamento, uint8_t *final_dc, uint8_t *final_mascara){
	// Efetua o sort no vetor, preenchendo com 0
	uint8_t dc[6] = {0,0,0,0,0,0};
	uint8_t pinos[6] = {0,0,0,0,0,0};


	uint8_t i = 6, j = 0;
	uint8_t temp_dc = 0, temp_pino = 0;

	// Copia entrada pra saida
	for(j = 0; j < 6; j++){
		dc[j] = entrada[j];
		pinos[j] = (1 << (5 - j));
	}

	for(i = 6 - 1; i >= 1; i--){
		for(j = 0; j < i; j++){
			if (dc[j] > dc[j+1]){
				// Switch
				temp_dc = dc[j];
				temp_pino = pinos[j];

				dc[j] = dc[j+1];
				pinos[j] = pinos[j+1];

				dc[j+1] = temp_dc;
				pinos[j+1] = temp_pino;
			}
		}
	}

	// Simplifica:

	// Percorre até o PENULTIMO item da lista ordenada de forma crescente
	// zerando os elementos que já tiveram uma ocorrência
	for(i = 0; i < 5; i++){
		j = 1;
		while((dc[i+j] - dc[i]) < limiar_agrupamento){
			dc[i+j] = 0;

			if ((i + j) < 5)
				j++;
			else
				break;
		}
		i += j-1;
	}

	// Lógica de agrupamento
	uint8_t lastNonZero = 0;

	final_dc[0] = dc[0];
	final_mascara[0] = pinos[0];

	for(i = 1; i < 6; i++){
		// Se precisar ser agrupado
		if (dc[i] == 0){
			final_mascara[lastNonZero] |=  pinos[i];
		}else{
			lastNonZero = i;

			final_dc[i] = dc[i];
			final_mascara[i] = pinos[i];
		}
	}


	// Remove buracos
	for(i = 0; i < 6; i++){
		if (final_mascara[i] == 0){
			j = ((i + 1) > 5) ? 5 : i + 1;
			while( (final_mascara[j] == 0) && j != 5){
				j = ((j + 1) > 5) ? 5 : j + 1;
			}

			//final_dc[i] = final_dc[j];
			final_dc[i] = (i > 0) ? final_dc[j] - final_dc[i-1] : final_dc[j];
			final_mascara[i] = final_mascara[j];

			final_dc[j] = 0;
			final_mascara[j] = 0;
		}
	}
}
