/* MUTEX ::  https://docs.oracle.com/cd/E19455-01/806-5257/index.html           ::
         ::  https://pl.wikibooks.org/wiki/POSIX_Threads/Atrybuty_w%C4%85tku    ::
         :: https://www.geeksforgeeks.org/multithreading-c-2/                   ::
         :: https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html    ::
  
 Wątek typu joinable to taki, z którego można odczytać wartość wynikową zwróconą przez funkcję. 
 Gdy wątek tego typu kończy się, jego zasoby nie są zwalniane do chwili wywołania funkcji pthread_join 
 (patrz Oczekiwanie na zakończenie wątku).
 Warto więc zwrócić uwagę, że utworzenie wątku typu joinable i nie wywołanie wspomnianej funkcji skutkować 
 będzie wyciekiem pamięci (następstwem którego tworzenie nowych wątków może stać się niemożliwe).
 Wątek typu detached z chwilą zakończenia działania od razu zwalnia wszystkie zasoby; 
 funkcja pthread_join nie akceptuje identyfikatorów do wątków tego typu. 
-------------------------------------------------------------------------------------
 Wątek typu detached z chwilą zakończenia działania od razu zwalnia wszystkie zasoby; 
 funkcja pthread_join nie akceptuje identyfikatorów do wątków tego typu. 

Funkcje
    int pthread_detach(pthread_t id) 
        zmiana rodzaju wątku

    PTHREAD_CREATE_JOINABLE - utworzenie wątku typu joinable (domyślnie);
    PTHREAD_CREATE_DETACHED - utworzenie wątku typu detached.

Funkcje
    int pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate)
        ustawienie rodzaju

    int pthread_attr_getdetachstate(const pthread_attr_t *attr, int *detachstate)
        odczyt

EXAMPLE:|-->
  #include <pthread.h>

  pthread_attr_t tattr;
  pthread_t tid;
  void *start_routine;
  void arg
  int ret;

 // initialized with default attributes 
 ret = pthread_attr_init()(&tattr);
 ret = pthread_attr_setdetachstate()(&tattr,PTHREAD_CREATE_DETACHED);
 ret = pthread_create()(&tid, &tattr, start_routine, arg);                   
 <--|
------------------------------------------------------------------------------------

 pthread_attr_t atrybuty;

 pthread_attr_init(&atrybuty);
 // ... //
 pthread_attr_destroy(&atrybuty);

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

pthread_mutex_t latch=PTHREAD_MUTEX_INITIALIZER;
pthread_attr_t attr;

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
void *fundeatch(void *data){
    elVal *data_=(elVal*)data;
    char *str_= "Hello in fuction fundeatch\0";
    elVal *current=(elVal*)malloc(sizeof(elVal));

    
    data_->index=696;
    while (1){
    data_->index=data_->index+1;
    delay(200);
    if(data_->index==800){break;}
    }
    data_->str=str_;
    current=data_;

  return current;
 }
//--------------------------------
int main(int argc, char **arvc){

    int type_w;
    pthread_t w1;
    pthread_attr_init(&attr);
    pthread_mutex_init(&latch, NULL);

    elVal *area=(elVal*)malloc(sizeof(elVal));
    char *str_area="First Called out";

    area->index=2000000;               
    area->str=str_area;             

    fprintf(stdout, "#_int:[%d] #_std:[%s]\n", area->index, area->str);         
    fprintf(stdout, "-----------------------------------------------\n"); 
    delay(2000);    

    //int retattr = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);  // ustawiamy rodzaj watku
    //if (retattr){printf("Cod Error:[%d]\n", retattr);}

    int retval=pthread_create(&w1, NULL, fundeatch, (void*) area);             // stworzenie watku
    if(retval){printf("Error !\n");}

   // int ret = pthread_attr_getdetachstate(&attr, &type_w);                      // sprwadzenie rodaju watku
   // if (ret){printf("Cod Error:[%d]\n", ret);}


    int ret = pthread_attr_getdetachstate(&attr, &type_w); 
     switch(type_w) {
      case PTHREAD_CREATE_JOINABLE:
         printf("joinable\n"); // zrobic kopiowanie po adres wskaznika !!!
         delay(1000);
         break;
      case PTHREAD_CREATE_DETACHED:
         printf("detached\n");
         delay(1000);
         break;
      default:
         printf("pthread_attr_getdetachstate returned: %d\n", ret);
         exit(2);
  }   

    //fprintf(stdout, "int:[%d] std:[%s]\n", area->index, area->str);  

    //MAIN:
    while(1){
        int x;
        fprintf(stdout, "int:[%d] std:[%s] val:[%d]\n", area->index, area->str, x);
        x++;
        delay(200);
        system("clear");
        
    }
 return EXIT_SUCCESS;
}
