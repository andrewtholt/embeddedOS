
#include "myDatabase.h"


void myDatabase::act( const void *id, const std::string key, std::string value) {
        printf("PUBLISH ID  : %04x\n", id);
        printf("       KEY  : %s\n", key.c_str());
        printf("       VALUE: %s\n", value.c_str());
}

void myDatabase::doPublish(std::string key) {

    const std::set<void *> *ptr = getSubscriber(key); 
    const std::string value = get(key);

//    std::set<void *> ptr = getSubscriber( key) ;

    if( ptr->size() > 0 ) {
        for( auto id : *ptr ) {
            act( id, key, value) ;
        }
    }
}

bool myDatabase::add(std::string k, std::string v) {
    std::cout << "Here" << std::endl;
    
    bool f = database::add(k,v);
    bool pub = false;

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

    if( pub ) {
        doPublish(k);
    }

    return pub;
}
