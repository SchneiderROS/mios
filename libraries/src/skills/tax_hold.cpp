#include "skills/tax_hold.hpp"
#include "strategies/move_to_pose.hpp"
#include "strategies/cart_compliance_strategy.hpp"

namespace mios{
bool SkillParametersTaxHold::from_json(const nlohmann::json& parameters){
    if(parameters.find("p0")==parameters.end()){
        spdlog::error("Parameters for primitive 0 are missing.");
        return false;
    }else if(parameters.find("p0")!=parameters.end()){
        if(!msrm_utils::read_json_param<double,6,1>(parameters["p0"],"K_x",p0.K_x)){
            spdlog::error("Missing parameter: p0.K_x");
            return false;
        }
        if(!msrm_utils::read_json_param(parameters["p0"],"t_hold",p0.t_hold)){
            spdlog::error("Missing parameter: p0.t_hold");
            return false;
        }
    }
    return true;
}

std::map<std::string, std::set<std::string> > SkillParametersTaxHold::get_parameter_list(){
    return {{"p0",{"K_x","t_hold"}}};
}

TaxHold::TaxHold(const std::string& id, Memory* memory, Portal* portal):Skill("TaxHold",{},id,memory,portal,{ControlMode::mCartTorque,ControlMode::mCartVelocity}){

}

std::shared_ptr<ManipulationPrimitive> TaxHold::get_initial_mp(const Percept& p){
    return create_hold_mp(p);
}

std::shared_ptr<ManipulationPrimitive> TaxHold::create_hold_mp(const Percept &p){
    spdlog::trace("TaxHold::create_hold_mp");
    m_T_T_EE_hold=p.proprioception.T_T_EE;
    std::shared_ptr<SkillParametersTaxHold> skill_params = get_parameters<SkillParametersTaxHold>();
    std::shared_ptr<ManipulationPrimitive> mp = create_mp("hold",p);
    mp->create_strategy<CartComplianceStrategy>("compliance",1);
    mp->get_strategy<CartComplianceStrategy>("compliance")->set_complicance(skill_params->p0.K_x,m_memory->read_parameters()->control.cart_imp.xi_x);
    return mp;
}

bool TaxHold::check_local_pre_conditions(const Percept &p){
    return true;
}

bool TaxHold::check_local_err_conditions(const Percept &p){
    const Eigen::Matrix<double,6,1>& ROI_x=get_parameters<SkillParametersTaxHold>()->ROI_x;
    const Eigen::Matrix<double,6,1>& ROI_phi=get_parameters<SkillParametersTaxHold>()->ROI_phi;
    double error_angle=acos(p.proprioception.T_T_EE.block<3,1>(0,2).dot(m_T_T_EE_hold.block<3,1>(0,2)));
    Eigen::Matrix<double,3,1> dist = p.proprioception.T_T_EE.block<3,1>(0,3)-m_T_T_EE_hold.block<3,1>(0,3);
    if(dist(0) < ROI_x(0) || dist(0) > ROI_x(1) || dist(1) < ROI_x(2) || dist(1) > ROI_x(3) || dist(2) < ROI_x(4) || dist(2) > ROI_x(5)){
        return true;
    }
    return false;
}

bool TaxHold::check_local_suc_conditions(const Percept &p){
    std::shared_ptr<SkillParametersTaxHold> skill_params = get_parameters<SkillParametersTaxHold>();
    if(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()-m_memory->get_live_context()->t_mp).count()>skill_params->p0.t_hold*1000){
        return true;
    }
    return false;
}

double TaxHold::get_goal_heuristic(const Percept &p){
    return 0;
}

}
