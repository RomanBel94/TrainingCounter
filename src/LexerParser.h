#pragma once
#ifndef LEXERPARSER_H

#include <stdint.h> // uint8_t
#include <cstdlib> // atoi()
#include <cctype> // isdigit()

class LexerParser final
{
public:
	enum task {help=0, add, set, show, mark, version, remove_log, show_log};    // types of job 

private:
    task todo{ help };    // what to do
    uint8_t num{ 0 };    // number to add or set

public:
	void operator()(int argc, char** argv);                  // evaluate job and num
	const task getTask() const noexcept { return todo; }       // returns job
    const uint8_t getNum() const noexcept { return num; }    // returns num
};

#define LEXERPARSER_H
#endif
