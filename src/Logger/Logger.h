#pragma once
#ifndef LOGGER_H

#include <filesystem> // exists(), create_directory()
#include <iostream>   // cout
#include <string_view>

class Logger final
{
private:
#ifdef _WIN32
#pragma warning(disable : 4996)
    // cache directory for windows
    inline const static std::filesystem::path cache_directory{
        std::filesystem::path(std::getenv("WINDIR")) / ".." / "ProgramData" /
        "TrainingCounter"};
#pragma warning(default : 4996)
#else
    // cache directory for linux
    inline const static std::filesystem::path cache_directory{
        std::filesystem::path(std::getenv("HOME")) / ".TrainingCounter"};
#endif // _WIN32

    inline const static std::filesystem::path logfile_path{cache_directory /
                                                           "log.txt"};

private:
    inline static constexpr std::size_t BUFFER_SIZE =
        std::numeric_limits<unsigned char>().max();

    Logger(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger& operator=(Logger&&) = delete;

public:
    inline static bool constexpr NO_LOGFILE = false;
    inline static bool constexpr LOGFILE = true;

    static void write(const std::string_view msg,
                      bool file = NO_LOGFILE) noexcept;

    [[nodiscard]] static const decltype(cache_directory)
    get_cache_dir() noexcept
    {
        return cache_directory;
    }

    static void remove_logfile();
    static void show_logfile(std::size_t lines_num = 0);
};

#define LOGGER_H
#endif
