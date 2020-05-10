#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct Plc{
    int index;
    char *znak;
}elPlc;

void *funx(void *data){
    int *data_=(int*)data;
    int *ret;

    while(1){
        fprintf(stdout, "Val:[%d]", *(data_));
        data_++;
        ret=data_;
        // return ret;
    }
    return ret;
 }
void *funy(void *data){
    int *data_=(int*)data;
    int tem=30;

    while(1){
        fprintf(stdout, "Val:[%d]", tem);
        tem++;
        data_=&tem;
        // return data_;
    }
 return data_;
 }
//---------------------------


int main(int argc, char **argv){
    pthread_t IdFw;
    int status,i=200000;
    //void *retvL;
    int *x;
    int x_=600000;
    x=&x_;

    status=pthread_create(&IdFw, NULL, funy, (void*) x);
    if(status){printf("error ! \n"); exit(0);}

    while(1){
        i++;
        printf("[%d] FUN:[%d]\n", i, *(x));

    }
 return 0;
}