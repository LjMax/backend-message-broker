#include "MessageBrokerClient.h"
#include <gmock/gmock.h>

class MockMessageListener : public MessageBrokerClient::MessageListener {
public:
    MOCK_METHOD(void, onMessageReceived, (const std::string& message), (override));
};
