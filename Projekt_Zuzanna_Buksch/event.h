#ifndef EVENT_H
#define EVENT_H

#include <queue>
#include "wireless_network.h"
#include <functional>

class Event
{
public:
	typedef std::priority_queue<Event*, std::vector<Event*>, std::function<bool(Event*, Event*)>> EventList; // priority queue of time events
	
	explicit Event(size_t time, WirelessNetwork* wireless_network_ptr);
	~Event();

	virtual void Execute()=0;
	virtual int GetId() { return NULL; };

	WirelessNetwork* GetWirelessNetPtr() { return wireless_network_; };

	size_t get_time() { return time_; }

protected:
	size_t time_;
	WirelessNetwork* wireless_network_ = nullptr;
};


#endif EVENT_H