#include "logger.h"
#include <iostream>
#include <fstream>

Logger::Logger()
{
}

Logger::~Logger()
{
}

void Logger::Info(std::string message)
{
  std::ofstream save_logger_info("LoggerInfo.txt", std::ios_base::app);

 if(level_ != Level::Error)
  std::cout << "[Info] " << message << std::endl;

 save_logger_info << "[Info] " << message << std::endl;
 save_logger_info.close();
}

void Logger::Error(std::string message)
{
  std::cout << "[Error] " << message << std::endl;
}
