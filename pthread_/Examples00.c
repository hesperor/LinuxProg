#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <errno.h>

pthread_attr_t attr;

typedef struct Data{
    int index;
    int exe;
    char *znak0;
    char *znak1;
}elData;


void delay(int number_of_seconds){ 
    
    int milli_seconds = 1000 * number_of_seconds;   // Converting time into milli_seconds   
    clock_t start_time = clock();                   // Stroing start time 

    while (clock() < start_time + milli_seconds)    // looping till required time is not acheived 
        ; 
 }
void* fun0(void* data){
    elData *data_=(elData*)data;
    //elData *tem = (elData*)malloc(sizeof(elData));
    int i = data_->index;

    pthread_detach(pthread_self());

    while(1){
        printf("\x1B[36m [%d] fun_nr0:[%d]\n", i, data_->index);
        i++;
        delay(100);
    }
 pthread_exit(NULL);			
 }
void* fun1(void* data){
    elData *data_=(elData*)data;
    //elData *tem=(elData*)malloc(sizeof(elData));   
    int j=data_->exe;

    pthread_detach(pthread_self());

    while(1){
        printf("\x1B[35m [%d] Fun_nr1:[%d]\n", j, data_->exe);
        j++;
        delay(100);
    }
 pthread_exit(NULL);			
 }

void *funTest(void *dx){
    int i;
    elData *dx_=(elData*)dx;
    elData *returnData=(elData*)malloc(sizeof(elData));


    dx_->index=2019;
    dx_->znak0=":)\0";
    dx_->znak1=":(\0";
    returnData=dx;
    for (i=0; i<1000; i++){
        printf("[%d]", i);
    }


    return(returnData);
 }
//-------------------------------------------------------

int main (int argc, char **argv){

    int type_w;
    int x,index_m=1000,exe_m=2000;
    char *znak_0="fun_0";
    char *znak_1="fun_1";
    //void *result;

    pthread_attr_init(&attr);
    pthread_t id0,id1;
    elData *current=(elData*)malloc(sizeof(elData));
    


    fprintf(stdout, "Przypisanie wartosci w main\n");
    current->exe=exe_m;
    current->index=index_m;
    current->znak0=znak_0;
    current->znak1=znak_1;

  
    
 

    int retattr = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE); //PTHREAD_CREATE_DETACHED)
    if (retattr){printf("Cod Error:[%d]\n", retattr);}

    int result_id0 = pthread_create(&id0, &attr, fun0, (void*)current);
    if(result_id0){fprintf(stderr, "Error id0\n"); return EXIT_FAILURE;}

    int result_id1 = pthread_create(&id1, NULL, fun1, (void*)current);
    if(result_id1){fprintf(stderr, "error id1\n"); return EXIT_FAILURE;}
       
    //pthread_join(id0, &result); //pthread_join(w1, (void**) &current);
    //pthread_join(id1, &result);

    //pthread_join(id0, NULL);
    //pthread_join(id1, NULL);

   int ret = pthread_attr_getdetachstate(&attr, &type_w);                      
   if (ret){printf("Cod Error:[%d]\n", ret);}

while(1){
    int ret_ = pthread_attr_getdetachstate(&attr, &type_w); 
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
      //--> 
        fprintf(stdout, "[%d]\n", x);
        x++;
        delay(100);

        fprintf(stdout, "dane z main: [%d | %d]\n", current->exe, current->index);
        system("@cls||clear"); //system("clear");
    }

    return EXIT_SUCCESS;
}
