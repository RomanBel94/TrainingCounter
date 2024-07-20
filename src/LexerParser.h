#pragma once
#ifndef LEXERPARSER_H

#include <stdint.h> // uint16_t
#include <cstdlib> // atoi()
#include <cctype> // isdigit()

class LexerParser final
{
private:
    char key{ '\0' };     // the key given in argv[1]
    uint16_t num{ 0 };          // number to add or set

public:
	void operator()(int argc, char** argv);                  // evaluate task and num
	const char getKey() const noexcept { return key; }     // returns task
    const uint16_t getNum() const noexcept { return num; }    // returns num
};

#define LEXERPARSER_H
#endif
