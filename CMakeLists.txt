cmake_minimum_required(VERSION 3.10)
project(MessageBroker)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(MessageBroker main.cpp
                             src/MessageBrokerClient.cpp
                             src/MessageDatabase.cpp
                             src/MessageHandler.cpp)

# Link with Qpid Proton C++ library and SQLite library
target_link_libraries(MessageBroker qpid-proton-cpp sqlite3 pthread)

# Check if Google Test and Google Mock are available
find_package(GTest QUIET)

if(GTest_FOUND)
    # Add Google Test
    enable_testing()
    include_directories(${GTEST_INCLUDE_DIRS})

    # Add test
    add_executable(MessageBrokerClientTest tests/MessageBrokerClientTest.cpp
                                           src/MessageBrokerClient.cpp
                                           src/MessageHandler.cpp
                                           src/MessageDatabase.cpp)

    target_link_libraries(MessageBrokerClientTest ${GTEST_BOTH_LIBRARIES} gmock qpid-proton-cpp sqlite3 pthread)

    # Add the test to CTest
    add_test(MessageBrokerTest MessageBrokerClientTest COMMAND MessageBrokerClientTest)
endif()

