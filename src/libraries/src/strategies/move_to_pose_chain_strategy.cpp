#include "mios/strategies/move_to_pose_chain_strategy.hpp"

namespace mios{

MoveToPoseChainStrategy::MoveToPoseChainStrategy():PrimitiveStrategy({CommandPatternCartesianTwist}){
    m_cnt=0;
}

void MoveToPoseChainStrategy::initialize(const Percept &p_0){
}

void MoveToPoseChainStrategy::get_next_command(Actuator &cmd, [[maybe_unused]] const Percept &p){
}

void MoveToPoseChainStrategy::terminate([[maybe_unused]] const Percept &p){
}

bool MoveToPoseChainStrategy::finished(){
}

void MoveToPoseChainStrategy::set_goal(const std::vector<Eigen::Matrix<double,4,4> >& T_EE_d_chain, const Eigen::Matrix<double,2,1>& dX_d, const Eigen::Matrix<double,2,1>& ddX_d){
    m_T_EE_d_chain=T_EE_d_chain;
    m_dX_d=dX_d;
    m_ddX_d=ddX_d;
}

}
