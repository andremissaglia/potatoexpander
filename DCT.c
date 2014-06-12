#include "DCT.h"
#include <math.h>
#include <stdlib.h>
#define PI 3.141592653589793238
#define SQRT2 1.41421356237309504880

double L[] = {
        16, 11, 10, 16, 24, 40, 51, 61,
        12, 12, 14, 19, 26, 58, 60, 55,
        14, 13, 16, 24, 40, 57, 69, 56,
        14, 17, 22, 29, 51, 87, 80, 62,
        18, 22, 37, 56, 68, 109, 103, 77,
        24, 35, 55, 64, 81, 104, 113, 92,
        49, 64, 78, 87, 103, 121, 120, 101,
        72, 92, 95, 98, 112, 100, 103, 99
        };
void DCT_block(unsigned char *src, unsigned char *dest){

    int i,j,x,y;
    double sum, partial;
    unsigned char teste;
    char teste_signed;
    int result = 0;
    for(i = 0; i < BLOCKSIZE; i++){
        for(j = 0; j < BLOCKSIZE;j++){
            sum = 0;
            for(x = 0; x < BLOCKSIZE; x++){
                for(y = 0; y< BLOCKSIZE; y++){
                    teste = src[LINEAR_AT(x,y,BLOCKSIZE)];
                    partial = teste;
                    partial -= 128;
                    partial *= cos((2*x+1)*i*PI/16.0f);
                    partial *= cos((2*y+1)*j*PI/16.0f);
                    sum += partial;
                }
            }
            sum = sum/4;
            if(i == 0){
                sum = sum / SQRT2;
            }
            if(j == 0){
                sum = sum / SQRT2;
            }
            sum = sum / L[LINEAR_AT(i,j,BLOCKSIZE)]/ COMPRESS_FACTOR;

            result = round(sum);
            //if(i == 0 && j == 0 && result > 120)printf("%d %d: %d\n", i,j,result);

            teste_signed = result;

            //printf("%5lf\t", sum);
            dest[LINEAR_AT(i,j,BLOCKSIZE)] = teste_signed;
        }
        //printf("\n");
    }
    //printf("\n");
}

void IDCT_block(unsigned char *src, unsigned char *dest){
    int i,j,x,y;
    double sum, partial;
    char teste_signed;
    for(x = 0; x < BLOCKSIZE; x++){
        for(y = 0; y < BLOCKSIZE;y++){
            sum = 0;
            for(i = 0; i < BLOCKSIZE; i++){
                for(j = 0; j< BLOCKSIZE; j++){
                    teste_signed = src[LINEAR_AT(i,j,BLOCKSIZE)];
                    partial =  teste_signed;
                    partial *= L[LINEAR_AT(i,j,BLOCKSIZE)]*COMPRESS_FACTOR;
                    partial *= cos((2*x+1)*i*PI/16.0f);
                    partial *= cos((2*y+1)*j*PI/16.0f);
                    if(i == 0){
                        partial = partial /SQRT2;
                    }
                    if(j == 0){
                        partial = partial /SQRT2;
                    }
                    sum += partial;
                }
            }
            sum = sum/4;
            sum += 128;
            dest[LINEAR_AT(x,y,BLOCKSIZE)] = round(sum);
        }
    }
}

void DCT(Blocos *b){
    int i;
    unsigned char *buffer = (unsigned char *) malloc(64*sizeof(unsigned char));
    unsigned char *aux;

    for(i = 0; i < b->nblocos; i++){
        DCT_block(b->blocos[i], buffer);
        aux = buffer;
        buffer = b->blocos[i];
        b->blocos[i] = aux;

    }
    free(buffer);

}
void IDCT(Blocos *b){
    int i;
    unsigned char *buffer = (unsigned char *) malloc(64*sizeof(unsigned char));
    unsigned char *aux;
    for(i = 0; i < b->nblocos; i++){
        IDCT_block(b->blocos[i], buffer);
        aux = buffer;
        buffer = b->blocos[i];
        b->blocos[i] = aux;

    }
    //printf("_.%d\n", sum);
    free(buffer);
}
