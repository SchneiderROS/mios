#pragma once

#include "skill/skill.hpp"

namespace mios {

class SkillParametersNullSkill : public SkillParameters{
public:
    SkillParametersNullSkill();
    bool read_parameters(const nlohmann::json &parameters);
};

class NullSkill : public Skill{
public:
    NullSkill(const std::string& id,Memory *memory, const Percept& p);
    void evaluate();
private:
    bool build_primitives(const Percept& p);
    std::optional<std::tuple<bool,std::string> > check_edges(const Percept& p);
    bool check_local_suc_conditions(const Percept& p);
    bool check_local_err_conditions(const Percept &p);
};

}
