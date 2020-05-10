/*
#define _OPEN_THREADS                                                           
#include <stdio.h>                                                              
#include <pthread.h>                                                            
                                                                                
int main()                                                                      
{                                                                               
   pthread_attr_t attr;                                                         
   char           typ[12];                                                      
                                                                                
   if (pthread_attr_init(&attr) == -1) {                                        
      perror("error in pthread_attr_init");                                     
      exit(1);                                                                  
   }                                                                            
                                                                                
   switch(pthread_attr_getdetachstate(&attr)) {                                 
      default:                                                                  
         perror("error in pthread_attr_getdetachstate()");                      
         exit(2);                                                               
      case 0:                                                                   
         strcpy(typ, "undetached");                                             
         break;                                                                 
      case 1:                                                                   
         strcpy(typ, "detached");                                               
   }                                                                            
   printf("The detach state is %s.\n", typ);                                    
                                                                                
   if (pthread_attr_destroy(&attr) == -1) {                                     
      perror("error in pthread_attr_destroy");                                  
      exit(2);                                                                  
   }                                                                            
   exit(0);                                                                     
} 
*/         
//-----------------------------------------------------------------------------
/*
#define _UNIX03_THREADS 1                                                          
#include <stdio.h>                                                              
#include <stdlib.h>
#include <string.h>
#include <pthread.h>                                                            
#include <errno.h>                                                            

                                                                                
int main(void)                                                                      
{                                                                               
  pthread_attr_t attr;                                                         
  int            rc, newstate, foundstate; 
  char           state[12];
                                                                                
  if (pthread_attr_init(&attr) == -1) {                                        
     perror("error in pthread_attr_init");                                     
     exit(1);                                                                  
  }                                                                            

  newstate = PTHREAD_CREATE_DETACHED; 
  pthread_attr_setdetachstate(&attr, newstate);
                                                                                
  rc = pthread_attr_getdetachstate(&attr,&foundstate);
  switch(foundstate) {
      case PTHREAD_CREATE_JOINABLE:
         strcpy(state,"joinable");
         break;
      case PTHREAD_CREATE_DETACHED:
         strcpy(state,"detached");
         break;
      default:
         printf("pthread_attr_getdetachstate returned: %d\n", rc); 
         printf("Error: %d, Errno_Jr: %08x\n", errno, __errno2());
         exit(2);
  }   

  printf("Threads created with this attribute object are %s.\n",state);

  if (pthread_attr_destroy(&attr) == -1) {                                     
     perror("error in pthread_attr_destroy");                                  
     exit(3);                                                                  
  }                                                                            

  exit(0);                                                                     
}      
*/
