/*
To, czy obiekt synchronizujący będzie współdzielony decydują jego atrybuty - ustawiane funkcjami 
int pthread_XXXattr_setpshared(pthread_XXXattr_t *attr, int shared) (XXX=mutex, cond, rwlock, barrier), 
gdzie parametr shared przyjmuje wartości:

PTHREAD_PROCESS_PRIVATE (domyślnie) - obiekt prywatny;
PTHREAD_PROCESS_SHARED - współdzielony.
Przykład
Przykładowy program w zależności od argumentów:

Tworzy segment pamięci dzielonej, podłącza go do przestrzeni adresowej procesu, w którego obszarze 
inicjalizuje mutex i zmienną warunkową na współdzielone (PTHREAD_PROCESS_SHARED) i oczekuje na warunek - ustawienie napisu.
Podłącza się do już utworzonego segmentu pamięci, ustawia napis i sygnalizuje zmienną warunkową ten fakt.
*/

#define _XOPEN_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/shm.h>

#include <errno.h>
#include <unistd.h>

#define test_errno(msg) do{if (errno) {perror(msg); exit(EXIT_FAILURE);}} while(0)

struct pamiec_dzielona {
	/* współdzielone mutex i zmienna warunkowa */
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
    pthread_mutexattr_t	mattr;
	pthread_condattr_t	cattr;

	/* dane */
	char napis_dostepny;
	char napis[256];
} *pamiec;


/* proces 1 tworzy segment pamięci wspólnej, tworzy mutex i zmienną warunkową WSPÓŁDZIELONE
   z innymi procesami, po czym oczekuje na sygnał, aż napis stanie się dostępny */
void proces1() {
	int shmid;
	int errno;

	shmid = shmget(IPC_PRIVATE, sizeof(struct pamiec_dzielona), 0666);
	test_errno("shm_open");
	printf("id segmentu pamięci dzielonej: %d\n", shmid);

	pamiec = shmat(shmid, 0, 0);
	test_errno("shmat");
	printf("adres przyłączonego segmentu: %p\n", (void*)pamiec);

	/* inicjalizacja */
	pamiec->napis_dostepny	= 0;
	memset(pamiec->napis, 0, sizeof(pamiec->napis));

	/* tworzenie mutexu i zmiennej warunkowej */
	errno = pthread_mutexattr_init(&pamiec->mattr);
	test_errno("pthread_mutexattr_init");

	errno = pthread_mutexattr_setpshared(&pamiec->mattr, PTHREAD_PROCESS_SHARED);
	test_errno("pthread_mutexattr_setpshared");

	errno = pthread_mutex_init(&pamiec->mutex, &pamiec->mattr);
	test_errno("pthread_mutex_init");

	/* tworzenie mutexu i zmiennej warunkowej */
	errno = pthread_condattr_init(&pamiec->cattr);
	test_errno("pthread_condattr_init");

	errno = pthread_condattr_setpshared(&pamiec->cattr, PTHREAD_PROCESS_SHARED);
	test_errno("pthread_condattr_setpshared");

	errno = pthread_cond_init(&pamiec->cond, &pamiec->cattr);
	test_errno("pthread_cond_init");

	/* oczekiwanie na ustawienie napisu przez inny proces */
	errno = pthread_mutex_lock(&pamiec->mutex);
	test_errno("pthread_mutex_lock");
	do {
		if (pamiec->napis_dostepny) {
			printf("inny proces ustawił napis: '%s'\n", pamiec->napis);
			break;
		}
		else {
			puts("pthread_cond_wait");
			errno = pthread_cond_wait(&pamiec->cond, &pamiec->mutex);
			test_errno("pthread_cond_wait");
		}
	} while (1);

	errno = pthread_mutex_unlock(&pamiec->mutex);
	test_errno("pthread_mutex_unlock");

	/* odłączenie od segmentu pamięci */
	shmdt(pamiec);
	test_errno("shmdt");

	/* i skasowanie go */
	shmctl(shmid, IPC_RMID, NULL);

	return;
}
//------------------------------------------------------------------------

/* proces 2 przyłącza się do segmentu i używając współdzielonego mutexu i zmiennej
   warunkowej ustawia napis i sygnalizuje go procesowi 1 funkcją pthread_cond_signal */
void proces2(int shmid, const char* napis) {
	int errno;

	pamiec = shmat(shmid, 0, 0);
	test_errno("shmat");
	printf("adres przyłączonego segmentu: %p\n", (void*)pamiec);

	errno = pthread_mutex_lock(&pamiec->mutex);
	test_errno("pthread_mutex_lock");

	strcat(pamiec->napis, napis);	// uwaga: możliwe przepełnienie bufora
	pamiec->napis_dostepny = 1;

	errno = pthread_cond_signal(&pamiec->cond);
	test_errno("pthread_cond_signal");

	errno = pthread_mutex_unlock(&pamiec->mutex);
	test_errno("pthread_mutex_unlock");

	printf("proces ustawił napis '%s' i wykonał pthread_cond_signal\n", napis);

	shmdt(pamiec);
	test_errno("shmdt");
}
//------------------------------------------------------------------------

int main(int argc, char* argv[]) {
	if (argc > 2) {
		printf("proces 2: segment pamięci dzielonej %d\n", atoi(argv[1]));
		proces2(atoi(argv[1]), argv[2]);
	}
	else {
		puts("proces 1");
		proces1();
	}

	return EXIT_SUCCESS;
}
//------------------------------------------------------------------------