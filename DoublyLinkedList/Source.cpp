#include <iostream>
#include "MyDoublyLinkedList.h"
#include <string>
using namespace std;

void printMenu() {
	cout << "MENU\n";
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
	int choice = 0;
	while (choice != 7) {
		switch (choice) {
		case 0:
			cout << "What number would you like to add?: ";
			cin >> num;
			dList->insert(num);
			printMenu();
			cin >> choice;
			break;
		case 1:
			cout << "printing list...\n";
			dList->printList();
			cout << "Which node would you like to delete?: ";
			cin >> num;
			dList->deleteNode(num);
			printMenu(); 
			cin >> choice;
			break;
		case 2:
			cout << "Prining list...\n";
			dList->printList();
			cout << "Which node's data would you like to see?: ";
			cin >> num;
			cout << "Data: " << dList->getData(num) << endl;
			printMenu();
			cin >> choice;
			break;
		case 3: 
			cout << "Head: " << dList->getHead() << endl;
			printMenu();
			cin >> choice;
			break;
		case 4:
			cout << "Tail: " << dList->getTail() << endl;
			printMenu();
			cin >> choice;
			break;
		case 5:
			cout << "Doubly linked list size: " << dList->getSize() << endl;
			printMenu();
			cin >> choice;
			break;
		case 6:
			dList->printList();
			printMenu();
			cin >> choice;
			break;
		case 7:
			dList->printIndexes();
			printMenu();
			cin >> choice;
			break;
		case 8:
			cout << "Thank you, bye!";
			cin >> choice;
			break;
		default:
			cout << "Not a valid choice, please try again";
			printMenu();
			cin >> choice;
			break;
		}
	}
	
}

int main() {
	MyDoublyLinkedList<int>* dlinked = new MyDoublyLinkedList<int>();
	menu(dlinked);
	//MyDoublyLinkedList<int> dlinked;

	//dlinked.append(10);
	//dlinked.append(16);
	//dlinked.append(12);
	//dlinked.append(14);
	//dlinked.append(18);
	//dlinked.append(15);
	//dlinked.append(58);
	//dlinked.insert(1);
	//dlinked.insert(2);
	//dlinked.insert(3);
	//dlinked.insert(4);
	//dlinked.insert(5);
	//dlinked.insert(6);

	//cout << "head: " << dlinked.getHead() << "\n";
	//cout << "tail: " << dlinked.getTail() << "\n";
	//dlinked.printList();

	//cout << "\nIndexes of nodes\n";
	//dlinked.printIndexes();

	//cout << "\nSize of list\n";
	//cout << dlinked.getSize();

	//cout << "\n\nDeleting\n";
	//dlinked.deleteNode(-1);

	//cout << "\nGetting node\n";
	//Node<int>* current;
	//current = dlinked.getNode(2);
	//cout << current->data;

	//cout << "\n\ngetting node data\n";
	//cout << dlinked.getData(1);

	//cout << "\n\ndeleting head\n";
	//dlinked.deleteNode(0);
	//cout << "new head: " << dlinked.getHead() << "\n";
	//dlinked.printList();
	//dlinked.printIndexes();

	//cout << "\ndeleting tail\n";
	//dlinked.deleteNode(4);
	//cout << "new tail: " << dlinked.getTail() << "\n";
	//dlinked.printList();
	//dlinked.printIndexes();

	//cout << "\ndeleting node\n";
	//dlinked.deleteNode(1);
	//dlinked.printList();
	//dlinked.printIndexes();

	//dlinked.prepend(-1);
	//dlinked.printList();
	//dlinked.printIndexes();
}