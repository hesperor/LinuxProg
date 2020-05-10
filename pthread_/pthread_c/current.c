/*MUTEX*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

pthread_mutex_t latch=PTHREAD_MUTEX_INITIALIZER;

typedef struct Vall{ 
    int index;
    char *str;
}elVal;

void delay(int number_of_seconds){  // Funkcja ralizujaca opuznienie
    
    int milli_seconds = 1000 * number_of_seconds;   // Converting time into milli_seconds   
    clock_t start_time = clock();                   // Stroing start time 

    while (clock() < start_time + milli_seconds)    // looping till required time is not acheived 
        ; 
 } 
//--------------------------------
void *ioOutF(void *data){           // Funkcja pobiera struct i zwraca struc
    
    int i;
    elVal *data_=(elVal*)data;
    elVal *current=(elVal*)malloc(sizeof(elVal));

    //pthread_detach(pthread_self());

    char *str_= "Second Called out\n";

    
    data_->str=str_;
    pthread_mutex_lock(&latch);
    for(i=0; i<1000000; i++){
        data_->index=data_->index-1;
    }
    pthread_mutex_unlock(&latch);
    //pthread_mutex_trylock(&latch);
    current=data_;

 return current;
 }
//--------------------------------
int main(int argc, char **arvc){

    
    pthread_t w1,w2;
    pthread_mutex_init(&latch, NULL);

    elVal *area=(elVal*)malloc(sizeof(elVal));
    char *str_area="First Called out";

    area->index=2000000;               
    area->str=str_area;             

    fprintf(stdout, "#_int:[%d] #_std:[%s]\n", area->index, area->str);         
    fprintf(stdout, "-----------------------------------------------\n"); 
    delay(2000);    

    int result = pthread_create(&w1, NULL, ioOutF, (void*) area);      // watek nr1         
    if(result){printf("Error int ioOut [w1] !\n");}

    int result_ = pthread_create(&w2, NULL, ioOutF, (void*) area);      // watek nr2          
    if(result_){printf("Error int ioOut [w2] !\n");}

   // pthread_join(w1, (void**) &area);
   // pthread_join(w2, (void**) &area);


    // MAIN:
    while(1){
        fprintf(stdout, "int:[%d] std:[%s]\n", area->index, area->str);  
        system("clear");
        
        //delay(500);
    }
    pthread_mutex_destroy(&latch);
 return 0;
}
