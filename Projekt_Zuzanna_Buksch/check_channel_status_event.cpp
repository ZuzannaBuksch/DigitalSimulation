#include "check_channel_status_event.h"

CheckChannelStatusEvent::CheckChannelStatusEvent(size_t time, WirelessNetwork* wireless_network, EventList* event_list, Logger* logger_ptr, int id)
  :Event(time, wireless_network), event_list_(event_list), logger_ptr_(logger_ptr), transmitter_id(id)
{
}

CheckChannelStatusEvent::~CheckChannelStatusEvent()
{
}



void CheckChannelStatusEvent::Execute()
{
  if (!wireless_network_->GetTransmitters()->at(transmitter_id)->GetPackets()->empty())
  { 
    static size_t time_of_start_transmission = 0; // auxiliary variable that enables to checked if another transmitter started 
                                                  //transmitting at the same time
    wireless_network_->GetTransmitters()->at(transmitter_id)->SetCheckStatus(true); // the transmitter has already started listening

    if (wireless_network_->GetChannel()->GetChannelStatus() == true) // if channel is idle
    {
      //logger_ptr_->Info("Channel is idle");

      if (wireless_network_->GetTransmitters()->at(transmitter_id)->GetWaitingTime() > wireless_network_->kDifsTime) // if channel is idle more than 5ms -> 50
      {
        time_of_start_transmission = time_;
        wireless_network_->GetChannel()->SetChannelStatus(false);
        wireless_network_->GetTransmitters()->at(transmitter_id)->SetWaitingTime(0); // set listening time to 0
        auto packet_ptr = wireless_network_->GetTransmitters()->at(transmitter_id)->GetPackets()->front();
        wireless_network_->GetTransmitters()->at(transmitter_id)->StartTransmission(logger_ptr_, packet_ptr, wireless_network_, time_); // start transmission of package
        size_t transmission_time = wireless_network_->GetTransmitters()->at(transmitter_id)->GetPackets()->front()->GetCtpkTime();
        event_list_->push(new EndTransmissionPacketEvent(time_ + transmission_time, wireless_network_, event_list_, logger_ptr_, transmitter_id));
       }

      else // if channel is idle less than 5 ms -> 50
      {
        //logger_ptr_->Info("Transmitter "+std::to_string(transmitter_id)+", waiting time: " + std::to_string(wireless_network_->GetTransmitters()->at(transmitter_id)->GetWaitingTime()));
        size_t temp = wireless_network_->GetTransmitters()->at(transmitter_id)->GetWaitingTime() + (wireless_network_->kWaitTime);
        wireless_network_->GetTransmitters()->at(transmitter_id)->SetWaitingTime(temp); // increase the listening time by 0.5 ms -> 5
        event_list_->push(new CheckChannelStatusEvent(time_ + (wireless_network_->kWaitTime), wireless_network_, event_list_, logger_ptr_, transmitter_id));
      }
    }

    else // if channel is busy
    {
      if (wireless_network_->GetTransmitters()->at(transmitter_id)->GetWaitingTime() > wireless_network_-> kDifsTime && time_of_start_transmission == time_) // jeœli pakiet nas³uchiwa³ ju¿ > difs
      {
        wireless_network_->GetTransmitters()->at(transmitter_id)->SetWaitingTime(0); // set listening time to 0
        auto packet_ptr = wireless_network_->GetTransmitters()->at(transmitter_id)->GetPackets()->front();
        wireless_network_->GetTransmitters()->at(transmitter_id)->StartTransmission(logger_ptr_, packet_ptr, wireless_network_, time_); // start transmission  
        size_t transmission_time = wireless_network_->GetTransmitters()->at(transmitter_id)->GetPackets()->front()->GetCtpkTime();
        event_list_->push(new EndTransmissionPacketEvent(time_ + transmission_time, wireless_network_, event_list_, logger_ptr_, transmitter_id));
      }
      else
      {
        //logger_ptr_->Info("Channel is busy...");
        wireless_network_->GetTransmitters()->at(transmitter_id)->SetWaitingTime(0);
        event_list_->push(new CheckChannelStatusEvent(time_ + (wireless_network_->kWaitTime), wireless_network_, event_list_, logger_ptr_, transmitter_id));
      }
    }
  }
  else
  {
    wireless_network_->GetTransmitters()->at(transmitter_id)->SetCheckStatus(false);
  } 
}
