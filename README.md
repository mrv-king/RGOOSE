# DESCRIPTION
This repository contains the source files for creating an IEC61850-related application (publisher or subscriber) on two different platforms (WINDOWS or LINX). The publisher's goal is to generate a timestamp, integrate it into the R-GOOSE message, and send it to the server over UDP. The goal of the subscriber is to receive a new R-GOOSE message sent by the publisher and calculate its latency (how long it took the message to travel from the publisher to the subscriber). The latency calculation is based on the difference between the two timestamps (publisher and subscribers) generated at the time the R-GOOSE message is sent and received. Latency tests can be performed on different communication networks (wired or wireless). To use the applications provided in the current repository, it is assumed that the communication link between the server and client devices is properly configured. Using current software, it is possible to perform a latency test over both a wired and wireless connection.  

# IMPORTANT
Before running a new latency test, both the publisher and subscriber must be time-synchronized. To do this, use third-party PTP server/client applications. As an option, the "ptpd" tool can be used. To install it, run "sudo apt -y install ptpd" (for LINUX)

# PREREQUISITES (LINUX)
Mandatory:
1. Install cmake: sudo apt-get install cmake
2. Install libboost libraries: sudo apt-get install libboost-all-dev

Optional:
- To run ptp master (LINUX), run: sudo ptpd -i eth0 -E -M
- To run ptp master (LINUX), run: sudo ptpd -i eth0 -E -S

# PREREQUISITES (WINDOWS)
Mandatory:
1. Install cmake by following [this](https://cmake.org/download/) link
2. Install MSYS2 by following [this](https://www.msys2.org/) link
3. Install libboost from MSYS2 by following [this](https://packages.msys2.org/package/mingw-w64-x86_64-boost) link
4. Make sure that paths to "cmake" and "make" are specified in the "Path" variable of the Windows environment.
   - make sure that "path_to_MSYS\msys64\mingw64\include" folder is added
   - make sure that "path_to_MSYS\msys64\usr\bin" folder is added
   - make sure that "path_to_CMAKE\CMake\bin" folder is added

Optional:
- Install PTP server/client (one alternative is presented [here](https://timemachinescorp.com/wp-content/uploads/Windows10PTPClient.pdf)).

# Connection to the 5G base station (OPTIONAL)
Detailed instructions on how to connect to the 5G base station using the QMI interface is presented [here](https://docs.sixfab.com/page/setting-up-a-data-connection-over-qmi-interface-using-libqmi)

# HOW TO PREPARE SERVER OR CLIENT APPLICATION
- Go to the 'source' folder,
- Open the 'main.cpp' file,

To design the server application:
- uncomment the 'LINUX/WINDOWS R-GOOSE SUBSCRIBER EXAMPLE' section (section 'LINUX/WINDOWS R-GOOSE PUBLISHER EXAMPLE' should be commented out).

To design the client application:
- uncomment the 'LINUX/WINDOWS R-GOOSE PUBLISHER EXAMPLE' section (section 'LINUX/WINDOWS R-GOOSE SUBSCRIBER EXAMPLE' should be commented out).
- specify the IP address of the server. For that, change the second argument in the 'iec61850_publisher' function in line 36. Do not change the port number.

# HOW TO BUILD
1. Open the command line (terminal)
2. Change the directory to the '{platform name}_release and create a new 'build' folder.
3. From the 'build' folder, run 'cmake ..' for LINUX or 'cmake .. -G "MSYS Makefiles"' for WINDOWS. Wait while the compilation is over.
4. run 'make'

# HOW TO RUN
From the 'build' folder run 'sudo ./iec61850' on LINUX or 'iec61850' on WINDOWS. Run the server application first and after that the client.

# HOW TO INTERPRET THE RESULTS
Whenever the client application is started, it spits out one RGOOSE message. When the server application receives the RGOOSE message it tries to calculate its time latency and, if the attempt is successful, prints the results in seconds. It is the user's responsibility to be sure that two devices (server and client) are properly time synchronized and that the communication line between them is stable and robust. Otherwise, the latency test will be incorrect.

# Latency test setup. Step-by-step instruction. Raspberry Pi 4
1. Update the package index: sudo apt-get update
2. Install cmake: sudo apt-get install cmake
3. Install libboost libraries: sudo apt-get install libboost-all-dev
4. Install ptpd deb package: sudo apt-get install ptpd
   - To run ptpd in master mode : sudo ptpd -i eth0 -E -M
   - To run ptpd in slave mode: sudo ptpd -i eth0 -E -S
5. In the "iec61850_rpi_release" directory, create new "build" directory: sudo mkdir build
6. Connect USB 5G modem with Raspberry Pi 4.
7. Disable "wwan0" interface: sudo ip link set wwan0 down
8. Change interface type to "raw_ip": echo 'Y' | sudo tee /sys/class/net/wwan0/qmi/raw_ip
9. Enable "wwan0" interface: sudo ip link set wwan0 up
10. Initiate registration process in 5G network: sudo qmicli -p -d /dev/cdc-wdm0 --device-open-net='net-raw-ip' --wds-start-network="apn='5gsa.lulea',ip-type=4" --client-no-release-cid
11. Get an IP address from the network: sudo udhcpc -q -f -i wwan0
12. On the device that is going to be a server during the latency test check the IP address: ifconfig wwan0
13. In the "iec61850_rpi_release" directory, go to "source" directory: cd source
14. Open the 'main.cpp' file: sudo nano main.cpp
   - To design the server application: uncomment the 'LINUX/WINDOWS R-GOOSE SUBSCRIBER EXAMPLE' section (section 'LINUX/WINDOWS R-GOOSE PUBLISHER EXAMPLE' should be commented out).
   - To design the client application: uncomment the 'LINUX/WINDOWS R-GOOSE PUBLISHER EXAMPLE' section (section 'LINUX/WINDOWS R-GOOSE SUBSCRIBER EXAMPLE' should be commented out). Specify the IP address of the server (the one that was shown in step 12). For that, 
     change the second argument in the 'iec61850_publisher' function in line 36. Do not change the port number.
15. In the "iec61850_rpi_release" directory, change the directory to build: cd build
16. Generate Makefile: cmake ..
17. Generate binary file: make
18. Run latency test on the server/subscriber (If the server starts successfully the application prints "Server started..."): sudo ./iec61850. 
19. Run latency test on the client/publisher: sudo ./iec61850
20. The server/subscriber application should print out the latency value of the package that has been sent (value printed in seconds)
21. To run a series of latency tests, the server should be run once, but the "iec61850_publisher" function in the client/publisher application should be called in the loop as many times as needed.
