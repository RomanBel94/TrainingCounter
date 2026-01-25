/**
 * @file TaskManager.cpp
 *
 * @brief TaskManager implementation.
 * @author Roman Belyaev
 */
#include "TaskManager.h"

void TaskManager::add_task(
    std::function<void(TrainingCounter*, std::optional<std::size_t>)> func,
    std::optional<std::size_t> arg)
{
    task_queue.emplace(func, tc, arg);
}

void TaskManager::execute_all_tasks()
{
    while (!task_queue.empty())
    {
        task_queue.front().execute();
        task_queue.pop();
    }
}
