#include "TrainingCounter.h"

class iTask
{
public:
    iTask() = default;
    ~iTask() = default;
    void execute();

protected:
    virtual void exec();

private:
    iTask(const iTask&) = delete;
    iTask(iTask&&) noexcept = delete;
    iTask& operator=(const iTask&) = delete;
    iTask& operator=(iTask&&) noexcept = delete;
};
