/***************************** FILE HEADER ***********************************/
/*!
*  \file		spi_driver.h
*
*  \brief		<b>Definitions for the spi_driver interface.</b>\n
*
*  \author		Vaduva Jan Alexandru\n
*				Copyright 2013 Daisy Pi
*
*  \version	1.0	2013-08-11 Vaduva Jan Alexandru    created
*
*//**************************** FILE HEADER **********************************/
#ifndef __spiDriverh
#define __spiDriverh

/******************************************************************************
 * Includes
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

/******************************************************************************
 * Defines
 *****************************************************************************/
#define ARRAY_SIZE(a) 	(sizeof(a) / sizeof((a)[0]))
#define BUFF_SIZE 		3

/* Configuration bits for single-ended channel selection */
#define CHANNEL0 0x060000   // Channel 0
#define CHANNEL1 0x064000   // Channel 1
#define CHANNEL2 0x068000   // Channel 2
#define CHANNEL3 0x06C000   // Channel 3
#define CHANNEL4 0x070000   // Channel 4
#define CHANNEL5 0x074000   // Channel 5
#define CHANNEL6 0x078000   // Channel 6
#define CHANNEL7 0x07C000   // Channel 7

#define TEST(assertion, call_description) 	\
	do { 									\
		if (assertion) {					\
			fprintf (stderr, "(%s, %d): ", 	\
				__FILE__, __LINE__);		\
			perror(call_description);		\
			exit(EXIT_FAILURE);				\
		}									\
	} while (0)

/******************************************************************************
 * Local variables
 *****************************************************************************/
//static const char *device = "/dev/spidev0.0";
static const char *device = "/dev/spidev0.0";
static uint8_t mode = SPI_MODE_0;
static uint8_t bits = 8;
//static uint32_t speed = 1000000;
static uint32_t speed = 10000;
static uint16_t delay;

uint32_t channel;

/******************************************************************************
 * Forward declaration
 *****************************************************************************/
void print_usage(const char *prog);
void parse_opts(int argc, char *argv[]);
void spi_open(int fd);
void transfer(int fd);


#endif /* __spiDriverh */
