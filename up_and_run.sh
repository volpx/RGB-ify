#!/bin/bash
set -e

# import the configuration
. server.conf

REMOTE=$REMOTE_USER@$REMOTE_ADDRESS

up(){

	echo -ne "\nBuilding...\n"
	make

	echo -ne "\nLoading to home server...\n"
	scp build/RGB-ify $REMOTE:~/RGB-ify/build/RGB-ify
	scp run_the_baracca.sh $REMOTE:~/RGB-ify/run_the_baracca.sh
	scp server.conf $REMOTE:~/RGB-ify/server.conf
}

run(){
	echo "Running..."
	ssh $REMOTE "~/bin/RGB-ify"
}

prepare(){
	# TODO: add spidev overlay, write udev rule for spi, add user to spi group, reboot
	ssh $REMOTE "mkdir -p ~/RGB-ify/build \
	&& touch ~/RGB-ify/build/RGB-ify && chmod +x ~/RGB-ify/build/RGB-ify\
	&& touch ~/RGB-ify/run_the_baracca.sh && chmod +x ~/RGB-ify/run_the_baracca.sh\
	&& touch ~/RGB-ify/server.conf && chmod +x ~/RGB-ify/server.conf"
}

$1
