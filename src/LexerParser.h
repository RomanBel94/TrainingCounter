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
    job getJob() { return todo; }
    uint8_t getNum(){ return num; }
};

#define LEXERPARSER_H
#endif
