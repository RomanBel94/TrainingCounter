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
		operator()(ex.what());
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
	Shows log from logfile, if number is 0 shows full log

	@param number of lines to show
*/
void OutputManager::showLog(size_t lines_num)
{
	logfile.close();

	std::ifstream logfileRead(_logFileName, std::ios::in);

	std::deque<std::string> lines;
	char buffer[UINT8_MAX];

	while (logfileRead.getline(buffer, UINT8_MAX, '\n'))
	{
		lines.push_back(buffer);
	}

	if (lines.empty())
    {
		operator()("Log file is empty.", false);
        return;
    }
	
	if (lines_num > lines.size() || lines_num == 0)
	{
		lines_num = lines.size();
	}

	for (auto iterator{ lines.end() - lines_num }; iterator != lines.end(); ++iterator)
	{
		operator()(*iterator, false);
	}
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
	std::filesystem::remove(_logFileName);
}
