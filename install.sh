#Daisy Pi Installer 1.0

#!/bin/sh

# Preparing OS by installing needed packages and tools
/daisypi/autoconf/prepare.sh

# Modifing config files for Daisy Pi
/daisypi/autoconf/modify.sh

# Building for each sensor / component 
/daisypi/autoconf/build.sh

echo " Installer execution ended."
