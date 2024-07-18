#pragma once
#ifndef LEXERPARSER_H

#include <stdint.h> // uint8_t
#include <cstdlib> // atoi()
#include <cctype> // isdigit()

class LexerParser final
{
public:
	// types of task
	enum task {undefined = 0, help, add, set, show, mark, version, remove_log, show_log};

private:
    task todo{ undefined };    // what to do
    uint8_t num{ 0 };          // number to add or set

public:
	void operator()(int argc, char** argv);                  // evaluate task and num
	const task getTask() const noexcept { return todo; }     // returns task
    const uint8_t getNum() const noexcept { return num; }    // returns num
};

#define LEXERPARSER_H
#endif
