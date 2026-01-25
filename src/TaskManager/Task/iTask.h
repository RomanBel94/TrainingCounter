/**
 * @file iTask.h
 *
 * @brief Contains definition of class iTask.
 * @author Roman Belyaev
 */
#pragma once
#ifndef ITASK_H
#define ITASK_H

#include <functional>
#include <optional>

/** Forward declaration of TrainingCounter class. */
class TrainingCounter;

/**
 * @brief Class iTask. Represents a task to be executed by TaskManager.
 */
class iTask
{
public:
    /**
     * @brief iTask constructor.
     *
     * @param[in] func - a TrainingCounter member function that will be called
     *                   by execute() function.
     * @param[in] tc - pointer to TrainingCounter instance.
     * @param[in] arg - argument that will pe passed to the func.
     */
    iTask(
        std::function<void(TrainingCounter*, std::optional<std::size_t>)> func,
        TrainingCounter* tc, std::optional<std::size_t> arg = std::nullopt)
        : func{func}, tc{tc}, arg{arg} {};

    /**
     * @brief Destructor is default.
     */
    ~iTask() noexcept = default;

    /**
     * @brief Calls a function passed in constructor.
     */
    void execute() { func(tc, arg); }

private:
    /** @brief Deleted copy constructor. */
    iTask(const iTask&) = delete;

    /** @brief Deleted move constructor. */
    iTask(iTask&&) noexcept = delete;

    /** @brief Deleted copy assignment operator. */
    iTask& operator=(const iTask&) = delete;

    /** @brief Deleted move assignment operator. */
    iTask& operator=(iTask&&) noexcept = delete;

    /** @brief Function to be called. */
    std::function<void(TrainingCounter*, std::optional<std::size_t>)> func{};

    /** @brief TrainingCounter pointer. */
    TrainingCounter* tc{nullptr};

    /** @brief Argument for func. */
    std::optional<std::size_t> arg{std::nullopt};
};

#endif // ITASK_H
