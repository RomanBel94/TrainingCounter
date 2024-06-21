#pragma once
#ifndef LEXERPARSER_H

#include <stdint.h>

class LexerParser final
{
public:
	enum job {usage=0, add, set, get, mark};

private:
    job todo{ usage };
    uint8_t num{ 0 };

private:
    Token _getToken();

public:
	LexerParser() {};
	~LexerParser() {};

	void operator()(int argc, char** argv);
    job getJob() { return todo; }
    uint8_t getNum(){ return num; }
};

#define LEXERPARSER_H
#endif
