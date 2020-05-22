#include "skills/nullskill.hpp"

namespace mios {

SkillParametersNullSkill::SkillParametersNullSkill():SkillParameters(){

}

bool SkillParametersNullSkill::read_parameters(const nlohmann::json &parameters){
    return false;
}

NullSkill::NullSkill(const std::string& id, Memory *memory, const Percept& p):Skill("NullSkill",{},id,memory,p){

}

void NullSkill::evaluate(){

}

bool NullSkill::build_primitives(const Percept &p){
    return false;
}

std::optional<std::tuple<bool, std::string> > NullSkill::check_edges(const Percept &p){
    return {};
}

bool NullSkill::check_local_suc_conditions(const Percept &p){
    return false;
}

bool NullSkill::check_local_err_conditions(const Percept &p){
    return true;
}

}
