#pragma once

#ifndef _MYDB_H
#define _MYDB_H

#ifdef __cplusplus

#include <set>
#include <string>
#include "database.h"
#include "msg.h"

extern struct queueRoot *tasks[LAST];
/*
extern "C" {
#include "msg.h"
}
*/

class myDatabase : public database {
    private:
        bool ownerSet = false;
        threadId owner = NO_ONE;

        std::map<std::string,std::set<enum threadId> > subs;

    public:
        myDatabase();
        myDatabase( threadId owner );
        void setOwner( threadId owner );
        std::string get(std::string);
//        void sub(std::string key, enum threadId id);

        bool add(std::string k, std::string v) ;
        bool parseMsg(struct msg *m);
}; 

#endif

#ifdef __cplusplus
extern "C" {
#endif
#include "tasks.h"
#include "msg.h"

struct myDatabase *newDatabase();
bool dbAdd(struct myDatabase *db,char *key, char *value);
void dbSetOwner(struct myDatabase *db,enum threadId id);
const char *dbGet(struct myDatabase *db,char *key);
bool dbParseMsg(struct myDatabase *db, struct msg *m);
#ifdef __cplusplus
}
#endif

#endif
