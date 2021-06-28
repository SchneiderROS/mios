#pragma once

#include <vector>
#include <string>
#include <memory>
#include "Eigen/Core"

class cntr_nullsp_projModelClass;

namespace cntr_nullsp_proj {

struct P_cntr_nullsp_proj{
Eigen::Matrix<double,1,1> singlr_comp_mode;
Eigen::Matrix<double,1,1> singlr_threshold;
P_cntr_nullsp_proj(){
singlr_comp_mode.setZero();
singlr_threshold.setZero();
}
};
struct U_cntr_nullsp_proj{
Eigen::Matrix<double,7,1> tau_c;
Eigen::Matrix<double,7,7> M;
Eigen::Matrix<double,6,7> J;
U_cntr_nullsp_proj(){
tau_c.setZero();
M.setZero();
J.setZero();
}
};
struct Y_cntr_nullsp_proj{
Eigen::Matrix<double,7,1> tau_n;
Y_cntr_nullsp_proj(){
tau_n.setZero();
}
};
struct L_cntr_nullsp_proj{
Eigen::Matrix<double,1,1> singlr_flag;
L_cntr_nullsp_proj(){
singlr_flag.setZero();
}
};
class cntr_nullsp_proj{
public:
cntr_nullsp_proj();
~cntr_nullsp_proj();
void initialize(bool log = false,unsigned long long l_len = 0,const std::string& path_logs="");
void step();
void terminate();
P_cntr_nullsp_proj p;
U_cntr_nullsp_proj u;
Y_cntr_nullsp_proj y;
L_cntr_nullsp_proj l;

private:
void write_input();
void write_output();
void write_log();
std::unique_ptr<cntr_nullsp_projModelClass> m_model;
std::vector<U_cntr_nullsp_proj> m_log_u;
std::vector<Y_cntr_nullsp_proj> m_log_y;
std::vector<L_cntr_nullsp_proj> m_log_l;
std::string m_path_logs;
unsigned long long m_cnt_step;
bool m_flag_log;};

}