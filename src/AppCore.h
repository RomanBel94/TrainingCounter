#pragma once
#ifndef CORE_H

#include "Counter.hpp"
#include "OutputManager.h"
#include "Save.h"
#include "LexerParser.h"

class AppCore final
{
private:
	Counter counter;       // counter
	OutputManager out;     // console and log output
	Save save;             // save file
	LexerParser parser;    // command argument parser

private:
    void _printHelp();                        // print help (usage)
    void _addTrainings(const uint8_t num);    // add <num> trainings
    void _setTrainings(const uint8_t num);    // set <num> trainings
    void _markTraining();                     // mark completed training (decrement by 1))
    void _showTrainings();                    // show current number of trainings
    void _printVersion();                     // show program version

public:
	AppCore(int argc, char** argv);          // constructor

	int run();                                // main function of program
};

#define CORE_H
#endif
