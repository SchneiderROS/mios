#pragma once

#include "task/task.hpp"

namespace mios{
class place_object : public Task{
public:
place_object();
void initialize_task();
void execute_task();
const EvalTask& evaluate_task();
bool read_parameters(const nlohmann::json& params);
private:
std::string loc_place;
Eigen::Matrix<double,3,1> Delta_approach;
Eigen::Matrix<double,3,1> Delta_retreat;
std::vector<std::string> loc_intermediate;
std::vector<int> loc_cart;
};
}
