#ifndef _TESTING
#define _TESTING

#ifdef __cplusplus
#include <string>

enum cmdOpcode {
    NOP=0,
    GET,
    SET,
    SUB,
    UNSUB
};

class msg {
    private:
        cmdOpcode cmd;
        std::string key;
        std::string value;
        // msgId id;

    public:
        msg();
        void setCmd(cmdOpcode c);
        void setKey(std::string k);
        void setValue(std::string v);

        cmdOpcode getCmd();
        std::string getKey();
        std::string getValue();

        void clear();

        void display();
};

class msgPool {
    private:

    public:

        msgPool();
        std::string msgPooling;

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
