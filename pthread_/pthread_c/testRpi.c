#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>

#include <unistd.h>
#include <time.h>

#define test_errno(msg) do{if (errno) {perror(msg); exit(EXIT_FAILURE);}} while(0)

typedef struct DataRead{
    int index;
    char strN[10];
}el_DataRead;

void ms_sleep(unsigned ms){
    struct timespec reg;
    reg.tv_sec = (ms / 1000);
    reg.tv_nsec = (ms%1000*1000000);
    nanosleep(&reg, NULL);
 }

void delay(int number_of_seconds){ 
    
    int milli_seconds = 1000 * number_of_seconds;   // Converting time into milli_seconds   
    clock_t start_time = clock();                   // Stroing start time 

    while (clock() < start_time + milli_seconds)    // looping till required time is not acheived 
        ; 
  } 
//----------------------------------- 
void *jobData(void *argx_){
    int i=0,j=0;

    //char *x=(char*)i;
    el_DataRead *argx=(el_DataRead*) argx_;
    el_DataRead *current=(el_DataRead*)malloc(sizeof(argx));


    while(1){
        argx->index=i;
        if(i==10){strcpy(argx->strN, "x");}

        i++;
        j++;
        if(i==30){i=0;}
        if(j==30){j=0;}
        //if(i==50){memset(argx->strN, 0, 0x100*sizeof(char));}
        if(i==20){memset(argx->strN, 0, 0xA*sizeof(char));}

        printf("argx:[%d]\n", argx->index);
        printf("argx:[%s]\n", argx->strN);
        printf("j:[%d]\n", j);
    current=argx;
    //sleep(2);
    ms_sleep(500);
    }

 return current;
 }
//-----------------------------------
void *dysplayData(void *argx_){
    el_DataRead *argx=(el_DataRead*)argx_; // rzutowanie typów

    fprintf(stdout, "fun_1:[]\n");
    fprintf(stdout, "index:[%d] strN:[%s]\n", 
    argx->index,
    argx->strN);
  return NULL;
 }
//-----------------------------------

int main(int argc, char **argv){

    int loop=0;
    pthread_t w_job;
    el_DataRead Data;

    printf("---------------------------------\n");
    pthread_create(&w_job, NULL, jobData, &Data);
    //pthread_join(w_job, (void**)&Data);
    printf("---------------------------------\n");

    while(loop!=3){
        printf("%d\n", loop);
        printf("Data->index:[%d]\n", Data.index);
        printf("Data->strN:[%s]\n", Data.strN);
        if(Data.index==20){printf("@#\n"); //loop=loop+1;}
        system("clear");
    }


 return 0;
}