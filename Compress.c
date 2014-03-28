#include "Compress.h"
#include "Image.h"
#include "Blocos.h"
#include "Huffman.h"
void compress(FILE *input, FILE *output){
        BMPImage *img= readBMP(input);
        Blocos *b = newBlocos();
        createBlocos(img,b);

        Huffman *h = newHuffman();

        writeHuffman(b,h);
        criaArvore(h, 0);
        criaDicionario(h);

        writeall(h, output);
        freeBMP(img);

}

