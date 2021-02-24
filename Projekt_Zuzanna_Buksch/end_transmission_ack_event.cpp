#include "end_transmission_ack_event.h"


#include <iostream>
#include <fstream>
#include <iterator>

EndTransmissionAckEvent::EndTransmissionAckEvent(size_t time, WirelessNetwork* wireless_network, EventList* event_list, Logger* logger_ptr, int id)
  :Event(time, wireless_network), event_list_(event_list), logger_ptr_(logger_ptr), transmitter_id(id)
{
}

EndTransmissionAckEvent::~EndTransmissionAckEvent()
{
}

void EndTransmissionAckEvent::Execute()
{
	if (wireless_network_->GetChannel()->GetSentAck() == true)
	{
		wireless_network_->SetAllPacketsCorrectlySent();
		if (wireless_network_->GetAllPacketsCorrectlySent() >= wireless_network_->GetInitialPhase())
		{
			wireless_network_->GetTransmitters()->at(transmitter_id)->SetSentPackets();
			wireless_network_->SetNumberOfPacketsCorrectlySent();
			wireless_network_->SetNumberOfRetransmission(wireless_network_->GetTransmitters()->at(transmitter_id)->GetPackets()->front()->GetLrNumber());
			int delay = time_ - wireless_network_->kAckTime - (wireless_network_->GetTransmitters()->at(transmitter_id)->GetPackets()->front()->GetPacketGenerationTime());
			wireless_network_->SetTotalDelayOfPackets(delay);
			wireless_network_->SaveDataForInitialPhase();
		}
	
		//logger_ptr_->Info("Transmitter " + std::to_string(transmitter_id) + " ACK received ");
		wireless_network_->GetTransmitters()->at(transmitter_id)->GetPackets()->pop();
		wireless_network_->GetChannel()->GetPacketsCurrentlyTransmitting()->pop_back();
		wireless_network_->GetChannel()->SetChannelStatus(true);
		if (wireless_network_->GetTransmitters()->at(transmitter_id)->GetPackets()->empty()) // if transmitter buffer is empty, transmitter is not listening 
		{
			wireless_network_->GetTransmitters()->at(transmitter_id)->SetCheckStatus(false);
		}
		else
		{
			event_list_->push(new CheckChannelStatusEvent(time_ +10, wireless_network_, event_list_, logger_ptr_, transmitter_id)); // if buffer is not empty
		}
	}

	else // if ACK not receved
	{
		//logger_ptr_->Info("Transmitter " + std::to_string(transmitter_id) + " ACK not received");
		int lr_number_temp = wireless_network_->GetTransmitters()->at(transmitter_id)->GetPackets()->front()->GetLrNumber() + 1;

		if (lr_number_temp < wireless_network_->kLR) // if number of retransmission <= LR (10)
		{
			wireless_network_->GetTransmitters()->at(transmitter_id)->GetPackets()->front()->SetLrNumber(lr_number_temp);
			int R = wireless_network_->GetTransmitters()->at(transmitter_id)->GetRGenerator()->Rnd(0, std::pow(2, lr_number_temp) - 1)*10;
			//logger_ptr_->Info("R: " + std::to_string(R));
			int crp_time = R * (wireless_network_->GetTransmitters()->at(transmitter_id)->GetPackets()->front()->GetCtpkTime());
			//logger_ptr_->Info("LR: " + std::to_string(wireless_network_->GetTransmitters()->at(transmitter_id)->GetPackets()->front()->GetLrNumber()));
			//logger_ptr_->Info("CRP time: " + std::to_string(crp_time));
			event_list_->push(new CheckChannelStatusEvent(time_ + (crp_time), wireless_network_, event_list_, logger_ptr_, transmitter_id)); // zaplanuj nowe zdarzenie nas³uchiwania kana³u 
	
		}
		else
		{
			if (wireless_network_->GetAllPacketsCorrectlySent() >= wireless_network_->GetInitialPhase())
			{
				wireless_network_->GetTransmitters()->at(transmitter_id)->SetLostPackets();
				wireless_network_->SetNumberOfRetransmission(wireless_network_->GetTransmitters()->at(transmitter_id)->GetPackets()->front()->GetLrNumber());
			}
			
			wireless_network_->GetTransmitters()->at(transmitter_id)->GetPackets()->pop(); // remove package from buffer

			if (wireless_network_->GetTransmitters()->at(transmitter_id)->GetPackets()->empty()) // if transmitter buffer is empty, transmitter is not listening 
			{
				wireless_network_->GetTransmitters()->at(transmitter_id)->SetCheckStatus(false);
			}
			else
			{
				event_list_->push(new CheckChannelStatusEvent(time_, wireless_network_, event_list_, logger_ptr_, transmitter_id)); // if buffer is not empty
																																																														// schedule to listening 
			}
		}
	}
	if (wireless_network_->GetAllPacketsCorrectlySent() >= wireless_network_->GetInitialPhase())
	{
		if (wireless_network_->GetTransmitters()->at(transmitter_id)->GetSentPackets()!=0)
		{
			double rate = (double)wireless_network_->GetTransmitters()->at(transmitter_id)->GetLostPackets() / wireless_network_->GetTransmitters()->at(transmitter_id)->GetSentPackets();
			wireless_network_->GetTransmitters()->at(transmitter_id)->SetPacketErrorRate(rate);
		}
		else
		{
			wireless_network_->GetTransmitters()->at(transmitter_id)->SetPacketErrorRate(wireless_network_->GetTransmitters()->at(transmitter_id)->GetLostPackets());
		}
		wireless_network_->SaveAverageNumberOfRetransmission(time_, logger_ptr_);

		/*
		std::cout<<"\nNumber of packets: \nSent: " +std::to_string(wireless_network_->GetTransmitters()->at(transmitter_id)->GetSentPackets())+
		"\nLost: "+std::to_string(wireless_network_->GetTransmitters()->at(transmitter_id)->GetLostPackets())+
		"\nPacket error rate: "+std::to_string(wireless_network_->GetTransmitters()->at(transmitter_id)->GetPacketErrorRate());
		*/
		
	}

}
