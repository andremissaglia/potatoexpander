#include "Image.h"
BMPHeader *newBMPHeader(){
    BMPHeader *bmp = (BMPHeader *) calloc(1,sizeof(BMPHeader));
    bmp->type = 0x4d42; // BM
    bmp->starting_pos = 0x36; //usando BITMAPINFOHEADER
    bmp->DIPSize = 40;
    bmp->color_planes = 1;
    bmp->bpp = 24;

    return bmp;
}
BMPHeader *readBMPHeader(FILE *fp){
    //lendo manualmente por causa do alinhamento da struct
    fseek(fp,0,SEEK_SET);
    BMPHeader *bmp = newBMPHeader();
    fread(&(bmp->type), sizeof(unsigned short), 1,fp);
    fread(&(bmp->size), sizeof(unsigned int), 1,fp);
    fread(&(bmp->reserved1), sizeof(unsigned short), 1,fp);
    fread(&(bmp->reserved2), sizeof(unsigned short), 1,fp);
    fread(&(bmp->starting_pos), sizeof(unsigned int), 1,fp);

    fread(&(bmp->DIPSize), sizeof(unsigned int), 1,fp);
    fread(&(bmp->width), sizeof(int), 1,fp);
    fread(&(bmp->height), sizeof(int), 1,fp);
    if(bmp->DIPSize == 12) return bmp; //Compatibilidade com BITMAPCOREHEADER

    //Continuando a ler com BITMAPINFOHEADER
    fread(&(bmp->color_planes), sizeof(unsigned short), 1,fp);
    fread(&(bmp->bpp), sizeof(unsigned short), 1,fp); // TODO: tratar caso com bpp != 24
    fread(&(bmp->compression_method), sizeof(unsigned int), 1,fp);
    fread(&(bmp->bitmap_size), sizeof(unsigned int), 1,fp);
    fread(&(bmp->resolution_x), sizeof(int), 1,fp);
    fread(&(bmp->resolution_y), sizeof(int), 1,fp);
    fread(&(bmp->ncolors), sizeof(unsigned int), 1,fp);
    fread(&(bmp->important_colors), sizeof(unsigned int), 1,fp);
    return bmp;
}
void writeBMPHeader(FILE *fp, BMPHeader *bmp){
    fseek(fp,0,SEEK_SET);

    fwrite(&(bmp->type), sizeof(unsigned short), 1,fp);
    fwrite(&(bmp->size), sizeof(unsigned int), 1,fp);
    fwrite(&(bmp->reserved1), sizeof(unsigned short), 1,fp);
    fwrite(&(bmp->reserved2), sizeof(unsigned short), 1,fp);
    fwrite(&(bmp->starting_pos), sizeof(unsigned int), 1,fp);

    fwrite(&(bmp->DIPSize), sizeof(unsigned int), 1,fp);
    fwrite(&(bmp->width), sizeof(int), 1,fp);
    fwrite(&(bmp->height), sizeof(int), 1,fp);
    if(bmp->DIPSize == 12) return; //Compatibilidade com BITMAPCOREHEADER

    //Continuando a ler com BITMAPINFOHEADER
    fwrite(&(bmp->color_planes), sizeof(unsigned short), 1,fp);
    fwrite(&(bmp->bpp), sizeof(unsigned short), 1,fp); // TODO: tratar caso com bpp != 24
    fwrite(&(bmp->compression_method), sizeof(unsigned int), 1,fp);
    fwrite(&(bmp->bitmap_size), sizeof(unsigned int), 1,fp);
    fwrite(&(bmp->resolution_x), sizeof(int), 1,fp);
    fwrite(&(bmp->resolution_y), sizeof(int), 1,fp);
    fwrite(&(bmp->ncolors), sizeof(unsigned int), 1,fp);
    fwrite(&(bmp->important_colors), sizeof(unsigned int), 1,fp);

    //preenche com 0 ateh o inicio da matriz

    unsigned char c = 0;
    while(bmp->starting_pos > ftell(fp)){
        fwrite(&c, sizeof(unsigned char),1, fp);
    }
}

BMPImage *readBMP(FILE *fp){
    BMPImage *bmp = (BMPImage *) malloc(sizeof(BMPImage));
    bmp->header = readBMPHeader(fp);
    fseek(fp,bmp->header->starting_pos, SEEK_SET);
    //alocando matrizes
    bmp->B = (unsigned char **) malloc(bmp->header->width*sizeof(unsigned char *));
    bmp->G = (unsigned char **) malloc(bmp->header->width*sizeof(unsigned char *));
    bmp->R = (unsigned char **) malloc(bmp->header->width*sizeof(unsigned char *));

    int i,j;
    for(i = 0; i < bmp->header->width;i++){
        bmp->B[i] = (unsigned char *) malloc(bmp->header->height*sizeof(unsigned char));
        bmp->G[i] = (unsigned char *) malloc(bmp->header->height*sizeof(unsigned char));
        bmp->R[i] = (unsigned char *) malloc(bmp->header->height*sizeof(unsigned char));
    }
    //Lendo matrizes.
    //Nota: as matrizes B,G e R sao indexadas em [x][y],
    //com [0][0] correspondendo ao canto inferior esquerdo

    int rowsize = ((bmp->header->bpp*bmp->header->width + 31)/32)*4;
    int padding = rowsize - sizeof(unsigned char)*3*bmp->header->width;
    for(j = 0; j < bmp->header->height ;j++){
        for(i = 0; i < bmp->header->width;i++){
            fread(&(bmp->B[i][j]), sizeof(unsigned char), 1,fp);
            fread(&(bmp->G[i][j]), sizeof(unsigned char), 1,fp);
            fread(&(bmp->R[i][j]), sizeof(unsigned char), 1,fp);
        }
        fseek(fp, padding, SEEK_CUR);
    }
    return bmp;
}
void writeBMP(FILE *fp, BMPImage *bmp){
    writeBMPHeader(fp,bmp->header);
    fseek(fp,bmp->header->starting_pos, SEEK_SET);
    int rowsize = ((bmp->header->bpp*bmp->header->width + 31)/32)*4;
    int padding = rowsize - sizeof(unsigned char)*3*bmp->header->width;
    int skip = 0;
    int i,j;
    for(j = 0; j < bmp->header->height ;j++){
        for(i = 0; i < bmp->header->width;i++){
            fwrite(&(bmp->B[i][j]), sizeof(unsigned char), 1,fp);
            fwrite(&(bmp->G[i][j]), sizeof(unsigned char), 1,fp);
            fwrite(&(bmp->R[i][j]), sizeof(unsigned char), 1,fp);
        }
        fwrite(&skip,sizeof(unsigned char), padding, fp);
    }
}
void make_BMPHeader(BMPImage *bmp){
    int rowsize = ((bmp->header->bpp*bmp->header->width + 31)/32)*4;
    bmp->header->bitmap_size = rowsize*bmp->header->height;
    bmp->header->size = bmp->header->DIPSize+14+bmp->header->bitmap_size;
}
void freeBMP(BMPImage *bmp){
    free(bmp->header);

    int i;
    for(i = 0; i < bmp->header->width;i++){
        free(bmp->B[i]);
        free(bmp->G[i]);
        free(bmp->R[i]);
    }
    free(bmp->B);
    free(bmp->G);
    free(bmp->R);
    free(bmp);
}
