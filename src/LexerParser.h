#pragma once
#ifndef LEXERPARSER_H

#include <cstdint>  // uint16_t
#include <cstdlib>  // atoi()
#include <cctype>   // isdigit()
#include <deque>    // deque
#include <string>   // string
#include <iostream> // cerr
#include <exception>   // runtime_error

class LexerParser final
{
private:
    std::string keys;

    std::deque<uint16_t> nums;
public:
    void operator()(int argc, char** argv);

    inline const std::string& getKeys() const noexcept { return keys; }
    const uint16_t getNum() noexcept;

    inline bool _keyExists(const char key) const noexcept { return keys.find(key) != std::string::npos; }
    inline void _validateKey(const char key) const { if (_keyExists(key)) throw std::runtime_error(std::string("Key -") + key + " is not unique. All keys have to be given once"); }

    void _collectArguments(std::string& strArgs, int argc, char** argv) noexcept;
    void _extractTokens(const std::string& tokensString);
    void _extractKey(const char* reader);
    void _extractNum(const char* reader);
};

#define LEXERPARSER_H
#endif
