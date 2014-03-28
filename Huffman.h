#ifndef __HUFFMAN
#define __HUFFMAN
#include <stdio.h>
#include <string.h>

//no da arvore de Huffman
typedef struct _noArvore noArvore;
struct _noArvore{

        char valor;
        int freq;
        noArvore* esq; 
        noArvore* dir; 
};

//verbete do dicionario de Huffman
typedef struct {
        char valor;
        char* huffCode;
        int frequencia;
}Verbete;


//Dicionario de Huffman
typedef struct {
        Verbete** palavra;
        int nVerbetes;
}Dicionario;

//Objeto criado para controle da compressao em Huffman. 
typedef struct {
        int textSize;//tamanho do texto(3*area da imagem)
        char* textoEntrada;//texto de entrada que sera compactado
        char buffer;
        int freq[256];//vetor que guarda as frequencias de cada um dos possiveis valores de uma componente de cor dor RGB(1 byte).
        noArvore* arvore; //guarda a arvore de Huffman
        Dicionario* dicionario;//guarda o dicionario de huffman
        int nVerbetes;//numero de verbetes do dicionario
}Huffman;



Huffman* newHuffman(int tamanhoTexto, char* texto); //cria a struct de Huffman
void freeHuffman(Huffman* h);//libera a struct de Huffman
void writeChar(Huffman *h, FILE* output);//escreve o caracter q esta no buffer da struct h no arquivo de saida



//cria a arvore de Huffman e guarda dentro da struct h na variavel arvore. 
//A flagDescompressao quando eh 1 indica que a funcao nao deve extrair o vetor de frequencias de um texto de entrada. 
//Tendo h, copiar o vetor de frequencias extraido do cabecalho da imagem para o vetor h->freq. (implementar a copia?)
void criaArvore(Huffman *h,int flagDescompressao );


void criaDicionario(Huffman *h);//cria o dicionario de Huffman e guarda dentro da struct h na variavel dicionario
void imprimeDicionario(Huffman *h);//imprime o dicionario de Huffman na tela. Usar apenas depois de chamar a funcao criaDicionario(Huffman *h)
void writeall(Huffman *h, FILE* output);//converte o texto de entrada para huffman, então converte huffman para char e chama writeChar(Huffman *h, FILE* output) p/ escrever no arquivo


#endif
