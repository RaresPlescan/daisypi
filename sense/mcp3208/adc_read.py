#!/usr/bin/env python
import time
import os
import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BCM)
DEBUG = 1

# read SPI data from MCP3008 chip, 8 possible adc's (0 thru 7)
def readadc(adcnum, clockpin, mosipin, misopin, cspin):
        if ((adcnum > 7) or (adcnum < 0)):
                return -1
        GPIO.output(cspin, True)

        GPIO.output(clockpin, False)  # start clock low
        GPIO.output(cspin, False)     # bring CS low

        commandout = adcnum
        commandout |= 0x18  # start bit + single-ended bit
        commandout <<= 3    # we only need to send 5 bits here
        for i in range(5):
                if (commandout & 0x80):
                        GPIO.output(mosipin, True)
                else:
                        GPIO.output(mosipin, False)
                commandout <<= 1
                GPIO.output(clockpin, True)
                GPIO.output(clockpin, False)

        adcout = 0
        # read in one empty bit, one null bit and 10 ADC bits
        for i in range(14):
                GPIO.output(clockpin, True)
                GPIO.output(clockpin, False)
                adcout <<= 1
                if (GPIO.input(misopin)):
                        adcout |= 0x1

        GPIO.output(cspin, True)
        
        adcout >>= 1       # first bit is 'null' so drop it
        return adcout

# change these as desired - they're the pins connected from the
# SPI port on the ADC to the Cobbler
SPICLK = 11
SPIMISO = 9
SPIMOSI = 10
SPICS = 8

# set up the SPI interface pins
GPIO.setup(SPIMOSI, GPIO.OUT)
GPIO.setup(SPIMISO, GPIO.IN)
GPIO.setup(SPICLK, GPIO.OUT)
GPIO.setup(SPICS, GPIO.OUT)

# 10k trim pot connected to adc #0
potentiometer_adc = 0;

last_read = 0       # this keeps track of the last potentiometer value
tolerance = 5       # to keep from being jittery we'll only change
                    # volume when the pot has moved more than 5 'counts'
t1 = 0
dt = 0
er = 10

#while True:
        # we'll assume that the pot didn't move
#        trim_pot_changed = False


        # read the analog pin
#rap1 = eval('820 / 1290')
#rap2 = eval('1 / 2')
#q = eval('3.3 / 4096')

ar = readadc(0, SPICLK, SPIMOSI, SPIMISO, SPICS)
#r = eval(' 5 * q / rap1')
print " P0 %s %.2f" % (ar, 2)

pdiff = readadc(1, SPICLK, SPIMOSI, SPIMISO, SPICS)
print " P1 %s %.2f" % (pdiff, 1)

pdiff = readadc(2, SPICLK, SPIMOSI, SPIMISO, SPICS)
print " P2 %s %.2f" % (pdiff, 1)

pdiff = readadc(3, SPICLK, SPIMOSI, SPIMISO, SPICS)
print " P3 %s %.2f" % (pdiff, 2)

pdiff = readadc(4, SPICLK, SPIMOSI, SPIMISO, SPICS)
print " P4 %s %.2f" % (pdiff, 2)


pdiff = readadc(5, SPICLK, SPIMOSI, SPIMISO, SPICS)
print " P5 %s %.2f" % (pdiff, 2)

pdiff = readadc(6, SPICLK, SPIMOSI, SPIMISO, SPICS)
print " P6 %s %.2f" % (pdiff, 2)

pdiff = readadc(7, SPICLK, SPIMOSI, SPIMISO, SPICS)
print " P7 %s %.2f" % (pdiff, 22)






GPIO.cleanup()
