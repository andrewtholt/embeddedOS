
#include "myDatabase.h"
#include <queue>

// extern std::map<std::string, std::queue<msg *> *>  pipe;

void myDatabase::act( enum threadId id, const std::string key, std::string value) {

    msg *ptr = getMsg();

    if( ptr == NULL) {
        printf("No messages remaining\n");
    } else {

        mkMsg(NO_ONE,SET,key.c_str(),value.c_str());


        pushQueue( tasks[id], sizeof(void *),ptr );
//        out->push( ptr );

        printf("PUBLISH ID  : %d\n", id);
        printf("       KEY  : %s\n", key.c_str());
        printf("       VALUE: %s\n", value.c_str());
    }
}

const std::set<enum threadId> *myDatabase::getSubscriber(const std::string key) {
}

void myDatabase::doPublish(std::string key) {

    const std::set<enum threadId> *ptr = getSubscriber(key); 
    const std::string value = get(key);

    if( ptr->size() > 0 ) {
        for( auto id : *ptr ) {
            act( id, key, value) ;
        }
    }
}

void myDatabase::sub(std::string key, enum threadId id) {
}

bool myDatabase::add(std::string k, std::string v) {
    std::cout << "Here" << std::endl;

    bool f = database::add(k,v);  // True if created.
    bool pub = true;

    // Changed
    /*
    uint8_t p = getPubPolicy(k);

    switch(p) {
        case PUB_ON_UPDATE:
            if(f == false ) {
                std::cout << k << " updated, so publish" << std::endl;
                pub = true;
            } else {
                pub = false;
            }
            break;
        case PUB_ON_CHANGE:
            if(f == true ) {
                std::cout << k << " changed, so publish" << std::endl;
                pub = true;
            } else {
                pub = false;
            }

            break;
    }
    */

    pub = true;

    if( pub ) {
        doPublish(k);
    }

    return pub;
}


#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif
