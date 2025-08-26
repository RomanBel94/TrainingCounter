#pragma once
#ifndef LOGGER_H

#include <cstdlib>    // getenv()
#include <ctime>      // asctime()
#include <deque>      // deque
#include <filesystem> // exists(), create_directory()
#include <fstream>    // ofstream
#include <iostream>   // cout

#include "fmt/format.h"

class Logger final
{
private:
    inline static std::ofstream logfile;

#ifdef _WIN32
#pragma warning(disable : 4996)
    // cache directory for windows
    inline const static std::string cacheDir{fmt::format(
        "{}\\..\\ProgramData\\TrainingCounter\\", getenv("WINDIR"))};
#pragma warning(default : 4996)
#else
    // cache directory for linux
    inline const static std::string cacheDir{
        fmt::format("{}/.TrainingCounter", getenv("HOME"))};
#endif // _WIN32

    inline const static std::string logFileName{
        fmt::format("{}/log.txt", cacheDir)};

private:
    inline static size_t const BUFFER_SIZE = UINT8_MAX;
    inline static std::time_t seconds = time(nullptr);
    inline static char const* const date_time_format = "%a %d.%m.%Y %H:%M\t";

    Logger(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger& operator=(Logger&&) = delete;

public:
    inline static bool const NO_LOG = false;
    inline static bool const LOG = true;

    Logger();
    ~Logger() noexcept = default;

    /*
        Writes message in logfile and console

        @param message
        @param need to write log
    */
    template <class T = char const*>
    static void write(T const* msg, bool log = LOG) noexcept
    {
        if (log && logfile.is_open())
        {
            logfile << std::put_time(localtime(&seconds), date_time_format)
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
    static void write(T const&& msg, bool log = LOG) noexcept
    {
        if (log && logfile.is_open())
        {
            logfile << std::put_time(localtime(&seconds), date_time_format)
                    << msg << '\n';
        }
        std::cout << msg << std::endl;
    }

    const auto& getCacheDir() const noexcept { return cacheDir; }

    void removeLogfile();
    void showLog(size_t lines_num = 0);
};

#define LOGGER_H
#endif
