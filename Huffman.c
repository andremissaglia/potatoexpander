#include "Huffman.h"

Huffman* newHuffman(int tamanhoTexto, char* texto){
int i;
         
         Huffman *h = (Huffman *)malloc(sizeof(Huffman));
         
         h->textSize = tamanhoTexto; //3*Area da imagem
         
         h->textoEntrada = texto;
         
         for(i=0;i<256;i++){
            h->freq[i] = 0;
         }
         
         return h;
}

//conta frequencia dos caracteres
void contaFreq(Huffman *h){
int i, index=0;
     for(i=0; i< h->textSize; i++){
        index = h->textoEntrada[i];
        h->freq[index] = h->freq[index]+1;        
     }   

}


void criaArvore(Huffman *h){
noArvore* a;

   

}
