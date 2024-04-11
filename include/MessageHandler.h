#pragma once

#include "MessageBrokerClient.h"
#include "MessageDatabase.h"
#include <string>

class MessageHandler : public MessageBrokerClient::MessageListener {
public:
    MessageHandler(const std::string& brokerUrl, const std::string& address,
                   const std::string& dbPath, IMessageBroker* bClient = nullptr, bool isExternal = false);
    ~MessageHandler();

    void sendMessage(const std::string& message);
    void onMessageReceived(const std::string& message) override; // Callback for received messages
    void checkInvalidMessage(const std::string& message);
    std::string retrieveMessage(int messageId); // Method to retrieve a message from the database
    void waitForSender();

private:
    IMessageBroker* brokerClient;
    MessageDatabase messageDb;
    bool externalBrokerClient = false;  // Flag to indicate if brokerClient is externally provided
};
