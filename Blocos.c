#include "Blocos.h"
#include "Huffman.h"
#include <stdlib.h>
/**
* Guarda uma das matrizes RGB no formato de uma lista de blocos, sendo cada bloco de 64 bytes.
*/
void writeBlocks(unsigned char **matrix, int width, int height, unsigned char **blocks);
/**
* Converte uma parte dos blocos de 64 bytes em uma das componentes RGB.
*/
unsigned char **makeMatrix(int width, int height, unsigned char **blocks);
Blocos* newBlocos(){
    Blocos *b = (Blocos*) malloc(sizeof(Blocos));
    b->nblocos =0;
    return b;
}
void freeBlocos(Blocos* b){
    int i;
    for(i = 0; i < b->nblocos; i++){
        free(b->blocos[i]);
    }
    free(b->blocos);
    free(b);
}
void createBlocos(BMPImage *bmp, Blocos *b){
    //Assumindo que as dimensoes sao multiplas de 8
    b->width = bmp->header->width / BLOCKSIZE;
    b->height = bmp->header->height / BLOCKSIZE;
    b->nblocos = 3*b->width*b->height;
    b->blocos = (unsigned char **) malloc(b->nblocos*sizeof(unsigned char*));
    writeBlocks(bmp->R,b->width,b->height,b->blocos);
    writeBlocks(bmp->G,b->width,b->height,b->blocos+b->width*b->height);
    writeBlocks(bmp->B,b->width,b->height,b->blocos+2*b->width*b->height);


}
BMPImage *recriateImage(Blocos *b){
    BMPImage *bmp = (BMPImage *) malloc(sizeof(BMPImage));
    bmp->header = newBMPHeader();
    bmp->header->width = BLOCKSIZE*b->width;
    bmp->header->height = BLOCKSIZE*b->height;
    bmp->R = makeMatrix(b->width,b->height,b->blocos);
    bmp->G = makeMatrix(b->width,b->height,b->blocos+b->width*b->height);
    bmp->B = makeMatrix(b->width,b->height,b->blocos+2*b->width*b->height);
    make_BMPHeader(bmp);
    return bmp;
}
void writeRL(Blocos *b, Carreira *rl){
    int i,j;
    writeInt(rl->huffman,b->width);
    writeInt(rl->huffman,b->height);
    for(i = 0; i < b->nblocos;i++){
        for(j = 0; j <BLOCKSIZE*BLOCKSIZE;j++){


            RLWriteChar(rl,b->blocos[i][j]);
        }
    }
}
void writeBlocks(unsigned char **matrix, int width, int height, unsigned char **blocks){
    int i,j;//posicao do bloco
    int x,y; //coordenadas internas ao bloco
    //para cada bloco
    for(i = 0; i < width;i++){
        for(j = 0; j < height; j++){
            blocks[LINEAR_AT(i,j,height)] = (unsigned char *) malloc(BLOCKSIZE*BLOCKSIZE*sizeof(unsigned char));
            //para cada pixel referente
            for(x = 0; x < BLOCKSIZE; x++){
                    for(y = 0; y < BLOCKSIZE; y++){
                            blocks[LINEAR_AT(i,j,height)][LINEAR_AT(x,y,BLOCKSIZE)] = matrix[i*BLOCKSIZE+x][j*BLOCKSIZE+y];
                    }
            }
        }
    }
}
unsigned char **makeMatrix(int width, int height, unsigned char **blocks){
        unsigned char **matrix;
        int i,j;

        //alocar matriz
        matrix = (unsigned char **) malloc(width*BLOCKSIZE*sizeof(unsigned char *));
        for(i = 0; i < BLOCKSIZE*width; i++){
            matrix[i] = (unsigned char *) malloc(height*BLOCKSIZE*sizeof(unsigned char));
        }
        //reconstruir matriz
        for(i = 0; i < width*BLOCKSIZE; i++){
            for(j = 0; j < height*BLOCKSIZE; j++){
                matrix[i][j] = blocks[LINEAR_AT(i/BLOCKSIZE,j/BLOCKSIZE, height)][LINEAR_AT(i%BLOCKSIZE,j%BLOCKSIZE, BLOCKSIZE)];
            }
        }
        return matrix;
}
Blocos *readBlocksRL(Carreira *rl){
    int i,j;
    Blocos *b = newBlocos();
    b->width = readInt(rl->huffman);
    b->height = readInt(rl->huffman);
    b->nblocos = 3*b->width*b->height*BLOCKSIZE*BLOCKSIZE;
    b->blocos = (unsigned char **) malloc(b->nblocos*sizeof(unsigned char*));
    for(i = 0; i < b->nblocos;i++){
        b->blocos[i] = (unsigned char *) malloc(BLOCKSIZE*BLOCKSIZE*sizeof(unsigned char));
        for(j = 0; j <BLOCKSIZE*BLOCKSIZE;j++){
            b->blocos[i][j] = RLReadChar(rl);
        }
    }
    return b;
}
