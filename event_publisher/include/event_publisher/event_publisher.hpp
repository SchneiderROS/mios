#pragma once

#include <vector>
#include <set>
#include <nlohmann/json.hpp>

namespace mios {

struct EventSubscriber{
    std::string uuid;
    std::string address;
    unsigned port;
    std::string endpoint;
    std::string method_name;

    bool operator<(const EventSubscriber& rhs) const
    {
      return uuid < rhs.uuid;
    }

    bool operator==(const EventSubscriber& rhs) const
    {
      return uuid == rhs.uuid;
    }
};

class EventPublisher{
public:
    EventPublisher(const EventPublisher&) = delete;

    static EventPublisher& get();

    static void publish_event(const nlohmann::json& event);
    static std::string subscribe(const EventSubscriber &subscriber);
    static void unsubscribe(const std::string& subscriber_uuid);
private:
    void i_publish_event(const nlohmann::json& event);
    std::string i_subscribe(const EventSubscriber& subscriber);
    void i_unsubscribe(const std::string& subscriber_uuid);
    EventPublisher(){}

    nlohmann::json events;
    std::set<EventSubscriber> m_subscribers;
};

}
