#!/bin/bash

echo "interface entered: $1";
if [ "$EUID" -ne 0 ]
  then echo "Please run as root"
  exit
fi

if [ $# -eq 0 ]
  then
    echo "No arguments supplied, please provide name of ethernet interface in bridge from ifconfig"
    exit
fi

echo "Deleting qtap";

brctl delif br0 qtap
brctl delif br0 $1
tunctl -d qtap
ifconfig br0 down
brctl delbr br0
ifconfig $1 up
dhclient -v $1

echo "IP assigned to Bridge"
ifconfig $1 | grep "inet "
