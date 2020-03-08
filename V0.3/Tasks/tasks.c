#include "sched2.h"
#include "tasks.h"

struct queueRoot *tasks[LAST];
// 
// A task is ready when it has written it Q ptr into the tasks list.
//
bool taskReady(threadId id) {
    bool ready = false;

    if( tasks[ id ] == NULL ) {
        ready = false ;
    } else {
        ready = true ;
    }

    return ready;
}

void waitUntilReady(threadId id) {

    while( taskReady( id ) == false ) {
        yield();
    }
}
