#ifndef __HUFFMAN
#define __HUFFMAN
#include <stdio.h>

typedef struct _noArvore noArvore;
struct _noArvore{

        char valor;
        int freq;
        noArvore* esq; 
        noArvore* dir; 
};

typedef struct {
        int textSize;
        char* textoEntrada;
        char buffer;
        int freq[256];
        noArvore* raiz; 
}Huffman;

Huffman* newHuffman(int tamanhoTexto, char* texto); //cria a struct de Huffman
void freeHuffman(Huffman* h);//libera a struct de Huffman
void writechar(Huffman *h, char c);//pega char por char do textoEntrada, codifica e poe no buffer
void writeint(Huffman *h, char c);
void contaFreq(Huffman *h);
void criaArvore(Huffman *h);
void writeall(Huffman *h, FILE* output);//escreve no arquivo, chama as funcoes write e cria arvore de huffman

#endif
