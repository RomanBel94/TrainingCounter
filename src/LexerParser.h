#pragma once
#ifndef LEXERPARSER_H

#include <set>        // set
#include <cstdint>    // uint32_t
#include <cstdlib>    // atoi()
#include <cctype>     // isdigit()
#include <cstring>    // strchr()
#include <unordered_map>

#include "../fmt/include/fmt/format.h"

class Task;

class LexerParser final
{
public:
    LexerParser() = default;
    ~LexerParser() = default;

    void parseCommandLine(int argc, char** argv);

    const auto& getTasks() const noexcept { return tasks; }

private:
    
    LexerParser(const LexerParser&) = delete;
    LexerParser(LexerParser&&) = delete;
    LexerParser& operator=(const LexerParser&) = delete;
    LexerParser& operator=(LexerParser&&) = delete;

    static constexpr char DIVIDER{ '-' };
    
    std::set<Task> tasks{};
    std::string currentKey{ "h" };

    unsigned int currentNum{ 0 };

    void (LexerParser::*_currentArgumentReadingFunction)(const char* reader) = nullptr;

    void _collectArguments(std::string& strArgs, int argc, char** argv) noexcept;
    void _extractTokens(const std::string& tokensString);
    void _extractSingleCharKey(const char* reader);
    void _extractMultiCharKey(const char* reader);
    void _extractNum(const char* reader);

    bool _numberIsRequired(char ch) const noexcept
    { return std::strchr("as", ch); }

    bool _isAllowedSingleKey(char ch) const noexcept
    { return strchr("astvmlh", ch); }
};

struct Task final
{
public:
    enum class jobType {
        undefined = 0,
        show_help,
        add_trainings,
        set_trainings,
        mark_training,
        show_trainings,
        show_log,
        remove_logfile,
        remove_savefile,
        remove_cache,
        draw_cat,
        draw_moo,
        show_version,
    } const job { jobType::undefined };
    const uint32_t number{ 0 };
    
    explicit Task(const std::string& key, uint32_t num = 0) noexcept
    : job(jobs[key])
    , number(num) {};

    bool operator==(const Task& rhs) const noexcept { return this->job == rhs.job; }
    bool operator<(const Task& rhs) const noexcept { return this->job < rhs.job; }

private:

    inline static std::unordered_map<std::string, Task::jobType> jobs
    {
        {"*", jobType::undefined},
        {"h", jobType::show_help},
        {"help", jobType::show_help},
        {"draw_cat", jobType::draw_cat},
        {"moo", jobType::draw_moo},
        {"a", jobType::add_trainings},
        {"s", jobType::set_trainings},
        {"t", jobType::show_trainings},
        {"m", jobType::mark_training},
        {"v", jobType::show_version},
        {"version", jobType::show_version},
        {"l", jobType::show_log},
        {"remove_logfile", jobType::remove_logfile},
        {"remove_cache", jobType::remove_cache},
        {"remove_savefile", jobType::remove_savefile},
    };
};

template<>
struct std::hash<Task>
{
    uint32_t operator()(Task const& task) const
    {
        return std::hash<Task::jobType>()(task.job);
    }
};

#define LEXERPARSER_H
#endif

