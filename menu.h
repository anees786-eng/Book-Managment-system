#ifndef MENU_H
#define MENU_H
#include <iostream>
using namespace std;
void ShowBookKaperMenu() {
	cout << "\n--- Book kaper Menu ---\n";
	cout << "1: Add book \n";
	cout << "2: Display book \n";
	cout << "3: Update book \n";
	cout << "4: Delete book \n";
	cout << "5: Borrow book \n";
	cout << "6: Return book \n";
	cout << "7: Search book \n";
	cout << "8: Exit \n";
}

void ShowUserMenu() {
	cout << "\n--- User Menu ---\n";
	cout << "1: Borrow book \n";
	cout << "2: Search  book \n";
	cout << "3: Return book \n";
}


#endif