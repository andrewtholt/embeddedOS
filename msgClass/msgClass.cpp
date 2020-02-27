/***********************************************************************
 * AUTHOR: andrewh <andrewh>
 *   FILE: .//msgClass.cpp
 *   DATE: Thu Feb 27 18:03:42 2020
 *  DESCR: 
 ***********************************************************************/
#include "msgClass.h"

#include <iostream>

/***********************************************************************
 *  Method: msg::msg
 *  Params: 
 * Effects: 
 ***********************************************************************/
msg::msg()
{
}


/***********************************************************************
 *  Method: msg::display
 *  Params: 
 * Returns: void
 * Effects: 
 ***********************************************************************/
void msg::display() {

    std::cout << "Op code : " << cmd   << std::endl;
    std::cout << "Key     :>" << key   << "<" << std::endl;
    std::cout << "Value   :>" << value << "<" << std::endl;
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
void
msg::setCmd(cmdOpcode c)
{
}


/***********************************************************************
 *  Method: msg::setKey
 *  Params: std::string k
 * Returns: void
 * Effects: 
 ***********************************************************************/
void
msg::setKey(std::string k)
{
}


/***********************************************************************
 *  Method: msg::setValue
 *  Params: std::string v
 * Returns: void
 * Effects: 
 ***********************************************************************/
void
msg::setValue(std::string v)
{
}


/***********************************************************************
 *  Method: msg::getCmd
 *  Params: 
 * Returns: cmdOpcode
 * Effects: 
 ***********************************************************************/
cmdOpcode
msg::getCmd()
{
}


/***********************************************************************
 *  Method: msg::getKey
 *  Params: 
 * Returns: std::string
 * Effects: 
 ***********************************************************************/
std::string
msg::getKey()
{
}


/***********************************************************************
 *  Method: msg::getValue
 *  Params: 
 * Returns: std::string
 * Effects: 
 ***********************************************************************/
std::string
msg::getValue()
{
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


