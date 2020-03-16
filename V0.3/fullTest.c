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
// #include "parseMsg.h"


void thread1(void) {
    int count=0;

    const threadId iam = THREAD1;
    while (1) {
        count++;

        if( (count % 2) == 0) {
            printf("\n\rthread 1:even\n");
        } else {
            printf("\n\rthread 1:Odd\n");
        }
        yield();
    }
}

void thread2(void) {
    bool failFlag = true;
    const threadId iam = THREAD2;
    int counter = 1;
    
    char valueBuffer[MAX_VALUE];
    memset(valueBuffer, 0, MAX_VALUE);

    struct myDatabase *mydb = newDatabase();
    dbSetOwner(mydb, iam);

    if( mydb == NULL ) {
        fprintf(stderr, "thread2: failed to create db");
        exit(2);
    }

    failFlag = dbAdd(mydb, "TEST", "0000");

    tasks[THREAD2] = mkQueue();

    while (1) {
        printf("\n\rthread 2");
        
        sprintf(valueBuffer,"%04d", counter++);
        failFlag = dbAdd(mydb, "TEST", valueBuffer);

        if( queueEmpty( tasks[THREAD2])== false ) {
            printf("\nI have work\n");

            struct msg *ptr = (struct msg *)popQueue( tasks[THREAD2] );
            displayMsg( ptr );
            //
            //  Update the database from the message
            //
            failFlag = dbParseMsg(mydb, ptr);
        }

        yield();
    }
}

void thread3(void) {

    bool failFlag=true;
    const threadId iam = THREAD3;

    struct myDatabase *mydb = newDatabase();
    dbSetOwner(mydb, iam);

    tasks[iam] = mkQueue();

    waitUntilReady(THREAD2);

    struct msg *myMsg = mkMsg(iam, GET, "TEST", "");
    pushQueue( tasks[THREAD2], (void *)myMsg );

    myMsg = mkMsg(iam, SUB, "TEST", "");

    pushQueue( tasks[THREAD2], (void *)myMsg );

    while (1) {
        printf("\n\rthread 3");
        if( queueEmpty( tasks[THREAD3])== false ) {
            printf("\nI have work\n");
            struct msg *ptr = (struct msg *)popQueue( tasks[iam] );
            displayMsg( ptr );
            failFlag = dbParseMsg(mydb, ptr);
        }
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

