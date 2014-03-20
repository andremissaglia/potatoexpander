#ifndef __IMAGE
#define __IMAGE
#include <stdio.h>


/**
* Esta estrutura contem o cabecalho da imagem bmp
* Contem informacoes do BITMAPINFOHEADER, sendo que qualquer outra coisa eh desconsiderada
* http://en.wikipedia.org/wiki/BMP_file_format
*/
typedef struct {
    //Bitmap File Header
    unsigned short type;
    unsigned int size;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int starting_pos;
    //DIP Header
    unsigned int DIPSize;
    int width;
    int height;
    unsigned short color_planes;
    unsigned short bpp;
    unsigned int compression_method;
    unsigned int bitmap_size;
    int resolution_x;
    int resolution_y;
    unsigned int ncolors;
    unsigned int important_colors;
} BMPHeader;
/**
* Estrutura contendo a imagem em si.
*/
typedef struct {
    BMPHeader *header;
    //Raw_Data
    unsigned char **R;
    unsigned char **G;
    unsigned char **B;

} BMPImage;
BMPHeader *newBMPHeader();
BMPHeader *readBMPHeader(FILE *fp);
BMPImage *readBMP(FILE *fp);
void freeBMP(BMPImage *bmp);

#endif

