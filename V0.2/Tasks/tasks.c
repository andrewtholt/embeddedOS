#include "sched2.h"
#include "tasks.h"

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
