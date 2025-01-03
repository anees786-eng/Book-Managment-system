
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
    vector<int> borrowedBooks;
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
        cout << "Invalid bookkeeper gmail and password .\n";
        return false;
    }
}

// Function to login as a user

bool userLogin(User& logInUser) {
    string email, password;
    bool  log = false;  // Flag to indicate login status

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
            log = true;  // Set flag to true when credentials match
            logInUser.email = storedEmail;
            logInUser.password = storedPassword;
            break;  // Exit loop early as login is successful
        }
    }

    file.close();

    if (log) {
        cout << "User logged in successfully.\n";
    }
    else {
        cout << "Invalid email or password.\n";
    }

    return log;
}

// Function to register a new user

void registerUser() {
    User newUser;
    bool emailExists = false;  // Flag to indicate if the email already exists

    cout << "Enter email: ";
    cin.ignore(); // To clear the input buffer
    getline(cin, newUser.email);

    cout << "Enter username: ";
    getline(cin, newUser.userName);

    cout << "Enter password: ";
    getline(cin, newUser.password);

    // Check if the email already exists in the file
    ifstream fileIn(USER_FILE);
    if (fileIn.is_open()) {
        string storedEmail, storedPassword;
        while (fileIn >> storedEmail >> storedPassword) {
            if (storedEmail == newUser.email) {
                emailExists = true;  // Set flag to true if email is found
                break;  // No need to continue checking
            }
        }
        fileIn.close();
    }
    else {
        cout << "Error: Could not open the user file for reading.\n";
        return;
    }

    // If email exists, notify the user and exit the function
    if (emailExists) {
        cout << "Error: Email already exists. Please use a different email.\n";
        return;
    }

    // Save the user to the global user list
    users.push_back(newUser);

    // Append the new user to the user file
    ofstream fileOut(USER_FILE, ios::app);
    if (fileOut.is_open()) {
        fileOut << newUser.email << " " << newUser.password << "\n";
        fileOut.close();
        cout << "User registered successfully.\n";
    }
    else {
        cout << "Error: Could not open the user file for writing.\n";
    }
}


#endif 


