#pragma once

#include "skill/skill.hpp"
namespace mios{
class SkillParametersSpotWipe : public SkillParameters{
public:
    bool from_json(const nlohmann::json& parameters) override;
    double radius;
    double speed;
    double f_contact;
    double run_time;
};

class SpotWipe : public Skill{
public:
    SpotWipe(const std::string& name,Memory* memory, Portal* portal, const Percept& p);
    void evaluate() override;
    Eigen::Matrix<double,3,3> get_O_R_T_0(const Percept& p) const override;
private:
    std::shared_ptr<ManipulationPrimitive> get_initial_mp(const Percept& p_0) override;
    bool check_local_suc_conditions(const Percept& p) override;
};
}
