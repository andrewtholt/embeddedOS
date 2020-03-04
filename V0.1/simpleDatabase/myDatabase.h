
#ifndef _MYDB_H
#define _MYDB_H
#include <string>

#include "msgClass.h"
#include "database.h"

extern msgPool pool;

class myDatabase : public database {
    private:
        void doPublish(std::string key);
    public:
        bool add(std::string, std::string) ;
        void act( const std::string id, const std::string key, std::string value) ;
}; 

#endif
