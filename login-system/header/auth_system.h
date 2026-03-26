#ifndef AUTHSYSTEM_H
#define AUTHSYSTEM_H

#include <string>
#include "sqlite3.h"

class Authorizing_System {  // used to handle authorizing user login and registration
    public:
        Authorizing_System(sqlite3* database);
        bool registerUser(const std::string& username, const std::string& password);
        bool loginUser(const std::string& username, const std::string& password);
        bool deleteAccount(const std::string& username);
        bool changePassword(const std::string& username, const std::string& password);
    private:
        sqlite3* db;
};

#endif