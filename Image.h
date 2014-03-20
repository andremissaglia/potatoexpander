#ifndef __IMAGE
#define __IMAGE
/**
*
*/
typedef struct {
    //Bitmap File Header
    unsigned short type;
    unsigned int size;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int starting_pos;
    //DIP Header
    unsigned int DIPSize;
} BMPHeader;
#endif

