#pragma once

#include "task/task.hpp"

namespace mios{
class fetch_object : public Task{
public:
fetch_object();
void initialize_task();
void execute_task();
const EvalTask& evaluate_task();
bool read_parameters(const nlohmann::json& params);
private:
std::string object;
Eigen::Matrix<double,3,1> Delta_approach;
Eigen::Matrix<double,3,1> Delta_retreat;
std::vector<std::string> loc_intermediate;
std::vector<int> loc_cart;
};
}
