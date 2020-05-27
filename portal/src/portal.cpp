#include "portal/portal.hpp"

#include <msrm_utils/network.hpp>
#include <spdlog/spdlog.h>

namespace mios {

Portal::Portal(const std::string &websocket_address, unsigned websocket_port, const std::string &websocket_endpoint, const std::string &rpc_address, unsigned rpc_port, unsigned udp_port){
    spdlog::info("Initializing portal...");
    m_servers.insert(std::make_pair(JsonServers::Websocket,std::make_unique<msrm_utils::JsonWebsocketServer>(websocket_address,websocket_port,websocket_endpoint)));
    m_servers.insert(std::make_pair(JsonServers::RPC,std::make_unique<msrm_utils::JsonRPCServer>(rpc_address,rpc_port)));
    m_servers.insert(std::make_pair(JsonServers::UDP,std::make_unique<msrm_utils::JsonUDPServer>(udp_port)));
    unsigned n_failures=0;
    for(const auto& s : m_servers){
        if(!s.second->start_listening()){
            n_failures++;
            if(s.first==JsonServers::Websocket){
                spdlog::warn("Could not start websocket server with parameters: [address: "+websocket_address+", port: "+std::to_string(websocket_port)+", endpoint: "+websocket_endpoint+"]");
            }
            if(s.first==JsonServers::Websocket){
                spdlog::warn("Could not start rpc server with parameters: [address: "+rpc_address+", port: "+std::to_string(rpc_port)+"]");
            }
            if(s.first==JsonServers::UDP){
                spdlog::warn("Could not start udp server with parameters: [port: "+std::to_string(udp_port)+"]");
            }
        }
    }
    if(n_failures>=m_servers.size()){
        spdlog::critical("Could not start any communication interfaces.");
    }
}

Portal::~Portal(){
    for(const auto& s : m_servers){
        s.second->stop_listening();
    }
}

void Portal::bind_method_to_websocket_server(const char *method_name, std::function<nlohmann::json (const nlohmann::json &)> method_callback,
                                               const std::vector<msrm_utils::ArgPair> &method_arguments){
    m_servers[JsonServers::Websocket]->bind_method(method_name,method_callback,method_arguments);
}

void Portal::bind_method_to_rpc_server(const char *method_name, std::function<nlohmann::json (const nlohmann::json &)> method_callback,const std::vector<msrm_utils::ArgPair> &method_arguments){
    m_servers[JsonServers::RPC]->bind_method(method_name,method_callback,method_arguments);
}

void Portal::bind_method_to_udp_server(const char *method_name, std::function<nlohmann::json (const nlohmann::json &)> method_callback,const std::vector<msrm_utils::ArgPair> &method_arguments){
    m_servers[JsonServers::UDP]->bind_method(method_name,method_callback,method_arguments);
}

void Portal::bind_method_to_all(const char *method_name, std::function<nlohmann::json (const nlohmann::json &)> method_callback,const std::vector<msrm_utils::ArgPair> &method_arguments){
    for(const auto& s : m_servers){
        if(!s.second->bind_method(method_name,method_callback,method_arguments)){
            if(s.first==JsonServers::Websocket){
                spdlog::warn("Could not bind method with name "+std::string(method_name)+" to websocket server.");
            }
            if(s.first==JsonServers::Websocket){
                spdlog::warn("Could not bind method with name "+std::string(method_name)+" to rpc server.");
            }
            if(s.first==JsonServers::UDP){
                spdlog::warn("Could not bind method with name "+std::string(method_name)+" to udp server.");
            }
        }
    }
}

}
