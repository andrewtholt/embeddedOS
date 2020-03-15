
#include "myDatabase.h"
#include <queue>
#include <iostream>

// extern std::map<std::string, std::queue<msg *> *>  pipe;

myDatabase::myDatabase() : database () {

}

myDatabase::myDatabase(threadId o) : database () {
    owner = o;
    ownerSet = true;
}

bool myDatabase::parseMsg(struct msg *m) {
    bool failFlag = true;

    switch( m->cmd ) {
        case NOP:
            break;
        case SET:
            failFlag = add( m->key, m->value);
            break;
        case GET:
            {
                std::string v = get( m->key);
                // 
                // TODO Assemble SEND message to sender, and
                // send it.
                // 
            }
            break;
        case SUB:
            (subs[m->key]).insert(m->sender);
            // 
            // TODO Assemble SEND message to sender, and
            // send it.
            // 
            break;
        case UNSUB:
            // 
            // TODO Delete this sender from the subscribe list, no message.
            // 
            break;
        default:
            failFlag=true;
            break;
    }

    return failFlag;
}

void myDatabase::setOwner(threadId o) {

    if( ownerSet == false ) {
        owner = o;
        ownerSet = true;
    }
}

bool myDatabase::add(std::string k, std::string v) {
    std::cout << "Here" << std::endl;
    bool pub = true;
    bool ff = database::add(k,v);  // true if created,

    int subSize = (subs[k]).size();

    if( pub ) {
        if (subSize > 0) {
            for(auto f: subs[k]) {
                printf("Subscriber %d\n", f);
                // 
                // TODO Send message to subscriber here
                // 
            }
        }
    }
    return ff;
}

std::string myDatabase::get(std::string key) {
    return database::get(key);
}


#ifdef __cplusplus
extern "C" {
#endif
    struct myDatabase *newDatabase() {
        return new myDatabase();
    }

    void dbSetOwner(struct myDatabase *db, enum threadId id) {
        db->setOwner(id);
    }

    bool dbAdd(struct myDatabase *db,char *key, char *value) {
        bool failFlag = db->add(key, value);
        return failFlag;
    }

    const char *dbGet(struct myDatabase *db,char *key) {
        std::string tmp = db->get(key);

        const char *ret= tmp.c_str();
        return ret;
    }
    bool dbParseMsg(struct myDatabase *db, struct msg *m) {
        db->parseMsg( m );
    }

#ifdef __cplusplus
}
#endif
