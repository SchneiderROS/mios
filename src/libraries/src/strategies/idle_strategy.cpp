#include "mios/strategies/idle_strategy.hpp"

namespace mios {

IdleStrategy::IdleStrategy():PrimitiveStrategy({CommandPatternCartesianTwist}){

}

void IdleStrategy::initialize([[maybe_unused]] const Percept &p_0){

}

void IdleStrategy::get_next_command([[maybe_unused]] Actuator &cmd, [[maybe_unused]] const Percept &p){
    cmd.TF_dX_d.setZero();
}

void IdleStrategy::terminate([[maybe_unused]] const Percept &p){

}

bool IdleStrategy::finished(){
    return true;
}

}
