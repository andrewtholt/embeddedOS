
#define MAX_KEY    8
#define MAX_VALUE 16

typedef enum cmdType {
    NOP = 0,
    SET,
    GET,
    SUB,
    UNSUB
} cmdType ;

struct msg {
    threadId sender;
    cmdType cmd;

    char key[MAX_KEY];
    char value[MAX_VALUE];
    
};

struct msg *mkMsg(const threadId s, const cmdType c, const char *k, const char *v);
