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
        write(ex.what());
        exit(-1);
    }
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
        lines.push_back(buffer);

    if (lines.empty())
    {
        write("Log file is empty.", NO_LOG);
        return;
    }

    if (lines_num > lines.size() || lines_num == 0)
        lines_num = lines.size();

    for (auto it{lines.cend() - lines_num}; it != lines.cend(); ++it)
        write((*it).c_str(), NO_LOG);
}

/*
    Removes logfile
*/
void Logger::removeLogfile()
{
    logfile.close();
    std::filesystem::remove(logFileName);
}
