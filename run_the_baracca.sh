#!/bin/bash

# add this file to the rc.local
# this must be run by root otherwise do nothing
if [[ $EUID -ne 0 ]]; then
	echo "Run me as root. Exiting..."
	exit -1
fi

cd /home/kruidnagel/RGB-ify

# import configuration
. server.conf

# Done in the c code
# if [ ! -f "/sys/class/gpio/gpio$GPIO_CS_HELPER/direction" ]; then
#     # export the gpio to be used for cs of helper
# 	echo $GPIO_CS_HELPER > /sys/class/gpio/export
# fi

# set gpio as out
# echo "out" > /sys/class/gpio/gpio$GPIO_CS_HELPER/direction
# echo "1" > /sys/class/gpio/gpio$GPIO_CS_HELPER/value

./build/RGB-ify $1 $2 $3

# # unexport
# echo $GPIO_CS_HELPER > /sys/class/gpio/unexport

exit 0
