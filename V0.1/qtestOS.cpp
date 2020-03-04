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

#define MAX_NAME (16)
#define MAX_DATA (32)

enum cmdEnum {
    NOP=0,
    PING,
    GET,
    SET,
    SUB,
    UNSUB
};

struct msg {
    cmdEnum cmd;
    char key[MAX_NAME];
    char data[MAX_DATA];
};
using namespace std;

map<string, queue<struct msg> * >  pipe;

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

void dumpMsg(struct msg *ptr) {

    cout << "cmd  : " << ptr->cmd << endl;

    if(strlen(ptr->key) > 0) {
        cout << "key  : " << ptr->key << endl;
    } else {
        cout << "key  : EMPTY" << ptr->key << endl;
    }
    if(strlen(ptr->data) > 0) {
        cout << "data : " << ptr->data << endl;
    } else {
        cout << "data : EMPTY" << ptr->data << endl;
    }
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
    struct msg dataOut;
    int idx=0;

    bool ready=false;

    waitUntilReady("THREAD3");

    queue<struct msg> *t3Q = pipe["THREAD3"];

    dataOut.cmd = PING;
    strcpy(dataOut.key, "TEST");
    strcpy(dataOut.data, "DATA");

    while (true) {
        //
        // Put message in Q
        //
        sprintf(dataOut.data,"DATA%05d", idx++);
        t3Q->push(dataOut); 

        yield();
    }
}

void thread3(void) {
    struct msg dataIn;

    queue<struct msg> *myQ = new queue<struct msg>;
    pipe["THREAD3"] = myQ;

    while (true) {
        //
        // Gte message from Q and print it
        //
        if(false == myQ->empty()) {
            dataIn = myQ->front();
            myQ->pop();

            cout << "Q depth : " << myQ->size() << endl;
            dumpMsg(&dataIn);
        } else {
            cout << "T3 Empty" << endl;
            yield();
        }
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

