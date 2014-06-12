#ifndef __BLOCOS
#define __BLOCOS
#include <stdio.h>
#include "Image.h"
#include "Carreira.h"
/**
* O codigo gerara blocos de 8x8, e espera que a imagem seja de dimensoes
* multiplas deste valor.
*/
#define BLOCKSIZE 8
/**
* Dado uma posicao X,Y; encontrar a posicao em uma matriz linearizada
*/
#define LINEAR_AT(x,y,columns) x+y*columns

/**
*  A imagem eh armazenada nesta estrutura como um conjunto de blocos 8x8.
*/
typedef struct{
        /**
        * Vetor de blocos.
        * Os blocos de 8x8 sao linearizados em um vetor de 64.
        */
        unsigned char ** blocos;
        /**
        * Numero de blocos no vetor "blocos"
        */
        unsigned int nblocos;
        /**
        * Largura da imagem em *numero de blocos*.
        * Largura em pixels = width * BLOCKSIZE
        */
        unsigned int width;
        /**
        * Altura da imagem em *numero de blocos*.
        * Altura em pixels = height * BLOCKSIZE
        */
        unsigned int height;
}Blocos;

/**
* Instancia um novo conjunto de blocos.
*/
Blocos* newBlocos();
/**
* Libera a memoria dos blocos alocados.
*/
void freeBlocos(Blocos* b);
/**
* Decodifica uma imagem BMP em um conjunto de blocos.
*/
void createBlocos(BMPImage * bmp, Blocos *b);
/**
* Cria uma imagem BMP baseado em um conjunto de blocos.
*/
BMPImage *recriateImage(Blocos *b);
/**
* Escreve os blocos, codificados como carreira.
*/
void writeRL(Blocos *b, Carreira *rl);
/**
* Le os blocos que estavam codificados como carreira.
*/
Blocos *readBlocksRL(Carreira *rl);

#endif
