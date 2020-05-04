#pragma once

#include "task/task.hpp"
#include "primitives/mp_telepresence.hpp"


namespace mios {

class telepresence : public Task{
public:
    telepresence();
    void initialize_task();
    void execute_task();
    const EvalTask& evaluate_task();
    bool read_parameters(const nlohmann::json& params);
private:
    bool _master;
    bool _repeater;
    bool _bilateral;
    TelepresenceMode _mode;

    std::string _alias_peer;
    Eigen::Matrix<double,7,1> _q_0;
    Eigen::Matrix<double,4,4> _TF_T_EE_0;


};


}
