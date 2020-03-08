#include <stdio.h>
#include <ctype.h>
#include <string.h>

#ifndef HEXDUMP_COLS
#define HEXDUMP_COLS 8
#endif

#include "mdump.h"

void mdump( void *mem, int len) {
    unsigned int i, j;
    char lineBuffer[133];
    char tmpBuffer[16];

    for (i = 0; i < len + ((len % HEXDUMP_COLS) ? (HEXDUMP_COLS - len % HEXDUMP_COLS) : 0); i++) {
        /* print offset */
        if (i % HEXDUMP_COLS == 0) {
            sprintf(lineBuffer,"0x%06x: ", i);
        }

        /* print hex data */
        if (i < len) {
            sprintf(tmpBuffer,"%02x ", 0xFF & ((char*) mem)[i]);
            strcat(lineBuffer,tmpBuffer);
            /* end of block, just aligning for ASCII dump */
        } else {
            strcat(lineBuffer,"   ");
        }

        /* print ASCII dump */
        if (i % HEXDUMP_COLS == (HEXDUMP_COLS - 1)) {
            for (j = i - (HEXDUMP_COLS - 1); j <= i; j++) {
                /* end of block, not really printing */
                if (j >= len) {
                    strcat(lineBuffer," ");
                    /* printable char */
                } else if (isprint(((char* )mem)[j])) {
                    sprintf(tmpBuffer,"%c", (0xFF & ((char*) mem)[j]));
                    strcat(lineBuffer,tmpBuffer);
                    /* other char */
                } else {
                    strcat(lineBuffer,".");
                }
            }
            strcat(lineBuffer,"\n");

            printf("%s", lineBuffer);

//            Log::debug(lineBuffer);
        }
    }
}
