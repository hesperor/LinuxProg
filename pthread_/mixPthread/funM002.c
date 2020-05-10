#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>      
#include <pthread.h>   


//fonts color
#define FBLACK      "\033[30;"
#define FRED        "\033[31;"
#define FGREEN      "\033[32;"
#define FYELLOW     "\033[33;"
#define FBLUE       "\033[34;"
#define FPURPLE     "\033[35;"
#define D_FGREEN    "\033[6;"
#define FWHITE      "\033[7;"
#define FCYAN       "\x1b[36m"

//background color
#define BBLACK      "40m"
#define BRED        "41m"
#define BGREEN      "42m"
#define BYELLOW     "43m"
#define BBLUE       "44m"
#define BPURPLE     "45m"
#define D_BGREEN    "46m"
#define BWHITE      "47m"

//end color
#define NONE        "\033[0m"

//printf(D_FGREEN BBLUE"Change color!\n"NONE);
//------------------------------------------------->

void delay(int number_of_seconds){ 
    
    int milli_seconds = 1000 * number_of_seconds;   // Converting time into milli_seconds   
    clock_t start_time = clock();                   // Stroing start time 

    while (clock() < start_time + milli_seconds)    // looping till required time is not acheived 
        ; 
 } 
void* fun0(void* data){
    int data_ = (int)data;     	
    int i;

    pthread_detach(pthread_self());

    while(1){
        printf("\x1B[36m [%d] Data:[%d]", i, data_);
        i++;
        delay(100);
    }
 pthread_exit(NULL);			
 }

void* fun1(void* data){
    int data_ = (int)data;     
    int i;

    pthread_detach(pthread_self());

    while(1){
        printf("\x1B[35m [%d] Data:[%d]", i, data_);
        i++;
        delay(100);
    }
 pthread_exit(NULL);			
 }

void error(char *msg){
    fprintf(stderr , "%s:%s\n", msg, strerror(errno));
    exit(1);
 }
//---------------------------------------------------------------------------
int main(int argc, char **argv){
         	
    pthread_t id0;
    pthread_t id1;     	
    int t=11;  

    
    if(pthread_create(&id0, NULL, fun0, (void*)t)==-1)
        error("No run pthread nr 1");
    if(pthread_create(&id1, NULL, fun1, (void*)t)==-1)
        error("NO run pthread nr 2");  

    void *result;
    if(pthread_join(id0, &result)==-1)
        error("Error pthread 1");
    if(pthread_join(id1, &result)==-1)
        error("Error pthread 2");

/*
    pthread_join(id0, NULL);
    pthread_join(id1, NULL);
*/  
    //pthread_exit(NULL);	
}	
