#include "Carreira.h"

#include <stdlib.h>

Carreira *newCarreira(Huffman *h){
    Carreira *rl = (Carreira *) malloc(sizeof(Carreira));
    rl->huffman = h;
    rl->count = 0;
    rl->current = SKIPCHAR;
    return rl;
}
void RLWriteChar(Carreira *rl, unsigned char c){
    if(c == SKIPCHAR) c = REPLACECHAR;

    if(c != rl->current || rl->count == 255){
        flush(rl);
        rl->current = c;
    }
    rl->count++;

}
unsigned char RLReadChar(Carreira *rl){
    if(rl->count == 0){
        rl->current = readChar(rl->huffman);
        if(rl->current == SKIPCHAR){
            rl->current = readChar(rl->huffman);
            rl->count = readChar(rl->huffman);
        } else {
            rl->count = 1;
        }
    }
    rl->count--;
    return rl->current;
}
void flush(Carreira *rl){
    if(rl->count > 3){
        writeChar(rl->huffman,SKIPCHAR);
        writeChar(rl->huffman,rl->current);
        writeChar(rl->huffman,rl->count);
    } else {
        for(;rl->count > 0;rl->count--){
            writeChar(rl->huffman, rl->current);
        }
    }
    rl->count = 0;
}
