#include "IMessageBroker.h"
#include <gmock/gmock.h>

class MockMessageBrokerClient : public IMessageBroker {
public:
    MOCK_METHOD(void, send_message, (const std::string& message), (override));
    MOCK_METHOD(void, wait_for_sender, (), (override));
};
