#pragma once
#ifndef CORE_H

#include "Counter/Counter.hpp"
#include "TaskManager/TaskManager.h"
#include <memory>

#include "CLIlib.h"

class TrainingCounter final
{
private:
    using counter_t = std::size_t;

    int argc;    // number of given arguments
    char** argv; // value of given arguments

    std::unique_ptr<Counter<counter_t>> m_counter =
        std::make_unique<Counter<std::size_t>>();
    std::unique_ptr<TaskManager> m_task_manager =
        std::make_unique<TaskManager>(this);
    std::unique_ptr<CLI::CLI> m_cli = std::make_unique<CLI::CLI>();

    std::unordered_map<
        std::string,
        std::function<void(TrainingCounter*, std::optional<counter_t>)>>
        task_table;

private:
    TrainingCounter() = delete;
    TrainingCounter(const TrainingCounter&) = delete;
    TrainingCounter(TrainingCounter&&) = delete;
    TrainingCounter& operator=(const TrainingCounter&) = delete;
    TrainingCounter& operator=(TrainingCounter&&) = delete;

    void _init_task_table() noexcept;
    void _init_cli_options() noexcept;
    void
    _fill_task_queue(const std::list<CLI::CLI::token>& tokens) const noexcept;

    void _printVersion(std::optional<counter_t> opt_arg = {
                           std::nullopt}) const noexcept;

    void _printHelp(std::optional<counter_t> opt_arg = {
                        std::nullopt}) const noexcept;

    void _printPrompt(std::optional<counter_t> opt_arg = {
                          std::nullopt}) const noexcept;

    void _addTrainings(std::optional<counter_t> opt_arg = {
                           std::nullopt}) noexcept;

    void _setTrainings(std::optional<counter_t> opt_arg = {
                           std::nullopt}) noexcept;

    void _markTraining(std::optional<counter_t> opt_arg = {
                           std::nullopt}) noexcept;

    void _removeLogfile(std::optional<counter_t> opt_arg = {
                            std::nullopt}) const noexcept;

    void _removeSaveFile(std::optional<counter_t> opt_arg = {
                             std::nullopt}) const noexcept;

    void _removeCache(std::optional<counter_t> opt_arg = {
                          std::nullopt}) const noexcept;

    void _drawCat(std::optional<counter_t> opt_arg = {
                      std::nullopt}) const noexcept;

    void _drawMoo(std::optional<counter_t> opt_arg = {
                      std::nullopt}) const noexcept;

    void _showTrainings(std::optional<counter_t> opt_arg = {
                            std::nullopt}) const noexcept;

    void _showNumTrainings(std::optional<counter_t> opt_arg = {
                               std::nullopt}) const noexcept;

    void _showLog(std::optional<counter_t> opt_arg = {
                      std::nullopt}) const noexcept;

public:
    /*
        Constructor.
        Starts command arguments parsing, reads save file and sets counter.

        @param argc from main
        @param argv from main
    */
    TrainingCounter(int argc, char** argv);

    template <class... Args>
    static std::shared_ptr<TrainingCounter>& getInstance(Args&&... args)
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
