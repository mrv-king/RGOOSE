# DESCRIPTION
This repository contains the source files for creating an IEC61850-related application (publisher or subscriber) on two different platforms (WINDOWS or LINX). The publisher's goal is to generate a timestamp, integrate it into the R-GOOSE message, and send it to the client over UDP. The goal of the subscriber is to receive a new R-GOOSE message sent by the publisher and calculate its latency (how long it took the message to travel from the publisher to the subscriber). The latency calculation is based on the difference between the two timestamps (publisher and subscribers) generated at the time the R-GOOSE message is sent and received.

# IMPORTANT
Before running a new latency test, both the publisher and subscriber must be synchronized. To do this, use third-party PTP server/client applications. As an option, the "ptpd" tool can be used. To install it, run "sudo apt -y install ptpd" (for LINUX)

# Prerequisites (LINUX)
Mandatory:
1. Install cmake: sudo apt-get install cmake
2. Install libboost libraries: sudo apt-get install libboost-all-dev

Optional:
- To run ptp server (LINUX), run: sudo ptpd -i eth0 -E -M
- To run ptp client (LINUX), run: sudo ptpd -i eth0 -E -S

# Prerequisites (WINDOWS)
1. Install cmake by following [this](https://cmake.org/download/) link
2. Install MSYS2 by following [this](https://www.msys2.org/) link
3. Install libboost from MSYS2 by following [this](https://packages.msys2.org/package/mingw-w64-x86_64-boost) link
4. Make sure that paths to "cmake" and "make" are specified in the "Path" variable of the Windows environment.

# HOW TO PREPARE SERVER OR CLIENT APPLICATION
- Go to the 'source' folder,
- Open the 'main.cpp' file,

To design the server application:
- uncomment the 'LINUX/WINDOWS R-GOOSE SUBSCRIBER EXAMPLE' section (section 'LINUX/WINDOWS R-GOOSE PUBLISHER EXAMPLE' should be commented out).

To design the client application:
- uncomment the 'LINUX/WINDOWS R-GOOSE PUBLISHER EXAMPLE' section (section 'LINUX/WINDOWS R-GOOSE SUBSCRIBER EXAMPLE' should be commented out).
- specify the IP address of the server. For that, change the second argument in the 'iec61850_publisher' function in line 36. Do not change the port number.

# HOW TO BUILD
1. Open the command line
2. Open {platform name}_release folder.
3. change the directory to 'build' folder
4. run 'cmake ..' for LINUX or 'cmake .. -G "MSYS Makefiles"' for WINDOWS
5. run 'make'

# HOW TO RUN
From the 'build' folder run 'sudo ./iec61850' on LINUX or 'iec61850' on WINDOWS. Run the server application first and after that the client.

# HOW TO INTERPRET THE RESULTS
Whenever the client application connects to the server, it spits out one RGOOSE message. When the server application receives the RGOOSE message it tries to calculate its time latency and, if the attempt is successful, prints the results in seconds. It is the user's responsibility to be sure that two devices (server and client) are properly synchronized and that the communication line between them is stable and robust. Otherwise, the latency test will be incorrect.
