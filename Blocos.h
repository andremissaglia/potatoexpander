#ifndef __BLOCOS
#define __BLOCOS
#include <stdio.h>
#include "Image.h"
#include "Huffman.h"
/**
* O codigo gerara blocos de 8x8, e espera que a imagem seja de dimensoes
* multiplas deste valor.
*/
#define BLOCKSIZE 8
/**
* Dado uma posicao X,Y; encontrar a posicao em uma matriz linearizada
*/
#define LINEAR_AT(x,y,columns) x+y*columns


typedef struct{
        unsigned char ** blocos;
        int nblocos;
        int width;
        int height;
}Blocos;

Blocos* newBlocos();
void freeBlocos(Blocos* b);
void createBlocos(BMPImage * bmp, Blocos *b);
BMPImage *recriateImage(Blocos *b);
void writeHuffman(Blocos *b, Huffman *h);
Blocos *readBlocksHuffman(Huffman *h, FILE *input);

#endif
