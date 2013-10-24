#!/bin/sh


timp=$(cat /daisypi/timelapse/date.txt | awk '{print $4}')

date +%T -s $timp

#echo $timp