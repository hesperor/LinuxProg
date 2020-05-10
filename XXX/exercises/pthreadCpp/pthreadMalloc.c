#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *hello_world(void *arg) {
    char *s = (char *) arg;
    printf("Hello %s!\n", s);

    int *result = malloc(sizeof(int));
    *result = 15;
    return result;
}

int main(int argc, char* argv[]) {
    pthread_t hello_world_thread;
    int result = pthread_create(&hello_world_thread, NULL, hello_world, (void *) argv[0]);
    if (result != 0) {
        perror("Could not create thread.");
    }

    int *hello_world_result;
    pthread_join(hello_world_thread, (void **) &hello_world_result);
    printf("Thread returned, %d.\n", *hello_world_result);

    return 0;
}