#pragma once
#ifndef CORE_H

#include "Counter.hpp"
#include "OutputManager.h"
#include "Save.h"
#include "LexerParser.h"
#include "Version.hpp"

class AppCore final
{
private:
	Counter _counter;       // counter
	OutputManager _out;     // console and log output
	Save _save;             // save file
	LexerParser _parser;    // command argument parser

private:
    void _printHelp() noexcept;
    void _addTrainings(const uint16_t num) noexcept;
    void _setTrainings(const uint16_t num) noexcept;
    void _markTraining() noexcept;
    void _showTrainings() noexcept;
    void _removeLogfile();

public:
	AppCore(int argc, char** argv) noexcept;

	int run() noexcept;
};

#define CORE_H
#endif
