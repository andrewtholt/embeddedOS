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

/*
struct dbValue {
    std::string value;

    uint8_t pubPolicy;

    std::set<void *> subscriber;
};
*/

class dbValue {
    private:
        std::string value;

        uint8_t pubPolicy;

        std::set<std::string> *subscriber;
//        std::set<std::string> subscriber;
    public:
        dbValue(std::string v ) {
            value = v;

            subscriber = new std::set<std::string>;

        }
        void setValue(std::string v) {
            value = v;
        }

        std::string getValue() {
            return value;
        }

        void setPubPolicy(uint8_t p) {
            pubPolicy = p;
        }

        uint8_t getPubPolicy() {
            return pubPolicy;
        }

        std::set<std::string> *getSubscriber() {
            return subscriber;
        }

        void addSubscriber(std::string id) {
            subscriber->insert( id );
        }

        void display() {
            uint8_t subCount=0;

            std::cout << "Value      : " << value << std::endl;
            subCount = subscriber->size() ;
            std::cout << "Subscribers: " << subCount <<  std::endl;

            if( subCount > 0 ) {
                for( auto elem : *subscriber ) {
                    std::cout << "\t" << elem << std::endl;
                }
            }
        }

};

class database {
    private:
//        std::map<std::string, struct dbValue *> data;
//
        std::map<std::string, dbValue *> data ;
//        std::map<std::string, dbValue *> data;
        void commonInit();

    public:
        uint8_t getPubPolicy(std::string key);
        void    setPubPolicy(std::string key, uint8_t policy);

        std::set<std::string> *getSubscriber(std::string key);
        database();

        bool add(std::string key, std::string v);
        std::string get(std::string key);

        void sub(std::string id, std::string key);
        void unsub(std::string id, std::string key);

        void display();

       void act(const std::string id, const std::string key, const std::string value);

};

#endif

#ifdef __cplusplus
extern "C" {
#endif

// struct database* newClass();
// void display(struct database*);

#ifdef __cplusplus
}
#endif

#endif // _DATABASE
