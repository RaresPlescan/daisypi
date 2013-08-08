#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

#include "wiringPiSPI.h"
#include "wiringPi.h"

// The A-D convertor won't run at more than 100KHz at 5v
#define SPI_ADC_SPEED   100000
#define SPI_DAC_SPEED   100000
#define SPI_A2D         0
#define SPI_D2A         1

// Channel definitions
#define CHANNEL_PRESSURE    0
#define CHANNEL_VOLTAGE     1   //ignored
#define CHANNEL_LIGHT       2
#define CHANNEL_CARBON      3

#define BUFF_SIZE       200


extern void daisyAnalogWrite (int chan, int value)
{
    uint8_t spiData [2];
    uint8_t chanBits, dataBits;

    if (chan == 0)
        chanBits = 0x30;
    else
        chanBits = 0xB0;

    chanBits |= ((value >> 4) & 0x0F);
    dataBits  = ((value << 4) & 0xF0);

    spiData [0] = chanBits;
    spiData [1] = dataBits;

    wiringPiSPIDataRW (SPI_D2A, spiData, 2);
}

extern int  daisyAnalogRead (int chan)
{
    uint8_t spiData [2];
    uint8_t chanBits;

    if (chan == 0)
        chanBits = 0b11010000;
    else
        chanBits = 0b11110000;

    spiData [0] = chanBits;
    spiData [1] = 0;
    wiringPiSPIDataRW (SPI_A2D, spiData, 2);

    return ((spiData [0] << 7) | (spiData [1] >> 1)) & 0x3FF;
}

extern int  daisySPISetup (void)
{
    if (wiringPiSPISetup (SPI_A2D, SPI_ADC_SPEED) < 0)
        return -1;
    //if (wiringPiSPISetup (SPI_D2A, SPI_DAC_SPEED) < 0)
    //    return -1;
    return 0;
}

int main()
{
    unsigned char buff[BUFF_SIZE] = {0};
    int chanSelect = CHANNEL_LIGHT;
    int i, value = 0;

    double angle;
    uint32_t x1;

    if (wiringPiSetupSys() < 0)
        printf("System initialization error\n");
    if (daisySPISetup() < 0)
        printf ("SPI-Driver initialization error.\n");
    
    /*
    for (i = 0; i < B_SIZE; i++)
    {
        angle = ((double)i / (double)B_SIZE) * M_PI * 2.0;
        buff[i] = (int)rint ((sin (angle)) * 127.0 + 128.0);
    }
    */

    while (1)
    {
        memset(buff, 0, BUFF_SIZE*sizeof(char));

        //daisyAnalogWrite (chanSelect, value);     
        //printf("value: %d - %x\n", value, value);

        //for (i = 0 ; i < B_SIZE ; i++)
        //{
            //gertboardAnalogWrite (chanSelect, buffer [i]);
            
            x1 = gertboardAnalogRead (chanSelect);
            //gertboardAnalogWrite (1, x1);   // 10-bit A/D, 8-bit D/A
            //value = daisyAnalogRead (chanSelect);
            printf("value: %d - %x\n", x1, x1);
        //}
        //wiringPiSPIDataRW (chanSelect, buff, 2);
        //printf ("buffer: %s\n", buff);

        break;
    }
    
	return 0;	
}
