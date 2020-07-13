#include "strategies/ff_strategy.hpp"
#include "msrm_utils/math.hpp"

namespace mios {

FFStrategy::FFStrategy():PrimitiveStrategy({CommandPatternCartesianFFWrench}){
    m_TF_F_ff.setZero();
    m_TF_F_ff_limiter.setZero();
    m_dF_max.setZero();
}

void FFStrategy::initialize(const Percept &p_0){
}

void FFStrategy::get_next_command(Actuator &cmd, const Percept &p){
    for(unsigned i=0;i<3;i++){
        double diff_TF_F_ff_t = m_TF_F_ff(i)-m_TF_F_ff_limiter(i);
        double diff_TF_F_ff_r = m_TF_F_ff(i+3)-m_TF_F_ff_limiter(i+3);
        if(fabs(diff_TF_F_ff_t)/0.001>m_dF_max(0)){
            cmd.TF_F_ff(i)=m_TF_F_ff_limiter(i)+msrm_utils::sgn(diff_TF_F_ff_t)*m_dF_max(0)*0.001;
        }
        if(fabs(diff_TF_F_ff_r)/0.001>m_dF_max(1)){
            cmd.TF_F_ff(i+3)=m_TF_F_ff_limiter(i+3)+msrm_utils::sgn(diff_TF_F_ff_r)*m_dF_max(1)*0.001;
        }
    }
    m_TF_F_ff_limiter=cmd.TF_F_ff;
}

void FFStrategy::terminate(const Percept &p){

}

bool FFStrategy::finished(){
    return false;
}

void FFStrategy::set_TF_F_ff(const Eigen::Matrix<double,6,1> &TF_F_ff, Eigen::Matrix<double, 2, 1> dF_max){
    m_dF_max=dF_max;
    m_TF_F_ff=TF_F_ff;
}



}
