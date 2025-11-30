#pragma once
#ifndef LOGGER_H

#include <filesystem> // exists(), create_directory()
#include <fstream>    // ofstream
#include <iostream>   // cout

#include "fmt/format.h"

class Logger final
{
private:
    inline static std::ofstream m_logfile;

#ifdef _WIN32
#pragma warning(disable : 4996)
    // cache directory for windows
    inline const static std::string m_cache_dir{fmt::format(
        "{}\\..\\ProgramData\\TrainingCounter\\", std::getenv("WINDIR"))};
#pragma warning(default : 4996)
#else
    // cache directory for linux
    inline const static std::string m_cache_dir{
        fmt::format("{}/.TrainingCounter", std::getenv("HOME"))};
#endif // _WIN32

    inline const static std::string m_logfilename{
        fmt::format("{}/log.txt", m_cache_dir)};

private:
    inline static constexpr size_t BUFFER_SIZE =
        std::numeric_limits<unsigned char>().max();
    inline static std::time_t const seconds = time(nullptr);
    inline static char const* const date_time_format = "%a %d.%m.%Y %H:%M\t";

    Logger(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger& operator=(Logger&&) = delete;

public:
    inline static bool const NO_LOGFILE = false;
    inline static bool const LOGFILE = true;

    Logger();
    ~Logger() noexcept = default;

    /*
        Writes message in logfile and console

        @param message
        @param need to write log
    */
    template <class T = char const*>
    static void write(T const* msg, bool log = NO_LOGFILE) noexcept
    {
        if (log && m_logfile.is_open())
        {
            m_logfile << std::put_time(localtime(&seconds), date_time_format)
                      << msg << '\n';
        }
        std::cout << msg << std::endl;
    }

    /*
        Writes message in logfile and console

        @param message
        @param need to write log
    */
    template <class T>
    static void write(T const&& msg, bool log = NO_LOGFILE) noexcept
    {
        if (log && m_logfile.is_open())
        {
            m_logfile << std::put_time(localtime(&seconds), date_time_format)
                      << msg << '\n';
        }
        std::cout << msg << std::endl;
    }

    const auto& get_cache_dir() const noexcept { return m_cache_dir; }

    void remove_logfile();
    void show_logfile(std::size_t lines_num = 0);
};

#define LOGGER_H
#endif
