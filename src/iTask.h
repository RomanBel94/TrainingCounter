#ifndef ITASK_H
#define ITASK_H

#include <cstddef>
#include <functional>
#include <optional>

class TrainingCounter;

class iTask
{
public:
    iTask(
        TrainingCounter* tc,
        std::function<void(TrainingCounter*, std::optional<std::size_t>)> func,
        std::optional<std::size_t> arg = {})
        : tc{tc}, func{func}, arg{arg} {};
    ~iTask() = default;
    void execute() { func(tc, arg); }

protected:
    TrainingCounter* tc;
    std::optional<std::size_t> arg{};
    std::function<void(TrainingCounter*, std::optional<std::size_t>)> func{};

private:
    iTask(const iTask&) = delete;
    iTask(iTask&&) noexcept = delete;
    iTask& operator=(const iTask&) = delete;
    iTask& operator=(iTask&&) noexcept = delete;
};

#endif // ITASK_H
