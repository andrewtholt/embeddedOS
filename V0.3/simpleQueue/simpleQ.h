#pragma once
#ifndef __SIMPLE_Q
#define __SIMPLE_Q

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define NO_INT (-1)
typedef void * queue_data_type;

struct queueName{
    void *contents;
    struct queueName *next;
};

struct queueRoot {
    struct queueName *head;
    struct queueName *tail;
    int size;

    // Place the id of the IRQ to be disabled, enabled here
    // Otherwise set to <0.
    //
    int intId;
};

struct queueRoot *mkQueue();
void initQueue(struct queueRoot *queue, uint8_t irq);
void pushQueue(struct queueRoot* queue, void *contents);
void processQueue(struct queueRoot* queue, void (*func)(queue_data_type));
void *popQueue(struct queueRoot *queue);
int sizeOfQueue(struct queueRoot* queue);
bool queueEmpty( struct queueRoot *queue);

// Return the front of the Q without removing it.
queue_data_type peekQueue(struct queueRoot* queue);

#ifdef __cplusplus
}
#endif

#endif
