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
        cout << endl << "1. Register" << endl << "2. Login" << endl << "3. Remove Account" << endl << "4. Exit" << endl << "Choice: ";
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
                cout << "Username or password incorrect, login failed" << endl;
            }
        } else if (choice == 3) {
            cout << "Login to delete" << endl;
            bool looping = true;
            while(looping) {
                cout << "Username: ";
                cin >> username;
                cout << "Password: ";
                cin >> password;

                if (auth.loginUser(username, password)) {
                    cout << "Login Successfull" << endl << "Deleting account" << endl;
                    if(auth.deleteAccount(username) == true) {
                        cout << "Account Deleted" << endl;
                    } else {
                        cout << "Error Deleting Account" << endl;
                    }
                    looping = false;
                } else {
                    cout << "Username or password incorrect, login failed" << endl;
                }
            }
        } else if (choice == 4) {
            break; // exit program
        } else {
            cout << "Not valid input, try again" << endl;
        }
    }

    return 0;
}