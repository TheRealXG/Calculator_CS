FROM ubuntu:18.04
RUN	apt-get update && \
	 apt-get install -y --no-install-recommends sudo \
	 qemu-system \
	 uml-utilities \
	 bridge-utils \
	 iproute2 \
	 net-tools \
	 isc-dhcp-client \
	 netcat \
	 iputils-ping \
	 openssh-server 


RUN mv /sbin/dhclient /usr/sbin/dhclient

# After dependencies
# Setup TAP or other networking needs
# CMD ["/volume/config_tap.sh eth0"]
# CMD ["ip addr add 10.18.0.2/16 dev br0"]

# Navigate to and run the QEMU command to launch UA
# WORKDIR /volume/build/src
# CMD ["qemu-system-arm -serial null -serial mon:stdio -nographic   -M xilinx-zynq-a9 -m 256M   -net tap,ifname=qtap,script=no,downscript=no   -net nic,model=cadence_gem,macaddr=0e:b0:ba:5e:ba:12 -no-reboot  -kernel build/arm-rtems6-xilinx_zynq_a9_qemu/rtems/calc.exe"]

COPY ./usr/tmp /usr/tmp
RUN chmod +x /usr/tmp/start.sh
CMD ["/usr/tmp/start.sh"]