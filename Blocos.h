#ifndef __BLOCOS
#define __BLOCOS
#include <stdio.h>
#include "Image.h"
#include "Huffman.h"

typedef struct{
        unsigned char ** blocos;
        
}Blocos;

Blocos* newBlocos();
void freeBlocos(Blocos* b);
void createBlocos(BMPImage * bmp, Blocos *b);
void writeHuffman(Huffman *h);


#endif
