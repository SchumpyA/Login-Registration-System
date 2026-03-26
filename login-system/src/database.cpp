#include "../header/database.h"
#include <iostream>

Database::Database(const char* filename) {  // open SQL database file
    if (sqlite3_open(filename, &db)) {
        std::cout << "Error opening DB" << std::endl;
    }
}

Database::~Database() {  // close database connection on destruction
    sqlite3_close(db);
}

// Initialize database tables
void Database::init() {
    // create a table if it doesn't exist
    const char* sql = "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT UNIQUE, password TEXT);";
    char* errMsg = nullptr;
    sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);
}