#include "Decompress.h"
#include "Image.h"
#include "Blocos.h"
#include "Huffman.h"
void decompress(FILE *input, FILE *output){
    Huffman *h = readHuffmanFile(input);

    Blocos *b = readBlocksHuffman(h,input);
    printf("hey1\n");
    BMPImage *bmp = recriateImage(b);
    printf("hey2\n");

    writeBMP(output,bmp);
}


