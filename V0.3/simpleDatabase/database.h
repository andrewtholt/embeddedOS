#pragma once
#ifndef _DATABASE
#define _DATABASE

#include <stdint.h>

#ifdef __cplusplus
#include <string>
#include <set>
#include <map>
#include <iostream>

#define PUB_ON_UPDATE (0)
#define PUB_ON_CHANGE (1)

class dbValue {
    private:
        std::string value;

        uint8_t pubPolicy;

    public:
        dbValue(std::string v ) {
            value = v;
        }

        void setValue(std::string v) {
            value = v;
        }

        std::string getValue() {
            return value;
        }

        void display() {
            std::cout << "Value      : " << value << std::endl;
        }

};

class database {
    private:
        std::map<std::string, dbValue *> data ;
        void commonInit();

    public:
        database();

        bool add(std::string key, std::string v);
        std::string get(std::string key);

        void display();

};

#endif

#ifdef __cplusplus
extern "C" {
#endif

// struct database* newDatabase();
// void display(struct database*);

#ifdef __cplusplus
}
#endif

#endif // _DATABASE
