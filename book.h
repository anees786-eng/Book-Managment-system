
#ifndef BOOK_H
#define BOOK_H
#include"user.h"
#include<stdexcept>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// Struct to store book details
struct Book {
    int bookID;
    string title;
    string authorName;
    int year;
    int availableCopies;
    void display()const {

        cout << "Book ID: " << bookID
            << ", Title: " << title
            << ", Author: " << authorName
            << ", Year: " << year
            << ", Available Copies: " << availableCopies << "\n";
    }
};

// Vector to store books
vector<Book> books;
vector<int>borrowbook;
//vector<User> users;
// Function to save books to a file

void saveBooksToFile(const string& filename = "books.txt") {
    ofstream outfile(filename);
    if (!outfile.is_open()) {
        cout << "Error: Could not open the file for saving books.\n";
        return;
    }

    for (const auto& book : books) {
        outfile
            << book.bookID << "\n"
           << book.title << "\n"
             << book.authorName << "\n"
            << book.year << "\n"
            << book.availableCopies << "\n";
           
    }
    outfile.close();
}


// Function to add a new book

void addBook(const string& filename = "books.txt") {
    Book newBook;

    try {
        // Find the next bookID based on the file data
        ifstream inFile(filename);
        if (!inFile) {
            throw runtime_error("Error: Could not open the file for reading.");
        }

        int nextbookID = 1;  // Default to 1 if no file or no books
        int bookID, year;
        string title, authorName;
        int availableCopies;

        while (inFile >> bookID) {  // Read until end of file
            inFile.ignore();  // Ignore the value
            getline(inFile, title);  // Read title
            getline(inFile, authorName);  // Read author name
            inFile >> availableCopies;  // Read available copies
            inFile.ignore();
            inFile >> year;  // Read year
            inFile.ignore();  // Ignore the newline after year

            // Update nextbookID to be the highest bookID + 1
            if (bookID >= nextbookID) {
                nextbookID = bookID + 1;
            }
        }
        inFile.close();

        // Get book details from the user
        cout << "Enter Book Title: ";
        cin.ignore();  // To clear any remaining newline
        getline(cin, newBook.title);

        cout << "Enter Author Name: ";
        getline(cin, newBook.authorName);

        cout << "Enter Publication Year: ";
        if (!(cin >> newBook.year)) {
            throw invalid_argument("Invalid input for year. Please enter a valid number.");
        }
        cin.ignore();  // Ignore the newline after entering the year

        cout << "Enter Number of Available Copies: ";
        if (!(cin >> newBook.availableCopies)) {
            throw invalid_argument("Invalid input for available copies. Please enter a valid number.");
        }

        // Set the new book's ID to the next available bookID
        newBook.bookID = nextbookID;

        // Add the book to the vector
        books.push_back(newBook);

        

        cout << "Book added successfully.\n";
        saveBooksToFile();
    }
    catch (const runtime_error& e) {
        cerr << e.what() << "\n";
    }
    catch (const invalid_argument& e) {
        cerr << e.what() << "\n";
        cin.clear();  // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore invalid input
    }
   
}

// Function to display all books

void displayBooks(const string& filename = "books.txt") {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Error: Could not open file '" << filename << "'\n";
        return;
    }

    vector<Book> books;
    int bookID, year, availableCopies;
    string title, authorName;

    while (inFile >> bookID) {
        inFile.ignore();  // Ignore the newline after the bookID
        getline(inFile, title);
        getline(inFile, authorName);
        inFile >> year;
        inFile.ignore();
        inFile >> availableCopies;
        inFile.ignore();  // Ignore the newline after the year

        books.push_back({ bookID, title, authorName, year,availableCopies});
    }
    if (books.empty()) {
        cout << "No books available.\n";
        return;
    }

    cout << "Book Inventory:\n";
    for (const auto& book : books) {
        book.display(); // Call the display function
    }
}


// Function to update a book's details
void updateBook(const string& filename = "books.txt") {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Error: Could not open file '" << filename << "'\n";
        return;
    }

    vector<Book> books;
    int bookID, year, availableCopies;
    string title, authorName;

    while (inFile >> bookID) {
        inFile.ignore();  // Ignore the newline after the bookID
        getline(inFile, title);
        getline(inFile, authorName);
        inFile >> year;
        inFile >> availableCopies;
        inFile.ignore();  // Ignore the newline after the year

        books.push_back({ bookID, title, authorName, year,availableCopies});


        int bookID;
        cout << "Enter Book ID to update: ";
        cin >> bookID;
        cin.ignore();

        for (auto& book : books) {
            if (book.bookID == bookID) {
                cout << "Current Title: " << book.title << "\n";
                cout << "Enter New Title: ";
                getline(cin, book.title);

                cout << "Current Author: " << book.authorName << "\n";
                cout << "Enter New Author: ";
                getline(cin, book.authorName);

                cout << "Current Year: " << book.year << "\n";
                cout << "Enter New Year: ";
                cin >> book.year;

                cout << "Current Available Copies: " << book.availableCopies << "\n";
                cout << "Enter New Available Copies: ";
                cin >> book.availableCopies;

                cout << "Book details updated successfully.\n";
                return;
            }
        }
        cout << "Book with ID " << bookID << " not found.\n";
    }

}
// Function to search for books by title or author
void searchBooks(const string& filename = "books.txt") {
    string rol;
    cin.ignore();
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Error: Could not open file '" << filename << "'\n";
        return;
    }

    vector<Book> books;
    int bookID, year, availableCopies;
    string title, authorName;

    while (inFile >> bookID) {
        inFile.ignore();  // Ignore the newline after the bookID
        getline(inFile, title);
        getline(inFile, authorName);
        inFile >> year;
        inFile >> availableCopies;
      
        inFile.ignore();  // Ignore the newline after the year

        books.push_back({ bookID, title, authorName, year,availableCopies});
    }
    cout << "Enter book title or author to search: ";
    getline(cin, rol);

    bool found = false;
    for (const auto& book : books) {
        if (book.title.find(rol) != string::npos || book.authorName.find(rol) != string::npos) {
            cout << "Book ID: " << book.bookID
                << ", Title: " << book.title
                << ", Author: " << book.authorName
                << ", Year: " << book.year
                << ", Available Copies: " << book.availableCopies << "\n";
            found = true;
        }
    }

    if (!found) {
        cout << "No books found for the search .\n";
    }
}

void deletebooks(const string& filename = "books.txt") {
    ifstream inFile(filename);
    if (!inFile) {
    cout << "Error: Could not open file '" << filename << "'\n";
        return;
    }

    vector<Book> books;
    int bookID, year, availableCopies;
    string title, authorName;

    // Read books from file into a vector
    while (inFile >> bookID) {
        inFile.ignore();  // Ignore the newline after the bookID
        getline(inFile, title);
        getline(inFile, authorName);
        inFile >> year;
        inFile >> availableCopies;
        inFile.ignore();  // Ignore the newline after the year

        books.push_back({ bookID, title, authorName, year,availableCopies});
    }
    inFile.close();  // Close the input file

    cout << "Enter Book ID to delete: ";
    cin >> bookID;

    // Find and delete the book from the vector
    bool found = false;
    for (auto it = books.begin(); it != books.end(); ) {
        if (it->bookID == bookID) {
            it = books.erase(it); // Erase returns the next iterator
            found = true;
            cout << "Book deleted successfully.\n";
            break; // Exit after deleting the book
        } else {
           it;
        }
    }

    if (!found) {
        cout << "book not found. \n";
    }

    // Write updated vector back to the file
    ofstream outFile(filename);
    if (!outFile) {
    cout << "Error: Could not open file '" << filename << "' for writing.\n";
        return;
    }

    for (const auto& book : books) {
        outFile << book.bookID << "\n"
            << book.title << "\n"
            << book.authorName << "\n"
            << book.year << "\n"
            << book.availableCopies << "\n";
       
    }
    outFile.close();
}


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
    
            books.push_back({ bookID, title, authorName, year,availableCopies});
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
                string userFile =  "userid.txt";
                ofstream outFile(userFile, ios::app);  // Open in append mode
                if (outFile) {
                    outFile << bookID << "\n";  // Save the bookID
                    outFile.close();
                    cout << "Book borrowed successfully and record in file '" << userFile << "'.\n";
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

    // If no book was found with the given ID
    cout << "Book not found.\n";
}

void returnBook(vector<Book>& books, User& user) {
    //int bookID;
    const string& userfile = "userid.txt";
    ifstream inFile(userfile);
    if (!inFile) {
        cout << "Error: Could not open file '" << userfile << "'\n";
        return;
    }
    int bookID;
    while (inFile >> bookID) {
        user.borrowedBooks.push_back(bookID);
        inFile.ignore();  // Ignore the newline after the bookID
        books.push_back({ bookID });
    }
    cout << "Enter Book ID to return: ";
    cin >> bookID;

    // Check if the user has borrowed this book
    auto it = find(user.borrowedBooks.begin(), user.borrowedBooks.end(), bookID);
    if (it == user.borrowedBooks.end()) {
        cout << "You have not borrowed this book.\n";
        return;
    }

    // Search for the book in the library
    for (auto& book : books) {
        if (book.bookID == bookID) { // If book found
            book.availableCopies++;  // Increment available copies in the library

            // Remove the book ID from the user's borrowedBooks list
            user.borrowedBooks.erase(it);

            // Update the user's borrowed book file
            string userFile =  "userid.txt";
            ifstream inFile(userFile);
            vector<int> currentBorrowed;

            if (inFile) {
                int id;
                while (inFile >> id) {
                    if (id != bookID) { 
                        currentBorrowed.push_back(id);
                    }
                }
                inFile.close();
            }

            // Write updated list back to the user's file
            ofstream outFile(userFile);
            if (outFile) {
                for (int id : currentBorrowed) {
                    outFile << id << "\n";
                }
                outFile.close();
            }
            else {
                cout << "Error: Could not update user's borrowed file.\n";
            }

            cout << "Book returned successfully.\n";
            return;
        }
    }

    // If the book is not found in the library
    cout << "Book not found in the library.\n";
}
#endif