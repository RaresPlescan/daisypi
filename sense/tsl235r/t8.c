
// Author : Plescan Rares
// gcc -o tsl_read tsl_read.c -lm -lrt -L/usr/local/lib -lwiringPi -lwiringPiDev -lpthread
// power of ligt
// tsl_read poll_time x_times
// where poll_time is the polling interval in uSeconds for the autorange procedure
// and the x_times is the number of itterations for the above polling 
// After all the itterations are done, an average is computed and printed as final output
//
//  Warning : the command will take a little longer than poll_time*x_times/1000000 seconds
//  to complete. For a run as in the following example
//  ./tsl_read 300000 10
// is expected to take about 3 seconds plus some processing time.

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
  unsigned int autoscale;

  
  wiringPiSetup () ;
  pinMode (tsl_pin, INPUT) ;
  cycle1=atoi(argv[1]);

  printf("Start\n");




//actual readout - gettime/ loop untill "cycles" counts are met / gettime again and make diff
  autoscale=2;
  ra=1;
// autoscale till time is more than 300 ms then perform real readout
  while (ra<300000)
  {
  autoscale=autoscale*2;
  clock_gettime(CLOCK_REALTIME, &tp1);
  count_wait_tsl(autoscale);
  clock_gettime(CLOCK_REALTIME, &tp2);
  ra=time_diff(tp1,tp2)/1000;

 }

  cycle1=autoscale;  
// normal read
  clock_gettime(CLOCK_REALTIME, &tp1);
  count_wait_tsl(cycle1);
  clock_gettime(CLOCK_REALTIME, &tp2);


  printf(" Rezultat %ld \n",time_diff(tp1,tp2));
  printf("Sec2 %d \n",tp2.tv_sec);
  printf("Sec1 %d \n",tp1.tv_sec);
  printf("NANO Sec2 %ld \n",tp2.tv_nsec);
  printf("NANO Sec1 %ld \n",tp1.tv_nsec);
  printf(" REZ  %ld \n",tp2.tv_nsec-tp1.tv_nsec+1000000000*(tp2.tv_sec-tp1.tv_sec));
 

// here frequency should be computed and converted to uW/cm2 .  1khz = 1 uW/m2
//  ra=time_diff(tp1,tp2)/1000;
//  rb=cycle1*500/(float)ra;

  printf("(-)Cycles = %d \n",cycle1);
  printf("(-)Frequency is : %.9f \n",(float)time_diff(tp1,tp2)/((float)cycle1*(float)1000));
  printf("(-)Power is     : %.9f uW/cm2\n",(float)cycle1*(float)(1000000)/(float)time_diff(tp1,tp2));

  printf("(0)Cycles = %d \n",cycle1);
  printf("(0)Frequency is : %.9f \n",time_diff(tp1,tp2)/(cycle1*1000));   
  printf("(0)Power is     : %.9f uW/cm2\n",cycle1*1000000/time_diff(tp1,tp2));   

  cycle1=autoscale;

//----------------------------

//actual readout - gettime/ loop untill "cycles" counts are met / gettime again and make diff
//  cycle1=cycle1*2;

  clock_gettime(CLOCK_REALTIME, &tp1);
  count_wait_tsl(cycle1);
  clock_gettime(CLOCK_REALTIME, &tp2);
  

// here frequency should be computed and converted to uW/cm2 .  1khz = 1 uW/m2
  ra=time_diff(tp1,tp2)/1000;
  rb=cycle1*500/ra;
//  printf("(2)Cycles = %d \n",cycle1);
//  printf("(2)Frequency is : %.3f ms/cycle %.3f  \n",ra,cycle1);   
//  printf("(2)Power is     : %.3f uW/cm2\n",rb*1000);   

  printf("(2)Cycles = %d \n",cycle1);
  printf("(2)Frequency is : %.9f \n",(float)time_diff(tp1,tp2)/((float)cycle1*(float)1000));
  printf("(2)Power is     : %.9f uW/cm2\n",(float)cycle1*(float)(1000000)/(float)time_diff(tp1,tp2));
 
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