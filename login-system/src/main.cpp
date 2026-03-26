#include <iostream>
#include "sqlite3.h"
using namespace std;

int main() {
    cout << "Hello World" << endl;

    sqlite3* db;
    if (sqlite3_open("test.db", &db) == SQLITE_OK) {
        cout << "Database opened successfully" << endl;
    } else {
        cout << "Failed to open database" << endl;
    }
    sqlite3_close(db);

    return 0;
}