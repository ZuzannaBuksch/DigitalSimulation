#include "generate_packet_event.h"

#include<iostream>
#include<string>
#include<cstdlib>
#include<queue>

GeneratePacketEvent::GeneratePacketEvent(size_t time, WirelessNetwork* wireless_network, EventList* event_list, Logger* logger_ptr, int id)
  :Event(time, wireless_network), event_list_(event_list), logger_ptr_(logger_ptr), transmitter_id(id)
{
}

GeneratePacketEvent::~GeneratePacketEvent()
{
}

void GeneratePacketEvent::Execute()
{
  wireless_network_->GetTransmitters()->at(transmitter_id)->GeneratePacket(logger_ptr_, transmitter_id, time_);
  int CGPk = wireless_network_->GetTransmitters()->at(transmitter_id)->GetExpGenerator()->RndExp(wireless_network_->GetLambda()) *10;// time *10

  event_list_->push(new GeneratePacketEvent(time_ + CGPk, wireless_network_,event_list_, logger_ptr_,transmitter_id));
  
  // if buffer is not empty and the transmitter did not start listening
  if (!wireless_network_->GetTransmitters()->at(transmitter_id)->GetPackets()->empty() && wireless_network_->GetTransmitters()->at(transmitter_id)->GetCheckStatus() == false)
  {
    event_list_->push(new CheckChannelStatusEvent(time_, wireless_network_, event_list_, logger_ptr_, transmitter_id)); // start listening
  }
}
