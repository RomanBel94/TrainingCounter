#pragma once
#ifndef CORE_H

#include "Counter.hpp"
#include "Logger.h"
#include "Version.h"

#include <cstdlib>
#include <memory>

#include "../external/CLIlib/include/CLIlib.h"

class TrainingCounter final
{
private:
    int argc;    // number of given arguments
    char** argv; // value of given arguments

    std::unique_ptr<Counter> counter = std::make_unique<Counter>();
    std::unique_ptr<Logger> log = std::make_unique<Logger>();

private:
    TrainingCounter() = delete;
    TrainingCounter(const TrainingCounter&) = delete;
    TrainingCounter(TrainingCounter&&) = delete;
    TrainingCounter& operator=(const TrainingCounter&) = delete;
    TrainingCounter& operator=(TrainingCounter&&) = delete;

    void _printHelp() noexcept;
    void _addTrainings(const uint32_t num);
    void _setTrainings(const uint32_t num);
    void _markTraining() noexcept;
    void _removeLogfile() const noexcept;
    void _removeSaveFile() const noexcept;
    void _removeCache() const noexcept;
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
    TrainingCounter(int argc, char** argv) : argc(argc), argv(argv){};

    template <class... Args>
    static std::shared_ptr<TrainingCounter>&
    getInstance(Args&&... args) noexcept
    {
        static auto ptr(std::make_shared<TrainingCounter>(args...));
        return ptr;
    };

    /*
     * Main program function
     */
    int run() noexcept;
};

#define CORE_H
#endif
