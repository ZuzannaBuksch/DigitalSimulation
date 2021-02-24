//Class that represents transmitter

#ifndef BUFFER_H
#define BUFFER_H

#include <queue>

#include "packet.h"

class Buffer
{
public:
	Buffer();
	~Buffer();

private:
	std::queue<Packet*>packets_; // queue of packets 
};
#endif
