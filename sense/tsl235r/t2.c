// gcc -o t2.o t2.c -lm -lrt -L/usr/local/lib -lwiringPi -lwiringPiDev -lpthread

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <wiringPi.h>

main()
{

  struct timespec tp1, tp2;
  long timp1, timp2, timp3;
  int i1,i2,x,y;
  int count;
  double s1,s2;
  
  wiringPiSetup () ;
  pinMode (7, INPUT) ;

  printf("Start\n");
  clock_gettime(CLOCK_REALTIME, &tp1);
  count=0;
   
   while ( count < 5 ) 
   {
     
     while ( digitalRead(7)== LOW )
     { 
     }
     count++;
      while ( digitalRead(7) == HIGH )
     {
     }
     count++;
    }
  clock_gettime(CLOCK_REALTIME, &tp2);
  s1 = tp2.tv_sec-tp1.tv_sec;
  s2 = tp2.tv_nsec-tp1.tv_nsec;


  
   printf(" t1 %lld \n",s1);
   printf(" t2 %lld \n",s2);
   
 
  printf(" R1  %lld %lld\n",tp1.tv_sec, tp1.tv_nsec);
  printf(" R2  %lld %lld\n",tp2.tv_sec, tp2.tv_nsec);
  
  printf(" Rez sec %lld\n",(long)(tp2.tv_sec-tp1.tv_sec));
  printf(" Rez nanosec %lld\n",(long)(tp2.tv_nsec-tp1.tv_nsec));
  printf("Stop\n");
  
}