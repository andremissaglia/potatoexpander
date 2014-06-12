#include "Compress.h"
#include "Image.h"
#include "Blocos.h"
#include "Huffman.h"
#include "Carreira.h"
#include "Vetorizacao.h"
#include "DCT.h"
#include <stdlib.h>
void compress(FILE *input, FILE *output){
        BMPImage *img= readBMP(input);
        Blocos *b = newBlocos();

        createBlocos(img,b);
        Huffman *h = newHuffman();
        Carreira *rl = newCarreira(h);
        DCT(b);
        vetorizar(b);
        writeRL(b,rl);

        flush(rl);

        criaArvore(h, 0);
        criaDicionario(h);
        writeall(h, output);
        freeBMP(img);
        freeHuffman(h);
        freeBlocos(b);
        free(rl);
}
