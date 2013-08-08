
// Author : Plescan Rares
// Use : Read TSL235R sensor connected to GPIO pin by measuring average time for a defined
// number of cycles. Output is calculated as kHz or according to docs, in uW/cm2 (illumination).
//
// 
//      gcc -o tsl_read tsl_read.c -lm -lrt -L/usr/local/lib -lwiringPi -lwiringPiDev
// Illumination measuring, command example :
//
//      tsl_read poll_time x_times
//
// where poll_time is the polling interval in uSeconds for the autorange procedure
// and the x_times is the number of itterations for the above polling 
// After all the itterations are done, an average is computed and printed as final output
// in a awk-friendly manner :
//
//      TSL235READ--poll_time--itterations--avg_value 300000 10 0.193
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


//const int tsl_pin = 7 ;
const int tsl_pin = 7 ; // GPIO04, pin 7

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

  pinMode (tsl_pin, OUTPUT) ;
// pin 26, GPIO07, wiring 11
  digitalWrite(11, HIGH);
//ping 22, GPIO 25, wiring 6
  digitalWrite(6, HIGH);


//  digitalWrite(tsl_pin, LOW);

 
}
