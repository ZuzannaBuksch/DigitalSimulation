// Projekt_Zuzanna_Buksch.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <queue>
#include <time.h>
#include <vector>
#include <iterator>

#include "generate_packet_event.h"
#include "check_channel_status_event.h"
#include "end_transmission_packet_event.h"
#include "end_transmission_ack_event.h"
#include "transmitter.h"
#include "receiver.h"
#include "channel.h"
#include "packet.h"
#include "logger.h"
#include "wireless_network.h"
#include "simulator.h"


int main()
{
	std::ofstream save_initial_phase("InitialPhase.txt");
	std::ofstream save_average_number_of_retransmission("AverageNumberOfRetransmission.txt");

  std::srand((int)time(NULL)); 
	size_t simulation_time;
	size_t end_of_initial_phase;
	int simulation_number = 0;
	double lambda = 0;

	std::cout << "Event Scheduling, Protocol A6e"<< std::endl;
	std::cout << "Select simulation number 1-10:" << std::endl;
	std::cin >> simulation_number;

	int wn_seed = 10*simulation_number;
  auto wnetwork = new WirelessNetwork(wn_seed);
	Simulator simulator = Simulator(wnetwork);

	std::cout << "Simulation time: " << std::endl;
	std::cin >> simulation_time;

	std::cout << "Set a lambda parameter (less than or equal to 0.1) " << std::endl;
	std::cin >> lambda;
	wnetwork->SetLambda(lambda);

	std::cout << "End of initial phase: " << std::endl;
	std::cin >> end_of_initial_phase;
	
	wnetwork->SetInitialPhase(end_of_initial_phase);
	simulator.M2(simulation_time);
}

