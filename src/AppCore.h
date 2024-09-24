#pragma once
#ifndef CORE_H

#include "Counter.hpp"
#include "OutputManager.h"
#include "Save.h"
#include "LexerParser.h"
#include "Version.hpp"

constexpr bool NO_LOG = false;

class AppCore final :
    protected Counter,
    protected OutputManager
{
private:
    Save save;             // save file
    LexerParser parser;    // command argument parser

    int argc;              // number of given arguments
    char** argv;           // value of given arguments

private:
    void _printHelp() noexcept;
    void _addTrainings(const uint32_t num);
    void _setTrainings(const uint32_t num);
    void _markTraining();
    void _removeLogfile();

    inline void _showTrainings() { 
        out("Remaining trainings: " + std::to_string(getTrainings()), NO_LOG);
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
