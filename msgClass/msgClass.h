#ifndef _TESTING
#define _TESTING

#ifdef __cplusplus
#include <string>
#include <list>
#define MAX_POOL_SIZE 10

enum cmdOpcode {
    NOP=0,
    SET,
    GET,
    SUB,
    UNSUB
};

class msg {
    private:
        cmdOpcode cmd;
        std::string sender;
        std::string key;
        std::string value;
        // msgId id;

        std::string cmdToString();

    public:
        msg();
        void setCmd(cmdOpcode c);
        void setSender(std::string s);
        void setKey(std::string k);
        void setValue(std::string v);

        cmdOpcode getCmd();
        std::string getSender();
        std::string getKey();
        std::string getValue();
        
        void set(cmdOpcode c,std::string s, std::string k, std::string v);

        void clear();

        void display();

        int serialize(uint8_t *ptr, int maxLen);  // Returns length, or < 0 on error.
        
        int deSerialize(uint8_t *ptr, int maxLen);  // Returns length, or < 0 on error.

};

class msgPool {
    private:
        int initialPoolSize = 1;
        int maxPoolSize = MAX_POOL_SIZE;
        int capacity = 1;
        void commonInit();
        std::list<msg *> thePool;

    public:
        msgPool();
        msgPool(int max);
        msgPool(int max, int min);

        msg *getMsg();
        void returnMsg(msg *p);

        int poolSize();
        int getCapacity();

        void increaseMaxMessages(int m);
        void preAllocateMax();

        void display();
};
#endif

#ifdef __cplusplus
extern "C" {
#endif

struct msg* newClass();
void display(struct msg*);

#ifdef __cplusplus
}
#endif

#endif // _TESTING
