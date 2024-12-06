#pragma once
#ifndef CORE_H

#include "Counter.hpp"
#include "Logger.h"
#include "Save.h"
#include "LexerParser.h"
#include "Version.h"

#include <memory>

#include "../fmt/include/fmt/core.h"

class AppCore final
{
private:

    int argc;              // number of given arguments
    char** argv;           // value of given arguments
    
    std::unique_ptr<Counter> counter = std::make_unique<Counter>();
    std::unique_ptr<Logger> log = std::make_unique<Logger>();
    std::unique_ptr<Save> save = std::make_unique<Save>();
    std::unique_ptr<LexerParser> parser = std::make_unique<LexerParser>();

private:

    AppCore() = delete;
    AppCore(const AppCore&) = delete;
    AppCore(AppCore&&) = delete;
    AppCore& operator=(const AppCore&) = delete;
    AppCore& operator=(AppCore&&) = delete;

    void _printHelp() noexcept;
    void _addTrainings(const uint32_t num);
    void _setTrainings(const uint32_t num);
    void _markTraining();
    void _removeLogfile();
    void _drawCat();

    inline void _showTrainings() { 
        log->out(fmt::format("Remaining trainings: {}", counter->getTrainings()), Logger::NO_LOG);
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
