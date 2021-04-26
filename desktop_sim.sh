#!/bin/bash

# Setup Docker User Defined Bridge or continue if it already exists
docker network create --driver=bridge --subnet=10.18.0.0/16 --gateway=10.18.0.1 calc-bridge || true

# Start A661 Server
cd build/DF
../../A661Server server_conf.xml UA_1.bin&
a661_pid=$!
# Start Calc UA Docker Container (will need to update container location to registry eventually)
docker run -ti --cap-add=NET_ADMIN --device=/dev/net/tun --network calc-bridge --hostname calc_ua --name calc_ua_con -v ~/Documents/calculator:/volume -d ua_qemu

# ?Some way to exit gracefully?
tail --pid=$a661_pid -f /dev/null
# Cleanup docker containers after the server is quit
docker kill calc_ua_con
docker rm calc_ua_con