#include <iostream>
#include "../header/auth_system.h"
#include "../header/database.h"
using namespace std;

// to complie: g++ login-system/src/main.cpp login-system/src/database.cpp login-system/src/auth_system.cpp sqlite3.o -o  run_login

int main() {
    Database userDataBase("users.db");  // set up database and authorization
    userDataBase.init();
    Authorizing_System auth(userDataBase.db);

    int choice;
    string username, password;

    while(true) {
        cout << endl << "1. Register" << endl << "2. Login" << endl << "3. Exit" << endl << "Choice: ";
        cin >> choice;

        if (choice == 1) {  // register user
            cout << "Your new username: ";
            cin >> username;
            cout << "Your new password: ";
            cin >> password;

            if(auth.registerUser(username, password)) {
                cout << "Your username and password have been registered" << endl;
            }
        } else if (choice == 2) {  // attempt login
            cout << "Username: ";
            cin >> username;
            cout << "Password: ";
            cin >> password;

            if (auth.loginUser(username, password)) {
                cout << "Login Successfull" << endl;
            } else {
                cout << "Login Failed" << endl;
            }
        } else if (choice == 3) {
            break; // exit program
        } else {
            cout << "Not valid input, try again" << endl;
        }
    }

    return 0;
}