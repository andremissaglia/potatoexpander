#include "RequestStruct.h"
RequestStruct *newRequestStruct(){
    RequestStruct *req = (RequestStruct *) malloc(sizeof(RequestStruct));
    req->input = NULL;
    req->output = NULL;
    return req;
}

void freeRequestStruct(RequestStruct *rs){
    fclose(rs->input);
    fclose(rs->open);
    free(rs);
}
