#ifndef __MSG_H
#define __MSG_H

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "tasks.h"

#define MAX_KEY    8
#define MAX_VALUE 16
#define POOL_SIZE 10

struct freePoolDef {
    struct msg *head;

    uint8_t count;
};

struct freePoolDef *pool;

typedef enum cmdType {
    NOP = 0,
    SET,
    GET,
    SUB,
    UNSUB
} cmdType ;

struct msg {
    threadId sender;
    cmdType cmd;

    char key[MAX_KEY];
    char value[MAX_VALUE];

    struct msg *next;
    
};

struct msg *mkMsg(const threadId s, const cmdType c, const char *k, const char *v);
struct msg *getMsg();

bool addToPool(struct msg *ptr);
bool initPool();

#endif
