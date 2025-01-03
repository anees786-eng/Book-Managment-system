
#ifndef BOOK_H
#define BOOK_H
#include"user.h"

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
};

// Vector to store books
vector<Book> books;
vector<int>borrowbook;
//vector<User> users;
// Function to save books to a file
void saveBooks(const string& filename = "books.txt") {
    ofstream outfile(filename, ios::app);
    if (!outfile.is_open()) {
        cout << "Error: Could not open the file for saving books.\n";
        return;
    }

    for (const auto& book : books) {
        outfile << book.bookID << "\n "
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

    // Find the next bookID based on the file data
    ifstream inFile(filename);
    int nextbookID = 1;  // Default to 1 if no file or no books

    if (inFile) {
        int bookID, year;
        string title, authorName, availableCopies;
        while (inFile >> bookID) {  // Read until end of file
            inFile.ignore();  // Ignore the value
            getline(inFile, title);  // Read title
            getline(inFile, authorName);  // Read author name
            getline(inFile, availableCopies);  // Read available copies
            inFile >> year;  // Read year
            inFile.ignore();  // Ignore the newline after year

            // Update nextbookID to be the highest bookID + 1
            if (bookID >= nextbookID) {
                nextbookID = bookID + 1;
            }
        }
        inFile.close();
    }

    // Get book details from the user
    cout << "Enter Book Title: ";
    cin.ignore();  // To clear any remaining newline
    getline(cin, newBook.title);

    cout << "Enter Author Name: ";
    getline(cin, newBook.authorName);

    cout << "Enter Publication Year: ";
    cin >> newBook.year;
    cin.ignore();  // Ignore the newline after entering the year

    cout << "Enter Number of Available Copies: ";
    /*getline(cin, newBook.availableCopies);*/
    cin>> newBook.availableCopies;
    // Set the new book's ID to the next available bookID
    newBook.bookID = nextbookID;

    // Add the book to the vector
    books.push_back(newBook);

    // Save the updated list of books to the file
    saveBooks(filename);

    cout << "Book added successfully.\n";
}


// Function to display all books
void displayBooks(const string& filename = "books.txt") {
    
        cout << "Book Inventory:\n";
        for (const auto& book : books) {
            cout << "Book ID: " << book.bookID
                << ", Title: " << book.title
                << ", Author: " << book.authorName
                << ", Year: " << book.year
                << ", Available Copies: " << book.availableCopies << "\n";
        }
    }

// Function to update a book's details
void updateBook() {
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

// Function to search for books by title or author
void searchBooks() {
    string rol;
    cin.ignore();
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


void deletebooks() {
       int bookID;
            cout << "Enter Book ID to delete: ";
            cin >> bookID;
            for (auto it = books.begin(); it != books.end(); ) {
                if (it->bookID == bookID) {
                    it = books.erase(it); // Erase returns the next iterator
                    cout << "book  delete successfully.\n";
                }
              
                else {
                    cout << "Book not found.\n";
                }
              
            }
        }
    


    void borrowBook(vector<Book>& books, User& user) {
        int bookID;
        cout << "Enter book ID to borrow: ";
        cin >> bookID;
    
        // Search for the book by ID
        for (auto& book : books) {
            if (book.bookID == bookID) { // Check if book ID matches
                if (book.availableCopies > 0) {
                    // Deduct one copy and add book ID to user's borrowedBooks
                    book.availableCopies--;
                    //user.borrowBook; // Add bookID to the user's list
                    cout << "Book borrowed successfully.\n";
                }
                else {
                    cout << "No copies available for this book.\n";
                }
                return; // Exit after processing the book
            }
        }
    
        // If no book was found with the given ID
        cout << "Book not found.\n";
    }
#endif // BOOK_H
