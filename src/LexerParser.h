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
#include "../extern/include/fmt/core.h"    // fmt::format

class LexerParser 
{
private:

    static constexpr char DIVIDER{ '-' };
    static constexpr const char* numberIsRequiredKeys = "as";
    static constexpr const char* numberIsNotRequiredKeys = "thmvrC";
    static constexpr const char* numberIsOptionalKeys = "l";

    std::string keys;
    std::deque<uint32_t> nums;

public:
    virtual ~LexerParser() {}

    void parseCommandLine(int argc, char** argv);

    inline const std::string& getKeys() const noexcept { return keys; }
    const uint32_t getNum() noexcept;

private:

    inline bool _keyExists(const char key) const noexcept { return keys.find(key) != std::string::npos; }
    inline void _validateKey(const char key) const 
    { 
        _keyExists(key) ? 
            throw std::runtime_error(
                    fmt::format("Key \"-{}\" is not unique. All keys have to be given once", key
                        ))
            : key;
    }

    void _collectArguments(std::string& strArgs, int argc, char** argv) noexcept;
    void _extractTokens(const std::string& tokensString);
    void _extractKey(const char* reader);
    void _extractNum(const char* reader);

    inline bool _numberIsRequired(char ch) const noexcept
        { return strchr(numberIsRequiredKeys, ch); }

    inline bool _numberIsNotRequired(char ch) const noexcept
        { return strchr(numberIsNotRequiredKeys, ch); } 

    inline bool _numberIsOptional(char ch) const noexcept
        { return strchr(numberIsOptionalKeys, ch); }
};

#define LEXERPARSER_H
#endif
