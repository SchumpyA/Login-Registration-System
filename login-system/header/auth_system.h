#ifndef AUTHSYSTEM_H
#define AUTHSYSTEM_H

#include <string>
#include "sqlite3.h"

class Authorizing_System {
    public:
        Authorizing_System(sqlite3* database);
        bool registerUser(const std::string& username, const std::string& password);
        bool loginUser(const std::string& username, const std::string& password);
    private:
        sqlite3* db;
};

#endif