// Class that includes informations about receiver
#ifndef RECEIVER_H
#define RECEIVER_H

#include "channel.h"
#include "logger.h"


class Receiver
{
public:
	Receiver(int id);
	~Receiver();

	//metody

private:
	int receiver_id; // transmitter identification number

};


#endif

