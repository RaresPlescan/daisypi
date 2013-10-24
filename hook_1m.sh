#!/bin/bash

#check for the usb wifi and restart it if no connection
/daisypi/sense/wifi_watch/wifi_watch.sh

#general script collecting and posting data 
/daisypi/exec/all_readings_sense.sh

#read and exec commands - if any
/daisypi/exec/cmd_exec/read_command.sh


