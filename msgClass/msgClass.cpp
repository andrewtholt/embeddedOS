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
    std::cout << "Op code : " << cmd ;
    std::cout << " is " << cmdToString() << std::endl;
    std::cout << "Key     :>" << key   << "<" << std::endl;
    std::cout << "Value   :>" << value << "<" << std::endl;
    std::cout << "===================" << std::endl;
}


/***********************************************************************
 *  Method: msgPool::msgPool
 *  Params: 
 * Effects: 
 ***********************************************************************/
msgPool::msgPool()
{
}


/***********************************************************************
 *  Method: msgPool::display
 *  Params: 
 * Returns: void
 * Effects: 
 ***********************************************************************/
    void
msgPool::display()
{
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
 * Effects: Copy the data into a buffer for transmission.  Return length
 *  of data or < 0 on error.
 *
 ***********************************************************************/
int msg::serialize(uint8_t *ptr, int maxLen) {
    int len=0;
    int idx = 0;

    memset(ptr, 0, maxLen);

    int keyLen=key.length();
    int valueLen=value.length();

    ptr[idx++] = cmd;
    ptr[idx++] = keyLen;

    strncpy( (char *)&ptr[idx], key.c_str(), keyLen);
    idx += keyLen ;

    if ( cmd == SET ) {
        ptr[idx++] = valueLen;
        strncpy( (char *)&ptr[idx], value.c_str(), valueLen);
        idx += valueLen;
    }

    return idx;
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


