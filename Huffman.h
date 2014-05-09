#ifndef __HUFFMAN
#define __HUFFMAN
#include <stdio.h>
#include <string.h>

/**
* No da arvore de Huffman
*/
typedef struct _noArvore noArvore;
struct _noArvore{
        char valor;
        int freq;
        noArvore* esq;
        noArvore* dir;
};

/**
* Verbete do dicionario de Huffman
*/
typedef struct {
        char valor;
        char* huffCode;
        int frequencia;
}Verbete;

/**
* Dicionario de Huffman
*/
typedef struct {
        Verbete** palavra;
        int nVerbetes;
}Dicionario;

/**
* Objeto criado para controle da compressao em Huffman.
*/
typedef struct {
        int textSize;//tamanho do texto(3*area da imagem)
        unsigned char* textoEntrada;//texto de entrada que sera compactado
        unsigned char buffer;
        char bufferPos;//valor entre 0 e 7 indicando quanto o bit deve ser deslocado para ser inserido no buffer
        int freq[256];//vetor que guarda as frequencias de cada um dos possiveis valores de uma componente de cor dor RGB(1 byte).
        noArvore* arvore; //guarda a arvore de Huffman
        Dicionario* dicionario;//guarda o dicionario de huffman
        int nVerbetes;//numero de verbetes do dicionario

        long textoEntradaPos; // Necessario para as operacoes de leitura, indica em que posicao de "textoEntrada" esta o proximo byte
}Huffman;


/**
* Cria a struct de Huffman
*/
Huffman* newHuffman();
/**
* Libera a struct de Huffman
*/
void freeHuffman(Huffman* h);
/**
* Escreve o caracter q esta no buffer da struct h no arquivo de saida
*/
void writeChar(Huffman *h, unsigned char c);
void writeInt(Huffman *h, int i);


/**
* Cria a arvore de Huffman e guarda dentro da struct h na variavel arvore.
* A flagDescompressao quando eh 1 indica que a funcao nao deve extrair o vetor de frequencias de um texto de entrada.
* Tendo h, copiar o vetor de frequencias extraido do cabecalho da imagem para o vetor h->freq. (implementar a copia?)
*/
void criaArvore(Huffman *h,int flagDescompressao );

/**
* Cria o dicionario de Huffman e guarda dentro da struct h na variavel dicionario
*/
void criaDicionario(Huffman *h);
/**
* Imprime o dicionario de Huffman na tela. Usar apenas depois de chamar a funcao criaDicionario(Huffman *h)
*/
void imprimeDicionario(Huffman *h);
/**
* Converte o texto de entrada para huffman, então converte huffman para char e chama writeChar(Huffman *h, FILE* output) p/ escrever no arquivo
*/
void writeall(Huffman *h, FILE* output);

/**
* Le a arvore de um arquivo
*/
Huffman* readHuffmanFile(FILE *input);
/**
* Le o proximo char
*/
char readChar(Huffman *h);
/**
* Lê o proximo Int
*/
int readInt(Huffman *h);

#endif
