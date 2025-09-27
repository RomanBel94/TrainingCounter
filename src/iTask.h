#include "TrainingCounter.h"
#include <cstddef>
#include <functional>
#include <optional>

class iTask
{
public:
    iTask(std::function<void(std::optional<std::size_t>)> func,
          std::optional<std::size_t> arg = {})
        : func{func}, arg{arg} {};
    ~iTask() = default;
    void execute() { func(arg) };

protected:
    std::optional<std::size_t> arg{};
    std::function<void(std::optional<std::size_t>)> func{};

private:
    iTask(const iTask&) = delete;
    iTask(iTask&&) noexcept = delete;
    iTask& operator=(const iTask&) = delete;
    iTask& operator=(iTask&&) noexcept = delete;
};
