#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <setjmp.h>
#include "sched2.h"
#include "simpleQ.h"

struct queueRoot root;

void thread1(void) {
    int count=0;
    while (1) {
        count++;

        if( (count % 2) == 0) {
            printf("thread 1:even");
        } else {
            printf("thread 1:Odd");
        }
        printf("\n");
        yield();
    }
}

void thread2(void) {
    int idx=0;
    while (1) {
        // Put message in Q
        pushQueue(&root, sizeof(void *), idx);
        idx++;
        yield();
    }
}

void thread3(void) {
    int t=0;
    while (1) {

        // Gte message from Q and print it
        if( queueEmpty( &root ) ) {
            printf("thread 3:Q Empty\n");
        } else {
            t = popQueue( &root );

            printf("hread 3:%d\n",t);
        }
        yield();
    }
}

int main() {
    int i = 0;
    initThreadTable();
    initQueue(&root, (uint8_t)0);

    run_queue_head = run_queue_tail = NO_THREAD;
    stack_swap_start = (STR) &i;

    if (!setjmp(new_thread_start_buff)) {
        /* starts three threads */
        startNewThread(thread1); // should error-check return value.
        startNewThread(thread2);
        startNewThread(thread3);
        swapThreadBlock();
    }
    (*(cpr->function))();
    freeCurrentThread();
}

