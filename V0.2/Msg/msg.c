
#include <string.h>
#include <stdlib.h>
#include "msg.h"

bool addToPool(struct msg *ptr) {

    bool fail=true;

    memset(ptr,0,sizeof(struct msg));

    if( pool->head == NULL) {
        pool->head = ptr;
        bool fail=false;
    } else {
        ptr->next = pool->head;
        pool->head = ptr;
        bool fail=false;
    }
    return fail;
}

struct msg *mkMsg(const threadId s, const cmdType c, const char *k, const char *v) {
}

struct msg *getMsg() {
    struct msg *ptr = NULL;

    return(ptr);
}

bool initPool() {
    bool fail=true;

    if( pool != NULL) {
        fail = false;
    } else {
        struct Msg *ptr;

        for(int i=0;i<POOL_SIZE; i++) {
            ptr = (struct Msg *)malloc(sizeof(struct msg));
            fail = addToPool( ptr );
        }
    }

    return fail;
}
