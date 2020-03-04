
#include "myDatabase.h"
#include <queue>

extern std::map<std::string, std::queue<msg *> *>  pipe;

void myDatabase::act( std::string id, const std::string key, std::string value) {

    msg *ptr = pool.getMsg();

    if( ptr == NULL) {
        printf("No messages remaining\n");
    } else {

        ptr->set(SET,"NO_ONE",key,value);

        std::queue<msg *> *out=pipe[id];

        out->push( ptr );

        printf("PUBLISH ID  : %s\n", id.c_str());
        printf("       KEY  : %s\n", key.c_str());
        printf("       VALUE: %s\n", value.c_str());
    }
}

void myDatabase::doPublish(std::string key) {

    const std::set<std::string> *ptr = getSubscriber(key); 
    const std::string value = get(key);

    if( ptr->size() > 0 ) {
        for( auto id : *ptr ) {
            act( id, key, value) ;
        }
    }
}

bool myDatabase::add(std::string k, std::string v) {
    std::cout << "Here" << std::endl;

    bool f = database::add(k,v);  // True if created.
    bool pub = true;

    // Changed
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

    pub = true;

    if( pub ) {
        doPublish(k);
    }

    return pub;
}
