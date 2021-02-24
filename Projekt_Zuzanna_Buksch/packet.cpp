#include "packet.h"

Packet::Packet(int packet_id, int ctpk, int tx_rx_id, size_t time) : packet_id_(packet_id), ctpk_time(ctpk), transmitter_receiver_id(tx_rx_id),
lr_number(0), packet_generation_time(time)
{
}

Packet::~Packet()
{
}

size_t Packet::GetPacketId() const
{
  return packet_id_;
}

int Packet::GetLrNumber()
{
  return lr_number;
}

void Packet::SetLrNumber(int lr)
{
  lr_number = lr;
}

int Packet::GetTransmitterReceiverId()
{
  return transmitter_receiver_id;
}

size_t Packet::GetPacketGenerationTime()
{
  return packet_generation_time;
}

bool Packet::GetTransmissionStatus()
{
  return transmission_status;
}

void Packet::SetTransmissionStatus(bool status)
{
  transmission_status = status;
}

int Packet::GetCtpkTime()
{
  return ctpk_time;
}
