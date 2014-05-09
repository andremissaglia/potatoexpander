#include "Blocos.h"
#include <stdlib.h>


void vetorizar(Blocos *b){
int i,j,ordem;
unsigned char *a;
int mask[64] = {0,
                8,1,
                2,9,16,
                24,17,10,3,
                4,11,18,25,32,
                40,33,26,19,12,5,
                6,13,20,27,34,41,48,
                56,49,42,35,28,21,14,7,
                15,22,29,36,43,50,57,
                58,51,44,37,30,23,
                31,38,45,52,59,
                60,53,46,39,
                47,54,61,
                62,55,
                63};
   
   


    for(i=0; i < b->nblocos;i++){
       a = (unsigned char*)malloc(sizeof(unsigned char)*(64));
       for(j=0;j<64;j++){
          a[j] = b->blocos[i][mask[j]];
       
       }
       
       free(b->blocos[i]);
       b->blocos[i] = a;
                                     
    }   
}



void desvetorizar(Blocos *b){
int i,j;
unsigned char *a;
int mask[64] = {0,
                8,1,
                2,9,16,
                24,17,10,3,
                4,11,18,25,32,
                40,33,26,19,12,5,
                6,13,20,27,34,41,48,
                56,49,42,35,28,21,14,7,
                15,22,29,36,43,50,57,
                58,51,44,37,30,23,
                31,38,45,52,59,
                60,53,46,39,
                47,54,61,
                62,55,
                63};

    
    for(i=0; i < b->nblocos;i++){
      a = (unsigned char*)malloc(sizeof(unsigned char)*(64));
                                     
       for(j=0;j<64;j++){
          a[mask[j]] = b->blocos[i][j];
       
       }
       
       free(b->blocos[i]);
       b->blocos[i] = a;
                                     
    } 
}
