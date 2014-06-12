#ifndef __VETORIZACAO
#define __VETORIZACAO

#include "Blocos.h"

/**
* Transforma a matriz de 8x8 em um vetor de 64 posicoes reordenado.
*/
void vetorizar(Blocos *b);
/**
* Realiza uma trainsformação inversa no vetor para a matriz de 8x8 original.
*/
void desvetorizar(Blocos *b);
#endif // __VETORIZACAO
