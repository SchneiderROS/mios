#include "utils/actuator.hpp"
#include <spdlog/spdlog.h>
#include <msrm_utils/math.hpp>

namespace mios {

Actuator::Actuator(const Percept &p_0){
    initialize(p_0);
}

void Actuator::initialize(const Percept &p_0){
    TF_T_EE_d=p_0.Proprioception.TF_T_EE;
    TF_dX_d.setZero();
    TF_F_d.setZero();
    TF_F_ff.setZero();
    K_x=p_0.Controller.K_x;
    xi_x=p_0.Controller.xi_x;

    q_d=p_0.Proprioception.q;
    dq_d.setZero();
    tau_d.setZero();
    tau_ff.setZero();
    K_theta=p_0.Controller.K_theta;
    xi_theta=p_0.Controller.xi_theta;
}

void Actuator::stop(){
    m_stop=true;
}

void Actuator::read_from_buffer(){
    TF_T_EE_d=m_TF_T_EE_d_buffer;
    TF_dX_d=m_TF_dX_d_buffer;
    TF_F_d=m_TF_F_d_buffer;
    TF_F_ff=m_TF_F_ff_buffer;
    K_x=m_K_x_buffer;
    xi_x=m_xi_x_buffer;

    q_d=m_q_d_buffer;
    dq_d=m_dq_d_buffer;
    tau_d=m_tau_d_buffer;
    tau_ff=m_tau_ff_buffer;
    K_theta=m_K_theta_buffer;
    xi_theta=m_xi_theta_buffer;
}

void Actuator::limit_output(const ConfigLimits &config){
    for(unsigned i=0;i<7;i++){
        if(q_d[i]>config.q_upper(i)){
            q_d[i]=config.q_upper(i);
        }
        if(q_d[i]<config.q_lower(i)){
            q_d[i]=config.q_lower(i);
        }
    }

    // Check for joint velocity limits
    for(unsigned i=0;i<7;i++){
        if(dq_d(i)>config.dq_max(i)){
            dq_d(i)=config.dq_max(i);
        }
        if(dq_d(i)<-config.dq_max(i)){
            dq_d(i)=-config.dq_max(i);
        }
    }

    // Check for joint stiffness limits
    for(unsigned i=0;i<7;i++){
        if(K_theta(i)>config.K_theta_max(i)){
            K_theta(i)=config.K_theta_max(i);
        }
        if(K_theta(i)<0){
            K_theta(i)=0;
        }
        if(xi_theta(i)>config.xi_theta_max(i)){
            xi_theta(i)=config.xi_theta_max(i);
        }
        if(xi_theta(i)<0){
            xi_theta(i)=0;
        }
    }

    // Check for Cartesian pose limits
    for(unsigned i=0;i<3;i++){
        if(TF_T_EE_d(i,3)>config.x_upper(i)){
            TF_T_EE_d(i,3)=config.x_upper(i);
        }
        if(TF_T_EE_d(i,3)<config.x_lower(i)){
            TF_T_EE_d(i,3)=config.x_lower(i);
        }
    }

    // Check for Cartesian stiffness limits
    for(unsigned i=0;i<6;i++){
        if(K_x(i)>config.K_x_max(i)){
            K_x(i)=config.K_x_max(i);
        }
        if(K_x(i)<0){
            K_x(i)=0;
        }
        if(xi_x(i)>config.xi_x_max(i)){
            xi_x(i)=config.xi_x_max(i);
        }
        if(xi_x(i)<0){
            xi_x(i)=0;
        }
    }

    // Check for Cartesian velocity limits
    for(unsigned i=0;i<3;i++){
        if(TF_dX_d(i)>config.dX_max(0)){
            TF_dX_d(i)=config.dX_max(0);
        }
        if(TF_dX_d(i)<-config.dX_max(0)){
            TF_dX_d(i)=-config.dX_max(0);
        }
        if(TF_dX_d(i+3)>config.dX_max(1)){
            TF_dX_d(i+3)=config.dX_max(1);
        }
        if(TF_dX_d(i+3)<-config.dX_max(1)){
            TF_dX_d(i+3)=-config.dX_max(1);
        }
    }
}

void Actuator::limit_output_rate(const ConfigLimits &config){
    for(unsigned i=0;i<3;i++){
        double diff_dX_t = TF_dX_d(i)-m_TF_dX_d_limiter[i];
        double diff_dX_r = TF_dX_d(i+3)-m_TF_dX_d_limiter[i+3];
        double diff_dF_t = TF_F_d(i)-m_TF_F_d_limiter(i);
        double diff_dF_r = TF_F_d(i+3)-m_TF_F_d_limiter(i+3);
        double diff_dF_ff_t = TF_F_ff(i)-m_TF_F_ff_limiter(i);
        double diff_dF_ff_r = TF_F_ff(i+3)-m_TF_F_ff_limiter(i+3);
        if(fabs(diff_dX_t)/0.001>config.ddX_max[0]){
            TF_dX_d(i)=m_TF_dX_d_limiter(i)+msrm_utils::sgn(diff_dX_t)*config.ddX_max(0)*0.001;
        }
        if(fabs(diff_dX_r)/0.001>config.ddX_max[1]){
            TF_dX_d(i+3)=m_TF_dX_d_limiter(i+3)+msrm_utils::sgn(diff_dX_r)*config.ddX_max(1)*0.001;
        }
        if(fabs(diff_dF_t)/0.001>config.dF_J_max[0]){
            TF_F_d(i)=m_TF_F_d_limiter(i)+msrm_utils::sgn(diff_dF_t)*config.dF_J_max(0)*0.001;
        }
        if(fabs(diff_dF_r)/0.001>config.dF_J_max[1]){
            TF_F_d(i+3)=m_TF_F_d_limiter(i+3)+msrm_utils::sgn(diff_dF_r)*config.dF_J_max(1)*0.001;
        }
        if(fabs(diff_dF_ff_t)/0.001>config.dF_J_max[0]){
            TF_F_ff(i)=m_TF_F_ff_limiter(i)+msrm_utils::sgn(diff_dF_ff_t)*config.dF_J_max(0)*0.001;
        }
        if(fabs(diff_dF_ff_r)/0.001>config.dF_J_max[1]){
            TF_F_ff(i+3)=m_TF_F_ff_limiter(i+3)+msrm_utils::sgn(diff_dF_ff_r)*config.dF_J_max(1)*0.001;
        }
    }

    for(unsigned i=0;i<6;i++){
        double diff_K_x = K_x(i)-m_K_x_limiter[i];
        double diff_xi_x = xi_x(i)-m_xi_x_limiter[i];
        if(fabs(diff_K_x)/0.001>config.dK_x_max[i]){
            K_x(i)=m_K_x_limiter(i)+msrm_utils::sgn(diff_K_x)*config.dK_x_max(i)*0.001;
        }
        if(fabs(diff_xi_x)/0.001>config.dxi_x_max[i]){
            xi_x(i)=m_xi_x_limiter(i)+msrm_utils::sgn(diff_xi_x)*config.dxi_x_max(i)*0.001;
        }
    }


    for(unsigned i=0;i<7;i++){
        double diff_q = q_d(i)-m_q_d_limiter(i);
        double diff_dq = dq_d(i)-m_dq_d_limiter(i);
        double diff_tau = tau_d(i)-m_tau_d_limiter(i);
        double diff_tau_ff = tau_ff(i)-m_tau_ff_limiter(i);
        double diff_K_theta = K_theta(i)-m_K_theta_limiter(i);
        double diff_xi_theta = xi_theta(i)-m_xi_theta_limiter(i);
        if(fabs(diff_q)/0.001>config.dq_max(i)){
            q_d(i)=m_q_d_limiter(i)+msrm_utils::sgn(diff_q)*config.dq_max(i)*0.001;
        }
        if(fabs(diff_dq)/0.001>config.ddq_max(i)){
            dq_d(i)=m_dq_d_limiter(i)+msrm_utils::sgn(diff_dq)*config.ddq_max(i)*0.001;
        }
        if(fabs(diff_tau)/0.001>config.tau_J_max(i)){
            tau_d(i)=m_tau_d_limiter(i)+msrm_utils::sgn(diff_tau)*config.tau_J_max(i)*0.001;
        }
        if(fabs(diff_tau_ff)/0.001>config.tau_J_max(i)){
            tau_ff(i)=m_tau_ff_limiter(i)+msrm_utils::sgn(diff_tau_ff)*config.tau_J_max(i)*0.001;
        }
        if(fabs(diff_K_theta)/0.001>config.dK_theta_max(i)){
            K_theta(i)=m_K_theta_limiter(i)+msrm_utils::sgn(diff_K_theta)*config.dK_theta_max(i)*0.001;
        }
        if(fabs(diff_xi_theta)/0.001>config.dxi_theta_max(i)){
            xi_theta(i)=m_xi_theta_limiter(i)+msrm_utils::sgn(diff_xi_theta)*config.dxi_theta_max(i)*0.001;
        }
    }
    m_TF_dX_d_limiter=TF_dX_d;
    m_TF_F_d_limiter=TF_F_d;
    m_TF_F_ff_limiter=TF_F_ff;
    m_K_x_limiter=K_x;
    m_xi_x_limiter=xi_x;

    m_q_d_limiter=q_d;
    m_dq_d_limiter=dq_d;
    m_tau_d_limiter=tau_d;
    m_tau_ff_limiter=tau_ff;
    m_K_theta_limiter=K_theta;
    m_xi_theta_limiter=xi_theta;
}

bool Actuator::is_valid() const{
    for(unsigned i=0;i<7;i++){
        if(q_d(i)!=q_d(i)){
            spdlog::error("Detected NaN in skill command at q_d["+std::to_string(i)+"].");
            return false;
        }
        if(dq_d(i)!=dq_d(i)){
            spdlog::error("Detected NaN in skill command at dq_d["+std::to_string(i)+"].");
            return false;
        }
        if(tau_d(i)!=tau_d(i)){
            spdlog::error("Detected NaN in skill command at tau_d["+std::to_string(i)+"].");
            return false;
        }
        if(tau_ff(i)!=tau_ff(i)){
            spdlog::error("Detected NaN in skill command at tau_ff["+std::to_string(i)+"].");
            return false;
        }
        if(K_theta(i)!=K_theta(i)){
            spdlog::error("Detected NaN in skill command at K_theta["+std::to_string(i)+"].");
            return false;
        }
        if(xi_theta(i)!=xi_theta(i)){
            spdlog::error("Detected NaN in skill command at xi_theta["+std::to_string(i)+"].");
            return false;
        }
    }
    for(unsigned i=0;i<6;i++){
        if(TF_dX_d(i)!=TF_dX_d(i)){
            spdlog::error("Detected NaN in skill command at TF_dX_d["+std::to_string(i)+"].");
            return false;
        }
        if(TF_F_d(i)!=TF_F_d(i)){
            spdlog::error("Detected NaN in skill command at TF_F_d["+std::to_string(i)+"].");
            return false;
        }
        if(TF_F_ff(i)!=TF_F_ff(i)){
            spdlog::error("Detected NaN in skill command at TF_F_ff["+std::to_string(i)+"].");
            return false;
        }
        if(K_x(i)!=K_x(i)){
            spdlog::error("Detected NaN in skill command at K_x["+std::to_string(i)+"].");
            return false;
        }
        if(xi_x(i)!=xi_x(i)){
            spdlog::error("Detected NaN in skill command at xi_x["+std::to_string(i)+"].");
            return false;
        }
    }
    for(unsigned i=0;i<4;i++){
        for(unsigned j=0;j<4;j++){
            if(TF_T_EE_d(i)!=TF_T_EE_d(i)){
                spdlog::error("Detected NaN in skill command at TF_T_EE_d["+std::to_string(i)+","+std::to_string(j)+"].");
                return false;
            }
        }
    }
    if(!msrm_utils::is_orthonormal(TF_T_EE_d.block<3,3>(0,0))){
        spdlog::error("Rotation part of TF_T_EE_d is not orthonormal.");
        return false;
    }
    return true;
}

bool Actuator::is_stopped() const{
    return m_stop;
}

bool Actuator::is_settled(const ConfigLimits &config) const{
    bool all_zero=true;
    for(unsigned i=0;i<3;i++){
        if(fabs(TF_dX_d(i))>config.ddX_max(0)/1000/2 ||
                fabs(TF_F_d(i))>config.dF_J_max(0)/1000/2 ||
                fabs(TF_F_ff(i))>config.dF_J_max(0)/1000/2){
            all_zero=false;
            break;
        }
    }
    for(unsigned i=3;i<6;i++){
        if(fabs(TF_dX_d(i))>config.ddX_max(1)/1000/2 ||
                fabs(TF_F_d(i))>config.dF_J_max(1)/1000/2 ||
                fabs(TF_F_ff(i))>config.dF_J_max(1)/1000/2){
            all_zero=false;
            break;
        }
    }
    return all_zero;
}

}
