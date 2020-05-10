#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>

int counter=2000000;
pthread_mutex_t syntax=PTHREAD_MUTEX_INITIALIZER;

void ms_sleep(unsigned ms){
    struct timespec reg;
    reg.tv_sec = (ms / 1000);
    reg.tv_nsec = (ms%1000*1000000);
    nanosleep(&reg, NULL);
 }
//------------------------------
void * funError(void *x){
    int i;
    pthread_mutex_lock(&syntax);
    for(i=0; i<1000000; i++){
        counter=counter-1;
    }
    pthread_mutex_unlock(&syntax);
 return(0);
 }
//------------------------------


int main(int argc, char **argv){

    pthread_t id0, id1;
    int i;

    pthread_create(&id0, NULL, funError, NULL);
    pthread_create(&id1, NULL, funError, NULL);

    void *result;
    pthread_join(id0, &result);
    pthread_join(id1, &result);

    for(i=0; i<10000; i++){
        printf("%d\n", i);
        ms_sleep(1000);
    }

    printf("#:[%d]\n", counter);

 return(0);
}