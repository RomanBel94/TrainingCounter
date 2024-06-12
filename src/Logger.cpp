#include "Logger.h"

Logger::Logger()
{
	std::string dir = getenv("HOME"); dir += "/.tc/";
	std::string path = dir + "log.txt";

	logfile.open(path);
	
	if (!logfile.is_open())
	{
		std::filesystem::create_directory(dir);
		logfile.open(path);
	}
}

Logger::~Logger()
{
	logfile.close();
}
