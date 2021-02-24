#ifndef GENERATE_PACKET_EVENT_H
#define GENERATE_PACKET_EVENT_H

#include "event.h"
#include "logger.h"
#include "wireless_network.h"
#include "check_channel_status_event.h"

class Transmitter;

class GeneratePacketEvent 
	: public Event
{
public:

	GeneratePacketEvent(size_t time, WirelessNetwork* wireless_network, EventList* event_list, Logger* logger_ptr, int id);
	~GeneratePacketEvent();

	int GetId() override { return transmitter_id; };
	void Execute() override;

private:
	Logger* logger_ptr_ = nullptr;
	EventList* event_list_ = nullptr;
	int transmitter_id; 
};


#endif GENERATE_PACKET_EVENT_H
