#pragma once
#ifndef CORE_H

#include "Counter.hpp"
#include "OutputManager.h"
#include "Save.h"
#include "LexerParser.h"
#include "Version.hpp"

constexpr bool NO_LOG = false;

class AppCore final
{
private:
	Counter _counter;       // counter
	OutputManager _out;     // console and log output
	Save _save;             // save file
	LexerParser _parser;    // command argument parser

	int argc;               // number of given arguments
	char** argv;            // value of given arguments

private:
    void _printHelp() noexcept;
    void _addTrainings(const uint32_t num);
    void _setTrainings(const uint32_t num);
    void _markTraining();
    void _removeLogfile();

	inline void _showTrainings() { 
		_out("Remaining trainings: " + std::to_string(_counter.getTrainings()), NO_LOG);
	}

public:
	/*
	    Constructor.
	    Starts command arguments parsing, reads save file and sets counter.
	    
	    @param argc from main
	    @param argv from main
    */
	AppCore(int argc, char** argv) : argc(argc), argv(argv) {};

	int run();
};

#define CORE_H
#endif
