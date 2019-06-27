#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "simpleQ.h"

struct queueRoot root;

void func( queue_data_type content) {
    printf("Content is %p\n", content);
}

int main() {

    void *d1=(void *)0x01;
    void *d2=(void *)0x02;
    void *d3=NULL;

    initQueue(&root, (uint8_t)0);

    if( queueEmpty( &root ) ) {
        printf("Q Empty\n");
    } else {
        printf("Q Not Empty\n");
    }

    pushQueue(&root, sizeof(void *), d1);
    pushQueue(&root, sizeof(void *), d2);

    if( queueEmpty( &root ) ) {
        printf("Q Empty\n");
    } else {
        printf("Q Not Empty\n");
    }

    printf("1:size = %d\n", sizeOfQueue(&root));

    d3 = popQueue(&root);

    printf("d3 = %p\n", d3);

    processQueue(&root, func );

    printf("2:size = %d\n", sizeOfQueue(&root));

    d3 = popQueue(&root);
    printf("3:size = %d\n", sizeOfQueue(&root));

}
