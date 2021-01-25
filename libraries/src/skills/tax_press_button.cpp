#include "skills/tax_press_button.hpp"
#include "strategies/desired_wrench_strategy.hpp"
#include "strategies/move_to_pose.hpp"
#include <msrm_utils/math.hpp>

namespace mios{

bool SkillParametersTaxPressButton::from_json(const nlohmann::json& parameters){
    if(!msrm_utils::read_json_param<double,6,1>(parameters,"ROI_x",ROI_x)){
        spdlog::error("Parameter ROI_x could not be loaded but is mandatory.");
        return false;
    }
    if(!msrm_utils::read_json_param<double,6,1>(parameters,"ROI_phi",ROI_phi)){
        spdlog::error("Parameter ROI_phi could not be loaded but is mandatory.");
        return false;
    }
    if(!msrm_utils::read_json_param<double,2,1>(parameters,"approach_speed",approach_speed)){
        spdlog::error("Parameter approach_speed could not be loaded but is mandatory.");
        return false;
    }
    if(!msrm_utils::read_json_param<double,2,1>(parameters,"approach_acc",approach_acc)){
        spdlog::error("Parameter approach_acc could not be loaded but is mandatory.");
        return false;
    }
    if(!msrm_utils::read_json_param<double,2,1>(parameters,"press_speed",press_speed)){
        spdlog::error("Parameter press_speed could not be loaded but is mandatory.");
        return false;
    }
    if(!msrm_utils::read_json_param<double,2,1>(parameters,"press_acc",press_acc)){
        spdlog::error("Parameter press_acc could not be loaded but is mandatory.");
        return false;
    }
    if(!msrm_utils::read_json_param(parameters,"duration",duration)){
        spdlog::error("Parameter duration could not be loaded but is mandatory.");
        return false;
    }
    return true;
}

std::map<std::string, std::set<std::string> > SkillParametersTaxPressButton::get_parameter_list(){
    return {{"duration",{}},{"approach_speed",{}},{"approach_acc",{}},{"press_speed",{}},{"press_acc",{}},{"ROI_x",{}},{"ROI_phi",{}}};
}

TaxPressButton::TaxPressButton(const std::string& name, Memory* memory, Portal *portal):Skill("TaxPressButton",{"Button","Approach"},name,memory,portal,{ControlMode::mCartTorque}){

}

Eigen::Matrix<double,3,3> TaxPressButton::get_O_R_T_0(const Percept &p) const{
    if(get_object("Button")->name!="NullObject"){
        return get_object("Button")->O_T_OB.block<3,3>(0,0);
    }else{
        throw SkillException("No valid object has been grounded.");
    }
}

std::shared_ptr<ManipulationPrimitive> TaxPressButton::get_initial_mp(const Percept& p){
    return create_approach_mp(p);
}

std::optional<std::shared_ptr<ManipulationPrimitive> > TaxPressButton::graph_transition(const Percept &p){
    if(get_active_mp()->get_name()=="approach"){
        if(get_active_mp()->get_strategy_interface("move")->finished()){
            return create_push_mp(p);
        }else{
            return {};
        }
    }
    if(get_active_mp()->get_name()=="push"){
        if(get_active_mp()->get_strategy_interface("push")->finished()){
            return create_hold_mp(p);
        }else{
            return {};
        }
    }
    if(get_active_mp()->get_name()=="hold"){
        std::shared_ptr<SkillParametersTaxPressButton> skill_params = get_parameters<SkillParametersTaxPressButton>();
        if(std::chrono::duration_cast<std::chrono::milliseconds>(p.time-m_memory->get_live_context()->t_mp).count()>=skill_params->duration*1000){
            return create_retract_mp(p);
        }else{
            return {};
        }
    }
    return {};
}

std::shared_ptr<ManipulationPrimitive> TaxPressButton::create_approach_mp(const Percept &p){
    std::shared_ptr<SkillParametersTaxPressButton> skill_params = get_parameters<SkillParametersTaxPressButton>();
    std::shared_ptr<ManipulationPrimitive> mp = create_mp("approach",p);
    mp->create_strategy<MoveToPoseStrategy>("move",1);
    std::shared_ptr<MoveToPoseStrategy> move = mp->get_strategy<MoveToPoseStrategy>("move");
    move->set_goal(get_object_pose_T("Approach"),skill_params->approach_speed,skill_params->approach_acc);
    return mp;
}

std::shared_ptr<ManipulationPrimitive> TaxPressButton::create_push_mp(const Percept &p){
    std::shared_ptr<SkillParametersTaxPressButton> skill_params = get_parameters<SkillParametersTaxPressButton>();
    std::shared_ptr<ManipulationPrimitive> mp = create_mp("push",p);
    mp->create_strategy<MoveToPoseStrategy>("push",1);
    std::shared_ptr<MoveToPoseStrategy> move = mp->get_strategy<MoveToPoseStrategy>("push");
    move->set_goal(get_object_pose_T("Button"),skill_params->approach_speed,skill_params->approach_acc);
    return mp;
}

std::shared_ptr<ManipulationPrimitive> TaxPressButton::create_hold_mp(const Percept &p){
    std::shared_ptr<SkillParametersTaxPressButton> skill_params = get_parameters<SkillParametersTaxPressButton>();
    std::shared_ptr<ManipulationPrimitive> mp = create_mp("hold",p);
    return mp;
}

std::shared_ptr<ManipulationPrimitive> TaxPressButton::create_retract_mp(const Percept &p){
    std::shared_ptr<SkillParametersTaxPressButton> skill_params = get_parameters<SkillParametersTaxPressButton>();
    std::shared_ptr<ManipulationPrimitive> mp = create_mp("retract",p);
    mp->create_strategy<MoveToPoseStrategy>("move",1);
    std::shared_ptr<MoveToPoseStrategy> move = mp->get_strategy<MoveToPoseStrategy>("move");
    move->set_goal(get_object_pose_T("Approach"),skill_params->approach_speed,skill_params->approach_acc);
    return mp;
}

bool TaxPressButton::check_local_pre_conditions(const Percept &p){
    Eigen::Matrix<double,4,4> T_container = get_object_pose_T("Container");
    std::shared_ptr<SkillParametersTaxPressButton> skill_params = get_parameters<SkillParametersTaxPressButton>();
    for(unsigned i=0;i<3;i++){
        if(p.proprioception.T_T_EE(3,i)<T_container(3,i)+skill_params->ROI_x(i*2) || p.proprioception.T_T_EE(3,i)<T_container(3,i)+skill_params->ROI_x(i*2+1)){
            return false;
        }
    }
    return true;
}

bool TaxPressButton::check_local_suc_conditions(const Percept &p){
    std::shared_ptr<SkillParametersTaxPressButton> skill_params = get_parameters<SkillParametersTaxPressButton>();
        if((p.proprioception.O_T_EE.block<3,1>(0,3)-get_object_pose_T("Approach").block<3,1>(0,3)).norm()<0.005 && get_active_mp()->get_name()=="retract"){
            return true;
        }
    return false;
}

bool TaxPressButton::check_local_err_conditions(const Percept &p){
    const Eigen::Matrix<double,6,1>& ROI_x=get_parameters<SkillParametersTaxPressButton>()->ROI_x;
    const Eigen::Matrix<double,6,1>& ROI_phi=get_parameters<SkillParametersTaxPressButton>()->ROI_phi;
    double error_angle=acos(p.proprioception.T_T_EE.block<3,1>(0,2).dot(get_object_pose_T("Button").block<3,1>(0,2)));
    Eigen::Matrix<double,3,1> dist = p.proprioception.T_T_EE.block<3,1>(0,3)-get_object_pose_T("Button").block<3,1>(0,3);
    if(dist(0) < ROI_x(0) || dist(0) > ROI_x(1) || dist(1) < ROI_x(2) || dist(1) > ROI_x(3) || dist(2) < ROI_x(4) || dist(2) > ROI_x(5)){
        return true;
    }
    return false;
}

}
