#include "CompressRequest.h"
#include "RequestStruct.h"
#include <stdlib.h>
#include <stdio.h>

void compressInput(int argc, char *argv[]){
    if(argc != 3){
        printf("compress: Syntax error. See 'compress help' for correct use.\n");
        return;
    }
    RequestStruct *request = newRequestStruct();
    request->input = fopen(argv[1],"rb");
    if(request->input == NULL) {
        printf("compress: file '%s' does not exist.\n", argv[1]);
        return;
    }
    request->output = fopen(argv[1],"wb");
    if(request->output == NULL) {
        printf("compress: could not save on file %s.\n", argv[1]);
        return;
    }
}

void showCompressHelp(){
    printf("Usage:\n");
    printf("\tcompress <inputFile> <outputFile>\n");
    printf("\n\n");
    printf("<inputFile>\t A BMP file name to be compressed.\n");
    printf("<outputFile>\t The output file name for the compressed file.\n");
}
