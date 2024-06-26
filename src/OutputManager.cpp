#include "OutputManager.h"

OutputManager::OutputManager()
{
	if (!std::filesystem::exists(dir))
		std::filesystem::create_directory(dir);

	logfile.open(file, std::ios::out | std::ios::app);

	if (!logfile.is_open())
		throw std::runtime_error("Could not open log file");
}

OutputManager::~OutputManager()
{
	logfile.close();
}

const std::string OutputManager::_datetime()
{
	time_t seconds = time(nullptr);
	std::string time{ asctime(localtime(&seconds)) };
	time.pop_back();
	return time;
}
