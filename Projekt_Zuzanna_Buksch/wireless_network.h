#ifndef WIRELESS_NETWORK_H
#define WIRELESS_NETWORK_H

//Class that includes all system components
class Transmitter;
class Receiver;
class Channel;
class Generators;

#include<vector>
#include "transmitter.h"
#include "receiver.h"
#include "channel.h"
#include "generators.h"

class WirelessNetwork
{
public:
	WirelessNetwork(int wn_seed);
	~WirelessNetwork();

	std::vector<Transmitter*>* GetTransmitters();
	Channel* GetChannel();

	double GetLambda();
	double GetErrorRateOfNetwork();

	int GetNumberOfRetransmission();
	void SetNumberOfRetransmission(int lr);

	void SaveAverageNumberOfRetransmission(size_t time, Logger* logger_ptr);

	int GetNumberOfPackets();

	int GetNumberOfPacketsCorrectlySent();
	void SetNumberOfPacketsCorrectlySent();

	int GetAllPacketsCorrectlySent();
	void SetAllPacketsCorrectlySent();

	void SetTotalDelayOfPackets(int delay);

	int GetPacketDelay();

	int GetInitialPhase();
	void SetInitialPhase(int number);

	size_t GetTotalWaintingTime();
	void SetTotalWaitingTime(size_t time);

	double GetMaximumErrorRate();

	std::vector<int>* GetSeeds();

	void SetLambda(double l);

	void SaveDataForInitialPhase();

	const int kNumberOfTransmitters = 8; // number of transmitters and receivers in wireless network
	const int kLR = 5; // the maximal number of package retransmission
	const int kAckTime = 10; // time required to transmission ACK message
	const int kDifsTime = 50; //if listening time > DIFS_time - start transmission
	const int kWaitTime = 5;
	const int kNumberOfSeeds = 3*kNumberOfTransmitters +1;
	const int kSeedSaveStep = 100000;

private:
	std::vector<Transmitter*>transmitters_; // Vector of transmitters
	std::vector<int> seeds_;
	Channel* channel = nullptr;
	Generators* seeds_generator = nullptr;
	
	int initial_phase = 0;
	int seed = 0;
	double lambda = 0.05;

	//
	int all_packets_correctly_sent = 0;
	double error_rate_of_network = 0;
	int number_of_packets = 0; // liczba wszystkich pakietów, wys³anych i straconych w ca³ym systemie
	int number_of_retransmission = 0; 
	int number_of_packets_correctly_sent = 0;
	int total_delay_of_packets = 0;
	size_t total_waiting_time = 0;
};

#endif // WIRELESS_NETWORK_H

