#pragma once
#ifndef LEXERPARSER_H

#include <stdint.h> // uint8_t
#include <cstdlib> // atoi()
#include <cctype> // isdigit()

class LexerParser final
{
public:
	enum job {help=0, add, set, show, mark};

private:
    job todo{ help };
    uint8_t num{ 0 };

public:
	LexerParser() {};
	~LexerParser() {};

	void operator()(int argc, char** argv);
	const job getJob() const noexcept { return todo; }
    const uint8_t getNum() const noexcept { return num; }
};

#define LEXERPARSER_H
#endif
