#include <stdio.h>

#include <msg.h>


int main() {
    bool failFlag = true;

    failFlag = initPool();

    struct msg *ptr = mkMsg(THREAD3, SET,"TEST","THREE");
}
