#ifdef __linux__
#include <cstdlib>
#include <memory>
#include <pthread.h>
#include <utility>
#include <string>
#include <netpacket/packet.h>
#include <net/ethernet.h>
#include <boost/format.hpp>
#endif

#include <iostream>
#include <sstream>
#include <cstring>
#include <fstream>

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>

#include <chrono>
#include <stdio.h>
#include <time.h>

#include <thread>
#include "goose_header.h"
#include "r_header.h"

int main(int argc, char **argv)
{
    //
    // **************  LINUX/WINDOWS R-GOOSE PUBLISHER EXAMPLE  *************************
    //
    /*boost::asio::io_service io_service;

    R_pub iec61850_publisher(io_service, "192.168.10.86", "8080");
	iec61850_publisher.send_rgoose();

    return 0;*/
	//
    // ***************************************************************************
    //
	
	//
    // **************  LINUX/WINDOWS R-GOOSE SUBSCRIBER EXAMPLE  *************************
    //

    try {
        boost::asio::io_service io_service;
        R_sub server{io_service};
        io_service.run();
    } catch (const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }

    return 0;
    //
    // ***************************************************************************
    //

}
