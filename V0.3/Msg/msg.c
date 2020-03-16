
#include <string.h>
#include <stdlib.h>
#include "msg.h"

struct freePoolDef pool;

bool addToPool(struct msg *ptr) {

    bool fail=true;

    memset(ptr,0,sizeof(struct msg));

    if( pool.head == NULL) {
        pool.head = ptr;
        pool.count=1;

        bool fail=false;
    } else {
        ptr->next = pool.head;
        pool.head = ptr;

        pool.count++;
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

    if (ptr != NULL) {

        pool.head = ptr->next;

        ptr->next = NULL;

        pool.count--;
        if( pool.count < 0) {
            pool.count=0;
        }
    }
    return(ptr);
}

void displayMsg(struct msg *ptr) {
    if( ptr != NULL) {
        printf("Sender  : %02d\n", (uint8_t) ptr->sender);
        printf("Command : %02d\n", (uint8_t) ptr->cmd);
        printf("Key     : %s\n", ptr->key);
        printf("Value   : %s\n", ptr->value);
    }
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
