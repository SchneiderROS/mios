#include "event_publisher/event_publisher.hpp"

#include <msrm_utils/network.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <sstream>

namespace mios
{

EventPublisher& EventPublisher::get(){
    static EventPublisher instance;
    return instance;
}

void EventPublisher::publish_event(const nlohmann::json& event){
    get().i_publish_event(event);
}

std::string EventPublisher::subscribe(const EventSubscriber& subscriber){
    return get().i_subscribe(subscriber);
}

void EventPublisher::unsubscribe(const std::string& subscriber_uuid){
    get().i_unsubscribe(subscriber_uuid);
}

void EventPublisher::i_publish_event(const nlohmann::json &event){
    for(const EventSubscriber& subscriber : m_subscribers){
        nlohmann::json response;
        msrm_utils::JsonWebsocketClient::call_method(subscriber.address,subscriber.port,subscriber.endpoint,subscriber.method_name,event,response);
    }
}

std::string EventPublisher::i_subscribe(const EventSubscriber& subscriber){
    if(m_subscribers.find(subscriber)!=m_subscribers.end()){
        m_subscribers.erase(m_subscribers.find(subscriber));
    }
    m_subscribers.insert(subscriber);
    boost::uuids::uuid task_uuid = boost::uuids::random_generator()();
    std::stringstream ss;
    ss<<task_uuid;
    return ss.str();
}

void EventPublisher::i_unsubscribe(const std::string &subscriber_uuid){
    EventSubscriber tmp_sub;
    tmp_sub.uuid=subscriber_uuid;
    if(m_subscribers.find(tmp_sub)!=m_subscribers.end()){
        m_subscribers.erase(m_subscribers.find(tmp_sub));
    }
}

}
