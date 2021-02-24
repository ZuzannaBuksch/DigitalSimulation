#include "end_transmission_packet_event.h"

EndTransmissionPacketEvent::EndTransmissionPacketEvent(size_t time, WirelessNetwork* wireless_network, EventList* event_list, Logger* logger_ptr, int id)
  :Event(time, wireless_network), event_list_(event_list), logger_ptr_(logger_ptr), transmitter_id(id)
{
}

EndTransmissionPacketEvent::~EndTransmissionPacketEvent()
{
}

void EndTransmissionPacketEvent::Execute()
{

	if (wireless_network_->GetChannel()->GetPacketsCurrentlyTransmitting()->size() > 1)
		wireless_network_->GetChannel()->SetCollisionStatus(true);

	int ter = wireless_network_->GetChannel()->GetGeneratorTer()->RndZeroOne(0.8);
	//logger_ptr_->Info("Transmitter " + std:: to_string(transmitter_id) +" ended transmission of packet");

	if (wireless_network_->GetChannel()->GetCollisionStatus() == true || ter == 0) // if detected collision od ter error
	{
		/*
		if(ter==0)
			logger_ptr_->Info("TER detected");
		if(wireless_network_->GetChannel()->GetCollisionStatus() == true)
			logger_ptr_->Info("Collision detected");

		logger_ptr_->Info("ACK not sent");
		*/
		
		wireless_network_->GetChannel()->SetSentAck(false);
		wireless_network_->GetChannel()->GetPacketsCurrentlyTransmitting()->pop_back();

		if (wireless_network_->GetChannel()->GetPacketsCurrentlyTransmitting()->empty()) // in case of collision, the channel will be busy for the duration of the longest package
		{
			wireless_network_->GetChannel()->SetChannelStatus(true);
			wireless_network_->GetChannel()->SetCollisionStatus(false);
		}
		event_list_->push(new EndTransmissionAckEvent(time_ + (wireless_network_->kAckTime), wireless_network_, event_list_, logger_ptr_, transmitter_id)); // scheduling end of transmission
	}
	else
	{
		//logger_ptr_->Info("ACK sent");
		wireless_network_->GetChannel()->SetSentAck(true); // true - ACK sent
		event_list_->push(new EndTransmissionAckEvent(time_ + (wireless_network_->kAckTime), wireless_network_, event_list_, logger_ptr_, transmitter_id));
	}

}
