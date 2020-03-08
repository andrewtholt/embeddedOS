/***********************************************************************
 * AUTHOR:  <andrewh>
 *   FILE: .//database.cpp
 *   DATE: Fri Feb 21 12:41:37 2020
 *  DESCR: 
 ***********************************************************************/
#include "database.h"

/***********************************************************************
 *  Method: database::commonInit
 *  Params: 
 * Returns: void
 * Effects: 
 ***********************************************************************/
void
database::commonInit()
{
}

/***********************************************************************
 *  Method: database::database
 *  Params: 
 * Effects: 
 ***********************************************************************/
database::database()
{
}


/***********************************************************************
 *  Method: database::add
 *  Params: std::string key, std::string v
 * Returns: bool
 * Effects: Return true if the value had to be created, otherwise false.
 ***********************************************************************/
bool database::add(std::string key, std::string v) {

    bool flag=false;

    if( data.count( key ) == 0 ) {
        data[key] = new dbValue( v );
        flag=true;
    } else {
        if( v == data[key]->getValue() ) {
            flag = false;
        } else {
            data[key]->setValue( v ) ;
            flag=true;
        }
    }
    return flag;
}


/***********************************************************************
 *  Method: database::get
 *  Params: std::string key
 * Returns: std::string
 * Effects: 
 ***********************************************************************/
std::string database::get(std::string key) {
    std::string result="<NO DATA>";

    if( data.count( key ) == 1 ) {
        result = data[key]->getValue();
    }

    return result;

}


/***********************************************************************
 *  Method: database::display
 *  Params: 
 * Returns: void
 * Effects: 
 ***********************************************************************/
void database::display() {

    for(std::pair<std::string, dbValue* > element : data ) {
        std::cout << "Key   : " << element.first << std::endl;
        data[element.first]->display();
    }

}

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

