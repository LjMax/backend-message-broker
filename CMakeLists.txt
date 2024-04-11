cmake_minimum_required(VERSION 3.10)
project(MessageBroker)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

# Add Google Test
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(MessageBroker main.cpp
                             src/MessageBrokerClient.cpp
                             src/MessageDatabase.cpp
                             src/MessageHandler.cpp)

# Link with Qpid Proton C++ library and SQLite library
target_link_libraries(MessageBroker qpid-proton-cpp sqlite3 pthread)

# Add test
add_executable(MessageBrokerClientTest tests/MessageBrokerClientTest.cpp
                                       src/MessageBrokerClient.cpp
                                       src/MessageHandler.cpp
                                       src/MessageDatabase.cpp)

target_link_libraries(MessageBrokerClientTest ${GTEST_BOTH_LIBRARIES} gmock qpid-proton-cpp sqlite3 pthread)

# Add the test to CTest
add_test(BrokerTest MessageBrokerClientTest COMMAND MessageBrokerClientTest)
