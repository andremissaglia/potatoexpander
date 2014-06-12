/**
* Gerencia os modulos usados na descompressao do arquivo
*/
#ifndef __DECOMPRESS
#define __DECOMPRESS

#include <stdio.h>
/**
* Abre o arquivo de entrada *input* como BMP, extrai e salva
* no arquivo de saida *output*
*/
void decompress(FILE *input, FILE *output);

#endif

