#include "OutputManager.h"

OutputManager::OutputManager()
{
	if (!std::filesystem::exists(dir))
		std::filesystem::create_directory(dir);

	logfile.open(file, std::ios::out | std::ios::app);
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
