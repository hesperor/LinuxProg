#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define buff 20

typedef struct Dane{
        int index;
       char tab[buff];
}elDane;


void *funInOut(void *dane_){
    elDane *v_=(elDane*)dane_;
    elDane *current=(elDane*)malloc(sizeof(elDane));

    v_->index=666;
    strcpy(v_->tab, "Devil\0");
    current=v_;
 return current;
 }
//----------------------------------
void *funOut(void *dane_){
    
    elDane *v_=malloc(sizeof(elDane));
    v_->index=200;
    strcpy(v_->tab, "Bernz\0");   
 return v_;
 }
//----------------------------------
int main(int argc, char **argv){
    
 /* char *pc;
    char **pcc; */
    elDane *retVal;
    pthread_t w1,w2;
    
    pthread_create(&w1, NULL, funOut, NULL);
    pthread_join(w1, (void**) &retVal);

    printf("[%d]\n", retVal->index);
    printf("[%s]\n", retVal->tab);

    pthread_create(&w2, NULL, funInOut, (void*) retVal);
    pthread_join(w2, (void**) &retVal);
    

    printf("[%d]\n", retVal->index);
    printf("[%s]\n", retVal->tab);
    free(retVal);
    
/*
    pcc=retVal->tab;
    pc=pcc;
    
    while (*pc!=0)  {
        printf ( "%c ", *pc);
        pc+=1;
        }
    printf("\n");
*/

 return 0;
}
