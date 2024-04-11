#include "MessageDatabase.h"
#include <iostream>

MessageDatabase::MessageDatabase(const std::string& dbPath) {
    openDatabase(dbPath);
    initializeDatabase(); // Initialize the database schema after opening the database
}

MessageDatabase::~MessageDatabase() {
    closeDatabase();
}

void MessageDatabase::openDatabase(const std::string& dbPath) {
    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
    }
}

void MessageDatabase::closeDatabase() {
    if (db) {
        sqlite3_close(db);
    }
}

void MessageDatabase::persistMessage(const std::string& message) {
    std::string sql = "INSERT INTO messages (content) VALUES ('" + message + "');";
    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Error inserting message: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

std::string MessageDatabase::retrieveMessage(int messageId) {
    std::string sql = "SELECT content FROM messages WHERE id = " + std::to_string(messageId) + ";";
    std::string message;
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            message = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        }
        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Error retrieving message: " << sqlite3_errmsg(db) << std::endl;
    }
    return message;
}

void MessageDatabase::initializeDatabase() {
    std::string sql = "CREATE TABLE IF NOT EXISTS messages ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "content TEXT);";
    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Error initializing database: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}
