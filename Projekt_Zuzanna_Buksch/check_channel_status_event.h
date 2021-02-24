#ifndef CHECK_CHANNEL_STATUS_EVENT_H
#define CHECK_CHANNEL_STATUS_EVENT_H

#include "event.h"
#include "logger.h"
#include "wireless_network.h"
#include "end_transmission_packet_event.h"


class Transmitter;


class CheckChannelStatusEvent
	: public Event
{
public:
	CheckChannelStatusEvent(size_t time, WirelessNetwork* wireless_network, EventList* event_list, Logger* logger_ptr, int id);
	~CheckChannelStatusEvent();
	int GetId() override { return transmitter_id; };


	void Execute() override;

private:
	Logger* logger_ptr_ = nullptr;
	EventList* event_list_ = nullptr;
	int transmitter_id; 
};



#endif CHECK_CHANNEL_STATUS_EVENT_H
