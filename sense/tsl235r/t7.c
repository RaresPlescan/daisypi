// gcc -o t2.o t2.c -lm -lrt -L/usr/local/lib -lwiringPi -lwiringPiDev -lpthread

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <wiringPi.h>


  struct timespec tp1, tp2;

unsigned long int time_diff(struct timespec start, struct timespec stop);
void count_wait_tsl(unsigned int cycles);

const int tsl_pin = 7 ;

void main(int argc, char* argv[])
{

//  struct timespec tp1, tp2;
  long timp1, timp2, timp3;
  int i1,i2,x,y;
  int s1;
  long double s2;
  long double accum;
  long double accum1;
  float rb;
  float ra;
  struct timespec     clock_resolution;
  int stat;
  unsigned int cycle1;

  
  wiringPiSetup () ;
  pinMode (tsl_pin, INPUT) ;
  cycle1=atoi(argv[1]);

  printf("Start\n");
  printf("(1)Cycles = %d \n",cycle1);




//actual readout - gettime/ loop untill "cycles" counts are met / gettime again and make diff

  clock_gettime(CLOCK_REALTIME, &tp1);
  count_wait_tsl(cycle1);
  clock_gettime(CLOCK_REALTIME, &tp2);
  

// here frequency should be computed and converted to uW/cm2 .  1khz = 1 uW/m2
  ra=time_diff(tp1,tp2)/1000;
  rb=cycle1*500/ra;
  printf("(1)Frequency is : %.3f \n",ra);   
  printf("(1)Power is     : %.3f uW/cm2\n",rb*1000);   
 
//Just verification prints

//  printf(" Rezultat %ld \n",time_diff(tp1,tp2));
//  printf("Sec2 %d \n",tp2.tv_sec);
//  printf("Sec1 %d \n",tp1.tv_sec);
//  printf("NANO Sec2 %ld \n",tp2.tv_nsec);
//  printf("NANO Sec1 %ld \n",tp1.tv_nsec);
//  printf(" REZ  %ld \n",tp2.tv_nsec-tp1.tv_nsec+1000000000*(tp2.tv_sec-tp1.tv_sec));
 
//----------------------------

//actual readout - gettime/ loop untill "cycles" counts are met / gettime again and make diff
  cycle1=cycle1*2;

  clock_gettime(CLOCK_REALTIME, &tp1);
  count_wait_tsl(cycle1);
  clock_gettime(CLOCK_REALTIME, &tp2);
  

// here frequency should be computed and converted to uW/cm2 .  1khz = 1 uW/m2
  ra=time_diff(tp1,tp2)/1000;
  rb=cycle1*500/ra;
  printf("(2)Cycles = %d \n",cycle1);
  printf("(2)Frequency is : %.3f ms/cycle %.3f  \n",ra,cycle1);   
  printf("(2)Power is     : %.3f uW/cm2\n",rb*1000);   
 
//Just verification prints

//  printf(" Rezultat %ld \n",time_diff(tp1,tp2));
//  printf("Sec2 %d \n",tp2.tv_sec);
//  printf("Sec1 %d \n",tp1.tv_sec);
//  printf("NANO Sec2 %ld \n",tp2.tv_nsec);
//  printf("NANO Sec1 %ld \n",tp1.tv_nsec);
//  printf(" REZ  %ld \n",tp2.tv_nsec-tp1.tv_nsec+1000000000*(tp2.tv_sec-tp1.tv_sec));



  printf("Stop\n");
  
}
unsigned long int time_diff(struct timespec start, struct timespec stop)
{
 unsigned long int r1;
 
 r1 =(unsigned long int) ((stop.tv_sec - start.tv_sec)*1000000000 + stop.tv_nsec - start.tv_nsec );
 
// printf(" R1  %ld \n",r1);
 return r1;
 
}
void count_wait_tsl(unsigned int cycles)
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