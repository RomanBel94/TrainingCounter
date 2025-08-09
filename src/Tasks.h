#include "iTask.h"

class task_add_trainings : public iTask
{
public:
    virtual void exec() override;
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
