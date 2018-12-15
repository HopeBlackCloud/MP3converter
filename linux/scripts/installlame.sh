#!/bin/bash

sudo apt-get install build-essential
wget https://downloads.sourceforge.net/lame/lame-3.100.tar.gz
tar xf lame-3.100.tar.gz
cd lame-3.100
cp include/lame.h ../../cots/lame-3.100/include
./configure
make
sudo make install
