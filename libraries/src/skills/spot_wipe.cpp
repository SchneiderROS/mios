#include "skills/spot_wipe.hpp"
#include "strategies/twist_wiggle_strategy.hpp"
#include "strategies/ff_strategy.hpp"

namespace mios{
bool SkillParametersSpotWipe::from_json(const nlohmann::json& parameters){
    if(!msrm_utils::read_json_param(parameters,"radius",radius)){
        spdlog::error("Parameter radius could not be loaded but is mandatory.");
        return false;
    }
    if(!msrm_utils::read_json_param(parameters,"f_contact",f_contact)){
        spdlog::error("Parameter f_contact could not be loaded but is mandatory.");
        return false;
    }
    if(!msrm_utils::read_json_param(parameters,"speed",speed)){
        spdlog::error("Parameter speed could not be loaded but is mandatory.");
        return false;
    }
    if(!msrm_utils::read_json_param(parameters,"run_time",run_time)){
        spdlog::error("Parameter run_time could not be loaded but is mandatory.");
        return false;
    }
    return true;
}
SpotWipe::SpotWipe(const std::string& name, Memory* memory, Portal* portal, const Percept& p):Skill("SpotWipe",{"wipeable"},name,memory,portal,p,{ControlMode::mCartTorque}){

}

std::shared_ptr<ManipulationPrimitive> SpotWipe::get_initial_mp(const Percept& p){
    std::shared_ptr<SkillParametersSpotWipe> skill_params = get_parameters<SkillParametersSpotWipe>();
    std::shared_ptr<ManipulationPrimitive> mp = create_mp("wipe",p);
    mp->create_strategy<TwistWiggleStrategy>("wiggle",1);
    mp->create_strategy<FFStrategy>("push",1);
    Eigen::Matrix<double,6,1> a;
    Eigen::Matrix<double,6,1> b;
    Eigen::Matrix<double,6,1> f_a;
    Eigen::Matrix<double,6,1> f_b;
    a<<skill_params->radius,0,0,0,0,0;
    b<<0,skill_params->radius,0,0,0,0;
    f_a<<skill_params->speed,0,0,0,0,0;
    f_b<<0,skill_params->speed,0,0,0,0;
    mp->get_strategy<TwistWiggleStrategy>("wiggle")->set_coefficients(a,b,f_a,f_b,Eigen::Matrix<double,6,1>::Zero(),Eigen::Matrix<double,6,1>::Zero());
    Eigen::Matrix<double,6,1> T_F_ff;
    T_F_ff<<0,0,skill_params->f_contact,0,0,0;
    mp->get_strategy<FFStrategy>("push")->set_TF_F_ff(T_F_ff,m_memory->read_parameters()->limits.cartesian_space.dF_J_max);
    return mp;
}

Eigen::Matrix<double,3,3> SpotWipe::get_O_R_T_0(const Percept &p) const{
    if(get_object("wipeable")->name!="NullObject"){
        return get_object("wipeable")->O_T_OB.block<3,3>(0,0);
    }else{
        throw SkillException("No valid object has been grounded.");
    }
}

bool SpotWipe::check_local_suc_conditions(const Percept &p){
    if(std::chrono::duration_cast<std::chrono::milliseconds>(p.time-m_memory->get_live_context()->t_skill).count()>get_parameters<SkillParametersSpotWipe>()->run_time*1000){
        return true;
    }else{
        return false;
    }
}

void SpotWipe::evaluate(){}
}
