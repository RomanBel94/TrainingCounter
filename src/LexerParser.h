#pragma once
#ifndef LEXERPARSER_H

#include <cstdint>  // uint16_t
#include <cstdlib>  // atoi()
#include <cctype>   // isdigit()
#include <deque>    // deque

class LexerParser final
{
private:
    std::deque<char> keys;

    std::deque<uint16_t> nums;
    std::deque<uint16_t>::iterator current_num{ nums.begin() };
public:
    void operator()(int argc, char** argv) noexcept;
	
    inline const std::deque<char>& getKeys() const noexcept { return keys; }  // returns task
    const uint16_t getNum() noexcept;
};

#define LEXERPARSER_H
#endif
