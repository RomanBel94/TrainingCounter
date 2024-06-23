#pragma once
#ifndef CORE_H

#include "Counter.h"
#include "Logger.h"
#include "Save.h"
#include "LexerParser.h"

class AppCore
{
private:
	int argc;
	char** argv;

private:
	Counter counter;
	Logger log;
	Save save;
	LexerParser parser;

private:
    void _printHelp();
    void _addTrainings(uint8_t num);
    void _setTrainings(uint8_t num);
    void _markTraining();
    void _showTrainings();

public:
	AppCore(int argc, char* argv[]) : argc(argc), argv(argv) {};
	~AppCore() {};

	int run();
};

#define CORE_H
#endif
