#pragma once
#ifndef CORE_H

#include "Counter.hpp"
#include "OutputManager.h"
#include "Save.h"
#include "LexerParser.h"

class AppCore
{
private:
	int argc;
	char** argv;

private:
	Counter counter;
	OutputManager out;
	Save save;
	LexerParser parser;

private:
    void _printHelp();
    void _addTrainings(const uint8_t num);
    void _setTrainings(const uint8_t num);
    void _markTraining();
    void _showTrainings();

public:
	AppCore(int argc, char* argv[]) : argc(argc), argv(argv) {};
	~AppCore() {};

	int run();
};

#define CORE_H
#endif
