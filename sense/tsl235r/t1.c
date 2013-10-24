// gcc delayTest.c -o t1 -L/usr/local/lib -lwiringPi -lwiringPiDev -lpthread -lm

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <wiringPi.h>

main()
{

  struct timespec tp1, tp2;
  int i1,i2,x,y;
  int count;
  
  wiringPiSetup () ;
  pinMode (7, INPUT) ;

  printf("Start\n");
  clock_gettime(CLOCK_REALTIME, &tp1);

  // gettimeofday(tp1, NULL);
//  printf(" R1 %d %d \n",i1,tp1.tv_nsec);
//  sleep(2);


//  i2=clock_gettime(CLOCK_REALTIME, &tp2);
//   if (x!=y)
//   {
//    printf("ee");
//  }

   count=0;
   
   while ( count < 20000 ) 
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



  printf (" Contor %d \n", digitalRead(7) );
  clock_gettime(CLOCK_REALTIME, &tp2);
//   gettimeofday(tp2, NULL);
  printf(" R1 %d %d %d\n",i1,tp1.tv_sec, tp1.tv_nsec);
  printf(" R2 %d %d %d\n",i2,tp2.tv_sec, tp2.tv_nsec);
  
  printf(" Rez sec %d\n",(int)(tp2.tv_sec-tp1.tv_sec));
  printf(" Rez nanosec %d\n",(int)(tp2.tv_nsec-tp1.tv_nsec));
//  delay(1000);
// sleep(1);
  printf("Stop\n");
  
}