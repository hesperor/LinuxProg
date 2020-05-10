#include <iostream>

using namespace std;
class Driver;

class Floor{

    //private/protected/public

 private:
    int code;
    string name;

 public:
 Floor(int=0, string="xxx");
 ~Floor();

 void write();
 void read();

 friend void readAll(Floor p_, Driver m_);
};

class Driver{
   private:
    int encoderVal;
    int up;
    int down;
    int run;
    int stop;
    string nameDriver;
   
   public:
    Driver(int=1000, int=0, int=0, int=0, int=0, string="xxx");
    ~Driver();

    void EncoderVar();
    void read();

   friend void readAll(Floor p_, Driver m_);
};