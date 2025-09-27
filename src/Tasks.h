#include "TrainingCounter.h"
#include "iTask.h"

class task_add_trainings : public iTask
{
    using tc_method = void (*)(TrainingCounter*, int);

public:
    task_add_trainings(TrainingCounter* tc, tc_method func, int param);
    virtual void exec() override;

private:
    tc_method function;
    int param;
};

class task_set_trainings : public iTask
{
public:
    virtual void exec() override;
};

class task_mark_trainings : public iTask
{
public:
    virtual void exec() override;
};
