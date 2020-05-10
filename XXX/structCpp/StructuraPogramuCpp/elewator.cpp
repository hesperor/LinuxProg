#include <iostream>
#include "elewator.h"

using namespace std;

/* class Floor */
 void Floor::write(){
    cout << "Zapis: " << endl;
    cout << "Get code: "; cin >> code;
    cout << "Get name:"; cin >> name;
 }
 void Floor::read(){
    cout << "code: " << code << endl; 
    cout << "name: " << name << endl;
 }



 Floor::Floor(int c_, string n_){
    name=n_;
    code=c_;
 } 
 Floor::~Floor(){
    cout << "Finish Floor" << endl;
 }
//--------------->
/* class Driver*/
 void Driver::EncoderVar(){
     if((run==1 && up==1) & (stop==0)){encoderVal++;}
     if((run==1 && down==1) & (stop==0)){encoderVal--;}
 }
 void Driver::read(){
    cout << "EncoderVar: " << encoderVal << endl;
    cout << "up: " << up << endl; 
    cout << "down: " << down << endl;
    cout << "run: " << run << endl;
    cout << "stop: " << stop << endl; 
    cout << "nameDriver: " << nameDriver << endl;
 }



 Driver::Driver(int encoder_, int up_, int down_, int run_, int stoop_, string name_){
    encoderVal=encoder_;
    up=up_;
    down=down_;
    run=run_;
    stop=stoop_;
    nameDriver=name_;
 }
 Driver::~Driver(){
    cout << "Finish Driver" << endl;
 }
//--------------->