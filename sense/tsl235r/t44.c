// gcc -o t2.o t2.c -lm -lrt -L/usr/local/lib -lwiringPi -lwiringPiDev -lpthread

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <wiringPi.h>

#define BILLION  1000000000L;

long double time_diff(struct timespec tp1, struct timespec tp2);

main()
{

  struct timespec tp1, tp2;
  long timp1, timp2, timp3;
  int i1,i2,x,y;
  int count;
  int s1;
  long double s2;
  long double accum;
  long double accum1;
  struct timespec     clock_resolution;
  int stat;

  
  wiringPiSetup () ;
  pinMode (7, INPUT) ;



  printf("Start\n");
  stat = clock_getres(CLOCK_REALTIME, &clock_resolution);
   printf("Clock resolution is %d seconds, %ld nanoseconds\n", clock_resolution.tv_sec, clock_resolution.tv_nsec);


  clock_gettime(CLOCK_REALTIME, &tp1);
  count=0;
   
   while ( count < 20 ) 
   {
     
     while ( digitalRead(7) == LOW )
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
  
  




  clock_gettime(CLOCK_REALTIME, &tp1);
  count=0;
   
   while ( count < 200000 ) 
   {
     
     while ( digitalRead(7) == LOW )
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

  

  accum = ( tp2.tv_nsec - tp1.tv_nsec );
  accum1= accum;
  if ( accum<0 )
  {
   accum=accum+1000000000;
   printf(" acumulator atenuat \n");
  }
  accum1=accum1+s1*1000000000;
  printf( "ACCUM %lf \n", accum );
  printf( "!! ACCUM1 %lf !! \n", accum1);

  
   printf(" dif1 calcul scadere secunde %ld \n",s1);
   printf(" dif2 calcul scadere nanosec %ld \n",s2);
   
 
  printf(" Rez citit secunde  %d %d \n",tp1.tv_sec, tp1.tv_nsec);
  printf(" Rez citit nanosec  %ld %lld \n",tp2.tv_sec, tp2.tv_nsec);
  
  printf(" Rez calc     sec %ld \n",tp2.tv_sec-tp1.tv_sec);
  printf(" Rez calc nanosec %ld \n",tp2.tv_nsec-tp1.tv_nsec);

  printf("Stop\n");
  
}
long double time_diff( struct timespec start, struct timespec stop)
{
 return 1;
 
}
