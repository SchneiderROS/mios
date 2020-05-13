#pragma once

#include "task/task.hpp"

namespace mios {

class NullTask : public Task{
public:
    NullTask();

    void initialize_task();
    void execute_task();
    const EvalTask& evaluate_task();
};

}
