#include "MessageHandler.h"
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    // Replace these
    std::string brokerUrl = "amqp://localhost:5672";
    std::string address = "testQueue";
    std::string dbPath = "messages.db";

    MessageHandler handler(brokerUrl, address, dbPath);

    // Wait for the sender to become active
    handler.waitForSender();

    // Send a message
    handler.sendMessage("Test message!");

    // Wait for the message to be received and processed
    std::this_thread::sleep_for(std::chrono::seconds(10));

    // Retrieve and print the persisted message
    std::string retrievedMessage = handler.retrieveMessage(1);
    std::cout << "Retrieved message: " << retrievedMessage << std::endl;

    std::cout << "exiting! " << std::endl;
    return 0;
}
