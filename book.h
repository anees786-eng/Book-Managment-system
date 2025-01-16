#ifndef BOOK_H
#define BOOK_H
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

        //// Save the updated list of books to the file
        ofstream outFile(filename, ios::app);
        if (!outFile) {
            throw runtime_error("Error: Could not open the file for saving.");
        }
        outFile << newBook.bookID << "\n"
            << newBook.title << "\n"
            << newBook.authorName << "\n"
            << newBook.year << "\n"
            << newBook.availableCopies << "\n";
                outFile.close();
             cout << "Book added successfully.\n";
    }
    catch (const runtime_error& e) {
        cout << e.what() << "\n";
    }
    catch (const invalid_argument& e) {
        cout << e.what() << "\n";
        cin.clear();  // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore invalid input
        
    }
   
}

// Function to display all books

void displayBooks(const string& filename = "books.txt") {
    ifstream inFile(filename);
    if (!inFile) {
        cout << "Error: Could not open file '" << filename << "'\n";
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
        cout << "Error: Could not open file '" << filename << "'\n";
        return;
    }

    vector<Book> books;
    int bookID, year, availableCopies;
    string title, authorName;

    // Read all books from the file into the vector
    while (inFile >> bookID) {
        inFile.ignore(); // Ignore the newline after the bookID
        getline(inFile, title);
        getline(inFile, authorName);
        inFile >> year;
        inFile >> availableCopies;
        inFile.ignore(); // Ignore the newline after the year

        books.push_back({ bookID, title, authorName, year, availableCopies });
     }
    inFile.close();

    // Ask for the book ID to update
    cout << "Enter Book ID to update: ";
    cin >> bookID;
    cin.ignore();
    // Search for the book and update its details
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
            break;
        }
        else {
            cout << "books not found.\n";
        }
    }
    // Save the updated list of books back to the file
    ofstream outFile(filename);
    if (!outFile) {
        cout << "Error: Could not open the file for saving.\n";
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

// Function to search for books by title or author
 void searchBooks(const string& filename = "books.txt") {
     string rol;
    cin.ignore();  // Clear input buffer
    ifstream inFile(filename);
    if (!inFile) {
        cout << "Error: Could not open file '" << filename << "'\n";
        return;
    }

    vector<Book> books;
    int bookID, year, availableCopies;
    string title, authorName;

    // Load books from the file into the vector
    while (inFile >> bookID) {
        inFile.ignore();  // Ignore the newline after the bookID
        getline(inFile, title);
        getline(inFile, authorName);
        inFile >> year;
        inFile >> availableCopies;
        inFile.ignore();  // Ignore the newline after the year
        books.push_back({ bookID, title, authorName, year, availableCopies });
    }
    inFile.close();  // Close the file after reading

    // Search for books
    cout << "Enter book title or author to search: ";
    getline(cin, rol);
    for (auto& book : books) {
        if (book.title.find(rol) != string::npos || book.authorName.find(rol) != string::npos) {
            
            cout << "Book ID: " << book.bookID
                << ", Title: " << book.title
                << ", Author: " << book.authorName
                << ", Year: " << book.year
                << ", Available Copies: " << book.availableCopies << "\n";
            
            // Save the updated books back to the file
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
            return;     // Exit the loop after processing the first found book
        }
    }

     {
        cout << "No books found for the search.\n";
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
    inFile.close();  // Close the input fil
    cout << "Enter Book ID to delete: ";
    cin >> bookID;
    // Find and delete the book from the vector
    bool found = false;
    for (auto it = books.begin(); it != books.end(); ) {
        if (it->bookID == bookID) {
            it = books.erase(it); 
            found = true;
            cout << "Book deleted successfully.\n";
            break; // Exit after deleting the book
        } else {
         ++it;
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
#endif