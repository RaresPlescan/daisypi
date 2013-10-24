/***************************** FILE HEADER ***********************************/
/*!
*  \file		adc_read.c
*
*  \brief		<b>Demo application that uses the spi_driver interface for
* 				Microchip MCP3208 ADC chip.</b>\n
*
*  \note		Some special notes
*
*  \author		Vaduva Jan Alexandru\n
*				Copyright 2013 Daisy Pi
*
*  \version	1.0	2013-08-11 Vaduva Jan Alexandru    created
*
*//**************************** FILE HEADER **********************************/

/******************************************************************************
* Includes
******************************************************************************/
#include "spi_driver.h"
	
	
int main(int argc, char *argv[])
{
	int fd, ret = 0;

	parse_opts(argc, argv);

	fd = open(device, O_RDWR);
	TEST(fd < 0, "Could not open SPI device");

    spi_open(fd);

	printf("spi device: %s\n", device);
	printf("spi mode: %d\n", mode);
	printf("bits per word: %d\n", bits);
	printf("max speed: %d Hz (%d KHz)\n", speed, speed/1000);

	
	channel = CHANNEL0;  // we use channel 7 here
	transfer(fd);
	channel = CHANNEL1;  // we use channel 7 here
	transfer(fd);
	channel = CHANNEL2;  // we use channel 7 here
	transfer(fd);
	channel = CHANNEL3;  // we use channel 7 here
	transfer(fd);
	channel = CHANNEL4;  // we use channel 7 here
	transfer(fd);
	channel = CHANNEL5;  // we use channel 7 here
	transfer(fd);
	channel = CHANNEL6;  // we use channel 7 here
	transfer(fd);
	channel = CHANNEL7;  // we use channel 7 here
	transfer(fd);

	close(fd);
	return ret;
}

