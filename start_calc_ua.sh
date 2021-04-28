#!/bin/bash

/volume/config_tap.sh eth0
ip addr add 10.18.0.3/16 dev br0

cd /volume/build/src
qemu-system-arm -serial null -serial mon:stdio -nographic   -M xilinx-zynq-a9 -m 256M   -net tap,ifname=qtap,script=no,downscript=no   -net nic,model=cadence_gem,macaddr=0e:b0:ba:5e:ba:12 -no-reboot  -kernel build/arm-rtems6-xilinx_zynq_a9_qemu/rtems/calc.exe