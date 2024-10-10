#pragma once
#ifndef CORE_H

#include "Counter.hpp"
#include "Logger.h"
#include "Save.h"
#include "LexerParser.h"
#include "Version.hpp"

#include "../fmt/include/fmt/core.h"

constexpr bool NO_LOG = false;

class AppCore final :
    protected Counter,
    protected Logger,
    protected Save,
    protected LexerParser
{
private:
    int argc;              // number of given arguments
    char** argv;           // value of given arguments

private:
    void _printHelp() noexcept;
    void _addTrainings(const uint32_t num);
    void _setTrainings(const uint32_t num);
    void _markTraining();
    void _removeLogfile();
    void _drawCat();

    inline void _showTrainings() { 
        out(fmt::format("Remaining trainings: {}", getTrainings()), NO_LOG);
    }

public:
    /*
        Constructor.
        Starts command arguments parsing, reads save file and sets counter.
        
        @param argc from main
        @param argv from main
    */
    AppCore(int argc, char** argv) : argc(argc), argv(argv) {};

    static AppCore& getInstance(int argc, char** argv) noexcept;
    int run();
};

#define CORE_H
#endif
