#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <setjmp.h>
#include "sched2.h"

#include <queue>

using namespace std;

queue<int> queueIn3;

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
        queueIn3.push(idx); 
        idx++;
        yield();
    }
}

void thread3(void) {
    int t=0;
    while (1) {

        // Gte message from Q and print it
        if(false == queueIn3.empty()) {
            t=queueIn3.front();
            queueIn3.pop();

            printf("t3 = %d\n", t);
        }
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

