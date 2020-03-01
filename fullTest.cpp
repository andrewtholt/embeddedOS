#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <setjmp.h>
#include "sched2.h"

#include <string.h>
#include <iostream>

#include <map>
#include <queue>

#include "msgClass.h"

using namespace std;
map<string, queue<msg *> *>  pipe;

msgPool pool;


bool threadReady(string name) {
    bool ready = false;

    if ( pipe.count(name) > 0) {
        ready = true;
    } else {
        ready = false;
    }
    return ready;
}

void waitUntilReady(string name) {
    bool ready=false;
    do {
        ready = threadReady(name);

        if( ready == false) {
            yield();
        }
    } while(ready == false) ;
}


void thread1(void) {
    int count=0;

    while (true) {
        count++;
        

        if( (count % 2) == 0) {
            cout << "thread 1:Even" << endl;
        } else {
            cout << "thread 1:Odd" << endl;
        }

        yield();
    }
}

void thread2(void) {
    int idx=0;

    bool ready=false;

    waitUntilReady("THREAD3");

    queue<msg *> *t3Q ;
    t3Q = pipe["THREAD3"];

    while (true) {
        //
        // Put message in Q
        //
        msg *ptr = pool.getMsg();
        ptr->setCmd(SET);
        ptr->setKey("COUNT");

        ptr->setValue( to_string(idx++));
        
        t3Q->push(ptr); 

        yield();
    }
}

void thread3(void) {

    queue<msg *> *myQ = new queue<msg *>;
    pipe["THREAD3"] = myQ;

    msg *dataIn;
    while (true) {
        //
        // Get message from Q and print it
        //
        if(false == myQ->empty()) {
            dataIn = myQ->front();
            myQ->pop();
            
            dataIn->display();
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

