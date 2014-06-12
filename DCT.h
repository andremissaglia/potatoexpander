/**
* Este arquivo eh responsavel por realizar a transformada discreta
* dos cossenos (DCT), juntamente com a quantizacao.
* A etapa de quantizacao consiste em dividir a matriz transformada
* por um conjunto de valores preestabelecidos.
*/
#ifndef __DCT
#define __DCT

#include "Blocos.h"

/**
* Valor pelo qual a matriz de quantizacao sera multiplicado.
* Quanto maior o valor, maior a compressao, mas pior a qualidade.
* Deve ser um valor maior que 0.
*/
#define COMPRESS_FACTOR 1

/**
* Realiza a transformada discreta dos cossenos e a quantização;
*/
void DCT(Blocos *b);
/**
* Realiza a transformada discreta  inversa dos cossenos, voltando
* a imagem original e com perda de qualidade.
*/
void IDCT(Blocos *b);

#endif // __DCT
