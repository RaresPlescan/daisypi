#!/bin/bash





#!/bin/sh

# GPIO numbers should be from this list
# 0, 1, 4, 7, 8, 9, 10, 11, 14, 15, 17, 18, 21, 22, 23, 24, 25

# Note that the GPIO numbers that you program here refer to the pins
# of the BCM2835 and *not* the numbers on the pin header. 
# So, if you want to activate GPIO7 on the header you should be 
# using GPIO4 in this script. Likewise if you want to activate GPIO0
# on the header you should be using GPIO17 here.

# Set up GPIO 4 and set to output
echo "4" > /sys/class/gpio/export
echo "out" > /sys/class/gpio/gpio4/direction

# Set up GPIO 7 and set to input
#echo "7" > /sys/class/gpio/export
#echo "in" > /sys/class/gpio/gpio7/direction

# Write output
echo "1" > /sys/class/gpio/gpio4/value

# Read from input
cat /sys/class/gpio/gpio7/value 

sleep 5

# Clean up
echo "4" > /sys/class/gpio/unexport
echo "7" > /sys/class/gpio/unexport





#---------------------

# check if the script is run by root
if [ "$(whoami)" != "root" ]; then
        echo "You must run this script as a root user." 2>&1
        exit 1
fi

# GPIO numbers should be from this list:
# Rev 1. 0, 1, 4, 7, 8, 9, 10, 11, 14, 15, 17, 18, 21, 22, 23, 24, 25
# Rev 2. 2, 3, 4, 7, 8, 9, 10, 11, 14, 15, 17, 18, 22, 23, 24, 25, 27

# set GPIO pin according to argument, otherwise default to pin 4
GPIOPIN=${1:-4}

# set pause time according to argument, otherwise default to 1 sec
PAUSETIME=${2:-1}

# if the incorrect number of arguments were passed, echo verbose message
if [ $# -ne 2 ]; then
        echo -n "* Toggle GPIO pin $GPIOPIN: "
fi

# set GPIO direction
echo "$GPIOPIN" > /sys/class/gpio/export
echo "out" > /sys/class/gpio/gpio$GPIOPIN/direction

# set GPIO value HIGH
echo -n "ON "
echo "1" > /sys/class/gpio/gpio$GPIOPIN/value

# pause
sleep $PAUSETIME

# set GPIO value (LOW)
echo -n "-> OFF"
echo "0" > /sys/class/gpio/gpio$GPIOPIN/value

# cleanup
echo "$GPIOPIN" > /sys/class/gpio/unexport

# if the incorrect number of arguments were passed, then finish with a newline
if [ $# -ne 2 ]; then
        echo 
fi