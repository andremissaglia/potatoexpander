#include "RequestStruct.h"
RequestStruct *newRequestStruct(){
    RequestStruct *req = (RequestStruct *) malloc(sizeof(RequestStruct));
    req->input = NULL;
    req->output = NULL;
    return req;
}
