
#ifndef USER_H
#define USER_H

#include <fstream>
#include <string>
#include <iostream>
#include <vector>
using namespace std;


struct User {
    string userName;
    string email;
    string password;
};

// Constants for bookkeeper credentials and user file
const string BOOKKEEPER_EMAIL = "anees123@gmail.com";
const string BOOKKEEPER_PASSWORD = "anees123";
const string USER_FILE = "users.txt"; // Fixed file extension to .txt

vector<User> users; // Global user list

// Function to login as bookkeeper
bool bookkeeperLogin(bool& BookkeeperLogIn) {
    string email, password;
    cout << "Enter bookkeeper email: ";
    cin >> email;
    cout << "Enter bookkeeper password: ";
    cin >> password;

    if (email == BOOKKEEPER_EMAIL && password == BOOKKEEPER_PASSWORD) {
        BookkeeperLogIn = true;
        cout << "Bookkeeper logged in successfully.\n";
        return true;
    }
    else {
        BookkeeperLogIn = false;
        cout << "Invalid bookkeeper credentials.\n";
        return false;
    }
}

// Function to login as a user
bool userLogin(User& logInUser) {
    string email, password;

    cout << "Enter email: ";
    cin >> email;
    cout << "Enter password: ";
    cin >> password;

    ifstream file(USER_FILE);
    if (!file) {
        cout << "Error: Could not open user file.\n";
        return false;
    }

    string storedEmail, storedPassword;
    while (file >> storedEmail >> storedPassword) {
        if (email == storedEmail && password == storedPassword) {
            logInUser.email = storedEmail;
            logInUser.password = storedPassword;
            cout << "User logged in successfully.\n";
            file.close();
            return true;
        }
    }

    file.close();
    cout << "Invalid email or password.\n";
    return false;
}

// Function to register a new user
void registerUser() {
    User newUser;
    cout << "Enter email: ";
    cin.ignore(); // To clear the input buffer
    getline(cin, newUser.email);

    cout << "Enter username: ";
    getline(cin, newUser.userName);

    cout << "Enter password: ";
    getline(cin, newUser.password);

    // Save the user to the global user list
    users.push_back(newUser);

    // Append the new user to the user file
    ofstream file(USER_FILE, ios::app);
    if (file.is_open()) {
        file << newUser.email << " " << newUser.password << "\n";
        file.close();
        cout << "User registered successfully.\n";
    }
    else {
        cout << "Error: Could not open the user file.\n";
    }
}

#endif 


