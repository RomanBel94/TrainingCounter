#include "TaskManager.h"

void TaskManager::add_task(
    std::function<void(TrainingCounter*, std::optional<std::size_t>)> func,
    std::optional<std::size_t> arg)
{
    task_list.emplace_back(tc, func, arg);
}

void TaskManager::execute_all_tasks()
{
    for (auto& task : task_list)
        task.execute();
}
