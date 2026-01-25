/**
 * @file Logger.h
 *
 * @brief Logger component definition.
 */
#pragma once
#ifndef LOGGER_H

#include <filesystem> // exists(), create_directory()
#include <string_view>

/**
 * @brief Class Logger for printing messages in condole and logfile.
 */
class Logger final
{
private:
#ifdef _WIN32
#pragma warning(disable : 4996)
    /** @brief Cache directory for Windows. */
    inline const static std::filesystem::path cache_directory{
        std::filesystem::path(std::getenv("WINDIR")) / ".." / "ProgramData" /
        "TrainingCounter"};
#pragma warning(default : 4996)
#else
    /** @brief Cache directory for Linux. */
    inline const static std::filesystem::path cache_directory{
        std::filesystem::path(std::getenv("HOME")) / ".TrainingCounter"};
#endif // _WIN32

    /** @brief Path to the logfile.. */
    inline const static std::filesystem::path logfile_path{cache_directory /
                                                           "log.txt"};

private:
    /** @brief Max size of line buffer for reading logfile. */
    inline static constexpr std::size_t BUFFER_SIZE =
        std::numeric_limits<unsigned char>().max();

    /** @brief Deleted copy constructor. */
    Logger(const Logger&) = delete;

    /** @brief Deleted move constructor. */
    Logger(Logger&&) = delete;

    /** @brief Deleted copy assignment operator. */
    Logger& operator=(const Logger&) = delete;

    /** @brief Deleted move assignment operator. */
    Logger& operator=(Logger&&) = delete;

public:
    /** @brief Parameter that means do not write message to logfile. */
    inline static bool constexpr NO_LOGFILE = false;

    /** @brief Parameter that means write message to logfile. */
    inline static bool constexpr LOGFILE = true;

    /**
     * @brief Writes a message.
     *
     * @param[in] msg - message to write.
     * @param[in] file - write message to logfile or not.
     */
    static void write(const std::string_view msg,
                      bool file = NO_LOGFILE) noexcept;

    /**
     * @brief Returns cache_directory path.
     *
     * @return std::filesystem::path to the cache directory.
     */
    [[nodiscard]] static const decltype(cache_directory)
    get_cache_dir() noexcept
    {
        return cache_directory;
    }

    /**
     * @brief Removes logfile.
     */
    static void remove_logfile();

    /**
     * @brief Shows logfile content.
     *
     * @function You can pass a number of last lines that would be read from
     * file. If num is null all logfile will be printed.
     *
     * @param[in] lines_num - number of lines to show.
     */
    static void show_logfile(std::size_t lines_num = 0);
};

#define LOGGER_H
#endif
