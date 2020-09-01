#pragma once

#include "skill/skill.hpp"
namespace mios{
class SkillParametersLineWipe : public SkillParameters{
public:
bool from_json(const nlohmann::json& parameters) override;
Eigen::Matrix<double,2,1> distance;
double speed;
double acc;
double f_contact;
};

class LineWipe : public Skill{
public:
LineWipe(const std::string& name,Memory* memory, Portal* portal, const Percept& p);
void evaluate() override;
Eigen::Matrix<double,3,3> get_O_R_T_0(const Percept& p) const override;
private:
std::shared_ptr<ManipulationPrimitive> get_initial_mp(const Percept& p_0) override;
bool check_local_suc_conditions(const Percept& p) override;
};
}
