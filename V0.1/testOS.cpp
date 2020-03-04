#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <setjmp.h>
#include "sched2.h"
#include "simpleQ.h"

struct queueRoot queueThread3;

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
        pushQueue(&queueThread3, sizeof(void *), (void *)idx);
        idx++;
        yield();
    }
}

void thread3(void) {
    void *t=NULL;
    while (1) {

        // Get message from Q and print it
        if( queueEmpty( &queueThread3 ) ) {
            printf("thread 3:Q Empty\n");
        } else {
            t = (void *)popQueue( &queueThread3 );

            printf("hread 3:%d\n",t);
        }
        yield();
    }
}

int main() {
    int i = 0;
    initThreadTable();
    initQueue(&queueThread3, (uint8_t)0);

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

