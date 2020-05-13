#include "skills/nullskill.hpp"

namespace mios {

NullSkill::NullSkill(KnowledgeBase *kb, std::shared_ptr<ConfigSkill> config):Skill("NullSkill",kb,config){

}

void NullSkill::evaluate(){

}

bool NullSkill::read_skill_parameters(const nlohmann::json &p){
    return false;
}

void NullSkill::create_config(){
    m_config=std::make_shared<ConfigSkill_NullSkill>();
}

void NullSkill::build_primitives(const Percept &p){

}

std::tuple<bool,std::string> NullSkill::check_edges(const Percept &p){
    return std::tuple<bool,std::string>(false,"");
}

bool NullSkill::check_local_suc_conditions(const Percept &p){
    return false;
}

bool NullSkill::check_local_err_conditions(const Percept &p){
    return true;
}

}
