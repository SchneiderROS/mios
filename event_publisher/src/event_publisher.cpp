#include "event_publisher/event_publisher.hpp"

#include "cpp_utils/network.hpp"

namespace mios
{

EventPublisher& EventPublisher::get(){
    static EventPublisher instance;
    return instance;
}

void EventPublisher::publish_event(const nlohmann::json& event){
    get().i_publish_event(event);
}

void EventPublisher::subscribe(const std::pair<std::string,unsigned>& subscriber){
    get().i_subscribe(subscriber);
}

void EventPublisher::i_publish_event(const nlohmann::json &event){
    for(const std::pair<std::string,unsigned>& url : m_subscribers){
        nlohmann::json response;
        if(!cpp_utils::rpc_call(url.first,url.second,"event",{event},response)){

        }
    }
}

void EventPublisher::i_subscribe(const std::pair<std::string, unsigned> &subscriber){
    m_subscribers.insert(subscriber);
}

}
