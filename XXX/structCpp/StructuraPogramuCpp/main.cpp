#include <iostream>
#include "elewator.h"

using namespace std;


void readAll(Floor p_, Driver m_){
    cout << "p_.code: " << p_.code << endl;
    cout << "m_.encoderVal: " << m_.encoderVal << endl;
}

int main(void)
{
    Floor shaft_no1;
    Driver motor_no1;

    cout << "Bernz (r) " << endl;

    //shaft_no1.write();
    shaft_no1.read();
    motor_no1.read();

    cout << "Bernz (r) " << endl;
    readAll(shaft_no1, motor_no1);



    return 0;
}
