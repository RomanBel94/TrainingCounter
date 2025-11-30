#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include "Task/iTask.h"
#include <list>
#include <queue>

class TrainingCounter;

class TaskManager final
{
public:
    explicit TaskManager(TrainingCounter* tc) : tc{tc} {};
    ~TaskManager() noexcept = default;

    void execute_all_tasks();
    void add_task(
        std::function<void(TrainingCounter*, std::optional<std::size_t>)> func,
        std::optional<std::size_t> arg = {std::nullopt});

private:
    std::queue<iTask, std::list<iTask>> task_queue{};
    TrainingCounter* tc{nullptr};
};

#endif // TASK_MANAGER_H
