#pragma once
#ifndef CORE_H

#include "Counter.hpp"
#include "Logger.h"
#include "TaskManager.h"
#include "Version.h"
#include <optional>

#include "CLIlib.h"

class TrainingCounter final
{
private:
    int argc;    // number of given arguments
    char** argv; // value of given arguments

    std::unique_ptr<Counter> counter = std::make_unique<Counter>();
    std::unique_ptr<Logger> log = std::make_unique<Logger>();
    std::unique_ptr<TaskManager> task_manager =
        std::make_unique<TaskManager>(this);

private:
    TrainingCounter() = delete;
    TrainingCounter(const TrainingCounter&) = delete;
    TrainingCounter(TrainingCounter&&) = delete;
    TrainingCounter& operator=(const TrainingCounter&) = delete;
    TrainingCounter& operator=(TrainingCounter&&) = delete;

    void _printVersion(std::optional<std::size_t> opt_arg = {}) const noexcept;
    void _printHelp(std::optional<std::size_t> opt_arg = {}) const noexcept;
    void _addTrainings(std::optional<std::size_t> opt_arg = {});
    void _setTrainings(std::optional<std::size_t> opt_arg = {});
    void _markTraining(std::optional<std::size_t> opt_arg = {}) noexcept;
    void _removeLogfile(std::optional<std::size_t> opt_arg = {}) const noexcept;
    void
    _removeSaveFile(std::optional<std::size_t> opt_arg = {}) const noexcept;
    void _removeCache(std::optional<std::size_t> opt_arg = {}) const noexcept;
    void _drawCat(std::optional<std::size_t> opt_arg = {}) const noexcept;
    void _drawMoo(std::optional<std::size_t> opt_arg = {}) const noexcept;
    void _showTrainings(std::optional<std::size_t> opt_arg = {}) const noexcept;
    void _showLog(std::optional<std::size_t> opt_arg = {}) const;

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
