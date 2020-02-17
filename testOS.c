#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <setjmp.h>
#include "sched2.h"
#include "simpleQ.h"

void thread1(void) {
    int count=0;
    while (1) {
        count++;

        if( (count % 2) == 0) {
            printf("\n\rthread 1:even");
        } else {
            printf("\n\rthread 1:Odd");
        }
        yield();
    }
}

void thread2(void) {
    while (1) {
        printf("\n\rthread 2");

        // Put message in Q
        yield();
    }
}

void thread3(void) {
    while (1) {
        printf("\n\rthread 3");

        // Gte message from Q and print it
        yield();
    }
}

int main() {
    int i = 0;
    initThreadTable();
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

