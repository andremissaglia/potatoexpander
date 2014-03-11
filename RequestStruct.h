#ifndef __RRQUESTSTRUCT
#define __REQUESTSTRUCT
#include <stdlib.h>
#include <stdio.h>
/**
* Esta estrutura sera passada para o metodo usado, o qual nao precisara lidar com entrada e saida.
*/
typedef struct {
    FILE *input;
    FILE *output;
} RequestStruct;

/**
* Cria uma nova estrutura.
*/
RequestStruct *newRequestStruct();

/**
* Apaga a estrutura fechando seus arquivos.
*/
void freeRequestStruct(RequestStruct *rs);
#endif

