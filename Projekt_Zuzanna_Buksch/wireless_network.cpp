#include "wireless_network.h"

#include <iostream>
#include <fstream>
#include <iterator>

WirelessNetwork::WirelessNetwork(int wn_seed) : seed(wn_seed)
{
  seeds_generator = new Generators(seed);
 
  for (int i = 0; i < kNumberOfSeeds * kSeedSaveStep; ++i)
  {
    seeds_generator->Rnd();
    if (i % kSeedSaveStep == 0)
      seeds_.push_back(seeds_generator->GetKernel());
  }

  // Save data to file
  std::ofstream output_file("./example.txt");
  std::ostream_iterator<double> output_iterator(output_file, "\n");
  std::copy(seeds_.begin(), seeds_.end(), output_iterator);

  auto seed_uniform = seeds_.back();
  seeds_.pop_back();
  channel = new Channel(seed_uniform);
 
  for (int i = 0; i < kNumberOfTransmitters; ++i)
  {
    auto seed_uniform = seeds_.back();
    seeds_.pop_back();
    auto seed_exp = seeds_.back();
    seeds_.pop_back();
    auto seed_r = seeds_.back();
    seeds_.pop_back();

    auto transmitter = new Transmitter(i,seed_uniform,seed_exp, seed_r);
    transmitters_.push_back(transmitter);
  } 
}

WirelessNetwork::~WirelessNetwork()
{
}

std::vector<Transmitter*>* WirelessNetwork::GetTransmitters()
{
  return &transmitters_;
}

Channel* WirelessNetwork::GetChannel()
{
  return channel;
}



double WirelessNetwork::GetLambda()
{
  return lambda;
}

double WirelessNetwork::GetErrorRateOfNetwork()
{
  error_rate_of_network = 0;
  for (int i = 0; i < kNumberOfTransmitters; ++i)
  {
    error_rate_of_network += GetTransmitters()->at(i)->GetPacketErrorRate();
  }
  return error_rate_of_network/kNumberOfTransmitters;
}

int WirelessNetwork::GetNumberOfRetransmission()
{
  return number_of_retransmission;
}

void WirelessNetwork::SetNumberOfRetransmission(int lr)
{
  number_of_retransmission += lr;
}

void WirelessNetwork::SaveAverageNumberOfRetransmission(size_t time, Logger* logger)
{
  double average = 0;

  if (GetNumberOfPackets() == 0)
     average = (double)GetNumberOfRetransmission();
  else
     average = (double)GetNumberOfRetransmission() / GetNumberOfPackets();

  //logger->Info("\nRetransmission number: "+ std::to_string(GetNumberOfRetransmission())
  //+"\nPackets number: "+ std::to_string(GetNumberOfPackets())
  //+"\nAverage number of retransmission: "+ std::to_string(average));

  std::ofstream save_average_number_of_retransmission("AverageNumberOfRetransmission.txt", std::ios_base::app);
  save_average_number_of_retransmission << "time " +std::to_string(time) 
    +" average: " + std::to_string(average) << std::endl;
  save_average_number_of_retransmission.close();

}

int WirelessNetwork::GetNumberOfPackets()
{
  number_of_packets = 0;
  for (int i = 0; i < kNumberOfTransmitters; ++i)
  {
    number_of_packets += GetTransmitters()->at(i)->GetSentPackets() + GetTransmitters()->at(i)->GetLostPackets();
  }
  return number_of_packets;
}

int WirelessNetwork::GetNumberOfPacketsCorrectlySent()
{
  return number_of_packets_correctly_sent;
}

void WirelessNetwork::SetNumberOfPacketsCorrectlySent()
{
  ++number_of_packets_correctly_sent;
}

int WirelessNetwork::GetAllPacketsCorrectlySent()
{
  return all_packets_correctly_sent;
}

void WirelessNetwork::SetAllPacketsCorrectlySent()
{
  ++all_packets_correctly_sent;
}

void WirelessNetwork::SetTotalDelayOfPackets(int delay)
{
  total_delay_of_packets += delay;
}

int WirelessNetwork::GetPacketDelay()
{
  if(number_of_packets_correctly_sent!=0)
    return total_delay_of_packets/number_of_packets_correctly_sent;
  else
    return 0;
}

int WirelessNetwork::GetInitialPhase()
{
  return initial_phase;
}

void WirelessNetwork::SetInitialPhase(int number)
{
  initial_phase = number;
}

size_t WirelessNetwork::GetTotalWaintingTime()
{
  return total_waiting_time;
}

void WirelessNetwork::SetTotalWaitingTime(size_t time)
{
  total_waiting_time += time;
}

double WirelessNetwork::GetMaximumErrorRate()
{
  std::cout << "\nError rate:\n";
  double temp = 0;
  for (int i = 0; i < kNumberOfTransmitters; ++i)
  {
    double rate = GetTransmitters()->at(i)->GetPacketErrorRate()*100;
    std::cout << "Transmitter " + std::to_string(i) + " " + std::to_string(rate)+ " %\n";
    if (rate >= temp)
      temp = rate;

  }
  std::cout << "" << std::endl;
  return temp;
}

std::vector<int>* WirelessNetwork::GetSeeds()
{
  return &seeds_;
}

void WirelessNetwork::SetLambda(double l)
{
  lambda = l;
}

void WirelessNetwork::SaveDataForInitialPhase()
{
  if (number_of_retransmission > 0)
  {
    double temp = (double)number_of_retransmission;
    std::ofstream save_initial_phase("InitialPhase.txt", std::ios_base::app);
    save_initial_phase << std::to_string(number_of_packets_correctly_sent) + " " +
      std::to_string(temp / number_of_packets) + "\n";
    save_initial_phase.close();
  }
 

}











