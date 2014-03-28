#include "Huffman.h"

//cria uma instancia do objeto de controle para huffman
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
        //printf("\n");
     for(i=0; i< h->textSize; i++){
        index = h->textoEntrada[i];
        h->freq[index] = h->freq[index]+1;   

        //printf("%d%c",i,index);     
     }   
     
     
     
}


//utiliza o Bubblesort para organizar os vetores dos simbolos e de suas frequencias
void ordenaVetor(int size, noArvore** vetLeaf){
int i,j;
noArvore* temp;

         for(i=size-2;i>=0;i--)  
         {  
            for(j=0;j<=i;j++)  
  
                  {  
                    if(vetLeaf[j]->freq < vetLeaf[j+1]->freq)  
                                    {
                                               
                                     temp =  vetLeaf[j];
                                     vetLeaf[j] = vetLeaf[j+1];
                                     vetLeaf[j+1] = temp;
                                    
                                    }  
                   }  
         
  
           }
}




//imprime vetor de char
void imprimeVet(noArvore** vetLeaf, int size){
int i;
   for(i=0;i<size;i++){
         if(vetLeaf[i]!=NULL){              
            printf("\nchar:%c: freq:%d",vetLeaf[i]->valor,vetLeaf[i]->freq);
         }
      
   }
   printf("\n\n");
    
}



//cria a arvore de huffman
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
               //printf("\n[%d]: %d",i,h->freq[i] );
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
   
   //imprimeVet(vetFolhas,size);
   
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
   h->nVerbetes = size;

}



//faz a busca em profundidade para montar o dicionario
void DFS(Dicionario* dicionario, noArvore* tree, char* codigo){
int i;
char* bufferDir, *bufferEsq;

          if((tree->esq == NULL)&&(tree->esq == NULL)){//checa se eh noh folha

             for(i=0; i<dicionario->nVerbetes;i++){
                      
               if(strcmp(dicionario->palavra[i]->huffCode, "") == 0){//procura uma posicao livre no vetor de verbetes    
                    dicionario->palavra[i]->valor = tree->valor;        //guarda a palavra
                    dicionario->palavra[i]->frequencia = tree->freq;    //guarda a frequencia da palavra
                    strcpy(dicionario->palavra[i]->huffCode, codigo);   //guarda o codigo Huffman da palavra
                    return;
               }
               
             }
             
          }
          else{//se nao eh folha chama recursivamente a funcao
               
               //buffer q recebe 0 para uma chamada recursiva a direita e 1 para uma chamada a esquerda
               bufferDir = (char*)malloc(sizeof(char)*9);
               bufferEsq = (char*)malloc(sizeof(char)*9);
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
          printf("\npalavra:%c ---> Huffman:%s --->frequencia:%d",h->dicionario->palavra[i]->valor,h->dicionario->palavra[i]->huffCode,h->dicionario->palavra[i]->frequencia);
       }
       printf("\n\n===============================================");
       printf("\n\n");

}




//utiliza o Bubblesort para organizar o dicionario pela frequencia dos verbetes
void ordenaDicionario(int nVerbetes, Dicionario* dicionario){
int i,j;
Verbete* temp;

         for(i=nVerbetes-2;i>=0;i--)  
         {  
            for(j=0;j<=i;j++)  
  
                  {  
                    if(dicionario->palavra[j]->frequencia < dicionario->palavra[j+1]->frequencia)
                                    {
                                               
                                     temp =  dicionario->palavra[j];
                                     dicionario->palavra[j] = dicionario->palavra[j+1];
                                     dicionario->palavra[j+1] = temp;
                                    
                                    }  
                   }  
         
  
           }
}






//cria o dicionario de Huffman
void criaDicionario(Huffman *h){
Dicionario* dicionario;
char* codigo;
int size,i;
       
         
       size = h->nVerbetes; 
       dicionario = (Dicionario*)malloc(sizeof(Dicionario));
       dicionario->palavra = (Verbete**)malloc(sizeof(Verbete*)*size);//cria o vetor de verbetes
       dicionario->nVerbetes = size;
       
       
       //inicializa os verbetes do dicionario
       for(i=0;i<size;i++){
             dicionario->palavra[i] = (Verbete*)malloc(sizeof(Verbete));//cria cada verbete      
             dicionario->palavra[i]->valor = 0;
             dicionario->palavra[i]->huffCode = (char*)malloc(sizeof(char)*9);
             strcpy(dicionario->palavra[i]->huffCode, "");
       }
       
       codigo = (char*)malloc(sizeof(char)*9);
       strcpy(codigo, "");
       
       
       DFS(dicionario, h->arvore, codigo);//chama a busca em profundidade para montar o dicionario
       
       ordenaDicionario(dicionario->nVerbetes, dicionario);//ordena o dicionario pela frequencia das palavras
       
       h->dicionario = dicionario;//guarda o dicionario na instancia de huffman
}





//escreve o caracter q esta no buffer da struct h no arquivo de saida
writeChar(Huffman *h, FILE* output){
char c;
     
     c = h->buffer;

}



void writeall(Huffman *h, FILE* output){
int i,j, wordSize,freq, total, nChar, resto, length,size,achou, bufferInt;
char* textoTemp, * buffer;
char c;
    //calcula o total de bits da imagem compactada (soh a matriz rgb) 
    total = 0; 
    size = h->dicionario->nVerbetes;
    for(i=0; i<size;i++){
         wordSize = strlen(h->dicionario->palavra[i]->huffCode);
         freq = h->dicionario->palavra[i]->frequencia;
         total = total+ (wordSize*freq);             
    }
  
    nChar = total/8;//total de caracteres q o arquivo tera q tem seus 8 bits totalmente ocupados
    resto = total%8;//quantos bits serao ocupados no ultimo char do arquivo comprimido
    printf("\n\ntotal: %d  ---> nChar:%d ---> resto:%d\n\n",total,nChar,resto);
    
    length = h->textSize;//tamanho do texto de entrada
    //printf("\n\nlength: %d\n\n",length);
    
    
    //traduz o texto de entrada em codigo de Huffman e guarda na variavel textoTemp
    textoTemp = (char*)malloc(sizeof(char)*total);//cria textoTempo utilizando o total calculado anteriormente para setar o tamanho
    strcpy(textoTemp,"");//inicializa a variavel textoTemp
    for(i=0;i<length;i++){
        c = h->textoEntrada[i];
        
        achou = 0;
        for(j=0;( (j<size) && (achou ==0));j++){
             if(h->dicionario->palavra[j]->valor == c){
             
                 strcat(textoTemp,h->dicionario->palavra[j]->huffCode);//concatena os codigos de Huffman num texto unico em textoTemp
                 achou =1;
             
             }     
   
        }                
    
    }
    
    
    //printf(textoTemp);
    
    buffer = (char*)malloc(sizeof(char)*9);//instancia a variavel buffer

    
    //reseta o buffer para utiliza-lo no ultimo caracter q nao teve todos seus bits usados            
    for(i=0;i<9;i++){
                                        
       buffer[i] = '\0';   
    
    }
    
    
    h->buffer = '\0';//inicializa o buffer da struct
    for(i=0;i<nChar;i++){//há nChar caracteres q terao seus 8 bits totalmente utilizados
    
       for(j=8*i; j<(8*(i+1)); j++){//le char por char na string buffer do texto em Huffman
             
         buffer[j%8] = textoTemp[j];         
       
       }                  
       buffer[9] = '\0';//finaliza o buffer
       
       h->buffer = strtol(buffer, 0, 2);//converte string para char entendendo a string como binario e guarda no buffer da struct
       writeChar(h, output);//escreve o caracter q esta no buffer da struct h no arquivo de saida
    
    }   
    
    
    //se há resto de texto
    if(resto!=0){
                 
         //reseta o buffer para utiliza-lo no ultimo caracter q nao teve todos seus bits usados            
         for(i=0;i<9;i++){
                                        
              buffer[i] = '\0';   
    
          }

          //poe no buffer o que restou do texto
          for(j=0; j<resto; j++){
             
             buffer[j] = textoTemp[total-2+j];         
       
          } 
          buffer[9] = '\0';//finaliza o buffer
          
          h->buffer = strtol(buffer, 0, 2);//converte string para char entendendo a string como binario e guarda no buffer da struct
          
          writeChar(h, output);//escreve o caracter q esta no buffer da struct h no arquivo de saida
          //printf("\n\nbuffer: %s", buffer);
          //printf("\nchar: %c", h->buffer);
    
    }

}
