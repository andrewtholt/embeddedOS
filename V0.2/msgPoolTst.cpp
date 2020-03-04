#include <string>
#include <iostream>

#include "msgClass.h"

using namespace std;

int main() {

    msgPool pool;

    msg *msg;

    pool.display();

    msg = pool.getMsg() ;

    if( msg == nullptr ) {
        cout << "Message pool empty" << endl;
    } else {
        msg->display() ;
    }
    pool.display();

    // done with message
    //
    pool.returnMsg( msg );
    pool.display();

    pool.preAllocateMax();
    pool.display();
}

