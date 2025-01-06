#include "user.h"
#include "book.h"
#include<iostream>
using namespace std;


int main() {
    int choice;
   bool BookkeeperLogIn ;
    User logInUser;

    do {
        cout << "\nLibrary Management System\n";
        cout << "1. Bookkeeper Login\n";
        cout << "2. User Registration\n";
        cout << "3. User Login\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            if (bookkeeperLogin(BookkeeperLogIn)) {
                int bookkeeperChoice;
                do {
                    cout << "1. Add Book\n";
                    cout << "2. Display Books\n";
                    cout << "3. Search Books\n";
                    cout << "4. Update Book\n";
                    cout << "5. Delete Book\n";
                    cout << "6. Logout\n";
                    cout << "Enter your choice: ";
                    cin >> bookkeeperChoice;

                    switch (bookkeeperChoice) {
                    case 1: addBook(); break;
                    case 2: displayBooks();break;
                    case 3: searchBooks();break;
                    case 4: updateBook(); break;
                    case 5: deletebooks(); break;
                    case 6: cout << "Logging out.\n";     break;
                    default:
                        cout << "Invalid choice. Try again.\n";
                    }
                } while (bookkeeperChoice != 6);
            }
            break;

        case 2:registerUser(); break;
          
        case 3:
            if (userLogin(logInUser)) {
                int userChoice;
                do {
                    cout << "\nUser Menu\n";
                    cout << "1. Borrow Book\n";
                    cout << "2.  Return Books\n";
                    cout << "3. Search Books\n";
                    cout << "4. Logout\n";
                    cout << "Enter your choice: ";
                    cin >> userChoice;

                    switch (userChoice) {
                    case 1:  borrowBook(books, logInUser); break;
                    case 2:returnBook(books, logInUser); break;
                    case 3: searchBooks(); break;
                    case 4: 
                        cout << "Logging out.\n";
                        break;
                    default:
                        cout << "Invalid choice. Try again.\n";
                    }
                } while (userChoice != 4);
            }
            break;

        case 5:
            cout << "Exiting the system. Goodbye!\n";
            break;

        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}

