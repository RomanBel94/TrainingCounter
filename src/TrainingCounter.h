/**
 * @file TrainingCounter.h
 *
 * @brief Main class of TrainingCounter application. Contains main logic.
 *
 */

#pragma once
#ifndef TRAINING_COUNTER_H

#include "Counter/Counter.hpp"
#include "TaskManager/TaskManager.h"
#include <memory>

#include "CLIlib.h"

/**
 * @brief Main application class, contains logic.
 */
class TrainingCounter final
{
private:
    using counter_t = std::size_t; /**< @brief Counter type. */
    using param_t = std::size_t;   /**< @brief Method parameter type. */

    int argc;    /**< @brief Number of given arguments. */
    char** argv; /**< @brief Value of given arguments */

    std::unique_ptr<Counter<counter_t>> m_counter{
        std::make_unique<Counter<counter_t>>()}; /**< @brief Component for
                                                    counting trainings. */

    std::unique_ptr<TaskManager> m_task_manager{std::make_unique<TaskManager>(
        this)}; /**< @brief Component for creating and executing tasks. */

    std::unique_ptr<CLI::CLI> m_cli{
        std::make_unique<CLI::CLI>()}; /**< @brief Component for parsing CLI. */

    std::unordered_map<
        std::string,
        std::function<void(TrainingCounter*, std::optional<counter_t>)>>
        task_table{}; /**< @brief Task hashtable. */

private:
    /** @brief Deleted default constructor. */
    TrainingCounter() = delete;

    /** @brief Deleted copy constructor. */
    TrainingCounter(const TrainingCounter&) = delete;

    /** @brief Deleted move constructor. */
    TrainingCounter(TrainingCounter&&) = delete;

    /** @brief Deleted copy assignment operator. */
    TrainingCounter& operator=(const TrainingCounter&) = delete;

    /** @brief Deleted move assignment operator. */
    TrainingCounter& operator=(TrainingCounter&&) = delete;

    void _init_task_table() noexcept;
    void _init_cli_options() noexcept;
    void
    _fill_task_queue(const std::list<CLI::CLI::token>& tokens) const noexcept;

    void _printVersion(std::optional<param_t> opt_arg = {
                           std::nullopt}) const noexcept;

    void _printHelp(std::optional<param_t> opt_arg = {
                        std::nullopt}) const noexcept;

    void _printPrompt(std::optional<param_t> opt_arg = {
                          std::nullopt}) const noexcept;

    void _addTrainings(std::optional<param_t> opt_arg = {
                           std::nullopt}) noexcept;

    void _setTrainings(std::optional<param_t> opt_arg = {
                           std::nullopt}) noexcept;

    void _markTraining(std::optional<param_t> opt_arg = {
                           std::nullopt}) noexcept;

    void _removeLogfile(std::optional<param_t> opt_arg = {
                            std::nullopt}) const noexcept;

    void _removeSaveFile(std::optional<param_t> opt_arg = {
                             std::nullopt}) const noexcept;

    void _removeCache(std::optional<param_t> opt_arg = {
                          std::nullopt}) const noexcept;

    void _drawCat(std::optional<param_t> opt_arg = {
                      std::nullopt}) const noexcept;

    void _drawMoo(std::optional<param_t> opt_arg = {
                      std::nullopt}) const noexcept;

    void _showTrainings(std::optional<param_t> opt_arg = {
                            std::nullopt}) const noexcept;

    void _showNumTrainings(std::optional<param_t> opt_arg = {
                               std::nullopt}) const noexcept;

    void _showLog(std::optional<param_t> opt_arg = {
                      std::nullopt}) const noexcept;

public:
    /**
     * @brief Constructor.
     *
     * @param[in] argc - number of given arguments from main.
     *
     * @param[in] argv - values of given arguments from main.
     */
    TrainingCounter(int argc, char** argv);

    /**
     * @brief Creates TrainingCounter instance and returns it.
     *
     * @param[in] argc - number of CLI arguments.
     *
     * @param[in] argv - values of CLI arguments.
     *
     * @return Instance of TrainingCounter.
     */
    static TrainingCounter& get_instance(int argc, char** argv)
    {
        static TrainingCounter instance(argc, argv);
        return instance;
    };

    /**
     * @brief Main program function.
     *
     * @return Exit code.
     */
    int run() noexcept;
};

#define TRAINING_COUNTER_H
#endif
