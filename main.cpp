#include "MessageHandler.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <string>

int main(int argc, char *argv[]) {
    // Replace these
    std::string brokerUrl = "amqp://localhost:5672";
    std::string address   = "testQueue";
    std::string dbPath    = "messages.db";
    std::string message   = "";

    // accept command line arguments (optional)
    if(argc > 1) {
        switch (argc) {
        case 2:
            brokerUrl = argv[1];
            break;
        case 3:
            brokerUrl = argv[1];
            address   = argv[2];
            break;
        case 4:
            brokerUrl = argv[1];
            address   = argv[2];
            dbPath    = argv[3];
            break;
        case 5:
            brokerUrl = argv[1];
            address   = argv[2];
            dbPath    = argv[3];
            message   = argv[4];
            break;
        default:
            break;
        }
    }

    MessageHandler handler(brokerUrl, address, dbPath);

    // Wait for the sender to become active
    handler.waitForSender();

    // Send a message
    handler.sendMessage(message.empty() ? "Test message!" : message);

    // Wait for the message to be received and processed
    std::this_thread::sleep_for(std::chrono::seconds(10));

    // Retrieve and print the persisted message
    std::string retrievedMessage = handler.retrieveMessage(1);
    std::cout << "Retrieved message: " << retrievedMessage << std::endl;

    std::cout << "exiting! " << std::endl;
    return 0;
}
