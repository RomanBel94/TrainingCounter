#include "OutputManager.h"

// constructor checks cache directory, and if it's not exists creates it
OutputManager::OutputManager()
{
	if (!std::filesystem::exists(dir))
		std::filesystem::create_directory(dir);
	
	try
	{
		logfile.open(file, std::ios::out | std::ios::app);
	}
	catch (std::exception ex)
	{
#ifdef _WIN32
		setlocale(LC_ALL, "ru");
#endif // _WIN32
		operator()(ex.what(), red, false);
	}
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
void OutputManager::showLog(int lines_num)
{
	logfile.close();

	if (std::filesystem::exists(file))
	{
		try 
		{
			std::ifstream logfileRead(file, std::ios::in);

			std::deque<std::string> lines;
			char buffer[UINT8_MAX];

			while (logfileRead.getline(buffer, UINT8_MAX, '\n')) 
				lines.push_back(buffer);

			if (!lines.empty())
			{
				if (lines_num > lines.size() || lines_num == 0)
					lines_num = lines.size();

				size_t line{ lines.size() - (lines_num - 1)};
				for (auto iterator{ lines.end() - lines_num }; iterator != lines.end(); ++iterator, ++line)
					std::cout << " " << std::to_string(line) << " >\t" << *iterator << std::endl;
			}
			else
				operator()("Log file is empty.", yellow, false);
		}
		catch (std::exception ex)
		{
#ifdef _WIN32
			setlocale(LC_ALL, "ru");
#endif // _WIN32
			operator()(ex.what(), red, false);
		}
	}
}

// set console color
void OutputManager::_setColor(color color) const noexcept
{
	std::cout << std::string{ "\x1b[" + std::to_string(30 + color) + "m" };
}

#ifdef _WIN32
#pragma warning (disable: 4996)
#endif // _WIN32

// returns current date and time
const std::string OutputManager::_datetime() const noexcept
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
		operator()(ex.what(), red, false);
		return false;
	}
}
