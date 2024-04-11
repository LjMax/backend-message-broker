#include "MessageHandler.h"

MessageHandler::MessageHandler(const std::string& brokerUrl, const std::string& address,
                               const std::string& dbPath, IMessageBroker* bClient, bool isExternal)
    : brokerClient(bClient ? bClient : new MessageBrokerClient(brokerUrl, address, this)),
      messageDb(dbPath),
      externalBrokerClient(isExternal) {}

MessageHandler::~MessageHandler() {
    // Only delete if brokerClient is not pointing to an external object
    if (!externalBrokerClient) {
        delete brokerClient;
    }
}

void MessageHandler::sendMessage(const std::string& message) {
    brokerClient->send_message(message);
}

void MessageHandler::onMessageReceived(const std::string& message) {
    messageDb.persistMessage(message);

    checkInvalidMessage(message);
}

void MessageHandler::checkInvalidMessage(const std::string& message) {
    // Some kind of logic is needed here, like what type of message would be considered invalid
    // placeholder here
    if (message == "INVALID") {
        sendMessage("Invalid message received: " + message);
    }
}

std::string MessageHandler::retrieveMessage(int messageId) {
    return messageDb.retrieveMessage(messageId);
}

void MessageHandler::waitForSender()
{
    brokerClient->wait_for_sender();
}
