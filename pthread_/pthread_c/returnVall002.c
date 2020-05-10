/*
 http://www.cs.put.poznan.pl/ksiek/sk2/pthreads.html
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>


#define buff 10

typedef struct Data{
    int index;
    char tabS[buff];
}el_Data;

void *in_out(void* arg){
    el_Data *arg_= (el_Data*)arg;
    el_Data *current=(el_Data*)malloc(sizeof(el_Data));

    printf("fun->index:[%d]\n", arg_->index);
    printf("fun->tabS:[%s]\n", arg_->tabS);
    
    arg_->index=100;
    strcpy(arg_->tabS, "Bernz(r)\0");
    current=arg_;
 return current; 
 }
//-----------------------------------------
int main(int argc, char* argv[]) {

    pthread_t w1;
    el_Data *sData=(el_Data*)malloc(sizeof(el_Data));

    sData->index=696;
    strcpy(sData->tabS, "xxxx");


    int result = pthread_create(&w1, NULL, in_out, (void *) sData);
    if (result != 0) {perror("Could not create thread.");}

    pthread_join(w1, (void**) &sData);
    printf("index:[%d]\n", sData->index);
    printf("tabS:[%s]\n", sData->tabS);

    return 0;
}