#ifndef DATABASE_H
#define DATABASE_H

#include "sqlite3.h"

class Database {  // simple wrapper for the SQLite database
    public:
        sqlite3* db;
        Database(const char* filename);
        ~Database();
        void init();
};

#endif