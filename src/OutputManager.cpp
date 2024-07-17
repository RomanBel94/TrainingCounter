#include "OutputManager.h"
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

// prints message on console and log file
void OutputManager::operator()(const char* msg, color color, bool log) noexcept
{
	if (log && logfile.is_open())
	{
		logfile << _datetime() << '\t' << msg << '\n';
	}
	_setColor(color);
	std::cout << msg << std::endl;
	_setColor();
}

// shows log
void OutputManager::showLog() noexcept
{
	logfile.close();

	if (std::filesystem::exists(file))
	{
		std::ifstream logfileRead(file, std::ios::in);

		const unsigned char BUFSIZE = 128;
		char buffer[BUFSIZE];

		while (logfileRead.getline(buffer, BUFSIZE, '\n'))
		{
			if (logfileRead.eof()) return;
			std::cout << buffer << std::endl;
		}
	}
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

// removes logfile
bool OutputManager::removeLogfile()
{
	logfile.close();

	try 
	{
		return std::filesystem::remove(file);
	}
	catch (std::exception ex) 
	{
#ifdef _WIN32
		setlocale(LC_ALL, "ru");
#endif // _WIN32
		std::cout << ex.what() << std::endl;
		return false;
	}
}
