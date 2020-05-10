#include <iostream>  //#include <bits/stdc++.h> 
#include <string>
#include <math.h>

#define ChannelAnalogs 3 // Numbers of analogue channels
 
using namespace std;

uint16_t analogs[ChannelAnalogs];

typedef struct HerbalFarm {
    string *namefarm;
    struct HerbalFarm *next;
    uint16_t flowerpot[ChannelAnalogs];   
}el_farm;

class Calculations {
    virtual void humanity();
    virtual void tempC();

};

class Flowerpot{
    private:
        string *nameFlowerpot;
        uint16_t humidity[ChannelAnalogs];
        uint16_t tempC[ChannelAnalogs];
    public:



};

int main(int argc, char **argv) {
    cout << "xxx"<< endl;

    return 0;
}