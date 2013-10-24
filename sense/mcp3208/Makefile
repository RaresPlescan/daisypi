#Makefile used for MCP3208 ADC chip demo


UNAME := $(shell uname -m)

ifeq ($(UNAME), x86_64)
	CC := arm-none-linux-gnueabi-gcc
	INCLUDES := -I ../../RaspberryPi_LinuxKernel/include
else
	CC := gcc
	INCLUDES :=
endif
ifeq ($(UNAME), x86)
	CC := arm-none-linux-gnueabi-gcc
	INCLUDES := -I ../../RaspberryPi_LinuxKernel/include
endif

CCFLAGS = -g $(INCLUDES)
CCFLAGS_TEST = -Wall $(INCLUDES)


all:
	$(CC) $(INCLUDES) spi_driver.c adc_read.c -o adc_read

test:
	$(CC) $(CCFLAGS_TEST) spi_driver.c adc_read.c -o adc_read
	
debug:
	$(CC) $(CCFLAGS) spi_driver.c adc_read.c -o adc_read
	
clean:
	rm -rf adc_read

distclean:
	rm -rf adc_read
	tar czvf adc_read.tar.gz adc_read.c spi_driver.c spi_driver.h Makefile