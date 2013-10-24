#!/bin/bash

#check for the usb wifi and restart it if no connection
/daisypi/sense/wifi_watch/wifi_watch.sh

#general script collecting and posting data 
/daisypi/exec/all_readings_sense.sh
sleep 2
#script making use of execution feature 
/daisypi/exec/cmd_exec/read_command.sh
sleep 15

#second poll of data collector
/daisypi/exec/all_readings_sense.sh

