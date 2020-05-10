#include <iostream>
#include <thread>

using namespace std;

class Background {
    public:
        void operator()()const{
            cout << "xxxx" <<endl; 
        }
 };
void pth(){
 int i=0;
    while(true){  
        cout << "[" << i << "]" << endl;
        i++;
    }
 }
//------------------------------


int main(int argc, char **argv){
    Background bt;


    thread t1(bt);
    thread t2(Background());

    thread t3(&pth);

    t1.join();
    //t2.join();
    t3.join();

 return 0;
}