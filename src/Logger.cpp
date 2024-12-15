#include "Logger.h"

/*
    Constructor
    Checks cache directory, and if it's not exists creates it
*/
Logger::Logger()
{
    std::filesystem::create_directory(cacheDir);
    
    try
    {
        logfile.open(logFileName, std::ios::out | std::ios::app);
    }
    catch (const std::exception& ex)
    {
        out(ex.what());
        exit(-1);
    }
}

/*
    Destructor
    Closes log file
*/
Logger::~Logger()
{
    logfile.close();
}

/*
    Shows log from logfile, if number is 0 shows full log

    @param number of lines to show
*/
void Logger::showLog(size_t lines_num)
{
    logfile.close();

    std::ifstream logfileRead(logFileName, std::ios::in);

    std::deque<std::string> lines;
    char buffer[BUFFER_SIZE];

    while (logfileRead.getline(buffer, BUFFER_SIZE, '\n'))
    {
        lines.push_back(buffer);
    }

    if (lines.empty())
    {
        out("Log file is empty.", NO_LOG);
        return;
    }
    
    if (lines_num > lines.size() || lines_num == 0)
    {
        lines_num = lines.size();
    }

    for (auto iterator{ lines.cend() - lines_num }; iterator != lines.cend(); ++iterator)
    {
        out((*iterator).c_str(), NO_LOG);
    }
}

#ifdef _WIN32
#pragma warning (disable: 4996)
#endif // _WIN32
/*
    Returns current date and time
*/
const std::string Logger::_datetime() const noexcept
{
    time_t seconds = time(nullptr);
    std::string time{ asctime(localtime(&seconds)) };
    time[time.size() - 1] = '\t';
    return time;
}
#ifdef _WIN32
#pragma warning (default: 4996)
#endif // _WIN32

/*
    Removes logfile
*/
void Logger::removeLogfile()
{
    logfile.close();
    std::filesystem::remove(logFileName);
}
