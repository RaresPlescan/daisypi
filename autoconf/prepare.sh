#!/bin/sh

echo " This script installs needed packages for Daisy Pi"

echo "Now checking / installing bc command line math tool ... "
apt-get -q -y install bc
echo "Now checking / installing mc file manager ... "
apt-get -q -y install mc
echo "Now checking / installing gammu modem utility ( for SMS usage ) ... "
apt-get -q -y install gammu

echo "Installing WiringPI .. "
cd /daisypi/3rdparty
git clone git://git.drogon.net/wiringPi
git pull origin
cd /daisypi/3rdparty/wiringPi
echo "git pull for WiringPi ended, now running build"
/daisypi/3rdparty/wiringPi/build