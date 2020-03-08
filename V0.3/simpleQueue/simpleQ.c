/*
   Implementation by Groxx, with absolutely no guarantees, so don't complain to me if it breaks stuff.
   Feel free to use it for awesome, as needed.  Apply liberally, and induce vomiting if you ingest large doses.
   Note from #0d15eb: BREAKING CHANGE FROM #1d1057: this is now a generic storage, storing pointers to data.  Manage your memory accordingly.
Note: now stores the "next" pointer prior to processing, allowing you to process and pop the first item in the list in one pass without losing your place in the queue (and possibly other shenanigans, this one was just handy for my uses so I changed it).
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "simpleQ.h"

struct queueRoot *mkQueue() {

    struct queueRoot *ptr;

    ptr = (struct queueRoot *)malloc(sizeof(struct queueRoot));

    if( ptr != NULL) {
        memset(ptr, 0 , sizeof(struct queueRoot));

        initQueue(ptr,0);
    }

    return ptr;
}

void initQueue(struct queueRoot* queue, uint8_t irq) {
    queue->head = queue->tail = NULL;
    queue->intId = irq;
    queue->size = 0;
}

void pushQueue(struct queueRoot* queue, int size, queue_data_type contents){
    struct queueName *item = (struct queueName *)malloc(size);
    item->contents = contents;

    if( queue->intId != NO_INT ) {
        // Disable int, or acquire mutex.
    }
    item->next = NULL;
    if (queue->head == NULL){
        queue->head = queue->tail = item;
    } else {
        queue->tail = queue->tail->next = item;
    }

    queue->size++;

    if( queue->intId != NO_INT ) {
        // Enable int, or release mutex.
    }
}

queue_data_type popQueue(struct queueRoot* queue){
    queue_data_type popped;
    if (queue->head == NULL){
        return NULL; // causes a compile warning.  Just check for ==NULL when popping.
    } else {

        if( queue->intId != NO_INT ) {
            // Disable int, or acquite mutex.
        }
        popped = queue->head->contents;
        struct queueName* next = queue->head->next;
        free(queue->head);
        queue->head = next;
        if (queue->head == NULL) {
            queue->tail = NULL;
            queue->size=0;
        } else {
            queue->size--;
        }

        if( queue->intId != NO_INT ) {
            // enable int,or release mutex.
        }
    }
    return popped;
}

void processQueue(struct queueRoot* queue, void (*func)(queue_data_type)){
    struct queueName *next = NULL;

    if (queue == NULL) {
        return;
    }

    struct queueName* current = queue->head;
    while (sizeOfQueue(queue) >  0) {
        func( popQueue(queue));
        /*
           if( queue->intId !=0 ) {
        // Disable int
        }
        next = current->next;
        func(current->contents);
        current = next;

        if( queue->intId !=0 ) {
        // Enable int
        }
        */
    }
}

int sizeOfQueue(struct queueRoot* queue) {
    int size = 0;
    if( queue->intId != NO_INT ) {
        // Disable int or acquire mutex
    }
    size = queue->size;

    if( queue->intId != NO_INT ) {
        // Enable int or release mutex
    }
    return size;
}

bool queueEmpty( struct queueRoot *queue) {
    bool empty=true;

    if( queue->intId != NO_INT ) {
        // Disable int or acquire mutex
    }
    empty = (queue->size == 0) ? true : false;

    if( queue->intId != NO_INT ) {
        // Enable int or release mutex
    }
    return empty;
}

