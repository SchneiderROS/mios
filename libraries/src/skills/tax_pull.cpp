#include "skills/tax_pull.hpp"
#include "strategies/desired_wrench_strategy.hpp"
#include "strategies/move_to_pose.hpp"
#include <msrm_utils/math.hpp>

namespace mios{

bool SkillParametersTaxPull::from_json(const nlohmann::json& parameters){
    if(parameters.find("p0")==parameters.end()){
        spdlog::error("Parameters for primitive 0 are missing.");
        return false;
    }else if(parameters.find("p0")!=parameters.end()){
        if(!msrm_utils::read_json_param<double,6,1>(parameters["p0"],"K_x",p0.K_x)){
            spdlog::error("Missing parameter: p0.K_x");
            return false;
        }
        if(!msrm_utils::read_json_param<double,2,1>(parameters["p0"],"dX_d",p0.dX_d)){
            spdlog::error("Missing parameter: p0.dX_d");
            return false;
        }
        if(!msrm_utils::read_json_param<double,2,1>(parameters["p0"],"ddX_d",p0.ddX_d)){
            spdlog::error("Missing parameter: p0.ddX_d");
            return false;
        }
    }
    return true;
}

std::map<std::string, std::set<std::string> > SkillParametersTaxPull::get_parameter_list(){
    return {{"p0",{"K_x","dX_d","ddX_d"}}};
}

TaxPull::TaxPull(const std::string& name, Memory* memory, Portal *portal):Skill("TaxPull",{"Pullable","GoalLocation"},name,memory,portal,{ControlMode::mCartTorque}){

}

Eigen::Matrix<double,3,3> TaxPull::get_O_R_T_0(const Percept &p) const{
    if(get_object("Pullable")->name!="NullObject"){
        return get_object("Pullable")->O_T_OB.block<3,3>(0,0);
    }else{
        throw SkillException("No valid object has been grounded.");
    }
}

std::shared_ptr<ManipulationPrimitive> TaxPull::get_initial_mp(const Percept& p){
    return create_pull_mp(p);
}

std::shared_ptr<ManipulationPrimitive> TaxPull::create_pull_mp(const Percept &p){
    std::shared_ptr<SkillParametersTaxPull> skill_params = get_parameters<SkillParametersTaxPull>();
    std::shared_ptr<ManipulationPrimitive> mp = create_mp("pull",p);
    mp->create_strategy<MoveToPoseStrategy>("move",1);
    std::shared_ptr<MoveToPoseStrategy> move = mp->get_strategy<MoveToPoseStrategy>("move");
    move->set_goal(get_object_pose_T("GoalLocation"),skill_params->p0.dX_d,skill_params->p0.ddX_d);
    return mp;
}

bool TaxPull::check_local_pre_conditions(const Percept &p){
    if(m_memory->get_live_context()->grasped_object->name!=get_object("Pullable")->name){
        return false;
    }
    return true;
}

bool TaxPull::check_local_suc_conditions(const Percept &p){
    return is_in_env("GoalLocation","move",p);
}

bool TaxPull::check_local_err_conditions(const Percept &p){
    if(m_memory->get_live_context()->grasped_object->name!=get_object("Pullable")->name){
        return true;
    }
    return false;
}

}
