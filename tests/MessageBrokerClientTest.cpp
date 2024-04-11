#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "MessageHandler.h"
#include "MessageBrokerClient.h"
#include "MockMessageListener.h"
#include "MockMessageBrokerClient.h"

using ::testing::Return;
using ::testing::_;
using ::testing::StrEq;

TEST(MessageBrokerClientTest, SendMessageAndReceive) {
    // Create a mock message listener
    MockMessageListener mockListener;

    // Expect the mock listener to receive a message
    EXPECT_CALL(mockListener, onMessageReceived("MessageBrokerClientTest")).Times(1);

    // Create the message broker client with the mock listener
    MessageBrokerClient client("amqp://localhost:5672", "testQueue", &mockListener);

    // Wait for the sender to be ready
    client.wait_for_sender();

    // Send a message
    client.send_message("MessageBrokerClientTest");

    // Wait for the message to be received
    client.wait_for_message_received();
}

TEST(MessageHandlerInvalidMessageTest, CheckInvalidMessageSendsMessage) {
    MockMessageBrokerClient mockBrokerClient;
    MessageHandler messageHandler("amqp://localhost:5672", "testQueue", "testMessages.db", &mockBrokerClient, true);

    // Expect the broker client to send a message when an invalid message is received
    EXPECT_CALL(mockBrokerClient, send_message(StrEq("Invalid message received: INVALID"))).Times(1);

    // Simulate receiving an invalid message
    messageHandler.onMessageReceived("INVALID");
}
