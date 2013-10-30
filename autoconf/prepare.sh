#!/bin/sh

echo " This script installs needed packages for Daisy Pi"

echo "Now checking / installing bc command line math tool ... "
apt-get -q -y install bc
echo "Now checking / installing mc file manager ... "
apt-get -q -y install mc
echo "Now checking / installing gammu modem utility ( for SMS usage ) ... "
apt-get -q -y install gammu

