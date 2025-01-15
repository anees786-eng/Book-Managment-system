
#ifndef USER_H
#define USER_H
#include"book.h"
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
                cout << "Error: Email already exists. Please use a different email.\n";
                fileIn.close(); // Close the file before returning
                return;         // Exit the function
            }
        }
        fileIn.close();
    }
    else {
        cout << "Error: Could not open the user file for reading.\n";
        return;
    }
    // Append the new user to the user file
    ofstream fileOut(USER_FILE, ios::app);
    if (fileOut.is_open()) {
        fileOut << newUser.email << "\n"
            << newUser.userName << "\n"
            << newUser.password << "\n";
        fileOut.close();
        cout << "User registered successfully.\n";
    }
    else {
        cout << "Error: Could not open the user file for writing.\n";
    }
}


//function use to borrow books
void borrowBook(vector<Book>& books, User& user) {
    //int bookID;
    const string& filename = "books.txt";
    ifstream inFile(filename);
    if (!inFile) {
        cout << "Error: Could not open file '" << filename << "'\n";
        return;
    }
    int bookID, year, availableCopies;
    string title, authorName;

    while (inFile >> bookID) {
        inFile.ignore();  // Ignore the newline after the bookID
        getline(inFile, title);
        getline(inFile, authorName);
        inFile >> year;
        inFile >> availableCopies;
        inFile.ignore();  // Ignore the newline after the year

        books.push_back({ bookID, title, authorName, year,availableCopies });
    }
    cout << "Enter book ID to borrow: ";
    cin >> bookID;

    // Search for the book by ID
    for (auto& book : books) {
        if (book.bookID == bookID) { // Check if book ID matches
            if (book.availableCopies > 0) {
                // Deduct one copy
                book.availableCopies--;

                // Add bookID to user's borrowedBooks list
                user.borrowedBooks.push_back(bookID);

                // Save bookID to user-specific file
                string userFile = "userid.txt";
                ofstream outFile(userFile, ios::app);  // Open in append mode
                if (outFile) {
                    outFile << bookID << "\n";  // Save the bookID
                    outFile.close();
                    cout << "Book borrowed successfully and store in file '" << userFile << "'.\n";
                }
                else {
                    cout << "Error: Could not write to user file.\n";
                }

                return;  // Exit after successful borrowing
            }
            else {
                cout << "No copies available for this book.\n";
                return;
            }
        }
    }


}
//funtion use to return books.
void returnBook(vector<Book>& books, User& user) {
    const string userFile = "userid.txt";

    ifstream inFile(userFile);
    if (!inFile) {
        cout << "Error: Could not open file '" << userFile << "'\n";
        return;
    }
    int bookID;
    user.borrowedBooks.clear();
    while (inFile >> bookID) {
        user.borrowedBooks.push_back(bookID);
        inFile.ignore();  // Ignore the newline after the bookID
        books.push_back({ bookID });
    }
    // Ask the user for the book ID to return
    cout << "Enter Book ID to return: ";
    //int bookID;

    cin >> bookID;

    // Check if the user has borrowed this book
    auto it = find(user.borrowedBooks.begin(), user.borrowedBooks.end(), bookID);
    if (it == user.borrowedBooks.end()) {
        cout << "You have not borrowed this book.\n";
        return;
    }

    // Search for the book in the library
    for (auto& book : books) {
        if (book.bookID == bookID) { // If the book is found
            book.availableCopies++; // Increment available copies in the library

            // Remove the book ID from the user's borrowedBooks list
            user.borrowedBooks.erase(it);

            // Update the user's borrowed book file
            ofstream outFile(userFile);
            if (outFile) {
                for (int id : user.borrowedBooks) {
                    outFile << id << "\n";
                }
                outFile.close();
                cout << "Book returned successfully.\n";
            }
            else {
                cout << "Error: Could not update user's borrowed file.\n";
            }

            return;
        }
    }

    // If the book is not found in the library
    cout << "Book not found in the library.\n";
}

#endif 


