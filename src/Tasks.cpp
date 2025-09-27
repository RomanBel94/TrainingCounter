#include "Tasks.h"

task_add_trainings::task_add_trainings(tc_method function, int param)
    : function{function}, param(param)
{
}

void task_add_trainings::exec() { function(training_counter, param); }
