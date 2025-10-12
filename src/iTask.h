#pragma once
#ifndef ITASK_H
#define ITASK_H

#include <functional>
#include <optional>

class TrainingCounter;

class iTask
{
public:
    iTask(
        std::function<void(TrainingCounter*, std::optional<std::size_t>)> func,
        TrainingCounter* tc, std::optional<std::size_t> arg = {std::nullopt})
        : func{func}, tc{tc}, arg{arg} {};
    ~iTask() noexcept = default;

    void execute() { func(tc, arg); }

private:
    iTask(const iTask&) = delete;
    iTask(iTask&&) noexcept = delete;
    iTask& operator=(const iTask&) = delete;
    iTask& operator=(iTask&&) noexcept = delete;

    std::function<void(TrainingCounter*, std::optional<std::size_t>)> func{};
    TrainingCounter* tc{nullptr};
    std::optional<std::size_t> arg{std::nullopt};
};

#endif // ITASK_H
