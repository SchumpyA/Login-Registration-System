#include "../header/database.h"
#include <iostream>

Database::Database(const char* filename) {
    if (sqlite3_open(filename, &db)) {
        std::cout << "Error opening DB" << std::endl;
    }
}

Database::~Database() {
    sqlite3_close(db);
}

void Database::init() {
    const char* sql = "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT UNIQUE, password TEXT);";
    char* errMsg = nullptr;
    sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);
}