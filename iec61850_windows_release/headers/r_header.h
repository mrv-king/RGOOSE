#ifndef R_HEADER_H
#define R_HEADER_H

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

class R_pub
{
public:
	R_pub(
		boost::asio::io_service& io_service, 
		const std::string& host, 
		const std::string& port
	);
	~R_pub();
	void send(const std::string& msg);
	void send_rgoose();

private:
	boost::asio::io_service& io_service_;
	boost::asio::ip::udp::socket socket_;
	boost::asio::ip::udp::endpoint endpoint_;
};

class R_sub {
public:
    R_sub(boost::asio::io_service& io_service);
	
private:
    void startReceive();
    void handleReceive(const boost::system::error_code& error,std::size_t bytes_transferred);

    boost::asio::ip::udp::socket _socket;
    boost::asio::ip::udp::endpoint _remoteEndpoint;
    std::array<char, 300> _recvBuffer;
    std::chrono::system_clock::time_point tp;
    std::chrono::system_clock::duration current_time;
    std::stringstream ss;
    std::string message;
    goose_header goose_obj;
    char time_buff[100];
};

#endif
