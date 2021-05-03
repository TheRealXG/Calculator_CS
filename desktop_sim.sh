#!/bin/bash

# Setup Docker User Defined Bridge or continue if it already exists
docker network create --driver=bridge --subnet=10.18.0.0/16 --gateway=10.18.0.1 calc-bridge || true

# Start A661 Server container
xhost +local:docker
docker run -ti -e DISPLAY --network=calc-bridge --hostname=server --name=server_con -v ~/Documents/calculator:/volume -v /tmp/.X11-unix:/tmp/.X11-unix -d a661_server

sleep 5
a661_pid=`pgrep A661S`

# Start Calc UA Docker Container (will need to update container location to registry eventually)
docker run -ti --cap-add=NET_ADMIN --device=/dev/net/tun --network=calc-bridge --hostname=calc_ua --name=calc_ua_con -v ~/Documents/calculator:/volume -d ua_qemu

# What for the Server GUI to be closed (which will stop that process ID)
tail --pid=$a661_pid -f /dev/null
# Cleanup docker containers after the server is quit
docker kill calc_ua_con
docker rm calc_ua_con
docker rm server_con