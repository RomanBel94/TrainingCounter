#pragma once
#ifndef LEXERPARSER_H

#include <cstdint>  // uint16_t
#include <cstdlib>  // atoi()
#include <cctype>   // isdigit()
#include <deque>    // deque
#include <string>   // string

class LexerParser final
{
private:
    std::string keys;

    std::deque<uint16_t> nums;
public:
    void operator()(int argc, const char** argv) noexcept;
	
    inline const std::string& getKeys() const noexcept { return keys; }
    const uint16_t getNum() noexcept;
};

#define LEXERPARSER_H
#endif
