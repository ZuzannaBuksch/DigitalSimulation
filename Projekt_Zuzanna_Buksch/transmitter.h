// Class that represents transmitter

#ifndef TRANSMITTER_H
#define TRANSMITTER_H

#include <queue>
#include<iostream>

#include "channel.h"
#include "packet.h"
#include "logger.h"
#include "wireless_network.h"
#include "generators.h"

class WirelessNetwork;
class Channel;

class Transmitter 
{
public:
	Transmitter(int id, int uniform_seed, int exp_seed, int r_seed);
	~Transmitter();

	int GetTransmitterId();
	void SetTransmitterId(int tx_id); 

	size_t GetWaitingTime();
	void SetWaitingTime(size_t w_time);

	//bool GetAckReceved();
	//void SetAckReceved(bool ack_status);
	
	bool GetCheckStatus();
	void SetCheckStatus(bool status);

	int GetLostPackets();
	void SetLostPackets();

	int GetSentPackets();
	void SetSentPackets();

	double GetPacketErrorRate();
	void SetPacketErrorRate(double rate);

	Generators* GetUniformGenerator();
	Generators* GetExpGenerator();
	Generators* GetRGenerator();

	std::queue<Packet*>* GetPackets();

	// metody
	void GeneratePacket(Logger* logger, int tx_id, size_t time);
	void StartTransmission(Logger* logger, Packet* packet, WirelessNetwork* wn_ptr, size_t time);
	

private:
	int transmitter_id; // transmitter identification number
	size_t waiting_time = 0; // time of channel idling 
	//bool ack_receved = false; // true - ack recevd
	bool check_status = false; // false - the transmitter is not listening currently
	//generators
	Generators* uniform_generator = nullptr;
	Generators* exp_generator = nullptr;
	Generators* r_generator = nullptr;

	std::queue<Packet*> packets_;  // queue of packets 
	
	//size_t generate_timer = -1;
	//size_t transmission_timer_ = -1;

	double packet_error_rate = 0;
	int lost_packets = 0; 
	int sent_packets = 0;
};

#endif

