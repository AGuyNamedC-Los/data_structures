#include <iostream>
#include "MyDoublyLinkedList.h"
#include <string>
using namespace std;

void printMenu() {
	cout << "************************************************\n";
	cout << "                     MENU\n";
	cout << "************************************************\n";
	cout << "0 - add number\n";
	cout << "1 - delete number\n";
	cout << "2 - print specific node\n";
	cout << "3 - print head\n";
	cout << "4 - print tail\n";
	cout << "5 - get size of doubly linked list\n";
	cout << "6 - print the entire double linked list\n";
	cout << "7 - print the indexes of the double linked list\n";
	cout << "8 - quit\n";
}

/* uses ints for testing purposes */
template <typename T>
void menu(MyDoublyLinkedList<T>* dList) {
	int num;
	int choice;
	printMenu();
	cout << "menu choice: ";
	cin >> choice;
	while (choice != 8) {
		switch (choice) {
			case 0:
				cout << "What number would you like to add?: ";
				cin >> num;
				dList->insert(num);
				printMenu();
				cout << "menu choice: ";
				cin >> choice;
				break;
			case 1:
				cout << "printing list...\n";
				dList->printList();
				cout << "Which node would you like to delete?: ";
				cin >> num;
				dList->deleteNode(num);
				printMenu(); 
				cout << "menu choice: ";
				cin >> choice;
				break;
			case 2:
				cout << "Prining list...\n";
				dList->printList();
				cout << "Which node's data would you like to see?: ";
				cin >> num;
				cout << "Data: " << dList->getData(num) << endl;
				cout << "menu choice: ";
				printMenu();
				cin >> choice;
				break;
			case 3: 
				cout << "Head: " << dList->getHead() << endl;
				printMenu();
				cout << "menu choice: ";
				cin >> choice;
				break;
			case 4:
				cout << "Tail: " << dList->getTail() << endl;
				printMenu();
				cout << "menu choice: ";
				cin >> choice;
				break;
			case 5:
				cout << "Doubly linked list size: " << dList->getSize() << endl;
				printMenu();
				cout << "menu choice: ";
				cin >> choice;
				break;
			case 6:
				dList->printList();
				printMenu();
				cout << "menu choice: ";
				cin >> choice;
				break;
			case 7:
				dList->printIndexes();
				printMenu();
				cout << "menu choice: ";
				cin >> choice;
				break;
			case 8:
				cout << "Thank you, bye!";
				break;
			default:
				cout << "Not a valid choice, please try again\n";
				printMenu();
				cout << "menu choice: ";
				cin >> choice;
				break;
		}
	}
}

int main() {
	MyDoublyLinkedList<int>* dlinked = new MyDoublyLinkedList<int>();
	menu(dlinked);
	cout << "Good bye!\n";
}