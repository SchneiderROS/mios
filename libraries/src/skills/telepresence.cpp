#include "skills/telepresence.hpp"

namespace mios{

bool SkillParametersTelepresence::read_parameters(const nlohmann::json &parameters){
    return true;
}

Telepresence::Telepresence(const std::string &name, Memory *memory, const Percept &p):Skill("Telepresence",{},name,memory,p){

}

std::shared_ptr<ManipulationPrimitive> Telepresence::get_initial_mp(const Percept &p_0){
    return create_mp("sync",p_0);
}

std::optional<std::shared_ptr<ManipulationPrimitive> > Telepresence::graph_transition(const Percept &p){
    return {};
}

bool Telepresence::check_local_suc_conditions(const Percept &p){
    return false;
}

}

