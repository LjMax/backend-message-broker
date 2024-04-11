#pragma once

#include <string>

class IMessageBroker {

public:
    virtual void send_message(const std::string& message) = 0;
    virtual void wait_for_sender() = 0;
    virtual ~IMessageBroker() = default;
}; 
