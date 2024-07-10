#include "OutputManager.h"

// constructor checks cache directory, and if it's not exists creates it
OutputManager::OutputManager()
{
	if (!std::filesystem::exists(dir))
		std::filesystem::create_directory(dir);

	logfile.open(file, std::ios::out | std::ios::app);
}

// close log file
OutputManager::~OutputManager()
{
	logfile.close();
}

void OutputManager::operator()(const char* msg, color color) noexcept
{
	logfile << _datetime() << '\t' << msg << '\n';
	_setColor(color);
	std::cout << msg << std::endl;
	_setColor();
}

// set console color
void OutputManager::_setColor(color color) noexcept
{
	std::string paint{ "\x1b[" + std::to_string(30 + color) + "m" };
	std::cout << paint;
}

// returns current date and time
const std::string OutputManager::_datetime()
{
	time_t seconds = time(nullptr);
	std::string time{ asctime(localtime(&seconds)) };
	time.pop_back();
	return time;
}
