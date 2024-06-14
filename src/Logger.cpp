#include "Logger.h"

Logger::Logger()
{
	std::string dir = getenv("HOME"); dir += "/.tc/";
	std::string path = dir + "log.txt";
	
	if (!std::filesystem::exists(dir))
		std::filesystem::create_directory(dir);

	logfile.open(path, std::ios::out | std::ios::app);

	if (!logfile.is_open())
		throw std::runtime_error("Could not open log file");
}

Logger::~Logger()
{
	logfile.close();
}

char* Logger::_datetime()
{
	time_t seconds = time(NULL);
	tm* timeinfo = localtime(&seconds);
	return asctime(timeinfo);
}
