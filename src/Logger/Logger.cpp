#include <deque>

#include "Logger.h"

/*
    Constructor
    Checks cache directory, and if it's not exists creates it
*/
Logger::Logger()
{
    std::filesystem::create_directory(m_cache_dir);

    m_logfile.open(m_logfilename, std::ios::out | std::ios::app);
}

/*
    Shows log from logfile, if number is 0 shows full log

    @param number of lines to show
*/
void Logger::show_logfile(size_t lines_num)
{
    m_logfile.close();
    std::ifstream logfileRead(m_logfilename, std::ios::in);

    std::deque<std::string> lines{};
    std::string buffer{};
    buffer.reserve(BUFFER_SIZE);

    while (logfileRead.getline(buffer.data(), BUFFER_SIZE, '\n'))
        lines.emplace_back(buffer.c_str());

    if (lines.empty())
    {
        write("Log file is empty.");
        return;
    }

    if (lines_num > lines.size() || lines_num == 0)
        lines_num = lines.size();

    for (auto it{lines.cend() - lines_num}; it != lines.cend(); ++it)
        write((*it).c_str());
}

void Logger::write(std::string const& msg, bool logfile) noexcept
{
    if (logfile && m_logfile.is_open())
        m_logfile << std::put_time(std::localtime(&m_time), m_time_format)
                  << msg << std::endl;

    std::clog << msg << std::endl;
}

/*
    Removes logfile
*/
void Logger::remove_logfile()
{
    m_logfile.close();
    std::filesystem::remove(m_logfilename);
}
