#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/*

https://pl.wikibooks.org/wiki/C/Wska%C5%BAniki_-_wi%C4%99cej

int rozmiar, i;
 printf("Podaj rozmiar tabliczki mnozenia: ");
 scanf("%d", &rozmiar);
 int **tabliczka = (int **)malloc(rozmiar * sizeof (*tabliczka));   // 1 
 for(i=0; i<rozmiar; ++i)                                           // 2 
 {
    tabliczka[i]= (int *)malloc(rozmiar * sizeof (**tabliczka));
 }

 // tutaj można zainicjować tabliczkę mnożenia 
 // i operować na niej. Gdy już wykonamy wszystkie czynności.. 
 
 for(i=0; i<rozmiar; ++i)                                           // 3 
    free(tabliczka[i]);
 free(tabliczka);                                                   // 4 
 tabliczka = NULL;

*/

// https://pl.wikibooks.org/wiki/C/Napisy
// https://www.geeksforgeeks.org/storage-for-strings-in-c/
// https://www.geeksforgeeks.org/swap-strings-in-c/
// https://kmim.wm.pwr.edu.pl/myszka/dydaktyka/informatyka-i/materialy-pomocnicze/jezyk-c-dynamiczne-tablice-dwuwymiarowe-i-funkcje/

typedef struct xx{
    int index;
    char *opis;
} el_xx;

uint16_t valString(char *tab);
uint16_t valInt(int *tab);



char *ind="1234567890ABCD";
char str[]="1234567890";
int indexC[]={1,2,3,4,5,6,7,8,9,0};
int i,j,x=0, row=0;

int main(int argc, char **argv){

    // int **wsk_=(int**)calloc(1, sizeof(*wsk_));
    // *(wsk_+1)=(int*)calloc(1, sizeof(**wsk_)); //wsk_[i]

    fprintf(stdout, "How meny row:\n");
    scanf("%d", &row);
    fprintf(stdout, "Rows are [%d]\n", row);

    int **tab=(int**)calloc(row, sizeof(*tab));  // Declaring the indicators tables
    for(i=0; i<=row; i++) {
        *(tab+i)=(int*)calloc(row, sizeof(**tab)); // Saving addres indicators tables tab[i]=*(tab+i) tab[i][j]=*(*(tab+i)+j)
    }
    for(i=0; i<row; i++)
        for(j=0; j<row; j++)
            *(*(tab+i)+j)=x++;
  

    for(i=0; i<row; i++)
        for(j=0; j<row; j++)
            printf("tab[%d][%d]:%d\n", i, j, *(*(tab+i)+j));

    for(i=0; i<row; ++i){
       free(*(tab+i));
    }
    //free(tab);
    //tab==NULL;
  
   



/*
  int *pc=indexC;
//char **pcc=pc;

    for (i=0; i<14; i++) {
     printf("(%i) Addres[%p] Value[%c]\n", i, ind, *ind);
       ind+=1;  
    }
    
    for(i=0; i<10; i++) {
       printf("(%d) Addres[%p] Value[%d]\n", i, pc, *pc); //pc[i]
       pc+=1;
       //pc++;
      
    } */




    // fprintf(stdout, "**[%p]\n", wsk_);

    return(0);
}

uint16_t valString(char *tab) {
    uint16_t size_;
    return size_=strlen(tab)/sizeof(char);
}
uint16_t valInt(int *tab) {
    uint16_t size_;
    return size_=sizeof(tab)/sizeof(int);
}