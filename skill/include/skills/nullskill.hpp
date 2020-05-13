#pragma once

#include "skill/skill.hpp"

namespace mios {

struct ConfigSkill_NullSkill : public ConfigSkill{

};

class NullSkill : public Skill{
public:
    NullSkill(KnowledgeBase *kb, std::shared_ptr<ConfigSkill> config);
    void evaluate();
    bool read_skill_parameters(const nlohmann::json &p);
private:
    void create_config();
    void build_primitives(const Percept& p);
    std::tuple<bool,std::string> check_edges(const Percept& p);
    bool check_local_suc_conditions(const Percept& p);
    bool check_local_err_conditions(const Percept &p);
};

}
