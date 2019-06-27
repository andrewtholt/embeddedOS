#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <setjmp.h>

#include "sched.h"

/*****************************************************************/
/*    A very simple task scheduler which does cooperative        */
/*    multitasking between two tasks only                        */
/*****************************************************************/


jmp_buf OTask;
int IsOtherTask = 0;

void SwitchToNextTask(void) {

    if ( IsOtherTask ) {
        jmp_buf ThisTask;

        if ( setjmp( ThisTask ) == 0 ) {
            jmp_buf OtherTask;
            memcpy( OtherTask, OTask, sizeof(OtherTask) );
            memcpy( OTask, ThisTask, sizeof(OTask) );
            longjmp( OtherTask, 1 );
        }
    }
}

void EndThisTask(void) {

    if ( IsOtherTask ) {   /* Switch to other task */
        jmp_buf ThisTask;
        IsOtherTask = 0;   /* Remove this task */

        if ( setjmp( ThisTask ) == 0 ) {
            jmp_buf OtherTask;
            memcpy( OtherTask, OTask, sizeof(OtherTask) );
            memcpy( OTask, ThisTask, sizeof(OTask) );
            longjmp( OtherTask, 1 );
        }
    } else {
        /* no other task to switch to -- terminate program */
        exit(0);
    }
}

void CallNewTask( void (*f)(void) ) {
    char stack_placeholder[256];
    f();
    EndThisTask();
}

int StartNewTask( void (*f)(void) ) {
    if ( IsOtherTask ) {
        return -1;     /* Other task already started */
    }

    IsOtherTask = 1;

    if ( setjmp( OTask ) == 0 ) {
        CallNewTask(f);
    }
    return 0;
}


/*****************************************************************/
/*    Test application for multitasker                           */
/*****************************************************************/

int nmax = 10;

void task1(void) {
    int n;

    for( n=1; n<=nmax; n++ ) {
        printf( "Task 1 loop %d\n", n );
        SwitchToNextTask();
    }
}

void task2(void) {
    int n;

    for( n=1; n<=nmax; n++ ) {
        printf( "Task 2 loop %d\n", n );
        SwitchToNextTask();
    }
}

int main(void) {
    StartNewTask( task1 );
    task2();
    return 0;
}

