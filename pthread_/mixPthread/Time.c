#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/*
size_t      //This is the unsigned integral type and is the result of the sizeof keyword.
clock_t     //This is a type suitable for storing the processor time.	
time_t is   //This is a type suitable for storing the calendar time.	
struct tm   //This is a structure used to hold the time and date.

struct tm {
   int tm_sec;         // seconds,  range 0 to 59          
   int tm_min;         // minutes, range 0 to 59           
   int tm_hour;        // hours, range 0 to 23             
   int tm_mday;        // day of the month, range 1 to 31  
   int tm_mon;         // month, range 0 to 11             
   int tm_year;        // The number of years since 1900   
   int tm_wday;        // day of the week, range 0 to 6    
   int tm_yday;        // day in the year, range 0 to 365  
   int tm_isdst;       // daylight saving time             
};
*/


// C program to demonstrate 
// example of localtime() function. 
  
#include <stdio.h> 
#include <time.h> 
  
int main() 
{ 
  
    struct tm* local; 
    time_t t = time(NULL); 
  
    // Get the localtime 
    local = localtime(&t); 
  
    printf("Local time and date: %s\n", 
           asctime(local)); 
  
    return 0; 
} 