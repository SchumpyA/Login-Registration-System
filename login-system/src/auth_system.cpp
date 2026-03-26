#include "../header/auth_system.h"
#include <iostream>

Authorizing_System::Authorizing_System(sqlite3* database) {
    db = database;
}

bool Authorizing_System::registerUser(const std::string& username, const std::string& password) {
    std::string sql = "INSERT INTO users (username, password) VALUES (?, ?);";
    
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cout << "Registration failed" << std::endl;
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

bool Authorizing_System::loginUser(const std::string& username, const std::string& password) {
    std::string sql = "SELECT password FROM users WHERE username = ?;";

    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

    if(sqlite3_step(stmt) == SQLITE_ROW) {
        std::string stored = (const char*)sqlite3_column_text(stmt, 0);

        sqlite3_finalize(stmt);
        return stored == password;  // no hashing for now
    }

    sqlite3_finalize(stmt);
    return false;
}