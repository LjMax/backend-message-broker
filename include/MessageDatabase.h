#pragma once

#include <string>
#include <sqlite3.h>

class MessageDatabase {
public:
    MessageDatabase(const std::string& dbPath);
    ~MessageDatabase();
    void persistMessage(const std::string& message);
    std::string retrieveMessage(int messageId);

private:
    sqlite3* db;
    void openDatabase(const std::string& dbPath);
    void closeDatabase();
    void initializeDatabase(); // method to initialize the database schema
};
