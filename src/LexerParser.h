#pragma once
#ifndef LEXERPARSER_H

#include <cstdint>    // uint32_t
#include <cstdlib>    // atoi()
#include <cctype>     // isdigit()
#include <cstring>    // strchr()
#include <exception>  // runtime_error
#include <unordered_set>
#include <unordered_map>

#include "../fmt/include/fmt/core.h"    // fmt::format

struct Task final
{
public:
    enum class jobType {
        undefined = 0,
        show_help,
        draw_cat,
        add_trainings,
        set_trainings,
        show_trainings,
        mark_training,
        show_version,
        show_log,
        remove_logfile,
    } const job { Task::jobType::undefined };
    const uint32_t number{ 0 };
    
    inline static std::unordered_map<char, Task::jobType> keys
    {
        {'*', Task::jobType::undefined},
        {'h', Task::jobType::show_help},
        {'C', Task::jobType::draw_cat},
        {'a', Task::jobType::add_trainings},
        {'s', Task::jobType::set_trainings},
        {'t', Task::jobType::show_trainings},
        {'m', Task::jobType::mark_training},
        {'v', Task::jobType::show_version},
        {'l', Task::jobType::show_log},
        {'r', Task::jobType::remove_logfile},
    };

    explicit Task(jobType job, uint32_t num = 0) noexcept
    : job(job)
    , number(num) {};

    bool operator==(const Task& rhs) const noexcept { return this->job == rhs.job; }
    bool operator<(const Task& rhs) const noexcept { return this->job < rhs.job; }
};

template<>
struct std::hash<Task>
{
    uint32_t operator()(Task const& task) const
    {
        return std::hash<Task::jobType>()(task.job);
    }
};

class LexerParser final
{
private:

    LexerParser(const LexerParser&) = delete;
    LexerParser(LexerParser&&) = delete;
    LexerParser& operator=(const LexerParser&) = delete;
    LexerParser& operator=(LexerParser&&) = delete;

    static constexpr char DIVIDER{ '-' };
    static constexpr auto numberIsRequiredKeys = "as";
    static constexpr auto numberIsNotRequiredKeys = "thmvrC";
    static constexpr auto numberIsOptionalKeys = "l";

    std::unordered_set<Task> tasks;

public:
    LexerParser() = default;
    ~LexerParser() = default;

    void parseCommandLine(int argc, char** argv);

    const auto& getTasks() const noexcept { return tasks; }

private:

    unsigned char currentKey{ '*' };
    unsigned int currentNum{ 0 };

    void _collectArguments(std::string& strArgs, int argc, char** argv) noexcept;
    void _extractTokens(const std::string& tokensString);
    void _extractKey(const char* reader);
    void _extractNum(const char* reader);

    bool _numberIsRequired(const char ch) const noexcept
        { return strchr(numberIsRequiredKeys, ch); }

    bool _numberIsNotRequired(const char ch) const noexcept
        { return strchr(numberIsNotRequiredKeys, ch); } 

    bool _numberIsOptional(const char ch) const noexcept
        { return strchr(numberIsOptionalKeys, ch); }
};

#define LEXERPARSER_H
#endif
