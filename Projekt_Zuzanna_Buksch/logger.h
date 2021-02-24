#ifndef LOGGER_H
#define LOGGER_H

#include <string>

class Logger
{
public:
	enum class Level{Info, Error};
	Logger();
	~Logger();

	void SetLevel(Level level) { level_ = level; }

	void Info(std::string message);
	void Error(std::string message);

private:
	Level level_ = Level::Info;

};


#endif LOGGER_H