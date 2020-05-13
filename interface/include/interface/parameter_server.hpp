#pragma once

#pragma once

#include <string>
#include <deque>
#include <array>
#include <thread>
#include <functional>

#include <msrm_utils/network.hpp>
#include <msrm_utils/output.hpp>

namespace mios {

class ParameterServer{
public:
    ParameterServer(unsigned port);

    void initialize();
    void start();
    void stop();

    nlohmann::json get_parameter(const std::string& parameter);

private:
    void bind_methods();

    nlohmann::json set_parameter(const nlohmann::json &parameter);

    msrm_utils::JsonUDPServer _ws_server;
    std::map<std::string,nlohmann::json> _parameters;
    std::mutex _mtx_parameters;
};

}
