/**
* Provem uma abstracao para leitura e escrita de *unsigned char*,
* compactando quando se encontra uma sequencia de caracteres iguais
* maior que 3.
*/
#ifndef __CARREIRA
#define __CARREIRA

#include "Huffman.h"
/**
* Caractere para controle da codificadao por carreira
*/
#define SKIPCHAR 85
/**
* Caso o usuario tente codificar SKIPCHAR, sera automaticamente
* substituido por REPLACECHAR para evitar problemas.
* Foi usado um valor aleatorio (84) pois o valor antigo (255) era muito usado
* apos a DCT, e a imagem perdia bastante a qualidade. Este valor aparentemente apresenta bons resultados.
*/
#define REPLACECHAR 84

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
