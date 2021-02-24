#include "transmitter.h"

Transmitter::Transmitter(int id, int uniform_seed, int exp_seed, int r_seed)
{
  transmitter_id = id;
  uniform_generator = new Generators(uniform_seed);
  exp_generator = new Generators(exp_seed);
  r_generator = new Generators(r_seed);
}

Transmitter::~Transmitter()
{
}

int Transmitter::GetTransmitterId()
{
  return transmitter_id; 
}

void Transmitter::SetTransmitterId(int tx_id)
{
    transmitter_id = tx_id;
}


size_t Transmitter::GetWaitingTime()
{
  return waiting_time;
}

void Transmitter::SetWaitingTime(size_t difs)
{
  waiting_time = difs;
}

/*bool Transmitter::GetAckReceved()
{
  return ack_receved;
}

void Transmitter::SetAckReceved(bool ack_status)
{
  ack_receved = ack_status;
}*/



bool Transmitter::GetCheckStatus()
{
  return check_status;
}

void Transmitter::SetCheckStatus(bool status)
{
  check_status = status;
}

int Transmitter::GetLostPackets()
{
  return lost_packets;
}

void Transmitter::SetLostPackets()
{
  ++lost_packets;
}

int Transmitter::GetSentPackets()
{
  return sent_packets;
}

void Transmitter::SetSentPackets()
{
  ++sent_packets;
}

double Transmitter::GetPacketErrorRate()
{
  return packet_error_rate;
}

void Transmitter::SetPacketErrorRate(double rate)
{
  packet_error_rate = rate;
}

Generators* Transmitter::GetUniformGenerator()
{
  return uniform_generator;
}

Generators* Transmitter::GetExpGenerator()
{
  return exp_generator;
}

Generators* Transmitter::GetRGenerator()
{
  return r_generator;
}

std::queue<Packet*>* Transmitter::GetPackets()
{
  return &packets_;
}

void Transmitter::GeneratePacket(Logger *logger, int temp, size_t time)
{
  static size_t id = 0; // id of new package
  ++id;
  auto packet = new Packet(id, GetUniformGenerator()->Rnd(1,10) *10, temp, time); // package duration 1, 2, ... 10ms -> 10, 20, ..., 100
  packets_.push(packet);
  //logger->Info("Transmitter "+ std::to_string(temp)+ ", generated packet id: "+ std::to_string(id)+ ", packet transmission time: "+ std::to_string(packets_.front()->GetCtpkTime()));
}

void Transmitter::StartTransmission(Logger* logger, Packet* packet, WirelessNetwork* wn_ptr, size_t time)
{

  //logger->Info("Transmitter " + std::to_string(transmitter_id) +
   // " started transmission of packet "+ std::to_string(packets_.front()->GetPacketId()) + ", transmission time: "+ std::to_string(packets_.front()->GetCtpkTime()));
  wn_ptr->GetChannel()->GetPacketsCurrentlyTransmitting()->push_back(packet);
  if (packets_.front()->GetTransmissionStatus() == false)
  {
    packets_.front()->SetTransmissionStatus(true);
    if(wn_ptr->GetAllPacketsCorrectlySent() >= wn_ptr->GetInitialPhase())
      wn_ptr->SetTotalWaitingTime(time - (packets_.front()->GetPacketGenerationTime()));
  }
}

  


