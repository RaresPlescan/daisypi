// gcc -o t2.o t2.c -lm -lrt -L/usr/local/lib -lwiringPi -lwiringPiDev -lpthread

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <wiringPi.h>


  struct timespec tp1, tp2;

unsigned long int time_diff(struct timespec start, struct timespec stop);
void count_wait_tsl(int cycles);

const int tsl_pin = 7 ;

main()
{

//  struct timespec tp1, tp2;
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




//actual readout - gettime/ loop untill "cycles" counts are met / gettime again and make diff

  clock_gettime(CLOCK_REALTIME, &tp1);
  count_wait_tsl(80000);
  clock_gettime(CLOCK_REALTIME, &tp2);

// here frequency should be computed and converted to uW/cm2 .  1khz = 1 uW/m2


//Just verification prints

  printf(" Rezultat %ld \n",time_diff(tp1,tp2));
  printf("Sec2 %d \n",tp2.tv_sec);
  printf("Sec1 %d \n",tp1.tv_sec);
  printf("NANO Sec2 %ld \n",tp2.tv_nsec);
  printf("NANO Sec1 %ld \n",tp1.tv_nsec);
  printf(" REZ  %ld \n",tp2.tv_nsec-tp1.tv_nsec+1000000000*(tp2.tv_sec-tp1.tv_sec));
 

  printf("Stop\n");
  
}
unsigned long int time_diff(struct timespec start, struct timespec stop)
{
 int d1;
 double d2,d3;
 long double rez;
 unsigned long int r1;
 
 d1 = 0;
 d1 = stop.tv_sec - start.tv_sec;
 d2 = stop.tv_nsec - start.tv_nsec;
 d3 = (double)d1 * 100000000 ;
 d3 = d3 + d2 ;
 rez = (((long double)stop.tv_sec - (long double)start.tv_sec)*1000000000 + stop.tv_nsec - start.tv_nsec );
 r1 =(unsigned long int) ((stop.tv_sec - start.tv_sec)*1000000000 + stop.tv_nsec - start.tv_nsec );
 
 printf(" D1 %d \n",d1);
 printf(" D2 %ld \n",d2);
 printf(" D3 %ld \n",d3);
 printf("NANO Sec2 %ld \n",stop.tv_nsec);
 printf("NANO Sec1 %ld \n",start.tv_nsec);
 printf(" Rez  %ld \n",rez);
 printf(" R1  %ld \n",r1);
 
// return d3;
 return r1;
 
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