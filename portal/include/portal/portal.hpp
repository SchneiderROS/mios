#pragma once

#include <functional>
#include <vector>
#include <map>
#include <nlohmann/json.hpp>
#include <msrm_utils/network.hpp>

namespace mios {

enum JsonServers{Websocket,RPC,UDP};

class Portal{
public:
    Portal(const std::string& websocket_address, unsigned websocket_port, const std::string& websocket_endpoint,
           const std::string& rpc_address, unsigned rpc_port, unsigned udp_port);
    Portal(const Portal&) = delete;
    ~Portal();

    void bind_method_to_websocket_server(const char* method_name, std::function<nlohmann::json(const nlohmann::json&)> method_callback, const std::vector<msrm_utils::ArgPair> &method_arguments);
    void bind_method_to_rpc_server(const char* method_name, std::function<nlohmann::json(const nlohmann::json&)> method_callback, const std::vector<msrm_utils::ArgPair> &method_arguments);
    void bind_method_to_udp_server(const char* method_name, std::function<nlohmann::json(const nlohmann::json&)> method_callback, const std::vector<msrm_utils::ArgPair> &method_arguments);
    void bind_method_to_all(const char* method_name, std::function<nlohmann::json(const nlohmann::json&)> method_callback, const std::vector<msrm_utils::ArgPair> &method_arguments);

private:
    std::map<JsonServers,std::unique_ptr<msrm_utils::IJsonMethodServer> > m_servers;
};

}
