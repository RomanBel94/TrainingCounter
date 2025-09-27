#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include "iTask.h"
#include <list>

class TrainingCounter;

class TaskManager final
{
public:
    TaskManager(TrainingCounter* tc) : tc{tc} {};
    ~TaskManager() noexcept = default;

    void execute_all_tasks();
    void add_task(
        std::function<void(TrainingCounter*, std::optional<std::size_t>)> func,
        std::optional<std::size_t> arg = {});

private:
    std::list<iTask> task_list{};
    TrainingCounter* tc;
};

#endif // TASK_MANAGER_H
