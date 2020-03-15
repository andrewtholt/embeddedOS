
#include "parseMsg.h"

bool parseMsg(struct myDatabase *mydb, struct msg *m ) {
    bool failFlag = true;

    switch( m->cmd ) {
        case NOP:
            break;
        case SET:
            failFlag = dbAdd(mydb, m->key, m->value);
            break;
        case GET:
            break;
        case SUB:
            break;
        case UNSUB:
            break;
    }


    return failFlag;
}


