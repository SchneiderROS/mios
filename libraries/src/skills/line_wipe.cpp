#include "skills/line_wipe.hpp"
#include "strategies/ff_strategy.hpp"
#include "strategies/move_to_pose.hpp"

namespace mios{
bool SkillParametersLineWipe::from_json(const nlohmann::json& parameters){
    if(!msrm_utils::read_json_param<double,2,1>(parameters,"distance",distance)){
        spdlog::error("Parameter distance could not be loaded but is mandatory.");
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
    if(!msrm_utils::read_json_param(parameters,"acc",acc)){
        spdlog::error("Parameter acc could not be loaded but is mandatory.");
        return false;
    }
    return true;
}
LineWipe::LineWipe(const std::string& name, Memory* memory, Portal* portal, const Percept& p):Skill("LineWipe",{"wipeable"},name,memory,portal,p,{ControlMode::mCartTorque}){

}

Eigen::Matrix<double,3,3> LineWipe::get_O_R_T_0(const Percept &p) const{
    if(get_object("wipeable")->name!="NullObject"){
        return get_object("wipeable")->O_T_OB.block<3,3>(0,0);
    }else{
        throw SkillException("No valid object has been grounded.");
    }
}

std::shared_ptr<ManipulationPrimitive> LineWipe::get_initial_mp(const Percept& p){
    std::shared_ptr<SkillParametersLineWipe> skill_params = get_parameters<SkillParametersLineWipe>();
    std::shared_ptr<ManipulationPrimitive> mp = create_mp("wipe",p);
    mp->create_strategy<MoveToPoseStrategy>("move",1);
    mp->create_strategy<FFStrategy>("push",1);

    Eigen::Matrix<double,4,4> T_T_EE_g=p.proprioception.T_T_EE;
    T_T_EE_g(0,3)+=skill_params->distance(0);
    T_T_EE_g(1,3)+=skill_params->distance(1);

    Eigen::Matrix<double,2,1> dX_d,ddX_d;
    dX_d<<skill_params->speed,m_memory->read_parameters()->user.dX_default(1);
    ddX_d<<skill_params->acc,m_memory->read_parameters()->user.ddX_default(1);


    mp->get_strategy<MoveToPoseStrategy>("move")->set_goal(T_T_EE_g,dX_d,ddX_d);
    mp->get_strategy<MoveToPoseStrategy>("move")->set_scale(Eigen::Matrix<double,2,1>::Ones(2,1));
    Eigen::Matrix<double,6,1> T_F_ff;
    T_F_ff<<0,0,skill_params->f_contact,0,0,0;
    mp->get_strategy<FFStrategy>("push")->set_TF_F_ff(T_F_ff,m_memory->read_parameters()->limits.cartesian_space.dF_J_max);
    return mp;
}

bool LineWipe::check_local_suc_conditions(const Percept &p){
    return get_active_mp()->get_strategy_interface("move")->finished();
}

void LineWipe::evaluate(){}
}
