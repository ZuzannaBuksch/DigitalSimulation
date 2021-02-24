#ifndef END_TRANSMISSION_ACK_EVENT_H
#define END_TRANSMISSION_ACK_EVENT_H

#include "event.h"
#include "logger.h"
#include "wireless_network.h"
#include "check_channel_status_event.h"

class Transmitter;

class EndTransmissionAckEvent
	: public Event
{
public:
	EndTransmissionAckEvent(size_t time, WirelessNetwork* wireless_network, EventList* event_list, Logger* logger_ptr, int id);
	~EndTransmissionAckEvent();

	int GetId() override { return transmitter_id; };

	void Execute() override;

private:
	Logger* logger_ptr_ = nullptr;
	EventList* event_list_ = nullptr;
	int transmitter_id;

};

#endif END_TRANSMISSION_ACK_EVENT_H