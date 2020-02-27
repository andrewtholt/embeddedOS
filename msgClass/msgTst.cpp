#include "msgClass.h"
#include <iostream>
#include <string>

using namespace std;

int main() {

    msg fred;

    fred.display();

    fred.display();

    fred.setKey("TEST");
    fred.display();

    fred.setValue("VALUE");
    fred.display();
}

