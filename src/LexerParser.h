#pragma once
#ifndef LEXERPARSER_H

#include <cstdint>    // uint32_t
#include <cstdlib>    // atoi()
#include <cctype>     // isdigit()
#include <cstring>    // strchr()
#include <deque>      // deque
#include <string>     // string
#include <iostream>   // cerr
#include <exception>  // runtime_error

#include "../fmt/include/fmt/core.h"    // fmt::format

struct Task final
{
public:
    enum class job {
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
    }

    task { Task::job::undefined };
    uint32_t number{ 0 };

    Task(job to_do, uint32_t num = 0)
    : task(to_do)
    , number(num) {};
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

    std::string keys{ "" };
    std::deque<uint32_t> nums{};

public:
    LexerParser() = default;
    ~LexerParser() = default;

    void parseCommandLine(int argc, char** argv);

    const auto& getKeys() const noexcept { return keys; }
    const uint32_t getNum() noexcept;

private:

    bool _keyExists(const char key) const noexcept { return keys.find(key) != std::string::npos; }
    void _validateKey(const char key) const 
    { 
        _keyExists(key) ? throw std::runtime_error(
                    fmt::format("Key \"-{}\" is not unique. All keys have to be given once", key
                        ))
            : key;
    }

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
