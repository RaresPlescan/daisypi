#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/i2c-dev.h>

#define SRF02_I2C_ADDR 0x70
#define ADXL345_I2C_ADDR 0x53

void selectDevice(int fd, int addr, char * name)
{
   if (ioctl(fd, I2C_SLAVE, addr) < 0)
   {
      fprintf(stderr, "%s not present\n", name);
      //exit(1);
   }
}

void writeToDevice(int fd, int reg, int val)
{
   char buf[2];
   buf[0]=reg; buf[1]=val;
   if (write(fd, buf, 2) != 2)
   {
      fprintf(stderr, "Can't write to ADXL345\n");
      //exit(1);
   }
}

int main(int argc, char **argv)
{
   unsigned int range;
   int count, b;
   short x, y, z;
   float xa, ya, za;
   int fd;
   unsigned char buf[16];
   
   if ((fd = open("/dev/i2c-1", O_RDWR)) < 0)
   {
      // Open port for reading and writing
      fprintf(stderr, "Failed to open i2c bus\n");
      exit(1);
   }
   
   /* initialise ADXL345 */

   selectDevice(fd, ADXL345_I2C_ADDR, "ADXL345");

   writeToDevice(fd, 0x2d, 0);
   writeToDevice(fd, 0x2d, 16);
   writeToDevice(fd, 0x2d, 8);
   writeToDevice(fd, 0x31, 0);
   writeToDevice(fd, 0x31, 11);

   while (1)
   {   
      /* select SRF02 */

      selectDevice(fd, SRF02_I2C_ADDR, "SRF02");

      buf[0]=0; buf[1]=81;
      if ((write(fd, buf, 2)) != 2)
      {
         fprintf(stderr, "Can't write to SRF02\n");
         //exit(1);
      }
   
      usleep(100000);  // wait long enough to ensure ping
   
      buf[0] = 0;
      if ((write(fd, buf, 1)) != 1)
      {
         fprintf(stderr, "Can't write to SRF02\n");
         //exit(1);
      }
   
      if (read(fd, buf, 4) != 4)
      {
         fprintf(stderr, "Can't read from SRF02\n");
         //exit(1);
      }
      else
      {
         range = buf[2]<<8 | buf[3];
         printf("%3u ", range);
      }

      /* select ADXL345 */

      selectDevice(fd, ADXL345_I2C_ADDR, "ADXL345");

      buf[0] = 0x32;
   
      if ((write(fd, buf, 1)) != 1)
      {
         // Send the register to read from
         fprintf(stderr, "Error writing to i2c slave\n");
         //exit(1);
      }
   
      if (read(fd, buf, 6) != 6)
      {
         //  X, Y, Z accelerations

         fprintf(stderr, "Unable to read from ADXL345\n");
         //exit(1);
      }
      else
      {
         x = buf[1]<<8| buf[0];
         y = buf[3]<<8| buf[2];
         z = buf[5]<<8| buf[4];
         xa = (90.0 / 256.0) * (float) x;
         ya = (90.0 / 256.0) * (float) y;
         za = (90.0 / 256.0) * (float) z;
         //printf("x=%d, y=%d, z=%d\n", x, y, z);
         printf("%4.0f %4.0f %4.0f\n", xa, ya, za);
         //for (b=0; b<6; b++) printf("%02x ",buf[b]); printf("\n");
      }
      usleep(900000);
   }
   
   return 0;
}
