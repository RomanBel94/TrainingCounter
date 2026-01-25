/**
 * @file Logger.cpp
 *
 * @brief Logger implementation.
 * @author Roman Belyaev
 */
#include <chrono>
#include <deque>
#include <format>
#include <fstream>
#include <iostream>

#include "Logger.h"

void Logger::show_logfile(std::size_t lines_num)
{
    std::ifstream logfile(logfile_path, std::ios::in);

    if (!logfile)
    {
        write("\033[31;1mCan't open logfile\033[0m");
        return;
    }

    std::deque<std::string> lines{};
    std::string buffer{};
    buffer.reserve(BUFFER_SIZE);

    while (logfile.getline(buffer.data(), BUFFER_SIZE, '\n'))
        lines.emplace_back(buffer.c_str());

    if (lines.empty())
    {
        write("\033[33;1mLog file is empty\033[0m");
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
        std::filesystem::create_directory(cache_directory);
        std::ofstream logfile{logfile_path, std::ios::out | std::ios::app};

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

void Logger::remove_logfile() { std::filesystem::remove(logfile_path); }
