#include <chrono>
#include <deque>
#include <fstream>

#include "Logger.h"

/*
    Shows log from logfile, if number is 0 shows full log

    @param number of lines to show
*/
void Logger::show_logfile(size_t lines_num)
{
    std::ifstream logfile(m_logfilename, std::ios::in);

    std::deque<std::string> lines{};
    std::string buffer{};
    buffer.reserve(BUFFER_SIZE);

    while (logfile.getline(buffer.data(), BUFFER_SIZE, '\n'))
        lines.emplace_back(buffer.c_str());

    if (lines.empty())
    {
        write("Log file is empty");
        return;
    }

    if (lines_num > lines.size() || lines_num == 0)
        lines_num = lines.size();

    for (auto it{lines.cend() - lines_num}; it != lines.cend(); ++it)
        write((*it).c_str());
}

void Logger::write(const std::string_view msg, bool file) noexcept
{
    if (file)
    {
        std::filesystem::create_directory(cache_dir);
        std::ofstream logfile{m_logfilename, std::ios::out | std::ios::app};

        if (logfile.is_open())
        {
            const auto now = std::chrono::system_clock::now();
            const auto zone = std::chrono::current_zone();
            std::chrono::zoned_time fact_time(zone, now);

            logfile << std::format("{:%a %d.%m.%Y %H:%M %Z}\t{}\n", fact_time,
                                   msg);
        }
    }
    std::clog << std::format("{}\n", msg);
}

/*
    Removes logfile
*/
void Logger::remove_logfile() { std::filesystem::remove(m_logfilename); }
