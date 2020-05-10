/*http://www.cs.put.poznan.pl/ksiek/sk2/pthreads.html
-----------------------------------------------------------------------
 Utworzenie wątku

    int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);

        pthread_t *thread: wskaźnik do wątku
        pthread_attr_t *attr: parametry wątku
        *(*start_routine) (void *): wskaźnik na funkcję wykonywaną przez wątek, funkcja ta musi przyjmować 1 argument typu ``void * i zwracać wynik typu void *
        void *arg argument przekazywany funkcji start_routine
        zwraca 0 w wypadku poprawnego wykonania lub kod błędu
 -----------------------------------------------------------------------
 Oczekiwanie na zamknięcie wątku:

    int pthread_join(pthread_t thread, void **retval);

        pthread_t thread: wątek na który czekamy (nie wskaźnik)
        void **retval: wartość zwracana przez wątek
        zwraca 0 w wypadku poprawnego wykonania lub kod błędu
 -----------------------------------------------------------------------



 */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *hello_world(void *arg) {
    int x=0;
    char *s = (char *) arg;
    printf("Hello %s!\n", s);
    //-->
    for(;;){
        printf("#: %d\n", x);
        sleep(1);
        x++;
    }
    //-->
    return 0;
}

int main(int argc, char* argv[]) {
    pthread_t hello_world_thread;
    int result = pthread_create(&hello_world_thread, NULL, hello_world, (void *) argv[0]);
    if (result != 0) {
        perror("Could not create thread.");
    }
    //-->
    //pthread_join(hello_world_thread, NULL); //oczekiwanie na zmkniecie watku
    printf("Main thread exiting.\n");
    //getchar();
    //-->

  int y=0;
    for(;;){
        printf("@: %d\n", y);
        y++;
        sleep(1);
        //if (y==10000){return(0);}
    }

    return 0;
}




