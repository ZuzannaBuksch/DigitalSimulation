#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "wireless_network.h"
#include "event.h"
#include "generate_packet_event.h"
#include "check_channel_status_event.h"
#include "end_transmission_packet_event.h"
#include "end_transmission_ack_event.h"


class Simulator
{
public:
	explicit Simulator(WirelessNetwork *wieless_network_ptr);
	~Simulator();

  void M2(int time);
  void StepInto();
  bool SelectMode(int mode);

private:
  size_t clock_ = 0;
  WirelessNetwork* wireless_network_ = nullptr;
};

#endif SIMULATOR_H

