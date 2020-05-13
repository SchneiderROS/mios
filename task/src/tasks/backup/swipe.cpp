#include "tasks/swipe.hpp"
#include "tasks/move_to_cart_pose.hpp"
#include "skills/move_to_contact.hpp"
#include "skills/swiping.hpp"

namespace mios{
swipe::swipe():Task("swipe"){
}
void swipe::initialize_task(){
    this->create_subtask<move_to_cart_pose>("move_to_surface");
    this->create_skill<move_to_contact>("contact");
    this->create_skill<swiping>("swiping");
}
void swipe::execute_task(){

    Object obj;
    this->_kb->load_object(this->locations[0],obj);
    Eigen::Matrix<double,4,4> TF_T_EE_o = this->_kb->transform_to_EE(obj.O_T_o);
    Eigen::Matrix<double,4,4> TF_T_EE_o_approach=TF_T_EE_o;

    Eigen::Matrix<double,3,1> Dx,TF_Dx;
    Dx<<0,0,0.02;

    TF_Dx=TF_T_EE_o.block<3,3>(0,0)*Dx;

    TF_T_EE_o_approach(0,3)+=TF_Dx(0);
    TF_T_EE_o_approach(1,3)+=TF_Dx(1);
    TF_T_EE_o_approach(2,3)+=TF_Dx(2);

    nlohmann::json parameters;
    msrm_utils::write_json_array<double,4,4>(parameters["TF_T_EE_g"],TF_T_EE_o_approach);

    if(!this->get_subtask("move_to_surface")->read_parameters(parameters)){
        return;
    }
    this->execute_subtask("move_to_surface");
    if(!this->get_subtask("move_to_surface")->get_eval().success){
        msrm_utils::print_error("Could not approach surface.");
        return;
    }

    this->get_skill("contact")->set_object("surface",this->locations[0]);
    this->execute_skill("contact");
    if(!this->get_skill("contact")->get_eval().success){
        msrm_utils::print_error("Could not establish contact, aborting swipe task");
        return;
    }

    this->execute_skill("swiping");

    this->_kb->load_object(this->locations[this->locations.size()-1],obj);
    TF_T_EE_o = this->_kb->transform_to_EE(obj.O_T_o);
    Eigen::Matrix<double,4,4> TF_T_EE_o_retreat=TF_T_EE_o;

    Dx<<0,0,0.02;

    TF_Dx=TF_T_EE_o.block<3,3>(0,0)*Dx;

    TF_T_EE_o_retreat(0,3)+=TF_Dx(0);
    TF_T_EE_o_retreat(1,3)+=TF_Dx(1);
    TF_T_EE_o_retreat(2,3)+=TF_Dx(2);

    msrm_utils::write_json_array<double,4,4>(parameters["TF_T_EE_g"],TF_T_EE_o_retreat);

    if(!this->get_subtask("move_to_surface")->read_parameters(parameters)){
        return;
    }
    this->execute_subtask("move_to_surface");

}
const EvalTask& swipe::evaluate_task(){
    this->_eval_task.success=this->get_skill("swiping")->get_eval().success;
    return this->_eval_task;
}
bool swipe::read_parameters(const nlohmann::json& params){
    if(!msrm_utils::read_json_param<std::string>(params,"locations",this->locations)){
        this->locations.resize(0);
    }
    return true;
}
}
