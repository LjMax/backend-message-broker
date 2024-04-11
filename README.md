# backend-message-broker
Example backend application built with qpid proton that sends and receives amqp messages

# Prerequisites
Before building and running this project, you will need the following:

* A C++ compiler that supports C++17 (e.g., GCC, Clang, MSVC)

* [CMake](https://cmake.org/) (version 3.10 or higher)

* [Apache Qpid Proton C++ library](https://qpid.apache.org/proton/index.html) for AMQP messaging

* [SQLite3 library](https://www.sqlite.org/) for database interactions

* [Google Test](https://github.com/google/googletest) and [Google Mock](https://github.com/google/googletest/tree/main/googlemock) for running tests (optional)

# Building the Project

To build the project, follow these steps:

1. Clone the repository:
   
   `git clone https://github.com/LjMax/backend-message-broker.git`
   
   `cd backend-message-broker`

3. Create a build directory and navigate to it:

   `mkdir build`
   
   `cd build`

4. Run CMake to configure the build and generate the Makefiles:

   `cmake ..`

5. Build the project:

   `make`

# Running the Client

After building the project, you can run the client executable from the build directory:

   `./MessageBroker`

Ensure that your AMQP message broker is running and accessible at the configured URL and address.

For this example [Apache ActiveMQ (version 5.18.3)](https://activemq.apache.org/components/classic/download/) was used as the message broker.

# Running Tests

If you have Google Test and Google Mock installed, the test will be built with the main application.


* Run the tests:

   `./MessageBrokerClientTest`

* Alternatively you can also use:

   `ctest`

The tests will verify the functionality of the message broker client, including message sending and receiving.


