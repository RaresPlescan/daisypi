# Modify tool allows various setting to be operated in their
# corresponding files via scripting.
# These are one time only operations performed on a fresh 
# Raspbian installation.

# Main insert in crontab :
# * * * * * /daisypi/hook_1m.sh
# 0,30 * * * * /daisypi/hook_30m.sh

# Inserts to /etc/modprobe.d/raspi-blacklist.conf - enables SPI and I2C
#
#  #blacklist spi-bcm2708
#  #blacklist i2c-bcm2708
#



#!/bin/sh



echo " Daisy Pi automatic modifier for crontab, blacklist.conf "
echo " Checking crontab now ... "


pattern="# Modified by Daisy Pi installer 1.0"

flag_1=$(crontab -l | grep -c daisy)
flag_2=$(crontab -l | grep -c 'Modified by Daisy Pi')

#flag_1='0'
#flag_2='0'

if [[ ( "$flag_1" < 1 ) || ( "$flag_2" < 1 )  ]] ; then

   # Adding the tag pattern in order to nicely document modificantions and
   # prevent double changes in the future.
   (crontab -l; echo "$pattern" ) | crontab -

   # Adding 1 minute hook.
   add_line="* * * * * /daisypi/hook_1m.sh"
   (crontab -l; echo "$add_line" ) | crontab -

   # Adding 30 minutes hook
   add_line="0,30 * * * * /daisypi/hook_30m.sh"
   (crontab -l; echo "$add_line" ) | crontab -

   echo " Crontab modification done !"

 else
  echo " Crontab already configured with Diasy Pi hooks, now exiting."
fi 


echo " Blacklist removing for SPI and I2C in /etc/modprobe.d/raspi-blacklist.conf "

 sed -i.bak 's/^blacklist spi-bcm2708/\ #blacklist spi-bcm2708/g' /etc/modprobe.d/raspi-blacklist.conf
 sed -i.bak 's/^blacklist i2c-bcm2708/\ #blacklist i2c-bcm2708/g' /etc/modprobe.d/raspi-blacklist.conf

echo " Reboot needed !"

