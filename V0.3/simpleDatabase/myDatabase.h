#pragma once

#ifndef _MYDB_H
#define _MYDB_H

#ifdef __cplusplus

#include <string>
#include "database.h"
#include "msg.h"

/*
extern "C" {
#include "msg.h"
}
*/

class myDatabase : public database {
    private:
        void doPublish(std::string key);

        void act( enum threadId id, const std::string key, const std::string value) ;

        const std::set<enum threadId> *getSubscriber(const std::string key);
    public:
        std::string get(std::string);
        void sub(std::string key, enum threadId id);

        bool add(std::string k, std::string v) ;
}; 

/*
class myDbValue : public dbValue {
    private:
        std::set<enum threadId> subscriber;
    public:
        void sub(enum threadId id);

};
*/
#endif

#ifdef __cplusplus
extern "C" {
#endif
struct myDatabase *newDatabase();
bool dbAdd(struct myDatabase *db,char *key, char *value);
const char *dbGet(struct myDatabase *db,char *key);
#ifdef __cplusplus
}
#endif

#endif
