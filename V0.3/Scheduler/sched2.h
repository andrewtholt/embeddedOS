#ifndef SCHED_HEAD
#define SCHED_HEAD
#include <setjmp.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include <setjmp.h>
#include <stdlib.h>
#ifdef __cplusplus
extern "C" {
#endif

#define MAX_THREAD              10
#define THREAD_SWAP_STACK_SIZE  10000
typedef short    int            THREAD_NUM;
typedef unsigned char           UCHAR;
typedef unsigned long           ULONG;
typedef unsigned int            UINT;
typedef unsigned short int      USHORT;
typedef unsigned char *         STR;

/*-------------------the threads structure-------------------------------*/
struct threads {
    THREAD_NUM threadNumber;
    jmp_buf    swapThreadBuff;
    UCHAR      c_stack[THREAD_SWAP_STACK_SIZE];/* save area for c stack */
    size_t     c_stack_size;                   /* save state info       */

    THREAD_NUM volatile next_thread;   /* forward chain for queues      */
    THREAD_NUM volatile prev_thread;   /* backward chain for some queues*/
    UCHAR      volatile queue;         /* current queue that thread is  */
    /* on: 'R'means RUN, 'F'is Free  */
    void (*function)(void);
    /* other info can be added here as needed */
};
typedef struct threads thrd;
thrd thread[MAX_THREAD];
thrd *cpr; /* pointer to the current running thread */
/*-----------------------------------------------------------------------*/

jmp_buf   new_thread_start_buff;
#define NO_THREAD           (MAX_THREAD+100)

STR  stack_swap_start;

/*
 * note that the following variables have been declared volatile, since
 * they may be altered by an interrupt service routine
 */
static THREAD_NUM volatile run_queue_head;
static THREAD_NUM volatile run_queue_tail;


//------------------------Function prototypes-----------------

void     initThreadTable     (void);
int      startNewThread      (void (*program)(void));
void     freeCurrentThread   (void);
void     setupThreadGlobals  (THREAD_NUM thread_no, STR buff);
void     saveThreadGlobals   (void);
int      swapOutThread       (void);
void     swapInThread        (void);
void     swapThread          (void);  // yield

#define yield swapThread
void     swapThreadBlock     (void); // put curr thread to sleep on event
void     queueThread          (THREAD_NUM threadNumber);
void     unqueueThread        (UCHAR new_queue);
static int getFreeThreadId() ;
int freeThread(THREAD_NUM thread_num) ;

#ifdef __cplusplus
}
#endif

#endif
