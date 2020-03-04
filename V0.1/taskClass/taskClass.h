#ifndef _TESTING
#define _TESTING

#include <stdlib.h>
#include <setjmp.h>

// #include "sched2.h"

#ifdef __cplusplus
#include <string>
class taskClass {
    public:
        taskClass();

        void display();
};

#endif

#ifdef __cplusplus
extern "C" {
#endif

struct taskClass* newClass();
void display(struct taskClass*);

#ifdef __cplusplus
}
#endif

#endif // _TESTING
