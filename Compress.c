#include "Image.h"

void compress(FILE *input, FILE *output){
        BMPImage *img= readBMP(input);
        writeBMP(output,img);
        freeBMP(img);
}
