#include "TaskManager.h"
#include <algorithm>

void TaskManager::add_task(
    std::function<void(TrainingCounter*, std::optional<std::size_t>)> func,
    std::optional<std::size_t> arg)
{
    task_list.emplace_back(tc, func, arg);
}

void TaskManager::execute_all_tasks()
{
    std::for_each(task_list.begin(), task_list.end(),
                  [](iTask& task) { task.execute(); });
}
