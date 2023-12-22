#ifndef GOOSE_HEADER_H
#define GOOSE_HEADER_H

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <iomanip>
#include <time.h>
#include <chrono>
#include <cstddef>

#ifdef _WIN32
#include <pcap.h>
#endif

class goose_header
{	
	public:
		struct g_struct{
			std::string gosbRef;
			std::string dataset;
			std::string goid;
			int timeAllowedtoLive;
			int stNum;
			int sqNum;
			bool simflag;
			int confRev;
			bool ndsComflag;
		};

		#ifdef _WIN32
	    typedef pcap_t ethII;
		char errbuf[256];
		
		ethII* socket_open(char* dev);
		void socket_close(ethII* socket_header);
		int send_goose_frame(ethII* socket_header, const u_char* goose_frame_ptr, int goose_frame_length);
		#endif

		void initialize_frame(const std::string src_addr, const std::string dst_addr, g_struct user_structure);
		std::vector<uint8_t> get_ethernetII_frame();
        std::vector<uint8_t> get_r_goose_frame();
		void set_goose_numDatSetEntries(const int confRev);
		void set_goose_allData_ID();
		void set_goose_value_type_int(const int value);
		void set_goose_value_type_binaryTime(const int value);
        void get_currentTime_from_UTC_frame(std::string utc_time, std::chrono::system_clock::duration total);
		void generate_currentTime_in_UTC_frame(std::vector<uint8_t> *frame);
			
	private:
		uint8_t convert_int2hex(int value);
		void calculate_goose_frame_length(int value);		
		std::vector<uint8_t> ethernetII_frame;
		std::vector<uint8_t> goose_frame;
		int it_goosePdu = 0;
		int it_allData = 0;	
		short it_utcTime = 0;
		int alldata_bit_counter = 0;
		int goosePdu_bit_counter = 0;
		
		void set_destination_address(const std::string dst_addr);
		void set_source_address(const std::string src_addr);
		void set_EthernetII_as_virtual_LAN();
		void set_VLAN_properties();
		void set_VLAN_type_as_GOOSE();		
		void set_GOOSE_APPID();
		void set_GOOSE_Reserved_bytes();
		void set_GOOSE_PDU_ID();
		void set_GOOSE_CBREFID();
		void set_gosbRef(const std::string gosbRef);
		void set_goosePDU_Time2Live_ID();
		void set_timeAllowedtoLive(const int timeAllowedtoLive);		
		void set_goose_dataset_ID();
		void set_goose_dataset(const std::string dataset);
		void set_goose_goid_ID();
		void set_goose_goid(const std::string goid);
		void set_goose_t_ID();	
		void generate_UTC_frame();
		void set_goose_stNum();
		void set_goose_stNumValue(const int intstNum);
		void set_goose_sqNum();
		void set_goose_sqNumValue(const int sqNum);
		void set_goose_simulation();
		void set_goose_simulation_flag(const bool simflag);		
		void set_goose_confRev_ID();
		void set_goose_confRev(const int confRev);
		void set_goose_ndsCom_ID();
		void set_goose_ndsCom_flag(const bool ndsComflag);							
		void set_goose_numDatSetEntries_ID();
		void get_goose_frame();
};

#ifdef _WIN32
void got_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *packet);
#endif

#endif

