
/* Lightweight Multitasker in C -- by Jonathan Finger, 1995   (reformatted) */

/*
#include <setjmp.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include <setjmp.h>
#include <stdlib.h>
*/
#include "sched2.h"

THREAD_NUM  current_thread = NO_THREAD;
#if 0
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
        yield();
    }
}

void thread3(void) {
    while (1) {
        printf("\n\rthread 3");
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
#endif

void initThreadTable() {
    int i = 0;

    while (i < MAX_THREAD) {
        thread[i].threadNumber = i;
        thread[i].queue         = 'F';
        thread[i].next_thread   = i + 1;
        thread[i].prev_thread   = i - 1;
        i++;
    };
    thread[MAX_THREAD-1].next_thread = NO_THREAD;
}

int startNewThread(void (*program)(void)) {
    THREAD_NUM thread_num;
    thrd *threadp;
    thread_num = getFreeThreadId();
    if (thread_num == NO_THREAD) return(NO_THREAD);
    threadp = &thread[thread_num];
    threadp->c_stack_size = 0;
    threadp->next_thread  = NO_THREAD;
    threadp->function     = program;
    memcpy(threadp->swapThreadBuff, new_thread_start_buff, sizeof(jmp_buf));

    /* 
     * the memcpy copies the contents of new_thread_start_buff 
     * to the thread's swap buff so that when swapInThread() 
     * calls longjmp(), control returns from the setjmp in main()
     */
    queueThread(thread_num);
    return(thread_num);
}

static int getFreeThreadId() {
    int i = 0;
    do {
        while ((i < MAX_THREAD) && (thread[i].queue != 'F')) 
            i++;
        if (i < MAX_THREAD) {
            return(i);
        }
    } while (i < MAX_THREAD);
    return(NO_THREAD);
}

void setupThreadGlobals(THREAD_NUM thread_num, STR buff) {
    /*STR buff; needed to defeat optimizer */
    cpr = &thread[thread_num];
}

void saveThreadGlobals() {
}

int swapOutThread() {
    long int i;
    if (current_thread == NO_THREAD) {
        return(0);
    }
    saveThreadGlobals();     
    i = stack_swap_start - ((STR)&i);
    cpr->c_stack_size = (size_t) i;
    memcpy(cpr->c_stack, ((STR)&i)+1, (size_t) i);
    return(setjmp(cpr->swapThreadBuff));
    /* 
     * The setjmp sets the return point where the thread will 
     * resume execution when longjmp() in swapInThread()  
     */
}

void swapInThread() {
    UCHAR buffer[THREAD_SWAP_STACK_SIZE];
    /* make sure we are above (below) the swap stack */
    current_thread = run_queue_head;
    setupThreadGlobals(current_thread, &buffer[0]);
    memcpy(stack_swap_start - cpr->c_stack_size + 1, cpr->c_stack, cpr->c_stack_size);

    /* 
     * longjmp() transfers control back to setjmp() in swapOutThread 
     */
    longjmp(cpr->swapThreadBuff, 1);
}

void swapThreadInMs(int ms) {

    usleep(ms * 1000);
    swapThread();
}

void swapThread() {
    int next_thread;
    next_thread = thread[run_queue_head].next_thread;

    if (next_thread != NO_THREAD) {
        run_queue_head = next_thread;
        thread[run_queue_tail].next_thread = current_thread;
        run_queue_tail = current_thread;
        thread[current_thread].next_thread = NO_THREAD;

        if (!swapOutThread()) {
            swapInThread();
        }
        /* if swapOutThread() returns 0, this is a return from the
         * call to swapOutThread and we call swapInThread. If it 
         * returns !0 then swapOutThread is returning from longjmp()
         * in swapInThread and task switch has already occurred 
         */
    }
}

/*
 * put current thread to sleep on event.
 */
void swapThreadBlock() {
    while (run_queue_head == NO_THREAD) 
        continue;
    /* if this loop is encountered and run queue is empty, 
     * process idles until a process is queue either in an 
     * interrupt service routine or signal handler 
     */
    if (current_thread != run_queue_head && !swapOutThread()) {
        swapInThread();
    }
}

/* 
 * If run queue can be modified by an interrupt service routine or
 * signal handler then code must be added to assure mutual exclusion 
 */
void queueThread(THREAD_NUM threadNumber) {
    if (run_queue_tail != NO_THREAD) {
        thread[run_queue_tail].next_thread = threadNumber;
    } else {
        run_queue_head = threadNumber;
    }
    run_queue_tail = threadNumber;
    thread[threadNumber].next_thread = NO_THREAD;
    thread[threadNumber].queue = 'R';
}

void unqueueThread(UCHAR new_queue) {
    THREAD_NUM thread_num;
    thread_num = run_queue_head;
    if ((run_queue_head =  thread[thread_num].next_thread) == NO_THREAD) {
        run_queue_tail = NO_THREAD;
    }
    thread[thread_num].queue = new_queue;
}

void freeCurrentThread() {
    freeThread(current_thread);                    
    unqueueThread('F');
    swapThreadBlock(); /* this will never return */
}

int freeThread(THREAD_NUM thread_num) {

    thrd *threadp = &thread[thread_num];
    if (threadp->queue == 'F') {
        return(0);
    }
    if (current_thread == thread_num) {
        current_thread = NO_THREAD;
    }
    return(1);
}

