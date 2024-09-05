#pragma once
#ifndef LEXERPARSER_H

#include <cstdint>    // uint32_t
#include <cstdlib>    // atoi()
#include <cctype>     // isdigit()
#include <deque>      // deque
#include <string>     // string
#include <iostream>   // cerr
#include <exception>  // runtime_error

constexpr char DIVIDER{ '-' };

class LexerParser final
{
private:

    std::string keys;
    std::deque<uint32_t> nums;

    std::string undefinedTaskErrorMessage{ "Undefined task, keys are not given. Use \"TrainingCounter -h\" for help" };
    std::string unexpectedTokenErrorMessage{ "Unexpected token: " };
    std::string numberIsRequiredMessage{ "Number is required."} ;

public:

    void operator()(int argc, char** argv);

    inline const std::string& getKeys() const noexcept { return keys; }
    const uint32_t getNum() noexcept;

private:

    inline bool _keyExists(const char key) const noexcept { return keys.find(key) != std::string::npos; }
    inline void _validateKey(const char key) const 
    { 
        _keyExists(key) ? throw std::runtime_error(std::string("Key \"-") + key + "\" is not unique. All keys have to be given once") : key;
    }

    void _collectArguments(std::string& strArgs, int argc, char** argv) noexcept;
    void _extractTokens(const std::string& tokensString);
    void _extractKey(const char* reader);
    void _extractNum(const char* reader);
    inline bool _numberIsRequired(char ch) { return ch == 'a' || ch == 's'; }
    inline bool _numberIsNotRequired(char ch) { return ch == 't' || ch == 'h' || ch == 'm' || ch == 'v' || ch == 'r'; }
    inline bool _numberIsOptional(char ch) { return ch == 'l'; }
};

#define LEXERPARSER_H
#endif
