#pragma once
#ifndef __MSG_H
#define __MSG_H

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "tasks.h"

#define MAX_KEY    8
#define MAX_VALUE 16
#define POOL_SIZE 10

#ifdef __cplusplus
extern "C" {
#endif
    struct freePoolDef {
        struct msg *head;

        uint8_t count;
    };

    extern struct freePoolDef pool;

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
    void displayMsg(struct msg*ptr);

    bool addToPool(struct msg *ptr);
    bool initPool();
#ifdef __cplusplus
}
#endif
#endif
