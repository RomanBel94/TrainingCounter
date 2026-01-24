/**
 * @file TrainingCounter.h
 *
 * @brief Main class of TrainingCounter application. Contains main logic.
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
    /** @brief Counter type. */
    using counter_t = std::size_t;

    /** @brief Method parameter type. */
    using param_t = std::size_t;

    /** @brief CLI tokens list type. */
    using cli_token_list = std::list<CLI::CLI::token>;

    /** @brief Optional argument type */
    using opt_arg = std::optional<param_t>;

    /** @brief Number of given arguments. */
    int argc;

    /** @brief Value of given arguments */
    char** argv;

    /** @brief Component for counting trainings. */
    std::unique_ptr<Counter<counter_t>> m_counter;

    /** @brief Component for creating and executing tasks. */
    std::unique_ptr<TaskManager> m_task_manager;

    /** @brief Component for parsing CLI. */
    std::unique_ptr<CLI::CLI> m_cli;

    /** @brief Task hashtable. */
    std::unordered_map<
        std::string,
        std::function<void(TrainingCounter*, std::optional<counter_t>)>>
        task_table{};

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

    /** @brief Fills task table with method pointers and string keys.*/
    void _init_task_table() noexcept;

    /** @brief Adds valid options to CLI. */
    void _init_cli_options() noexcept;

    /**
     * @brief Converts CLI token list to Task queue.
     *
     * @param[in] tokens - token list from CLIlib.
     */
    void _fill_task_queue(const cli_token_list& tokens) const noexcept;

    /**
     * @brief Prints app version.
     */
    void _printVersion(opt_arg) const noexcept;

    /**
     * @brief Prints help message.
     */
    void _printHelp(opt_arg) const noexcept;

    /**
     * @brief Prints short help message.
     */
    void _printPrompt(opt_arg) const noexcept;

    /**
     * @brief Decreases training number by 1 if it is greater than 0.
     */
    void _markTraining(opt_arg) noexcept;

    /**
     * @brief Sets trainings amount to num.
     *
     * If num is lower than number of trainings you have you will be warned.
     *
     * @param[in] num - new amount of trainings.
     */
    void _setTrainings(opt_arg num) noexcept;

    /**
     * @brief Adds num of trainings.
     *
     * @param[in] num - number of trainings to add.
     */
    void _addTrainings(opt_arg num) noexcept;

    /**
     * @brief Removes logfile.
     */
    void _removeLogfile(opt_arg) const noexcept;

    /**
     * @brief Removes savefile.
     */
    void _removeSaveFile(opt_arg) const noexcept;

    /**
     * @brief Removes logfile and savefile.
     */
    void _removeCache(opt_arg) const noexcept;

    /**
     * @brief Prints message with number of trainings.
     */
    void _showTrainings(opt_arg) const noexcept;

    /**
     * @brief Prints only number of trainings.
     */
    void _showNumTrainings(opt_arg) const noexcept;

    /**
     * @brief Prints some last lines of logfile if number
     *        of lines was passed, else prints full logfile.
     *
     * @param[in] lines - number of lines to be showed.
     */
    void _showLog(opt_arg lines) const noexcept;

    /**
     * @brief Prints ASCII cat.
     */
    void _drawCat(opt_arg) const noexcept;

    /**
     * @brief Prints ASCII cow.
     */
    void _drawMoo(opt_arg) const noexcept;

public:
    /**
     * @brief Constructor.
     *
     * @param[in] argc - number of CLI arguments.
     * @param[in] argv - values of CLI arguments.
     */
    TrainingCounter(int argc, char** argv);

    /**
     * @brief Creates TrainingCounter instance and returns it.
     *
     * @param[in] argc - number of CLI arguments.
     * @param[in] argv - values of CLI arguments.
     *
     * @return Instance of TrainingCounter.
     */
    static TrainingCounter& get_instance(int argc, char** argv)
    {
        static auto instance{std::make_unique<TrainingCounter>(argc, argv)};
        return *instance;
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
