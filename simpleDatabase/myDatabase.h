
#ifndef _MYDB_H
#define _MYDB_H
#include <string>

#include "database.h"

class myDatabase : public database {
    private:
        void doPublish(std::string key);
    public:
        bool add(std::string, std::string) ;
        void act( const void *id, const std::string key, std::string value) ;
}; 

#endif
