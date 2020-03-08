#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <setjmp.h>
#include "myDatabase.h"
#include "sched2.h"
#include "simpleQ.h"
#include "tasks.h"
#include "msg.h"


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
    bool failFlag = true;
    struct myDatabase *mydb = newDatabase();

    if( mydb == NULL ) {
        fprintf(stderr, "thread2: failed to create db");
        exit(2);
    }

    failFlag = dbAdd(mydb, "TEST", "TWO");

    tasks[THREAD2] = mkQueue();

    while (1) {
        printf("\n\rthread 2");

        if( queueEmpty( tasks[THREAD2])== false ) {
            printf("\nI have work\n");

            struct msg *ptr = (struct msg *)popQueue( tasks[THREAD2] );

            displayMsg( ptr );
            //
            //  Update the database from the message
            //
            // parseMsg(mydb, ptr);
            //
            failFlag = addToPool(ptr);
        }

        yield();
    }
}

void thread3(void) {

    tasks[THREAD3] = mkQueue();

    waitUntilReady(THREAD2);

    struct msg *myMsg = mkMsg(THREAD3, SET, "TEST", "THREE");

    pushQueue( tasks[THREAD2], (void *)myMsg );

    while (1) {
        printf("\n\rthread 3");
        yield();
    }
}

int main() {
    int i = 0;
    initPool();
    initThreadTable();

    run_queue_head = run_queue_tail = NO_THREAD;
    stack_swap_start = (STR) &i;

    if (!setjmp(new_thread_start_buff)) {
        /* starts three threads */

        startNewThread(thread3);
        startNewThread(thread1); // should error-check return value.
        startNewThread(thread2);
        swapThreadBlock();
    }
    (*(cpr->function))();
    freeCurrentThread();
}

