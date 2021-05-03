#!/bin/bash

echo "interface entered: $1";
if [ "$EUID" -ne 0 ]
  then echo "Please run as root"
  exit
fi

if [ $# -eq 0 ]
  then
    echo "No arguments supplied, please provide name of ethernet interface from ifconfig"
    exit
fi

echo "Creating qtap";

brctl addbr br0;
ip addr flush dev $1;
brctl addif br0 $1;
tunctl -t qtap -u $(whoami);
brctl addif br0 qtap;
ifconfig $1 up;
ifconfig qtap up;
ifconfig br0 up;
brctl show;

if [ "$2" != "nodhcp" ]
  then
    dhclient -v br0;
    echo "IP assigned to Bridge"
    ifconfig br0 | grep "inet "
fi