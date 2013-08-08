#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

#include "wiringPiSPI.h"

int main(void)
{
    int chan = 2;
    int speed = 100000;
    unsigned char buff[2];

    if (wiringPiSPISetup (chan, speed) != 0)
    {
        printf("Could not initialise SPI\n");
        return -1;
    }

    while (1)
    {
        printf ("Input a string, Input 0 to finish.\n");
        gets (buff);
        if( buff[0] == '0')
            break;
        else
        {
            int ret = wiringPiSPIDataRW (chan, buff, 2);
            printf ("buffer: %s\n", buff);
        }
    }

    return 0;
}
