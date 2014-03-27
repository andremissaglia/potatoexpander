#ifndef __HUFFMAN
#define __HUFFMAN
#include <stdio.h>

typedef struct _noArvore noArvore;
struct _noArvore{

        char valor;
        int freq;
        noArvore* esq; 
        noArvore* dir; 
}

typedef struct {

        char* textoEntrada;
        char buffer;
        int freq[256];
        noArvore* raiz;//guarda a arvore de Huffman 
}Huffman;

Huffman* newHuffman(); //cria a struct de Huffman
void freeHuffman(Huffman* h);//libera a struct de Huffman
void writechar(Huffman *h, char c);//escreve o char no texto temporario 
void writeint(Huffman *h, char c);
void writeall(Huffman *h, FILE* output);//escreve no arquivo, chama as funcoes write e cria arvore de huffman

#endif