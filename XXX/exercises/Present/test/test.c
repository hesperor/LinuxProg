#include <stdio.h>
#include <stdlib.h>

    int source;
    char* tgt;
//    tgt = (char*)&source;


    union {
      int source;
      char tgt[sizeof(int)];
    } converter;

int main(int arg, char **argc){

        converter.source = 100;
        converter.tgt[0] = 100;

	printf("INT:[%d] CHAR:[%c]\n", converter.source, converter.tgt[0]);

 return (0);
}
