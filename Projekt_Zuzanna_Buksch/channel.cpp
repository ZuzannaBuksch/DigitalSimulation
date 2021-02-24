#include "channel.h"


Channel::Channel(int a)
{
  generator_ter = new Generators(a);
}


Channel::~Channel()
{
}

bool Channel::GetChannelStatus()
{
  return channel_status;
}

void Channel::SetChannelStatus(bool status)
{
  channel_status = status;
}

bool Channel::GetCollisionStatus()
{
  return collision_status;
}

void Channel::SetCollisionStatus(bool status)
{
  collision_status = status;
}

bool Channel::GetSentAck()
{
  return sent_ack;
}

void Channel::SetSentAck(bool status)
{
  sent_ack = status;
}


Generators* Channel::GetGeneratorTer()
{
  return generator_ter;
}

std::vector<Packet*>* Channel::GetPacketsCurrentlyTransmitting()
{
  return &packets_currently_transmitting_;
}
