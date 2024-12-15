#pragma once
#ifndef CORE_H

#include "Counter.hpp"
#include "Logger.h"
#include "Save.h"
#include "LexerParser.h"
#include "Version.h"

#include <memory>
#include <cstdlib>

class TrainingCounter final
{
private:

    int argc;              // number of given arguments
    char** argv;           // value of given arguments
    
    std::unique_ptr<Counter> counter = std::make_unique<Counter>();
    std::unique_ptr<Logger> log = std::make_unique<Logger>();
    std::unique_ptr<Save> save = std::make_unique<Save>();
    std::unique_ptr<LexerParser> parser = std::make_unique<LexerParser>();

private:

    TrainingCounter() = delete;
    TrainingCounter(const TrainingCounter&) = delete;
    TrainingCounter(TrainingCounter&&) = delete;
    TrainingCounter& operator=(const TrainingCounter&) = delete;
    TrainingCounter& operator=(TrainingCounter&&) = delete;

    void _printHelp() noexcept;
    void _addTrainings(const uint32_t num);
    void _setTrainings(const uint32_t num);
    void _markTraining();
    void _removeLogfile() const;
    void _removeSaveFile() const;
    void _removeCache() const;
    void _drawCat() const noexcept;
    void _drawMoo() const noexcept;
    void _showTrainings() const noexcept;

public:

    /*
        Constructor.
        Starts command arguments parsing, reads save file and sets counter.
        
        @param argc from main
        @param argv from main
    */
    TrainingCounter(int argc, char** argv) : argc(argc), argv(argv) {};

    template<class... Args>
    static std::shared_ptr<TrainingCounter>& getInstance(Args&& ...args) noexcept
    {
        static auto ptr(std::make_shared<TrainingCounter>(args...));
        return ptr;
    };

    /*
     * Main program function
    */
    int run();
};

#define CORE_H
#endif
