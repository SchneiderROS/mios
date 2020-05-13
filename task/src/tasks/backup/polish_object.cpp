#include "tasks/polish_object.hpp"
#include "skills/move_to_pose_joint.hpp"
#include "skills/move_to_contact.hpp"
#include "skills/polish.hpp"

namespace mios {

polish_object::polish_object():Task("polish_object"){
}
void polish_object::initialize_task(){
    this->create_skill<move_to_pose_joint>("move");
    this->create_skill<move_to_contact>("contact");
    this->create_skill<polish>("polish");

    this->create_subtask<handover_object>("handover");
}
void polish_object::execute_task(){

    if(this->is_grasping()){
        this->grasp_object("polisher");
    }

    this->get_skill("move")->set_object("loc_goal",this->object);
    this->execute_skill("move");
    this->get_skill("contact")->set_object("surface",this->object);
    this->execute_skill("contact");
    this->get_skill("polish")->set_object("surface",this->object);
    this->execute_skill("polish");

}
const EvalTask &polish_object::evaluate_task(){
this->_eval_task.cost_suc=0;
this->_eval_task.cost_err=0;
this->_eval_task.success=true;
return this->_eval_task;
}

bool polish_object::read_parameters(const nlohmann::json& params){
    if(!msrm_utils::read_json_param(params,"object",this->object)){
        msrm_utils::print_error("Missing parameter: object");
        return false;
    }
    return true;
}

}
