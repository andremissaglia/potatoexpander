#include "Decompress.h"
#include "Image.h"
#include "Blocos.h"
#include "Huffman.h"

#include <stdlib.h>
void decompress(FILE *input, FILE *output){
    Huffman *h = readHuffmanFile(input);
    Carreira *rl = newCarreira(h);

    Blocos *b = readBlocksRL(rl);
    desvetorizar(b);
    BMPImage *bmp = recriateImage(b);
    writeBMP(output,bmp);
    free(rl);
    freeHuffman(h);
    freeBlocos(b);
    freeBMP(bmp);
}


