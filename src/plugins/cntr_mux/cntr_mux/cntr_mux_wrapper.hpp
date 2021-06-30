#pragma once

#include <vector>
#include <string>
#include <memory>
#include "Eigen/Core"

class cntr_muxModelClass;

namespace cntr_mux {

struct P_cntr_mux{
Eigen::Matrix<double,7,1> tau_max;
Eigen::Matrix<double,7,1> dtau_max;
P_cntr_mux(){
tau_max.setZero();
dtau_max.setZero();
}
};
struct U_cntr_mux{
Eigen::Matrix<double,7,1> tau_J_d;
Eigen::Matrix<double,6,7> B_J_EE;
U_cntr_mux(){
tau_J_d.setZero();
B_J_EE.setZero();
}
};
struct Y_cntr_mux{
Eigen::Matrix<double,7,1> tau_J_d_checked;
Y_cntr_mux(){
tau_J_d_checked.setZero();
}
};
struct L_cntr_mux{
Eigen::Matrix<double,1,1> valid_cart;
L_cntr_mux(){
valid_cart.setZero();
}
};
class cntr_mux{
public:
cntr_mux();
~cntr_mux();
void initialize(bool log = false,unsigned long long l_len = 0,const std::string& path_logs="");
void step();
void terminate();
P_cntr_mux p;
U_cntr_mux u;
Y_cntr_mux y;
L_cntr_mux l;

private:
void write_input();
void write_output();
void write_log();
std::unique_ptr<cntr_muxModelClass> m_model;
std::vector<U_cntr_mux> m_log_u;
std::vector<Y_cntr_mux> m_log_y;
std::vector<L_cntr_mux> m_log_l;
std::string m_path_logs;
unsigned long long m_cnt_step;
bool m_flag_log;};

}