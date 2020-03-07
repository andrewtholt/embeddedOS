
#include <string.h>
#include <stdlib.h>
#include "msg.h"

bool addToPool(struct msg *ptr) {

    bool fail=true;

    memset(ptr,0,sizeof(struct msg));

    if( pool.head == NULL) {
        pool.head = ptr;
        bool fail=false;
    } else {
        ptr->next = pool.head;
        pool.head = ptr;
        bool fail=false;
    }
    return fail;
}

struct msg *mkMsg(const threadId s, const cmdType c, const char *k, const char *v) {

    struct msg *ptr = NULL;

    ptr = getMsg() ;

    if( ptr != NULL) {
        ptr->sender = s;
        ptr->cmd = c;

        strncpy(ptr->key,  k, MAX_KEY);
        strncpy(ptr->value,v, MAX_VALUE);
    }
    return ptr;
}

struct msg *getMsg() {
    struct msg *ptr = NULL;

    ptr = pool.head;

    pool.head = ptr->next;

    ptr->next = NULL;

    return(ptr);
}

bool initPool() {
    bool fail=true;

    struct msg *ptr;

    for(int i=0;i<POOL_SIZE; i++) {
        ptr = (struct msg *)malloc(sizeof(struct msg));
        fail = addToPool( ptr );
    }

    return fail;
}
