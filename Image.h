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
/**
* Instancia um novo cabecalho.
*/
BMPHeader *newBMPHeader();
/**
* Le o cabecalho de um arquivo bmp.
*/
BMPHeader *readBMPHeader(FILE *fp);
/**
* Escreve o cabecalho bmp no arquivo, e preenche com zeros ate a posicao inicial para escrita da matriz.
*/
void writeBMPHeader(FILE *fp, BMPHeader *bmp);
/**
* Le um arquivo BMP e extrai suas informacoes.
*/
BMPImage *readBMP(FILE *fp);
/**
* Escreve um arquivo BMP com a matriz e cabecalho dados.
*/
void writeBMP(FILE *fp, BMPImage *bmp);
/**
* Calcula os valores "bitmap_size" e "size" do cabecalho do arquivo
*/
void make_BMPHeader(BMPImage *bmp);
/**
* Libera a memoria alocada pelo BMPImage.
*/
void freeBMP(BMPImage *bmp);

#endif

