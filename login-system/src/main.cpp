#include <iostream>
#include "../header/auth_system.h"
#include "../header/database.h"
using namespace std;

// to complie:
// g++ login-system/src/main.cpp login-system/src/database.cpp login-system/src/auth_system.cpp login-system/src/hash_helper.cpp sqlite3.o -lssl -lcrypto -o run_login

int main() {
    Database userDataBase("users.db");  // set up database and authorization
    userDataBase.init();
    Authorizing_System auth(userDataBase.db);

    int choice;
    string username, password, birthdate;

    while(true) {
        cout << endl << "1. Register" << endl << "2. Login" << endl << "3. Remove Account" << endl << "4. Change Password" << endl << "5. Exit" << endl << "Choice: ";
        cin >> choice;

        if (choice == 1) {  // register user
            cout << "Choose Username: ";
            cin >> username;
            cout << "Choose Password: ";
            cin >> password;
            cout << "Choose Birthdate (In case you forget password): ";
            cin >> birthdate;

            if(auth.registerUser(username, password, birthdate)) {
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
            cout << "Login to delete, or enter q/Q to quit" << endl;
            bool looping = true;
            while(looping) {
                cout << "Username: ";
                cin >> username;
                if (username == "q" || username == "Q") {
                    break;
                }
                cout << "Password: ";
                cin >> password;
                if (password == "q" || username == "Q") {
                    break;
                }

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
            cout << "1. Login to change password, 2. Enter username and birthdate, 3. Quit" << endl;
            int option;
            cin >> option;
            bool looping = true;
            while(looping) {
                if (option == 1) {
                    cout << "Enter q/Q to quit" << endl << "Username: ";
                    cin >> username;
                    if (username == "q" || username == "Q") {
                        break;
                    }
                    cout << "Password: ";
                    cin >> password;
                    if (password == "q" || username == "Q") {
                        break;
                    }

                    if (auth.loginUser(username, password)) {
                        cout << "Login Successfull" << endl << "New Password:";
                        cin >> password;
                        if(auth.changePassword(username, password)) {
                            cout << "Password changed" << endl;
                        } else {
                            cout << "Error Changing Password" << endl;
                        }
                        looping = false;
                    } else {
                        cout << "Username or password incorrect, login failed" << endl;
                    }
                } else if (option == 2) {
                    cout << "Enter q/Q to quit" << endl << "Username: ";
                    cin >> username;
                    if (username == "q" || username == "Q") {
                        break;
                    }
                    cout << "Birthdate: ";
                    cin >> birthdate;
                    if (birthdate == "q" || username == "Q") {
                        break;
                    }
                    if (auth.checkBirthdate(username, birthdate)) {
                        cout << "Login Successfull" << endl << "New Password:";
                        cin >> password;
                        if(auth.changePassword(username, password)) {
                            cout << "Password changed" << endl;
                        } else {
                            cout << "Error Changing Password" << endl;
                        }
                        looping = false;
                    } else {
                        cout << "Username or password incorrect, login failed" << endl;
                    }
                }                                
            }
        } else if (choice == 5) {
            break; // exit program
        } else {
            cout << "Not valid input, try again" << endl;
        }
    }

    return 0;
}