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
    void _printHelp() noexcept;                        // print help (usage)
    void _addTrainings(const uint8_t num) noexcept;    // add <num> trainings
    void _setTrainings(const uint8_t num) noexcept;    // set <num> trainings
    void _markTraining() noexcept;                     // mark completed training (decrement by 1))
    void _showTrainings() noexcept;                    // show current number of trainings
    void _removeLogfile() noexcept;                    // remove log file

    // show program version
    inline void _printVersion() noexcept { out("TrainingCounter v-1.2.0", OutputManager::white, false); }

    // print log file
    inline void _showLog() noexcept { out.showLog(); }

public:
	AppCore(int argc, char** argv) noexcept;           // constructor

	int run() noexcept;                                // main function of program
};

#define CORE_H
#endif
