// gcc -o t2.o t2.c -lm -lrt -L/usr/local/lib -lwiringPi -lwiringPiDev -lpthread

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <wiringPi.h>

double time_diff(struct timespec start, struct timespec stop);
void count_wait_tsl(int cycles);

const int tsl_pin = 7 ;

main()
{

  struct timespec tp1, tp2;
  long timp1, timp2, timp3;
  int i1,i2,x,y;
  int s1;
  long double s2;
  long double accum;
  long double accum1;
  struct timespec     clock_resolution;
  int stat;

  
  wiringPiSetup () ;
  pinMode (tsl_pin, INPUT) ;



  printf("Start\n");
  stat = clock_getres(CLOCK_REALTIME, &clock_resolution);
   printf("Clock resolution is %d seconds, %ld nanoseconds\n", clock_resolution.tv_sec, clock_resolution.tv_nsec);



  clock_gettime(CLOCK_REALTIME, &tp1);
  count_wait_tsl(20000);
  clock_gettime(CLOCK_REALTIME, &tp2);

  printf(" Rezultat %ld \n",time_diff(tp1,tp2));
  printf("Sec2 %d \n",tp2.tv_sec);
  printf("Sec1 %d \n",tp1.tv_sec);
  printf("NANO Sec2 %ld \n",tp2.tv_nsec);
  printf("NANO Sec1 %ld \n",tp1.tv_nsec);

 

  printf("Stop\n");
  
}
double time_diff(struct timespec start, struct timespec stop)
{
 int d1;
 double d2,d3;
 
 d1 = stop.tv_sec - start.tv_sec;
 d2 = ( stop.tv_nsec - start.tv_nsec)/1000000;
 d3 = d1*1000;
 d3 = d3 + d2 ;

 printf(" D1 %d \n",d1);
 printf(" D2 %ld \n",d2);
 printf(" D3 %ld \n",d3);
 
 return d3;
 
}
void count_wait_tsl(int cycles)
{
  int count;
  count=0;

   while ( count < cycles ) 
   {
     
     while ( digitalRead(tsl_pin) == LOW )
     { 
     }
     count++;
      while ( digitalRead(tsl_pin) == HIGH )
     {
     }
     count++;
    }
}