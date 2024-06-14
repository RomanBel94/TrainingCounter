#pragma once
#ifndef CORE_H

#include "Counter.h"
#include "Logger.h"
#include "Save.h"
#include "LexerParser.h"
#include "OutputManager.h"

class AppCore
{
private:
	int argc;
	char** argv;
private:
	Counter trainingCounter;
	Logger log;
	Save savefile;
	LexerParser parser;
	OutputManager output;
public:
	AppCore(int argc, char* argv[]) : argc(argc), argv(argv) {};
	~AppCore() {};

	int run();
};

#define CORE_H
#endif
