//
// Copyright June, 2013 Rares Plescan
// This is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License 
// as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// It is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of 
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//
// Reference :  http://www.gnu.org/licenses/.
//
//
//
// Author : Plescan Rares
// Use : Read TSL235R sensor connected to GPIO pin by measuring average time for a defined
// number of cycles. Output is calculated as kHz or according to docs, in uW/cm2 (illumination).
//
// 
//      gcc -o tsl_read tsl_read.c -lm -lrt -L/usr/local/lib -lwiringPi -lwiringPiDev -lpthread
// Illumination measuring, command example :
//
//      tsl_read poll_time x_times
//
// where poll_time is the polling interval in uSeconds for the autorange procedure
// and the x_times is the number of itterations for the above polling 
// After all the itterations are done, an average is computed and printed as final output
// in a awk-friendly manner :
//
//      READTSL235--poll_time--itterations--avg_value 300000 10 0.193
//
//  Warning : the command will take a little longer than poll_time*x_times/1000000 seconds
//  to complete. For a run as in the following example
//  ./tsl_read 300000 10
// is expected to take about 3 seconds plus some processing time.
//
//
//  Circuit diagram :  
//
//   


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

  long timp1, timp2, timp3;
  int poll_time,itterations;
  long double s2;
  float sum;
  float rb;
  float ra;
  float value[1000];
  int stat;
  unsigned int cycle1,it;
  unsigned int autoscale;

// init phase
  
  wiringPiSetup () ;
  pinMode (tsl_pin, INPUT) ;
  if ( argc>1 )
  {
  
  poll_time=atoi(argv[1]);
  itterations=atoi(argv[2]);
  }
  else
{
  poll_time=200000;
  itterations=10;
}
  autoscale=2;
  ra=1;
// autoscale till time is more than 300 ms then perform real readout
  while (ra<poll_time)
  {
  autoscale=autoscale*2;
  clock_gettime(CLOCK_REALTIME, &tp1);
  count_wait_tsl(autoscale);
  clock_gettime(CLOCK_REALTIME, &tp2);
  ra=time_diff(tp1,tp2)/1000;
 }

//end of autoscaling, now performing real readouts
  cycle1=autoscale;  
  sum=0;
   for (it=0;it<itterations;it++)
   {
    clock_gettime(CLOCK_REALTIME, &tp1);
    count_wait_tsl(cycle1);
    clock_gettime(CLOCK_REALTIME, &tp2);
    value[it]=(float)cycle1*(float)(1000000)/(float)time_diff(tp1,tp2);
    sum=sum+value[it];
//    printf(" %d : %.3f \n",value[it]);
   }

 printf("READTSL235--poll_time--itterations--avg_value %d %d %.3f\n",poll_time,itterations,sum/(float)itterations);

  
}
unsigned long int time_diff(struct timespec start, struct timespec stop)
{
 unsigned long int r1;
 
 r1 =(unsigned long int) ((stop.tv_sec - start.tv_sec)*1000000000 + stop.tv_nsec - start.tv_nsec );
 
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
