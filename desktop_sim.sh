#!/bin/bash

# Setup Docker User Defined Bridge or continue if it already exists
docker network create --driver=bridge --subnet=10.18.0.0/16 --gateway=10.18.0.1 calc-bridge || true

# Start A661 Server
./launchServer.sh&

# Start Calc UA Docker Container (will need to update container location to registry eventually)
docker run -ti --cap-add=NET_ADMIN --device=/dev/net/tun --network calc-bridge --hostname calc_ua -v ~/Documents/calculator:/volume ua_qemu

# ?Some way to exit gracefully?