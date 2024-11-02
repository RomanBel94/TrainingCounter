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

class Logger 
{
using string = std::string;

private:

    std::ofstream logfile;

#ifdef _WIN32
#pragma warning (disable: 4996)
    // cache directory for windows
    const string cacheDir{ fmt::format("{}\\..\\ProgramData\\TrainingCounter\\", getenv("WINDIR")) };
#pragma warning (default: 4996)
#else
    // cache directory for linux
    const string cacheDir{ fmt::format("{}/.TrainingCounter", getenv("HOME")) };
#endif // _WIN32

    const string logFileName{ fmt::format("{}/log.txt", cacheDir) };

private:

    const string _datetime() const noexcept;

    Logger(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger& operator=(Logger&&) = delete;

public:

    Logger();
    virtual ~Logger();
    
    /*
        Writes message in logfile and console

        @param message
        @param need to write log
    */
    template <class T = const char*>
    void out(T* msg, bool log = true) noexcept
    {
        if (log && logfile.is_open())
        {
            logfile << _datetime() << msg << '\n';
        }
        std::cout << msg << std::endl;
    }
    
    template <class T>
    void out(const T&& msg, bool log = true) noexcept
    {
        if (log && logfile.is_open())
        {
            logfile << _datetime() << msg << '\n';
        }
        std::cout << msg << std::endl;
    }

    void removeLogfile();
    void showLog(size_t lines_num = 0);
};

#define LOGGER_H
#endif
