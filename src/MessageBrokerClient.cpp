#include "MessageBrokerClient.h"

#include <proton/container.hpp> // Include for proton::container
#include <proton/message.hpp>   // Include for proton::message
#include <proton/delivery.hpp> // Include for proton::delivery
#include <iostream>
#include <thread>

MessageBrokerClient::MessageBrokerClient(const std::string& url, const std::string& address, MessageListener* listener)
    : url(url), address(address), listener(listener) {

    // Create and start the container in a separate thread
    std::thread([this]() {
        proton::container container(*this);
        container.run();
    }).detach();
}

void MessageBrokerClient::on_container_start(proton::container& container) {
    proton::connection conn = container.connect(url);
    sender = conn.open_sender(address);
    receiver = conn.open_receiver(address);

    // Notify that the sender is active
    {
        std::lock_guard<std::mutex> lock(mutex_);
        is_sender_active_ = true;
    }
    sender_ready_.notify_one();
}

void MessageBrokerClient::send_message(const std::string& message_text) {

    if (!sender || !sender.active()) {
        std::cerr << "Sender is not active. Cannot send message." << std::endl;
        return;
    }

    proton::message message;
    message.body(message_text);

    std::cout << "Sending message: " << message_text << std::endl;
    sender.send(message);
}

void MessageBrokerClient::on_message(proton::delivery& delivery, proton::message& message) {
    std::string received_message = proton::get<std::string>(message.body());
    std::cout << "Received message: " << received_message << std::endl;

    if (listener) {
        listener->onMessageReceived(received_message);
    }

    delivery.accept();

    // Signal the condition variable
    {
        std::lock_guard<std::mutex> lock(message_received_mutex_);
        message_received_ = true;
        message_received_cond_.notify_one();
    }
}

void MessageBrokerClient::wait_for_sender() {
    std::unique_lock<std::mutex> lock(mutex_);
    sender_ready_.wait(lock, [this] { return is_sender_active_; });
}

void MessageBrokerClient::wait_for_message_received() {
    std::unique_lock<std::mutex> lock(message_received_mutex_);
    message_received_cond_.wait(lock, [this] { return message_received_; });
}

// Method to reset the message received flag
void MessageBrokerClient::reset_message_received() {
    std::lock_guard<std::mutex> lock(message_received_mutex_);
    message_received_ = false;
}
