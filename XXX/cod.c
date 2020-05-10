/*
  https://www.reddit.com/r/C_Programming/comments/5hczva/integer_in_c_and_how_to_print_its_binary/

signed char a;      ///zmienna a przyjmuje wartości od -128 do 127 
unsigned char b;    // zmienna b przyjmuje wartości od 0 do 255    
unsigned short c;
unsigned long int d;
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


void binprintf(int v);
void byte1_2bin(uint8_t v);
void int2bin(int v);
void short2bin(short int v);
void long2bin(uint64_t v);
uint8_t IntNaChar(uint16_t liczba, uint8_t ktory_bajt);
uint16_t CharNaInt(uint8_t LByte, uint8_t HByte);

int main(int argc, char **argv){

 //uint8_t int8;
 //uint64_t int64;

    uint8_t int_b=0xF0;
    unsigned short int bit_s=0xFFF0;
    int bit_i =0xF0F0F0F0;
    uint64_t bit_l=0xF0F0F0F0F0F0F0F0;  //unsigned long int


    unsigned char znak='s';
    
   

    system("clear");
   // fprintf(stdout, "Val:[%#x]\n", bit);
   // fprintf(stdout, "Val:[%i]\n", znak);

    
    fprintf(stdout, "SiezInt:[%lu byte][short]\n", sizeof(bit_s));
    fprintf(stdout, "SiezInt:[%lu byte][int]\n", sizeof(bit_i));
    fprintf(stdout, "SiezInt:[%lu byte][long]\n", sizeof(bit_l));
    fprintf(stdout, "SiezInt:[%lu byte][char]\n", sizeof(znak));


    // printf("%04x", 4779); 
    // printf("%04X", 4779);

    printf("byte 1:");
    byte1_2bin(int_b);
    printf("\n");

    printf("short: ");
    short2bin(bit_s);
    printf("\n");

    printf("int:   ");
    int2bin(bit_i);
    printf("\n");

    printf("long:  ");
    long2bin(bit_l);
    printf("\n");

    printf("--------------------------------\n");

    uint8_t back_8 = IntNaChar(bit_s, 'H');
    byte1_2bin(back_8);printf("\n");
    back_8 = IntNaChar(bit_s, 'L');
    byte1_2bin(back_8);printf("\n");

    printf("--------------------------------\n");
   
  //  uint8_t test = 0x00;
    uint8_t tmp = 0x00;
/*
    byte1_2bin(test);
    printf("\n");
    byte1_2bin(test &= 0x02);
*/
    tmp |= 0 << 0;
    tmp |= 1 << 1;
    tmp |= 1 << 2;
    tmp |= 0 << 3;

    tmp |= 0 << 4;
    tmp |= 1 << 5;
    tmp |= 1 << 6;
    tmp |= 0 << 7;

    byte1_2bin(tmp);
    

    printf("\n");


    







  return(0);
}



void binprintf(int v){
    unsigned int mask=1<<((sizeof(int)<<3)-1);
    while(mask) {
        printf("%d", (v&mask ? 1 : 0));
        mask >>= 1;
    }
 }
void byte1_2bin(uint8_t v){
    uint8_t mask=1<<((sizeof(uint8_t)<<3)-1);  //unsigned int mask = 1 << sizeof (int) * CHAR_BIT - 1;
    while(mask) {
        printf("%d", (v&mask ? 1 : 0));
        mask >>= 1;
    }
 }
void int2bin(int v){
    unsigned int mask=1<<((sizeof(int)<<3)-1);  //unsigned int mask = 1 << sizeof (int) * CHAR_BIT - 1;
    while(mask) {
        printf("%d", (v&mask ? 1 : 0));
        mask >>= 1;
    }
 }
void short2bin(short int v){
    unsigned short int mask=1<<((sizeof(short int)<<3)-1);  //unsigned int mask = 1 << sizeof (int) * CHAR_BIT - 1;
    while(mask) {
        printf("%d", (v&mask ? 1 : 0));
        mask >>= 1;
    }
 }
 
void long2bin(uint64_t v){
 uint64_t mask=1UL<<((sizeof(uint64_t)<<3)-1);  //unsigned int mask = 1 << sizeof (int) * CHAR_BIT - 1;
    while(mask) {
        printf("%d", (v&mask ? 1 : 0));
        mask >>= 1;
    }
 }
uint8_t IntNaChar(uint16_t liczba, uint8_t ktory_bajt){
    if (ktory_bajt == 'L'){
        return (liczba & 0xFF);  //Zwracamy młodszy bajt
    }
    else if(ktory_bajt == 'H'){
        return (liczba >> 8);   //Zwracamy starszy bajt
    }
  return 1;
 }
uint16_t CharNaInt(uint8_t LByte, uint8_t HByte){
  return ((HByte << 8) + LByte);
 }