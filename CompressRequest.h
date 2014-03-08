/**
* Este arquivo eh responsavel por tratar o comando 'compress'
*/

#ifndef __COMPRESSREQUEST
#define __COMPRESSREQUEST

/**
* Metodo chamado quando um comando do tipo 'compress [args..]' eh executado.
* Se o comando estiver bem formado, encaminhara para compressao do arquivo.
*/
void compressInput(int argc, char *argv[]);
/**
* Mostra como este comando deve ser usado.
*/
void showCompressHelp();
#endif
