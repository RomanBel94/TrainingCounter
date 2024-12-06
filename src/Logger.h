#pragma once
#ifndef LOGGER_H

#include <fstream>	// ofstream
#include <chrono>   // now()
#include <filesystem>	// exists(), create_directory()
#include <string>	// strings
#include <cstdlib>	// getenv()
#include <ctime>	// asctime()
#include <iostream> // cout
#include <deque>    // deque

#include "../fmt/include/fmt/core.h"

class Logger final
{
private:

    std::ofstream logfile;

#ifdef _WIN32
#pragma warning (disable: 4996)
    // cache directory for windows
    const string cacheDir{ fmt::format("{}\\..\\ProgramData\\TrainingCounter\\", getenv("WINDIR")) };
#pragma warning (default: 4996)
#else
    // cache directory for linux
    const std::string cacheDir{ fmt::format("{}/.TrainingCounter", getenv("HOME")) };
#endif // _WIN32

    const std::string logFileName{ fmt::format("{}/log.txt", cacheDir) };

private:

    inline static size_t const BUFFER_SIZE = UINT8_MAX;

    const std::string _datetime() const noexcept;

    Logger(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger& operator=(Logger&&) = delete;

public:

    inline static bool const NO_LOG = false;

    Logger();
    ~Logger();
    
    /*
        Writes message in logfile and console

        @param message
        @param need to write log
    */
    template <class T = char const*>
    void out(T const* msg, bool log = true) noexcept
    {
        if (log && logfile.is_open())
        {
            logfile << fmt::format("{0}{1}\n", _datetime(), msg);
        }
        std::cout << msg << std::endl;
    }
    
    template <class T>
    void out(T const&& msg, bool log = true) noexcept
    {
        if (log && logfile.is_open())
        {
            logfile << fmt::format( "{0}{1}\n", _datetime(), msg);
        }
        std::cout << msg << std::endl;
    }

    void removeLogfile();
    void showLog(size_t lines_num = 0);
};

#define LOGGER_H
#endif
