#pragma once

#include "task/task.hpp"
namespace mios{
class LearnerTest : public Task{
public:
LearnerTest(Core* core);
void initialize_context() override;
void execute_task() override;
void evaluate_task() override;
bool read_parameters(const nlohmann::json& params) override;
private:
Eigen::Matrix<double,6,1> m_x;
};
}
