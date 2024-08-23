#include "OutputManager.h"

/*
	Constructor
	Checks cache directory, and if it's not exists creates it
*/
OutputManager::OutputManager()
{
	if (!std::filesystem::exists(_cacheDir))
		std::filesystem::create_directory(_logFileName);
	
	try
	{
		logfile.open(_logFileName, std::ios::out | std::ios::app);
	}
	catch (std::exception ex)
	{
#ifdef _WIN32
		setlocale(LC_ALL, "ru");
#endif // _WIN32
		operator()(error, ex.what());
		exit(-1);
	}
}

/*
	Destructor
	Closes log file
*/
OutputManager::~OutputManager()
{
	logfile.close();
}

/*
	Writes message in logfile and console

	@param message type
	@param message
	@param message color
	@param need to write log
*/
void OutputManager::operator()(messageType type, const char* msg, color color, bool log) noexcept
{
	if (log && logfile.is_open() && type != error)
	{
		logfile << _datetime() << '\t' << msg << '\n';
	}

    switch (type)
    {
    case message:
	    _setColor(color);
	    std::cout << msg << std::endl;
		break;
    case error:
        _setColor(red);
        std::cerr << "\a[ERROR] " << msg << std::endl;
    }
	_setColor();
}

/*
	Shows log from logfile, if number is 0 shows full log

	@param number of lines to show
*/
void OutputManager::showLog(size_t lines_num)
{
	logfile.close();

	if (std::filesystem::exists(_logFileName))
	{
		try 
		{
			std::ifstream logfileRead(_logFileName, std::ios::in);

			std::deque<std::string> lines;
			char buffer[UINT8_MAX];

			while (logfileRead.getline(buffer, UINT8_MAX, '\n'))
			{
				lines.push_back(buffer);
			}

			if (!lines.empty())
			{
				if (lines_num > lines.size() || lines_num == 0)
				{
					lines_num = lines.size();
				}

				for (auto iterator{ lines.end() - lines_num }; iterator != lines.end(); ++iterator)
				{
					operator()(message, *iterator, white, false);
				}
			}
			else
			{
				operator()(message, "Log file is empty.", yellow, false);
			}
			
		}
		catch (std::exception& ex)
		{
#ifdef _WIN32
			setlocale(LC_ALL, "ru");
#endif // _WIN32
			operator()(error, ex.what());
			exit(-1);
		}
	}
}

/*
	Sets text color for console

	@param text color
*/
void OutputManager::_setColor(color color) const noexcept
{
	std::cout << std::string{ "\x1b[" + std::to_string(30 + color) + "m" };
}

#ifdef _WIN32
#pragma warning (disable: 4996)
#endif // _WIN32

/*
	Returns current date and time
*/
const std::string OutputManager::_datetime() const noexcept
{
	time_t seconds = time(nullptr);
	std::string time{ asctime(localtime(&seconds)) };
	time.pop_back();
	return time;
}

/*
	Removes logfile
*/
void OutputManager::removeLogfile()
{
	logfile.close();

	try 
	{
		std::filesystem::remove(_logFileName);
	}
	catch (std::exception& ex) 
	{
#ifdef _WIN32
		setlocale(LC_ALL, "ru");
#endif // _WIN32
		operator()(error, ex.what());
		exit(-1);
	}
}
