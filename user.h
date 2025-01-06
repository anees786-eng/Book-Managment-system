
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
    string input, password;
    bool log = false;  // Flag to indicate login status

    // Prompt for email/username and password
    cout << "Enter email or username: ";
    cin >> input;
    cout << "Enter password: ";
    cin >> password;

    ifstream file(USER_FILE);
    if (!file.is_open()) {
        cerr << "Error: Could not open file '" << USER_FILE << "'\n";
        return false;
    }

    string storedEmail, storedUserName, storedPassword;

    // Read user records from the file
    while (file >> storedEmail >> storedUserName >> storedPassword) {
        // Check if the input matches either the email or username
        if ((input == storedEmail || input == storedUserName) && password == storedPassword) {
            log = true;  // Credentials match
            logInUser.email = storedEmail;
            logInUser.userName = storedUserName;
            logInUser.password = storedPassword;
            break;  // Exit loop on successful login
        }
    }

    file.close();

    if (log) {
        cout << "User logged in successfully.\n";
    }
    else {
        cout << "Invalid email/username or password.\n";
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

    // Save the user to the global user list (temporary storage of user records)
    users.push_back(newUser);
    
    // Append the new user to the user file
    ofstream fileOut(USER_FILE, ios::app);
    if (fileOut.is_open()) {
        fileOut 
            << newUser.email << "\n"
            << newUser.userName << "\n"
            << newUser.password << "\n";
        fileOut.close();
        cout << "User registered successfully.\n";
    }
    else {
        cout << "Error: Could not open the user file for writing.\n";
    }
}


#endif 


