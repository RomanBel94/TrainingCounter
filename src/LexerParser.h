#pragma once
#ifndef LEXERPARSER_H

class LexerParser final
{
public:
	enum job {none=0, add, set, get};
public:
	LexerParser() {};
	~LexerParser() {};

	job operator()(char* argv, int& num);
};

#define LEXERPARSER_H
#endif
