#IFNDEF _GLOBAL_H_
#DEFINE _GLOBAL_H_

#include
/*
*OBSERVACAO: Arquivo nao mais usado.
*/
typedef struct _request {
    /**
    * Numero de argumentos na chamada do programa.
    */
    int argc;
    /**
    * Lista com os valores de entrada brutos, em caso de ser necessário.
    * (o que provavelmente nao vai ser)
    */
    char *argv[];
    /**
    * String contendo o nome do arquivo de entrada, seja ele uma imagem ou um codigo.
    */
    char *inputFile;
    /**
    * String contendo o nome do arquivo de saida.
    */
    char *outputFile;

} Request;

Request *newRequest();
void readArgs
#ENDIF
