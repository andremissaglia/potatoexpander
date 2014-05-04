#ifndef __CARREIRA
#define __CARREIRA

#include "Huffman.h"
//Caractere para controle da codificadao por carreira
#define SKIPCHAR 255
//Caso o usuario tente codificar SKIPCHAR, sera automaticamente
//substituido por REPLACECHAR para evitar problemas
#define REPLACECHAR 254

/**
* Estrutura basica com os atributos de "Carreira".
*/
typedef struct {
    unsigned char current;
    unsigned char count;
    Huffman *huffman;
} Carreira;

/**
* Instancia uma nova "Carreira".
*/
Carreira *newCarreira(Huffman *h);
/**
* Abstrai a escrita por carreira de modo a ser usado por outros modulos.
*/
void RLWriteChar(Carreira *rl, unsigned char c);
/**
* Abstrai a leitura por carreira.
*/
unsigned char RLReadChar(Carreira *rl);
/**
* Termina de escrever os dados no "buffer".
*/
void flush(Carreira *rl);

#endif // __CARREIRA
