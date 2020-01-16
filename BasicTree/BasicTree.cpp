// BasicTree.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include "BasicTree.h"
using namespace std;

int main()
{
    cout << "Hello World!\n";
    BasicTree<int> tree;
    /*
              10
            /    \
           6      12
          / \     / \
         5   7   11  13
    */


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
    Node<int>* node = tree.getNode_DFS(12);
    cout << "node: " << node->data << "\n";
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
