#ifndef __SIMPLE_Q
#define __SIMPLE_Q

#ifdef __coplusplus
extern "C" {
#endif

#include <stdint.h>

#define NO_INT (-1)
typedef void * queue_data_type;

struct queueName{
    queue_data_type contents;
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

void initQueue(struct queueRoot *queue, uint8_t irq);
void pushQueue(struct queueRoot* queue, int size, queue_data_type contents);
void processQueue(struct queueRoot* queue, void (*func)(queue_data_type));
queue_data_type popQueue(struct queueRoot* queue);
int sizeOfQueue(struct queueRoot* queue);
bool queueEmpty( struct queueRoot *queue);

// Return the front of the Q without removing it.
queue_data_type peekQueue(struct queueRoot* queue);

#ifdef __coplusplus
}

#endif
#endif
