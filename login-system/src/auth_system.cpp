#include "../header/auth_system.h"
#include <iostream>

Authorizing_System::Authorizing_System(sqlite3* database) {
    db = database;
}

// register a new user
bool Authorizing_System::registerUser(const std::string& username, const std::string& password) {
    // SQL statement with placeholders to prevent injection
    std::string sql = "INSERT INTO users (username, password) VALUES (?, ?);";
    
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    // bind username and password to SQL statement
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

    // Execute statment
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cout << "Username taken, registration failed" << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

// login a user
bool Authorizing_System::loginUser(const std::string& username, const std::string& password) {
    std::string sql = "SELECT password FROM users WHERE username = ?;";

    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    // bind username
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

    // check if user exists
    if(sqlite3_step(stmt) == SQLITE_ROW) {
        std::string stored = (const char*)sqlite3_column_text(stmt, 0);  // get stored password

        sqlite3_finalize(stmt);
        return stored == password;  // compared stored password and input password (no hashing for now)
    }

    sqlite3_finalize(stmt);  // false if there is no user
    return false;
}