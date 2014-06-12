#include "Huffman.h"
#include <stdlib.h>

#define MAXHUFFLENGTH 256
//cria uma instancia do objeto de controle para huffman
Huffman* newHuffman(){
        int i;

        Huffman *h = (Huffman *)malloc(sizeof(Huffman));
        h->textSize = 0;
        h->tamanhoAlocado = 0;
        h->textoEntrada = NULL;

        for(i=0;i<256;i++){
            h->freq[i] = 0;
        }
        h->bufferPos = 7;
        h->textoEntradaPos = 0;

        h->arvore = NULL;
        h->dicionario = NULL;
        return h;
}
void freeHuffmanTree(noArvore *no){
    if(no == NULL) return;
    freeHuffmanTree(no->dir);
    freeHuffmanTree(no->esq);
    free(no);
}
void freeHuffman(Huffman* h){
    int i;
    if(h->textoEntrada != NULL) free(h->textoEntrada);
    if(h->dicionario != NULL) {
        for(i = 0; i < h->nVerbetes;i++){
            free(h->dicionario->palavra[i]->huffCode);
            free(h->dicionario->palavra[i]);
        }
        free(h->dicionario->palavra);
        free(h->dicionario);
    }
    freeHuffmanTree(h->arvore);
    free(h);
}
/**
* Conta frequencia dos caracteres.
*/
void contaFreq(Huffman *h){
    int i, index=0;
    for(i=0; i< h->textSize; i++){
        index = h->textoEntrada[i];
        h->freq[index]++;
    }
}

/**
* Utiliza o Bubblesort para organizar os vetores dos simbolos e de suas frequencias
*/
void ordenaVetor(int size, noArvore** vetLeaf){
    int i,j;
    noArvore* temp;

    for(i=size-2;i>=0;i--){
        for(j=0;j<=i;j++){
            if(vetLeaf[j]->freq < vetLeaf[j+1]->freq){
                temp =  vetLeaf[j];
                vetLeaf[j] = vetLeaf[j+1];
                vetLeaf[j+1] = temp;
            }
        }
    }
}

/**
* imprime vetor de char
*/
void imprimeVet(noArvore** vetLeaf, int size){
    int i;
    for(i=0;i<size;i++){
        if(vetLeaf[i]!=NULL){
            printf("\nchar:%c: freq:%d",vetLeaf[i]->valor,vetLeaf[i]->freq);
        }
   }
   printf("\n\n");
}

/**
* Cria a arvore de huffman
*/
void criaArvore(Huffman *h, int flagDescompressao){
    noArvore* novo;
    noArvore **vetFolhas;
    int f,i, size, contador, tam;

    if(flagDescompressao != 1){
        contaFreq(h);//conta a frequencia de cada caracter do texto e guarda em h->freq
    }

    //conta o numero de valores q nao sao zero do vetor de frequencia
    size = 0;
    for(i=0; i<256;i++){
        if(h->freq[i] > 0){
            size = size+1;
        }
    }
    vetFolhas = (noArvore**)malloc(sizeof(noArvore*)*size);//vetor que guardara os nos folhas da arvore de huffman.


    f = 0;
    contador = 0;
    for(i=0; i<256;i++){
        if(h->freq[i] > 0){
            f = h->freq[i];

            novo = (noArvore*)malloc(sizeof(noArvore));
            novo->dir = NULL;
            novo->esq = NULL;
            novo->valor = i;
            novo->freq = f;
            vetFolhas[contador] = novo;
            //printf("\nfreq%d: %d",contador,vetFolhas[contador]->freq);
            contador = contador+1;
            novo = NULL;
        }
    }

    ordenaVetor(size, vetFolhas);//ordena i vetor pelas frequencias

    //cria um novo noh da arvore que tera os 2 nohs com a menor frequencia da arvore de huffman
    tam = size;
    while(tam>1){
        novo = (noArvore*)malloc(sizeof(noArvore));
        novo->dir = vetFolhas[tam-1];
        novo->esq = vetFolhas[tam-2];
        novo->freq = vetFolhas[tam-1]->freq + vetFolhas[tam-2]->freq;
        novo->valor = 0;
        vetFolhas[tam-1] = NULL;//diminui o tamanho do vetor
        vetFolhas[tam-2] = novo;//substitui os 2 nohs q foram ajuntados  por um unico novo noh q contem os 2
        tam = tam -1;
        ordenaVetor(tam, vetFolhas);//reordena o vetor com a frequencia do novo noh
    }

    //imprimeVet(vetFolhas,tam);

    h->arvore = vetFolhas[0];
    free(vetFolhas);
    h->nVerbetes = size;

}



//faz a busca em profundidade para montar o dicionario
void DFS(Dicionario* dicionario, noArvore* tree, char* codigo){
    int i;
    char bufferDir[MAXHUFFLENGTH], bufferEsq[MAXHUFFLENGTH];

    if((tree->esq == NULL)&&(tree->esq == NULL)){//checa se eh noh folha
        for(i=0; i<dicionario->nVerbetes;i++){
            if(strcmp(dicionario->palavra[i]->huffCode, "") == 0){//procura uma posicao livre no vetor de verbetes
                dicionario->palavra[i]->valor = tree->valor;        //guarda a palavra
                dicionario->palavra[i]->frequencia = tree->freq;    //guarda a frequencia da palavra
                strcpy(dicionario->palavra[i]->huffCode, codigo);   //guarda o codigo Huffman da palavra
                return;
            }
        }
    }else{//se nao eh folha chama recursivamente a funcao
        //buffer q recebe 0 para uma chamada recursiva a direita e 1 para uma chamada a esquerda
        strcpy(bufferDir, codigo);
        strcpy(bufferEsq, codigo);

        if(tree->esq != NULL){
            strcat (bufferEsq,"1");//concatena 1 para o buffer a esquerda
            DFS(dicionario,tree->esq,bufferEsq);//chamada recursiva para a esquerda
        }
        if(tree->dir != NULL){
            strcat (bufferDir,"0");//concatena 0 para o buffer a direita
            DFS(dicionario,tree->dir,bufferDir);//chamada recursiva para a direita
        }
    }
}

void imprimeDicionario(Huffman *h){
    int i;
    printf("\n\n=====================Dicionario================");
    for(i=0;i<h->dicionario->nVerbetes;i++){
        printf("\npalavra:%c(%x) ---> Huffman:%s --->frequencia:%d",
               h->dicionario->palavra[i]->valor,
               h->dicionario->palavra[i]->valor,
               h->dicionario->palavra[i]->huffCode,
               h->dicionario->palavra[i]->frequencia);
    }
    printf("\n\n===============================================");
    printf("\n\nNverbetes: %d",h->dicionario->nVerbetes);
    printf("\n\n===============================================");
    printf("\n\n");

}

/**
* Utiliza o Bubblesort para organizar o dicionario pela frequencia dos verbetes
*/
void ordenaDicionario(int nVerbetes, Dicionario* dicionario){
    int i,j;
    Verbete* temp;
    for(i=nVerbetes-2;i>=0;i--){
        for(j=0;j<=i;j++){
            if(dicionario->palavra[j]->frequencia < dicionario->palavra[j+1]->frequencia){
                temp =  dicionario->palavra[j];
                dicionario->palavra[j] = dicionario->palavra[j+1];
                dicionario->palavra[j+1] = temp;
            }
        }
    }
}

/**
* Cria o dicionario de Huffman
*/
void criaDicionario(Huffman *h){
    Dicionario* dicionario;
    char codigo[MAXHUFFLENGTH];
    int size,i;


    size = h->nVerbetes;
    dicionario = (Dicionario*)malloc(sizeof(Dicionario));
    dicionario->palavra = (Verbete**)malloc(sizeof(Verbete*)*size);//cria o vetor de verbetes
    dicionario->nVerbetes = size;


    //inicializa os verbetes do dicionario
    for(i=0;i<size;i++){
        dicionario->palavra[i] = (Verbete*)malloc(sizeof(Verbete));//cria cada verbete
        dicionario->palavra[i]->valor = 0;
        dicionario->palavra[i]->huffCode = (char*)malloc(sizeof(char)*MAXHUFFLENGTH);
        strcpy(dicionario->palavra[i]->huffCode, "");
    }

    codigo[0] = '\0';


    DFS(dicionario, h->arvore, codigo);//chama a busca em profundidade para montar o dicionario

    ordenaDicionario(dicionario->nVerbetes, dicionario);//ordena o dicionario pela frequencia das palavras

    h->dicionario = dicionario;//guarda o dicionario na instancia de huffman
}





/**
* Escreve o caracter q esta no buffer da struct h no arquivo de saida
*/
void writeChar(Huffman *h, unsigned char c){
    if(h->textSize == h->tamanhoAlocado){
        h->tamanhoAlocado++;
        h->tamanhoAlocado *= 2; // troque para nao perder muito tempo com o realloc
        h->textoEntrada = (unsigned char *) realloc(h->textoEntrada,h->tamanhoAlocado*sizeof(unsigned char));
    }
    h->textoEntrada[h->textSize++]=c;
}
void writeInt(Huffman *h, unsigned int i){
    unsigned char *ptr = (unsigned char *)(&i);
    writeChar(h,ptr[0]);
    writeChar(h,ptr[1]);
    writeChar(h,ptr[2]);
    writeChar(h,ptr[3]);
}
/**
* Escreve um bit no buffer.
*/
void writeBit(Huffman *h, FILE *out, unsigned char bit){
    h->buffer = h->buffer | (bit << h->bufferPos);
    h->bufferPos--;
    if(h->bufferPos == -1){
        fwrite(&(h->buffer),sizeof(unsigned char),1,out);
        h->bufferPos = 7;
        h->buffer = 0;
    }
}

void writeHeader(Huffman *h, FILE* output){
    fwrite(h->freq,sizeof(unsigned int),256, output);
}

void writeall(Huffman *h, FILE* output){
    int i,j;
    int size = h->dicionario->nVerbetes;
    unsigned char c;
    writeHeader(h, output);
    //percorre o texto codificando-o
    char *aux;
    for(i=0;i<h->textSize;i++){
        c = h->textoEntrada[i];
        for(j=0;j<size;j++){
            if(h->dicionario->palavra[j]->valor == c){
                aux = h->dicionario->palavra[j]->huffCode;
                //achou a palavra, escreve os bits dela
                while(*aux != '\0'){
                    writeBit(h,output,(*aux - '0'));
                    aux++;
                }
                break;
            }
        }
    }
    if(h->bufferPos != 7){
        fwrite(&(h->buffer),sizeof(char),1,output);
    }
}

void readHeader(Huffman *h, FILE* output){
    fread(h->freq,sizeof(int),256, output);
}
void readAll(Huffman *h, FILE* input){
    int curpos = ftell(input);
    fseek(input,0,SEEK_END);
    int endpos = ftell(input);
    h->textSize = endpos - curpos;
    fseek(input,curpos,SEEK_SET);

    h->textoEntrada = (unsigned char *) malloc(h->textSize*sizeof(unsigned char));
    fread(h->textoEntrada,sizeof(unsigned char), h->textSize, input);

}
unsigned char readBit(Huffman *h){
    if(h->bufferPos == -1){
        h->buffer = h->textoEntrada[h->textoEntradaPos];
        h->textoEntradaPos++;
        h->bufferPos = 7;
    }
    unsigned char bit = (h->buffer & (1 << h->bufferPos));
    bit = bit >> h->bufferPos;
    h->bufferPos--;
    return bit;
}
unsigned char extractChar(Huffman *h,noArvore *no){
    if(no->esq == NULL&& no->dir == NULL ){
        return no->valor;
    }
    char bit = readBit(h);
    if(bit == 1){
        return extractChar(h,no->esq);
    } else {
        return extractChar(h, no->dir);
    }
}
unsigned char readChar(Huffman *h){
    return extractChar(h,h->arvore);
}
unsigned int readInt(Huffman *h){
    unsigned int i = 0;
    char *ptr = (char*) (&i);
    ptr[0] = readChar(h);
    ptr[1] = readChar(h);
    ptr[2] = readChar(h);
    ptr[3] = readChar(h);
    return i;
}
Huffman* readHuffmanFile(FILE *input){
    Huffman*h = newHuffman();
    h->bufferPos = -1;
    fseek(input,0, SEEK_SET);
    readHeader(h,input);
    readAll(h, input);
    criaArvore(h, 1);
    criaDicionario(h);
    return h;
}
