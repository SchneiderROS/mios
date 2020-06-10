#include "interface/ros_node.hpp"

namespace mios {

RosNode::RosNode():m_spinner(4){

}

void RosNode::start(){
    m_spinner.start();
}

void RosNode::stop(){
    m_spinner.stop();
}

}
