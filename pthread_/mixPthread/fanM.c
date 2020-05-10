#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details. 
#include <pthread.h>
#include <time.h>



//----------------------------------
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

int counter=1000000;


void *ThreadFun0(void *vargp){ 

    int i;

    sleep(1); 
    while(1){
        printf("#:[%d] Counter:[%d]\n", i, counter);
        printf("%s", KGRN);
        i++;
        if(i>=1000){return(0);}
        counter--;
    }
 return NULL; 
 } 
 
void *ThreadFun1(void *vargp){ 
    int i;

    sleep(1); 
    while(1){
        printf("#:[%d] Counter:[%d]\n", i, counter);
        printf("%s", KBLU);
        if(i==1000)
            return(0);
        i++;
        counter--;
    }
 return NULL; 
 }   
//----------------------------------


int main(){ 
    pthread_t id0, id1;
 
    pthread_create(&id0, NULL, ThreadFun0, NULL);
    pthread_create(&id1, NULL, ThreadFun1, NULL); 
   

    pthread_join(id0, NULL);
    pthread_join(id1, NULL); 
  

 exit(0); 
}