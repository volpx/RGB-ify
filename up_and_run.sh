#!/bin/bash

. server.conf

REMOTE=$REMOTE_USER@$REMOTE_ADDRESS

echo "Building..."

# make all
echo "make all"

echo "Loading to home server..."

ssh $REMOTE "mkdir -p ~/bin"
scp build/RGB-ify $REMOTE:~/bin/RGB-ify
ssh $REMOTE "chmod +x ~/bin/RGB-ify && ~/bin/RGB-ify"

