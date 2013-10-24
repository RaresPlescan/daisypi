/***************************** FILE HEADER ***********************************/
/*!
*  \file		spi_driver.c
*
*  \brief		<b>File for interaction with the spidev interface.</b>\n
*
*				A detailed description...
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


/******************************************************************************
* Local functions
******************************************************************************/
/*!
 *******************************************************************************
 *  transfer
 *******************************************************************************
 *
 *  \brief      <b>Does the ADC conversion and reading of the value received
 *				from a channel.\n</b>
 *
 *  \param[in]		int      file descriptor
 *
 *  \author         Vaduva Jan Alexandru
 *
 *  \date           2013-08-11
 ******************************************************************************/
void transfer(int fd)
{
#ifdef DEMO_TEST
	int ret;
	uint8_t tx[] = {
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0x40, 0x00, 0x00, 0x00, 0x00, 0x95,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xDE, 0xAD, 0xBE, 0xEF, 0xBA, 0xAD,
		0xF0, 0x0D,
	};
#else
	uint16_t adc;
	uint8_t ret,i;

	uint8_t tx[BUFF_SIZE]; 		// BUFF_SIZE sent to MPC3208
#endif
	uint8_t rx[ARRAY_SIZE(tx)] = {0, };

	/* TODO: check this for a better version of the implementation.
	for (i = 0; i < ARRAY_SIZE(tx); i++)
  	{
      	tx[ARRAY_SIZE(tx)-i-1] = channel%256;
      	channel = channel >> 8;
  	}
  	*/
  	/* *
  	* first byte transmitted is the start bit(1) followed by SGL/DIFF and D2,
  	* second byte transmitted is D1 and D0 everything else does not matter,
  	* third byte transmitted value is not important.
  	* */
  	switch (channel)
    {
    	case CHANNEL0:
        	tx[0] = 0b00000110; 	
		  	tx[1] = 0b00000000;	
		  	tx[2] = 0b00000000;
        	break;
    	case CHANNEL1:
    		tx[0] = 0b00000110; 	
		  	tx[1] = 0b01000000;	
		  	tx[2] = 0b00000000;
        	break;
    	case CHANNEL2:
    		tx[0] = 0b00000110; 	
		  	tx[1] = 0b10000000;	
		  	tx[2] = 0b00000000;
    	    break;
    	case CHANNEL3:
    		tx[0] = 0b00000110; 	
		  	tx[1] = 0b11000000;	
		  	tx[2] = 0b00000000;
    	    break;
    	case CHANNEL4:
    		tx[0] = 0b00000111; 	
		  	tx[1] = 0b00000000;	
		  	tx[2] = 0b00000000;
    	    break;
    	case CHANNEL5:
    		tx[0] = 0b00000111; 	
		  	tx[1] = 0b01000000;	
		  	tx[2] = 0b00000000;
    	    break;
    	case CHANNEL6:
    		tx[0] = 0b00000111; 	
		  	tx[1] = 0b10000000;	
		  	tx[2] = 0b00000000;
    	    break;
    	case CHANNEL7:
    		tx[0] = 0b00000111; 	
		  	tx[1] = 0b11000000;	
		  	tx[2] = 0b00000000;
    	    break;
    	default:
    	    break;
    }

	/* TODO: cleanup, debug information */

	struct spi_ioc_transfer tr =
	{
		.tx_buf = (unsigned long)tx,
		.rx_buf = (unsigned long)rx,
		.len = ARRAY_SIZE(tx),
		.delay_usecs = delay,
		.speed_hz = speed,
		.bits_per_word = bits,
	};

	ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
	TEST(ret < 1, "can't send spi message");

	/* TODO: cleanup, debug information */
#ifdef DEMO_TEST
	for (ret = 0; ret < ARRAY_SIZE(tx); ret++) {
		if (!(ret % 6))
			puts("");
		printf("%.2X ", rx[ret]);
	}
	puts("");
#else

    adc = (rx[1] << 8) + rx[2];
	adc &= 0xFFF;
	printf("ADC: %5X (hex) - %5d (dec)\n", adc, adc);
	printf("ADC Voltage = %g mV\n", (float)adc*3300/4096);
#endif
}

/*!
 *******************************************************************************
 *	print_usage
 *******************************************************************************
 *
 *  \brief		<b>Prints to the screen the format of the call sequence. Is
 * 				the help sequence that quides the user on how to utilise
 * 				the interface.\n</b>
 *
 *  \param[in]		const char*      program name
 *
 *  \author         Vaduva Jan Alexandru
 *
 *  \date           2013-08-11
 ******************************************************************************/
void print_usage(const char *prog)
{
	printf("Usage: %s [-DsbdlHOLC3]\n", prog);
	puts("  -D --device   device to use (default /dev/spidev0.0)\n"
	     "  -s --speed    max speed (Hz)\n"
	     "  -d --delay    delay (usec)\n"
	     "  -b --bpw      bits per word \n"
	     "  -l --loop     loopback\n"
	     "  -H --cpha     clock phase\n"
	     "  -O --cpol     clock polarity\n"
	     "  -L --lsb      least significant bit first\n"
	     "  -C --cs-high  chip select active high\n"
	     "  -3 --3wire    SI/SO signals shared\n");
	exit(1);
}

/*!
 *******************************************************************************
 *	parse_opts
 *******************************************************************************
 *
 *  \brief		<b>Parses the output received to establish the corresponding
 *				settings for the communication.\n</b>
 *
 *  \param[in]		int			 arguments number
 *  \param[in]		char* []     arguments array
 *
 *  \author         Vaduva Jan Alexandru
 *
 *  \date           2013-08-11
 ******************************************************************************/
void parse_opts(int argc, char *argv[])
{
	while (1) {
		static const struct option lopts[] = {
			{ "device",  1, 0, 'D' },
			{ "speed",   1, 0, 's' },
			{ "delay",   1, 0, 'd' },
			{ "bpw",     1, 0, 'b' },
			{ "loop",    0, 0, 'l' },
			{ "cpha",    0, 0, 'H' },
			{ "cpol",    0, 0, 'O' },
			{ "lsb",     0, 0, 'L' },
			{ "cs-high", 0, 0, 'C' },
			{ "3wire",   0, 0, '3' },
			{ "no-cs",   0, 0, 'N' },
			{ "ready",   0, 0, 'R' },
			{ NULL, 0, 0, 0 },
		};
		int c;

		c = getopt_long(argc, argv, "D:s:d:b:lHOLC3NR", lopts, NULL);

		if (c == -1)
			break;

		switch (c) {
		case 'D':
			device = optarg;
			break;
		case 's':
			speed = atoi(optarg);
			break;
		case 'd':
			delay = atoi(optarg);
			break;
		case 'b':
			bits = atoi(optarg);
			break;
		case 'l':
			mode |= SPI_LOOP;
			break;
		case 'H':
			mode |= SPI_CPHA;
			break;
		case 'O':
			mode |= SPI_CPOL;
			break;
		case 'L':
			mode |= SPI_LSB_FIRST;
			break;
		case 'C':
			mode |= SPI_CS_HIGH;
			break;
		case '3':
			mode |= SPI_3WIRE;
			break;
		case 'N':
			mode |= SPI_NO_CS;
			break;
		case 'R':
			mode |= SPI_READY;
			break;
		default:
			print_usage(argv[0]);
			break;
		}
	}
}

/*!
 *******************************************************************************
 *  spi_open
 *******************************************************************************
 *
 *  \brief      <b>Opens the spi device for setting up the spidev interface.
 * 				private member variables are used to configure spidev.\n</b>
 *
 *  \param[in]		int      file descriptor
 *
 *  \author         Vaduva Jan Alexandru
 *
 *  \date           2013-08-11
 ******************************************************************************/
void spi_open(int fd)
{
	int ret;
	
	/* spi mode */
    ret = ioctl(fd, SPI_IOC_WR_MODE, &mode);
    TEST(ret == -1, "Could not set SPIMode (WR)");
    ret = ioctl(fd, SPI_IOC_RD_MODE, &mode);
    TEST(ret == -1, "Could not set SPIMode (RD)");

    /* bits per word */
    ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
    TEST(ret == -1, "Could not set SPI bitsPerWord (WR)");
	ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits);
    TEST(ret == -1, "Could not set SPI bitsPerWord (RD)");

    /* max speed hz */
    ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
    TEST(ret == -1, "Could not set SPI speed (WR)");
    ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
    TEST(ret == -1, "Could not set SPI speed (RD)");
}

