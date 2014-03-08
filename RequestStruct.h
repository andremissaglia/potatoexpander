#ifndef __RRQUESTSTRUCT
#define __REQUESTSTRUCT
#include <stdlib.h>
#include <stdio.h>
typedef struct {
    FILE *input;
    FILE *output;
} RequestStruct;

RequestStruct *newRequestStruct();
#endif

