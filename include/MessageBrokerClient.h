#pragma once

#include "IMessageBroker.h"

#include <proton/messaging_handler.hpp>
#include <proton/connection.hpp>
#include <proton/sender.hpp>
#include <proton/receiver.hpp>

#include <string>
#include <mutex>
#include <condition_variable>

class MessageBrokerClient : public proton::messaging_handler, public IMessageBroker {

public:

    class MessageListener {
    public:
        virtual void onMessageReceived(const std::string& message) = 0;
    };

    MessageBrokerClient(const std::string& url, const std::string& address, MessageListener* listener);


    MessageBrokerClient(const std::string& url, const std::string& address);
    void send_message(const std::string& message_text) override;
    void wait_for_sender() override;

    void wait_for_message_received();
    void reset_message_received(); // Method to reset the message received flag

protected:
    void on_container_start(proton::container& container) override;
    void on_message(proton::delivery& delivery, proton::message& message) override;

private:
    MessageListener* listener;
    std::string url;
    std::string address;
    proton::sender sender;
    proton::receiver receiver;

    // Synchronization members
    std::mutex message_received_mutex_;
    std::condition_variable message_received_cond_;
    bool message_received_ = false;

    std::mutex mutex_;
    std::condition_variable sender_ready_;
    bool is_sender_active_ = false;
};
