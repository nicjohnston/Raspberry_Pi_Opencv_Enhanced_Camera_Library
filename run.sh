#!/bin/bash
cd /home/pi/git/robidouille/raspicam_cv/
export PS1='$(whoami)@$(hostname):$(pwd)'
make
cd /home/pi/
g++-4.7 -W -O2 -Wall -std=c++11 -c -Wno-multichar -g -I/home/pi/git/robidouille$
#./Test
