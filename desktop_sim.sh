#!/bin/bash

# Check if newly compiled application exists, if so ask if you want to use it
FILE=build/src/build/arm-rtems6-xilinx_zynq_a9_qemu/rtems/calc.exe
if [ -f "$FILE" ]; then
    while true
	do
	 read -r -p "$FILE exists, would you like to use this Calc executable? [Y/n] " input
	 
	 case $input in
	     [yY][eE][sS]|[yY])
	 echo "Yes, using $FILE"
	 # Copy input file with same path to executable file
	 cp start_calc_ua.sh.in start_calc_ua.sh
	 break
	 ;;
	     [nN][oO]|[nN])
	 echo "No, using existing executable in Repo, build/calc.exe"
	 # Replace the default path in input script to executable file
	 sed -e 's|build/arm-rtems6-xilinx_zynq_a9_qemu/rtems|..|' start_calc_ua.sh.in  > start_calc_ua.sh
	 break
	        ;;
	     *)
	 echo "Invalid input..."
	 ;;
	 esac
	done
else 
    echo "No recently compiled Calc executable exists, using existing executable in Repo, build/calc.exe"
    # Replace the default path in input script to executable file
    sed -e 's|build/arm-rtems6-xilinx_zynq_a9_qemu/rtems|..|' start_calc_ua.sh.in  > start_calc_ua.sh
fi


# Setup Docker User Defined Bridge or continue if it already exists
bridge_name=calc-bridge
docker network create --driver=bridge --subnet=10.18.0.0/16 --gateway=10.18.0.1 $bridge_name || true

# Start A661 Server container
xhost +local:docker
server_name=server_con
docker run -ti -e DISPLAY --network=$bridge_name --hostname=server --name=$server_name -v "$(pwd)":/volume -v /tmp/.X11-unix:/tmp/.X11-unix -d therealxg/azure_pipeline:calc_a661_server

sleep 3
a661_pid=`pgrep A661S`

# Start Calc UA Docker Container (will need to update container location to registry eventually)
ua_name=calc_ua_con
docker run -ti --cap-add=NET_ADMIN --device=/dev/net/tun --network=$bridge_name --hostname=calc_ua --name=$ua_name -v "$(pwd)":/volume -d therealxg/azure_pipeline:calc_ua

# What for the Server GUI to be closed (which will stop that process ID)
tail --pid=$a661_pid -f /dev/null
# Cleanup docker containers after the server is quit
docker kill $ua_name
docker rm $ua_name
docker rm $server_name

# Delete Docker network
docker network rm $bridge_name
