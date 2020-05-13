#include "primitives/nullprimitive.hpp"

namespace mios {

NullPrimitive::NullPrimitive():ManipulationPrimitive("NullPrimitive"){
}

void NullPrimitive::initialize(const Percept &p_0, const std::shared_ptr<ConfigUser> config){

}

CmdMP& NullPrimitive::step(const Percept &p){
    return this->_cmd;
}

void NullPrimitive::terminate(){
}

bool NullPrimitive::check_attractor(){
    return true;
}

bool NullPrimitive::init_attractor(const Percept &p, const std::shared_ptr<ConfigUser> config){
    return true;
}

bool NullPrimitive::in_attractor(const Percept &p){
   return true;
}

void NullPrimitive::setup_logs(unsigned long long length){

}

void NullPrimitive::write_logs(){

}


}
