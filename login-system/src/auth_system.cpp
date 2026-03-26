#include "../header/auth_system.h"
#include "../header/hash_helper.h"
#include <iostream>

Authorizing_System::Authorizing_System(sqlite3* database) {
    db = database;
}

bool Authorizing_System::registerUser(const std::string& username, const std::string& password, const std::string& birthdate) {
    std::string hashedPassword = hashPassword(password);
    // SQL statement with placeholders to prevent injection
    std::string sql = "INSERT INTO users (username, password, birthdate) VALUES (?, ?, ?);";
    
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    // bind username, password, and birthdate to SQL statement
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, hashedPassword.c_str(), -1, SQLITE_STATIC);  // <- hashed password
    sqlite3_bind_text(stmt, 3, birthdate.c_str(), -1, SQLITE_STATIC);

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
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

    if(sqlite3_step(stmt) == SQLITE_ROW) {
        std::string storedHash = (const char*)sqlite3_column_text(stmt, 0);  // get stored password
        sqlite3_finalize(stmt);

        std::string enteredHash = hashPassword(password);
        return storedHash == enteredHash;  // compare hashes instead of plain text
    }

    sqlite3_finalize(stmt);  // false if there is no user
    return false;
}

bool Authorizing_System::checkBirthdate(const std::string& username, const std::string& birthdate) {
    std::string sql = "SELECT birthdate FROM users WHERE username = ?;";

    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    // bind username
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

    // check if user exists
    if(sqlite3_step(stmt) == SQLITE_ROW) {
        std::string stored = (const char*)sqlite3_column_text(stmt, 0);  // get stored password

        sqlite3_finalize(stmt);
        return stored == birthdate;  // compared stored password and input password (no hashing for now)
    }

    sqlite3_finalize(stmt);  // false if there is no user
    return false;
}

// delete user account
bool Authorizing_System::deleteAccount(const std::string& username) {
    std::string sql = "DELETE FROM users WHERE username = ?;";

    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    //bind username
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

    // check if user exists and delete if it does
    if(sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        return false;  // error during delete
    }

    int changes = sqlite3_changes(db);
    sqlite3_finalize(stmt);
    return changes > 0;  // returns true if the user was deleted (there should be a change)
}

// changes user password
bool Authorizing_System::changePassword(const std::string& username, const std::string& password) {
    std::string hashedPassword = hashPassword(password);

    std::string sql = "UPDATE users SET password = ? WHERE username = ?;";

    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    // bind username and password to SQL statement
    sqlite3_bind_text(stmt, 1, hashedPassword.c_str(), -1, SQLITE_STATIC);  // hashed password
    sqlite3_bind_text(stmt, 2, username.c_str(), -1, SQLITE_STATIC);

    if(sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        return false;
    }

    // executes password change
    int changes = sqlite3_changes(db);
    sqlite3_finalize(stmt);
    return changes > 0; // true if password change succeeds
}