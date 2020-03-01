/***********************************************************************
 * AUTHOR: andrewh <andrewh>
 *   FILE: .//msgClass.cpp
 *   DATE: Thu Feb 27 18:03:42 2020
 *  DESCR: 
 ***********************************************************************/
#include "msgClass.h"
#include <string.h>

#include <iostream>

/***********************************************************************
 *  Method: msg::msg
 *  Params: 
 * Effects: 
 ***********************************************************************/
msg::msg() {
}


/***********************************************************************
 *  Method: msg::display
 *  Params: 
 * Returns: void
 * Effects: 
 ***********************************************************************/
void msg::display() {
    std::cout << "Message Display" << std::endl;
    std::cout << "===============" << std::endl;
    std::cout << "Op code : " << cmd ;
    std::cout << " is " << cmdToString() << std::endl;
    std::cout << "Sender  :>" << sender << "<" << std::endl;
    std::cout << "Key     :>" << key    << "<" << std::endl;
    std::cout << "Value   :>" << value  << "<" << std::endl;
    std::cout << "==================="  << std::endl;
}


/***********************************************************************
 *  Method: msgPool::commonInit
 *  Params: int max, int min
 * Returns: void
 * Effects: 
 ***********************************************************************/
void msgPool::commonInit() {
    for(int i= 0 ; i< initialPoolSize; i++ ) {
        thePool.push_back( new msg );
    }
}

/***********************************************************************
 *  Method: msgPool::msgPool
 *  Params: 
 * Effects: 
 ***********************************************************************/
msgPool::msgPool() {
    commonInit();
}

/***********************************************************************
 *  Method: msgPool::msgPool
 *  Params: int max
 * Effects: 
 ***********************************************************************/
msgPool::msgPool(int max) {
    maxPoolSize = max;
    commonInit();
}


/***********************************************************************
 *  Method: msgPool::msgPool
 *  Params: int max, int min
 * Effects: 
 ***********************************************************************/
msgPool::msgPool(int max, int min) {
    maxPoolSize = max;
    initialPoolSize = min;
    commonInit();
}

/***********************************************************************
 *  Method: msgPool::display
 *  Params: 
 * Returns: void
 * Effects: 
 ***********************************************************************/
void msgPool::display() {
    std::cout << "Pool Display" << std::endl;
    std::cout << "============" << std::endl;

    std::cout << "Capacity  : " << int( getCapacity() ) << std::endl;
    std::cout << "Available : " << int( thePool.size() ) << std::endl;
    std::cout << "============" << std::endl;
}


/***********************************************************************
 *  Method: msg::setCmd
 *  Params: cmdOpcode c
 * Returns: void
 * Effects: 
 ***********************************************************************/
void msg::setCmd(cmdOpcode c) {
    cmd = c;
}


/***********************************************************************
 *  Method: msg::setKey
 *  Params: std::string k
 * Returns: void
 * Effects: 
 ***********************************************************************/
void msg::setKey(std::string k) {
    key = k;
}


/***********************************************************************
 *  Method: msg::setValue
 *  Params: std::string v
 * Returns: void
 * Effects: 
 ***********************************************************************/
void msg::setValue(std::string v) {
    value = v;
}


/***********************************************************************
 *  Method: msg::getCmd
 *  Params: 
 * Returns: cmdOpcode
 * Effects: 
 ***********************************************************************/
cmdOpcode msg::getCmd() {
    return cmd;
}


/***********************************************************************
 *  Method: msg::getKey
 *  Params: 
 * Returns: std::string
 * Effects: 
 ***********************************************************************/
std::string msg::getKey() {
    return key;
}


/***********************************************************************
 *  Method: msg::getValue
 *  Params: 
 * Returns: std::string
 * Effects: 
 ***********************************************************************/
std::string msg::getValue() {
    return value;
}


/***********************************************************************
 *  Method: msg::clear
 *  Params: 
 * Returns: void
 * Effects: 
 ***********************************************************************/
void msg::clear() {
    cmd = NOP;
    key = "";
    value = "";
}


/***********************************************************************
 *  Method: msg::serialize
 *  Params: uint8_t *ptr
 * Returns: int
 * Effects: Copy the data into a caller provided buffer for transmission.
 *      Return length of data or < 0 on error.
 *
 ***********************************************************************/
int msg::serialize(uint8_t *ptr, int maxLen) {
    int len=0;
    int idx = 0;

    bool validCmd = ( cmd == NOP ||cmd == GET || cmd == SET || cmd == SUB || cmd == UNSUB) ;

    if( validCmd ) {

        memset(ptr, 0, maxLen);

        uint8_t senderLen=sender.length();
        uint8_t keyLen   =key.length();
        uint8_t valueLen =value.length();

        ptr[idx++] = (uint8_t)cmd;
        ptr[idx++] = senderLen;
        strncpy( (char *)&ptr[idx], sender.c_str(), senderLen);
        idx += senderLen ;
        
        ptr[idx++] = keyLen;
        strncpy( (char *)&ptr[idx], key.c_str(), keyLen);
        idx += keyLen ;

        if ( cmd == SET ) {
            ptr[idx++] = valueLen;
            strncpy( (char *)&ptr[idx], value.c_str(), valueLen);
            idx += valueLen;
        }
    }

    return idx;
}

/***********************************************************************
 *  Method: msg::deSerialize
 *  Params: uint8_t *ptr, int maxLen
 * Returns: int
 * Effects: Takse a serialised message and unpacks it into the fields.
 ***********************************************************************/
int msg::deSerialize(uint8_t *ptr, int maxLen) {
    int idx = 0;
    
    cmdOpcode c = (cmdOpcode) ptr[idx++];
    uint8_t senderLen = (uint8_t) ptr[idx++];
    
    std::string sender( (char *)&ptr[idx], senderLen);
    idx += senderLen ;
   
    uint8_t localKeyLen = (uint8_t) ptr[idx++];
    std::string localKey( (char *)&ptr[idx], localKeyLen);
    idx += localKeyLen ;
   
    uint8_t localValueLen = (uint8_t) ptr[idx++];
    std::string localValue( (char *)&ptr[idx], localValueLen);
    idx += localValueLen ;
    
    
    std::cout << "======" << std::endl;
    std::cout << sender << std::endl;
    std::cout << localKey << std::endl;
    std::cout << localValue << std::endl;
    std::cout << "======" << std::endl;
    
}


/***********************************************************************
 *  Method: msg::cmdToString
 *  Params: 
 * Returns: std::string
 * Effects: 
 ***********************************************************************/
std::string msg::cmdToString() {

    std::string command = "";

    switch(cmd) {
        case NOP:
            command = "NOP";
            break;
        case GET:
            command = "GET";
            break;
        case SET:
            command = "SET";
            break;
        case SUB:
            command = "SUB";
            break;
        case UNSUB:
            command = "UNSUB";
            break;
        default:
            command = "UNKNOWN";
            break;
    }
    return command;
}


/***********************************************************************
 *  Method: msgPool::poolSize
 *  Params: 
 * Returns: int
 * Effects: 
 ***********************************************************************/
int msgPool::poolSize() {
    return thePool.size();
}


/***********************************************************************
 *  Method: msgPool::getMsg
 *  Params: 
 * Returns: msg *
 * Effects: 
 ***********************************************************************/
msg *msgPool::getMsg() {

    msg *ptr = nullptr;

    if( thePool.size() > 0) {
        ptr = thePool.front();
        thePool.pop_front();
    } 

    if( thePool.size() == 0) {
        if( capacity < maxPoolSize ) {
            thePool.push_back( new msg );
            capacity++;
        }
    }
    return ptr;
}


/***********************************************************************
 *  Method: msgPool::returnMsg
 *  Params: msg *p
 * Returns: void
 * Effects: 
 ***********************************************************************/
void msgPool::returnMsg(msg *p) {
    p->clear();

    thePool.push_back( p );
}


/***********************************************************************
 *  Method: msgPool::getCapacity
 *  Params: 
 * Returns: int
 * Effects: 
 ***********************************************************************/
int msgPool::getCapacity() {
    return capacity;
}


/***********************************************************************
 *  Method: msgPool::setMaxMessages
 *  Params: int m
 * Returns: void
 * Effects: Increase the maximum pool size.
 ***********************************************************************/
void msgPool::increaseMaxMessages(int m) {
    maxPoolSize += m;
}


/***********************************************************************
 *  Method: msgPool::preAllocateMax
 *  Params: 
 * Returns: void
 * Effects: Pre-allocates 'maxPoolSize' empty messages.
 ***********************************************************************/
void msgPool::preAllocateMax() {
    if( capacity < maxPoolSize ) {
        for(int i = 0; i < (maxPoolSize - capacity); i++) {
            thePool.push_back( new msg );
        }
    }
}


/***********************************************************************
 *  Method: msg::set
 *  Params: cmdOpcode c, std::string s, std::string k, std::string v
 * Returns: void
 * Effects: 
 ***********************************************************************/
void msg::set(cmdOpcode c, std::string s, std::string k, std::string v) {
    cmd    = c;
    sender = s;
    key    = k;
    value  = v;
}



/***********************************************************************
 *  Method: msg::setSender
 *  Params: std::string s
 * Returns: void
 * Effects: 
 ***********************************************************************/
void msg::setSender(std::string s) {
    sender =s;
}


/***********************************************************************
 *  Method: msg::getSender
 *  Params: 
 * Returns: std::string
 * Effects: 
 ***********************************************************************/
std::string msg::getSender() {
    return sender;
}


