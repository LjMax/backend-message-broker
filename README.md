# backend-message-broker
Example backend application built with qpid proton that sends and receives amqp messages

# Prerequisites
Before building and running this project, you will need the following:

* A C++ compiler that supports C++17 (e.g., GCC, Clang, MSVC)

* CMake (version 3.10 or higher)

* Apache Qpid Proton C++ library for AMQP messaging

* SQLite3 library for database interactions

* Google Test and Google Mock for running tests (optional)

# Building the Project

To build the project, follow these steps:

1. Clone the repository:
   
   `git clone https://github.com/yourusername/message-broker-client.git
cd message-broker-client`

2. Create a build directory and navigate to it:

   `mkdir build`
   
   `cd build`

3. Run CMake to configure the build and generate the Makefiles:

   `cmake ..`

4. Build the project:

   `make`

# Running the Client

After building the project, you can run the client executable from the build directory:

   `./MessageBrokerClient`

Ensure that your AMQP message broker is running and accessible at the configured URL and address.

# Running Tests

If you have Google Test and Google Mock installed, you can build and run the tests using the following commands:

1. Build the tests:

   `make MessageBrokerClientTest`

2. Run the tests:

   `./MessageBrokerClientTest`

The tests will verify the functionality of the message broker client, including message sending and receiving.


