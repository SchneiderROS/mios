#pragma once
#include <string>

namespace mios{

struct MiosConfiguration {
    std::string verbosity;
    std::string robot_ip;
    std::string database_name;

    unsigned    robot_configuration;
    unsigned    database_port;
    unsigned    websocket_port;
    unsigned    udp_port;
    unsigned    rpc_port;
};

}