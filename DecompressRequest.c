#include "DecompressRequest.h"
#include "Decompress.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void decompressInput(int argc, char *argv[]){
    if(argc == 2 && strcmp(argv[1],"help") == 0){
        showDecompressHelp();
        return;
    }
    if(argc != 3){
        printf("decompress: Syntax error. See 'decompress help' for correct use.\n");
        showDecompressHelp();
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
    decompress(input, output);
    fclose(input);
    fclose(output);
}

void showDecompressHelp(){
    printf("Usage:\n");
    printf("\tdecompress <inputFile> <outputFile>\n");
    printf("\n\n");
    printf("<inputFile>\t O nome do arquivo comprimido.\n");
    printf("<outputFile>\t Imagem .bmp de saida.\n");
}

