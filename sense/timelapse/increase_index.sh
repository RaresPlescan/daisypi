#!/bin/sh

i=$(cat /daisypi/timelapse/index.txt)

echo $i

i=$(($i+1))

echo $i > /daisypi/timelapse/index.txt
