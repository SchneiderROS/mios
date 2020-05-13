#include "tasks/nulltask.hpp"

namespace mios {

NullTask::NullTask():Task("NullTask"){

}

void NullTask::initialize_task(){

}

void NullTask::execute_task(){

}

const EvalTask& NullTask::evaluate_task(){
    return this->_eval_task;
}

}
