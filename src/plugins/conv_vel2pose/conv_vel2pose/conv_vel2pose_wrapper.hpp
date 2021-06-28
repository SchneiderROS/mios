#pragma once

#include <vector>
#include <string>
#include <memory>
#include "Eigen/Core"

class conv_vel2poseModelClass;

namespace conv_vel2pose {

struct P_conv_vel2pose{
P_conv_vel2pose(){
}
};
struct U_conv_vel2pose{
Eigen::Matrix<double,6,1> TF_dX_d;
Eigen::Matrix<double,4,4> TF_T_EE;
Eigen::Matrix<double,1,1> reset;
U_conv_vel2pose(){
TF_dX_d.setZero();
TF_T_EE.setZero();
reset.setZero();
}
};
struct Y_conv_vel2pose{
Eigen::Matrix<double,4,4> TF_T_EE_d;
Y_conv_vel2pose(){
TF_T_EE_d.setZero();
}
};
struct L_conv_vel2pose{
L_conv_vel2pose(){
}
};
class conv_vel2pose{
public:
conv_vel2pose();
~conv_vel2pose();
void initialize(bool log = false,unsigned long long l_len = 0,const std::string& path_logs="");
void step();
void terminate();
P_conv_vel2pose p;
U_conv_vel2pose u;
Y_conv_vel2pose y;
L_conv_vel2pose l;

private:
void write_input();
void write_output();
void write_log();
std::unique_ptr<conv_vel2poseModelClass> m_model;
std::vector<U_conv_vel2pose> m_log_u;
std::vector<Y_conv_vel2pose> m_log_y;
std::vector<L_conv_vel2pose> m_log_l;
std::string m_path_logs;
unsigned long long m_cnt_step;
bool m_flag_log;};

}