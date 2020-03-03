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

#include "myDatabase.h"

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
    
    queue<msg *> *myQ = new queue<msg *>;
    pipe["THREAD1"] = myQ;
    
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
    int count=0;
    
    string iam = "THREAD2";
    
    bool ready=false;
    
    queue<msg *> *myQ = new queue<msg *>;
    pipe[iam] = myQ;
    
    waitUntilReady("THREAD3");
    
    queue<msg *> *t3Q ;
    t3Q = pipe["THREAD3"];
    
    msg *ptr = pool.getMsg(); 
    ptr->set(SUB, iam, "THREAD_TEST", "");
    t3Q->push(ptr); 

    msg *dataIn;
    bool qEmpty=false;
    while (true) {
        qEmpty = myQ->empty();
        if(false == qEmpty ) {
            dataIn = myQ->front();
            myQ->pop();

            std::cout << myQ->size() << std::endl;

            dataIn->display();
            pool.returnMsg(dataIn);
        }
        ptr->set(GET, iam, "THREAD_TEST", "");
        t3Q->push(ptr); 
        //
        // Put message in Q
        //
        /*
        ptr = pool.getMsg(); 
        
        if(ptr != nullptr) {
            ptr->set(SET, iam, "COUNT", to_string(idx++));
            t3Q->push(ptr); 
        } else {
            cout << "Message pool empty" << endl;
        }
        */
        yield();
    }
}

void thread3(void) {
    
    string iam = "THREAD3";
    queue<msg *> *myQ = new queue<msg *>;
    pipe[iam] = myQ;
    
    myDatabase myData;

    myData.add("THREAD_TEST","0");
    
    int idx=0;
    int counter=0;

    msg *dataIn;
    while (true) {
        idx--;
        if( idx <= 0) {
            counter++;
            myData.add("THREAD_TEST",to_string(counter));
            idx=1000;
            counter++;
        }
        //
        // Get message from Q and print it
        //
        bool returnMsg = true;

        if(false == myQ->empty()) {
            dataIn = myQ->front();
            myQ->pop();
            
            dataIn->display();
            
            cmdOpcode c = dataIn->getCmd();
            string from = dataIn->getSender();
            string k = dataIn->getKey();
            string v = dataIn->getValue();
            
            switch(c) {
                case SET:
                    myData.add(k,v);
                    break;
                case GET:
                    cout << "GET " << k << endl;
                    {
                        queue<msg *> *toQ ;
                        toQ = pipe[from];
    
                        std::string res = myData.get(k);
                        dataIn->setSender(iam);
                        dataIn->setValue(res);

                        toQ->push( dataIn);
                        returnMsg=false;
                    }
                    break;
                case SUB:
                    cout << "SUB " << k << endl;
                    myData.sub(from, k);
                    break;
                case UNSUB:
                    break;
            }
            
            if( returnMsg) {
                pool.returnMsg(dataIn);
            }
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

