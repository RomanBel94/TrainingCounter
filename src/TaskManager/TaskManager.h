/**
 * @file TaskManager.h
 *
 * @brief Contains TaskManager class.
 * @author Roman Belyaev
 */
#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include "Task/iTask.h"
#include <list>
#include <queue>

/** Forward declaration of TrainingCounter */
class TrainingCounter;

/**
 * @brief TrainingCounter component that collects and
 *        executes tasks.
 */
class TaskManager final
{
public:
    /**
     * @brief Constructor.
     *
     * @param[in] tc - TrainingCounter pointer.
     */
    explicit TaskManager(TrainingCounter* tc) : tc{tc} {};

    /** @brief Destructor is default. */
    ~TaskManager() noexcept = default;

    /** @brief Calls execute() method for each task. */
    void execute_all_tasks();

    /**
     * @brief Adds a new task to the task queue.
     *
     * @param[in] func - member function of TrainingCounter that
     *                   will be passed to a new task.
     * @param[in] arg - argument for passed member function of TrainingCounter.
     */
    void add_task(
        std::function<void(TrainingCounter*, std::optional<std::size_t>)> func,
        std::optional<std::size_t> arg = std::nullopt);

private:
    /** @brief Task queue. */
    std::queue<iTask, std::list<iTask>> task_queue{};

    /** @brief Pointer to the TrainingCounter instance. */
    TrainingCounter* tc{nullptr};
};

#endif // TASK_MANAGER_H
