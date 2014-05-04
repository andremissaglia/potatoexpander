/*
* Andre Badawi Missaglia 8066523
* Jose Carlos Marquetti Junior 6909564
* Newton Jhun Koga 6426660
*/

/**
* Arquivo inicial do sistema.
* Contem um shell implementado, e chamara arquivos separados para os comandos especificos.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CompressRequest.h"
#include "DecompressRequest.h"

#define LINE_BUFFER 800
const int debug=0;
/**
* Le uma linha inteira, com no maximo sizeMax-1 caracteres.
* Caracteres alem desse limite serao ignorados.
*/
void readLine(char *buffer, int sizeMax);
/**
* A partir de uma linha, separa seus tokens e retorna.
* Necessario passar "&argc" que retorna a quantidade de tokens.
*/
char **getTokens(int *argc, char *buffer);
/**
* Exibe comandos disponiveis.
*/
void help(int argc, char *argv[]);

int main(int argc, char *argv[]){
	char buffer[LINE_BUFFER];
	char **commandArgv;
	int commandArgc;
    printf("# Image compressor for SCC0261 - Multimedia.\n");
    printf("# Type 'help' for available commands.\n");
	//Sempre esperando por novos comandos
    while(1){
        //Indica ao usuario que o terminal esta pronto para receber input
        printf("potato> ");
        //le a linha inteira, considerada um comando, e a processa.
        readLine(buffer,LINE_BUFFER);
        commandArgv = getTokens(&commandArgc, buffer);

        if(commandArgc == 0) continue;
        if(commandArgv[0][0] == '#') continue;

        if(strcmp(commandArgv[0],"help") == 0){
            help(commandArgc, commandArgv);
        } else if(strcmp(commandArgv[0],"quit") == 0){
            break;
        } else if(strcmp(commandArgv[0],"q") == 0){
            break;
        } else if(strcmp(commandArgv[0],"compress") == 0){
            compressInput(commandArgc, commandArgv);
        } else if(strcmp(commandArgv[0],"decompress") == 0){
            decompressInput(commandArgc, commandArgv);
        } else {
            printf("Shell: Command '%s' not found. See 'help' for available commands.\n",commandArgv[0]);
        }



        if(debug){
            int i;
            for(i = 0; i < commandArgc; i++){
                printf("{%s}\n", commandArgv[i]);
            }
        }
        free(commandArgv);
    }
    return EXIT_SUCCESS;
}

void readLine(char *buffer, int sizeMax){
    int pos = 0;
    char aux;
    //Le caracter por caractere ateh terminar a linha ou atingir o limite.
    while(aux=getchar(),aux != '\n' && pos < sizeMax-1){
        //desconsidera alguns tipos de caracteres.
        if(aux != '\r');
            buffer[pos++] = aux;
    }
    buffer[pos] = '\0';
    //Se ainda nao achou um \n, continua lendo ateh achar um.
    while(aux != '\n'){
        aux = getchar();
    }
}

char **getTokens(int *argc, char *buffer){
    char **commandArgv = NULL;
    char *token;
    int counter = 0;
    token = strtok(buffer, " \t");
    while(token != NULL){
        commandArgv = (char **) realloc(commandArgv,(counter + 1)*sizeof(char *));
        commandArgv[counter++] = token;
        token = strtok(NULL, " \t");
    }
    *argc = counter;
    return commandArgv;
}

void help(int argc, char *argv[]){
    if(argc > 1){
        if(strcmp(argv[1],"compress") == 0){
            showCompressHelp();
        } else {
            printf("Help: Unknown command '%s', see 'help' for available commands.\n", argv[1]);
        }
        return;
    }
    printf("Usage:\n");
    printf("\t<command> [arg [arg [arg [...]]\n");
    printf("\n\n");
    printf("Available Commands:\n");
    printf("\thelp\t\tShows this help.\n");
    printf("\tquit or q\tShows this help.\n");
    printf("\tcompress\tCompresses a given input image.\n");
    printf("\tdecompress\tDecompresses a given input compressed image.\n");
    printf("\n\n");
    printf("See 'help <command>' to read about a specific command.\n");
}
