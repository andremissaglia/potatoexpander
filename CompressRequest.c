#include "CompressRequest.h"


void compressInput(int argc, char *argv[]){
    printf("compress: Syntax error. See 'compress help' for correct use.");
}

void showCompressHelp(){
    printf("Usage:\n");
    printf("\tcompress <inputFile> <outputFile>\n");
    printf("\n\n");
    printf("<inputFile>\t A BMP file name to be compressed.\n");
    printf("<outputFile>\t The output file name for the compressed file.\n");
}
