#pragma once
#ifndef LEXERPARSER_H

#include <stdint.h> // uint8_t
#include <cstdlib> // atoi()
#include <cctype> // isdigit()

class LexerParser final
{
public:
	enum job {help=0, add, set, show, mark, version};    // types of job 

private:
    job todo{ help };    // what to do
    uint8_t num{ 0 };    // number to add or set

public:
	void operator()(int argc, char** argv);                  // evaluate job and num
	const job getJob() const noexcept { return todo; }       // returns job
    const uint8_t getNum() const noexcept { return num; }    // returns num
};

#define LEXERPARSER_H
#endif
