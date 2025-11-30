#pragma once
#ifndef LOGGER_H

#include <filesystem> // exists(), create_directory()
#include <iostream>   // cout

#include <format>

class Logger final
{
private:
#ifdef _WIN32
#pragma warning(disable : 4996)
    // cache directory for windows
    inline const static std::string m_cache_dir{std::format(
        "{}\\..\\ProgramData\\TrainingCounter\\", std::getenv("WINDIR"))};
#pragma warning(default : 4996)
#else
    // cache directory for linux
    inline const static std::string m_cache_dir{
        std::format("{}/.TrainingCounter", std::getenv("HOME"))};
#endif // _WIN32

    inline const static std::string m_logfilename{
        std::format("{}/log.txt", m_cache_dir)};

private:
    inline static constexpr size_t BUFFER_SIZE =
        std::numeric_limits<unsigned char>().max();

    Logger(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger& operator=(Logger&&) = delete;

public:
    inline static bool constexpr NO_LOGFILE = false;
    inline static bool constexpr LOGFILE = true;

    Logger();
    ~Logger() noexcept = default;

    static void write(std::string const& msg, bool file = NO_LOGFILE) noexcept;

    static const auto& get_cache_dir() noexcept { return m_cache_dir; }

    static void remove_logfile();
    static void show_logfile(std::size_t lines_num = 0);
};

#define LOGGER_H
#endif
