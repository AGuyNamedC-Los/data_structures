// BasicTree.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include "BasicTree.h"
using namespace std;

void menuOptions() {
     cout << "********************\n";
     cout << "0 - add node to tree\n";
     cout << "1 - delete node from tree\n";
     cout << "2 - print BFS\n";
     cout << "3 - print DFS\n";
     cout << "9 - exit\n";
     cout << "********************\n";
}

void basicTreeMenu() {
     BasicTree<int> basicTree;
     int choice = 0;
     int num = 0;
     char quit = 'q';

     while (choice != 9) {
          switch (choice) {
          case 0:
               cout << "number to add to tree: ";
               cin >> num;
               basicTree.insert(num);
               menuOptions();
               cout << "\nmenu choice: ";
               cin >> choice;
               break;
          case 1:
               cout << "delete node from tree: ";
               cin >> num;
               basicTree.deleteNode(num);
               menuOptions();
               cout << "\nmenu choice: ";
               cin >> choice;
               break;
          case 2:
               cout << "printing tree...\n";
               basicTree.printBFS();
               cout << endl;
               menuOptions();
               cout << "\nmenu choice: ";
               cin >> choice;
               break;
          case 3:
               cout << "printing tree...\n";
               basicTree.printDFS();
               menuOptions();
               cout << "\nmenu choice: ";
               cin >> choice;
               break;
          default:
               cout << "invalid menu option!\n";
               cout << "try again\n";
               menuOptions();
               cout << "\nmenu choice: ";
               cin >> choice;
               break;
          }
     }
}

int main()
{
     basicTreeMenu();
    //cout << "Hello World!\n";
    //BasicTree<int> tree;

    //tree.insert(50);
    //tree.deleteNode(50);
    //cout << "TREE: ";
    //tree.printDFS();
    //cout << "\n";


    /*
              10
            /    \
           6      12
          / \     / \
         5   7   11  13
    */

    /*
    tree.insert(10);
    tree.insert(12);
    tree.insert(6);
    tree.insert(7);
    tree.insert(5);
    tree.insert(11);
    tree.insert(13);


    tree.printDFS();
    cout << "\n";
    tree.printBFS();
    cout << "\n";
    Node<int>* node = tree.getNode(12);
    cout << "node: " << node->data << "\n";
    int nodeData = tree.getNodeData(12);
    if (nodeData == 0) cout << "couldn't find it!\n";
    cout << "node's data: " << nodeData << endl;
    */
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
