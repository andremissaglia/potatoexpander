#include "CompressRequest.h"
#include "Compress.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void compressInput(int argc, char *argv[]){
    if(argc == 2 && strcmp(argv[1],"help") == 0){
        showCompressHelp();
        return;
    }
    if(argc != 3){
        printf("compress: Syntax error. See 'compress help' for correct use.\n");
        showCompressHelp();
        return;
    }
    FILE *input = fopen(argv[1],"rb");
    if(input == NULL) {
        printf("compress: file '%s' does not exist.\n", argv[1]);
        return;
    }
    FILE *output = fopen(argv[2],"wb");
    if(output == NULL) {
        printf("compress: could not save on file %s.\n", argv[1]);
        return;
    }
    compress(input, output);
    fclose(input);
    fclose(output);
}

void showCompressHelp(){
    printf("Usage:\n");
    printf("\tcompress <inputFile> <outputFile>\n");
    printf("\n\n");
    printf("<inputFile>\t O nome do arquivo BMP a ser comprimido.\n");
    printf("<outputFile>\t Nome do arquivo de saida.\n");
}
