#pragma once
#ifndef CORE_H

#include "Counter.h"
#include "Logger.h"
#include "Save.h"
#include "Parser.h"
#include "OutputManager.h"

class Core
{
private:
	int argc;
	char** argv;
private:
	Counter trainingCounter;
	Logger log;
	Save savefile{"~/.tc/save"};
	Parser parser;
	OutputManager output;
public:
	Core(int argc, char* argv[]) : argc(argc), argv(argv) {};
	~Core() {};

	void run();
};

#define CORE_H
#endif
