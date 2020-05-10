#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>

#define test_errno(msg) do{if (errno) {perror(msg); exit(EXIT_FAILURE);}} while(0)

typedef struct _Arg {	// struktura argumentów dla wątku 1.
	char	napis[256];
	int	rok;
	int	mies;
	int	dzien;
} Argument;

void* watek1(void* _arg) {
	Argument* arg = (Argument*)_arg;

	printf("Witaj %s w dniu %04d-%02d-%02d\n",
		arg->napis,
		arg->rok,
		arg->mies,
		arg->dzien
	);

	return NULL;
 }
/* wątek 2. zwraca pewien dynamicznie tworzony napis */
void* watek2(void* liczba) {
	char* napis;
	int i;
	printf("Wątek 2 wywołany z argumentem liczbowym %d\n", (int)liczba);

	napis = malloc((int)liczba + 1);
	if (napis) {
		for (i=0; i < (int)liczba; i++)
			napis[i] = 'x';

		napis[(int)liczba] = 0;
	}
	return napis;
 }
//------------------------------------------------------------------------

int main() {
	pthread_t w1, w2;
	Argument arg;
	char* wynik;

	/* przygotowanie argumentów */
	strcpy(arg.napis, "Wikibooks");
	arg.rok   = 2010;
	arg.mies  = 3;
	arg.dzien = 14;

	/* utworzenie dwóch wątków */
	errno = pthread_create(&w1, NULL, watek1, &arg);
	test_errno("pthread_create");

	errno = pthread_create(&w2, NULL, watek2, (void*)27);
	test_errno("pthread_create");

	/* oczekiwanie na zakończenie obu */
	errno = pthread_join(w1, NULL);
	test_errno("pthread_join");

	errno = pthread_join(w2, (void**)&wynik);
	test_errno("pthread_join");

	if (wynik) {
		printf("wątek 2 zwrócił napis: '%s'\n", wynik);
		free(wynik);
	}
	else
		puts("wątek 2 nic nie zwrócił");

	return EXIT_SUCCESS;
}