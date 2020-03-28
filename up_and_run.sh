#!/bin/bash
set -e

# import the configuration
. server.conf

REMOTE=$REMOTE_USER@$REMOTE_ADDRESS


echo "Building..."

echo make all
aarch64-linux-gnu-gcc RGB-ify.cpp -o build/RGB-ify

echo "Loading to home server..."

ssh $REMOTE "mkdir -p ~/bin"
scp build/RGB-ify $REMOTE:~/bin/RGB-ify
ssh $REMOTE "chmod +x ~/bin/RGB-ify && ~/bin/RGB-ify /dev/spidev0.0"

