#include "msgClass.h"
#include "mdump.h"
#include <string.h>

#include <iostream>
#include <string>

#define BUFF_SIZE 255
using namespace std;

int main() {

    uint8_t len =0 ;
    uint8_t buffer[BUFF_SIZE];

    msg fred;

    fred.display();

    fred.setCmd(SET);
    fred.setKey("TEST");
    fred.setSender("IAM");
    fred.display();

    fred.setValue("VALUE");
    fred.display();

    len = fred.serialize( buffer, BUFF_SIZE );
    cout << "Length = " << int(len) << endl;
    mdump( buffer, 32 );
    
    len = fred.deSerialize( buffer, BUFF_SIZE );

    fred.clear();
    fred.display();

    fred.setCmd(GET);
    fred.setKey("TEST");
    fred.display();

    len = fred.serialize( buffer, BUFF_SIZE );
    cout << "Length = " << int(len) << endl;
    mdump( buffer, 32 );


}

