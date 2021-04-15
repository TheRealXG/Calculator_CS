# Table of contents
1. [Overview](#overview)
2. [Setup](#setup)
    1. [RTEMS Install](#install)
    2. [RTEMS LIBBSD](#libbsd)
    3. [Compiling](#compiling)
    4. [Network Configuration](#network)
3. [Running the Calculator](#running)
	1. [Without RTEMS](#no_rtems)
	2. [Localhost](#local)
	3. [2 Computers](#2_comp)
4. [Troubleshooting](#troubleshooting)
	

## Overview <a name="overview"></a>
This is a sample calculator application demonstrating implementation of a Server Client configuration between a GUI/Server and a Calculating Backend (User Application). This example demonstrates usage of A661 and FACE standards.  
The GUI and A661 server are a single binary already compiled. Source code is provided for the calculating backend which must be compiled.  
This can be run in several manners. Both the server and backend can run on the same [localhost](#local), or they can run on [two separate computers](#2_comp). The focus of this document and repository is running the calculator backend (UA) in an RTOS (RTEMS for this example) and the GUI/Server running on a Linux general purpose computer. It could also be simply run with both applications [in Linux](#no_rtems). This document currently covers running the UA in a HW emulated environment (QEMU), but the same application could theoretically be run on actual hardware, such as the Xilinx Ultra96 Cortex A53 board, with the same results. This example could also be extended to run both applications inside of containers.


## Setup <a name="setup"></a>
This section will cover setting up a new RTEMS 6 install, adding the LIBBSD networking package, and building a sample BSP (Xilinx A9 QEMU) with this LIBBSD networking package. Finally it will cover compiling the application and some simple network configuration options.  

### RTEMS Install <a name="install"></a>
  1. This has been tested with Ubuntu 18.04 and 20.10 though additionally required dependencies may vary. With Ubuntu 18.04 LTS all necessary dependencies to install RTEMS should be handled in the install process, but if anything is found, simply use the "apt-install" functionality to install them.  
  2.  `export PREFIX=$HOME/quick-start/rtems/6`  
  3. `mkdir -p $HOME/quick-start/src`  
  4. `cd $HOME/quick-start/src/`  
  5. `git clone git://git.rtems.org/rtems-source-builder.git rsb`  
    (Tested on commit 62363ba)  
  6. `git clone git://git.rtems.org/rtems.git`  
    (Tested on commit fd639b8abf)  
  7. `cd rsb/rtems/`  
  8. `../source-builder/sb-set-builder --prefix=$PREFIX 6/rtems-arm`  
  9. `export PATH=$HOME/quick-start/rtems/6/bin:$PATH`  
  10. `arm-rtems6-gcc --version`  
  	a. This command verifies the install worked.  
  11. `cd $HOME/quick-start/src/rtems`  
  12. `./bootstrap -c && ./rtems-bootstrap`  

#### Install BSP
  1. In `$HOME/quick-start/src/rtems` run `./waf bsp_list` to see the list of supported BSPs. This example will use the `xilinx_zynq_a9_qemu` BSP.  
  2. Create a text file called `config.ini` with the following contents: 
  ```
  [arm/xilinx_zynq_a9_qemu]
  BUILD_TESTS = True
  BUILD_SAMPLES = True
  RTEMS_NETWORKING = False
  RTEMS_POSIX_API = True
  ```  
  3. Next, the BSP install process will be configured and run.  
  4. `./waf configure --prefix=$PREFIX`  
  5. `./waf`  
  6. `./waf install`  
  7. The BSP is installed to `$HOME/quick-start/rtems/6/arm-rtems6/xilinx_zynq_a9_qemu/` and the test programs are installed in `$HOME/quick-start/src/rtems/build/arm/xilinx_zynq_a9_qemu/testsuites/`  


### RTEMS LIBSBSD <a name="libbsd"></a>
LIBBSD is a FreeBSD Networking library that has been ported to RTEMS to replace the legacy RTEMS networking stack. This must be installed as a separate add-on. Because it replaces the legacy RTEMS Networking the BSP must be built with the RTEMS_NETWORKING OFF (as was done in the step above) and the LIBBSD library takes the place of it with some additional wscript/waf configuration options.  
  1. `cd $HOME/quick-start/src`  
  2. `git clone git://git.rtems.org/rtems-libbsd.git`  
  3. `cd rtems-libbsd`  
  4. `git checkout 6-freebsd-12`  
    (Tested on commit aef7a74b9)  
  5. `git submodule init`  
  6. `git submodule update rtems_waf`  
  7.
```
./waf configure --prefix=$PREFIX \
  --rtems-bsps=arm/xilinx_zynq_a9_qemu \
  --buildset=buildset/default.ini
```  
  8. `./waf`  
  9. `./waf install`  
  10. This will install LIBBSD to the Prefix location and make it available for use when compiling RTEMS applications.  


### Compiling <a name="compiling"></a>
Now the calculator UA application must be compiled for the BSP to be used. Since this Git repository already has the appropriate scripts and code changes necessary to compile the generated code for RTEMS and LIBBSD, if checked out on the latest master commit, the following can be executed.  
  1. `cd $GIT_REPO/build/src/`  
  2. `git submodule init`  
  3. `git submodule update rtems_waf`  
  4. `./waf configure --rtems=$HOME/quick-start/rtems/6 --rtems-bsp=arm/xilinx_zynq_a9_qemu --rtems-libbsd=$HOME/quick-start/rtems/6`  
    a. At the end of the configuration it will show, among other things:  
```
Checking for RTEMS_NETWORKING               : no  
RTEMS LibBSD                                : arm/xilinx_zynq_a9_qemu  
```  
  5. `./waf`  

#### Changes That Were Made
The steps abve are all that are needed to compile the calculator UA for use in RTEMS and QEMU with this BSP since it is already setup in the repository. This will explain some of the changes that were made to use LIBBSD and RTEMS for this application. This is not necessarily comprehensive, but highlights some of the changes made.  
  
RTEMS uses the WAF build process. The rtems_waf submodule provides the python WAF build tool. WAF uses the `wscript` file to script the build process. This file had to be modified to include LIBBSD as part of the build process, in place of the legacy RTEMS networking library. The wscript imports the `rtems_waf.rtems_bsd` python file. And then the `rtems_bsd` functions are called in their corresponding rtems functions in the wscript. E.g., `rtems_bsd.init(ctx)` in `def init(ctx):` in `wscript`. See the following excerpt. 
```python
def init(ctx):
    rtems.init(ctx, version = rtems_version, long_commands = True)
    rtems_bsd.init(ctx)

def bsp_configure(conf, arch_bsp):
    # Add BSP specific configuration checks
    rtems_bsd.bsp_configure(conf, arch_bsp)
    pass

def options(opt):
    rtems.options(opt)
    rtems_bsd.options(opt)
```  
The wscript also needed the `includes` and `source` parameters updated for all relevant includes and \*.c files for the application.  
The file `man/user_macros.h` was added for basic RTEMS include files.  
The file `include/rtems/bsd/test/default-network-init.h` was added to initialize the network parameters and interface when running the application. This then calls the main() function to kick off the program.  
A `config.inc` file was also added that specifies IP, gateway, etc. but the IP will be overridden by the DHCP assigned IP when the application comes up. This file is required for the `./waf configure...` to work correctly.
  
These items should generally get the code to compile.  
  

### Network Configuration <a name="network"></a>
To run this with RTEMS and QEMU there is additional networking configuration to allow QEMU to connect to the network. This is done through a Tap. This is a virtual Ethernet connector that is bridged with the ethernet connection on the QEMU host machine (real or VM) to allow them to share an IP connection and connect locally or out of the localhost. You may need to install the TUN/TAP tool with `sudo apt-get install uml-utilities bridge-utils`.  

  a. In the repo, run `sudo ./config_tap.sh enp0s3` where `enp0s3` is the ethernet interface of the machine this is being run on.  
    The script is running the following commands:  
```bash
brctl addbr br0;
ip addr flush dev enp0s3;
brctl addif br0 enp0s3;
tunctl -t qtap -u $(whoami);
brctl addif br0 qtap;
ifconfig enp0s3 up;
ifconfig qtap up;
ifconfig br0 up;
brctl show;
dhclient -v br0;
```  
This will give the IP address assigned to the bridge (which both the localhost ethernet and the tap for QEMU will use. This IP will be used in a later step).  
  
  b. After testing is complete, the tap can be removed by restarting the machine or by running `sudo ./cleanup_tap.sh enp0s3` (`enp0s3` is the ethernet interface used above) which will delete the tap and bridge and assign a new IP to the local ethernet interface.  
    The script is running the following commands:  
```bash
brctl delif br0 qtap
brctl delif br0 enp0s3
tunctl -d qtap
ifconfig br0 down
brctl delbr br0
ifconfig enp0s3 up
dhclient -v enp0s3
```


## Running the Calculator <a name="running"></a>
This details how to run the Calculator GUI/Server and calculating UA backend. Running without RTEMS requires NONE of the above setup. It is a good place to start since it ensures the GUI/Server is running properly before replacing the calculator UA with an RTEMS version. The RTEMS/QEMU runs on Localhost and with 2 computers require the above setup to compile the application and then run it. They both assume QEMU is already installed. If it is not installed, on Ubuntu a simple `sudo apt-get install qemu-system` should install the necessary application.    
  

### Without RTEMS <a name="no_rtems"></a>
It is possible to run the A661 GUI/Server and the Calculator backend with both running simply in Linux. This is a useful exercise before running with RTEMS and QEMU to verify the GUI/Server is running properly, since it is run identically in this method as it will be in the RTEMS/QEMU examples.  
1. Checkout the base commit without RTEMS code changes `git checkout 0e44caa`  
2. `cd build` then run `make clean all` to build the calculator UA.  
3. In 1 terminal, from the base directory, run `./launchServer.sh`, this will launch the GUI and server backend.  
  a. This may not run initially if it is missing some graphics libraries necessary for the GUI. Run `ldd A661server` to see which dependencies are required to run the application and which are missing. At which point you can install them via `sudo apt-get install X`, where X is the name of the library. This may require some Googling to determine the appropriate name for the installation.  
4. In another terminal, also from the base directory, run `./launchUA.sh`.  This will execute the calculator backend. Now buttons can be pressed on the GUI and the actions will be passed back to the calculator to be processed and the results passed back to the GUI.  


### Localhost <a name="local"></a>
This assumes QEMU has been installed and the [Tap](#network) has been created.  
1. Verify *$GIT_REPO/build/src/man/a661_socket.h* has `#define A661_DEFAULT_HOSTNAME "10.0.2.15"` set to the IP address printed after running the Tap configuration. If it does not, then change the IP address to that, and [compile](#compiling). If the IP was correct, ensure it has been [compiled](#compiling) since cloning since the compiled binary (build/arm-rtems6-xilinx_zynq_a9_qemu/rtems/calc.exe) is not stored in the repo.  
2. In 1 terminal, from the base directory, run `./launchServer.sh`, this will launch the GUI and server backend, as [above](#no_rtems).  
3. In another terminal from *$GIT_REPO/build/src*, run: `sudo qemu-system-arm -serial null -serial mon:stdio -nographic   -M xilinx-zynq-a9 -m 256M   -net tap,ifname=qtap,script=no,downscript=no   -net nic,model=cadence_gem,macaddr=0e:b0:ba:5e:ba:12 -no-reboot  -kernel build/arm-rtems6-xilinx_zynq_a9_qemu/rtems/calc.exe`, this will launch QEMU and connect the calculator UA to the server. Once it starts printing `Data Buffer Print: ...` the connection has been established and the Calculator GUI can be utilized.  



### 2 Computers <a name="2_comp"></a>
This same setup can be accomplished with the A661 GUI/Server running on a separate physical machine (and could be extended to containers) from the UA RTEMS/QEMU backend.  
1. Ensure the A661 GUI/Server is avaible on the 2nd computer and can be launched, just like in the [Without RTEMS section](#no_rtems). It may also be valuable to ensure connectivity between the two computers as can be tested in [Troubleshooting](#connectivity).
2. Update the IP address in *a661_socket.h* in the Calculator UA to match the IP of the new server machine, as was done in the first step [here](#local), and recompile.
3. Then ensure the GUI/Server is running and simply launch the Calculator UA on the localhost in the same way as connecting to the [localhost](#local). `sudo qemu-system-arm -serial null -serial mon:stdio -nographic   -M xilinx-zynq-a9 -m 256M   -net tap,ifname=qtap,script=no,downscript=no   -net nic,model=cadence_gem,macaddr=0e:b0:ba:5e:ba:12 -no-reboot  -kernel build/arm-rtems6-xilinx_zynq_a9_qemu/rtems/calc.exe`  
4. Now you should be able to interact with the GUI on one computer, and the traffic is sent over the network to the UA running in RTEMS in QEMU which will process the calculation and send the results back.  
  

## Troubleshooting <a name="troubleshooting"></a>
### Verifying Connectivity <a name="connectivity"></a>
If there are problems connecting between the server and UA, it can be helpful to see if the network connection on port 1231 is functioning.  
1. First, on the computer going to run the A661 GUI/Server, in a terminal, execute `nc -lvp 1231`. This will listen for a TCP connection on that port and just print on the screen the raw data coming through.  
2. On the second computer (or VM, etc.) that will be running the Calculator UA run `nc -v X.X.X.X 1231` where the IP is the address of the A661 GUI/Server box. This will indicate a successful connection if it is able. You can type in either terminal and hit Enter and the raw text will be sent.   
3. Additionally, this can test the GUI/Server, by running the A661 GUI/Server in place of the `nc -lvp 1231` command, and then execute the `nc -v X.X.X.X 1231` command which will attempt to connect to the A661 GUI/Server. It will not complete a connection, but if successful the GUI/Server will print `Connection established for UA 1 from X.X.X.X`. If this is successful you know you have an open connection and any other problems are likely directly related to QEMU configuration or RTEMS compilation.  
