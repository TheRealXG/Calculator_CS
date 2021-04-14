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
	

## Overview <a name="overview"></a>
This is a sample calculator application demonstrating implementation of a Server Client configuration between a GUI/Server and a Calculating Backend (User Application). This example demonstrates usage of A661 and FACE standards.  
The GUI and A661 server are a single binary already compiled. Source code is provided for the calculating backend which must be compiled.  
This can be run in several manners. Both the server and backend can run on the same [localhost](#local), or they can run on [two separate computers](#2_comp). The focus of this document and repository is running the calculator backend (UA) in an RTOS (RTEMS for this example) and the GUI/Server running on a Linux general purpose computer. It could also be simply run with both applications [in Linux](#no_rtems). This document currently covers running the UA in a HW emulated environment (QEMU), but the same application could theoretically be run on actual hardware, such as the Xilinx Ultra96 Cortex A53 board, with the same results. This example could also be extended to run both applications inside of containers.


## Setup <a name="setup"></a>
This section will cover setting up a new RTEMS 6 install, adding the LIBBSD networking package, and building a sample BSP (Xilinx A9 QEMU) with this LIBBSD networking package. Finally it will cover compiling the application and some simple network configuration options.  

### RTEMS Install <a name="install"></a>
  a. This has been testing Ubuntu 18.04 and 20.10 though additionally required dependencies may vary. With Ubuntu 18.04 LTS all necessary dependencies to install RTEMS should be handled in the install process, but if anything is found, simply use the "apt-install" functionality to install them.  
  b.  `export PREFIX=$HOME/quick-start/rtems/6`  
  c. `mkdir -p $HOME/quick-start/src`  
  d. `cd $HOME/quick-start/src/`  
  e. `git clone git://git.rtems.org/rtems-source-builder.git rsb`  
    (Tested on commit 62363ba)  
  f. `git clone git://git.rtems.org/rtems.git`  
    (Tested on commit fd639b8abf)  
  g. `cd rsb/rtems/`  
  h. `../source-builder/sb-set-builder --prefix=$PREFIX 6/rtems-arm`  
  i. `export PATH=$HOME/quick-start/rtems/6/bin:$PATH`  
  j. `arm-rtems6-gcc --version`  
  	1. This command verifies the install worked.  
  k. `cd $HOME/quick-start/src/rtems`  
  l. `./bootstrap -c && ./rtems-bootstrap`  

#### Install BSP
  a. In `$HOME/quick-start/src/rtems` run `./waf bsp_list` to see the list of supported BSPs. This example will use the `xilinx_zynq_a9_qemu` BSP.  
  b. Create a text file called `config.ini` with the following contents: 
  ```
  [arm/xilinx_zynq_a9_qemu]
  BUILD_TESTS = True
  BUILD_SAMPLES = True
  RTEMS_NETWORKING = False
  RTEMS_POSIX_API = True
  ```  
  c. Next, the BSP install process will be configured and run.  
  d. `./waf configure --prefix=$PREFIX`  
  e. `./waf`  
  f. `./waf install`  
  g. The BSP is installed to `$HOME/quick-start/rtems/6/arm-rtems6/xilinx_zynq_a9_qemu/` and the test programs are installed in `$HOME/quick-start/src/rtems/build/arm/xilinx_zynq_a9_qemu/testsuites/`  


### RTEMS LIBSBSD <a name="libbsd"></a>
LIBBSD is a FreeBSD Networking library that has been ported to RTEMS to replace the legacy RTEMS networking stack. This must be installed as a separate add-on. Because it replaces the legacy RTEMS Networking the BSP must be built with the RTEMS_NETWORKING OFF (as was done in the step above) and the LIBBSD library takes the place of it with some additinoal wscript/waf configuration options.  
  a. `cd $HOME/quick-start/src`  
  b. `git clone git://git.rtems.org/rtems-libbsd.git`  
  c. `cd rtems-libbsd`  
  d. `git checkout 6-freebsd-12`  
    (Tested on commit aef7a74b9)  
  e. `git submodule init`  
  f. `git submodule update rtems_waf`  
  g.
  ```
  ./waf configure --prefix=$PREFIX \
    --rtems-bsps=arm/xilinx_zynq_a9_qemu \
    --buildset=buildset/default.ini
  ```  
  h. `./waf`  
  i. `./waf install`  
  j. This will install LIBBSD to the Prefix location and make it available for use when compiling RTEMS applications.  


### Compiling <a name="compiling"></a>
Now the calculator UA application must be compiled for the BSP to be used. Since this Git repository already has the appropriate scripts and code changes necessary to compile the generated code for RTEMS and LIBBSD, if checked out on the latest master commit, the following can be executed.  
  a. `cd $GIT_REPO/build/src/`  
  b. `./waf configure --rtems=$HOME/quick-start/rtems/6 --rtems-bsp=arm/xilinx_zynq_a9_qemu --rtems-libbsd=$HOME/quick-start/rtems/6`  
    1. At the end of the configuration it will show, among other things:  
    ```
    Checking for RTEMS_NETWORKING               : no  
    RTEMS LibBSD                                : arm/xilinx_zynq_a9_qemu  
    ```  
  c. `./waf`  

#### Changes That Were Made
The steps abve are all that is needed to compile the calculator UA for use in RTEMS and QEMU with this BSP since it is already setup in repository. This will detail some of the changes that were made to use LIBBSD and RTEMS for this application. This is not necessarily comprehensive, but highlights some of the changes made.  
  
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
  
These items should generally get the code to compile.  
  

### Network Configuration <a name="network"></a>
To run this with RTEMS and QEMU there is additional networking configuration to allow QEMU to connect to the network. This is done through a Tap. This is a virtual Ethernet connector that is bridged with the ethernet connection on the QEMU host machine (real or VM) to allow them to share an IP connection and connect locally or out of the localhost.  
  a. 


## Running the Calculator <a name="running"></a>
The second paragraph text  


### Without RTEMS <a name="no_rtems"></a>
Run both on Linux. Need server to run on Linx before the next 2 steps (may need to use ldd A661server to find missing GL dependencies). Checkout 0e44caa then make clean all


### Localhost <a name="local"></a>
Need to install QEMU first then run script to setup network tap


### 2 Computers <a name="2_comp"></a>
Get 2 computers. Find IP address. Maybe an "nc -lvp" command to verify connectivity. Then run


