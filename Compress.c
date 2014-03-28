#include "Image.h"
#include "Blocos.h"
void compress(FILE *input, FILE *output){
        BMPImage *img= readBMP(input);
        Blocos *b = newBlocos();
        createBlocos(img,b);
        BMPImage *rec = recriateImage(b);
        writeBMP(output,rec);
        freeBMP(img);
        freeBMP(rec);

}

