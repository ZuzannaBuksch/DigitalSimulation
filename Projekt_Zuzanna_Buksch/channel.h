// Class that includes informations about transmission channel

#ifndef CHANNEL_H
#define CHANNEL_H

#include <vector>
#include "packet.h"
#include "generators.h"

class Channel
{
public:
	Channel(int a);
	~Channel();

	bool GetChannelStatus();
	void SetChannelStatus(bool status);

	bool GetCollisionStatus();
	void SetCollisionStatus(bool status);

	bool GetSentAck();
	void SetSentAck(bool status);


	Generators* GetGeneratorTer();

	std::vector<Packet*>* GetPacketsCurrentlyTransmitting();

private:
	std::vector<Packet*>packets_currently_transmitting_; // vector of packets which is in channel

	bool channel_status = true; // true - no packet in channel, false - packet/packets in channel
	bool collision_status = false; // true - collision detected
	bool sent_ack = false;
	 
	Generators* generator_ter = nullptr;

};

#endif