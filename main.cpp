#include "user.h"
#include "book.h"
#include<iostream>
using namespace std;

int main() {
    try {
        int choice;
        bool BookkeeperLogIn;
        User logInUser;

        do {
            cout << "\nLibrary Management System\n";
            cout << "1. Bookkeeper Login\n";
            cout << "2. User Registration\n";
            cout << "3. User Login\n";
            cout << "4. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            // Validate the input
            if (cin.fail()) {
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                cout << "Invalid input. Please enter a number between 1 and 4.\n";
                continue; 
            }

            switch (choice) {
            case 1:
                if (bookkeeperLogin(BookkeeperLogIn)) {
                    int bookkeeperChoice;
                    do {
                        cout << "\nBookkeeper Menu\n";
                        cout << "1. Add Book\n";
                        cout << "2. Display Books\n";
                        cout << "3. Search Books\n";
                        cout << "4. Update Book\n";
                        cout << "5. Delete Book\n";
                        cout << "6. Logout\n";
                        cout << "Enter your choice: ";
                        cin >> bookkeeperChoice;

                        // Validate the input
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Invalid input. Please enter a number between 1 and 6.\n";
                            continue;
                        }

                        switch (bookkeeperChoice) {
                        case 1:
                            try {
                                addBook();
                            }
                            catch (const exception& e) {
                                cout << "Error while adding a book: " << e.what() << endl;
                            }
                            break;
                        case 2:
                            try {
                                displayBooks();
                            }
                            catch (const exception& e) {
                                cout << "Error while displaying books: " << e.what() << endl;
                            }
                            break;
                        case 3:
                            try {
                                searchBooks();
                            }
                            catch (const exception& e) {
                                cout << "Error while searching books: " << e.what() << endl;
                            }
                            break;
                        case 4:
                            try {
                                updateBook();
                            }
                            catch (const exception& e) {
                                cout << "Error while updating book: " << e.what() << endl;
                            }
                            break;
                        case 5:
                            try {
                                deletebooks();
                            }
                            catch (const exception& e) {
                                cout << "Error while deleting book: " << e.what() << endl;
                            }
                            break;
                        case 6:
                            cout << "Logging out.\n";
                            break;
                        default:
                            cout << "Invalid choice. Please enter a number between 1 and 6.\n";
                        }
                    } while (bookkeeperChoice != 6);
                }
                break;

            case 2:
                try {
                    registerUser();
                }
                catch (const exception& e) {
                    cout << "Error during user registration: " << e.what() << endl;
                }
                break;

            case 3:
                if (userLogin(logInUser)) {
                    int userChoice;
                    do {
                        cout << "\nUser Menu\n";
                        cout << "1. Borrow Book\n";
                        cout << "2. Return Books\n";
                        cout << "3. Search Books\n";
                        cout << "4. Logout\n";
                        cout << "Enter your choice: ";
                        cin >> userChoice;

                        // Validate the input
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Invalid input. Please enter a number between 1 and 4.\n";
                            continue;
                        }

                        switch (userChoice) {
                        case 1:
                            try {
                                borrowBook(books, logInUser);
                            }
                            catch (const exception& e) {
                                cout << "Error while borrowing a book: " << e.what() << endl;
                            }
                            break;
                        case 2:
                            try {
                                returnBook(books, logInUser);
                            }
                            catch (const exception& e) {
                                cout << "Error while returning a book: " << e.what() << endl;
                            }
                            break;
                        case 3:
                            try {
                                searchBooks();
                            }
                            catch (const exception& e) {
                                cout << "Error while searching books: " << e.what() << endl;
                            }
                            break;
                        case 4:
                            cout << "Logging out.\n";
                            break;
                        default:
                            cout << "Invalid choice. Please enter a number between 1 and 4.\n";
                        }
                    } while (userChoice != 4);
                }
                break;

            case 4:
                cout << "Exiting the system. Goodbye!\n";
                break;

            default:
                cout << "Invalid choice. Please enter a number between 1 and 4.\n";
            }
        } while (choice != 4);

    }
    catch (const exception& e) {
        cout << " error:The system will now terminate " << e.what() << endl;
  
    }

    return 0;
}



