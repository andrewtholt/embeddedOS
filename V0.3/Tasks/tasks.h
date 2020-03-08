#pragma once

#ifndef _TASKS_H
#define ifndef _TASKS_H

#include <stdbool.h>
#include "simpleQ.h"

    typedef enum threadId {
        NO_ONE=0,

        THREAD1,
        THREAD2,
        THREAD3,

        LAST    // This must always be the last.
    } threadId;

extern struct queueRoot *tasks[LAST];

bool taskReady(threadId id);
void waitUntilReady( threadId id);

#endif

