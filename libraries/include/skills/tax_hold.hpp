#pragma once

#include "skill/skill.hpp"
namespace mios{
class SkillParametersTaxHold : public SkillParameters{
public:
    bool from_json(const nlohmann::json& parameters) override;
    std::map<std::string, std::set<std::string> > get_parameter_list() override;
    struct P0{
        Eigen::Matrix<double,6,1> K_x;
        double t_hold;
    }p0;
};

class TaxHold : public Skill{
public:
    TaxHold(const std::string& id,Memory* memory, Portal* portal);
private:
    std::shared_ptr<ManipulationPrimitive> get_initial_mp(const Percept& p_0) override;
    bool check_local_pre_conditions(const Percept &p) override;
    bool check_local_suc_conditions(const Percept& p) override;
    bool check_local_err_conditions(const Percept &p) override;

    double get_goal_heuristic(const Percept &p) override;

    std::shared_ptr<ManipulationPrimitive> create_hold_mp(const Percept& p);

    Eigen::Matrix<double,4,4> m_T_T_EE_hold;

};

}
