
#ifndef _MYDB_H
#define _MYDB_H
#include <string>

// #include "msgClass.h"
#include "database.h"
#include "msg.h"

// extern struct freePoolDef *pool;

class myDatabase : public database {
    private:
        void doPublish(std::string key);
    public:
        bool add(std::string, std::string) ;
        void act( enum threadId id, const std::string key, const std::string value) ;
}; 
#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif
