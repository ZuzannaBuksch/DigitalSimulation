#include "simulator.h"


Simulator::Simulator(WirelessNetwork* wieless_network_ptr): wireless_network_(wieless_network_ptr)
{
}

Simulator::~Simulator()
{
}

void Simulator::StepInto()
{
  char key;
  std::cout << "\nPress ENTER to continue..." << std::endl;
  key = getchar();
}

bool Simulator::SelectMode(int mode)
{
  if (mode == 1)
    return true;
  else if (mode == 2)
    return false;
  else
  {
    std::cout<<"Select 1 or 2. \n";
    int temp;
    std::cin >> temp;
    SelectMode(temp);
  }
 
}

void Simulator::M2(int time)
{
  clock_ = 0;
  int select_mode;

  auto logger = Logger();
  logger.SetLevel(Logger::Level::Info);

  std::cout << "\nStarted Simulation method M2: \n";
  //std::cout << "\nSelect simulation mode: \n1. Step into. \n2. Step over. \n";
  //std::cin >> select_mode;
  //bool mode = SelectMode(select_mode);
  
  auto cmp = [](Event* left, Event* right) { return left->get_time() > right->get_time(); };
  Event::EventList event_list(cmp);

  // scheduling the first packet generation event
  for (int i = 0; i < wireless_network_->kNumberOfTransmitters; ++i)
  {
    int CGPk = wireless_network_->GetTransmitters()->at(i)->GetExpGenerator()->RndExp(wireless_network_->GetLambda())*10;
    event_list.push(new GeneratePacketEvent(CGPk, wireless_network_, &event_list, &logger, i));
  }

  while (clock_ < static_cast<size_t>(time))
  {
    Event* event = event_list.top();
    event_list.pop();
    clock_ = event->get_time();
    /*
    if (mode == true)
      StepInto();
    else
      std::cout << ""<<std::endl;
    std::cout << "Simulation Time: " << clock_ << "\n";
    */
    
    event->Execute();
  }

  // simulation results: 
  std::cout << "" <<std::endl;
  std::cout << "Statistics:" << std::endl;
  logger.Info("Maximum packet error rate: " + std::to_string(wireless_network_->GetMaximumErrorRate()) + " %");
  logger.Info("Average packet error rate (BER): " +std::to_string(wireless_network_->GetErrorRateOfNetwork()*100)+" %");
  logger.Info("Number of packets: " + std::to_string(wireless_network_->GetNumberOfPackets()));
  logger.Info("Number of sent packets : " + std::to_string(wireless_network_->GetNumberOfPacketsCorrectlySent()));
  logger.Info("Number of lost packets : " + std::to_string(wireless_network_->GetNumberOfPackets() - wireless_network_->GetNumberOfPacketsCorrectlySent()));
  logger.Info("Number of retransmission: " + std::to_string(wireless_network_->GetNumberOfRetransmission()));
  double temp = (double)wireless_network_->GetNumberOfRetransmission();
  if(wireless_network_->GetNumberOfPackets()==0)
    logger.Info("Average number of retransmission: -");
  else
  logger.Info("Average number of retransmission: " + std::to_string(temp/ wireless_network_->GetNumberOfPackets()));
  double clock_sec = (double)clock_ / 10000;
  logger.Info("System bit rate: " + std::to_string((int)(wireless_network_->GetNumberOfPackets() /clock_sec))+" packets per second");
  logger.Info("Average of packet delay: " + std::to_string(wireless_network_->GetPacketDelay()/10) + " ms");
  if (wireless_network_->GetNumberOfPackets() == 0)
    logger.Info("Average of waiting time: -");
  else
    logger.Info("Average of waiting time: " + std::to_string(wireless_network_->GetTotalWaintingTime() / (wireless_network_->GetNumberOfPackets() *10)) + " ms");
    

}
