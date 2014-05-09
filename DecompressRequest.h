/**
* Este arquivo eh responsavel por tratar o comando 'decompress'
*/

#ifndef __DECOMPRESSREQUEST
#define __DECOMPRESSREQUEST

/**
* Metodo chamado quando um comando do tipo 'decompress [args..]' eh executado.
* Se o comando estiver bem formado, encaminhara para compressao do arquivo.
*/
void decompressInput(int argc, char *argv[]);
/**
* Mostra como este comando deve ser usado.
*/
void showDecompressHelp();
#endif

